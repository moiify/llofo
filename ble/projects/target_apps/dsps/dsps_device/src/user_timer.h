/*
 * user_timer.h
 *
 *  Created on: 2018/7/13
 *      Author: lc
 */

#ifndef __USER_TIMER_H__
#define __USER_TIMER_H__
#include <stdint.h>

#include "ke_timer.h"

#include "app_api.h"

typedef enum
{
    TIMER_ONESECOND_LOOP,
    TIMER_UART1_RX_TIMEOUT,
    TIMER_UART2_RX_TIMEOUT,
    TIMER_ENABLE_VBUS,
    TIMER_ENABLE_SP4502,
    TIMER_AWAKE_SIMCOM,
	TIMER_RESTTEST,
	TIMER_SCAN_TIMEOUT,    
	TIMER_RENEW_BEACON,
    TIMER_NUM,
} TIMER_ENUM;

typedef enum
{
    TIMER_STOP,
    TIMER_START,
}TIMER_STATE;

typedef enum
{
    FALSE,
    TRUE,
}TIMER_BOOL;

typedef int (*TIMER_CB)(void);

typedef struct
{
    uint8_t isRepeat;
    uint8_t isStart;
    uint32_t period;
    uint32_t count;
    TIMER_CB pFun;
} TIMER_STRUCT;

int timer_stop(TIMER_ENUM id);
int timer_start(TIMER_ENUM id, uint32_t period, TIMER_CB pFun);
int timer_startRepeat(TIMER_ENUM id, uint32_t period, TIMER_CB pFun);

int timer_isSleep(void);

int timer_isTimerStart(TIMER_ENUM id);

int app_user_timer_handler (ke_msg_id_t const msgid,
                                         void const *param,
                                         ke_task_id_t const dest_id,
                                         ke_task_id_t const src_id);

#endif// __USER_TIMER_H__

