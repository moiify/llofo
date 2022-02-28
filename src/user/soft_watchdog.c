/*
 * user_watchdog.c
 *
 *  Created on:  2020.08.31
 *      Author: zsd
 */
#include "fibo_opencpu.h"
#include "protocol.h"
#include "soft_watchdog.h"
#include "setting.h"
#include "socket.h"
#include "log.h"
#include "msg.h"

int watchdog_time[REBOOT_TYPEMAX] = {0}; //喂狗时间
char record[REBOOT_TYPEMAX] = {0};   //记录开启哪路看门狗
int reboot_time[REBOOT_TYPEMAX] = {0}; //记录开启的那路看门狗的重启时间，单位是s

void softwatchdog_feed(char type)
{
    if(type < 0 || type > REBOOT_TYPEMAX)
    {
        LOG_DEBUG("[SoftWD] REBOOT_TYPE is illegal");
        return;
    }
    for(int i = 0; i < REBOOT_TYPEMAX; i++)
    {
        if(type == i)
        {
            watchdog_time[i] = 0;
            return;
        }
    }
}

void softwatchdog_start(char type, unsigned int time)  //时间单位为s
{
    if(type < 0 || type > REBOOT_TYPEMAX)
    {
        LOG_DEBUG("[SoftWD] start type is illegal");
        return;
    }
    for(int i = 0; i < REBOOT_TYPEMAX; i++)
    {
        if(type == i)
        {
            record[i] = 1;
            reboot_time[i] = time;
            watchdog_time[i] = 0;
            LOG_DEBUG("[SoftWD] %dStart, %ds", type, time);
            return;
        }
    }
}

void softwatchdog_stop(char type)
{
    if(type < 0 || type > REBOOT_TYPEMAX)
    {
        LOG_DEBUG("[SoftWD] stop type is illegal");
        return;
    }
    for(int i = 0; i < REBOOT_TYPEMAX; i++)
    {
        if(type == i)
        {
            record[i] = 0;
            return;
        }
    }
}

int Watchdog_handle(void)
{
    for(int i = 0; i < REBOOT_TYPEMAX; i++)
    {
        watchdog_time[i]++;
        if((watchdog_time[i] >= reboot_time[i]) && (record[i] == 1))   //此路看门狗超时而且被启动，则重启系统
        {
            LOG_DEBUG("[SoftWD] The system is abnormal, type is %d", i);
            if (record[i] != REBOOT_NETWORK)   //如果非网络故障导致重启，上报状态
            {
                MSG_SOFTWATCHDOG_REQ* watchdog_msg = alloc_msg(CMD_WATCHDOG_INFO, sizeof(MSG_SOFTWATCHDOG_REQ));
                if (!watchdog_msg)
                {
                    LOG_ERROR("[SoftWD] alloc message failed!");
                    //return -1;
                }
                watchdog_msg->WatchDog_Type = i;
                //socket_sendDataDirectly(watchdog_msg, sizeof(MSG_SOFTWATCHDOG_REQ));
            }
            setting_setRebootType(i);
            fibo_taskSleep(1000);
            fibo_softReset();
        }
    }
    return 0;
}

void softwatchdog_Thread(void *argument)
{
    osiThreadSetFPUEnabled(true); //线程使能FPU
    
    while(1)
    {
        Watchdog_handle();
        fibo_taskSleep(1000);
    }
    fibo_thread_delete();
}

void softwatchdog_Init(void)
{
	softwatchdog_start(REBOOT_NETWORK, 300); //网络状态看门狗        5分钟
}

