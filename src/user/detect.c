/*
 * detect.h
 *
 *  Created on: 2020/4/9
 *      Author: lc
 */
#include "fibo_opencpu.h"
#include <math.h>
#include <stdlib.h>

#include "log.h"
#include "data.h"
#include "car.h"
#include "lis3dh.h"
#include "types.h"
#include "detect.h"
#include "setting.h"
#include "userMsg.h"
#include "hardware.h"
#include "protocol.h"
#include "da14580.h"
#include "audio_driver.h"
#include "user_gpio.h"
#include "user_timer.h"
#include "request.h"
#include "utils.h"
#include "etcMsg.h"
#include "socket.h"
#include "accelerometer.h"
#include "flash.h"
#include "RFID.h"
#include "ETC_TaiBiTe.h"

#define MOVE_TIMER_PERIOD   20
#define DETECT_VIBRATION_SENSETIVE 1  //过滤mpu抖动用 0为最灵敏
#define MAX_ANGLE_DATA_LEN  30        //角度检测采集次数

static int detect_move_handler(void);

void detect_int_handler(void)//此中断较为频繁,不建议加IIC读取或者串口打印等其他耗时操作
{
    static u8 shakeCnt = 0;
    shakeCnt++;
    if(shakeCnt > DETECT_VIBRATION_SENSETIVE)
    {
        shakeCnt = 0;
        data_getData()->shaketimes = 3;//震动处理里每秒减一,保障持续振动能一直持续
        data_getData()->isShaking = L_TRUE;
        data_setAwakeTime(SLEEP_SHARK_WAKE);
    }
    return;
}

static int detect_getRFIDVerEnable(void) //主动读取RFID版本号使能
{
    data_getData()->isReadRFIDVersion = L_TRUE;
    return 0;
}

static void detect_switchChange_handler(void) //1s
{
    static int8_t last_isAccOn = -1;
    static u8 wheelSpinTime = 0;
    static u8 accOnTime = 0;
    int8_t new_isAccOn = car_isAccOn();
    
    if(last_isAccOn != -1 && last_isAccOn != new_isAccOn)
    {
        if(new_isAccOn) //电门线从低到高
        {        
            if(setting.settingConf.isRFIDEnable) //刚开电门时，获取一次版本号
            {
                detect_getRFIDVerEnable();
            }
            if(setting_isAccOn())
            {
                etcMsg_setETCAccOn(); //开电门下电门线抖动则重新发开电门命令
            }
            userMsg_setEvent(EVENT_ALARM, ALARM_SWITCH_OPEN);
            accOnTime = 1; //从1s开始计时
        }
        else //电门线从高到低
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_SWITCH_CLOSE);
            accOnTime = 0; //清空
        }

        //电门线状态变化，则重新累积轮动连续和霍尔可用
        data_getData()->isWheelSpinConti = L_FALSE;
        data_getData()->isPulseUsable = L_FALSE;
        wheelSpinTime = 0;
    }
    
    if(accOnTime || (last_isAccOn == L_TRUE && new_isAccOn == L_TRUE))
    {
        //开电门过两秒后，控制器返回的pulse值大于0，才标注此时pulse可用于校准轮动
        if(accOnTime >= 3 && data_getData()->etc.pulse > 0)
        {
            data_getData()->isPulseUsable = L_TRUE;
        }

        //开电门并且轮动持续超过2秒，则置位状态量
        if(data_getData()->isWheelSpinning)
        {
            wheelSpinTime++;
            if(wheelSpinTime >= 2)
            {
                data_getData()->isWheelSpinConti = L_TRUE;
            }
            if(wheelSpinTime == 0) //防止翻转
            {
                wheelSpinTime = 2;
            }
        }

        accOnTime++;
        if(accOnTime == 0) //防止翻转
        {
            accOnTime = 3;
        }
    }

    if(setting.settingConf.isRFIDEnable)
    {
        //RFID版本号为空时，主动发一次获取RFID版本号
        if(strlen(data_getData()->RFIDVersion) < 5)
        {
            detect_getRFIDVerEnable();
        }
    }
    
    last_isAccOn = new_isAccOn;
}

static void detect_SaddleChange_handler(void)
{
    static int8_t last_isSaddleLocked = -1;

    int8_t isSaddleLocked = car_isSaddleLocked();
    if(last_isSaddleLocked != -1 && last_isSaddleLocked != isSaddleLocked)
    {
        if(isSaddleLocked)
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_BACKSEAT_SHUT);
        }
        else
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_BACKSEAT_OPEN);
        }
    }
    last_isSaddleLocked = isSaddleLocked;
}

static int detetc_getStaticADC(void)
{
    static u8 count = 0;
    if(data_getData()->isWheelSpinning == L_TRUE) //如果持续1S的检测中轮子又转了,返回
    {
        count = 0;
        LOG_DEBUG("[detect] WheelSpinning, reset get static Bike Battery");
        return 0;
    }
    if(++count == 10)
    {
        count = 0;
        data_getData()->staticBikeBat_mV = data_getData()->vehicleBattery_mV; //更新车子静止时的电压值
        LOG_DEBUG("[detect] get static Bike Battery = %d", data_getData()->staticBikeBat_mV);
    }
    return 0;
}

static int detect_speed_handler(void)
{
#define MAX_COUNT 40
    static uint32_t low_level_count = 0;
    static uint32_t high_level_count = MAX_COUNT;
    static uint8_t last_isWheelSpinning = L_FALSE;
    u8 new_isWheelSpinning = L_FALSE;
    uint8_t pin_level = 0;

    fibo_gpio_get(PIN_SPEED_DETECT, &pin_level); //读速度端口的电平

    if(timer_isTimerStart(TIMER_RELEASE_ELOCK) || timer_isTimerStart(TIMER_BLINK_LIGHT)) return 0;
    if(pin_level == GPIO_LEVEL_LOW) //如果为低电平
    {
        low_level_count++;
        high_level_count = 0;
    }
    else //如果为高电平，高电平计数器加一，低电平复位
    {
        high_level_count++;
        low_level_count = 0;
    }

    data_getData()->speedCountTime++;
    if((abs(low_level_count-high_level_count)) < (int)(MAX_COUNT * 2 / 3) && data_getData()->speedCountTime >= MAX_COUNT)
    {
        if(data_getData()->etc.pulse == 0 && data_getData()->isPulseUsable) //若中控与控制器通信正常，且霍尔数为0，则无轮动
        {
            data_getData()->isWheelSpinning = L_FALSE;
        }
        else
        {
            data_getData()->isWheelSpinning = L_TRUE;
            new_isWheelSpinning = L_TRUE;
        }
    }
    else if((abs(low_level_count-high_level_count)) >= (int)(MAX_COUNT * 2 / 3) && data_getData()->speedCountTime >= MAX_COUNT)
    {
        data_getData()->isWheelSpinning = L_FALSE;
    }

    if(data_getData()->isWheelSpinning && new_isWheelSpinning)
    {
        if(setting.statusConf.Cnt_autoLockTime != 0)
        {
            setting.statusConf.Cnt_autoLockTime = 0;
            statusConf_save();
        }
        data_resetVibrationTime(); //轮动也重置自动落锁时间
        if(setting_isDefendOn())
        {
            if(L_TRUE == setting.defaultConf.isMoveAlarmOn && L_FALSE == data_isInNight(20, 7)) //移动告警语音打开且,不在夜间
            {
                audio_play(AUDIO_ALARM);
                LOG_DEBUG("[detect] wheelspin alarm");
            }
            car_lock();
        }
    }
    else if(data_getData()->isWheelSpinning == L_FALSE && last_isWheelSpinning == L_TRUE)
    {
        //由轮动变为静止，则主动上报一次状态
        userMsg_setEvent(EVENT_SENDSTATUS, 0);
    }

    if(car_isAccOn()) //isMoving条件
    {
        if(data_getData()->isWheelSpinning)
        {
            data_setMovedState(L_TRUE); //1.开电门加轮动信号 2.设防情况下的非法移动
        }
        else
        {
            data_setMovedState(L_FALSE);
        }
    }

    last_isWheelSpinning = data_getData()->isWheelSpinning;
    return 0;
}

static int detect_angle_cb(float x_dat, float y_dat, float z_dat, float *x_agl, float *y_agl, float *z_agl)
{
#define rad2agl (57.295799)
    float g = 0.0;
    g = sqrt(pow(x_dat, 2) + pow(y_dat, 2) + pow(z_dat, 2));
    *x_agl = acos(x_dat/g) * rad2agl;
    *y_agl = acos(y_dat/g) * rad2agl;
    *z_agl = acos(z_dat/g) * rad2agl;
    LOG_DEBUG("[detect] agl: X(%f) Y(%f) Z(%f)", *x_agl, *y_agl, *z_agl);
    return 0;
}

static int detect_angle_audio_cb(void)
{
    u8 angle = (data_getData()->angle & 0x07);
    u16 angle_begin = 90 - setting.settingConf.diffAngle;
    u16 angle_end = 90 + setting.settingConf.diffAngle;
    // 车辆未动 并且翻倒 继续播语音
    if(setting.settingConf.periodDiffAngleAudio)
    {
        if(setting_isDefendOn() && ((angle < angle_begin - 5) || (angle > angle_end + 5)))
        {
            audio_play(AUDIO_TURNOVER);
            timer_start(TIMER_TURNOVER_AUDIO, TIMER_S, setting.settingConf.periodDiffAngleAudio, detect_angle_audio_cb);
        }
    }
    return 0;
}

static int detect_angle_handle(void)
{
    static u8 last_isTurnOver = L_FALSE;
    static u16 data_cnt = 0;
    static float sum[3]= {0.0,0.0,0.0}; // x y z

    bool isTurnOver;

    short x_dat, y_dat, z_dat;
    float x_aver, y_aver, z_aver;
    float x_agl, y_agl, z_agl;
    float hor_angle = 0.0;
    static u8 turnoverTime = 0;
    DATA *pData = data_getData();

    u16 angle_begin = (90 - setting.settingConf.diffAngle) > 0? (90 - setting.settingConf.diffAngle) : 70;
    u16 angle_end = (90 + setting.settingConf.diffAngle) > 180? 110 : (90 + setting.settingConf.diffAngle);

    //电池不在位或撤防
    if(!car_isPowerExistence() || !setting_isDefendOn())
    {
        if(timer_isTimerStart(TIMER_TURNOVER_AUDIO))
        {
            timer_stop(TIMER_TURNOVER_AUDIO);
        }
        data_getData()->angle = 90 + 10000; // 万位为 1 用作对齐
        data_getData()->acceleromterData.isRead = L_FALSE;//标记倾倒检测已经没有在读加速度数据了
        return -1;
    }

    if(pData->acceleromterData.isRead)//如果移动检测已经读取到数据,那么直接从全局变量里拿数据
    {
        x_dat = pData->acceleromterData.x_data;
        y_dat = pData->acceleromterData.y_data;
        z_dat = pData->acceleromterData.z_data;
    }
    else//如果移动检测没有在读,需要自己读取
    {
        bool result = accelerometer_readOutputXYZ(&x_dat, &y_dat, &z_dat);
        if(!result)
        {
            LOG_ERROR("[Detect] accelerometer read error");
            return -1;
        }
    }
    //LOG_DEBUG("X: %d, Y: %d, Z: %d", x_dat, y_dat, z_dat);
    sum[0] += x_dat;
    sum[1] += y_dat;
    sum[2] += z_dat;
    data_cnt ++;

    // 30个数据取平均 时间间隔为30ms
    if(data_cnt < MAX_ANGLE_DATA_LEN)
    {
        if(!timer_isTimerStart(TIMER_ANGLE_CHECK))
        {
            timer_startRepeat(TIMER_ANGLE_CHECK, TIMER_MS, 30, detect_angle_handle);
        }
        return 0;
    }
    timer_stop(TIMER_ANGLE_CHECK);
    x_aver = sum[0] / data_cnt;
    y_aver = sum[1] / data_cnt;
    z_aver = sum[2] / data_cnt;


    data_cnt = 0;
    sum[0] = 0.0;
    sum[1] = 0.0;
    sum[2] = 0.0;
    detect_angle_cb(x_aver, y_aver, z_aver, &x_agl, &y_agl, &z_agl);

    if(y_agl <= 90)
    {
        hor_angle = 270 - z_agl;
    }
    else
    {
        hor_angle = z_agl - 90;
    }

    // 精度 和 默认万位为 1 对齐
    hor_angle += (hor_angle < 0) ? 360 : 0;
    pData->angle = hor_angle + 12000;

    if(!last_isTurnOver)
    {
        // 当角度落到 65 115 之外时，记为翻倒
        isTurnOver = ((hor_angle < angle_begin-5) || (hor_angle > angle_end+5))?L_TRUE : L_FALSE;
    }
    else
    {
        // 当回到 70 110 之间时，记为未翻倒
        isTurnOver = ((hor_angle >= angle_begin) && (hor_angle <= angle_end))? L_FALSE : L_TRUE;
    }
    if(isTurnOver != last_isTurnOver)
    {
        if(isTurnOver)//倾倒
        {
            turnoverTime = 0;
            data_getData()->isTurnoverChange = 1;
            if(setting.defaultConf.isTurnOverEnable)
            {
                userMsg_setEvent(EVENT_ALARM, ALARM_OVERTURN);
                audio_play(AUDIO_TURNOVER);
                timer_start(TIMER_TURNOVER_AUDIO, TIMER_S, setting.settingConf.periodDiffAngleAudio, detect_angle_audio_cb);
            }
            LOG_DEBUG("[Detect]  Car Turn over");
        }
        else//恢复
        {
            turnoverTime = 0;
            data_getData()->isTurnoverChange = 1;
            if(setting.defaultConf.isTurnOverEnable)
            {
                userMsg_setEvent(EVENT_ALARM, ALARM_OVERTURN_RESTORE);
                timer_stop(TIMER_TURNOVER_AUDIO);
            }
            LOG_DEBUG("[Detect] Car Turn recovery");
        }
    }

    if(data_getData()->isTurnoverChange)
    {
        if(turnoverTime++ > 10)//10s倾倒后允许移动告警
        {
            turnoverTime = 0;
            data_getData()->isTurnoverChange = 0;
        }
    }
    last_isTurnOver = isTurnOver;
    return 0;
}

static void detect_moveAlarm(void)
{
    car_lock();
    if(setting.defaultConf.isMoveAlarmOn  && !data_isInNight(20, 7))
    {
        audio_play(AUDIO_ALARM);
        LOG_INFO("[Detect] Move Alarm");
    }
    userMsg_setEvent(EVENT_ALARM, ALARM_VIBRATE);
    return;
}
static void DigitalIntegrate(float *sour, float *dest, int len, float cycle)
{
    int i = 0;
    if(len == 0)return;
    dest[0] = 0;
    for (i = 1; i < len; i++)
    {
        dest[i] = dest[i - 1] + (sour[i - 1] + sour[i]) * cycle / 2;
    }

}

static void lis3dh_CalcXYZAngle(short x,short y,short z)
{
    DATA *pData = data_getData();

    pData->acceleromterData.pitch = (short)(atan2((float)(0-y),z) * 180 / PI);     //转换为度数 俯仰角
    pData->acceleromterData.roll = (short)(atan2((float)(x),z) * 180 / PI);        //转换为度数 横滚角
    pData->acceleromterData.yaw = 0; //lis3dh无法获取角速度，所以无法计算偏航角,默认为0
    return;
}

static int defendMoveTimeout(void)//设防移动每次维持60s的5s上报gps状态
{
    data_setMovedState(L_FALSE);//设防不在移动状态GPS上报会在重复定时里恢复为10分钟
    return 0;
}

#define MAX_MOVE_DATA_LEN    50 //最大不要超过50 25ms读一次，即1s
#define MOVE_CHECK_TIME      (MAX_MOVE_DATA_LEN*MOVE_TIMER_PERIOD)
#define MOVE_SEC_TIME        (1000/MOVE_CHECK_TIME)
#define MOVE_JUDGE_TIMES     (5*MOVE_SEC_TIME)
#define MOE_DEFEND_TIMEOUT   (10*MOVE_SEC_TIME)//设防变化10s以上开始检测移动
#define MOVE_SHAKE_TIMEOUT   (30*MOVE_SEC_TIME) //持续震动也要校准，避免特殊场合一直有震动

static int detect_move_handler(void)
{
    static u16 count = 0;
    static u32 times = 0;
    static u8 lastDefendStatus = 2;//用于判断是否是刚设防状态
    static int totalX = 0, totalY = 0, totalZ = 0;
    static short g_x_dat = 0, g_y_dat = 0, g_z_dat = 0;
    static u32 accelerometerFaultTime = 0, defendTime = 0;
    static short originX[MAX_MOVE_DATA_LEN] = {0}, originY[MAX_MOVE_DATA_LEN] = {0}, originZ[MAX_MOVE_DATA_LEN] = {0};//存储加速度计原始数据
    static float actualX = 0, actualY = 0, actualZ = 0; //存储设备实际加速度值，单位mm/s2
    static L_BOOL Xdir = L_FALSE, Ydir = L_FALSE, Zdir = L_FALSE;//L_TRUE为正加速度
    static u8 XchangeCnt = 0, YchangeCnt = 0, ZchangeCnt = 0;//持续变化统计
    static u8 isDetectedMoved = 0;
    static u8 shaketime = 0;//持续震动
    static u8 staticTime = 0;
    static u8 wheelSpinningTime = 0;
    static L_BOOL isWheelMove = L_FALSE;
    static float staticX = 0, staticY = 0, staticZ = 0;//加速度静止校准基准数据
    int i = 0;
    u16 index = 0;
    DATA *pData = data_getData();
    float x_acc = 0, y_acc = 0, z_acc = 0;
    short x_dat = 0, y_dat = 0, z_dat = 0;

    L_BOOL result = accelerometer_readOutputXYZ(&x_dat, &y_dat, &z_dat);
    if(!result)
    {
        pData->acceleromterData.isRead = L_FALSE;//标记读取数据不正常
        return -1;
    }

    if(times++ % (100 / MOVE_TIMER_PERIOD) == 0)// 100ms更新一次角度
    {
        //根据读到的XYZ三轴加速度计算俯仰角和横滚角
        lis3dh_CalcXYZAngle(x_dat, y_dat, z_dat);
    }

    pData->acceleromterData.isRead = L_TRUE;//标记读取数据正常
    pData->acceleromterData.x_data = x_dat;
    pData->acceleromterData.y_data = y_dat;
    pData->acceleromterData.z_data = z_dat;//实时更新全局变量里的加速度计的数据

    index = count++ % MAX_MOVE_DATA_LEN;//0 ~ MAX_MOVE_DATA_LEN-1
    //1s平均加速度
    if(count > MAX_MOVE_DATA_LEN)//限制count大小，防止溢出
    {
        for(i = 0; i < MAX_MOVE_DATA_LEN; i++)
        {
            totalX +=  originX[i];
            totalY +=  originY[i];
            totalZ +=  originZ[i];
        }
        count = 0;
    }
    else
    {
        originX[index] = x_dat;
        originY[index] = y_dat;
        originZ[index] = z_dat;
        return -1;
    }

    x_acc = (float)totalX / MAX_MOVE_DATA_LEN;
    y_acc = (float)totalY / MAX_MOVE_DATA_LEN;
    z_acc = (float)totalZ / MAX_MOVE_DATA_LEN;

    totalX = 0;
    totalY = 0;
    totalZ = 0;

    //零点校准处理,如果车子静止超过3s且加速度数值没有较大的变化, 表明车子进入稳定状态
    if(!data_getData()->isShaking)//3s以上的连续震动才有告警，小于3s的震动不会进入
    {
        if(staticTime++ >= 3)
        {
            shaketime = 0;
            XchangeCnt = 0;
            YchangeCnt = 0;
            ZchangeCnt = 0;
            staticX = x_acc;
            staticY = y_acc;
            staticZ = z_acc;
            staticTime = 0;
        }
    }
    else
    {
        if(shaketime++ > MOVE_SHAKE_TIMEOUT)//一直震动超时60s也要校准
        {
            shaketime = 0;
            XchangeCnt = 0;
            YchangeCnt = 0;
            ZchangeCnt = 0;
            staticX = x_acc;
            staticY = y_acc;
            staticZ = z_acc;
        }
    }

    if(staticX == 0 && staticY == 0 && staticZ == 0)//如果没有校准，则返回不进行积分运算
    {
        return -1;
    }

    if(g_x_dat == x_dat && g_y_dat == y_dat && g_z_dat == z_dat)
    {
        // 如果持续60次读取加速度计数据没有一丁点变化 那么认为加速度计失效
        if(++accelerometerFaultTime >= 60)
        {
            data_setAccelerometerFault(L_TRUE);
        }
    }
    else
    {
        accelerometerFaultTime = 0;
    }

    g_x_dat = x_dat;
    g_y_dat = y_dat;
    g_z_dat = z_dat;

    if(isDetectedMoved)
    {
        static u32 time = 0;
        if(time++ > 8*MOVE_SEC_TIME)//检测到移动后8s不再进行移动检测
        {
            isDetectedMoved = 0;
            time = 0;
        }
    }

    //加速度实际值减去静态值得到实际加速度
    actualX = x_acc - staticX;
    actualY = y_acc - staticY;
    actualZ = z_acc - staticZ;

    //刚设防, 10s内不进行移动检测，防止姿态不稳定导致误报移动报警
    if(setting_isDefendOn() && lastDefendStatus == 0)
    {
        if(defendTime++ < MOE_DEFEND_TIMEOUT)
        {
            return -1;
        }

        defendTime = 0;
    }
    lastDefendStatus = setting_isDefendOn();

    if(!setting_isDefendOn() || isDetectedMoved || setting.settingConf.move_threshold == 0 || data_getData()->isTurnoverChange)//等于0默认不检测移动告警
    {
        return -1;
    }

    if(data_getData()->isWheelSpinning)//如果有轮动考虑为强推车告警
    {
        if(++wheelSpinningTime >= MOVE_JUDGE_TIMES)//轮动5s上报告警
        {
            wheelSpinningTime = 0;
            isWheelMove = L_TRUE;
        }
    }
    // LOG_INFO("actualX = %d",(int)(actualX));
    // LOG_INFO("actualY = %d",(int)(actualY));
    // LOG_INFO("actualZ = %d",(int)(actualZ));
    if(abs(actualX) > setting.settingConf.move_threshold)
    {
        if(actualX > 0)
        {
            if(Xdir ==L_FALSE)
            {
                XchangeCnt = 0;
            }
            Xdir = L_TRUE;//加速
        }
        else
        {
            if(Xdir == L_TRUE)
            {
                XchangeCnt = 0;
            }
            Xdir = L_FALSE;//减速
        }
        if(++XchangeCnt >= MOVE_JUDGE_TIMES || isWheelMove)
        {
            detect_moveAlarm();
            data_setMovedState(L_TRUE);
            timer_start(TIMER_DEFENDMOVE_TIMEOUT, TIMER_S, 60, defendMoveTimeout);//上报状态形成轨迹 上报状态会改为5s一次
            LOG_INFO("move alarm X");
            wheelSpinningTime = 0;
            isWheelMove = L_FALSE;
            XchangeCnt = 0;
            YchangeCnt = 0;
            ZchangeCnt = 0;
            isDetectedMoved = 1;//检测到移动后8s不再进行移动检测
            return 0;
        }
    }
    else
    {
        XchangeCnt = 0;
    }

    if(abs(actualY) > setting.settingConf.move_threshold)
    {
        if(actualY > 0)
        {
            if(Ydir == L_FALSE)
            {
                YchangeCnt = 0;
            }
            Ydir = L_TRUE;//正加速度
        }
        else
        {
            if(Ydir == L_TRUE)
            {
                YchangeCnt = 0;
            }
            Ydir = L_FALSE;//负加速度
        }

        if(++YchangeCnt >= MOVE_JUDGE_TIMES || isWheelMove)
        {
            detect_moveAlarm();
            data_setMovedState(L_TRUE);
            timer_start(TIMER_DEFENDMOVE_TIMEOUT, TIMER_S, 60, defendMoveTimeout);
            LOG_INFO("move alarm Y");
            wheelSpinningTime = 0;
            isWheelMove = L_FALSE;
            XchangeCnt = 0;
            YchangeCnt = 0;
            ZchangeCnt = 0;
            isDetectedMoved = 1;//检测到移动后8s不再进行移动检测
            return 0;
        }
    }
    else
    {
        YchangeCnt = 0;
    }

    if(abs(actualZ) > setting.settingConf.move_threshold)
    {
        if(actualZ > 0)
        {
            if(Zdir ==L_FALSE)
            {
                ZchangeCnt = 0;
            }
            Zdir = L_TRUE;//正加速度
        }
        else
        {
            if(Zdir == L_TRUE)
            {
                ZchangeCnt = 0;
            }
            Zdir = L_FALSE;//负加速度
        }
        if(++ZchangeCnt >= MOVE_JUDGE_TIMES || isWheelMove)
        {
            detect_moveAlarm();
            data_setMovedState(L_TRUE);
            timer_start(TIMER_DEFENDMOVE_TIMEOUT, TIMER_S, 60, defendMoveTimeout);
            LOG_INFO("move alarm Z");
            wheelSpinningTime = 0;
            isWheelMove = L_FALSE;
            XchangeCnt = 0;
            YchangeCnt = 0;
            ZchangeCnt = 0;
            isDetectedMoved = 1;//检测到移动后8s不再进行移动检测
            return 0;
        }
    }
    else
    {
        ZchangeCnt = 0;
    }
    return 0;
}

u8 g_buckctrl = 0;
int detect_5v_ctrl_cb(void)
{
    if(data_getData()->ble_state.isDA14580Alive)
    {
        if(g_buckctrl == 0)
        {
            da14580_setBlePinLevel(BLE_PORT2, BLE_PIN2, PIN_LEVEL_LOW);
            data_getData()->buckstate = 0;
        }
        else
        {
            da14580_setBlePinLevel(BLE_PORT2, BLE_PIN2, PIN_LEVEL_HIGH);
            data_getData()->buckstate = 1;
        }
        timer_stop(TIMER_5V_CTRL);
    }
    else
    {
        timer_startRepeat(TIMER_5V_CTRL, TIMER_MS, 100, detect_5v_ctrl_cb);
    }
    return 0;
}

static void detect_statusChange_handler(void)
{
    static s8 last_acc = -1;
    static s8 last_defend = -1;
    L_BOOL isSendStatus = L_FALSE;

    if(setting.statusConf.acc != last_acc)
    {
        last_acc = setting.statusConf.acc;
        isSendStatus = L_TRUE;
    }
    if(setting.statusConf.isDefend != last_defend)
    {
        last_defend = setting.statusConf.isDefend;
        isSendStatus = L_TRUE;
    }
    if(isSendStatus)
    {
        userMsg_setEvent(EVENT_SENDSTATUS, 0);
    }
}

static int detect_send_status_cb(void)
{
    if(data_isLogined())
    {
        cmd_status();
    }
    return timer_startRepeat(TIMER_SEND_GPS, TIMER_MS, data_getData()->gpsSendPeriod_ms, cmd_status);
}

static int detect_PowerChangeComplete_cb(void)
{
    data_getData()->isPowerChangeComplete = L_TRUE;
    return 0;
}

static void detect_PowerChange_handler(void)
{
    static s8 last_isPowerExist = -1;

    s8 isPowerExist = car_isPowerExistence();
    if(isPowerExist != last_isPowerExist)
    {
        if(isPowerExist)
        {
            timer_stop(TIMER_5V_CTRL);
            fibo_gpio_set(PIN_CHARGE_DRIVER, GPIO_LEVEL_HIGH); //打开充电
            g_buckctrl = 0;
            timer_start(TIMER_5V_CTRL, TIMER_MS, 50, detect_5v_ctrl_cb);

            data_getData()->isPowerChangeComplete = L_FALSE;
            timer_start(TIMER_WAIT_POWER_CHANGED, TIMER_S, 5, detect_PowerChangeComplete_cb); //5秒后认为换电完成并更新soc

            if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能产品
            {
                if(car_isAccOn() && !setting_isDefendOn())
                {
                    timer_start(TIMER_RFID_POWERON, TIMER_MS, 800, car_open_RFIDPower); //开机第一次或者刚完成换电，若电门已经打开，则执行一次打开RFID的5V供电操作
                }
            }

            if(data_getData()->workMode == NORMAL_MODE) //大电从无到有，检查头盔锁
            {
                if(!car_isSaddleLocked())
                {
                    car_checkSaddle();
                }
                
                if(setting.settingConf.isEtcSOC) //恢复大电开电门获取一次SOC
                {
                    car_lockAndGetSoc();
                }
            }

            if(setting.defaultConf.ccuType == TYPE_TAIBITE_SOC)
            {
                ETC_TaiBiTe_resetSocWindow();
            }

            userMsg_setEvent(EVENT_ALARM, ALARM_POWER_RESTORE);
            LOG_DEBUG("[Detect] ******** Close BUCK! ********");
        }
        else
        {
            fibo_gpio_set(PIN_CHARGE_DRIVER, GPIO_LEVEL_LOW); //关闭充电
            g_buckctrl = 1;
            timer_start(TIMER_5V_CTRL, TIMER_MS, 5000, detect_5v_ctrl_cb); //大电源没了5秒后将5V升压控制打开

            data_getData()->isPowerChangeComplete = L_FALSE;
            timer_stop(TIMER_WAIT_POWER_CHANGED);

            if(last_isPowerExist != -1)
            {
                memset((u8 *)&data_getData()->bms, 0, sizeof(BMS));  //如果大电拔掉了，清空BMS信息 = 不发送
                setting.statusConf.bmsSoc = 0;
                data_setAwakeTime(SLEEP_DEFAULT_TIME);

                if(setting.defaultConf.ccuType == TYPE_TAIBITE_SOC)
                {
                    ETC_TaiBiTe_resetSocWindow();
                }

                userMsg_setEvent(EVENT_ALARM, ALARM_POWER_CUT);
                // 统计数据 换电次数
                setting.statusConf.pwrCutCount++;
                statusConf_save();
            }
            LOG_DEBUG("[Detect] ******** Open BUCK!********");
        }
        LOG_INFO("power change send");
        timer_start(TIMER_SEND_GPS, TIMER_MS, 5000, detect_send_status_cb); //5秒后上报一次状态以供服务端同步电量信息

        if(last_isPowerExist == -1) //设备重启的时候,不论电池是否在位，都执行一次。
        {
            if(data_getData()->workMode == NORMAL_MODE)
            {
                if(!car_isSaddleLocked())
                {
                    car_checkSaddle();
                }

                if(setting.settingConf.isEtcSOC) //重启后则开电门获取一次SOC
                {
                    car_lockAndGetSoc();
                }
            }
            if(isPowerExist)
            {
                audio_playWithVolume(AUDIO_BEEP, 80); //带大电开机的时候"嘟"一声

                if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能产品
                {
                    if(!car_isAccOn() || setting_isDefendOn())
                    {
                        timer_start(TIMER_RFID_INIT, TIMER_MS, 4000, car_close_RFIDPower); //刚开机时若电门关或设防状态则关闭一下RFID
                    }
                }
            }
        }
    }

    last_isPowerExist = isPowerExist;
}

static void detect_vibration_handler(void)
{
    if(data_getData()->isShaking)
    {
        LOG_DEBUG("shaketimes = %d ", data_getData()->shaketimes);
        data_resetVibrationTime();//有震动清
        if(data_getData()->shaketimes > 0)
        {
            data_getData()->shaketimes--;
        }
        if(data_getData()->shaketimes == 0)
        {
            data_getData()->isShaking = L_FALSE;
        }
    }
    else
    {
        if(setting_isDefendOn())//没有震动又在设防
        {
            if(!timer_isTimerStart(TIMER_DEFENDMOVE_TIMEOUT))//不在设防移动告警则恢复移动标记
            {
                data_setMovedState(L_FALSE);
            }
        }
    }
    data_addVivrationTime();//5s+3s无震动认为没有移动

    /* 车辆不在设防状态 不在移动状态 并且车轮子没有在转 开始自动落锁计时 */
    if(!setting_isDefendOn() && !data_getData()->isMoving && !data_getData()->isShaking)
    {
        LOG_DEBUG("[Detect] staticMinues:%d RecordStime:%d  AutoLockPeriod:%d",data_getVibrationTime(),setting.statusConf.Cnt_autoLockTime,setting.settingConf.autoLockPeriod);
        if((data_getVibrationTime() + setting.statusConf.Cnt_autoLockTime) * 1000 > (setting.settingConf.autoLockPeriod* 1000)) //10min
        {
            if(setting.defaultConf.isAutoLockOn)
            {
                /* 到达自动落锁时间 自动落锁打开了 并且没有处于设防状态 自动落锁并上报通知 */
                setting_setDefend(L_TRUE);
                if(setting.statusConf.Cnt_autoLockTime != 0)
                {
                    setting.statusConf.Cnt_autoLockTime = 0;
                    statusConf_save();
                }
                data_resetVibrationTime();
                userMsg_setEvent(EVENT_ALARM, ALARM_AUTOLOCK_DEFEND);// 上报一次状态
                LOG_DEBUG("[Detect] *** Autolook ***");
            }
        }
    }
    else
    {
        /* 状态不对，重置计时 */
        if(setting.statusConf.Cnt_autoLockTime != 0)
        {
            setting.statusConf.Cnt_autoLockTime = 0;
            statusConf_save();
        }
    }
}

typedef enum
{
    MAGNETIC_IDLE,
    MAGNETIC_WAITSTATIC,
    MAGNETIC_MATCH,
} KickState_e;

static KickState_e KickState = MAGNETIC_IDLE;

static int detetc_MagneticKick(void)
{
    static u32 timeStamp = 0;
    static u8 checktimes = 0;
    static u8 ismoved = 0;
    switch (KickState)
    {
        case MAGNETIC_IDLE:
        {
            if(setting_isAccOn() && car_isMagneticKick()) //开电门状态下检测磁铁
            {
                audio_play(AUDIO_BEEP);
                KickState = MAGNETIC_WAITSTATIC;
                data_getData()->isKickMeet = 0;
                data_getData()->isKickUse = 0;
                timeStamp = rtc_getTimestamp();
                LOG_DEBUG("[detect] *** MagneticKick ***");
            }
        }
        break;
        case MAGNETIC_WAITSTATIC:
        {
            if(rtc_getTimestamp() - timeStamp > 2)
            {
                LOG_DEBUG("[detect] *** Check Wheel ***");
                if(!car_isSpeedSingal()) //轮动了
                {
                    ismoved = 1;
                }
                if(checktimes++ > 3)
                {
                    checktimes = 0;
                    if(!ismoved)
                    {
                        data_getData()->isKickMeet = 1;
                        KickState = MAGNETIC_MATCH;
                        timeStamp = rtc_getTimestamp();
                        audio_play(AUDIO_KICKOK);
                        LOG_DEBUG("[detect] *** DEFEND ***");
                    }
                    else
                    {
                        ismoved = 0;
                        data_getData()->isKickMeet = 0;
                        data_getData()->isKickUse = 0;
                        KickState = MAGNETIC_IDLE;
                        audio_play(AUDIO_KICKERROR);
                        LOG_DEBUG("[detect] *** MOVING ***");
                    }
                }
            }
            if(car_isMagneticKick() &&  KickState == MAGNETIC_WAITSTATIC)
            {
                audio_play(AUDIO_BEEP);
            }
        }
        break;
        case MAGNETIC_MATCH:
        {
            if(rtc_getTimestamp() - timeStamp > 2)
            {
                if(!data_getData()->isKickUse && !car_isSpeedSingal() ) //如果还没还车前轮子动了
                {
                    audio_play(AUDIO_KICKERROR);
                    data_getData()->isKickMeet = 0;
                    KickState = MAGNETIC_IDLE;
                    LOG_DEBUG("[detect] *** MOVE REFREASH ***");
                }
                
                if(data_getData()->isKickUse && setting_isAccOn() && data_getData()->etc.pulse > 10) //如果开电门了且轮子动了,开始检测磁铁
                {
                    data_getData()->isKickMeet = 0;
                    data_getData()->isKickUse = 0;
                    KickState = MAGNETIC_IDLE;
                }
            }
        }
        break;
        default:
            break;
    }
    return 0;
}

uint8_t detect_getKickState(void)
{
    return KickState;
}

#define DETECT_DIR_TIME     (2)     //2s
#define DETECT_DIR_ANGLE    (2)     //2°
#define DETECT_DIR_SPEED    (2)    //km/h
static void detect_heading_handler(void)
{
    static u32 cnt = 0;
    static float last_headingAngle = 0;
    float cur_headingAngle = data_getData()->headingAngle;
    
    //2s检测一次 每2°上报一次
    if(cnt++ % DETECT_DIR_TIME == 0)
    {
        cnt = 0;
        if(data_getRealEtcSpeed() < DETECT_DIR_SPEED && !setting_isDefendOn())
        {
            if((last_headingAngle <= DETECT_DIR_ANGLE && last_headingAngle >= 0 && cur_headingAngle >= (360 - DETECT_DIR_ANGLE)) || 
               (cur_headingAngle <= DETECT_DIR_ANGLE && cur_headingAngle >= 0 && last_headingAngle >= (360 - DETECT_DIR_ANGLE)))
            {
                //如果在两端 需要特殊处理一下
                if(abs(last_headingAngle - cur_headingAngle) <= (360 - DETECT_DIR_ANGLE))
                {
                    cmd_status();
                }
            }
            else if((abs(last_headingAngle - cur_headingAngle) >= DETECT_DIR_ANGLE))
            {
                cmd_status(); //如果不在两端 只需要判断角度差
            }
            last_headingAngle = cur_headingAngle;
        }
    }
}

#define ECU_ACCELERA_FAULT           (0x01 << 0)//加速度传感器故障
#define ECU_ACC_FAULT                (0x01 << 1)//电门故障
#define ETC_COM_FAULT                (0x01 << 15)//etc通信故障位
#define BMS_COM_FAULT                (0x01 << 12)//bms通信故障
#define ECU_RFID_FAULT               (0x01 << 2)//rfid通信故障

static int detect_accFault(void) //ACC故障检测
{
    static L_BOOL isAccAlarm = L_FALSE;
    DATA *pData = data_getData();

    //ACC故障检测，大电在位，软件ACC状态和硬件的不一致，发送ACC故障
    if(setting_isAccOn() != car_isAccOn() && car_isPowerExistence() && !setting_isDefendOn())
    {
        isAccAlarm = L_TRUE;
        if(pData->faultRecord.accFaultSendTimes < 3 && data_isLogined())//3次，故障未恢复则不再发送
        {
            pData->faultRecord.accFaultSendTimes++;
            LOG_DEBUG("ALARM_ACCFAULT*********");
            pData->ecuFault |= ECU_ACC_FAULT;
            cmd_faultRecord();
        }
    }
    else if(setting_isAccOn() == car_isAccOn() && car_isPowerExistence() && isAccAlarm && data_isLogined())
    {
        if(pData->faultRecord.accFaultSendTimes == 0)//故障恢复发送相同次数
        {
            isAccAlarm = L_FALSE;
        }
        else
        {
            LOG_DEBUG("ALARM_ACCFAULT_RESTORE");
            pData->faultRecord.accFaultSendTimes--;
            pData->ecuFault &= ~ECU_ACC_FAULT;//清除故障位
            cmd_faultRecord();
        }
    }

    return 0;
}

static int detect_etcFault(void) //ETC故障检测
{
    static L_BOOL isEtcAlarm = L_FALSE;
    static L_BOOL isEtcComAlarm = L_FALSE;
    DATA *pData = data_getData();

    //Fault故障检测
    if(pData->etc.fault && car_isPowerExistence() && car_isAccOn())
    {
        isEtcAlarm = L_TRUE;
        if(pData->faultRecord.etcFaultSendTimes < 3 && data_isLogined())//发送3次后,故障未恢复则不再发送
        {
            pData->faultRecord.etcFaultSendTimes++;
            LOG_INFO("ALARM_ETCFAULT******************");
            cmd_faultRecord();
        }
    }
    else if(!pData->etc.fault && car_isPowerExistence() && car_isAccOn() && isEtcAlarm && data_isLogined())
    {
        LOG_INFO("ALARM_ETCFAULT_RESTORE******************");
        if(pData->faultRecord.etcFaultSendTimes == 0)//和故障发送相同次数
        {
            isEtcAlarm = L_FALSE;
        }
        else
        {
            pData->faultRecord.etcFaultSendTimes--;
            cmd_faultRecord();
        }
    }

    //通讯故障检测
    if(!pData->faultRecord.isEtcRsp && car_isPowerExistence() && car_isAccOn())
    {
        isEtcComAlarm = L_TRUE;
        if(pData->faultRecord.etcComFaultSendTimes < 3 && data_isLogined()) //3次后,故障未恢复则不再发送
        {
            pData->faultRecord.etcComFaultSendTimes++;
            LOG_INFO("ALARM_ETCFAULT_COM ********************");
            pData->etc.fault |= ETC_COM_FAULT;//通讯故障位
            cmd_faultRecord();
        }
    }
    else if(pData->faultRecord.isEtcRsp && car_isPowerExistence() && car_isAccOn() && isEtcComAlarm)
    {
        LOG_INFO("ALARM_ETCFAULT_COM_RESTORE******************");
        if(pData->faultRecord.etcComFaultSendTimes == 0)//和故障发送相同次数
        {
            isEtcComAlarm = L_FALSE;
        }
        else
        {
            pData->faultRecord.etcComFaultSendTimes--;
            pData->etc.fault &= ~ETC_COM_FAULT;//清除通讯故障位
            cmd_faultRecord();
        }
    }

    return 0;
}

int detect_sendBmsComFault(void)  //上报三次
{
    static u8 times = 0;
    data_getData()->bms.fault |= BMS_COM_FAULT;//通讯故障位
    if(times < 3)
    {
        cmd_faultRecord();
        timer_start(TIMER_SEND_BMSFAULTLOOP, TIMER_MS, 1000, detect_sendBmsComFault);
        times++;
    }
    else
    {
        times = 0;
    }
    return 0;
}

static int detect_bmsFault(void) //BMS故障检测
{
    static L_BOOL isBmsAlarm = L_FALSE;
    static L_BOOL isBmsComAlarm = L_FALSE;
    static u8 times = 0;
    DATA *pData = data_getData();

    //fault故障 //星恒BMS暂无FAULT位
    if(setting.defaultConf.bmsType == TYPE_XIAOANBMS)
    {
        if(pData->bms.fault && car_isPowerExistence()) //目前只有易骑BMS有fault位
        {
            isBmsAlarm = TRUE;
            if(pData->faultRecord.bmsFaultSendTimes < 3 && data_isLogined())//3次，故障未恢复则不再发送
            {
                pData->faultRecord.bmsFaultSendTimes++;
                LOG_DEBUG("ALARM_BMSFAULT******************");
                cmd_faultRecord();
            }
        }
        else if(!pData->bms.fault && car_isPowerExistence() && isBmsAlarm && data_isLogined())
        {
            LOG_DEBUG("ALARM_BMSFAULT_RESTORE******************");
            if(pData->faultRecord.bmsFaultSendTimes == 0)
            {
                isBmsAlarm = FALSE;
            }
            else
            {
                pData->faultRecord.bmsFaultSendTimes--;
                cmd_faultRecord();
            }
        }
    }

    //通讯故障检测
    if(!pData->faultRecord.isBmsRsp && car_isPowerExistence() && data_isLogined())
    {
        isBmsComAlarm = L_TRUE;
        if(pData->faultRecord.bmsComFaultSendTimes < 3) //3次后,故障未恢复则不再发送
        {
            pData->faultRecord.bmsComFaultSendTimes++;
            LOG_INFO("ALARM_BMSFAULT_COM ********************");
            pData->bms.fault |= BMS_COM_FAULT;//通讯故障位
            cmd_faultRecord();
        }
    }
    else if(pData->faultRecord.isBmsRsp && car_isPowerExistence() && isBmsComAlarm && data_isLogined())
    {
        LOG_INFO("ALARM_ETCFAULT_COM_RESTORE******************");
        if(pData->faultRecord.bmsComFaultSendTimes == 0)
        {
            isBmsComAlarm = L_FALSE;
        }
        else
        {
            pData->faultRecord.bmsComFaultSendTimes--;
            pData->bms.fault &= ~BMS_COM_FAULT;//清除通讯故障位
            cmd_faultRecord();
        }
    }

    return 0;
}

static int detect_accelerationFault(void)  //加速度计故障上报
{
    static bool isAcceletaAlarm = L_FALSE;
    if(data_getData()->isAccelerometerFault)
    {
        isAcceletaAlarm = L_TRUE;
        if(data_getData()->faultRecord.acceleraFaultSendTimes < 3 && data_isLogined())
        {
            data_getData()->faultRecord.acceleraFaultSendTimes++;
            data_getData()->ecuFault |= ECU_ACCELERA_FAULT;
            cmd_faultRecord();
        }
    }
    else
    {
        if(isAcceletaAlarm)
        {
            if(data_getData()->faultRecord.acceleraFaultSendTimes == 0)
            {
                isAcceletaAlarm = L_FALSE;
            }
            else
            {
                data_getData()->faultRecord.acceleraFaultSendTimes--;
                data_getData()->ecuFault &= ~ECU_ACCELERA_FAULT;
                cmd_faultRecord();
            }
        }
    }
    return 0;
}

static int detect_rfidFault(void)  //RFID故障上报
{
    static bool isRFIDAlarm = L_FALSE;
    
    //通讯故障检测
    if(!data_getData()->faultRecord.isRFIDRsp && car_isPowerExistence() && car_isAccOn())
    {
        isRFIDAlarm = L_TRUE;
        if(data_getData()->faultRecord.rfidComFaultSendTimes < 3) //3次后,故障未恢复则不再发送
        {
            data_getData()->faultRecord.rfidComFaultSendTimes++;
            LOG_INFO("ALARM_RFIDFAULT_COM ********************");
            data_getData()->ecuFault |= ECU_RFID_FAULT;//通讯故障位
            cmd_faultRecord();
        }
    }
    else if(data_getData()->faultRecord.isRFIDRsp && car_isPowerExistence() && car_isAccOn() && isRFIDAlarm)
    {
        LOG_INFO("ALARM_RFIDFAULT_COM_RESTORE******************");
        if(data_getData()->faultRecord.rfidComFaultSendTimes == 0)
        {
            isRFIDAlarm = L_FALSE;
        }
        else
        {
            data_getData()->faultRecord.rfidComFaultSendTimes--;
            data_getData()->ecuFault &= ~ECU_RFID_FAULT;//清除通讯故障位
            cmd_faultRecord();
        }
    }
    return 0;
}

static void detect_faultRecord_handler(void)
{
    if(data_getData()->faultRecord.isDelayCheckAccState) //开电门时延迟ACC故障检测，避免误判
    {
        data_getData()->faultRecord.isDelayCheckAccState = L_FALSE;//等待1s后下一次检查
    }
    else
    {
        detect_accFault();
    }

    if(setting.defaultConf.ccuType != TYPE_NOCCU)
    {
        detect_etcFault();
    }

    if(setting.defaultConf.bmsType != TYPE_NOBMS || setting.settingConf.isEtcSOC)
    {
        detect_bmsFault();
    }
    
    if(setting.settingConf.isEtcSOC) //单线通
    {
//        detect_bmsFaultForSingle();
    }

    if(setting.settingConf.isRFIDEnable) //RFID功能产品
    {
        detect_rfidFault();
    }
    
    detect_accelerationFault();
}

static L_BOOL detect_isJudgeShaking(short x_dat, short y_dat, short z_dat)
{
#define ACCLEROMETER_THREADHOLD (1000)
    static short g_x_dat;
    static short g_y_dat;
    static short g_z_dat;
    static u8 isFirst = L_TRUE;

    L_BOOL result = L_FALSE;

    do
    {
        short tmp = 0;

        if(isFirst == L_TRUE)
        {
            isFirst = L_FALSE;
            break;
        }

        tmp = x_dat - g_x_dat;
        if(tmp > ACCLEROMETER_THREADHOLD || tmp < -ACCLEROMETER_THREADHOLD)
        {
            result = L_TRUE;
            break;
        }

        tmp = y_dat - g_y_dat;
        if(tmp > ACCLEROMETER_THREADHOLD || tmp < -ACCLEROMETER_THREADHOLD)
        {
            result = L_TRUE;
            break;
        }

        tmp = z_dat - g_z_dat;
        if(tmp > ACCLEROMETER_THREADHOLD || tmp < -ACCLEROMETER_THREADHOLD)
        {
            result = L_TRUE;
            break;
        }
    }while(L_FALSE);

    g_x_dat = x_dat;
    g_y_dat = y_dat;
    g_z_dat = z_dat;
    return result;
}

static int detect_shake_handler(void)
{
    DATA *pData = data_getData();
    short x_dat, y_dat, z_dat = 0;

    accelerometer_readOutputXYZ(&x_dat, &y_dat, &z_dat);

    //判断姿态 静止状态下 持续5秒钟姿态一致 判定姿态对应
    if(!data_getData()->isMoving && !data_getData()->isShaking)
    {
        static u32 poseTime_z = 0;
        static u32 poseTime_y = 0;
        static u32 poseTime_x = 0;
        if(pData->pose != POSE_Z && abs(z_dat) > 14000 && abs(y_dat) < 3000 && abs(x_dat) < 3000)
        {
            if(++poseTime_z > 500)
            {
                poseTime_z = 500;
                pData->pose = POSE_Z;
            }
        }
        else
        {
            poseTime_z = 0;
        }

        if(pData->pose != POSE_Y && abs(y_dat) > 14000 && abs(z_dat) < 3000 && abs(x_dat) < 3000)
        {
            if(++poseTime_y > 500)
            {
                poseTime_y = 500;
                pData->pose = POSE_Y;
            }
        }
        else
        {
            poseTime_y = 0;
        }

        if(pData->pose != POSE_X && abs(x_dat) > 14000 && abs(y_dat) < 3000 && abs(z_dat) < 3000)
        {
            if(++poseTime_x > 500)
            {
                poseTime_x = 500;
                pData->pose = POSE_X;
            }
        }
        else
        {
            poseTime_x = 0;
        }
    }

    //过滤底部抖动
    if(
        (pData->pose == POSE_Z && abs(z_dat) <= 256) ||
        (pData->pose == POSE_Y && abs(y_dat) <= 256) ||
        (pData->pose == POSE_X && abs(x_dat) <= 256)
    )
    {
        return -1;
    }

    // 判断一次震动
    if(detect_isJudgeShaking(x_dat, y_dat, z_dat))
    {
        LOG_DEBUG("SHAKE");
        pData->cnt_vibration++;
        pData->isShaking = L_TRUE;
        data_setAwakeTime(SLEEP_SHARK_WAKE);
    }

    return 0;
}

static void detect_helmetRebootHandle(u8 helmetStatus)
{
    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
    {
        if(car_isPowerExistence() == L_FALSE) //大电不在发生重启后，延时等待5v升压打开
        {
            if(data_getData()->buckstate == 1) //5v升压已经打开
            {
                if(helmetStatus == HELMET_LOCK_WITH_AUTOOPEN)
                {
                    car_unlockYaKeTe06Helmet();
                }
                else if(helmetStatus == HELMET_LOCK_ONLY)
                {
                    car_lockYaKeTe06Helmet();
                }
                else if(helmetStatus == HELMET_UNLOCK_ONLY)
                {
                    car_unlockYaKeTe06Helmet();
                }
            }
            else
            {
                timer_start(TIMER_LOCK_HELMET, TIMER_MS, 500, detect_helmetRebootHandle);
            }
        }
        else
        {
            if(helmetStatus == HELMET_LOCK_WITH_AUTOOPEN)
            {
                car_unlockYaKeTe06Helmet();
            }
            else if(helmetStatus == HELMET_LOCK_ONLY)
            {
                car_lockYaKeTe06Helmet();
            }
            else if(helmetStatus == HELMET_UNLOCK_ONLY)
            {
                car_unlockYaKeTe06Helmet();
            }            
        }
    }
    else if(setting.defaultConf.helmetType != TYPE_NOHELMET && setting.defaultConf.helmetType != TYPE_BUCKLEHELMET_SIX)
    {
        if(car_isPowerExistence() == L_FALSE) //大电不在发生重启后，延时等待5v升压打开
        {
            if(data_getData()->buckstate == 1)//5v升压已经打开
            {
                car_checkBuckHelmetState();
            }
            else
            {
                timer_start(TIMER_LOCK_HELMET, TIMER_MS, 500, detect_helmetRebootHandle);
            }
        }
        else
        {
            car_checkBuckHelmetState();
        }
    }
}

static int detect_helmet_autolock_cb(void)
{
    static u8 checkTimes = 0;
    
    if(car_isHelmetAtPos() == L_TRUE) //连续300毫秒检测到感应信号，认为锁销在孔内，执行复位动作
    {
        checkTimes++;
        if(checkTimes > 3)
        {
            checkTimes = 0;
            car_lockYaKeTe06Helmet();
            return 0;
        }
        timer_start(TIMER_LOCK_HELMET, TIMER_MS, 100, detect_helmet_autolock_cb);
    }
    else
    {
        checkTimes = 0;
    }
    return 0;
}

int detect_yaKeTeB06Helmet_handle(void)
{
    static u8 last_helmetReact = 255;
    static u8 last_helmetLock = 255;
    u8 helmetReact = car_isHelmetAtPos(); //头盔在位信号
    u8 helmetLock = car_isHelmetClose(); //锁销到位信号

    if(last_helmetReact != 255 && last_helmetReact != helmetReact) //头盔在位信号变化
    {
        if(helmetReact)
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_ATPOS);

            //如果上次为解锁后自动上锁的状态，头盔重新在位则自动上锁，且只在上锁成功后清除状态
            if(setting.statusConf.helmetTargetStatus == HELMET_AUTOLOCK_ENABLE)
            {
                //连续300毫秒检测到头盔重新在位，才认为信号有效，执行上锁
                timer_start(TIMER_LOCK_HELMET, TIMER_MS, 100, detect_helmet_autolock_cb);
            }
        }
        else
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_NOTATPOS);
        }
    }
    
    //连续2秒检测到头盔离位，才认为信号有效，置位状态；否则，清除计数
    if(setting.statusConf.helmetTargetStatus == HELMET_UNLOCK_WITH_AUTOLOCK)
    {
        static u8 checkTimes = 0;
        
        if(helmetReact == L_FALSE)
        {
            checkTimes++;
            if(checkTimes > (1000 / 100) * HELMET_CHECK_TIME)
            {
                checkTimes = 0;
                setting.statusConf.helmetTargetStatus = HELMET_AUTOLOCK_ENABLE;
                statusConf_save();
            }
        }
        else
        {
            checkTimes = 0;
        }
    }

    if(last_helmetReact == 255 && last_helmetLock == 255)
    {
        //开机如有遗留状态则重试
        if(setting.statusConf.helmetTargetStatus == HELMET_LOCK_WITH_AUTOOPEN)
        {
            if(!helmetReact || !helmetLock)
            {
                detect_helmetRebootHandle(HELMET_LOCK_WITH_AUTOOPEN);
            }
            setting.statusConf.helmetTargetStatus = HELMET_NULL;
            statusConf_save();
        }
        else if(setting.statusConf.helmetTargetStatus == HELMET_LOCK_ONLY)
        {
            detect_helmetRebootHandle(HELMET_LOCK_ONLY);
            setting.statusConf.helmetTargetStatus = HELMET_NULL;
            statusConf_save();
        }
        else if(setting.statusConf.helmetTargetStatus == HELMET_UNLOCK_ONLY)
        {
            detect_helmetRebootHandle(HELMET_UNLOCK_ONLY);
            setting.statusConf.helmetTargetStatus = HELMET_NULL;
            statusConf_save();
        }
    }

    last_helmetReact = helmetReact;
    last_helmetLock = helmetLock;
    return 0;
}

int detect_fourHelmet_handle(void) //四线头盔锁逻辑
{
    static u8 last_helmetLock = 255;
    u8 helmetLock = car_isHelmetLocked(); //锁销到位信号

    if(last_helmetLock != 255 && last_helmetLock != helmetLock) //锁销到位信号变化
    {
        if(helmetLock)
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_ATPOS);
        }
        else
        {
            userMsg_setEvent(EVENT_ALARM, ALARM_HELMET_NOTATPOS);
        }
    }

    if(last_helmetLock == 255)
    {
        //开机如有遗留状态则重试
        if(setting.statusConf.helmetTargetStatus == HELMET_UNLOCK_WITH_AUTOLOCK)
        {
            detect_helmetRebootHandle(HELMET_UNLOCK_WITH_AUTOLOCK);
        }
    }

    last_helmetLock = helmetLock;
    return 0;
}

static int detect_loop_handler(void) //1s
{
    detect_PowerChange_handler();

    detect_switchChange_handler();

    detect_SaddleChange_handler();

    detect_vibration_handler();

    detect_angle_handle();

    detect_statusChange_handler();

    if(setting.settingConf.gpsType == GPS_UBLOX_M8U || setting.settingConf.accleType == ACCLE_MPU6500) //定向停车产品
    {
        detect_heading_handler();
    }

    detect_faultRecord_handler();

    return 0;
}

int getRandNumber(unsigned int maxNum)
{
    u32 num = 0;
    srand((u32) rtc_getTimestamp());
    num = rand() % maxNum;
    return num;
}

void systemCore_handler_cb(void)
{
    if(data_isInNight(23, 7) && setting_isDefendOn() && data_isLogined()) //如果在晚上11点到早上7点时间段，且设防在线，则可升级
    {
        cmd_status(); //发送一次状态后升级
        fibo_taskSleep(3000);
        setting_checkCore();
    }
}

int detect_systemCore_handler(void)
{
    /*检测到该升级内核时，先随机延迟一个60分钟以内的时间(以秒为单位)，避免峰值效应*/
    timer_start(TIMER_GRADECORE_DELAY, TIMER_S, getRandNumber(DETECT_CORE_PERIOD * 60), systemCore_handler_cb);
}

static int detect_100ms_handler(void)
{
    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JDY)
    {
        detetc_getStaticADC();
    }

    if(setting.settingConf.accleType == ACCLE_MPU6500) //MPU6500产品
    {
        detect_shake_handler();
    }
    
    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX)
    {
        detect_yaKeTeB06Helmet_handle();
    }
    else if(setting.defaultConf.helmetType != TYPE_NOHELMET && setting.defaultConf.helmetType != TYPE_BUCKLEHELMET_SIX)
    {
        detect_fourHelmet_handle();
    }
    
    return 0;
}

void detect_initail(void)
{
    data_getData()->faultRecord.isBmsRsp = L_TRUE;//初始化默认ok
    data_getData()->faultRecord.isEtcRsp = L_TRUE;
    data_getData()->faultRecord.isRFIDRsp = L_TRUE;
    data_getData()->faultRecord.isDelayCheckAccState = L_FALSE;
    data_getData()->faultRecord.EtcComm = L_FALSE;//初始化默认没有通信
    data_getData()->faultRecord.BmsComm = L_FALSE;

    timer_startRepeat(TIMER_DETECT_LOOP, TIMER_MS, 1000, detect_loop_handler);
    timer_startRepeat(TIMER_SPEED_LOOP, TIMER_MS, 50, detect_speed_handler);
    timer_startRepeat(TIMER_MOVE_DETECT, TIMER_MS, MOVE_TIMER_PERIOD, detect_move_handler);
    timer_startRepeat(TIMER_DETECT_SHORT_LOOP, TIMER_MS, 100, detect_100ms_handler); //100ms

    if(setting_getVerisonType() == VERSION_TYPE_MX5F_JC)
    {
        data_getData()->kickType = KICK_TYPE_MAG;
        timer_startRepeat(TIMER_MAGKICKSTAND, TIMER_MS, 50, detetc_MagneticKick);
    }
    else
    {
        data_getData()->kickType = KICK_TYPE_NONE;
    }

    if(setting.settingConf.isRFIDEnable) //支持RFID功能产品
    {
        timer_startRepeat(TIMER_RFID_STATE_LOOP, TIMER_MS, RFID_STATE_TIMER_PERIOD, RFID_StateHandle);
    }
}
