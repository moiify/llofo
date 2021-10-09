/*
 * agps.c
 *
 *  Created on: 2017/12/16
 *      Author: wyb
 */
#include <stdio.h>
#include <string.h>

#include <types.h>

#include "agps.h"
#include "http.h"
#include "utils.h"
#include "gps_parse.h"
#include "user_at.h"
#include "user_timer.h"
#include "hardware.h"
#include "time.h"
#include "log.h"
#include "user_at.h"
#include "data.h"

static void agps_aidAssistData(u8 *data, int data_len)
{
    static u8 sendtimes = 0;
    int writeLen = 0;
    int leftLen = data_len;

    do
    {
        writeLen = fibo_hal_uart_put(UART_GPS, (UINT8  *)(data + (data_len - leftLen)), leftLen > 512 ? 512 : leftLen);
        leftLen -= writeLen;
    }while(leftLen > 0 && (sendtimes++ < 50)); 

    sendtimes = 0;
}

static void agps_getAssistData_cb(int result, uint8_t *data, int data_len)
{
    if(result == 0)
    {
        if(data[0] == 0xb5 && data[1] == 0x62)
        {
            LOG_DEBUG("[AGPS] **** agps Work **** ");
            agps_aidAssistData(data, data_len);
        }
    }
}

static u8 agps_url[256] = {0};

static int http_get_cb(void)
{
    http_get(agps_url, agps_getAssistData_cb);
    return 0;
}

static ATResult_enum agps_CLBS_cb(uint8_t isTimeout,char *buf, u16 len)
{
    int rc = 0;
    double lat, lon;
    if(isTimeout)
    {	
        return AT_RES_FINISHED;
    }
    u8 *pos = (u8 *)string_bypass((const char *)buf, "GTGIS:\"");
    if(strstr((const char *)buf, "ERROR") || strstr((const char *)buf, "OK")||(!pos))
    {
        if(strstr((const char *)buf, "ERROR"))
        {
            return AT_RES_FINISHED;
        }
        if(!pos)
        {
            return AT_RES_CONTRINUE;
        }
    }
    
    pos = (u8 *)string_trimLeft(pos);
    rc = sscanf((char *)pos, "%lf,%lf%*s", &lon, &lat);
    LOG_DEBUG("[GPS] rc:%d, lon:%lf, lat:%lf", rc, lon, lat);
    if(rc == 2)
    {
        snprintf((char *)agps_url, sizeof(agps_url), "http://online-live1.services.u-blox.com/GetOnlineData.ashx?token=u2PM1R6SZU2SSksKKHMeTw;gnss=gps,bds;datatype=eph;lat=%lf;lon=%lf", lat, lon);
        timer_start(TIMER_AGPS_HTTP, TIMER_MS, 10, http_get_cb);
        return 0;
    }
    return AT_RES_FINISHED;
}

static void agps_executeUblox(void)
{
    at_run("AT+GTGIS=6\r",agps_CLBS_cb); //获取一次基站定位
}

void agps_tryOnce(void)
{
    if(setting.settingConf.gpsType == GPS_UBLOX_M8U || setting.settingConf.gpsType == GPS_UBLOX_8130
        || setting.settingConf.gpsType == GPS_UBLOX_7020)
    {
        agps_executeUblox();
    }
}

int agps_NeedAGPS(void)
{
    if(!gps_getPosition()->isGPS && data_getData()->isLogined && setting.settingConf.isAgpsEnable)  //当前没有获取gps定位，已经登陆成功并启用agps
    {
        LOG_DEBUG("[GPS] Need AGPS Once");
        agps_tryOnce();
    }
    return 0;
}

void agps_initail(void)
{
    timer_startRepeat(TIMER_AGPS_PROC, TIMER_S, 3600, agps_NeedAGPS);  //每小时进行一次AGPS检测
}

