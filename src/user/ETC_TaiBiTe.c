#include <string.h>
#include "log.h"
#include "data.h"
#include "msg.h"
#include "da14580.h"
#include "etcMsg.h"
#include "event.h"
#include "ETC_TaiBiTe.h"
#include "ETC_XiaoAn.h"
#include "user_timer.h"

static int ETC_TaiBiTe_sendDATA(u8 address, u8 cmd, u8 *data, u8 dataLen);
static void *ETC_TaiBiTe_allocMsg(u8 address, u8 cmd, u8 *data, u8 dataLen);

static int ETC_TaiBiTe_GetBatteryTemp_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    float temperature = 0;
    u16 temp = 0;

    temp = (u16)msg->data[msg->length - 2] << 8 | msg->data[msg->length - 1];
    temp = temp - 2731;
    temperature = temp / 10;
    data_getData()->bms.temperature = temperature;
    LOG_DEBUG("Battery temperature is %f", temperature);

    return 0;
}

static int ETC_TaiBiTe_GetBatteryVoltage_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u16 voltage = 0;
    voltage = (u16)msg->data[msg->length - 2] << 8 | msg->data[msg->length - 1];
    data_getData()->bms.voltage = voltage;
    LOG_DEBUG("Battery voltage is %d", voltage);
    return 0;
}

static int ETC_TaiBiTe_GetBatteryCurrent_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u16 current = 0;
    current = (u16)msg->data[5] << 8 | msg->data[6];
    data_getData()->bms.current = current;
    LOG_DEBUG("Battery current is %d", current);
    return 0;
}

static int ETC_TaiBiTe_GetBatteryRelaCap_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u8 relaCap = 0;
    relaCap = msg->data[4];
    data_getData()->bms.relativeCapity = relaCap;
    LOG_DEBUG("Battery relative capity is %d%%", relaCap);
    return 0;
}

static int ETC_TaiBiTe_GetBatteryAbsCap_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u8 absCap = 0;
    absCap = msg->data[9];
    data_getData()->bms.absoluteCapity = absCap;
    LOG_DEBUG("Battery absolute capity is %d%%", absCap);
    return 0;
}
static int ETC_TaiBiTe_GetBatteryRemainCap_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u16 remainCap = 0;
    remainCap = (u16)msg->data[7] << 8 | msg->data[8];
    data_getData()->bms.remainCapacity = remainCap;
    LOG_DEBUG("Battery remainCap capity is %d mAh", remainCap);
    return 0;
}
static int ETC_TaiBiTe_GetBatteryCapity_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u16 capity = 0;
    capity = (u16)msg->data[msg->length - 2] << 8 | msg->data[msg->length - 1];
    data_getData()->bms.capacity = capity;
    LOG_DEBUG("Battery capity is %d", capity);
    return 0;
}
static int ETC_TaiBiTe_GetBatteryRecycleTimes_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u16 recycleTimes = 0;
    recycleTimes = (u16)msg->data[msg->length - 2] << 8 | msg->data[msg->length - 1];
    data_getData()->bms.cycleCount = recycleTimes;
    LOG_DEBUG("Battery recycle Times is %d", recycleTimes);
    return 0;
}

static int ETC_TaiBiTe_GetBatteryVoltBefore_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    int i=0;
    u16 voltage[7];
    for(; i < 7; i++)
    {
        voltage[i] =  (u16)msg->data[9 + i*2] << 8 | msg->data[10 + i*2];
        //data_getData()->bms.beforeVoltage[i] = voltage[i];
        LOG_DEBUG("the %d Battery's voltage is:%d", i+1, voltage[i]);
    }
    return 0;
}
static int ETC_TaiBiTe_GetBatteryVoltAfter_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    int i=0;
    u16 voltage[7];
    for(; i < 7; i++)
    {
        voltage[i] =  (u16)msg->data[9 + i*2] << 8 | msg->data[10 + i*2];
        //data_getData()->etc_bms_state.beforeVoltage[i] = voltage[i];
        LOG_DEBUG("the %d Battery's voltage is:%d", i+8, voltage[i]);
    }
    return 0;
}

static int ETC_TaiBiTe_GetBatteryChargeTime_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u16 chargeTime = 0;
    chargeTime = (u16)msg->data[msg->length - 2] << 8 | msg->data[msg->length - 1];
    //data_getData()->bms.chargeIntervalTime = chargeTime;
    LOG_DEBUG("Current charge interval time is %d", chargeTime);
    return 0;
}

static int ETC_TaiBiTe_GetBatteryMaxChargeTime_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u16 maxChargeTime = 0;
    maxChargeTime = (u16)msg->data[msg->length - 2] << 8 | msg->data[msg->length - 1];
    //data_getData()->bms.maxChargeIntervalTime = maxChargeTime;
    LOG_DEBUG("Max charge interval time is %d", maxChargeTime);
    return 0;
}

static int ETC_TaiBiTe_GetRWBarcode_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    int i=0;
    u16 barcode[16];
    for(; i < 16; i++)
    {
        barcode[i] = msg->data[9+i];
        data_getData()->bms.SN[i] = barcode[i];
    }

    //打印条码号
    return 0;
}

static int ETC_TaiBiTe_GetReadVersion_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    u8 softwareVerion, hardwareVersion;
    softwareVerion = msg->data[9];
    hardwareVersion = msg->data[10];
    data_getData()->bms.softwareVer = softwareVerion;
    data_getData()->bms.hardwareVer = hardwareVersion;
    LOG_DEBUG("softwareVerion : %d   hardwareVersion : %d",softwareVerion,hardwareVersion);
    return 0;
}

static int ETC_TaiBiTe_GetReadFactoryName_rsp(u8 *data)
{
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    int i=0;
    u16 factoryName[16];
    for(; i < 16; i++)
    {
        factoryName[i] = msg->data[9+i];
        data_getData()->bms.manufacturer[i] = factoryName[i];
    }
    //打印电池组制造厂名称
    return 0;
}

static int ETC_TaiBiTe_GetETC_rsp(u8 *data)
{
    //在消息分发时已经解析过
    return 0;
}

static u8 g_isDefend = 0;
static ETC_CTRL g_etcCtrl = {0};
static int ETC_TaiBiTe_reFreshCtrlData(void)
{
    g_etcCtrl.accOff = (~setting.statusConf.acc);
    g_etcCtrl.lock = setting.statusConf.isDefend;
    g_etcCtrl.reserve = 0;
    if(setting.defaultConf.etcSpeed <= 100 && setting.defaultConf.etcSpeed >= 70 && setting.defaultConf.etcSpeed % 5 == 0)
    {
        g_etcCtrl.etcspeed = (setting.defaultConf.etcSpeed - 70) / 5  + 1;//此公式是按照协议推算出来的
    }
    else
    {
        g_etcCtrl.etcspeed = 7;//如果限速值设置不正确，则将限速值设为100%
    }
    g_etcCtrl.mode = 2;
    return 0;
}

static int ETC_TaiBiTe_GetBatteryTempAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_TEMP, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryValtageAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryCurrentAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CURRENT, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryRelaCapAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_RELA_CAP, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryAbsCapAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_ABS_CAP, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryRemainCapAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_REMAIN_CAP, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryCapAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CAP, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryRecycleTimeAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_RECYCLE_TIME, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryVoltBeforeAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT_BEFORE, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryVoltAfterAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT_AFTER, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryChargeTimeAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CHARGE_TIME, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryMaxChargeTimeAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_MAX_CHARGE_TIME, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryRWBarcodeAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_RW_BARCODE, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryReadVersionAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_READ_VERSION, data, 2);//
}

static int ETC_TaiBiTe_GetBatteryReadFactoryNameAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);
    return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_READ_FACTORY_NAME, data, 2);//
}

static int ETC_TaiBiTe_sendDATA_ctrl(u8 *data, int len)
{
    if(setting.defaultConf.ccuType == TYPE_TAIBITE || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC) //老版本需要0x08和0x66一起发
    {
        ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_TEMP, data, len);//协议兼容处理
        return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, data, len);
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE_NEW) //只发0x66
    {
        return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, data, len);
    }
    else if(setting.defaultConf.ccuType == TYPE_TAIBITE_09) //只发0x09
    {
        return ETC_TaiBiTe_sendDATA(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT, data, len);
    }
    return -1;
}

static int ETC_TaiBiTe_SetETCSpeedAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);

    return ETC_TaiBiTe_sendDATA_ctrl(data, 2);
}

static int ETC_TaiBiTe_GetETCInfoAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    if(!setting_isDefendOn())
    {
        g_etcCtrl.accOff = 0;
        g_etcCtrl.lock = 0;
    }
    if(setting.settingConf.isEtcSOC)
    {
        data_getData()->bms.getSocTimes++;
    }
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);

    return ETC_TaiBiTe_sendDATA_ctrl(data, 2);
}

static int ETC_TaiBiTe_SetETCDefendAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    g_etcCtrl.lock = g_isDefend;

    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);

    return ETC_TaiBiTe_sendDATA_ctrl(data, 2);
}

static int ETC_TaiBiTe_SetETCAccOnAction(void)
{
    u8 data[2];
    ETC_TaiBiTe_reFreshCtrlData();
    g_etcCtrl.accOff = 0;
    g_etcCtrl.lock = 0;
    memcpy(&data[0], &g_etcCtrl, 1);
    memcpy(&data[1], &data_getData()->bms.SOC, 1);

    return ETC_TaiBiTe_sendDATA_ctrl(data, 2);
}

__attribute__((unused))static void ETC_TaiBiTe_SetETCSpeed(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, ETC_TaiBiTe_SetETCSpeedAction, ETC_TaiBiTe_GetETC_rsp, NULL);
}

void ETC_TaiBiTe_GetETCInfo(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, ETC_TaiBiTe_GetETCInfoAction, ETC_TaiBiTe_GetETC_rsp, NULL);
}

void ETC_TaiBiTe_SetETCDefend(u8 isDefend)
{
    g_isDefend = isDefend;
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, ETC_TaiBiTe_SetETCDefendAction, ETC_TaiBiTe_GetETC_rsp, NULL);
}

void ETC_TaiBiTe_SetETCDefendOnce(u8 isDefend)
{
    g_isDefend = isDefend;
    etcMsg_setETCHandlerOnce(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, ETC_TaiBiTe_SetETCDefendAction, ETC_TaiBiTe_GetETC_rsp, NULL);
}

void ETC_TaiBiTe_SetETCAccOn(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, ETC_TaiBiTe_SetETCAccOnAction, ETC_TaiBiTe_GetETC_rsp, NULL);
}

void ETC_TaiBiTe_SetETCAccOnOnce(void)
{
    etcMsg_setETCHandlerOnce(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, ETC_TaiBiTe_SetETCAccOnAction, ETC_TaiBiTe_GetETC_rsp, NULL);
}

void ETC_TaiBiTe_GetBatteryTemp(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_TEMP, ETC_TaiBiTe_GetBatteryTempAction, ETC_TaiBiTe_GetBatteryTemp_rsp, NULL);
}

void ETC_TaiBiTe_GetBatteryVoltage(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT, ETC_TaiBiTe_GetBatteryValtageAction, ETC_TaiBiTe_GetBatteryVoltage_rsp, NULL);
}

void ETC_TaiBiTe_GetBatteryCurrent(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CURRENT, ETC_TaiBiTe_GetBatteryCurrentAction, ETC_TaiBiTe_GetBatteryCurrent_rsp, NULL);
}

void ETC_TaiBiTe_GetBatteryRelaCap(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_RELA_CAP, ETC_TaiBiTe_GetBatteryRelaCapAction, ETC_TaiBiTe_GetBatteryRelaCap_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryAbsCap(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_ABS_CAP, ETC_TaiBiTe_GetBatteryAbsCapAction, ETC_TaiBiTe_GetBatteryAbsCap_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryRemainCap(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_REMAIN_CAP, ETC_TaiBiTe_GetBatteryRemainCapAction, ETC_TaiBiTe_GetBatteryRemainCap_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryCap(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CAP, ETC_TaiBiTe_GetBatteryCapAction, ETC_TaiBiTe_GetBatteryCapity_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryRecycleTimes(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_RECYCLE_TIME, ETC_TaiBiTe_GetBatteryRecycleTimeAction, ETC_TaiBiTe_GetBatteryRecycleTimes_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryVoltBefore(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT_BEFORE, ETC_TaiBiTe_GetBatteryVoltBeforeAction, ETC_TaiBiTe_GetBatteryVoltBefore_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryVoltAfter(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT_AFTER, ETC_TaiBiTe_GetBatteryVoltAfterAction, ETC_TaiBiTe_GetBatteryVoltAfter_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryChargeTime(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CHARGE_TIME, ETC_TaiBiTe_GetBatteryChargeTimeAction, ETC_TaiBiTe_GetBatteryChargeTime_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryMaxChargeTime(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_MAX_CHARGE_TIME, ETC_TaiBiTe_GetBatteryMaxChargeTimeAction, ETC_TaiBiTe_GetBatteryMaxChargeTime_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryRW_Barcode(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_RW_BARCODE, ETC_TaiBiTe_GetBatteryRWBarcodeAction, ETC_TaiBiTe_GetRWBarcode_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryReadVersion(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_READ_VERSION, ETC_TaiBiTe_GetBatteryReadVersionAction, ETC_TaiBiTe_GetReadVersion_rsp, NULL);
}
void ETC_TaiBiTe_GetBatteryReadFactoryName(void)
{
    etcMsg_setETCHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_READ_FACTORY_NAME, ETC_TaiBiTe_GetBatteryReadFactoryNameAction, ETC_TaiBiTe_GetReadFactoryName_rsp, NULL);
}

typedef void (*TAIBITE_CTRL_LOOP_PROC)(void);

void ETC_TaiBiTe_Initial(void)
{
    //协议发送按顺序占位置
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_TEMP, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CURRENT, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_RELA_CAP, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_ABS_CAP, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_REMAIN_CAP, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CAP, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_RECYCLE_TIME, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT_BEFORE, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_VOLT_AFTER, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_CHARGE_TIME, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_BATT_MAX_CHARGE_TIME, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_RW_BARCODE, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_READ_VERSION, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_GET_READ_FACTORY_NAME, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(TAIBITE_ETC_ADDRESS, TAIBITE_CMD_SET, NULL, NULL, NULL, L_FALSE);
}

static void *ETC_TaiBiTe_allocMsg(u8 address, u8 cmd, u8 *data, u8 dataLen)
{
    MSG_HEADER_TAIBITE *msg = Malloc(MSG_HEADER_TAIBITE_LEN + dataLen + 4);
    u16 checksum = 0;
    if (msg)
    {
        u8 i = 0;
        if(0x2a == address)//泰比特协议ETC地址
        {
            msg->head = 0x4F;
        }
        else if(0x16 == address)//泰比特协议BMS地址
        {
            msg->head = 0x3A;
        }

        msg->address = address;
        msg->cmd = cmd;

        if(dataLen == 0 || data == NULL)
        {
            msg->length = 0;
            msg->data[dataLen] = (u8)(address + cmd + dataLen);
            return msg;
        }

        msg->length = dataLen;

        memcpy(msg->data, data, dataLen);

        checksum = address + cmd + dataLen;
        //msg->data[dataLen] = (u8)(address + cmd + dataLen);
        for(i = 0; i < dataLen; i++)
        {
            checksum += data[i];
        }

        msg->data[dataLen] = (u8)checksum;
        msg->data[dataLen + 1] = (u8)(checksum >> 8);
        msg->data[dataLen + 2] = 0x0D;
        msg->data[dataLen + 3] = 0x0A;
    }

    return msg;
}

//检查校验和
L_BOOL ETC_TaiBiTe_IsCheckSumPass(MSG_HEADER_TAIBITE *msg)
{
    u8 i = 0;
    u16 checksum = msg->address + msg->cmd + msg->length;
    for(i = 0; i < msg->length; i++)
    {
        checksum += msg->data[i];
    }

    if(checksum == (u16)((msg->data[msg->length + 1] << 8) | msg->data[msg->length]))
    {
        return L_TRUE;
    }

    return L_FALSE;
}

static int ETC_TaiBiTe_ProcOneMsg(u8* data, u16 dataLen)
{
    LOG_INFO("[ETC] receive Taibite etc message:");
    LOG_BIN((const char *)data, dataLen);
    data_getData()->faultRecord.etcSendNoRspTimes = 0;
    data_getData()->faultRecord.isEtcRsp = L_TRUE; //收到ETC回复，发送通讯恢复告警
    data_getData()->faultRecord.EtcComm = L_TRUE;
    etcMsg_MsgProc(data, dataLen);
    return 0;
}

static int isPulseWorkTimeout(void)
{
    data_getData()->etc.isPulseWork = L_FALSE;
    return 0;
}

static u8 g_socBakWindow[SOC_WINDOW_SIZE] = {0};
static u8 g_socBakPoint = 0; //窗口轮询指针
static u8 g_socBakMain = 0; //窗口数据众数

int ETC_TaiBiTe_resetSocWindow(void)
{
    //换电后清空soc窗口，方便数值立刻刷新
    memset(g_socBakWindow, 0, SOC_WINDOW_SIZE);
    g_socBakPoint = 0;
    g_socBakMain = 0;
    return 0;
}

u8 *ETC_TaiBiTe_getSocWindow(void)
{
    return g_socBakWindow;
}

u8 ETC_TaiBiTe_getSocPoint(void)
{
    return g_socBakPoint;
}

L_BOOL ETC_TaiBiTe_FilterFrame(u8 *data, u16 length)
{
    u8 vaild = 0;
    u8 etcSoc = 0;
    u8 *pData = data;
    s16 leftlen = length;
    MSG_HEADER_TAIBITE *msg = (MSG_HEADER_TAIBITE *)data;
    TAIBITE_ETC_GENERAL_INFO *etcInfo = (TAIBITE_ETC_GENERAL_INFO *)msg->data;

    while(leftlen >= sizeof(MSG_HEADER_TAIBITE))
    {
        int i = 0;
		static u16 last_SOC = 0;
        for(i = 0; i < leftlen; i++)
        {
            if(pData[i] == 0x4F && pData[i + 1] == 0x2A)
            {
                break;
            }
        }

        if(i >= leftlen - 1 && leftlen > 1) //未找到消息头
        {
            break;
        }

        leftlen -= i;
        msg = (MSG_HEADER_TAIBITE*)(pData + i);

        //检查校验和
        if(!ETC_TaiBiTe_IsCheckSumPass(msg))
        {
            break;
        }
        etcInfo = (TAIBITE_ETC_GENERAL_INFO *)msg->data;

        LOG_INFO("etcGeneralInfo_siez = %d, songguoMsg->length = %d\n", sizeof(TAIBITE_ETC_GENERAL_INFO), msg->length);

        vaild = 1;
        data_getData()->etc.pulse = _ntohs(etcInfo->hallNumber);
        data_getData()->etc.fault = etcInfo->etcErrorState;
        data_getData()->etc.speed = HALL2SPEED(data_getData()->etc.pulse);
        data_getData()->etc.isPulseWork = L_TRUE;
        timer_start(TIMER_PULSE_TIMEOUT, TIMER_S, 20, isPulseWorkTimeout);

        if(etcInfo->soc)
        {
            etcSoc = etcInfo->soc; //优先填入data9
        }
        else if(etcInfo->socData5)
        {
            etcSoc = etcInfo->socData5; //其次填入data5
        }

        LOG_INFO("etc fault:0X%X", data_getData()->etc.fault);
        LOG_INFO("etc ModeRsp:0X%X", etcInfo->etcModeRsp);
        LOG_INFO("etc pulse:0X%X", data_getData()->etc.pulse);
		LOG_INFO("etc relative soc is %d%%", etcSoc);

        if(setting.defaultConf.ccuType == TYPE_TAIBITE_SOC)
        {
            int j = 0, k = 0;
            int max = 0, maxLoc = 0;
            u8 times[SOC_WINDOW_SIZE] = {0};

            g_socBakWindow[g_socBakPoint] = etcSoc; //将当前数值放入统计窗口

            g_socBakPoint++; //指针偏移
            if(g_socBakPoint >= SOC_WINDOW_SIZE)
            {
                g_socBakPoint = 0;
            }

            for(j = 0; j < SOC_WINDOW_SIZE; j++) //统计众数
            {
                for(k = 0; k < SOC_WINDOW_SIZE; k++)
                {
                    if(g_socBakWindow[j] == 0)
                    {
                        break; //0不参与众数统计
                    }
                    if(g_socBakWindow[j] == g_socBakWindow[k] && j > k)
                    {
                        break; //说明目前数值已经统计过
                    }
                    else if(g_socBakWindow[j] == g_socBakWindow[k] && j <= k)
                    {
                        times[j]++; //统计该数值有多少相同值
                    }
                }
            }
            for(j = 0; j < SOC_WINDOW_SIZE; j++)
            {
                if(times[j] > max)
                {
                    max = times[j]; //找到最大的相同值
                    maxLoc = j; //标记众数位置
                }
            }
            g_socBakMain = g_socBakWindow[maxLoc]; //将窗口中众数当做当前soc
            etcSoc = g_socBakMain;

            if(!car_isPowerExistence()) //大电不在位则直接将soc强置为0，避免大电拔掉之后控制器给错误soc
            {
                etcSoc = 0;
            }
        }
		
        if(etcSoc < 1 || etcSoc > 100) //1~100为有效值
        {
            if(!timer_isTimerStart(TIMER_GETSOC_TIMEOUT))
            {
                timer_start(TIMER_GETSOC_TIMEOUT, TIMER_S, 10, ETC_getSocTimeout); //持续10秒获取SOC异常，则上报故障并停止上报BMS信息
            }
        }
        else
        {
            if(timer_isTimerStart(TIMER_GETSOC_TIMEOUT))
            {
                timer_stop(TIMER_GETSOC_TIMEOUT);
            }
            data_getData()->bms.getSocTimes = 0; //获取到SOC，清空计数
            data_getData()->bms.sendSocFaultTimes = 0;
            if(setting.statusConf.bmsSoc != etcSoc)
            {          
                if(abs(setting.statusConf.bmsSoc - etcSoc) >= 2)
                {
                    data_getData()->socFluct = L_TRUE;
                }
                setting.statusConf.bmsSoc = etcSoc;
                statusConf_save(); //保存BMS电量

                event_checkActiveFreqSOC(); //获取到SOC后则重启主动获取定时器
            }
            //处于等待获取soc的状态，说明主动开电门未超时前获取到soc，则可以提前关闭电门
            if(data_getData()->socWait == L_TRUE)
            {
                car_unlock();
            }
        }

        ETC_TaiBiTe_ProcOneMsg((u8 *)msg, msg->length + MSG_HEADER_TAIBITE_LEN + 4);// checksum

        if(leftlen < (msg->length + MSG_HEADER_TAIBITE_LEN + 4))break; //避免长度溢出
        leftlen = leftlen - (msg->length + MSG_HEADER_TAIBITE_LEN + 4);
        pData = data + (length - leftlen);
    }
    if(vaild == 1)
    {
        return L_TRUE;
    }
    return L_FALSE;
}

static int ETC_TaiBiTe_sendDATA(u8 address, u8 cmd, u8 *data, u8 dataLen)
{
    u8 *send_data = (u8 *)ETC_TaiBiTe_allocMsg(address, cmd, data, dataLen);
    if(send_data)
    {
        da14580_sendUartData(send_data, MSG_HEADER_TAIBITE_LEN + dataLen + 4);
        free_msg((void*)send_data);
        return 0;
    }
    return -1;
}

