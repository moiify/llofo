#include <stdio.h>
#include <string.h>

#include "rtc.h"
#include "log.h"
#include "utc_time.h"

#define YEAROFFSET 2000

static u8 g_isRtcNoUpdate = FALSE;

void rtc_updateUTC(int year, int month, int day, int h, int m, int s)   //2020/1/1  1/1/1
{
    if(g_isRtcNoUpdate) //暂不再更新rtc时间，重启恢复
    {
        return;
    }

    struct utc_time_t rtc = {0};
	utc_time timestamp;
    if(year < 2020)
    {
        return;
    }
    rtc.year = year;
    rtc.month = month - 1; //从0开始计
    rtc.day = day - 1;	//从0开始计
    rtc.hour = h;
    rtc.minutes = m;
    rtc.seconds = s;

	timestamp = convert_utc_secs(&rtc);
	
	rtc_updateTimestamp(timestamp);
}

/*
* 1900年开始 0表示1月  timestamp从1970年开始的秒数且为UTC时间
*/
void rtc_updateTimestamp(uint32_t timestamp)
{
    struct utc_time_t utc_time_st = {0};
    hal_rtc_time_t rtc;
    memset(&rtc, 0, sizeof(rtc));
    
    if(g_isRtcNoUpdate) //暂不再更新rtc时间，重启恢复
    {
        return;
    }

    convert_utc_time(&utc_time_st, (utc_time)timestamp + 28800); //本地RTC设置成东八区时间
    LOG_DEBUG("[RTC]UTC+8 Convert %d-%d-%d %d-%d-%d", utc_time_st.year, utc_time_st.month + 1, utc_time_st.day + 1, utc_time_st.hour, utc_time_st.minutes, utc_time_st.seconds);

    rtc.year = (u8)(utc_time_st.year - YEAROFFSET);  //utc_time_st.year得出的2020,减去2000得到20 为广和通RTC时间
    rtc.month = utc_time_st.month + 1;
    rtc.day = utc_time_st.day + 1;
    rtc.hour = utc_time_st.hour;
    rtc.min = utc_time_st.minutes;
    rtc.sec = utc_time_st.seconds;

    LOG_DEBUG("[RTC]set fibo_RTC %d-%d-%d %d-%d-%d", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.min, rtc.sec);

    INT32 ret = fibo_setRTC(&rtc);  //UTC时间
    LOG_DEBUG("[RTC] fibo_setRTC ret=%d",ret);

    memset(&rtc, 0, sizeof(rtc));
    fibo_getRTC(&rtc);
    LOG_DEBUG("[RTC]get fibo RTC %d-%d-%d %d-%d-%d", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.min, rtc.sec);
}


//从January 1 1970 00:00:00到现在的时间(UTC)过的秒数
time_t rtc_getTimestamp(void)
{
    struct tm stm = {0};
    hal_rtc_time_t rtc = {0};
    time_t time = 0;

    fibo_getRTC(&rtc);

    stm.tm_year = rtc.year + YEAROFFSET - 1900;
    stm.tm_mon = rtc.month - 1;
    stm.tm_mday = rtc.day;
    stm.tm_hour = rtc.hour;
    stm.tm_min = rtc.min;
    stm.tm_sec = rtc.sec;

    time = mktime(&stm);

    return time - 28800;
}

void rtc_getLocaltime(hal_rtc_time_t *rtc)
{

    struct utc_time_t utc_time_st = {0};

    utc_time timestamp = (utc_time)rtc_getTimestamp() + 28800;

    convert_utc_time(&utc_time_st, (utc_time)timestamp);

    rtc->year = (utc_time_st.year - YEAROFFSET);
    rtc->month = utc_time_st.month + 1;
    rtc->day = utc_time_st.day + 1;
    rtc->hour = utc_time_st.hour;
    rtc->min = utc_time_st.minutes;
    rtc->sec = utc_time_st.seconds;
}

char *rtc_getTimeString(void)
{
    static char timeStr[32] = {0};

    hal_rtc_time_t rtc = {0};
    rtc_getLocaltime(&rtc);
    sprintf(timeStr, "%d-%02d-%02d %02d:%02d:%02d", rtc.year + YEAROFFSET, rtc.month, rtc.day, rtc.hour, rtc.min, rtc.sec);

    return timeStr;
}

int rtc_setNoUpdate(uint8_t isEnable)
{
    if(isEnable == TRUE || isEnable == FALSE)
    {
        g_isRtcNoUpdate = isEnable;
    }
    return 0;
}

