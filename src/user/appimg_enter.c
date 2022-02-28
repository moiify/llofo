/* Copyright (C) 2018 RDA Technologies Limited and/or its affiliates("RDA").
 * All rights reserved.
 *
 * This software is supplied "AS IS" without any warranties.
 * RDA assumes no responsibility or liability for the use of the software,
 * conveys no license or title under any patent, copyright, or mask work
 * right to the product. RDA reserves the right to make changes in the
 * software without notification.  RDA also make no representation or
 * warranty that such application will be suitable for the specified use
 * without further testing or modification.
 */

#define OSI_LOG_TAG OSI_MAKE_LOG_TAG('M', 'Y', 'A', 'P')

#include "fibo_opencpu.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "main.h"
#include "socket.h"
#include "user_at.h"
#include "user_timer.h"
#include "soft_watchdog.h"

static FIBO_CALLBACK_T user_callback = 
{
    .fibo_signal = socket_sig_callback,
    .at_resp = at_res_callback
};

static void prvInvokeGlobalCtors(void)
{
    extern void (*__init_array_start[])();
    extern void (*__init_array_end[])();

    size_t count = __init_array_end - __init_array_start;
    for (size_t i = 0; i < count; ++i)
    {
        __init_array_start[i]();
    }
}

void *appimg_enter(void *param)
{
    OSI_LOGI(0, "application image enter, param 0x%x", param);

    prvInvokeGlobalCtors();

    fibo_thread_create(mainThreadEntry, "mainThreadEntry", 50 * 1024, NULL, OSI_PRIORITY_NORMAL);
    fibo_thread_create(timer_threadhandler, "AppTimer", 80 * 1024, NULL, OSI_PRIORITY_NORMAL);
	fibo_thread_create(socket_ConnectThread, "SocketConnect", 20*1024, NULL, OSI_PRIORITY_BELOW_NORMAL);
	fibo_thread_create(softwatchdog_Thread, "SoftWatchDog", 5*1024, NULL, OSI_PRIORITY_BELOW_NORMAL);
    return (void *)&user_callback;
}

void appimg_exit(void)
{
    OSI_LOGI(0, "application image exit");
}

