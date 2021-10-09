/*
 * user_debug.h
 *
 *  Created on: 2020.04.03
 *      Author: lc
 */

#ifndef __USER_DEBUG_H__
#define __USER_DEBUG_H__

#include "log.h"

#define DEBUG_CMD_PLAY      "play"
#define DEBUG_CMD_DEBUG     "debug"
#define DEBUG_CMD_IMEI      "imei"
#define DEBUG_CMD_IMSI      "imsi"
#define DEBUG_CMD_CCID      "ccid"
#define DEBUG_CMD_AT        "AT"
#define DEBUG_CMD_at        "at"
#define DEBUG_CMD_REBOOT    "reboot"
#define DEBUG_CMD_SHUTDOWN  "shutdown"
#define DEBUG_CMD_RTC       "rtc"
#define DEBUG_CMD_IO        "io"
#define DEBUG_CMD_SETTT     "settt"
#define DEBUG_CMD_SETRT     "setrt"
#define DEBUG_CMD_LOG       "log"


typedef int (*CMD_ACTION)(const unsigned char* cmdString, unsigned short length);

int debug_initial(void);

void debug_RegistUserCmd(void);

#define DBG_OUT(fmt, ...) LOG_DEBUG("[DEBUG]>"fmt"\r\n", ##__VA_ARGS__)

#endif /* __USER_DEBUG_H__ */

