#include "app_mid.h"
#include "app_api.h"
#include "ke_timer.h"
#include "gpio.h"
#include "uart1.h"
#include "setting.h"
#include "ble_proc.h"
#include "protocol.h"
#include "local_event.h"
#include "ble_adv_proc.h"
#include "ble_scan_proc.h"
#include "ble_uart_port.h"
#include "user_sps_device.h"

extern ST_BLE_STATE setting;
extern beaconStatus_t g_beaconStatus;

static volatile uint32_t g_missHeartBeatTime = 0;

static uint32_t g_needRst = 0;

void ble_resetMissHeartBeatTime(void)
{
    g_missHeartBeatTime = 0;
}

void ble_setNeedRstMcu(void)
{
    g_needRst = 1;
}

void ble_watchdog_proc(void)
{
    static uint8_t g_LowpTime = 0;
    static uint8_t g_isGPIOHigh = 1;

    g_missHeartBeatTime++;
    if(g_needRst || g_missHeartBeatTime >= (5 * 60) )//如果心跳超时5分钟了 处理关机操作
    {
        g_isGPIOHigh = 0;// 置位0 因为输出查看status都是0
        g_missHeartBeatTime = 0;// 重置心跳丢失时间
        GPIO_SetInactive(GPIO_PORT_1, GPIO_PIN_2);//拉低关机L610
    }

    if(g_isGPIOHigh == 0)//当前正在处理关机操作
    {
        if(g_LowpTime >= 1)// 如果上一秒做了关机操作 这一秒恢复
        {
            g_needRst = 0; //重置重启设备标志
            g_isGPIOHigh = 1;// 置位1 因为输出查看status都是0
            g_LowpTime = 0;
            GPIO_SetActive(GPIO_PORT_1, GPIO_PIN_2);//恢复关机L610
        }
        g_LowpTime++;// 关机操作计时
    }
    else
    {
        g_LowpTime = 0;//个如果没处于关机操作 计时停止
    }

}

void ble_start_adv(void)
{
    default_advertise_operation();
}

void ble_start_scan(void)
{
    user_scan_start();
}

int8_t ble_rf_rssi_convert(uint8_t rssi_reg)
{
    // NOTE: Approximate conversion corresponding to the following formula:
    // dBm = (0.474f * rssi) - 112.4f.
    return ((rssi_reg >> 1U) - 112U);
}

void ble_selfCorrect(void)
{
    //广播保护 如果处于广播模式且未连接,2分钟重启一次协议栈
    static uint32_t adv_times = 0;
    if(setting.mode == BLE_MODE_ADV && setting.isconnected == 0)
    {
        if(++adv_times >= 120)
        {
            adv_times = 0;
            app_gapm_reset_op();
            if(setting.isHeartBeatOn)
            {
                uart_sendNotify(BLE_CONF, BIO_NOTIFY, NOTIFY_STACKRESTART);
            }
        }
    }
    else
    {
        adv_times = 0;
    }
}

int ble_proc_timer(void) //1s处理一次
{
    static uint8_t count = 0;
    if(BLE_FAILED == setting_isParamConfiged())
    {
        uart_sendMsgtoSIM868(BLE_CONF, BIO_SET_CONFIG_V2, 0, NULL);
    }
    else if(setting.isHeartBeatOn)
    {
        ST_BEACON_STATUS beaconStatus = {0};
        beaconStatus_t *pBeaconStatus = ble_getBeaconStatus();

        //if(GPIO_GetPinStatus(GPIO_PORT_2, GPIO_PIN_3))state |= (1 << 0);
        if(GPIO_GetPinStatus(GPIO_PORT_2, GPIO_PIN_4))beaconStatus.state |= (1 << 1);
        if(GPIO_GetPinStatus(GPIO_PORT_2, GPIO_PIN_6))beaconStatus.state |= (1 << 2);
        if(GPIO_GetPinStatus(GPIO_PORT_2, GPIO_PIN_7))beaconStatus.state |= (1 << 3);
        if(GPIO_GetPinStatus(GPIO_PORT_1, GPIO_PIN_0))beaconStatus.state |= (1 << 4);
        if(GPIO_GetPinStatus(GPIO_PORT_1, GPIO_PIN_1))beaconStatus.state |= (1 << 5);
        if(setting.isconnected == 1)beaconStatus.state |= (1 << 6);
        if(setting.mode == BLE_MODE_ADV)beaconStatus.state |= (1 << 7);
        
        beaconStatus.highestInfo1SecondsAgo = pBeaconStatus->highestInfo1SecondsAgo;
        beaconStatus.highestInfo2SecondsAgo = pBeaconStatus->highestInfo2SecondsAgo;
        beaconStatus.highestInfo3SecondsAgo = pBeaconStatus->highestInfo3SecondsAgo;
        beaconStatus.highestInfo4SecondsAgo = pBeaconStatus->highestInfo4SecondsAgo;
        beaconStatus.highestInfo5SecondsAgo = pBeaconStatus->highestInfo5SecondsAgo;
        
        uart_sendMsgtoSIM868(BLE_CONF, BIO_PING, sizeof(beaconStatus), (uint8_t *)&beaconStatus);
    }

    if(setting.isPKEType == 1) //如果使能蓝牙钥匙
    {
        if(0 == setting.scan.keyNum)
        {
            //如果没有配置钥匙 请求钥匙配置
            uart_sendMsgtoSIM868(BLE_CONF, PKE_KEYS_CONFIG, 0,NULL);
        }
    }

    //patch 如果接收的字符超过255 强制认为数据过大了 执行一次处理
    if(uart1_rx->length > 255)
    {
        reciv_data_fromSIM868_cb((const uint8_t *)uart1_rx->buffer, uart1_rx->length);
        uart1_rx->length = 0;
    }

    //patch 如果接收的字符超过255 强制认为数据过大了 执行一次处理
    if(uart2_rx->length > 255)
    {
        send_data_toSIM868((const uint8_t *)uart2_rx->buffer, uart2_rx->length);
        uart2_rx->length = 0;
    }

    //蓝牙看门狗处理
    ble_watchdog_proc();

    //蓝牙状态自校处理
    ble_selfCorrect();
    
    return 0;
};

static uint8_t ble_getCheckSum(BLE_MSG_HEADER *msg)
{
    uint8_t i = 0;
    uint8_t checksum = msg->cmd + msg->len;
    for(i = 0; i < msg->len; i++)
    {
        checksum += msg->data[i];
    }
    return checksum;
}

static bool ble_isCheckSumPass(BLE_MSG_HEADER *msg)
{
    uint8_t i = 0;
    uint8_t checksum = msg->cmd + msg->len;
    for(i = 0; i < msg->len; i++)
    {
        checksum += msg->data[i];
    }
    if(checksum == msg->data[msg->len])
    {
        return true;
    }

    return false;
}

int ble_procOneMsg(const uint8_t *data, uint16_t dataLen)
{
    BLE_MSG_HEADER *msg = (BLE_MSG_HEADER *)data;
    if(!ble_isCheckSumPass(msg))
    {
        return 0;
    }

    switch(msg->cmd)
    {
        case CMD_BLE_AWAKE_DEVICE:
        {
            uint8_t buf[128] = {0};
            uint16_t msgLen = sizeof(BLE_MSG_HEADER) + 1 + 1;// +1 +1为 code和校验字段

            BLE_MSG_HEADER *bleMsg = (BLE_MSG_HEADER *)buf;
            bleMsg->cmd = msg->cmd;
            bleMsg->len = 1;
            bleMsg->data[0] = 0;
            bleMsg->data[1] = ble_getCheckSum(bleMsg);

            send_data_toBLE(buf, msgLen);
        }
        break;
        default:
        {
            uint8_t buf[128] = {0};
            uint16_t wildMsgLength = sizeof(MSG_HEADER) + msg->len + 1;// +1为 校验字段

            MSG_HEADER *wildMsg = (MSG_HEADER *)buf;
            wildMsg->signature = 0x55AA;
            wildMsg->address = BLE_WILD;
            wildMsg->cmd = msg->cmd;
            wildMsg->len = msg->len;
            memcpy(wildMsg->data, msg->data, wildMsg->len+1);
            uart1_sendData((uint8_t*)wildMsg, wildMsgLength);
        }
        break;
    }
    return 0;
}
