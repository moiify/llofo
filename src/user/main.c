
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

#include "cJSON/cJSON.h"

#include "log.h"
#include "msg.h"
#include "adc.h"
#include "data.h"
#include "uart.h"
#include "audio.h"
#include "audio_driver.h"
#include "detect.h"
#include "lis3dh.h"
#include "socket.h"
#include "device.h"
#include "detect.h"
#include "da14580.h"
#include "version.h"
#include "userMsg.h"
#include "setting.h"
#include "response.h"
#include "hardware.h"
#include "gps_parse.h"
#include "user_debug.h"
#include "user_timer.h"
#include "user_at.h"
#include "event.h"
#include "sleep.h"
#include "diagnosis.h"
#include "etcMsg.h"
#include "watchdog.h"
#include "agps.h"
#include "request.h"
#include "utils.h"
#include "figlet.h"
#include "soft_watchdog.h"
#include "display_log.h"
#include "accelerometer.h"

static void cJson_initial(void)
{
    cJSON_Hooks mem_hooks;
    mem_hooks.malloc_fn = Malloc;
    mem_hooks.free_fn = Free;
    cJSON_InitHooks(&mem_hooks);//initial the cJSON memory hook
}

static ATResult_enum setting_getCoreVersionCb(uint8_t isTimeout,char *buf, u16 len)
{
    if(isTimeout)
    {
        LOG_ERROR("[setting] FiboCoreVersion get timeout ");
        return AT_RES_FINISHED;
    }
    if(strstr((const char *)buf, "ERROR") || strstr((const char *)buf, "OK"))
    {
        u8 * platform = string_bypassByNum((const char *)buf, "\r", 3) + 1;
        if(platform)
        {
            u16 platform_offset = strstr((const char *)platform, "-") - (const char *)platform;
            memcpy(setting.platform, platform, platform_offset);
            LOG_DEBUG("[setting] Platform = %s", setting.platform);
        }
        u8 *pbuf = (u8 *)string_bypass((const char *)buf, "16000");
        if(pbuf)
        {
            u8 *pBase = (u8 *)string_bypassByNum((const char *)pbuf, ".", 3);
            u8 *pProject = (u8 *)string_bypassByNum((const char *)pbuf, ".", 4);
            u8 *pMin = (u8 *)string_bypassByNum((const char *)pbuf, ".", 5);
            if(pBase && pProject && pMin)
            {
                setting.coreVersion = (atoi((const char *)pBase) << 16 | atoi((const char *)pProject) << 8 | atoi((const char *)pMin) );
                LOG_DEBUG("[setting] FiboCoreVersion = %d.%d.%d",setting.coreVersion >>16 & 0xff, setting.coreVersion >>8 & 0xff, setting.coreVersion & 0xff);
                if(setting_isCoreUnmatch() == L_TRUE)  //?????????????????????SDK,?????????????????????????????????????????????
                {
                    timer_startRepeat(TIMER_CHECKCORE_LOOP, TIMER_M, DETECT_CORE_PERIOD, detect_systemCore_handler);
                }
                return AT_RES_FINISHED;
            }
        }
        LOG_ERROR("[setting] FiboCoreVersion get failed ");
        return AT_RES_FINISHED;
    }
    else if(strstr((const char *)buf, "ati"))
    {
        return AT_RES_CONTRINUE;
    }

    return AT_RES_CONTRINUE; // need ERROR or OK
}

static void main_PresEt_AT(void)
{
    at_run("ATE1\r",at_default_cb);
    at_run("AT+CMGF=1\r", at_default_cb);          //??????????????????
    at_run("AT+CNMI=2,1,0,0,0\r", at_default_cb);  //??????????????????????????????
    at_run("AT+TLPG=0\r",at_default_cb);           //????????????????????? NC
    at_run("AT+GTSET=\"GDB\",1\r",at_default_cb);  //??????open???????????????????????????GDB
    at_runwithTimeout("ati\r", setting_getCoreVersionCb, 3);//??????????????????
}

static void main_LogUI(void)
{
    uart_print("\r\n");
    figlet_PrintStr("XIAOANTECH");
    uart_print("\r\n\r\n");
    uart_print("                                              Copyright 2020 XiaoAn Technology\r\n\r\n");
    uart_print("firmware version : %s\r\n", VERSION_STR);
    uart_print("firmware build_time : %s %s\r\n", __DATE__, __TIME__);
    uart_print("\r\n");
}

static void timer_patch(void)
{
    //patch ??????????????????????????????, ????????????????????????
    if(!data_isSleeping())
    {
        static u32 count = 0;
        static u64 last_s_timer_count = 0;
        static u64 last_ms_timer_count = 0;
        if(last_s_timer_count != timer_getTimerCount(TIMER_S)
        && last_ms_timer_count != timer_getTimerCount(TIMER_MS))
        {
            count = 0;
            last_s_timer_count = timer_getTimerCount(TIMER_S);
            last_ms_timer_count = timer_getTimerCount(TIMER_MS);
        }
        else
        {
            count++;
        }

        if(count == 2000)//??????20???, ???????????????
        {
            timer_initial();
        }

        if(count == 60000)//??????10??????,????????????
        {
            count = 0;
            fibo_softReset();
        }
    }
}

void mainThreadEntry(void *argument)
{
    int times = 0;
    osiThreadSetFPUEnabled(true);               //????????????FPU
    hardware_initial();                         //????????????
    main_LogUI();                               //LOG??????
    data_setAwakeTime(SLEEP_DEFAULT_TIME);      //?????????????????????
    cJson_initial();                            //Json??????????????????
    sysConf_initial();                          //??????????????????
    accelerometer_initial();                    //?????????????????????
    socket_initial();                           //socket??????
    debug_RegistUserCmd();                      //???????????????????????????
    gps_initial();                              //GPS???????????????
    da14580_initial();                          //BLE???????????????
    adc_initial();                              //AD??????
    debug_initial();                            //?????????????????????
    timer_initial();                            //????????????????????????
    display_log_timer_init();                   //???????????????
    diag_selfCheck();                           //???????????????
    audio_initail();                            //?????????????????????
    event_initial();                            //??????????????????
    request_initail();                          //??????????????????
    detect_initail();                           //??????????????????
    response_initial();                         //?????????????????????
    userMsg_initail();                          //????????????
    etcMsg_etcInitial();                        //ETC,BMS???????????????
    startWatchdog(WD_WAKE);                     //??????dump?????????
    softwatchdog_Init();                        //???????????????
    main_PresEt_AT();                           //???????????????????????????

    while(1)
    {
        timer_patch();
        sleep_socketAction();
        sleep_wakeupAction();
        fibo_taskSleep(100);
        if(times++ % 10 == 0)
        {
            uint32_t total, avali, block;
            fibo_get_heapinfo(&total, &avali, &block);
            LOG_DEBUG("[System]mem status: total(%d) avali(%d) block(%d)", total, avali, block);
            LOG_MAIN("[System]colckSystem %llums %llus %llum runtime(%d)", timer_getTimerCount(TIMER_MS), timer_getTimerCount(TIMER_S), timer_getTimerCount(TIMER_M), times / 10);
        }
    }
    fibo_thread_delete();
}

