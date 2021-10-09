#include <string.h>
#include <stdio.h>
#include "ke_mem.h"
#include "ke_msg.h"
#include "ble_proc.h"
#include "protocol.h"
#include "local_event.h"
#include "ble_scan_proc.h"
#include "user_sps_device.h"
#include "sharebike.h"
#include "app_easy_timer.h"
#include "user_timer.h"
#include "uart1.h"
#include "rf_585.h"
#include "ble_uart_port.h"

beaconStatus_t g_beaconStatus = {0};

beaconStatus_t *ble_getBeaconStatus(void)
{
    return &g_beaconStatus;
}



/*
* decode one ADV data and set the result point to the right place
* return:
*       success: total len
*       failed:  BLE_FAILED
*/
static uint32_t ble_scan_decodeOneTypeData(ST_BLE_SCAN_DATA_FEATURE *feature, char *headData)
{
    int len = headData[0] + 1;

    feature->type = headData[1];
    feature->dataLen = len - 2;
    if(len <= 31)
    {
        feature->data = headData + 2;
        return len;
    }
    return BLE_FAILED;
}

/*
* 从扫描结果中解析出 ST_BLE_SCAN_RESULT 信息，结果保留指针，
*/
static uint32_t ble_scan_decodeADVData(ST_BLE_SCAN_RESULT *result, char *ADVData, uint8_t dataLen)
{
    uint8_t pos =0;
    ST_BLE_SCAN_DATA_FEATURE feature_temp = {0, 0, NULL};
    memset(result, 0, sizeof(ST_BLE_SCAN_RESULT));
    do
    {
        int32_t len = ble_scan_decodeOneTypeData(&feature_temp, ADVData + pos);
        if(BLE_FAILED == len)
        {
            return BLE_FAILED;
        }
        pos += len;
        if(BLE_TYPE_MANUFACTURE == feature_temp.type) // manufactureData
        {
            result->manufacture = feature_temp.data;
            result->manufactureLen = feature_temp.dataLen;
        }
        else if(BLE_TYPE_NAME == feature_temp.type) //name
        {
            result->name = feature_temp.data;
            result->nameLen = feature_temp.dataLen;
        }
    }
    while(pos < dataLen);

    if(((NULL != result->name) && (NULL != result->manufacture) ) || (0 == memcmp(result->name, "Wy", 2)))
    {
        return BLE_SUCCESS;
    }
    return BLE_FAILED;
}

//检测是否是已配置的PKE KEY
static bool ble_scan_isCfgedKey(char *manufacture, uint8_t manufactureLen)
{
    if(sizeof(ST_BLE_SCAN_PKE_MANUFACTURE_DATA) != manufactureLen)
    {
        return false;
    }

    ST_BLE_SCAN_PKE_MANUFACTURE_DATA *key = (ST_BLE_SCAN_PKE_MANUFACTURE_DATA *)manufacture;
    for(int i=0; i < setting.scan.keyNum; i++)
    {
        if(0 == memcmp((const char*)key->keyId, (const char*)setting.scan.cfgedKeyID[i], PKE_KEY_ID_LEN))
        {
            return true;
        }
    }
    return false;
}

void ble_stop_scan(void)
{
    //arch_printf( "SCAN STOP\r\n");
    struct gapm_cancel_cmd *cmd =(struct gapm_cancel_cmd *) KE_MSG_ALLOC(GAPM_CANCEL_CMD, TASK_GAPM, TASK_APP, gapm_cancel_cmd);
    cmd->operation = GAPM_CANCEL; // Set GAPM_SCAN_PASSIVE
    ke_msg_send(cmd);// Send the message
}

static int ble_debug(uint8_t *data, uint16_t len)
{
    // debug
    uart_sendMsgtoSIM868(BLE_CONF, BIO_LOG, len, data);
    return 0;
}

int ble_scan_timeout_callback(void)
{
    //持续130ms的扫描结束了
    timer_stop(TIMER_SCAN_TIMEOUT);
    
    if(setting.isconnected != 1 || setting.mode == BLE_MODE_ADV) 
    {
        //如果当前没有处于连接状态或者非扫描模式, 则切换到广播
        ble_stop_scan();
        ble_start_adv();
    }
    else
    {
        //如果当前处于连接状态, 则继续扫描
        ble_stop_scan();
        user_scan_start();
        timer_start(TIMER_SCAN_TIMEOUT, USER_SCAN_TIMEOUT_MS, ble_scan_timeout_callback);
    }
    return 0;
}


static int ble_renew_beaconInfo_cb(void)
{
    //后移道钉信息
    g_beaconStatus.highestInfo5SecondsAgo = g_beaconStatus.highestInfo4SecondsAgo;
    g_beaconStatus.highestInfo4SecondsAgo = g_beaconStatus.highestInfo3SecondsAgo;
    g_beaconStatus.highestInfo3SecondsAgo = g_beaconStatus.highestInfo2SecondsAgo;
    g_beaconStatus.highestInfo2SecondsAgo = g_beaconStatus.highestInfo1SecondsAgo;
    //清空最新的道钉信息
    g_beaconStatus.highestInfo1SecondsAgo.dbm = 0;
    memset(g_beaconStatus.highestInfo1SecondsAgo.mac, 0, BD_ADDR_LEN);
    memset(g_beaconStatus.highestInfo1SecondsAgo.adv, 0, ADV_DATA_LEN);
    return 0;
}

//扫描道钉信息完成, 都在这里面处理
static int ble_scan_beacon_cb(beaconInfo_t *beaconInfo)
{
    //实时存储信号最强的信息
    if(g_beaconStatus.highestInfo1SecondsAgo.dbm == 0 || beaconInfo->dbm <= g_beaconStatus.highestInfo1SecondsAgo.dbm)
    { 
        g_beaconStatus.highestInfo1SecondsAgo = *beaconInfo;
    }

    if(!timer_isTimerStart(TIMER_RENEW_BEACON))
    {
        timer_startRepeat(TIMER_RENEW_BEACON, 1000, ble_renew_beaconInfo_cb);
    }
    return 0;
}

void ble_scan_cb(ST_SCAN_INFO *param)
{
    ST_BLE_SCAN_RESULT scan_result = {NULL, 0, NULL, 0};
    
    uint8_t dbm = 0;    
    sharebike_t stSharebike = {0};

    dbm = param->rssi;
    dbm = (~dbm) + 1; // rssi值为有符号数,就是-dbm，此处为符号转化，获得绝对值
    
    if(BLE_SUCCESS == ble_scan_decodeADVData(&scan_result, (char *)param->data, param->data_len))
    {
        //判断蓝牙钥匙ID
        if(ble_scan_isCfgedKey(scan_result.manufacture, scan_result.manufactureLen))
        {
            uint8_t funcNum = 0xFF;
            ST_BLE_SCAN_PKE_MANUFACTURE_DATA *pke_info = (ST_BLE_SCAN_PKE_MANUFACTURE_DATA *)scan_result.manufacture;
            memcpy((char *)&setting.scan.key, scan_result.manufacture, sizeof(ST_BLE_SCAN_PKE_MANUFACTURE_DATA));

            if((PKE_CMD_PKE		   == pke_info->cmd)&&(PKE_VALUE_PKE		   == pke_info->value)) funcNum = NOTIFY_PKE;
            if((PKE_CMD_DEFEND	   == pke_info->cmd)&&(PKE_VALUE_DEFEND_ON	   == pke_info->value)) funcNum = NOTIFY_DEFEND_ON;
            if((PKE_CMD_DEFEND	   == pke_info->cmd)&&(PKE_VALUE_DEFEND_OFF    == pke_info->value)) funcNum = NOTIFY_DEFEND_OFF;
            if((PKE_CMD_FINDME	   == pke_info->cmd)&&(PKE_VALUE_FINDME 	   == pke_info->value)) funcNum = NOTIFY_FINDME;
            if((PKE_CMD_UNLOCK	   == pke_info->cmd)&&(PKE_VALUE_UNLOCK 	   == pke_info->value)) funcNum = NOTIFY_START;
            if(funcNum != 0xFF)
            {
                //将扫描到的发给Master, 如果配置了蓝牙钥匙模式, 讲道理不能进行广播, 影响蓝牙扫描响应速度
                uart_sendMsgtoSIM868(BLE_CONF, BIO_NOTIFY, 1, &funcNum);
            }
            return;
        }
        
        shareBike_permit((char *)param->data, param->data_len, &stSharebike);
        //道钉逻辑判断, "Wy"浩源道钉, "IB"金桔道钉, "shareBike_permit"金通道钉
        if(
           (0 == memcmp(scan_result.name, "Wy", 2)) || 
           (0 == memcmp(scan_result.name, "IB", 2)) ||
           (1 == stSharebike.isLocationPile)
           )
        {
            beaconInfo_t beaconInfo = {0};
            beaconInfo.dbm = dbm;//道钉信号强度
			memcpy((uint8_t *)beaconInfo.mac, param->adv_addr.addr, BD_ADDR_LEN); //道钉广播地址
            memset((uint8_t *)beaconInfo.adv, 0, ADV_DATA_LEN);
            memcpy((uint8_t *)beaconInfo.adv, param->data, param->data_len);//道钉广播内容
            ble_scan_beacon_cb(&beaconInfo);
            return;
        }
    } 
}

