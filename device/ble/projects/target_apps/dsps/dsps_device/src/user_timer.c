/*
 * user_timer.c
 *
 *  Created on: 2018/7/13
 *      Author: lc
 */

#include "user_timer.h"

#include "ble_proc.h"

static volatile uint64_t timer_10ms_count = 0;

static volatile TIMER_STRUCT timer_handler[TIMER_NUM];

int app_user_timer_handler (ke_msg_id_t const msgid,
                                         void const *param,
                                         ke_task_id_t const dest_id,
                                         ke_task_id_t const src_id)
{    
    timer_10ms_count++;

    if(timer_10ms_count == 1)
    {
        timer_startRepeat(TIMER_ONESECOND_LOOP, 1000, ble_proc_timer);
    }
    
    for(uint8_t i = 0; i < TIMER_NUM; i++)
    {
        if(TIMER_START == timer_handler[i].isStart)
        {
            if(timer_handler[i].isRepeat)
            {
                if(timer_10ms_count % timer_handler[i].period == 0 && timer_handler[i].pFun)
                {
                    TIMER_CB pFun;
                    pFun = timer_handler[i].pFun;
                    pFun();
                }
            }
            else if(timer_10ms_count >= timer_handler[i].count)
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

    app_timer_set(APP_TIMER_USER_MES, TASK_APP, 1);
    return (KE_MSG_CONSUMED);
}


int timer_startRepeat(TIMER_ENUM id, uint32_t period, TIMER_CB pFun)
{
    timer_handler[id].isRepeat = TRUE;
    timer_handler[id].period = period / 10;
    timer_handler[id].pFun = pFun;
    timer_handler[id].isStart = TIMER_START;
    return 0;
}


int timer_start(TIMER_ENUM id, uint32_t period, TIMER_CB pFun)
{
    timer_handler[id].isRepeat = FALSE;
    timer_handler[id].count = timer_10ms_count + period / 10;
    timer_handler[id].pFun = pFun;
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
    return timer_handler[id].isStart;
}

int timer_isSleep(void)
{
    for(uint8_t i = 0; i < TIMER_NUM; i++)
    {
        if(timer_isTimerStart((TIMER_ENUM)i))
        {
            return 0;
        }
    }

    return 1;
}

