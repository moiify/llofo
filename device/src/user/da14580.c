/*
 * da14580.c
 *
 *  Created on: 2017.09.23
 *      Author: wyb
 */
#include <string.h>

#include "fibo_opencpu.h"

#include "msg.h"
#include "log.h"
#include "uart.h"
#include "data.h"
#include "bioMsg.h"
#include "bleMsg.h"
#include "etcMsg.h"
#include "da14580.h"
#include "setting.h"
#include "hardware.h"
#include "user_timer.h"
#include "da14580_boot.h"
#include "ETC_XiaoAn.h"
#include "ETC_TaiBiTe.h"
#include "BMS_XingHeng.h"
#include "diagnosis.h"
#include "RFID.h"

#define BLE_RCV_BUFLEN 1024

int da14580_sendUartData(uint8_t *msg, uint32_t dataLen)
{
    int len = 0;
    if(data_getData()->ble_state.isDA14580Alive)
    {
        if(!data_getData()->ble_workMode)
        {
            LOG_INFO("[BLE] send data: ");
            LOG_BIN((const char *)msg, dataLen);
        }
        len = fibo_hal_uart_put(UART_BLE, msg, dataLen);
    }
    return len;
}

void *da14580_allocMsg(uint8_t address, uint8_t cmd, uint8_t *data, uint8_t dataLen)
{
    MSG_HEADER_XA *msg = Malloc(MSG_HEADER_XA_LEN + dataLen + 1);
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

int da14580_sendDATA(uint8_t address, uint8_t cmd, uint8_t *data, uint8_t dataLen)
{
    uint8_t *send_data = (uint8_t *)da14580_allocMsg(address, cmd, data, dataLen);
    if(send_data)
    {
        da14580_sendUartData(send_data, MSG_HEADER_XA_LEN + dataLen + 1);
        free_msg((void *)send_data);
        return 0;
    }
    return -1;
}

static void da14580_refreshState(void)
{
    data_getData()->ble_state.missHeartbeatCount = 0;
    data_getData()->ble_state.isDA14580Alive = L_TRUE;
    if(data_isSleeping())
    {
        data_setAwakeTime(SLEEP_BLE_WAKE);
    }
}

static u8 *g_da14580_buf = NULL;
static volatile s16 g_da14580_buf_len = 0;
static int bleRev_Process_cb(void)  //一次把全部的数据都处理完
{
    s16 proclen = 0;
    s16 leftlen = 0;
    s16 offect = 0;
    while(proclen != g_da14580_buf_len && g_da14580_buf_len)
    {
        leftlen = g_da14580_buf_len - proclen; //得到本次需要处理的长度
        proclen = g_da14580_buf_len;           //更新长度缓存
        if(setting.defaultConf.ccuType == TYPE_TAIBITE
        || setting.defaultConf.ccuType == TYPE_TAIBITE_NEW
        || setting.defaultConf.ccuType == TYPE_TAIBITE_SOC
        || setting.defaultConf.ccuType == TYPE_TAIBITE_09)
        {
            if(ETC_TaiBiTe_FilterFrame(g_da14580_buf + offect, leftlen) == L_TRUE)
            {
                da14580_refreshState();
            }
        }
        if(XiaoAn_FilterFrame(g_da14580_buf + offect, leftlen) == L_TRUE)  //小安ETC,BMS和内部通信协议都走这个入口
        {
            da14580_refreshState();
            if(data_getData()->checkBle == L_FALSE)
            {
                diag_DA14580CheckSuccess();
            }
            data_getData()->blePortData = L_TRUE;
        }

        if(setting.defaultConf.bmsType == TYPE_XINGHENGBMS)
        {
            if(XingHeng_FilterFrame(g_da14580_buf + offect, leftlen) == L_TRUE)
            {
                data_getData()->faultRecord.isBmsRsp = L_TRUE; //收到星恒BMS回复
                data_getData()->faultRecord.BmsComm =  L_TRUE;
                data_getData()->faultRecord.bmsSendNoRspTimes = 0;
            }
        }
        
        if(setting.settingConf.isRFIDEnable) //支持RFID定点停车功能的产品
        {
            if(RFID_FilterFrame(g_da14580_buf + offect, leftlen) == L_TRUE)
            {
                da14580_refreshState();
            }
        }
        offect += proclen;
    }
    g_da14580_buf_len = 0;
    memset(g_da14580_buf, 0, BLE_RCV_BUFLEN);
    return 0;
}

static int da14580_revDataHandle(uint8_t *data, uint16_t length)
{
    if(!g_da14580_buf)
    {
        g_da14580_buf = (u8 *)Malloc(BLE_RCV_BUFLEN);
        if(g_da14580_buf)
        {
            g_da14580_buf_len = 0;
            memset(g_da14580_buf, 0, BLE_RCV_BUFLEN);
        }
    }
    if(g_da14580_buf)
    {
        if((g_da14580_buf_len + length < BLE_RCV_BUFLEN) && data)
        {
            memcpy(g_da14580_buf + g_da14580_buf_len, data, length);
            g_da14580_buf_len += length;
            if(!data_isSleeping())
            {
                timer_start(TIEMR_BLE_UART, TIMER_MS, 10, bleRev_Process_cb);//从串口中断转移到定时器线程
            }
            else
            {
                bleRev_Process_cb();
            }
        }
        else
        {
            g_da14580_buf_len = 0;
            memset(g_da14580_buf, 0, BLE_RCV_BUFLEN);
        }
    }
    return 0;
}

static int da14580_loop_handler(void)
{
    /* 如果10s没有心跳 那么reboot蓝牙 */
    if(data_getData()->ble_state.missHeartbeatCount >= 10)
    {
        da14580_bootStart();
        return 0;
    }
    data_getData()->ble_state.missHeartbeatCount++;

    return 0;
}

static int da14580_uartMsgProc(uint8_t *buf, uint16_t length)
{
    LOG_INFO("receive ble:");
    LOG_BIN((const char *)buf, length);
    da14580_bootHandler(buf, length);
    da14580_revDataHandle(buf, length);
    return 0;
}

int da14580_setHeartbeat(u8 set_heartbeat)
{
    static u8 heartbeat_on = 0x01;
    static u8 heartbeat_off= 0x00;
    if(L_TRUE == set_heartbeat)
        da14580_sendDATA(BIO_ADDRESS, CMD_BIO_SET_BEATHEART, &heartbeat_on, 1);
    else if(L_FALSE == set_heartbeat)
        da14580_sendDATA(BIO_ADDRESS, CMD_BIO_SET_BEATHEART, &heartbeat_off, 1);
    else
        return L_FALSE;
    return L_TRUE;
}

int da14580_initial(void)
{
    data_getData()->checkBle = L_FALSE;
    uart_registerHandler(UART_BLE, da14580_uartMsgProc);
    timer_startRepeat(TIMER_BLE_LOOP, TIMER_S, 1, da14580_loop_handler);
    da14580_bootStart();
    return 0;
}

int da14580_setBlePinLevel(u8 port, u8 pin, BLE_PIN_LEVEL level)
{
    u8 data[3] = {0};
    data[0] = port;
    data[1] = pin;
    data[2] = level;
    da14580_sendDATA(BIO_ADDRESS, CMD_BIO_SET_PIN_LEVEL, data, 3);
    return 0;
}

