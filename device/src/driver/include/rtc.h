/*
 * rtc.h
 *
 *  Created on: 2016/2/1
 *      Author: jk
 */

#ifndef __USER_RTC_H__
#define __USER_RTC_H__

#include "fibo_opencpu.h"

#include <time.h>
#include <stdlib.h>

time_t rtc_getTimestamp(void);

char* rtc_getTimeString(void);

void rtc_getLocaltime(hal_rtc_time_t *rtc);

void rtc_updateTimestamp(uint32_t timestamp);

void rtc_updateUTC(int year, int month, int day, int h, int m, int s);

int rtc_setNoUpdate(uint8_t isEnable);

#endif /* __USER_RTC_H__ */
