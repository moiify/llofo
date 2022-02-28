/*
 * userMsg.c
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */
#include "fibo_opencpu.h"
#include "types.h"
#include "userMsg.h"
#include "request.h"
#include "user_timer.h"
#include "userMsg.h"
#include "data.h"
#include "protocol.h"
#include "request.h"

static u8 g_event[EVENT_NUM];
static u8 g_alarmType[ALARM_NUM];

void userMsg_setEvent(EVENT_TYPE event, u8 type)
{
    if(event == EVENT_ALARM)
    {
        g_alarmType[type] = L_TRUE;
    }

    g_event[event] = L_TRUE;
}

static int userMsg_alarmMsg_proc(void)
{
    u8 i = 0;
    for(i = 0; i < ALARM_NUM; i++)
    {
        if(g_alarmType[i])break;
    }

    if(i >= ALARM_NUM) //告警处理完毕后返回0
    {
        return 0;
    }

    cmd_alarm(i);

    g_alarmType[i] = L_FALSE;
    return -1;
}

static int userMsg_event_proc(void)
{
    u8 i = 0;
    for(i = 0; i < EVENT_NUM; i++)
    {
        if(g_event[i])break;
    }

    if(i >= EVENT_NUM)
    {
        return -1;
    }

    switch(i)
    {
        case EVENT_ALARM:
        if(0 == userMsg_alarmMsg_proc())
        {
            //处理过告警上报, 其他的Pass
            g_event[EVENT_ALARM] = L_FALSE; //告警处理完后才置空
        }
        break;
        
        case EVENT_SENDSTATUS:
        {
            cmd_status();
            g_event[EVENT_SENDSTATUS] = L_FALSE;
        }
        break;
        
        case EVENT_SENDBMSINFO:
        {
            cmd_submitBMSInfo();
            g_event[EVENT_SENDBMSINFO] = L_FALSE;
        }
        break;
        
        default:
            break;
    }
    return 0;
}

void userMsg_initail(void)
{
    timer_startRepeat(TIMER_EVENT_PROC, TIMER_MS, 200, userMsg_event_proc);
}

