#ifndef __USER_GPS_PARSE_H__
#define __USER_GPS_PARSE_H__

#include "nmea/info.h"
#include "data.h"
#include "user_at.h"

#define KM_per_H_2_STEP_per_S(x) (u8)((x * 20.0 / 18.0) + 0.5)
#define STEP_per_S_2_KM_per_H(x) (u8)((x * 18.0 / 20.0) + 0.5)

typedef enum
{
    TYPE_OUT_WARNING_FENCE    = 1,
    TYPE_IN_WARNING_FENCE     = 2,
    TYPE_OUT_SERVER_FENCE     = 3,
    TYPE_IN_SERVER_FENCE      = 4,
} ALARM_TYPE_RETURN;

void gps_initial(void);

uint8_t *gps_getLastNMEA_str(void);
uint8_t *gps_getLastNMEA_strLimit(void);

void gps_nmeaOutputEnable(uint8_t isEnable);

POSITION *gps_getPosition(void);
void gps_getCLBS(AT_CB_PROC fun);
ATResult_enum gps_getCLBS_proc(uint8_t isTimeout,char *buf, u16 len);
float gps_getGPSValue(double val);
u32 gps_getGPSU32(double val);
void gps_moudleReset(void);
void gps_uart_send(void *msg, unsigned short length);
void gps_setRevGpsMsg(u8 isRevGpsMsg);
u8 gps_isRevGPSMsg(void);

int gps_parse(void);
int gps_setNmeaStr(u8 *pNmea, int size);

#endif/*__USER_GPS_PARSE_H__*/

