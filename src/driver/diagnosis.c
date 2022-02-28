#include "adc.h"
#include "led.h"
#include "log.h"
#include "msg.h"
#include "data.h"
#include "flash.h"
#include "types.h"
#include "bioMsg.h"
#include "lis3dh.h"
#include "version.h"
#include "da14580.h"
#include "hardware.h"
#include "diagnosis.h"
#include "user_gpio.h"
#include "user_timer.h"
#include "gps_parse.h"
#include "car.h"
#include "audio_driver.h"
#include "accelerometer.h"

static int MX5Check_inputInit(void);
static int MX5Check_outputInit(void);

//==================ProductionDiagnosis=====================//
static checkLists_t checkLists =
{
    .checkstate = CHECK_START,
    .checkCSQ_count = 0,
    .isInitCheckSuccess = L_FALSE,
    .isBLECheckSuccess = L_FALSE,
    .isGPSCheckSuccess = L_FALSE,
    .isGNSSstate = L_FALSE,
};

static int diag_getVersionAndIMEI(MSG_HEADER_XA *msg)
{
    CHECK_PARAM *checkParam = (CHECK_PARAM *)msg->data;
    CHECK_MSG_INFO info = {0};
    
    data_getData()->workMode = CHECK_MODE;
    if(checkParam->param == 1) //参数为1时，表示需要检测喇叭AD
    {
        data_getData()->isCheckSPK = L_TRUE;
    }
    
    info.version = _htonl(setting.defaultConf.version);
    memcpy(info.name, setting.defaultConf.name, PRODUCT_NAME_LEN);
    memcpy(info.imei, setting_getIMEI(), MAX_IMEI_LENGTH);
    da14580_sendDATA(CHECK_ADDRESS, CMD_GET_VERSION_AND_IMEI, (u8 *)&info, sizeof(info));
    return 0;
}

static u8 diag_noNeedCheckBMS(void)
{
    if(0 == memcmp(setting.defaultConf.name, "AT-MX5K", strlen("AT-MX5K")))
    {
        return L_TRUE;//MX5K系列有BMS类型，但是未出线,不检BMS
    }
    return L_FALSE;
}

static int MX5Check_getBaseInfo(CHECK_TYPE_MSG *checkMsg)
{
    CHECK_GET_BASEINFO baseInfoRsps= {0};
    baseInfoRsps.checkType = checkMsg->checkType;
    MX5Check_outputInit();//早点输出初始状态
    bioMsg_getBootDownStatus();//获取蓝牙boot下载状态

    baseInfoRsps.version = _htonl(setting.defaultConf.version);
    memcpy(baseInfoRsps.imei, setting_getIMEI(), MAX_IMEI_LENGTH);

    //检测喇叭AD
    if(data_getData()->isCheckSPK == L_TRUE)
    {
        audio_play(AUDIO_DIAG_SPK);
    }

    //这些基本上都会检测
    baseInfoRsps.checkSignal |= 1 << SIGNAL_BIGVILTAGE;
    baseInfoRsps.checkSignal |= 1 << SIGNAL_SIMCARD;
    baseInfoRsps.checkSignal |= 1 << SIGNAL_GSM;
    baseInfoRsps.checkSignal |= 1 << SIGNAL_GPS;
    baseInfoRsps.checkSignal |= 1 << SIGNAL_SELFCHECK;
    baseInfoRsps.checkSignal |= 1 << SIGNAL_ISLOGIN;
    baseInfoRsps.checkSignal |= 1 << SIGNAL_SPK_N;
    baseInfoRsps.checkSignal |= 1 << SIGNAL_SPK_P;
    baseInfoRsps.checkSignal |= 1 << SIGNAL_BLE_BOOT;

    //需要根据配置来判断是否需要检测
    //MX5系列目前MX5Z,MX5Z3,筋斗云设备,MX5S2不检电池仓锁到位
    if(setting.defaultConf.saddleType != TYPE_JDY500MS_MX5F
       && setting.defaultConf.saddleType != TYPE_DAHACHE
       && setting.defaultConf.saddleType != TYPE_48V_BUCKLESADDLE)
    {
        LOG_INFO("INPUT_SADDLEINPLACE");
        baseInfoRsps.checkInput |= 1 << INPUT_SADDLEINPLACE;
    }

    if(setting.defaultConf.backWheelType != TYPE_NOBACKWHEEL || setting.defaultConf.helmetType != TYPE_NOHELMET)
    {
        LOG_INFO("INPUT_BACKWHELLINPLACE");
        baseInfoRsps.checkInput |= 1 << INPUT_BACKWHELLINPLACE;
    }

    //轮动信号都检测
    baseInfoRsps.checkInput |= 1 << INPUT_SPEEDSIGNAL;
    LOG_INFO("INPUT_SPEEDSIGNAL");

    if(setting.defaultConf.ccuType == TYPE_NOCCU
       && setting.defaultConf.saddleType != TYPE_JDY500MS_MX5F) //筋斗云设备不检测超速报警
    {
        baseInfoRsps.checkInput |= 1 << INPUT_OVERSPEED;
        LOG_INFO("INPUT_OVERSPEED");
    }

    if(setting.defaultConf.helmetType == TYPE_BUCKLEHELMET_SIX) //6芯头盔锁需检测感应信号
    {
        LOG_INFO("INPUT_HELMETSENSE");
        baseInfoRsps.checkInput |= 1 << INPUT_HELMETSENSE;
    }
       
    //电门都检测
    baseInfoRsps.checkOutput |= 1 << OUTPUT_ACC;
    LOG_INFO("OUTPUT_ACC");

    baseInfoRsps.checkOutput |= 1 << OUTPUT_SADDLE_ON;
    LOG_INFO("OUTPUT_SADDLE_ON");

    //48V电磁锁只有开锁，故只检测开锁
    if(setting.defaultConf.saddleType != TYPE_EMAGNETICSADDLE
       && setting.defaultConf.saddleType != TYPE_JDY500MS_MX5F
       && setting.defaultConf.saddleType != TYPE_48V_SADDLELOCK_200
       && setting.defaultConf.saddleType != TYPE_48V_200_XBD
       && setting.defaultConf.saddleType != TYPE_48V_BUCKLESADDLE)
    {
        baseInfoRsps.checkOutput |= 1 << OUTPUT_SADDLE_OFF;
        LOG_INFO("OUTPUT_SADDLE_OFF");
    }

    if(setting.defaultConf.backWheelType != TYPE_NOBACKWHEEL || setting.defaultConf.helmetType != TYPE_NOHELMET)
    {
        baseInfoRsps.checkOutput |= 1 << OUTPUT_BACKWHELL_ON;
        LOG_INFO("OUTPUT_BACKWHELL_ON");
        if(setting.defaultConf.helmetType != TYPE_EMAGNETICHELMET)//头盔锁类型不为48V锁，这种锁只有开没有关
        {
            baseInfoRsps.checkOutput |= 1 << OUTPUT_BACKWHELL_OFF;
            LOG_INFO("OUTPUT_BACKWHELL_OFF");
        }
    }
    if(setting.defaultConf.ccuType == TYPE_NOCCU || setting.defaultConf.ccuType == TYPE_JINGHUICCU)//无控制器或者金丰协议
    {
        baseInfoRsps.checkOutput |= 1 << OUTPUT_BREAK_OPERATE;
        LOG_INFO("OUTPUT_BREAK_OPERATE");
    }
    //MX5D2&MX5D4需检测给LED灯供电的5V
    if((setting_getVerisonType() == VERSION_TYPE_MX5D2) || (setting_getVerisonType() == VERSION_TYPE_MX5D4))
    {
        baseInfoRsps.checkOutput |= 1 << OUTPUT_LIGHT;
        LOG_INFO("OUTPUT_LED_5V");
    }

    if(setting.settingConf.isRFIDEnable == L_TRUE) //RFID 5V检测及通讯检测
    {
        baseInfoRsps.checkOutput |= 1 << OUTPUT_RFID_5V;
        LOG_INFO("OUTPUT_RFID_5V");
        baseInfoRsps.checkTrans |= 1 << TRANS_RFIDCOM;
        LOG_INFO("TRANS_RFIDCOM");
    }

    da14580_sendDATA(CHECK_ADDRESS, CMD_CHK_ALL_NEW, (u8 *)&baseInfoRsps, sizeof(baseInfoRsps));
    MX5Check_inputInit();//晚点读外部状态
    return 0;
}

static int MX5Check_checkSignal(CHECK_TYPE_MSG *checkMsg)
{
    CHECK_TYPE_MSG_RSP msgRsp = {0};
    msgRsp.checkType = checkMsg->checkType;
    msgRsp.checkGroup = checkMsg->checkGroup;
    if(0 != checkMsg->checkParam[SIGNAL_BIGVILTAGE])
    {
        //检测大电压
        u8 batVoltage = 0;
        u8 voltage = 0;
        adc_getVoltageSync(&data_getData()->vehicleBattery_mV,ADC_PWR_DETECT);
        batVoltage = data_getData()->vehicleBattery_mV / 1000;
        voltage = checkMsg->checkParam[SIGNAL_BIGVILTAGE];
        LOG_INFO("battery voltage check: expect %d , actural %d", voltage, batVoltage);
        if (abs(batVoltage - voltage) > 5)  //允许电压波动5v
        {
            msgRsp.checkParamRsp |= 1 << SIGNAL_BIGVILTAGE;
        }
    }

    if(0 != checkMsg->checkParam[SIGNAL_SIMCARD])
    {
        //检测卡
        LOG_INFO("IMSI:%s", setting_getIMSI());
        if(!setting_getIMSI())
        {
            msgRsp.checkParamRsp |= 1 << SIGNAL_SIMCARD;
        }
    }

    if(0 != checkMsg->checkParam[SIGNAL_GSM])
    {
        //检测GSM信号
        INT32 csq = 0, ber = 0;
        fibo_get_csq(&csq, &ber);
        LOG_INFO("want csq:%d, real csq:%d", checkMsg->checkParam[SIGNAL_GSM], csq);
        if(csq <= 0 || csq < checkMsg->checkParam[SIGNAL_GSM])
        {
            msgRsp.checkParamRsp |= 1 << SIGNAL_GSM;
        }
    }

    if(0 != checkMsg->checkParam[SIGNAL_GPS])
    {
        //检测GPS定位
        CHECK_GPS rsp;
        LOG_INFO("data_getData()->position.isGPS:%d", data_getData()->lastPosition.isGPS);
        if(data_getData()->lastPosition.isGPS)
        {
            rsp.lat = gps_getGPSValue(data_getData()->lastPosition.nmeaInfo.lat);
            rsp.lon = gps_getGPSValue(data_getData()->lastPosition.nmeaInfo.lon);
            if(rsp.lat == 0 || rsp.lon == 0)
            {
                msgRsp.checkParamRsp |= 1 << SIGNAL_GPS;
            }
        }
        else
        {
            msgRsp.checkParamRsp |= 1 << SIGNAL_GPS;
        }
    }

    if(0 != checkMsg->checkParam[SIGNAL_SELFCHECK])
    {
        //检测设备自检结果(包括SIM卡，信号强度，小电池电压，加速度计以及蓝牙和GPS)
        LOG_INFO("Init:%d GPS:%d BLE:%d", checkLists.isInitCheckSuccess, checkLists.isGPSCheckSuccess, checkLists.isBLECheckSuccess);
        if(!checkLists.isInitCheckSuccess || !checkLists.isGPSCheckSuccess || !checkLists.isBLECheckSuccess)
        {
            msgRsp.checkParamRsp |= 1 << SIGNAL_SELFCHECK;
        }
    }

    if(0 != checkMsg->checkParam[SIGNAL_ISLOGIN])
    {
        //检测登录状态
        LOG_INFO("data_isLogined:%d", data_isLogined());
        if(!data_isLogined())
        {
            msgRsp.checkParamRsp |= 1 << SIGNAL_ISLOGIN;
        }
    }

    if(0 != checkMsg->checkParam[SIGNAL_SPK_N])
    {
        //检测喇叭电压 常规4欧喇叭，1.0-1.8V认为是合格电压，8欧合格电压为1.6V-2.4V
        u8 adc_spkN = 0;
        adc_spkN = checkMsg->checkParam[SIGNAL_SPK_N];
        LOG_INFO("adc_spkN :%d", checkMsg->checkParam[SIGNAL_SPK_N]);

        //目前MX5K系列+ME5K6产品为8欧喇叭
        if(0 == memcmp(setting.defaultConf.name, "AT-MX5K", strlen("AT-MX5K")) || 0 == memcmp(setting.defaultConf.name, "AT-ME5K6", strlen("AT-ME5K6")))
        {
            if(adc_spkN < 160 || adc_spkN > 240)  //SPK两个引脚的AD值放大100倍
            {
                msgRsp.checkParamRsp |= 1 << SIGNAL_SPK_N;
            }
        }
        else
        {
            if(adc_spkN < 100 || adc_spkN > 180)
            {
                msgRsp.checkParamRsp |= 1 << SIGNAL_SPK_N;
            }
        }
    }

    if(0 != checkMsg->checkParam[SIGNAL_SPK_P])
    {
        //检测喇叭电压
        u8 adc_spkP = 0;
        adc_spkP = checkMsg->checkParam[SIGNAL_SPK_P];
        LOG_INFO("adc_spkP :%d", checkMsg->checkParam[SIGNAL_SPK_P]);

        //目前MX5K系列+ME5K6产品为8欧喇叭
        if(0 == memcmp(setting.defaultConf.name, "AT-MX5K", strlen("AT-MX5K")) || 0 == memcmp(setting.defaultConf.name, "AT-ME5K6", strlen("AT-ME5K6")))
        {
            if(adc_spkP < 160 || adc_spkP > 240)
            {
                msgRsp.checkParamRsp |= 1 << SIGNAL_SPK_P;
            }
        }
        else
        {
            if(adc_spkP < 100 || adc_spkP > 180)
            {
                msgRsp.checkParamRsp |= 1 << SIGNAL_SPK_P;
            }
        }
    }

    if(0 != checkMsg->checkParam[SIGNAL_BLE_BOOT])
    {
        //检测蓝牙BOOT是否已下载
        LOG_INFO("data_getData()->isBleBootDown :%d", data_getData()->isBleBootDown);
        if(data_getData()->isBleBootDown == L_FALSE)
        {
            msgRsp.checkParamRsp |= 1 << SIGNAL_BLE_BOOT;
        }
    }

    da14580_sendDATA(CHECK_ADDRESS, CMD_CHK_ALL_NEW, (u8 *)&msgRsp, sizeof(msgRsp));
    return 0;
}

static u8 firstSaddleInplaceState = 0;
static u8 firstbackWheelInplaceState = 0;
static u8 firstSpeedSingalState = 0;
static u8 firstOverSpeedState = 0;
static u8 firstHelmetSenseState = 0;
static int MX5Check_inputInit(void)
{
    firstSaddleInplaceState = car_isSaddleLocked();
    firstbackWheelInplaceState = car_isBackWheelLocked();
    firstSpeedSingalState = car_isSpeedSingal();
    firstOverSpeedState = car_isOverSpeed();
    firstHelmetSenseState = car_isHelmetAtPos();
    LOG_INFO("firstSaddleInplaceState:%d, firstbackWheelInplaceState:%d, firstSpeedSingalState:%d, firstOverSpeedState:%d, firstHelmetSenseState:%d",
             firstSaddleInplaceState, firstbackWheelInplaceState, firstSpeedSingalState, firstOverSpeedState, firstHelmetSenseState);
    return 0;
}

static int MX5Check_outputInit(void)
{
    u8 pinMask = 0;
    pinMask = PIN_MASK_SADDLE_N_DRIVER | PIN_MASK_BACKWHEEL_N_DRIVER | PIN_MASK_ACC_DRIVER;
    control595(pinMask, GPIO_LEVEL_LOW);
    pinMask =  PIN_MASK_SADDLE_P_DRIVER | PIN_MASK_BACKWHEEL_P_DRIVER | PIN_MASK_BRAKE_DRIVER;
    control595(pinMask, GPIO_LEVEL_HIGH);
    da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_HIGH); //拉高蓝牙5V供电
    return 0;
}

static int MX5Check_outputDeInit(void)
{
    u8 pinMask = 0;
    pinMask = PIN_MASK_SADDLE_N_DRIVER | PIN_MASK_BACKWHEEL_N_DRIVER | PIN_MASK_ACC_DRIVER | PIN_MASK_SADDLE_P_DRIVER | PIN_MASK_BACKWHEEL_P_DRIVER | PIN_MASK_BRAKE_DRIVER;
    control595(pinMask, GPIO_LEVEL_LOW);
    da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_LOW);
    return 0;
}

CHECK_TYPE_MSG_RSP msgInputRsp = {0};
static int MX5Check_detectInput_cb(void)
{
    LOG_INFO("msgInputRsp.checkParamRsp:%d", msgInputRsp.checkParamRsp);
    if(0 != (msgInputRsp.checkParamRsp & (0X000001 << INPUT_SADDLEINPLACE)))//此项未检过
    {
        LOG_INFO("second detect saddle inplace:%d", car_isSaddleLocked());
        if(firstSaddleInplaceState != car_isSaddleLocked())
        {
            LOG_INFO("second detect saddle inplace succ");
            msgInputRsp.checkParamRsp &= ~(1 << INPUT_SADDLEINPLACE);//检过,清掉此标记为
        }
    }
    if(0 != (msgInputRsp.checkParamRsp & (0X000001 << INPUT_BACKWHELLINPLACE)))//此项未检过
    {
        //后轮到位信号输入
        LOG_INFO("second detect backwheel inplace:%d", car_isBackWheelLocked());
        if(firstbackWheelInplaceState != car_isBackWheelLocked())
        {
            LOG_INFO("second detect backwheel inplace succ");
            msgInputRsp.checkParamRsp &= ~(1 << INPUT_BACKWHELLINPLACE);//检过,清掉此标记为
        }
    }
    if(0 != (msgInputRsp.checkParamRsp & (0X000001 << INPUT_SPEEDSIGNAL)))//此项未检过
    {
        //轮动信号输入
        LOG_INFO("second detect speedSingal:%d", car_isSpeedSingal());
        if(firstSpeedSingalState != car_isSpeedSingal())
        {
            LOG_INFO("second detect speedSingal succ");
            msgInputRsp.checkParamRsp &= ~(1 << INPUT_SPEEDSIGNAL);//检过,清掉此标记为
        }
    }
    if(0 != (msgInputRsp.checkParamRsp & (0X000001 << INPUT_OVERSPEED)))//此项未检过
    {
        //超速信号输入
        LOG_INFO("second detect overspeed:%d", car_isOverSpeed());
        if(firstOverSpeedState != car_isOverSpeed())
        {
            LOG_INFO("second detect overspeed succ");
            msgInputRsp.checkParamRsp &= ~(1 << INPUT_OVERSPEED);//检过,清掉此标记为
        }
    }        
    if(0 != (msgInputRsp.checkParamRsp & (0X000001 << INPUT_HELMETSENSE)))//此项未检过
    {
        //超速信号输入
        LOG_INFO("second detect helmetsense:%d", car_isHelmetAtPos());
        if(firstHelmetSenseState != car_isHelmetAtPos())
        {
            LOG_INFO("second detect helmetsense succ");
            msgInputRsp.checkParamRsp &= ~(1 << INPUT_HELMETSENSE);//检过,清掉此标记为
        }
    }
    da14580_sendDATA(CHECK_ADDRESS, CMD_CHK_ALL_NEW, (u8 *)&msgInputRsp, sizeof(msgInputRsp));
    timer_stop(TIMER_DIAG_DETECT);
    return 0;
}
static int MX5Check_checkInput(CHECK_TYPE_MSG *checkMsg)
{
    memset((u8 *)&msgInputRsp, 0, sizeof(msgInputRsp));
    msgInputRsp.checkType = checkMsg->checkType;
    msgInputRsp.checkGroup = checkMsg->checkGroup;
    if(0 != checkMsg->checkParam[INPUT_SADDLEINPLACE])
    {
        //电池仓到位信号输入
        msgInputRsp.checkParamRsp |= 1 << INPUT_SADDLEINPLACE;
        LOG_INFO("saddle inplace:%d", msgInputRsp.checkParamRsp);
    }
    if(0 != checkMsg->checkParam[INPUT_BACKWHELLINPLACE])
    {
        //后轮到位信号输入
        msgInputRsp.checkParamRsp |= 1 << INPUT_BACKWHELLINPLACE;
        LOG_INFO("backwheel inplace:%d", msgInputRsp.checkParamRsp);
    }
    if(0 != checkMsg->checkParam[INPUT_SPEEDSIGNAL])
    {
        //轮动信号输入
        msgInputRsp.checkParamRsp |= 1 << INPUT_SPEEDSIGNAL;
        LOG_INFO("speedSingal:%d", msgInputRsp.checkParamRsp);
    }
    if(0 != checkMsg->checkParam[INPUT_OVERSPEED])
    {
        //超速信号输入
        msgInputRsp.checkParamRsp |= 1 << INPUT_OVERSPEED;
        LOG_INFO("overspeed:%d", msgInputRsp.checkParamRsp);
    }    
    if(0 != checkMsg->checkParam[INPUT_HELMETSENSE])
    {
        //超速信号输入
        msgInputRsp.checkParamRsp |= 1 << INPUT_HELMETSENSE;
        LOG_INFO("INPUT_HELMETSENSE:%d", msgInputRsp.checkParamRsp);
    }
    timer_start(TIMER_DIAG_DETECT, TIMER_MS, 50, MX5Check_detectInput_cb);
    return 0;
}

static int MX5Check_checkOutput(CHECK_TYPE_MSG *checkMsg)
{
    u8 pinLowMask = 0;
    u8 pinHightMask = 0;
    CHECK_TYPE_MSG_RSP msgRsp = {0};
    msgRsp.checkType = checkMsg->checkType;
    msgRsp.checkGroup = checkMsg->checkGroup;
    if(0 != checkMsg->checkParam[OUTPUT_ACC])
    {
        //检测电门
        LOG_INFO("set acc on");
        pinHightMask |= PIN_MASK_ACC_DRIVER;
    }
    if(0 != checkMsg->checkParam[OUTPUT_SADDLE_ON] || 0 != checkMsg->checkParam[OUTPUT_SADDLE_OFF])
    {
        //电池仓开关,      硬件上对应的P,N必须是反逻辑才能正常控制，需要同时操作P和N
        LOG_INFO("set saddle on or off");
        pinHightMask |= PIN_MASK_SADDLE_N_DRIVER;
        pinLowMask |= PIN_MASK_SADDLE_P_DRIVER;
    }
    if(0 != checkMsg->checkParam[OUTPUT_BACKWHELL_ON] || 0 != checkMsg->checkParam[OUTPUT_BACKWHELL_OFF])
    {
        //后轮锁开关,      硬件上对应的P,N必须是反逻辑才能正常控制，需要同时操作P和N
        LOG_INFO("set backwhell on or off");
        pinHightMask |= PIN_MASK_BACKWHEEL_N_DRIVER;
        pinLowMask |= PIN_MASK_BACKWHEEL_P_DRIVER;
    }
    if(0 != checkMsg->checkParam[OUTPUT_BREAK_OPERATE])
    {
        //刹车脚
        LOG_INFO("set break on");
        pinLowMask |= PIN_MASK_BRAKE_DRIVER;
    }
    if(0 != checkMsg->checkParam[OUTPUT_LIGHT] || 0 != checkMsg->checkParam[OUTPUT_RFID_5V])
    {
        //LED灯
        LOG_INFO("set BLE 5V off");
        da14580_setBlePinLevel(BLE_PORT2, BLE_PIN5, PIN_LEVEL_LOW); //关闭蓝牙5V供电
    }

    control595(pinHightMask, GPIO_LEVEL_HIGH);
    control595(pinLowMask, GPIO_LEVEL_LOW);

    da14580_sendDATA(CHECK_ADDRESS, CMD_CHK_ALL_NEW, (u8 *)&msgRsp, sizeof(msgRsp));
    return 0;
}

static int MX5Check_checkTrans(CHECK_TYPE_MSG *checkMsg)
{
    CHECK_TYPE_MSG_RSP msgRsp = {0};
    msgRsp.checkType = checkMsg->checkType;
    msgRsp.checkGroup = checkMsg->checkGroup;
    da14580_sendDATA(CHECK_ADDRESS, CMD_CHK_ALL_NEW, (u8 *)&msgRsp, sizeof(msgRsp));
    return 0;
}

static int MX5Check_checkReboot_cb(void)
{
    setting_setRebootType(REBOOT_COMAND);
    fibo_softPowerOff();
    return 0;
}

static int MX5Check_checkConst(CHECK_TYPE_MSG *checkMsg)
{
    CHECK_TYPE_MSG_RSP msgRsp = {0};
    msgRsp.checkType = checkMsg->checkType;
    msgRsp.checkGroup = checkMsg->checkGroup;
    da14580_sendDATA(CHECK_ADDRESS, CMD_CHK_ALL_NEW, (u8 *)&msgRsp, sizeof(msgRsp));
    if(0 != checkMsg->checkParam[0])//检测不通过
    {
        audio_play(AUDIO_DIAG_FAIL);
    }
    else//检测通过
    {
        audio_play(AUDIO_DIAG_SUCCESS);
        timer_start(TIMER_DIAG_DETECT, TIMER_MS, 5000, MX5Check_checkReboot_cb);
    }
    MX5Check_outputDeInit();
    data_getData()->workMode = NORMAL_MODE;
    return 0;
}

int MX5Check_checkAll_rsp(MSG_HEADER_XA *msg)
{
    MSG_HEADER_XA *checkMsgRsp = (MSG_HEADER_XA *)msg;
    CHECK_TYPE_MSG *typeMsg = (CHECK_TYPE_MSG *)checkMsgRsp->data;
    switch(typeMsg->checkType)
    {
        case CHECK_TYPE_GETBASEINFO:
        {
            MX5Check_getBaseInfo(typeMsg);
        }
        break;
        case CHECK_TYPE_CHECKSIGNAL:
        {
            MX5Check_checkSignal(typeMsg);
        }
        break;
        case CHECK_TYPE_CHECKINPUT:
        {
            MX5Check_checkInput(typeMsg);
        }
        break;
        case CHECK_TYPE_CHECKOUTPUT:
        {
            MX5Check_checkOutput(typeMsg);
        }
        break;
        case CHECK_TYPE_CHECKTRANS:
        {
            MX5Check_checkTrans(typeMsg);
        }
        break;
        case CHECK_TYPE_CHECKCONST:
        {
            MX5Check_checkConst(typeMsg);
        }
        break;
    }
    return 0;
}

PROC_MAP diag_msg_procs[] =
{
    {CMD_GET_VERSION_AND_IMEI,   (DA14580_PROC) diag_getVersionAndIMEI},
    {CMD_CHK_ALL_NEW,           (DA14580_PROC) MX5Check_checkAll_rsp},
};

int diag_diagMsgProc(u8* data, u16 dataLen)
{
    u8 i = 0;
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)data;

    for(i = 0; i < sizeof(diag_msg_procs)/sizeof(diag_msg_procs[0]); i++)
    {
        if(diag_msg_procs[i].cmd == msg->cmd)
        {
            LOG_INFO("check %d", diag_msg_procs[i].cmd);
            if(diag_msg_procs[i].action)
                diag_msg_procs[i].action(msg);
            return 0;
        }
    }

    return -1;
}


//==================checkSelf=====================//

static bool diag_checkSimCard(void);
static bool diag_checkMoudleCSQ(void);
static bool diag_checkCbcVoltage(void);
static void diag_LedRefrash(void);

static bool diag_checkSimCard(void)
{
    u8 imsi[32] = {0};
    u8 ret = fibo_get_imsi(imsi);
    if (ret != 0)
    {
        u16 rsp = C_SIMCARD_FAIL;
        da14580_sendDATA(CHECK_ADDRESS, CMD_CHK_SIMCARD, (u8 *)&rsp, sizeof(rsp));
        return L_FALSE;
    }

    LOG_INFO("imsi=%s", imsi);

    return L_TRUE;
}

static bool diag_checkMoudleCSQ(void)
{
    INT32 csq;
    INT32 ber;
    u8 ret;
    ret = fibo_get_csq(&csq, &ber);
    if(ret != 0)
    {
        return L_FALSE;
    }
    else
    {
        if (csq < 7)
        {
            //LOG_DEBUG("GSM signal quality not enough: %d", csq);
            return L_FALSE;
        }
        else
        {
            LOG_INFO("GSM passed, csq=%d", csq);
            return L_TRUE;
        }

    }
}

void diag_selfCheckDeinit(void)
{
    data_getData()->checkBle = L_FALSE;
    checkLists.checkstate = CHECK_START;
    checkLists.isInitCheckSuccess = L_FALSE;
    checkLists.isBLECheckSuccess = L_FALSE;
    checkLists.isGPSCheckSuccess = L_FALSE;
    checkLists.isGNSSstate = L_FALSE;
}

/*
 * 自检总入口
 */
int diag_selfCheck(void)
{
    DATA *pData = data_getData();
    //进入自检状态，开始闪灯
    if( !timer_isTimerStart(TIMER_WORK_BLINK))
    {
        diag_LedRefrash();
    }
    switch (checkLists.checkstate)
    {
        case CHECK_START:
        {
            timer_startRepeat(TIMER_DIAG_CHECK, TIMER_MS, 100, diag_selfCheck); //
            checkLists.checkstate = CHECK_SIMCARD;
        }
        break;
        case CHECK_SIMCARD:
        {
            if(diag_checkSimCard())
            {
                pData->checkSimcard = L_TRUE;
                checkLists.checkstate = CHECK_ACCELEROMETER;
            }
            else
            {
                LOG_ERROR("[Diag] SIMCARD check failed!");
                pData->checkSimcard = L_FALSE;
                checkLists.checkstate = CHECK_FAILED;
            }
        }
        break;
        case CHECK_ACCELEROMETER:
        {
            if(accelerometer_check() != true)
            {
                fibo_taskSleep(50);
                if(accelerometer_check() != true)
                {
                    LOG_ERROR("Accelerometer check failed!");
                    pData->checkAccel = L_FALSE;
                    checkLists.checkstate = CHECK_FAILED;
                    return 0;
                }
            }
            LOG_ERROR("Accelerometer check success!");
            pData->checkAccel = L_TRUE;
            checkLists.checkstate = CHECK_CSQ;
        }
        break;
        case CHECK_CSQ:
        {
            if(checkLists.checkCSQ_count < CHECK_CSQCOUNT_MAX * 10)
            {
                if(diag_checkMoudleCSQ())
                {
                    pData->checkCSQ = L_TRUE;
                    checkLists.checkstate = CHECK_SUCCESS;
                    checkLists.checkCSQ_count = 0;
                }
                else
                {
                    pData->checkCSQ = L_FALSE;
                }
            }
            else
            {
                LOG_ERROR("[Diag] CSQ check failed!");
                checkLists.checkstate = CHECK_FAILED;
            }
        }
        break;
        case CHECK_SUCCESS:
        {
            checkLists.isInitCheckSuccess = L_TRUE;
            timer_stop(TIMER_DIAG_CHECK);
            diag_LedRefrash();
        }
        break;
        case CHECK_FAILED:
        {
            checkLists.isInitCheckSuccess = L_FALSE;
            checkLists.checkstate = CHECK_START; //自检不过，则一直重复自检
            diag_LedRefrash();
        }
        break;
        default:
            break;
    }
    return 0;
}

int diag_GPSCheckSuccess(void)
{
    checkLists.isGPSCheckSuccess = L_TRUE;
    diag_LedRefrash();
    return 0;
}
int diag_GNSSState(u8 state)
{
    checkLists.isGNSSstate = state;
    diag_LedRefrash();
    return 0;
}
int diag_DA14580CheckSuccess(void)
{
    LOG_INFO("[Diag] DA14580 check success");
    data_getData()->checkBle = L_TRUE;
    checkLists.isBLECheckSuccess = L_TRUE;
    diag_LedRefrash();
    return 0;
}

static void diag_LedRefrash(void)
{
    if(checkLists.isGNSSstate == L_TRUE)
    {
        LED_on(LED_GNSS);
    }
    else
    {
        LED_startFastBlink(LED_GNSS);
    }

    if(checkLists.isInitCheckSuccess && checkLists.isGPSCheckSuccess && checkLists.isBLECheckSuccess)
    {
        LED_on(LED_WORK);
    }
    else
    {
        LOG_DEBUG("[Diag] Init:%d GPS:%d BLE:%d",checkLists.isInitCheckSuccess,checkLists.isGPSCheckSuccess,checkLists.isBLECheckSuccess);
        LED_startFastBlink(LED_WORK);
    }
}



