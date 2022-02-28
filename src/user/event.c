/*
 * event.c
 *
 *  Created on: 2015/6/25
 *      Author: jk
 */
#include <string.h>

#include "fibo_opencpu.h"
#include "nmea/gmath.h"

#include "msg.h"
#include "log.h"
#include "data.h"
#include "car.h"
#include "hardware.h"
#include "socket.h"
#include "setting.h"
#include "flash.h"
#include "watchdog.h"
#include "protocol.h"
#include "user_at.h"
#include "da14580.h"
#include "bioMsg.h"
#include "sleep.h"
#include "lis3dh.h"
#include "etcMsg.h"
#include "gps_parse.h"
#include "adc.h"
#include "audio_driver.h"
#include "request.h"
#include "user_timer.h"
#include "userMsg.h"
#include "soft_watchdog.h"
#include "accelerometer.h"

int event_fsm_running(void)
{
    softwatchdog_feed(REBOOT_NETWORK); //网络状态看门狗喂狗
    return 0;
}

static u8 isMeetOverSpeedConditions(void)
{
    if(setting.defaultConf.ccuType == TYPE_XIAOANCCU)
    {
        //小安的协议走这个超速报警
        if(setting.settingConf.isEtcOverspeedBit && (data_getData()->etc.fault & (0x01 << 6)) != 0)
        {
            LOG_DEBUG("[event] Meet XIAOAN OverSpeed Condition C1");
            return L_TRUE;
        }

        if(data_getRealEtcSpeed() >= setting.settingConf.overspeedThreshold)
        {
            LOG_DEBUG("[event] Meet XIAOAN OverSpeed Condition C2");
            return L_TRUE;
        }
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE
    || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
    || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
    || setting.defaultConf.ccuType == TYPE_TAIBITE_09)
    {
        //泰比特的协议走这个超速报警
        if(data_getRealEtcSpeed() >= setting.settingConf.overspeedThreshold)
        {
            LOG_DEBUG("[event] Meet TAIBITE OverSpeed Condition C2");
            return L_TRUE;
        }
    }
    else if(setting.defaultConf.ccuType == TYPE_NOCCU) //无控制器走这个超速报警
    {
        if(L_TRUE == car_isOverSpeed())
        {
            return L_TRUE;
        }
    }
    return L_FALSE;
}

void event_AcceleromterCheck(void)
{
    static u32 faulttime = 0;
    static short xAccBak = 0, yAccBak = 0, zAccBak = 0;
    short x_dat, y_dat, z_dat;

    bool result = lis3dh_readOutputXYZ(&x_dat, &y_dat, &z_dat);
    if(!result)
    {
        faulttime++;
    }
    else if(x_dat == xAccBak && y_dat == yAccBak && z_dat == zAccBak)
    {
        faulttime++;
    }
    else
    {
        faulttime = 0;
    }
    if(faulttime == 60)
    {
        data_getData()->isAccelerometerFault = 1;
        if(lis3dh_init() != true)//初始化有对mpu进行软复位
        {
            LOG_DEBUG("lis3dh_dmp_init error");
            data_getData()->isAccelerateInitFault = 1;
        }
        else
        {
            LOG_DEBUG("lis3dh_dmp_init success");
            data_getData()->isAccelerometerFault = 0;
            data_getData()->isAccelerateInitFault = 0;
            if(setting.settingConf.mpuAvoidanceRatio != 1)
            {
                setting.settingConf.mpuAvoidanceRatio = 1;
                settingConf_save();
            }
        }
    }
    if(faulttime >= (5 * 60 * setting.settingConf.mpuAvoidanceRatio)) //处于异常5分钟后重启
    {
        faulttime = 0;
        setting_setRebootType(REBOOT_MPUERROR);
        timer_start(TIMER_REBOOT, TIMER_MS, 300, fibo_softReset);
    }
    xAccBak = x_dat;
    yAccBak = y_dat;
    zAccBak = z_dat;
}

static void event_OverSpeedCheck(void)
{
    static u32 nowOverspeedCount = 0;
    static u32 lastOverspeedCount = 0;

    nowOverspeedCount++;
    if(nowOverspeedCount - lastOverspeedCount > 2 * setting.settingConf.checkOverSpeedTime) //避免翻转
    {
        nowOverspeedCount -= setting.settingConf.checkOverSpeedTime;
    }

    if(setting.defaultConf.isOverSpeedOn && data_getData()->workMode == NORMAL_MODE)
    {
        if(isMeetOverSpeedConditions() && data_getData()->isWheelSpinning) //有轮动时超速才报警
        {
            if((0 == lastOverspeedCount) || (nowOverspeedCount - lastOverspeedCount >= setting.settingConf.checkOverSpeedTime))
            {
                audio_playWithVolume(AUDIO_OVER_SPEED, (int)(setting.settingConf.overSpeedVolume));

                while(nowOverspeedCount > setting.settingConf.checkOverSpeedTime) //避免翻转
                {
                    nowOverspeedCount -= setting.settingConf.checkOverSpeedTime;
                }
                lastOverspeedCount = nowOverspeedCount;
            }
        }
    }
}

static void event_SleepEnvCheck(void)
{
    /*
        低电压休眠逻辑 登录状态 设防状态 没有计时定时器工作 有获取到基站定位或者GPS定位
                                                                                        */
    u32 voltage_mV = data_getData()->vehicleBattery_mV;

    LOG_DEBUG("[Event] SleepEnable:%d defendOn:%d AwakeTime:%d LoginState:%d ActiveTimerID:%d TIMERNUM:%d ALLOC:%d BLE_Alive:%d",
        setting.settingConf.isSleepEnable,
        setting_isDefendOn(),
        data_getAwakeTime(),
        data_getData()->isLogined,
        timer_isTimerSleep(),
        TIMER_NUM,
        data_getData()->malloctimes,
        data_getData()->ble_state.isDA14580Alive);

    if(setting.settingConf.isSleepEnable && setting_isDefendOn() && data_getData()->isLogined && timer_isTimerSleep() == TIMER_NUM && data_getData()->ble_state.isDA14580Alive)
    {
        // 低电压或电池不在    开始倒计时
        if(voltage_mV < setting.settingConf.protectVoltage)
        {
            data_minusAwakeTime();
            //休眠后就没有GPS定位了,进入休眠前五秒 没有定位,获取一次LBS定位;有定位,假装有LBS定位
            if(data_getAwakeTime() == 5)
            {
                if(!gps_getPosition()->isGPS)   //当前没定位
                {
                    data_getData()->lastPosition.isCLBS = L_FALSE;
                    gps_getCLBS(gps_getCLBS_proc);

                    if((data_getData()->lastPosition.tagNmeaInfo.lat < 0.0001 && data_getData()->lastPosition.tagNmeaInfo.lat > -0.0001)
                    || (data_getData()->lastPosition.tagNmeaInfo.lon < 0.0001 && data_getData()->lastPosition.tagNmeaInfo.lon > -0.0001))
                    {
                        data_getData()->lastPosition.tagNmeaInfo.lat = nmea_ndeg2degree(data_getData()->lastPosition.lbsInfo.lat);
                        data_getData()->lastPosition.tagNmeaInfo.lon = nmea_ndeg2degree(data_getData()->lastPosition.lbsInfo.lon);
                    }
                }
                else                            //当前有定位, 假装获取到LBS定位
                {
                    gps_getPosition()->isCLBS = L_TRUE;
                    gps_getPosition()->lbsInfo.lat = nmea_ndeg2degree(gps_getPosition()->nmeaInfo.lat);
                    gps_getPosition()->lbsInfo.lon = nmea_ndeg2degree(gps_getPosition()->nmeaInfo.lon);
                    gps_getPosition()->lbsTimestamp = gps_getPosition()->timestamp;
                    data_savePosition(gps_getPosition());
                }
            }
            if(data_isTime2Sleep()&&!timer_isTimerStart(TIMER_SLEEP_MOUDLE))
            {
                gps_getPosition()->isGPS = L_FALSE;//休眠后置为没有定位了
                sleep_sleepEnvironment();
            }
        }/* 电压上来了或电池在位 重置时间 */
        else if((voltage_mV > setting.settingConf.restoreVoltage)||(car_isPowerExistence()))
        {
            LOG_DEBUG("[Event] car vBatrrery up to normal");
            data_setAwakeTime(SLEEP_DEFAULT_TIME);
        }
    }
    else if (data_isSleeping())
    {
        //patch 如果不该处于休眠  但是却在休眠状态 唤醒之
        data_setAwakeTime(SLEEP_DEFAULT_TIME);
    }
}

static void event_AutoLookCheck(void)
{
    /*
        如果处于撤防状态 并且在近两分钟内没有震动(计时超过115秒) 执行一次自动落锁计时
                                                                                        */
    if(!setting_isDefendOn() && data_getVibrationTime() >= 115)
    {
        setting.statusConf.Cnt_autoLockTime += data_getVibrationTime();//累计时间 后续记录用两者之和
        data_resetVibrationTime();
        LOG_DEBUG(">> reset vib time");
        statusConf_save();
    }
    else if(data_getData()->isShaking) //如果在近两分钟震动了 重置时间
    {
        if(setting.statusConf.Cnt_autoLockTime != 0)
        {
            setting.statusConf.Cnt_autoLockTime = 0;
            LOG_DEBUG(">> reset auto time");
            statusConf_save();
        }
    }
}

static int event_activeFreqSOC_cb(void)
{
    if(setting.settingConf.isEtcSOC && setting.settingConf.activeFreqSOC //定时获取开关打开
       && !data_isInNight(19, 7) //处于早7点到晚7点的白天
       && setting_isDefendOn() && car_isPowerExistence()) //设防态下大电在位
    {
        car_lockAndGetSoc(); //定时开电门获取一线通SOC
    }
    return 0;
}

int event_checkActiveFreqSOC(void) //设防则重置主动获取的计时
{
    if(setting_isDefendOn() && setting.settingConf.isEtcSOC && setting.settingConf.activeFreqSOC)
    {
        timer_startRepeat(TIMER_ACTIVE_PREQ_SOC, TIMER_M, setting.settingConf.activeFreqSOC, event_activeFreqSOC_cb);
    }
    else
    {
        timer_stop(TIMER_ACTIVE_PREQ_SOC);
    }

    return 0;
}

static int event_sendBMSInfo(void)
{
    userMsg_setEvent(EVENT_SENDBMSINFO, 0);
    return 0;
}

static int event_sendBmsInfoOnce(void) //上报一次BMS。然后每周期上报一次
{
    event_sendBMSInfo();
    timer_start(TIMER_SEND_BMSINFO, TIMER_S, setting.statusConf.bmsSendPeriod, event_sendBmsInfoOnce);
}

static int event_LoopsendBMSInfo_cb(void)  //上报三次
{
    static u8 times = 0;

    if(times < 3)
    {
        event_sendBmsInfoOnce();
        timer_start(TIMER_SEND_BMSLOOP, TIMER_MS, 1000, event_LoopsendBMSInfo_cb);
        LOG_DEBUG("[Event] LoopSendBMS Times: %d", times);
        times++;
    }
    else
    {
        times = 0;
    }
    return 0;
}

static int reportSocAfterReboot(void) //保证设备重启连上网后上报三次SOC
{
    if(L_FALSE == data_isLogined() || data_getData()->isPowerChangeComplete == L_FALSE)
    {
        timer_start(TIMER_REPORT_SOC, TIMER_S, 2, reportSocAfterReboot);
    }
    else
    {
        event_LoopsendBMSInfo_cb(); //上报三次SOC
    }
}

static int event_bmsChangeCheck(void)
{
    static s8 bmsstate = -1;
    static s8 lastBmsState = -1;
    if((0 == memcmp("\x00\x00\x00\x00\x00\x00", data_getData()->bms.SN, 6) && setting.statusConf.bmsSoc == 0 && !setting.settingConf.isEtcSOC) ||
       (setting.settingConf.isEtcSOC && 0 == setting.statusConf.bmsSoc))  //没有获取到BMS信息,大电拔掉也会清空BMS
    {
        bmsstate = 0;
    }
    else
    {
        bmsstate = 1; //获取到BMS了
    }
    if(lastBmsState != bmsstate && bmsstate == 1) //如果BMS信息从无到有,立即上报三次
    {
        LOG_DEBUG("[Event] BMS first Get");
        reportSocAfterReboot();
    }
    lastBmsState = bmsstate;

    if(data_getData()->socFluct && data_getData()->isPowerChangeComplete) //如果SOC变化超过2，且大电更换完成
    {
        data_getData()->socFluct = L_FALSE;
        event_sendBmsInfoOnce();
        LOG_DEBUG("[Event] BMS fluct over 2 persent");
    }
    return 0;
}

static void event_BMSInfoCheck(void)
{
    event_bmsChangeCheck();
    if(car_isPowerExistence() && setting.statusConf.bmsSoc != 0)
    {
        //大电在位，获取到BMS但未开始上报，且认定大电更换完成，则上报三次，然后每周期上报一次
        if(!timer_isTimerStart(TIMER_SEND_BMSINFO) && data_getData()->isPowerChangeComplete)
        {
            event_LoopsendBMSInfo_cb();
        }
    }
    else
    {
        timer_stop(TIMER_SEND_BMSINFO); //没有大电,不上报BMS
    }
}

#define EVENT_OTAMAXTIME 600
static void event_OTATimeOutCheck(void)
{
    static u16 otaTimes = 0;
    if(setting.statusConf.bmsUpgradeFlag || setting.statusConf.etcUpgradeFlag) //如果BMS或ETC某一项在升级 1秒加一次
    {
        if(otaTimes++ > EVENT_OTAMAXTIME) //如果升级时间大于10分钟
        {
            if(setting.statusConf.bmsUpgradeFlag)
            {
                etcMsg_BMSOTA_Failed();
                LOG_ERROR("[event] BMS OTA TimeOut!");
            }
            if(setting.statusConf.etcUpgradeFlag)
            {
                etcMsg_ETCOTA_Failed();
                LOG_ERROR("[event] ETC OTA TimeOut!");
            }
            otaTimes = 0;
        }
    }

    if(!setting.statusConf.bmsUpgradeFlag && !setting.statusConf.etcUpgradeFlag)//如果都不在升级,清空计数
    {
        otaTimes = 0;
    }
}

static void event_MPUCheck(void)
{
    static u32 time = 0;
    static short xAccBak = 0, yAccBak = 0, zAccBak = 0;
    short x_dat, y_dat, z_dat;
    bool result = accelerometer_readOutputXYZ(&x_dat, &y_dat, &z_dat);

    if( !result || (x_dat == xAccBak && y_dat == yAccBak && z_dat == zAccBak))
    {
        LOG_DEBUG("accelerometer check error");
        if(++time == 60)
        {
            data_getData()->isAccelerateFault = 1;
            if(accelerometer_reset() != true)//进行软复位
            {
                LOG_DEBUG("accelerometer reset error");
                data_getData()->isAccelerateInitFault = 1;
            }
            else
            {
                LOG_DEBUG("accelerometer reset success");
                data_getData()->isAccelerateFault = 0;
                data_getData()->isAccelerateInitFault = 0;
                if(setting.settingConf.mpuAvoidanceRatio != 1)
                {
                    setting.settingConf.mpuAvoidanceRatio = 1;
                    settingConf_save();
                }
            }
        }
        if(time >= (5 * 60 * setting.settingConf.mpuAvoidanceRatio))
        {
            time = 0;
            setting_setRebootType(REBOOT_MPUERROR);
            timer_start(TIMER_REBOOT, TIMER_MS, 300, fibo_softReset);
        }
    }
    else
    {
        time = 0;
    }

    xAccBak = x_dat;
    yAccBak = y_dat;
    zAccBak = z_dat;
}

static L_BOOL event_isInRGBSetTime(void)
{
    if(setting.settingConf.ledConfig.isTrigger)
    {
        if(setting.settingConf.ledConfig.remainTime > 0)
        {
            setting.settingConf.ledConfig.remainTime--;
            return L_TRUE;
        }
        setting.settingConf.ledConfig.isTrigger = 0;
        settingConf_save();//只保存一次
    }

    if(setting.settingConf.ledConfig.isRepeat)
    {
        u32 timestamp = rtc_getTimestamp();
        u32 realTime = (timestamp + 28800) % 86400;//当天24小时
        LOG_DEBUG("realTime=%d ,endTime=%d,startTime=%d",realTime,setting.settingConf.ledConfig.endTime,setting.settingConf.ledConfig.startTime);
        if(timestamp < 1565588156)// 2019/8/12 13:35:56 尚未同步时间戳
        {
            return L_FALSE;
        }
        if(setting.settingConf.ledConfig.endTime > setting.settingConf.ledConfig.startTime)
        {
            if(realTime > setting.settingConf.ledConfig.startTime && realTime < setting.settingConf.ledConfig.endTime)
            {
                return L_TRUE;
            }
        }
        else//隔天
        {
            if((realTime > setting.settingConf.ledConfig.startTime && realTime > setting.settingConf.ledConfig.endTime) || \
               (realTime < setting.settingConf.ledConfig.startTime && realTime < setting.settingConf.ledConfig.endTime))
            {
                return L_TRUE;
            }
        }
    }

    return L_FALSE;
}

static int event_RGBLedBlink(void)//倒计时
{
    static u8 last_setLevel = 0;
    u8 tmp_ledtype = 0xff;
    u8 tmp_ledmode = 0xff;

    if(!data_getData()->ble_state.isDA14580Alive)
    {
        return L_FALSE;
    }
    if(setting.settingConf.ledConfig.isTrigger)
    {
        tmp_ledtype = setting.settingConf.ledConfig.triggerLedType;
        tmp_ledmode = setting.settingConf.ledConfig.triggerMode;
    }
    else if((setting.settingConf.ledConfig.isRepeat))
    {
        tmp_ledtype = setting.settingConf.ledConfig.repeatLedType;
        tmp_ledmode = setting.settingConf.ledConfig.repeatMode;
    }
    else
    {
        return L_FALSE;
    }

    if(last_setLevel == 0)
    {
        last_setLevel = 1;
        if(tmp_ledmode == CAR_BLINKFAST)
        {
            timer_start(TIMER_BIKELED_BLINK, TIMER_MS, 300, event_RGBLedBlink);
        }
        else if(tmp_ledmode == CAR_BLINKSLOW)
        {
            timer_start(TIMER_BIKELED_BLINK, TIMER_MS, 500, event_RGBLedBlink);
        }
        car_setRGBLed(tmp_ledtype, 1);//open 500ms
    }
    else
    {
        last_setLevel = 0;
        if(tmp_ledmode == CAR_BLINKFAST)
        {
            timer_start(TIMER_BIKELED_BLINK, TIMER_MS, 300, event_RGBLedBlink);
        }
        else if(tmp_ledmode == CAR_BLINKSLOW)
        {
            timer_start(TIMER_BIKELED_BLINK, TIMER_MS, 1000, event_RGBLedBlink);
        }
        car_setRGBLed(tmp_ledtype, 0);//close
    }

    return L_TRUE;
}

static int event_Check_RGBLed(void)
{
    static L_BOOL init_led = L_TRUE;
    static L_BOOL last_isLightOn = L_FALSE;
    static L_BOOL last_isPowerExist = L_FALSE;
    L_BOOL now_isPowerExist = car_isPowerExistence();

    if(car_isAccOn()) //电门打开时，关掉呼吸灯
    {
        timer_stop(TIMER_BIKELED_BLINK);
        car_setRGBLed(CAR_REDLED, 0);//灭
        car_setRGBLed(CAR_GREENLED, 0);//灭
        car_setRGBLed(CAR_BLUELED, 0);//灭
        return 0;
    }

    if(init_led && data_getData()->ble_state.isDA14580Alive)//上电初始化灭灯
    {
        init_led = L_FALSE;
        car_setRGBLed(CAR_REDLED, 0);//灭 目前只有红色灯引脚硬件支持
        car_setRGBLed(CAR_GREENLED, 0);//灭
        car_setRGBLed(CAR_BLUELED, 0);//灭
    }

    if(!now_isPowerExist && last_isPowerExist)//大电没了把灯关掉
    {
        timer_stop(TIMER_BIKELED_BLINK);
        car_setRGBLed(CAR_REDLED, 0);//灭
        car_setRGBLed(CAR_GREENLED, 0);//灭
        car_setRGBLed(CAR_BLUELED, 0);//灭
    }
    if(now_isPowerExist != last_isPowerExist)
    {
        last_isPowerExist = now_isPowerExist;
    }
    if(!now_isPowerExist)
    {
        return 0;
    }

    if(setting.settingConf.ledConfig.isTrigger)
    {
        if(event_isInRGBSetTime())
        {
            if(setting.settingConf.ledConfig.triggerMode == CAR_LIGHTON)
            {
                car_setRGBLed(setting.settingConf.ledConfig.triggerLedType, 1);//常亮
            }
            else
            {
                if(!timer_isTimerStart(TIMER_BIKELED_BLINK))
                {
                    event_RGBLedBlink();
                }
            }
        }
        else
        {
            car_setRGBLed(setting.settingConf.ledConfig.repeatLedType, 0);//常灭
        }
    }
    else if(setting.settingConf.ledConfig.isRepeat)
    {
        if(event_isInRGBSetTime() && setting.settingConf.ledConfig.isOn)
        {
            if(setting.settingConf.ledConfig.repeatMode == CAR_LIGHTON)//常亮
            {
                last_isLightOn = L_TRUE;
                car_setRGBLed(setting.settingConf.ledConfig.repeatLedType, 1);//常亮
            }
            else
            {
                if(!timer_isTimerStart(TIMER_BIKELED_BLINK))
                {
                    event_RGBLedBlink();
                }
            }
        }
        else
        {
            if(timer_isTimerStart(TIMER_BIKELED_BLINK))
            {
                timer_stop(TIMER_BIKELED_BLINK);
                last_isLightOn = L_FALSE;
                car_setRGBLed(setting.settingConf.ledConfig.repeatLedType, 0);//灭
            }
            else
            {
                if(last_isLightOn)
                {
                    last_isLightOn = L_FALSE;
                    car_setRGBLed(setting.settingConf.ledConfig.repeatLedType, 0);//灭
                }
            }
        }
    }

    return L_TRUE;
}

static int event_loop_1s(void)
{
    event_OverSpeedCheck();    //超速报警逻辑
    event_SleepEnvCheck();     //休眠环境条件
    event_AutoLookCheck();     //自动落锁检测
    //event_AcceleromterCheck(); //加速度计检测
    event_BMSInfoCheck();      //BMS信息上报
    event_OTATimeOutCheck();   //OTA超时退出检测
    //目前只有MX5D2 MX5D4支持led闪灯
    if((setting_getVerisonType() == VERSION_TYPE_MX5D2) || (setting_getVerisonType() == VERSION_TYPE_MX5D4))
    {
        event_Check_RGBLed();//RGB三色灯
    }

    if(setting.settingConf.accleType == ACCLE_MPU6500)
    {
        event_MPUCheck();      //mpu6500检测
    }

    return 0;
}

int event_long_loop(void)
{
    if(socket_isLogined())
    {
        if(!data_isSleeping()) //在线且不在休眠,只发送服务器心跳 2min
        {
            cmd_Heartbeat();
        }
        else
        {
            if(fibo_GetDeviceSleepState() != false)
            {
                fibo_setSleepMode(1);
            }
            cmd_Heartbeat();
            da14580_sendDATA(BIO_ADDRESS, CMD_BIO_PING, NULL, 0);
            adc_getVoltageSync(&data_getData()->vehicleBattery_mV,ADC_PWR_DETECT);
            if(data_getData()->vehicleBattery_mV > setting.settingConf.restoreVoltage)
            {
                data_setAwakeTime(SLEEP_DEFAULT_TIME);
            }
        }
    }
    else if(data_isSleeping()) //如果离线但是在休眠直接唤醒
    {
        data_setAwakeTime(SLEEP_DEFAULT_TIME);
    }
    return 0;
}

void event_initial(void)
{
    timer_startRepeat(TIMER_EVENT_SLOOP, TIMER_S, 1, event_loop_1s);
    timer_startRepeat(TIMER_EVENT_LLOOP, TIMER_M, 2, event_long_loop);

    event_checkActiveFreqSOC(); //初始化检查并启动主动获取SOC流程
}

