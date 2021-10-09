
#include <string.h>

#include "hardware.h"

#include "msg.h"
#include "log.h"
#include "data.h"
#include "utils.h"
#include "bioMsg.h"
#include "setting.h"
#include "da14580.h"
#include "hardware.h"
#include "user_timer.h"
#include "protocol.h"

void bioMsg_getBootDownStatus(void)
{
    da14580_sendDATA(BIO_ADDRESS, CMD_BIO_GET_BOOTSTATUS, NULL, 0);
}

void bioMsg_resetBLE(void)
{
    da14580_sendDATA(BIO_ADDRESS, CMD_BIO_REBOOT, NULL, 0);
}

static SACNTBEACON_RESULT_CB scanSuccessful_cb;
static SACNTBEACON_RESULT_CB scanFail_cb;

void bioMsg_startScanTBeacon(u8 *data, u8 dataLen)
{
    data_getData()->isWaitingTBeaconResult = L_TRUE;
    da14580_sendDATA(BIO_ADDRESS, CMD_BIO_START_SCAN_TBEACON, data, dataLen);
}

int bioMsg_setScanTBeaconResult_cb(SACNTBEACON_RESULT_CB scanSuccessful, SACNTBEACON_RESULT_CB scanFail)
{
    scanSuccessful_cb = scanSuccessful;
    scanFail_cb = scanFail;
	return 0;
}

int bioMsg_setBLEConfig_rsp(void *msg)
{	
    ST_MSG_SETTING_PARAM msgRsp = {0, {0}, {0}, {0}};
    char imei[MAX_IMEI_LENGTH + 1] = {0};
    uint8_t sw = 0;

    sw |= SW_IS_ADV;

    msgRsp.sw = sw;
    memcpy(msgRsp.name, setting.settingConf.ble_name, strlen((const char *)setting.settingConf.ble_name));
    fibo_get_imei((unsigned char *)imei, CFW_SIM_0);
    memcpy(msgRsp.imei, imei, MAX_IMEI_LENGTH);
	LOG_DEBUG("[BLE] set BLE config");
    da14580_sendDATA(BIO_ADDRESS, CMD_BIO_SET_CONFIG, (uint8_t *)&msgRsp, sizeof(ST_MSG_SETTING_PARAM));
    return 0;
}


int bioMsg_setBLEConfig(void)
{	
    return bioMsg_setBLEConfig_rsp(NULL);
}


/*
* decode one ADV data and set the result point to the right place
* return:
*       success: total len
*       failed:  -1
*/
static int bioMsg_decodeOneTypeData(ST_BLE_SCAN_DATA_FEATURE *feature, char *headData)
{
    int len = headData[0] + 1;

    if(len <= 1)
    {
        return -1;
    }

    feature->type = headData[1];
    feature->dataLen = len - 2;
    if(len <= 31)
    {
        feature->data = headData + 2;
        return len;
    }
    return -1;
}

/*
* 从扫描结果中解析出 ST_BLE_SCAN_RESULT 信息，结果保留指针，
*/
static int ble_scan_decodeADVData(ST_BLE_SCAN_RESULT *result, char *ADVData, uint8_t dataLen)
{
    int pos =0;
    ST_BLE_SCAN_DATA_FEATURE feature_temp = {0, 0, NULL};
    memset(result, 0, sizeof(ST_BLE_SCAN_RESULT));
    do
    {
        int len = bioMsg_decodeOneTypeData(&feature_temp, ADVData + pos);
        if(len < 0)
        {
            return len;
        }
        pos += len;
        if(0xFF == feature_temp.type) // manufactureData
        {
            result->manufacture = feature_temp.data;
            result->manufactureLen = feature_temp.dataLen;
        }
        else if(0x09 == feature_temp.type) //name
        {
            result->name = feature_temp.data;
            result->nameLen = feature_temp.dataLen;
        }
    }
    while(pos < dataLen);

    if((NULL != result->name) && (NULL != result->manufacture) )
    {
        //有name和manufactureData
        return 0;
    }
    else if(0 == memcmp(result->name, "Wy", 2))
    {
        //浩源道钉没有manufactureData
        return 0;
    }
    
    return -1;
}


static int bioMsg_pingRsp(void *m)
{
    u8 buf[64]={0};
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    
    if(data_getData()->ble_state.version == 0)
    {
        // 没有获取到蓝牙版本 获取之
        da14580_sendDATA(BIO_ADDRESS, CMD_BIO_VERSION, NULL, 0);
    }
    else
    {
        //回应ping包以避免被蓝牙看门狗重启
        da14580_sendDATA(BIO_ADDRESS, CMD_BIO_PING, NULL, 0);
    }
    
    if(msg->length == sizeof(ST_BEACON_STTAUS))
    {
        DATA *pData = data_getData();
        memset((u8 *)&pData->tBeaconStatus, 0, sizeof(beaconStatus_t));
        ST_BEACON_STTAUS *pBeaconStatus = (ST_BEACON_STTAUS *)msg->data;
        if(!pBeaconStatus)
        {
            return -1;
        }
        for(int i = 0; i < 5 && pBeaconStatus->highestInfoNSecondsAgo[i].dbm != 0; i++)
        {
            ST_BLE_SCAN_RESULT scan_result = {NULL, 0, NULL, 0};
            pData->tBeaconStatus.highestInfoNSecondsAgo[i].dbm = pBeaconStatus->highestInfoNSecondsAgo[i].dbm;
            memcpy(pData->tBeaconStatus.highestInfoNSecondsAgo[i].mac, pBeaconStatus->highestInfoNSecondsAgo[i].mac, 6);
            if(strstr(pBeaconStatus->highestInfoNSecondsAgo[i].adv, "Wy"))
            {
                if(0 == ble_scan_decodeADVData(&scan_result, (char *)pBeaconStatus->highestInfoNSecondsAgo[i].adv, ADV_DATA_LEN))
                {
                    //浩源道钉 需要从名字上解析一下数据
                    u8 tempStrData[2] = {0};
                    TBEACON_INFO_STR *tBeaconInfoStr = (TBEACON_INFO_STR *)(scan_result.name);
                    tempStrData[1] = tBeaconInfoStr->tBeaconNumStr;
                    AsciiToHex(tempStrData, &(pData->tBeaconStatus.highestInfoNSecondsAgo[i].tBeaconNum), 2);
                    tempStrData[1] = tBeaconInfoStr->tBeaconPileNumStr;
                    AsciiToHex(tempStrData, &(pData->tBeaconStatus.highestInfoNSecondsAgo[i].tBeaconPileNum), 2);
                    AsciiToHex(&tBeaconInfoStr->tBeaconSignalThresholdStr[0], &(pData->tBeaconStatus.highestInfoNSecondsAgo[i].tBeaconSignalThreshold), 2);
                    AsciiToHex(&tBeaconInfoStr->tBeaconSOCStr[0], &(pData->tBeaconStatus.highestInfoNSecondsAgo[i].tBeaconSOC), 2);
                    memcpy(pData->tBeaconStatus.highestInfoNSecondsAgo[i].tBeaconVersion, tBeaconInfoStr->tBeaconVersionStr, 2);
                    memcpy(pData->tBeaconStatus.highestInfoNSecondsAgo[i].tBeaconID, tBeaconInfoStr->tBeaconIDStr, 12);
                }
            }
        }
    }
    return 0;
}

static int bioMsg_connect_cb(void)
{
	if(!data_getData()->ble_workMode) //如果不是LOG透传模式
	{
		LOG_DEBUG("[bioMsg] connect protect");
		return da14580_sendDATA(BIO_ADDRESS, CMD_BIO_DISCONNECT_REQ, NULL, 0);
	}
	return 0;
}

static int bioMsg_bleNotify(void *data)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)data;
    
    if(msg->length != 1)return -1;
    
    switch (msg->data[0])
    {
        case NOTIFY_PKE:
            break;

        case NOTIFY_DEFEND_ON:
        break;
            
        case NOTIFY_DEFEND_OFF:
        break;
            
        case NOTIFY_FINDME:
        break;
            
        case NOTIFY_START:
        break;
            
        case NOTIFY_CONNECTED:
        {
            LOG_DEBUG("NOTIFY_CONNECTED...........");
            data_getData()->ble_state.isBLEConnected = L_TRUE;
            timer_start(TIMER_BLE_CONN_PROTECT, TIMER_S, 60, bioMsg_connect_cb);
        }
        break;
            
        case NOTIFY_DISCONNECTED:
        {
            LOG_DEBUG("NOTIFY_DISCONNECTED...........");
            data_getData()->ble_state.isBLEConnected = L_FALSE;
			timer_stop(TIMER_BLE_CONN_PROTECT);
        }
        break;
        case NOTIFY_STACKRESTART:
        {
            LOG_DEBUG("BLE STACK RESTART >>>>>");
        }
        break;

    }
    return 0;
}


static int bioMsg_getVersion_rsp(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    BIO_VERSION_NUM *version = (BIO_VERSION_NUM *)msg->data;
    data_getData()->ble_state.version = _ntohl(version->version);
    LOG_DEBUG("ble version: %x", data_getData()->ble_state.version);
    return 0;
}


int bioMsg_adcRsp(void *m)
{
    return 0;
}

static int bioMsg_log(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    char *logBuf = (char *)Malloc(msg->length +1);

    if(logBuf)
    {
        memset(logBuf, 0, msg->length + 1);
        memcpy(logBuf, msg->data, msg->length);
        LOG_DEBUG("%s", logBuf);
    }
    Free(logBuf);
	return 0;
}

static int bioMsg_logHex(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    LOG_HEX(msg->data, msg->length);
	return 0;
}

static int bioMsg_getBootStatusRsp(void *m)
{
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)m;
    if(msg->length == 1)
    {
        if(msg->data[0] == 0)
        {
            data_getData()->isBleBootDown = L_TRUE;
            LOG_DEBUG("ble boot has download");
        }
    }
    return 0;
}

PROC_MAP bio_msg_procs[] =
{
    {CMD_BIO_PING,          	bioMsg_pingRsp},
    {CMD_BIO_NOTIFY,        	bioMsg_bleNotify},
    {CMD_BIO_SET_CONFIG,    	bioMsg_setBLEConfig_rsp},
    {CMD_BIO_VERSION,       	bioMsg_getVersion_rsp},
    {CMD_BIO_LOG,           	bioMsg_log},
    {CMD_BIO_LOG_HEX,       	bioMsg_logHex},
    {CMD_BIO_ADC,           	bioMsg_adcRsp},
    {CMD_BIO_GET_BOOTSTATUS,    bioMsg_getBootStatusRsp},
};

int bioMsg_msgProc(uint8_t *data, uint16_t dataLen)
{
    uint8_t i = 0;
    MSG_HEADER_XA *msg = (MSG_HEADER_XA *)data;
    for(i = 0; i < sizeof(bio_msg_procs)/sizeof(bio_msg_procs[0]); i++)
    {
        if(bio_msg_procs[i].cmd == msg->cmd)
        {
            if(bio_msg_procs[i].action)
                bio_msg_procs[i].action(msg);
            return 0;
        }
    }

    return -1;
}

