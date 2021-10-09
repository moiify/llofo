/*
 * log.h
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */
#ifndef __USER_LOG_H__
#define __USER_LOG_H__

#include "rtc.h"
#include "uart.h"
#include "setting.h"
#include "data.h"

enum
{
    LOG_LEVEL_NULL,
    LOG_LEVEL_MAINTENANCE,
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG
} Log_Level_e;

void log_hex(const void *buf, int length);
void log_binary(const char* data, int length);

#define __FILENAME__ (strrchr(__FILE__, '/') ? (strrchr(__FILE__, '/') + 1):__FILE__)
#define LOG_DEBUG(fmt, ...) if(setting.settingConf.loglevel >= LOG_LEVEL_DEBUG)uart_print("%s[D][%s:%d %s]"fmt"\r\n", rtc_getTimeString(), __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)  if(setting.settingConf.loglevel >= LOG_LEVEL_INFO)uart_print("%s[I][%s:%d %s]"fmt"\r\n", rtc_getTimeString(), __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) if(setting.settingConf.loglevel >= LOG_LEVEL_WARNING)uart_print("%s[W][%s:%d %s]"fmt"\r\n", rtc_getTimeString(), __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) if(setting.settingConf.loglevel >= LOG_LEVEL_ERROR)uart_print("%s[E][%s:%d %s]"fmt"\r\n", rtc_getTimeString(), __FILENAME__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LOG_MAIN(fmt, ...) if(setting.settingConf.loglevel >= LOG_LEVEL_MAINTENANCE)uart_print("%s[B]"fmt"\r\n", rtc_getTimeString(), ##__VA_ARGS__)

#define LOG_HEX(data, len)  if(setting.settingConf.loglevel >= LOG_LEVEL_DEBUG)log_hex(data, len)
#define LOG_BIN(data, len)  if(setting.settingConf.loglevel >= LOG_LEVEL_INFO)log_binary(data, len)

#endif /* __USER_LOG_H__ */

