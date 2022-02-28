/*
 * async.c
 *
 *  Created on: 2018/06/03
 *      Author: lc
 */
#include "log.h"
#include "types.h"
#include "async.h"
#include "ETC_TaiBite.h"
#include "ETC_XiaoAn.h"
#include "BMS_XingHeng.h"
#include "RFID.h"

int async_procMsg(uint8_t *data,ASYNC_PROC_MAP eventProcs[], int size)
{
    int i = 0;

    if(ETC_XiaoAn_IsCheckSumPass((MSG_HEADER_XIAOAN_ETC *)data))
    {
        MSG_HEADER_XIAOAN_ETC *etcMsg = (MSG_HEADER_XIAOAN_ETC *)data;
        for(i = 0; i < size; i++)
        {
            if(eventProcs[i].cmd == etcMsg->cmd && eventProcs[i].address == etcMsg->address)
            {

                break;
            }
        }
    }
    else if(ETC_TaiBiTe_IsCheckSumPass((MSG_HEADER_TAIBITE *)data))
    {
        MSG_HEADER_TAIBITE *taibiteMsg = (MSG_HEADER_TAIBITE *)data;
        for(i = 0; i < size; i++)
        {
            if(eventProcs[i].cmd == taibiteMsg->cmd  && eventProcs[i].address == taibiteMsg->address)
            {
                break;
            }
        }
    }
    else if(BMS_XingHeng_isBMSCheckSumPass((MSG_HEADER_XINGHENG_BMS *)data))
    {
        MSG_HEADER_XINGHENG_BMS *xinghengMsg = (MSG_HEADER_XINGHENG_BMS *)data;
        for(i = 0; i < size; i++)
        {
            if(eventProcs[i].cmd == xinghengMsg->cmd  && eventProcs[i].address == xinghengMsg->address)
            {
                break;
            }
        }
    }
    else if(async_isRFIDCheckSumPass((DA14580_RFID485_MSG *)data))
    {
        DA14580_RFID485_MSG *rfidMsg = (DA14580_RFID485_MSG *)data;
        for(i = 0; i < size; i++)
        {
            if(eventProcs[i].address == 0xFF && eventProcs[i].cmd == rfidMsg->cmd) //匹配RFID
            {
                break;
            }
        }
    }

    if(i < size && eventProcs[i].actionTimes) //需要保证本次消息发送过至少一次
    {
        ASYNC_MSG_PROC msgProc = eventProcs[i].msgProc;
        ASYNC_RESPONSE_PROC responseAction = eventProcs[i].responseAction;
        eventProcs[i].time = 0;
        eventProcs[i].actionTimes = 0;
        eventProcs[i].param = NULL;
        eventProcs[i].action = NULL;
        eventProcs[i].responseAction = NULL;

        if(msgProc)
        {
            //如果需要数据处理 进行数据处理
            msgProc(data);
        }

        if(responseAction)
        {
            //如果需要响应处理 进行响应处理 在响应事件里可以重启事件
            responseAction(RESULT_OK, eventProcs[i].param);
        }
    }

    return 0;
}

//0XAA, 0X55,0X10,0X11,0X0D,0X01,0X20,0X00,0X02,0X00,0X03,0X00,0X28,0X11,0X00,0X12,0X00,0X00,0X9F
int async_procTimeout(ASYNC_PROC_MAP eventProcs[], int size)
{
    int i = 0;
    for(i = 0; i < size; i++)
    {
        ASYNC_PROC action = eventProcs[i].action;
        if(action)
        {
            if(!eventProcs[i].isWaitRsp)
            {
                // 如果不需要保证通信 不等待回复 不进行重复发送 发送完置空
                eventProcs[i].action = NULL;
                eventProcs[i].actionTimes++;
                return action();
            }

            if(eventProcs[i].time-- > 0) //200ms 执行一次命令的超时判断 time为次数
            {
                eventProcs[i].actionTimes++;
                return action();
            }
            else
            {
                ASYNC_RESPONSE_PROC responseAction = eventProcs[i].responseAction;
                void *param = eventProcs[i].param;
                eventProcs[i].time = 0;
                eventProcs[i].actionTimes = 0;
                eventProcs[i].param = NULL;
                eventProcs[i].action = NULL;
                eventProcs[i].responseAction = NULL;
                if(responseAction)
                {
                    //如果需要超时处理 进行超时处理 超时处理里面可以重启事件
                    responseAction(RESULT_TIMEOUT, param);
                }
            }
        }
    }

    return -1;
}

