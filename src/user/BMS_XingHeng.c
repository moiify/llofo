/*
 * BMS_XingHeng.c
 *
 *  Created on: 2020/10/24
 *      Author: cxb
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
#include "BMS_XingHeng.h"
#include "ETC_XiaoAn.h" //GetReTimeInfo查询完后,要去立即设置ETC,所以此处关联

#define XINGHENG_START_FLAG 0x3A

typedef void (*XINGHENG_BMS_DATA_LOOP)(void);
typedef struct
{
    XINGHENG_BMS_DATA_LOOP fun;
} XINGHENG_BMS_DATA_LOOP_MAP;

int BMS_XingHeng_procOneMsg(u8 *data, u8 dataLen)
{
    etcMsg_MsgProc(data, dataLen);
    return 0;
}

u8 *BMS_XingHeng_getBMSData(u8 cmd, u8 *data, u8 length)
{
    static u8 sendData[127] = {0};
    MSG_HEADER_XINGHENG_BMS *pData = NULL;
    u8 i = 0;
    u16 checksum = 0;

    pData = (MSG_HEADER_XINGHENG_BMS *)sendData;
    pData->signature = XINGHENG_START_FLAG;
    pData->address = XH_BMS_ADDRESS;
    pData->cmd = cmd;
    pData->length = length;

    if(length > 0)
    {
        memcpy(pData->data, data, length);
    }

    checksum = pData->address;
    checksum += pData->cmd;
    checksum += pData->length;

    for(i = 0; i < length; i++)
    {
        checksum += pData->data[i];
    }

    pData->data[length] = (u8)(checksum & 0x00ff);
    pData->data[length + 1] = (u8)(checksum >> 8 & 0x00ff);
    pData->data[length + 2] = 0x0d;
    pData->data[length + 3] = 0x0a;
    return sendData;
}

L_BOOL XingHeng_FilterFrame(u8 * data, u16 length)
{
    u8 vaild = 0;
	u8 proctimes = 0;
    s16 leftlen = length;
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;

    while(leftlen >= MSG_HEADER_XINGHENG_BMS_LEN)
    {
        if(XINGHENG_START_FLAG != msg->signature && msg->address != XH_BMS_ADDRESS)
        {
            int i = 0;
            u8 *pMsg = (u8 *)msg;

            //去掉485硬件产生的0x00的接收数据
            for(; i < leftlen - 1; i++)
            {
                if(pMsg[i] == XINGHENG_START_FLAG)
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
                msg = (MSG_HEADER_XINGHENG_BMS*)(pMsg + i);
            }
        }

        if(!BMS_XingHeng_isBMSCheckSumPass(msg)) //如果数据包校验错误，则认为整个接收数据都不可信，可以直接丢弃
        {
            break;
        }
        vaild = 1;
        BMS_XingHeng_procOneMsg((u8 *)msg, msg->length + MSG_HEADER_XINGHENG_BMS_LEN + 1);
        leftlen = leftlen - (msg->length + MSG_HEADER_XINGHENG_BMS_LEN + 1);
        msg = (MSG_HEADER_XINGHENG_BMS *)(data + length - leftlen);
		if(++proctimes > 5)
		{
			LOG_ERROR("[etc] MSG_HEADER_XINGHENG_BMS break");
			return L_FALSE;
		}
    }
    if(vaild == 1)
    {
        return L_TRUE;
    }
    return L_FALSE;
}

L_BOOL BMS_XingHeng_isBMSCheckSumPass(MSG_HEADER_XINGHENG_BMS *cmdData)
{
    u8 i = 0;
    u16 checksum = 0;
    u16 cmdDataChecksum = 0;
    
    if(0X16 != cmdData->address)
    {
        return L_FALSE;
    }

    if(0X3A != cmdData->signature)
    {
        return L_FALSE;
    }

    checksum = cmdData->address;
    checksum += cmdData->cmd;
    checksum += cmdData->length;
    for(i = 0; i < cmdData->length; i++)
    {
        checksum += cmdData->data[i];
    }

    cmdDataChecksum = cmdData->data[cmdData->length + 1];
    cmdDataChecksum = cmdDataChecksum << 8;
    cmdDataChecksum |= cmdData->data[cmdData->length];
    if(checksum != cmdDataChecksum)
    {
        return L_FALSE;
    }

    if(cmdData->data[cmdData->length + 2] != 0x0d || cmdData->data[cmdData->length + 3] != 0x0a)
    {
        return L_FALSE;
    }

    return L_TRUE;
}

static int BMS_XingHeng_getBMSVersionAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_VERSION, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSSNAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_SN, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSCapacityAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_CAPACITY, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSCyclesAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_CIRCLE_TIMES, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSHealthAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_HEALTH, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSRemainAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_REMAIN, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSTemperatureAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_TEMPERATURE, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSPercent_REAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_POWER_PERCENT_RE, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSCurrentAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_CURRENT, &data, sizeof(u8));
    return 0;
}

static int BMS_XingHeng_getBMSVoltageAction(void)
{
    u8 data = 0;
    BMS_XingHeng_sendBMSDATA(CMD_BMS_GET_VOLTAGE, &data, sizeof(u8));
    return 0;
}

//星恒BMS数据响应
static int BMS_XingHeng_getTemperature_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = ( MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 2)
    {
        return L_FALSE;
    }

    pData->bms.temperature = (u16)((msg->data[1]<<8) | msg->data[0]) - 2731;
    LOG_INFO("BMS-> temperature is:%d", pData->bms.temperature);
    return L_TRUE;
}

static int BMS_XingHeng_getVoltage_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 2)
    {
        return L_FALSE;
    }
    
    pData->bms.voltage = (u16)((msg->data[1]<<8) | msg->data[0]);
    LOG_INFO("BMS-> voltage is:%d",pData->bms.voltage);
    return L_TRUE;
}

static int BMS_XingHeng_getCurrent_rsp(uint8_t *data)
{
    static int lastSOC = 0;
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 2)
    {
        return L_FALSE;
    }

    //如果获取到的SOC的变化超过2的话, 主动上报一次
    if(pData->bms.SOC != lastSOC)
    {
        int SOC = pData->bms.SOC;
        if(abs(lastSOC - SOC) >= 2)
        {
            data_getData()->socFluct = L_TRUE;
            lastSOC = SOC;//确定上报了, 更新一下历史数据
        }
    }
    
    if(setting.statusConf.bmsSoc != data_getData()->bms.SOC)
    {
        setting.statusConf.bmsSoc = data_getData()->bms.SOC;
        statusConf_save(); //保存BMS电量
    }
    pData->bms.current = (s16)((msg->data[1]<<8) | msg->data[0]);
    LOG_INFO("BMS-> current is:%d", pData->bms.current);
    return L_TRUE;
}

static int BMS_XingHeng_getHealth_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 2)
    {
        return L_FALSE;
    }

    pData->bms.health = msg->data[0];
    LOG_INFO("BMS-> health is:%d", pData->bms.health);
    return L_TRUE;
}

static int BMS_XingHeng_getPowerPercentRelative_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 1)
    {
        return L_FALSE;
    }

    pData->bms.SOC = msg->data[0];
    if(setting.statusConf.bmsSoc != data_getData()->bms.SOC)
    {
        setting.statusConf.bmsSoc = data_getData()->bms.SOC;
        statusConf_save(); //保存BMS电量
    }
    LOG_INFO("BMS-> SOC is:%d", pData->bms.SOC);
    return L_TRUE;
}

static int BMS_XingHeng_getRemain_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 2)
    {
        return L_FALSE;
    }
    
    pData->bms.remainCapacity = (u16)((msg->data[1]<<8) | msg->data[0]);
    LOG_INFO("BMS-> remainCapacity is:%d",pData->bms.remainCapacity);
    return L_TRUE;
}

static int BMS_XingHeng_getCapacity_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 2)
    {
        return L_FALSE;
    }

    pData->bms.capacity = (u16)((msg->data[1]<<8) | msg->data[0]);
    LOG_INFO("BMS-> capacity is:%d",pData->bms.capacity);
    return L_TRUE;
}

static int BMS_XingHeng_getCircleTimes_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 2)
    {
        return L_FALSE;
    }

    pData->bms.cycleCount = (u16)((msg->data[1]<<8) | msg->data[0]);
    LOG_INFO("BMS-> cycleCount is:%d",pData->bms.cycleCount);
    return L_TRUE;
}
static int BMS_XingHeng_getVersion_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 3)
    {
        return L_FALSE;
    }
    pData->bms.softwareVer = msg->data[1];
    pData->bms.hardwareVer = msg->data[2];
    LOG_INFO("BMS-> softwareVer is:%d", pData->bms.softwareVer);
    LOG_INFO("BMS-> hardwareVer is:%d", pData->bms.hardwareVer);
    return L_TRUE;
}

static int BMS_XingHeng_getSN_rsp(uint8_t *data)
{
    MSG_HEADER_XINGHENG_BMS *msg = (MSG_HEADER_XINGHENG_BMS *)data;
    DATA *pData = data_getData();
    if(msg->length < 16 || msg->length >= MAX_BMS_SN_LEN)
    {
        return L_FALSE;
    }

    memcpy((void *)pData->bms.SN, msg->data, msg->length);
    LOG_INFO("BMS-> SN: %s", pData->bms.SN);
    LOG_HEX(pData->bms.SN, MAX_BMS_SN_LEN);
    return L_TRUE;
}

/**************************************************** 星恒BMS ************************************************************/
void BMS_XingHeng_getBMSVersion(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_VERSION, BMS_XingHeng_getBMSVersionAction, BMS_XingHeng_getVersion_rsp, NULL);
}
void BMS_XingHeng_getBMSSN(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_SN, BMS_XingHeng_getBMSSNAction, BMS_XingHeng_getSN_rsp, NULL);
}
void BMS_XingHeng_getBMSCapacity(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_CAPACITY, BMS_XingHeng_getBMSCapacityAction, BMS_XingHeng_getCapacity_rsp, NULL);
}
void BMS_XingHeng_getBMSCycles(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_CIRCLE_TIMES, BMS_XingHeng_getBMSCyclesAction, BMS_XingHeng_getCircleTimes_rsp, NULL);
}
void BMS_XingHeng_getBMSHealth(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_HEALTH, BMS_XingHeng_getBMSHealthAction, BMS_XingHeng_getHealth_rsp, NULL);
}
void BMS_XingHeng_getBMSRemain(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_REMAIN, BMS_XingHeng_getBMSRemainAction, BMS_XingHeng_getRemain_rsp, NULL);
}
void BMS_XingHeng_getBMSTemperature(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_TEMPERATURE, BMS_XingHeng_getBMSTemperatureAction, BMS_XingHeng_getTemperature_rsp, NULL);
}
void BMS_XingHeng_getBMSPercent_RE(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_POWER_PERCENT_RE, BMS_XingHeng_getBMSPercent_REAction, BMS_XingHeng_getPowerPercentRelative_rsp, NULL);
}
void BMS_XingHeng_getBMSCurrent(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_CURRENT, BMS_XingHeng_getBMSCurrentAction, BMS_XingHeng_getCurrent_rsp, NULL);
}
void BMS_XingHeng_getBMSVoltage(void)
{
    etcMsg_setETCHandler(XH_BMS_ADDRESS, CMD_BMS_GET_VOLTAGE, BMS_XingHeng_getBMSVoltageAction, BMS_XingHeng_getVoltage_rsp, NULL);
}

static const XINGHENG_BMS_DATA_LOOP_MAP xinghengBmsDataLoopMap[] = 
{
    {BMS_XingHeng_getBMSVersion}, //0x7f
    {BMS_XingHeng_getBMSSN}, //0x7e
    {BMS_XingHeng_getBMSVoltage}, //0x09
    {BMS_XingHeng_getBMSPercent_RE}, //0x0d
    {BMS_XingHeng_getBMSCapacity}, //0x10
    {BMS_XingHeng_getBMSRemain}, //0x0f
    {BMS_XingHeng_getBMSHealth}, //0x0c
    {BMS_XingHeng_getBMSCycles},
    {BMS_XingHeng_getBMSTemperature},
    {BMS_XingHeng_getBMSCurrent},
};

void BMS_XingHeng_getBMSDataLoop(void)
{
    static u8 i = 0;
    if(i >= sizeof(xinghengBmsDataLoopMap) / sizeof(xinghengBmsDataLoopMap[0]))
    {
        i = 0;
    }
    if(xinghengBmsDataLoopMap[i].fun)
    {
        xinghengBmsDataLoopMap[i].fun();
    }
    i++;
}

int BMS_XingHeng_sendBMSDATA(u8 cmd, u8 *data, u8 dataLen)
{
    u8 *pData = BMS_XingHeng_getBMSData(cmd, data, dataLen);
    da14580_sendUartData((u8 *)pData, sizeof(MSG_HEADER_XINGHENG_BMS) + dataLen + 4);
    return L_TRUE;
}

void BMS_XingHeng_Initial(void)
{
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_VERSION, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_SN, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_CAPACITY, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_CIRCLE_TIMES, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_HEALTH, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_POWER_PERCENT_RE, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_REMAIN, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_TEMPERATURE, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_CURRENT, NULL, NULL, NULL, L_FALSE);
    etcMsg_setAsyncHandler(XH_BMS_ADDRESS, CMD_BMS_GET_VOLTAGE, NULL, NULL, NULL, L_FALSE);
}

