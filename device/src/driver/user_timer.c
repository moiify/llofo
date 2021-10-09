/*
 * user_timer.c
 *
 *  Created on: 2020.04.03
 *      Author: lc
 */
#include "fibo_opencpu.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "data.h"
#include "types.h"
#include "user_timer.h"


static uint32_t g_pTimer_2m = 0;
static uint32_t g_pTimer_1s = 0;
static uint32_t g_pTimer_10ms = 0;

static uint8_t g_isTimerSleep = 0;

static TIMER_STRUCT timer_handler[TIMER_NUM] = {0};

static uint64_t timer_10ms_count = 0;
static volatile uint8_t timer_10ms_update = 0;  //相当于事件组里的一个事件
static void timer_10ms_handler(void *arg)
{
    timer_10ms_count++;
	timer_10ms_update = 1;

}

static uint32_t timer_1s_count = 0;
static volatile uint8_t timer_1s_update = 0;
static void timer_1s_handler(void *arg)
{
    timer_1s_count++;
	timer_1s_update = 1;
}

static uint32_t timer_2m_count = 0;
static volatile uint8_t timer_2m_update = 0;
static void timer_2m_handler(void *arg)
{
    timer_2m_count++;
    timer_2m_update = 1;
}

int timer_startRepeat(TIMER_ENUM id, TIMER_TYPE type, uint32_t period, TIMER_CB pFun)
{
    timer_handler[id].isRepeat = 1;
    switch(type)
    {
        case TIMER_MS:
            timer_handler[id].period = (period + 9) / 10;
            break;

        case TIMER_S:
            timer_handler[id].period = period;
            break;

        case TIMER_M:
            timer_handler[id].period = (period + 1) / 2;
            break;

        default:
            break;
    }
    
    timer_handler[id].pFun = pFun;
    timer_handler[id].type = type;
    timer_handler[id].isStart = TIMER_START;
    return 0;
}


int timer_start(TIMER_ENUM id, TIMER_TYPE type, uint32_t period, TIMER_CB pFun)
{
    timer_handler[id].isRepeat = 0;
    switch(type)
    {
        case TIMER_MS:
            timer_handler[id].count = timer_10ms_count + (period < 20 ? (20 / 10) : ((period + 9) / 10));
            break;

        case TIMER_S:
            timer_handler[id].count = timer_1s_count + (period < 2 ? 2 : period);
            break;

        case TIMER_M:
            timer_handler[id].count = timer_2m_count + (period < 4 ? (4 / 2) : ((period + 1) / 2));
            break;

        default:
            break;
    }
    
    timer_handler[id].pFun = pFun;
    timer_handler[id].type = type;
    timer_handler[id].isStart = TIMER_START;
    return 0;
}

int timer_stop(TIMER_ENUM id)
{
    timer_handler[id].isStart = TIMER_STOP;
    return 0;
}

int timer_isTimerStart(TIMER_ENUM id)
{
    if(timer_handler[id].isStart)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int timer_isTimerSleep(void)
{
    uint8_t i = 0;
    for(; i < TIMER_NUM; i++)
    {
        if(!timer_handler[i].isRepeat && timer_handler[i].isStart)
        {
            if(i == TIEMR_BLE_UART || i == TIEMR_GPS_UART) //此定时器为收到串口消息后启动，实际为周期性质，不能影响休眠进入
            {
                continue;
            }
            return i;
        }
    }
    return i;
}

int timer_enableSleep(uint8_t isSleep)
{
    g_isTimerSleep = isSleep;
    if(g_isTimerSleep)
    {
        if(g_pTimer_10ms)
        {
            fibo_timer_free(g_pTimer_10ms);
            g_pTimer_10ms = 0;
        }
        if(g_pTimer_1s)
        {
            fibo_timer_free(g_pTimer_1s);
            g_pTimer_1s = 0;
        }
    }
    else
    {
        if(!g_pTimer_1s)g_pTimer_1s = fibo_timer_period_new(TIMER_ONESECOND_LOOP_PERIOD, timer_1s_handler, NULL);
        if(!g_pTimer_10ms)g_pTimer_10ms = fibo_timer_period_new(TIMER_10MS_LOOP_PERIOD, timer_10ms_handler, NULL);
    }
    return 0;
}


void timer_initial(void)
{
    if(g_pTimer_2m)
    {
        fibo_timer_free(g_pTimer_2m);
        g_pTimer_2m = 0;
    }
    if(g_pTimer_1s)
    {
        fibo_timer_free(g_pTimer_1s);
        g_pTimer_1s = 0;
    }
    if(g_pTimer_10ms)
    {
        fibo_timer_free(g_pTimer_10ms);
        g_pTimer_10ms = 0;
    }

    g_pTimer_2m = fibo_timer_period_new(TIMER_LONGTIME_LOOP_PERIOD, timer_2m_handler, NULL);
    g_pTimer_1s = fibo_timer_period_new(TIMER_ONESECOND_LOOP_PERIOD, timer_1s_handler, NULL);
    g_pTimer_10ms = fibo_timer_period_new(TIMER_10MS_LOOP_PERIOD, timer_10ms_handler, NULL);
}

void timer_threadhandler(void *argument)
{
    osiThreadSetFPUEnabled(true); //定时器线程使能FPU

    while(true)
    {
        u8 i = 0;

        {
            static uint64_t tenMS_count = 0;

            if(timer_10ms_update)
            {
                while(tenMS_count < timer_10ms_count)
                {
					for(i = 0; i < TIMER_NUM; i++)
					{
						if(TIMER_MS == timer_handler[i].type && TIMER_START == timer_handler[i].isStart)
						{
							if(timer_handler[i].isRepeat)
							{
								if(tenMS_count % timer_handler[i].period == 0 && timer_handler[i].pFun)
								{
									TIMER_CB pFun;
									pFun = timer_handler[i].pFun;
									pFun();
								}
							}
							else if(tenMS_count >= timer_handler[i].count)
							{
								timer_handler[i].isStart = TIMER_STOP;
								if(timer_handler[i].pFun)
								{
									TIMER_CB pFun;
									pFun = timer_handler[i].pFun;
									timer_handler[i].pFun = NULL;
									pFun();
								}
							}
						}
					}
                    tenMS_count++;
                }
                timer_10ms_update = 0;
            }
        }

        {
            static uint64_t oneS_count = 0;
            if(timer_1s_update)
            {
                while(oneS_count < timer_1s_count)
                {
					for(i = 0; i < TIMER_NUM; i++)
					{
						if(TIMER_S == timer_handler[i].type && TIMER_START == timer_handler[i].isStart)
						{
							if(timer_handler[i].isRepeat)
							{
								if(oneS_count % timer_handler[i].period == 0 && timer_handler[i].pFun)
								{
									TIMER_CB pFun;
									pFun = timer_handler[i].pFun;
									pFun();
								}
							}
							else if(oneS_count >= timer_handler[i].count)
							{
								timer_handler[i].isStart = TIMER_STOP;
								if(timer_handler[i].pFun)
								{
									TIMER_CB pFun;
									pFun = timer_handler[i].pFun;
									timer_handler[i].pFun = NULL;
									pFun();
								}
							}
						}
					}
                    oneS_count++;
                }
                timer_1s_update = 0;
            }
        }

        {
            static uint64_t towM_count = 0;
            if(timer_2m_update)
            {
                while(towM_count < timer_2m_count)
                {
					for(i= 0; i < TIMER_NUM; i++)
					{
						if(TIMER_M == timer_handler[i].type && TIMER_START == timer_handler[i].isStart)
						{
							if(timer_handler[i].isRepeat)
							{
								if(towM_count % timer_handler[i].period == 0 && timer_handler[i].pFun)
								{
									TIMER_CB pFun;
									pFun = timer_handler[i].pFun;
									pFun();
								}
							}
							else if(towM_count >= timer_handler[i].count)
							{
								timer_handler[i].isStart = TIMER_STOP;
								if(timer_handler[i].pFun)
								{
									TIMER_CB pFun;
									pFun = timer_handler[i].pFun;
									timer_handler[i].pFun = NULL;
									pFun();
								}
							}
						}
					}
                    towM_count++;
                }
                timer_2m_update = 0;
            }
        }
        if(!data_isSleeping())
        {
            fibo_taskSleep(5);
        }
        else
        {
            fibo_taskSleep(1000);
        }
    }
}


unsigned long long timer_getTimerCount(TIMER_TYPE type)
{
    if(type == TIMER_MS)
    {
        return (unsigned long long)timer_10ms_count;
    }
    else if(type == TIMER_S)
    {
        return (unsigned long long)timer_1s_count;
    }
    else if(type == TIMER_M)
    {
        return (unsigned long long)timer_2m_count;
    }
    return 0;
}

