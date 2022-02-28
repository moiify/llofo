#include <string.h>
#include "log.h"
#include "data.h"
#include "msg.h"
#include "da14580.h"
#include "setting.h"
#include "rtc.h"
#include "etcMsg.h"
#include "bioMsg.h"
#include "bleMsg.h"
#include "diagnosis.h"
#include "user_fs.h"
#include "user_timer.h"
#include "etc_ota.h"
#include "car.h"
#include "ETC_XiaoAn.h"
#include "event.h"

extern u8 *g_etcFirmwareData;
extern u8 *g_etcFirmwareDataP;
extern u16 g_etcPackID;
extern u16 g_etcSendCompleteFlag;
extern u16 g_etcResendLenBak;
extern u32 g_etcFirmwareDataBytes;
extern u16 g_etcSendDataLenPerTime;
extern u16 g_etcRetransferCnt;
extern u16 g_etcReupgradeCnt;
extern u16 g_etcResendCommpleteDataCnt;

static void ETC_XiaoAn_SetFuncSwitch(void);
static int ETC_XiaoAn_retransfer_handler(void);
static int ETC_XiaoAn_sendDATA(u8 address, u8 cmd, u8 *data, u8 dataLen);
static void *ETC_XiaoAn_allocMsg(u8 address, u8 cmd, u8 *data, u8 dataLen);

static int ETC_XiaoAn_SetSpeedAction(void)
{
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_SPEED, &setting.defaultConf.etcSpeed, 1);
}

static int ETC_XiaoAn_GetETCInfoAction(void)
{
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_INFO, NULL, 0);
}

static int ETC_XiaoAn_GetSOCAction(void)
{
    data_getData()->bms.getSocTimes++;
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_SOC, NULL, 0);
}

static int ETC_XiaoAn_SetProtectVoltageAction(void)
{
    uint16_t protectVoltage = _htons(setting.settingConf.etcProtectVoltage_100mV);
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_PROTECTION_VOLTAGE, (uint8_t *)&protectVoltage, sizeof(uint16_t));
}

static u8 g_isDefend = 0;
int ETC_XiaoAn_SetDefendAction(void)
{
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_DEFEND, &g_isDefend, 1);
}

int ETC_XiaoAn_SetAccOnAction(void)
{
    u8 acc = 0xA5;
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_ACC, &acc, 1);
}

static u8 g_light = 0;
static int ETC_XiaoAn_SetLightAction(void)
{
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_LIGHT, &g_light, 1);
}

static int ETC_XiaoAn_SetIfSlowStartAction(void)
{
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_SLOWSTART, &setting.settingConf.etcIsSlowStart, sizeof(uint8_t));
}

static int ETC_XiaoAn_SetLimitCurrentAction(void)
{
    uint16_t limitCurrent = _htons(setting.settingConf.etcLimitCurrent_100mA);
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_LIMIT_CURRENT, (uint8_t *)&limitCurrent, sizeof(uint16_t));
}

static int ETC_XiaoAn_SetFuncSwitchAction(void)
{
    return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_FUNC, &setting.settingConf.etcFuncSwitch, 1);
}
static int ETC_XiaoAn_SetSocAction(void)
{
    if(0 != memcmp(data_getData()->bms.SN, "\x00\x00\x00\x00\x00\x00", 6))
    {
        u8 myData[3] = {0};
        DATA_16_BITS *u16Data = (DATA_16_BITS *)(myData + 1);

        myData[0] = data_getData()->bms.SOC;
        u16Data->data = _ntohs(data_getData()->bms.voltage);

        return ETC_XiaoAn_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_BMS_SOC, myData, sizeof(myData));
    }
    return 0;
}

static int ETC_XiaoAn_StartOTAAction(void)
{
    XIAOAN_ETC_START_OTA OTAMSG;
    OTAMSG.etc_version = setting.statusConf.etcUpgradeVersion;
    OTAMSG.etc_firmwareDataBytes = _ntohl(g_etcFirmwareDataBytes);
    LOG_DEBUG("[ETC_XiaoAn] ****** ETC_XiaoAn_SendOTAAction Version:%d ******",OTAMSG.etc_version);
    return da14580_sendDATA(ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_START, (u8 *)&OTAMSG, sizeof(XIAOAN_ETC_START_OTA));
}

static int ETC_XiaoAn_OTARealDataAction(void)
{
    int i = 0, rc = 0, m = 0;
    u8 *senddata = NULL;
    u32 datalen = g_etcSendDataLenPerTime + 2;
    u8 *p = (u8*)Malloc(datalen);

    if(NULL == p)
    {
        Free(p);
        return -1;
    }
    senddata = p;
    g_etcPackID++;
    *senddata++ = (u8)(g_etcPackID >> 8);
    *senddata++ = (u8)g_etcPackID;
    for(i = 0; i < g_etcSendDataLenPerTime; i++)
    {
        if((g_etcPackID - 1) * g_etcSendDataLenPerTime + i < g_etcFirmwareDataBytes)
        {
            *senddata++ = *g_etcFirmwareData++;
        }
        else
        {
            g_etcSendCompleteFlag = 1;
            break;
        }
    }
    if((g_etcPackID - 1) * g_etcSendDataLenPerTime + i == g_etcFirmwareDataBytes && g_etcSendCompleteFlag != 1)//当升级包是每帧发送长度的整数倍的时候会触发
    {
        g_etcSendCompleteFlag = 1;
    }

    LOG_DEBUG("[ETC_XiaoAn]********* g_etcSendDataLenPerTime:%d,etc_sendcnt:%d,total:%d,i:%d,*******************", g_etcSendDataLenPerTime,g_etcPackID, g_etcFirmwareDataBytes/g_etcSendDataLenPerTime, i);
    rc = da14580_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_DATA, senddata-(i+2), i+2);
    ASYNC_PROC_MAP * etc_async_procs = etcMsg_getAsyncProcs();
    //升级时，actionTimes手动加1，兼容异步机制，保证升级数据发出
    for(m = 0; m < etcMsg_getAsyncProcsSize(); m++)
    {
        if(etc_async_procs[m].address == XIAOAN_ETC_ADDRESS && etc_async_procs[m].cmd == XIAOAN_SET_ETC_UPGRADE_DATA)
        {
            etc_async_procs[m].actionTimes++;
        }
    }
    g_etcResendLenBak = i;
    timer_start(TIMER_ETC_RETRANSFER, TIMER_S, 2, ETC_XiaoAn_retransfer_handler);
    Free(p);
    return rc;
}

int ETC_XiaoAn_retransfer_handler() //升级包数据重发机制
{
    int i = 0, m = 0;
    u8 *p = (u8*)Malloc(g_etcResendLenBak + 2);
    u8 *senddata = NULL;
    if(NULL == p)
    {
        LOG_ERROR("[ETC_XA] malloc memory failed");
        return -1;
    }
    g_etcRetransferCnt++;
    LOG_DEBUG("**********failed to receive upgrade data response,retransfer now,g_etcPackID:%d  ************", g_etcPackID);
    senddata=p;
    *senddata++ = (u8)(g_etcPackID>>8);
    *senddata++ = (u8)g_etcPackID;
    g_etcFirmwareData = g_etcFirmwareData-g_etcResendLenBak;
    for(i = 0; i < g_etcResendLenBak; i++)
    {
        *senddata++ = *g_etcFirmwareData++;
    }
    LOG_DEBUG("retransfer: g_etcResendLenBak = %d", g_etcResendLenBak);
    LOG_HEX(g_etcFirmwareData - g_etcResendLenBak, g_etcResendLenBak);
    da14580_sendDATA(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_DATA, senddata - (i + 2), i + 2);
    ASYNC_PROC_MAP * etc_async_procs = etcMsg_getAsyncProcs();
    //升级时，actionTimes手动加1，兼容异步机制，保证升级数据发出
    for(m = 0; m < etcMsg_getAsyncProcsSize(); m++)
    {
        if(etc_async_procs[m].address == XIAOAN_ETC_ADDRESS && etc_async_procs[m].cmd == XIAOAN_SET_ETC_UPGRADE_DATA)
        {
            etc_async_procs[m].actionTimes++;
        }
    }

    Free(p);
    if(g_etcRetransferCnt < 3)
    {
        timer_start(TIMER_ETC_RETRANSFER, TIMER_MS, 300, ETC_XiaoAn_retransfer_handler);
    }
    else
    {
        if(g_etcReupgradeCnt++ >25)
        {
            g_etcReupgradeCnt = 0;
            etcMsg_ETCOTA_Failed();
            LOG_ERROR("[ETC_XiaoAn] Reupgrade Times over 25 times, OTA failed");
            return -1;
        }
        Free(g_etcFirmwareDataP);
        g_etcFirmwareDataP = NULL;
        LOG_ERROR("[ETC_XiaoAn] has retransfered over 3 times, reupgrade now!!!!");
        etcOta_setUpgrading(L_FALSE); //重新进行升级
        timer_start(TIMER_ETC_DELAY, TIMER_MS, 100, etcOta_upgardeTimerHandler);
        return 0;
    }
    return 0;
}

static int ETC_XiaoAn_OTACompleteAction(void)
{
    u32 crc = setting.statusConf.etcFirmwareCRC;
    crc = _htonl(crc);
    LOG_DEBUG("[ETC_XiaoAn] Send OTA Complete Action");
    return da14580_sendDATA(ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_END, (u8 *)&crc, sizeof(crc));
}

static int ETC_XiaoAn_SetSoc_rsp(uint8_t *data)
{
    LOG_DEBUG("[ETC_XiaoAn] set etc SOC data successful");
    return 0;
}

static int ETC_XiaoAn_SetSpeed_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    u8 code = msg->data[0];
    if(code)
    {
        LOG_ERROR("set etc speed error");
    }
    return 0;
}

#define MAX_SEND_BMSFAULT_TIMES  1
int ETC_getSocTimeout(void)
{    
    if(timer_isTimerStart(TIMER_SEND_BMSINFO))
    {
        timer_stop(TIMER_SEND_BMSINFO);
    }    
    setting.statusConf.bmsSoc = 0;
    statusConf_save();
    if(++data_getData()->bms.sendSocFaultTimes <= MAX_SEND_BMSFAULT_TIMES)
    {
        detect_sendBmsComFault();
    }
    return 0;
}

static int ETC_XiaoAn_GetSOC_rsp(uint8_t *data)
{
    DATA *pData = data_getData();
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    XIAOAN_ETC_GET_BMSINFO *info = (XIAOAN_ETC_GET_BMSINFO *)msg->data;
    u8 now_SOC = msg->data[0];

    if(msg->length != sizeof(XIAOAN_ETC_GET_BMSINFO))
    {
        LOG_ERROR("data length error");
        return -1;
    }
    
    pData->etc.soc = info->soc;
    pData->etc.soh = info->soh;
    pData->etc.capacity = info->capacity;
    pData->etc.cycle = info->cycle;
    pData->etc.batTemp = info->batTemp;
    pData->etc.bmsFault = info->bmsFault;
    
    LOG_DEBUG("soc: %d", pData->etc.soc);
    LOG_DEBUG("soh: %d", pData->etc.soh);
    LOG_DEBUG("capacity: %d", pData->etc.capacity);
    LOG_DEBUG("cycle: %d", pData->etc.cycle);
    LOG_DEBUG("batTemp: %d", pData->etc.batTemp);
    LOG_DEBUG("bmsFault: %d", pData->etc.bmsFault);

    if(now_SOC != 0xff && now_SOC > 0 && now_SOC <= 100) //1~100为有效值
    {
        if(timer_isTimerStart(TIMER_GETSOC_TIMEOUT))
        {
            timer_stop(TIMER_GETSOC_TIMEOUT);
        }
        data_getData()->bms.getSocTimes = 0; //获取到SOC，清空计数
        data_getData()->bms.sendSocFaultTimes = 0;
        if(setting.statusConf.bmsSoc != now_SOC)
        {            
            if(abs(setting.statusConf.bmsSoc - now_SOC) >= 2)
            {
                data_getData()->socFluct = L_TRUE;
            }
            setting.statusConf.bmsSoc = now_SOC;
            statusConf_save(); //保存BMS电量

            event_checkActiveFreqSOC(); //获取到SOC后则重启主动获取定时器
        }
        LOG_DEBUG("[ETC_XiaoAn] get SOC:%d", now_SOC);
        
        //处于等待获取soc的状态，说明主动开电门未超时前获取到soc，则可以提前关闭电门
        if(data_getData()->socWait == L_TRUE)
        {
            car_unlock();
        }
    }
    else
    {
        if(!timer_isTimerStart(TIMER_GETSOC_TIMEOUT))
        {
            timer_start(TIMER_GETSOC_TIMEOUT, TIMER_S, 10, ETC_getSocTimeout); //持续10秒获取SOC异常，则上报故障并停止上报BMS信息
        }
        LOG_DEBUG("[ETC_XiaoAn] get soc error"); //控制器与BMS通信异常
    }
    return 0;
}

static int isPulseWorkTimeout(void)
{
    data_getData()->etc.isPulseWork = L_FALSE;
	return 0;
}

static int ETC_XiaoAn_GetETCInfo_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    DATA *pData = data_getData();

    if(msg->length == sizeof(XIAOAN_ETC_DATA))
    {
        XIAOAN_ETC_DATA *data_etc = (XIAOAN_ETC_DATA *)msg->data;
        pData->etc.type = data_etc->type;
        pData->etc.voltage_mV = _ntohs(data_etc->voltage_mV) * 100;
        pData->etc.current_mA = _ntohs(data_etc->current_mA) * 100;
        pData->etc.pulse = _ntohs(data_etc->pulse);
        pData->etc.speed = data_etc->speed_per;
        pData->etc.protectVoltage_mV = _ntohs(data_etc->underVoltage_mV) * 100;
        pData->etc.limitCurrent_mA = _ntohs(data_etc->currentLimiting_mA) * 100;
        pData->etc.fault = data_etc->fault;
        pData->etc.timestamp = (u32)rtc_getTimestamp();
        pData->etc.protocolVer = 0;

        data_getData()->etc.isPulseWork = L_TRUE;
        timer_start(TIMER_PULSE_TIMEOUT, TIMER_S, 20, isPulseWorkTimeout);
        
        LOG_DEBUG("type: %d", pData->etc.type);
        LOG_DEBUG("voltage_mV: %d", pData->etc.voltage_mV);
        LOG_DEBUG("current_mA: %d", pData->etc.current_mA);
        LOG_DEBUG("pulse: %d", pData->etc.pulse);
        LOG_DEBUG("speed_per: %d", pData->etc.speed);
        LOG_DEBUG("underVoltage_mV: %d", pData->etc.protectVoltage_mV);
        LOG_DEBUG("currentLimiting_mA: %d", pData->etc.limitCurrent_mA);
        LOG_DEBUG("fault: %d", pData->etc.fault);
    }
    else if(msg->length == sizeof(XIAOAN_ETC_DATA_V3))
    {
        XIAOAN_ETC_DATA_V3 *data_etc = (XIAOAN_ETC_DATA_V3 *)msg->data;
        pData->etc.type = data_etc->type;
        pData->etc.voltage_mV = _ntohs(data_etc->voltage) * 100;
        pData->etc.current_mA = _ntohs(data_etc->current) * 100;
        pData->etc.pulse = _ntohs(data_etc->pulse);
        pData->etc.speed = data_etc->speed;
        pData->etc.fault = data_etc->fault;
        pData->etc.function = data_etc->function;
        pData->etc.protocolVer = data_etc->protocolVer;
        pData->etc.version = data_etc->version;
        pData->etc.manufacturer = data_etc->manufacturer;
        pData->etc.timestamp = (u32)rtc_getTimestamp();

        data_getData()->etc.isPulseWork = L_TRUE;
        timer_start(TIMER_PULSE_TIMEOUT, TIMER_S, 20, isPulseWorkTimeout);

        LOG_DEBUG("type: %d", pData->etc.type);
        LOG_DEBUG("voltage_mV: %d", pData->etc.voltage_mV);
        LOG_DEBUG("current_mA: %d", pData->etc.current_mA);
        LOG_DEBUG("pulse: %d", pData->etc.pulse);
        LOG_DEBUG("speed_per: %d", pData->etc.speed);
        LOG_DEBUG("fault: %d", pData->etc.fault);
        LOG_DEBUG("function: %d", pData->etc.function);
        LOG_DEBUG("protocolVer: %d", pData->etc.protocolVer);
        LOG_DEBUG("version: %d", pData->etc.version);
        LOG_DEBUG("manufacturer: %d", pData->etc.manufacturer);
    }
    else if(msg->length == sizeof(XIAOAN_ETC_DATA_V5))
    {
        XIAOAN_ETC_DATA_V5 *data_etc = (XIAOAN_ETC_DATA_V5 *)msg->data;
        pData->etc.type = data_etc->type;
        pData->etc.voltage_mV = _ntohs(data_etc->voltage) * 100;
        pData->etc.current_mA = _ntohs(data_etc->current) * 100;
        pData->etc.pulse = _ntohs(data_etc->pulse);
        pData->etc.speed = data_etc->speed;
        pData->etc.fault = data_etc->fault;
        pData->etc.function = data_etc->function;
        pData->etc.protocolVer = data_etc->protocolVer;
        pData->etc.version = data_etc->version;
        pData->etc.manufacturer = data_etc->manufacturer;
        pData->etc.ratio = data_etc->ratio;
        pData->etc.timestamp = (u32)rtc_getTimestamp();

        data_getData()->etc.isPulseWork = L_TRUE;
        timer_start(TIMER_PULSE_TIMEOUT, TIMER_S, 20, isPulseWorkTimeout);

        LOG_DEBUG("type: %d", pData->etc.type);
        LOG_DEBUG("voltage_mV: %d", pData->etc.voltage_mV);
        LOG_DEBUG("current_mA: %d", pData->etc.current_mA);
        LOG_DEBUG("pulse: %d", pData->etc.pulse);
        LOG_DEBUG("speed_per: %d", pData->etc.speed);
        LOG_DEBUG("fault: %d", pData->etc.fault);
        LOG_DEBUG("function: %d", pData->etc.function);
        LOG_DEBUG("protocolVer: %d", pData->etc.protocolVer);
        LOG_DEBUG("version: %d", pData->etc.version);
        LOG_DEBUG("manufacturer: %d", pData->etc.manufacturer);
        LOG_DEBUG("ratio: %d", pData->etc.ratio);
    }
    else if(msg->length == sizeof(XIAOAN_ETC_DATA_V6))
    {
        XIAOAN_ETC_DATA_V6 *data_etc = (XIAOAN_ETC_DATA_V6 *)msg->data;
        pData->etc.type = data_etc->type;
        pData->etc.voltage_mV = _ntohs(data_etc->voltage) * 100;
        pData->etc.current_mA = _ntohs(data_etc->current) * 100;
        pData->etc.pulse = _ntohs(data_etc->pulse);
        pData->etc.speed = data_etc->speed;
        pData->etc.fault = _ntohs(data_etc->fault);
        pData->etc.function = data_etc->function;
        pData->etc.protocolVer = data_etc->protocolVer;
        pData->etc.version = data_etc->version;
        pData->etc.manufacturer = data_etc->manufacturer;
        pData->etc.ratio = data_etc->ratio;
        pData->etc.timestamp = (u32)rtc_getTimestamp();

        data_getData()->etc.isPulseWork = L_TRUE;
        timer_start(TIMER_PULSE_TIMEOUT, TIMER_S, 20, isPulseWorkTimeout);

        LOG_DEBUG("type: %d", pData->etc.type);
        LOG_DEBUG("voltage_mV: %d", pData->etc.voltage_mV);
        LOG_DEBUG("current_mA: %d", pData->etc.current_mA);
        LOG_DEBUG("pulse: %d", pData->etc.pulse);
        LOG_DEBUG("speed_per: %d", pData->etc.speed);
        LOG_DEBUG("fault: %d", pData->etc.fault);
        LOG_DEBUG("function: %d", pData->etc.function);
        LOG_DEBUG("protocolVer: %d", pData->etc.protocolVer);
        LOG_DEBUG("version: %d", pData->etc.version);
        LOG_DEBUG("manufacturer: %d", pData->etc.manufacturer);
        LOG_DEBUG("ratio: %d", pData->etc.ratio);
    }
    
    //金丰控制器版本0固件需要设置功能开关为电动模式才能拧巴骑行
    if(ETC_MANUFACTURER_JF == pData->etc.manufacturer && 0 == pData->etc.version)
    {
        setting.settingConf.etcFuncSwitch = 0x04;
        ETC_XiaoAn_SetFuncSwitch();
    }
    return 0;
}

static int ETC_XiaoAn_SetProtectVoltage_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    uint8_t code = msg->data[0];
    if(code)
    {
        LOG_ERROR("set etc Protect Voltage error");
    }
    return 0;
}

static int ETC_XiaoAn_SetLimitCurrent_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    uint8_t code = msg->data[0];
    if(code)
    {
        LOG_ERROR("set etc Limit Current error");
    }
    return 0;
}

static int ETC_XiaoAn_GetETCLastError_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    DATA *pData = data_getData();
    XIAOAN_ETC_LAST_ERROR *pLastError = (XIAOAN_ETC_LAST_ERROR *)msg->data;
    pData->etc.errorCode = _ntohl(pLastError->lastError);
    return 0;
}

static int ETC_XiaoAn_SetIfSlowStart_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    uint8_t code = msg->data[0];
    if(code)
    {
        LOG_ERROR("set etc if slow start error");
    }
    return 0;
}

static int ETC_XiaoAn_SetAccOn_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    uint8_t code = msg->data[0];
    if(code)
    {
        LOG_ERROR("set etc AccOn error");
    }
    return 0;
}

static int ETC_XiaoAn_SetFuncSwitch_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    uint8_t code = msg->data[0];
    if(code)
    {
        LOG_ERROR("set etc Func Switch error");
    }
    return 0;
}

static int ETC_XiaoAn_SetDefend_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    uint8_t code = msg->data[0];
    if(code)
    {
        LOG_ERROR("set etc Defend error");
    }
    return 0;
}

static int ETC_XiaoAn_SetLight_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    uint8_t code = msg->data[0];
    if(code)
    {
        LOG_ERROR("set etc Light error");
    }
    return 0;
}

__attribute__((unused)) static int ETC_XiaoAn_GetETC_rsp(u8 *data)
{
    return 0;
}

static int ETC_XiaoAn_GetStartOTA_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    XIAOAN_ETC_START_OTA_RSP *udata =(XIAOAN_ETC_START_OTA_RSP *)msg->data;

    if(msg->length != 3)
    {
        return -1;
    }
    if(_htons(msg->signature) == 0xAA55)
    {
        if(udata->canUpgrade == 0x00)//返回0表示可以升级
        {
            timer_stop(TIMER_ETC_RETRANSFER);
            g_etcSendDataLenPerTime = _htons(udata->size);
            timer_start(TIMER_ETC_DELAY, TIMER_MS, 500, etcMsg_SendEtcOTARealData);
            LOG_DEBUG("[ETC_XiaoAn] GetStartOTA_Rsp DPT:%d",g_etcSendDataLenPerTime);
        }
    }
    else
    {
        LOG_ERROR("[ETC_XiaoAn] signature error");
        return -1;
    }
    return 0;
}

static int ETC_XiaoAn_GetOTARealData_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    XIAOAN_ETC_pageID *pdata=(XIAOAN_ETC_pageID *)msg->data;

    if(msg->length != 2)
    {
        return -1;
    }
    if(_htons(msg->signature) == 0xAA55)
    {
        timer_stop(TIMER_ETC_RETRANSFER);
        if(pdata->pageID == 0)
        {
            //重新开始升级
            LOG_ERROR("[ETC_XiaoAn] pageID error,restart ETC update");
            Free(g_etcFirmwareDataP);
            g_etcFirmwareDataP = NULL;
            etcOta_setUpgrading(L_FALSE);
            return -1;
        }
        if(!g_etcSendCompleteFlag)
        {
            LOG_DEBUG("[ETC_XiaoAn] continue send data");
            etcMsg_SendEtcOTARealData();
        }
        else
        {
            LOG_DEBUG("[ETC_XiaoAn] OTA data send finish");
            g_etcSendCompleteFlag=0;
            etcMsg_SendEtcOTAComplete();
        }
    }
    else
    {
        return -1;
    }
    return 0;
}


static int ETC_XiaoAn_GetOTAComplete_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;
    XIAOAN_ETC_ISSUCCESS *udata =(XIAOAN_ETC_ISSUCCESS *)msg->data;
    timer_stop(TIMER_ETC_RETRANSFER);

    if(msg->length != 1)
    {
        LOG_DEBUG("[ETC_XiaoAn] OTA resp Length Invalid");
        return -1;
    }
    if(udata->isRevSuccess == 0)//控制接受数据成功
    {
        LOG_DEBUG("[ETC_XiaoAn]  ETC UPGRADE FINISH!! ");
        da14580_setHeartbeat(L_TRUE); //OTA升级完成后，打开蓝牙心跳
        etcOta_setUpgrading(L_FALSE);
        car_accOff();
        setting.statusConf.etcUpgradeFlag = 0;
        data_getData()->etc.version = setting.statusConf.etcUpgradeVersion;//升级成功了 记录新的控制器版本
        setting.statusConf.etcVersion = setting.statusConf.etcUpgradeVersion;
        statusConf_save();
        fs_deleteFile(UPGRADE_ETC_FILE_NAME);
        timer_stop(TIMER_ETC_UPGRADE);
        timer_stop(TIMER_ETC_RETRANSFER);
        timer_stop(TIMER_ETC_DELAY);
        Free(g_etcFirmwareDataP);
        g_etcFirmwareDataP = NULL;
    }
    else
    {
        //重新开始升级
        Free(g_etcFirmwareDataP);
        g_etcFirmwareDataP = NULL;
        etcOta_setUpgrading(L_FALSE);
    }
    g_etcResendCommpleteDataCnt = 0;
    return 0;
}

__attribute__((unused)) static void ETC_XiaoAn_GetETCLastError(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_LASTERROR, ETC_XiaoAn_GetETCInfoAction, ETC_XiaoAn_GetETCLastError_rsp, NULL);
}

static void ETC_XiaoAn_SetSpeed(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_SPEED, ETC_XiaoAn_SetSpeedAction, ETC_XiaoAn_SetSpeed_rsp, NULL);
}

static void ETC_XiaoAn_SetProtectVoltage(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_PROTECTION_VOLTAGE, ETC_XiaoAn_SetProtectVoltageAction, ETC_XiaoAn_SetProtectVoltage_rsp, NULL);
}

static void ETC_XiaoAn_SetLimitCurrent(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_LIMIT_CURRENT, ETC_XiaoAn_SetLimitCurrentAction, ETC_XiaoAn_SetLimitCurrent_rsp, NULL);
}

static void ETC_XiaoAn_SetFuncSwitch(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_FUNC, ETC_XiaoAn_SetFuncSwitchAction, ETC_XiaoAn_SetFuncSwitch_rsp, NULL);
}

static void ETC_XiaoAn_SetIfSlowStart(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_SLOWSTART, ETC_XiaoAn_SetIfSlowStartAction, ETC_XiaoAn_SetIfSlowStart_rsp, NULL);
}

void ETC_XiaoAn_GetETCInfo(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_INFO, ETC_XiaoAn_GetETCInfoAction, ETC_XiaoAn_GetETCInfo_rsp, NULL);
}

void ETC_XiaoAn_GetSOC(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_SOC, ETC_XiaoAn_GetSOCAction, ETC_XiaoAn_GetSOC_rsp, NULL);
}

void ETC_XiaoAn_SetETCAccOn(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_ACC, ETC_XiaoAn_SetAccOnAction, ETC_XiaoAn_SetAccOn_rsp, NULL);
    if(L_FALSE == setting.settingConf.isDefaultSpeed)
    {
        ETC_XiaoAn_SetSpeed();
    }

    if(setting.settingConf.etcIsSlowStart != ETC_DEFAULT_ISSLOWSTART)
    {
        ETC_XiaoAn_SetIfSlowStart();
    }

    if(setting.settingConf.etcFuncSwitch != ETC_DEFAULT_FUNCSWITCH)
    {
        ETC_XiaoAn_SetFuncSwitch();
    }

    if(setting.settingConf.etcLimitCurrent_100mA != ETC_DEFAULT_LIMITCURRENT)
    {
        ETC_XiaoAn_SetLimitCurrent();
    }

    if(setting.settingConf.etcProtectVoltage_100mV != ETC_DEFAUTL_PROTECTVOLTAGE)
    {
        ETC_XiaoAn_SetProtectVoltage();
    }
}

void ETC_XiaoAn_SetETCAccOnOnce(void)
{
    etcMsg_setETCHandlerOnce(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_ACC, ETC_XiaoAn_SetAccOnAction, ETC_XiaoAn_SetAccOn_rsp, NULL);
}

void ETC_XiaoAn_SetETCDefend(u8 isDefend)
{
    g_isDefend = isDefend;
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_DEFEND, ETC_XiaoAn_SetDefendAction, ETC_XiaoAn_SetDefend_rsp, NULL);
}

void ETC_XiaoAn_SetETCDefendOnce(u8 isDefend)
{
    g_isDefend = isDefend;
    etcMsg_setETCHandlerOnce(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_DEFEND, ETC_XiaoAn_SetDefendAction, ETC_XiaoAn_SetDefend_rsp, NULL);
}

void ETC_XiaoAn_SetLight(u8 state)
{
    g_light = state;
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_LIGHT, ETC_XiaoAn_SetLightAction, ETC_XiaoAn_SetLight_rsp, NULL);
}
void ETC_XiaoAn_SetBMSSoc(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_BMS_SOC, ETC_XiaoAn_SetSocAction, ETC_XiaoAn_SetSoc_rsp, NULL);
}

void ETC_XiaoAn_OTAStart(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_START, ETC_XiaoAn_StartOTAAction, ETC_XiaoAn_GetStartOTA_rsp, NULL);
}

void ETC_XiaoAn_OTARealData(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS,XIAOAN_SET_ETC_UPGRADE_DATA, ETC_XiaoAn_OTARealDataAction, ETC_XiaoAn_GetOTARealData_rsp, NULL);
}
void ETC_XiaoAn_OTAComplete(void)
{
    etcMsg_setETCHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_END, ETC_XiaoAn_OTACompleteAction, ETC_XiaoAn_GetOTAComplete_rsp, NULL);
}

void ETC_XiaoAn_Initial(void)
{
    //占坑CMD和address 设置需要超时重发
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_START, NULL, ETC_XiaoAn_GetStartOTA_rsp, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_DATA, NULL, ETC_XiaoAn_GetOTARealData_rsp, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_UPGRADE_END, NULL, ETC_XiaoAn_GetOTAComplete_rsp, NULL, L_TRUE);

    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_LASTERROR, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_INFO, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_SPEED, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_PROTECTION_VOLTAGE, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_LIMIT_CURRENT, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_SLOWSTART, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_LIGHT, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_ACC, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_FUNC, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_DEFEND, NULL, NULL, NULL, L_TRUE);

    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_BOOST_RATIO, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_BMS_SOC, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_EVENT_INFO, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_SYNC_TIME, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_STATE_INFO, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_SET_ETC_CTRL_EVENT, NULL, NULL, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_ETC_ADDRESS, XIAOAN_GET_ETC_SOC, NULL, NULL, NULL, L_FALSE);
}

static void *ETC_XiaoAn_allocMsg(u8 address, u8 cmd, u8 *data, u8 dataLen)
{
    MSG_HEADER_XIAOAN_ETC *msg = Malloc(MSG_HEADER_XIAOAN_ETC_LEN + dataLen + 1);
    if(msg)
    {
        uint8_t i = 0;
        msg->signature = _htons(START_FLAG);
        msg->address = address;
        msg->cmd = cmd;
        msg->length = dataLen;

        memcpy(msg->data, data, dataLen);
        msg->data[dataLen] = (uint8_t)(address + cmd + dataLen);
        for(i = 0; i < dataLen; i++)
        {
            msg->data[dataLen] += data[i];
        }
    }

    return msg;
}

//检查校验和
L_BOOL ETC_XiaoAn_IsCheckSumPass(MSG_HEADER_XIAOAN_ETC *msg)
{
    u8 i = 0;
    u8 checksum = msg->address + msg->cmd + msg->length;
    for(i = 0; i < msg->length; i++)
    {
        checksum += msg->data[i];
    }

    if(checksum == msg->data[msg->length])
    {
        return L_TRUE;
    }

    return L_FALSE;
}

static int ETC_XiaoAn_procOneMsg(u8 *data, u8 dataLen)
{
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;

    if(msg->address == BLE_ADDRESS)
    {
        return bleMsg_msgProc(data, dataLen);
    }
    else if(msg->address == BIO_ADDRESS) //蓝牙内部协议为私有,单独拎开
    {
        return bioMsg_msgProc(data, dataLen);
    }
    else if (msg->address == ETC_ADDRESS)
    {
        LOG_INFO("[ETC] receive XiaoAn etc message:");
        LOG_BIN((const char *)data, dataLen);
        data_getData()->faultRecord.isEtcRsp = L_TRUE;//收到控制器回复
        data_getData()->faultRecord.EtcComm = L_TRUE;
        data_getData()->faultRecord.etcSendNoRspTimes = 0;
        return etcMsg_MsgProc(data, dataLen);
    }
    else if (msg->address == BMS_ADDRESS)
    {
        LOG_INFO("[ETC] receive XiaoAn bms message:");
        LOG_BIN((const char *)data, dataLen);
        data_getData()->faultRecord.isBmsRsp = L_TRUE; //收到BMS回复，发送通讯恢复告警
        data_getData()->faultRecord.BmsComm = L_TRUE;
        data_getData()->faultRecord.bmsSendNoRspTimes = 0;
        return etcMsg_MsgProc(data, dataLen);
    }
    else if(msg->address == CHECK_ADDRESS)
    {
        return diag_diagMsgProc(data, dataLen);
    }

    return -1;
}

L_BOOL XiaoAn_FilterFrame(u8 * data, u16 length)
{
    u8 vaild = 0;
    u8 proctimes = 0;
    s16 leftlen = length;
    MSG_HEADER_XIAOAN_ETC *msg = (MSG_HEADER_XIAOAN_ETC *)data;

    while(leftlen >= MSG_HEADER_XIAOAN_ETC_LEN)
    {
        if(START_FLAG != _ntohs(msg->signature))
        {
            int i = 0;
            u8 *pMsg = (u8 *)msg;

            //去掉485硬件产生的0x00的接收数据
            for(; i < leftlen - 1; i++)
            {
                if(pMsg[i] == 0xAA && pMsg[i + 1] == 0x55)
                {
                    break;
                }
            }

            if(i >= leftlen - 1 && leftlen > 1)
            {
                //没有匹配到的数据
                break;
            }
            else
            {
                //匹配到数据了
                leftlen -= i;
                msg = (MSG_HEADER_XIAOAN_ETC*)(pMsg + i);
            }

        }

        if(!ETC_XiaoAn_IsCheckSumPass(msg)) //如果数据包校验错误，则认为整个接收数据都不可信，可以直接丢弃
        {
            break;
        }
        vaild = 1;
        ETC_XiaoAn_procOneMsg((u8 *)msg, msg->length + MSG_HEADER_XIAOAN_ETC_LEN + 1);
        leftlen = leftlen - (msg->length + MSG_HEADER_XIAOAN_ETC_LEN + 1);
        msg = (MSG_HEADER_XIAOAN_ETC *)(data + length - leftlen);
        if(++proctimes > 10)
        {
            LOG_ERROR("[etc] procOneMsg break");
            return L_FALSE;
        }
    }
    if(vaild == 1)
    {
        return L_TRUE;
    }
    return L_FALSE;
}

static int ETC_XiaoAn_sendDATA(u8 address, u8 cmd, u8 *data, u8 dataLen)
{
    uint8_t *send_data = (uint8_t *)ETC_XiaoAn_allocMsg(address, cmd, data, dataLen);
    if(send_data)
    {
        da14580_sendUartData(send_data, MSG_HEADER_XIAOAN_ETC_LEN + dataLen + 1);
        free_msg((void *)send_data);
        return 0;
    }
    return -1;
}

