/*
 * BMS_XiaoAn.c
 *
 *  Created on: 2020/06/16
 *      Author: ltx
 */

#include <string.h>
#include <stdlib.h>
#include "log.h"
#include "data.h"
#include "msg.h"
#include "da14580.h"
#include "setting.h"
#include "rtc.h"
#include "car.h"
#include "etcMsg.h"
#include "bms_ota.h"
#include "user_fs.h"
#include "bioMsg.h"
#include "user_timer.h"
#include "BMS_XiaoAn.h"
#include "ETC_XiaoAn.h" //GetReTimeInfo查询完后,要去立即设置ETC,所以此处关联

static int BMS_XiaoAn_retransfer_handler(void);
static int BMS_XiaoAn_sendDATA(u8 address, u8 cmd, u8 *data, u8 dataLen);

__attribute__((unused)) static int BMS_XiaoAn_GetLastErrorAction(void)//获取最后一次错误码
{
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_GET_LASTERROR, NULL, 0);
}

__attribute__((unused)) static int BMS_XiaoAn_SetHeartAction(void)//发送一次心跳
{
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_HEART, NULL, 0);
}

__attribute__((unused)) static int BMS_XiaoAn_SetFuncAction(void)//设置功能开关
{
    u8 funcSwitch = data_getData()->bms.funcSwitch;
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_FUNC, &funcSwitch, 1);
}

__attribute__((unused)) static int BMS_XiaoAn_SetElecSwitchAction(void)//设置放电开关
{
    u8 elecSwitch = data_getData()->bms.elecSwitch;
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_OUT_ELEC_SWITCH, &elecSwitch, 1);
}

__attribute__((unused)) static int BMS_XiaoAn_SetStoreModeAction(void)//设置存储模式
{
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_STORE_MODE, NULL, 0);
}

__attribute__((unused)) static int BMS_XiaoAn_SetInputMosAction(void)//设置充电MOS控制
{
    u8 inputMosSwitch = data_getData()->bms.inputMosSwitch;
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_INPUT_MOS, &inputMosSwitch, 1);
}

__attribute__((unused)) static int BMS_XiaoAn_SetOutputMosAction(void)//设置放电电MOS控制
{
    u8 outputMosSwitch = data_getData()->bms.outputMosSwitch;
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_OUTPUT_MOS, &outputMosSwitch, 1);
}

static int BMS_XiaoAn_GetBaseInfoAction(void)//查询BMS基本数据
{
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_GET_BMS_BASE_INFO, NULL, 0);
}

static int BMS_XiaoAn_GetReTimeInfoAction(void)//查询BMS实时数据
{
    return BMS_XiaoAn_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_GET_BMS_RETIME_INFO, NULL, 0);
}

static int BMS_XiaoAn_StartOTAAction(void)
{
    XIAOAN_BMS_START_OTA OTAMSG;
    OTAMSG.bms_version = _htons(setting.statusConf.bmsUpgradeVersion);
    OTAMSG.g_bmsFirmwareDataBytes = _htonl(g_bmsFirmwareDataBytes);
    LOG_DEBUG("[BMS_OTA] Send start package");
    return da14580_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_START_UPDATE, (u8 *)&OTAMSG, sizeof(XIAOAN_BMS_START_OTA));
}

static int BMS_XiaoAn_OTARealDataAction(void)
{
    int i = 0, rc = 0, m = 0;
    u8 *senddata = NULL;
    u32 datalen = g_bmsSendDataLenPerTime + 2;
    u8 *p = (u8*)Malloc(datalen);

    if(NULL == p)
    {
        Free(p);
        return -1;
    }
    senddata = p;
    g_bmsPackID++;
    *senddata++ = (u8)(g_bmsPackID >> 8);
    *senddata++ = (u8)g_bmsPackID;
    for(i = 0; i < g_bmsSendDataLenPerTime; i++)
    {
        if((g_bmsPackID - 1) * g_bmsSendDataLenPerTime + i < g_bmsFirmwareDataBytes)
        {
            *senddata++ = *g_bmsFirmwareData++;
        }
        else
        {
            g_bmsSendCompleteFlag = 1;
            break;
        }
    }
    if((g_bmsPackID - 1) * g_bmsSendDataLenPerTime + i == g_bmsFirmwareDataBytes && g_bmsSendCompleteFlag != 1)//当升级包是每帧发送长度的整数倍的时候会触发
    {
        g_bmsSendCompleteFlag = 1;
    }

    LOG_DEBUG("[BMS_XA]*********g_bmsSendDataLenPerTime:%d,bms_sendcnt:%d,total:%d,i:%d,*******************", g_bmsSendDataLenPerTime,g_bmsPackID, g_bmsFirmwareDataBytes/g_bmsSendDataLenPerTime, i);
    rc = da14580_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SENDFILE, senddata-(i+2), i+2);
    ASYNC_PROC_MAP * etc_async_procs = etcMsg_getAsyncProcs();
    for(m = 0; m < etcMsg_getAsyncProcsSize(); m++)
    {
        if(etc_async_procs[m].address == XIAOAN_BMS_ADDRESS && etc_async_procs[m].cmd == XIAOAN_BMS_SENDFILE)
        {
            etc_async_procs[m].actionTimes++;
        }
    }
    g_bmsResendLenBak = i;
    timer_start(TIMER_BMS_RETRANSFER, TIMER_S, 2, BMS_XiaoAn_retransfer_handler);
    Free(p);
    return rc;
}

static int BMS_XiaoAn_retransfer_handler(void)
{
    int i = 0, m = 0;
    u8 *p = (u8*)Malloc(g_bmsResendLenBak + 2);
    u8 *senddata = NULL;
    if(NULL == p)
    {
        LOG_ERROR("[BMS_XA]mallocate memory failed");
        Free(p);
        return -1;
    }
    g_bmsRetransferCnt++;
    LOG_ERROR("[BMS_XA]***** failed to receive upgrade data response,retransfer now,g_etcPackID:%d  ******", g_bmsPackID);
    senddata=p;
    *senddata++ = (u8)(g_bmsPackID>>8);
    *senddata++ = (u8)g_bmsPackID;
    g_bmsFirmwareData = g_bmsFirmwareData-g_bmsResendLenBak;
    for(i = 0; i < g_bmsResendLenBak; i++)
    {
        *senddata++ = *g_bmsFirmwareData++;
    }
    LOG_DEBUG("retransfer: g_bmsResendLenBak = %d", g_bmsResendLenBak);
    LOG_HEX(g_bmsFirmwareData - g_bmsResendLenBak, g_bmsResendLenBak);
    da14580_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SENDFILE, senddata - (i + 2), i + 2);
    ASYNC_PROC_MAP * etc_async_procs = etcMsg_getAsyncProcs();
    for(m = 0; m < etcMsg_getAsyncProcsSize(); m++)
    {
        if(etc_async_procs[m].address == XIAOAN_BMS_ADDRESS && etc_async_procs[m].cmd == XIAOAN_BMS_SENDFILE)
        {
            etc_async_procs[m].actionTimes++;
        }
    }
    Free(p);
    if(g_bmsRetransferCnt < 3)
    {
        timer_start(TIMER_BMS_RETRANSFER, TIMER_MS, 300, BMS_XiaoAn_retransfer_handler);
    }
    else
    {
        if(g_bmsReupgradeCnt++ > 25)
        {
            g_bmsReupgradeCnt = 0;
            LOG_ERROR("[BMS_XA] Reupgrade Over 25 times  OTA failed !!!!");
            etcMsg_BMSOTA_Failed(); //重新升级25次失败，强行停止
            return -1;
        }
        else
        {
            LOG_ERROR("[BMS_XA] has retransfered over 3 times, reupgrade now!!!!");
            bmsOta_SetUpgrading(L_FALSE);
            Free(g_bmsFirmwareDataP);
            g_bmsFirmwareDataP = NULL;
            timer_start(TIMER_BMS_DELAY, TIMER_MS, 100, bmsOta_upgardeTimerHandler);
            return 0;
        }
    }
    return 0;
}

static int BMS_XiaoAn_OTACompleteAction(void)
{
    u32 crc = setting.statusConf.bmsFirmwareCRC;
    LOG_DEBUG("[BMS_XA] raw crc = %d CRC = %d", crc, setting.statusConf.bmsFirmwareCRC);
    crc = _htonl(crc);
    LOG_DEBUG("[BMS_XA] Send Complete Req");
    return da14580_sendDATA(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_STOP_UPDATE, (u8 *)&crc, sizeof(crc));
}

__attribute__((unused)) static int BMS_XiaoAn_GetLastError_rsp(u8 *data)
{
    MSG_HEADER_XIAOAN_BMS *msg = (MSG_HEADER_XIAOAN_BMS *)data;
    DATA_U32_BITS *u32Data = (DATA_U32_BITS *)msg->data;

    data_getData()->bms.lastErrorCode = _ntohl(u32Data->data);

    LOG_INFO("----------get BMS lastError data:%d---------",u32Data->data);
    return 0;
}
__attribute__((unused)) static int BMS_XiaoAn_SetHeart_rsp(u8 *data)
{
    LOG_INFO("----------get BMS heart rsp data---------");
    return 0;
}

__attribute__((unused)) static int BMS_XiaoAn_SetFunc_rsp(u8 *data)
{
    LOG_INFO("----------get setBMSFunc rsp data---------");
    return 0;
}

__attribute__((unused)) static int BMS_XiaoAn_SetElecSwitch_rsp(u8 *data)
{
    LOG_INFO("----------get setBMSElecSwitch rsp data---------");
    return 0;
}

__attribute__((unused)) static int BMS_XiaoAn_SetStoreMode_rsp(u8 *data)
{
    LOG_INFO("----------get setBMSStoreMode rsp data---------");
    return 0;
}

__attribute__((unused)) static int BMS_XiaoAn_SetInputMos_rsp(u8 *data)
{
    LOG_INFO("----------get setBMSInputMos rsp data---------");
    return 0;
}

__attribute__((unused)) static int BMS_XiaoAn_SetOutputMos_rsp(u8 *data)
{
    LOG_INFO("----------get setBMSOutputMos rsp data---------");
    return 0;
}

static int BMS_XiaoAn_GetBaseInfo_rsp(uint8_t *data)
{
    u8 tempBuffer[16] = {0};
    DATA *pData = data_getData();
    MSG_HEADER_XIAOAN_BMS *msg = (MSG_HEADER_XIAOAN_BMS *)data;

    XIAOAN_BMS_BASE_DATA *bmsBaseData = (XIAOAN_BMS_BASE_DATA *)msg->data;


    memcpy(tempBuffer, pData->bms.SN, 16);
    pData->bms.protocolVer = bmsBaseData->protocolVer;
    memcpy(pData->bms.manufacturer, bmsBaseData->manufacturer, 16);
    memcpy(pData->bms.model, bmsBaseData->model, 16);
    pData->bms.hardwareVer = _ntohs(bmsBaseData->hardwareVer);
    pData->bms.softwareVer = _ntohs(bmsBaseData->softwareVer);
    memcpy(pData->bms.SN, bmsBaseData->SN, 16);
    memcpy(pData->bms.gpsId, bmsBaseData->gpsId, 16);
    pData->bms.capacity = _ntohs(bmsBaseData->capacity);
    pData->bms.cycleCount = _ntohs(bmsBaseData->cycleCount);

    LOG_INFO("pData->bms.protocolVer:%d", pData->bms.protocolVer);
    LOG_INFO("pData->bms.manufacturer:%s", pData->bms.manufacturer);
    LOG_INFO("pData->bms.model:%s", pData->bms.model);
    LOG_INFO("pData->bms.hardwareVer:%d", pData->bms.hardwareVer);
    LOG_INFO("pData->bms.softwareVer:%d", pData->bms.softwareVer);
    LOG_INFO("pData->bms.SN:%s", pData->bms.SN);
    LOG_INFO("pData->bms.gpsId:%s", pData->bms.gpsId);
    LOG_INFO("pData->bms.capacity:%d", pData->bms.capacity);
    LOG_INFO("pData->bms.cycleCount:%d", pData->bms.cycleCount);

    return 0;
}

static int BMS_XiaoAn_GetReTimeInfo_rsp(uint8_t *data)
{
    static s16 last_SOC = 0;
    DATA *pData = data_getData();
    MSG_HEADER_XIAOAN_BMS *msg = (MSG_HEADER_XIAOAN_BMS *)data;

    XIAOAN_BMS_RETIME_DATA *bmsReTimeData = (XIAOAN_BMS_RETIME_DATA *)msg->data;
    pData->bms.protocolVer = bmsReTimeData->protocolVer;
    pData->bms.voltage = _ntohs(bmsReTimeData->voltage);
    pData->bms.current = _ntohl(bmsReTimeData->current);
    pData->bms.MOSTemperature = bmsReTimeData->MOSTemperature;
    pData->bms.temperature1 = bmsReTimeData->temperature1;
    pData->bms.temperature2 = bmsReTimeData->temperature2;
    pData->bms.cellVoltageMax = _ntohs(bmsReTimeData->cellVoltageMax);
    pData->bms.cellVoltageMin = _ntohs(bmsReTimeData->cellVoltageMin);
    pData->bms.cellVoltageDIF = _ntohs(bmsReTimeData->cellVoltageDIF);
    pData->bms.fault = _ntohs(bmsReTimeData->fault);
    pData->bms.SOC = bmsReTimeData->SOC;
    pData->bms.remainCapacity = _ntohs(bmsReTimeData->remainCapacity);
    pData->bms.timestamp = (u32)rtc_getTimestamp();

    LOG_INFO("pData->bms.protocolVer:%d", pData->bms.protocolVer);
    LOG_INFO("pData->bms.voltage:%d", pData->bms.voltage);
    LOG_INFO("pData->bms.current:%d", pData->bms.current);
    LOG_INFO("pData->bms.MOSTemperature:%d", pData->bms.MOSTemperature);
    LOG_INFO("pData->bms.temperature1:%d", pData->bms.temperature1);
    LOG_INFO("pData->bms.temperature2:%d", pData->bms.temperature2);
    LOG_INFO("pData->bms.cellVoltageMax:%d", pData->bms.cellVoltageMax);
    LOG_INFO("pData->bms.cellVoltageMin:%d", pData->bms.cellVoltageMin);
    LOG_INFO("pData->bms.cellVoltageDIF:%d", pData->bms.cellVoltageDIF);
    LOG_INFO("pData->bms.fault:%d", pData->bms.fault);
    LOG_INFO("pData->bms.SOC:%d", pData->bms.SOC);
    LOG_INFO("pData->bms.remainCapacity:%d", pData->bms.remainCapacity);

    if(pData->bms.SOC != last_SOC)
    {
        s16 tempSoc = pData->bms.SOC;
        if(abs(last_SOC - tempSoc)>= 2)
        {
            data_getData()->socFluct = L_TRUE;
        }
        last_SOC = pData->bms.SOC;
    }

    if(setting.statusConf.bmsSoc != data_getData()->bms.SOC)
    {
        setting.statusConf.bmsSoc = data_getData()->bms.SOC;
        statusConf_save(); //保存BMS电量
    }

    //ETC_XiaoAn_SetBMSSoc(); //此处关联ETC 未尝试解耦 暂存

    return 0;
}

static int BMS_XiaoAn_GetStartOTA_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_BMS *msg = (MSG_HEADER_XIAOAN_BMS *)data;
    XIAOAN_BMS_START_OTA_RSP *udata =(XIAOAN_BMS_START_OTA_RSP *)msg->data;

    if(msg->length != 3)
    {
        return -1;
    }
    if(_htons(msg->signature) == 0xAA55)
    {
        if(udata->canUpgrade == 0x00)//返回0表示可以升级
        {
            LOG_DEBUG("[BMS_OTA] receive start PAC resp");
            timer_stop(TIMER_BMS_RETRANSFER);
            g_bmsSendDataLenPerTime = _htons(udata->size);
            timer_start(TIMER_BMS_DELAY, TIMER_MS, 500, etcMsg_SendBmsRealData);
        }
    }
    else
    {
        LOG_ERROR("[BMS_XA] XiaoAn OTA Start signature error");
        return -1;
    }

    return 0;
}

static int BMS_XiaoAn_OTARealData_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_BMS *msg = (MSG_HEADER_XIAOAN_BMS *)data;
    XIAOAN_BMS_pageID *pdata=(XIAOAN_BMS_pageID *)msg->data;

    if(msg->length != 2)
    {
        return -1;
    }
    if(_htons(msg->signature) == 0xAA55)
    {
        timer_stop(TIMER_BMS_RETRANSFER);
        if(pdata->pageID == 0)
        {
            //重新开始升级
            LOG_ERROR("pageID error,restart BMS update");
            Free(g_bmsFirmwareDataP);
            g_bmsFirmwareDataP = NULL;
            bmsOta_SetUpgrading(L_FALSE);
            return -1;
        }
        if(!g_bmsSendCompleteFlag)
        {
            LOG_DEBUG("[BMS_XA] continue send Ota data");
            etcMsg_SendBmsRealData();
        }
        else
        {
            LOG_DEBUG("[BMS_XA] Pack Send Complete");
            g_bmsSendCompleteFlag = 0;
            etcMsg_SendBmsOTAComplete();
        }
    }
    else
    {
        LOG_ERROR("signature error");
        return -1;
    }
    return 0;
}

static int BMS_XiaoAn_OTAComplete_rsp(uint8_t *data)
{
    MSG_HEADER_XIAOAN_BMS *msg = (MSG_HEADER_XIAOAN_BMS *)data;
    XIAOAN_BMS_ISSUCCESS *udata =(XIAOAN_BMS_ISSUCCESS *)msg->data;
    timer_stop(TIMER_BMS_RETRANSFER);

    if(msg->length != 1)
    {
        LOG_ERROR("[BMS_XA] OTACompletePac length InValid");
        return -1;
    }
    if(udata->isRevSuccess == 0)//控制接受数据成功，开始升级操作
    {
        da14580_sendDATA(BIO_ADDRESS, CMD_BIO_PING, NULL, 0);
        da14580_setHeartbeat(L_TRUE);
        LOG_DEBUG("[BMS_XA]*********  UPGRADE FINISH!! *********");
        bmsOta_SetUpgrading(L_FALSE);
        setting.statusConf.bmsUpgradeFlag = 0;
        car_accOff();
        setting.statusConf.bmsVersion = setting.statusConf.bmsUpgradeVersion;
        data_getData()->bms.softwareVer = setting.statusConf.bmsUpgradeVersion;
        statusConf_save();
        fs_deleteFile(UPGRADE_BMS_FILE_NAME);
        timer_stop(TIMER_BMS_UPGRADE);
        timer_stop(TIMER_BMS_RETRANSFER);
        timer_stop(TIMER_BMS_DELAY);
        Free(g_bmsFirmwareDataP);
        g_bmsFirmwareDataP = NULL;
    }
    else
    {
        //重新开始升级
        Free(g_bmsFirmwareDataP);
        g_bmsFirmwareDataP = NULL;
        bmsOta_SetUpgrading(L_FALSE);
    }
    g_bmsResendCompleteDataCnt = 0;
    return 0;
}

static void BMS_XiaoAn_GetBaseInfo(void)//查询BMS基本数据
{
    etcMsg_setETCHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_GET_BMS_BASE_INFO,BMS_XiaoAn_GetBaseInfoAction, BMS_XiaoAn_GetBaseInfo_rsp, NULL);
}

static void BMS_XiaoAn_GetReTimeInfo(void)//查询BMS实时数据
{
    etcMsg_setETCHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_GET_BMS_RETIME_INFO, BMS_XiaoAn_GetReTimeInfoAction, BMS_XiaoAn_GetReTimeInfo_rsp, NULL);
}
void BMS_XiaoAn_OTAStart(void)
{
    etcMsg_setETCHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_START_UPDATE, BMS_XiaoAn_StartOTAAction, BMS_XiaoAn_GetStartOTA_rsp, NULL);
}

void BMS_XiaoAn_OTARealData(void)
{
    etcMsg_setETCHandler(XIAOAN_BMS_ADDRESS,XIAOAN_BMS_SENDFILE, BMS_XiaoAn_OTARealDataAction, BMS_XiaoAn_OTARealData_rsp, NULL);
}
void BMS_XiaoAn_OTAComplete(void)
{
    etcMsg_setETCHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_STOP_UPDATE, BMS_XiaoAn_OTACompleteAction, BMS_XiaoAn_OTAComplete_rsp, NULL);
}

void BMS_XiaoAn_Initial(void)
{
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_START_UPDATE, NULL, BMS_XiaoAn_GetStartOTA_rsp, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SENDFILE, NULL, BMS_XiaoAn_OTARealData_rsp, NULL, L_TRUE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_STOP_UPDATE, NULL, BMS_XiaoAn_OTAComplete_rsp, NULL, L_TRUE);

    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_GET_LASTERROR, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_HEART, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_FUNC, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_OUT_ELEC_SWITCH, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_STORE_MODE, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_INPUT_MOS, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SET_OUTPUT_MOS, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_GET_BMS_BASE_INFO, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_GET_BMS_RETIME_INFO, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_START_UPDATE, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_SENDFILE, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XIAOAN_BMS_ADDRESS, XIAOAN_BMS_STOP_UPDATE, NULL, NULL, NULL, L_FALSE);
}

typedef void (*XIAOAN_BMS_PROC)(void);

XIAOAN_BMS_PROC xiaoan_bms_proc[] =
{
    BMS_XiaoAn_GetBaseInfo,
    BMS_XiaoAn_GetReTimeInfo,
};

int BMS_XiaoAn_LoopGetData(void)
{
    static u8 i = 0;
    if(i < sizeof(xiaoan_bms_proc) / sizeof(xiaoan_bms_proc[0]) - 1)
    {
        i++;
    }
    else
    {
        i = 0;
    }
    if(xiaoan_bms_proc[i] != NULL)
    {
        xiaoan_bms_proc[i]();
    }
    return 0;
}

static void *BMS_XiaoAn_allocMsg(u8 address, u8 cmd, u8 *data, u8 dataLen)
{
    MSG_HEADER_XIAOAN_BMS *msg = Malloc(MSG_HEADER_XIAOAN_BMS_LEN + dataLen + 1);
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

static int BMS_XiaoAn_sendDATA(u8 address, u8 cmd, u8 *data, u8 dataLen)
{
    u8 *send_data = (u8 *)BMS_XiaoAn_allocMsg(address, cmd, data, dataLen);
    if(send_data)
    {
        da14580_sendUartData(send_data, MSG_HEADER_XIAOAN_BMS_LEN + dataLen + 1);
        free_msg((void *)send_data);
        return 0;
    }
    return -1;
}

