/*
 * log.h
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */
#ifndef __USER_REQUEST_H__
#define __USER_REQUEST_H__

int cmd_Login(void);
int cmd_status(void);
int cmd_Heartbeat(void);
int cmd_statusMatchPeriod(void);
int cmd_notify(u8 notifyType, u8 notifyValue);
int cmd_notify_V2(u16 notifyType, u16 payload, u32 reserved);
int cmd_submitBMSInfo(void);
int cmd_alarm(char alarm_type);
int cmd_faultRecord(void);

int request_initail(void);
int cmd_nmea_UDP(void);

/*
 * print message via UDP
 *
 * Note:
 *      the message length is limited to 1023 bytes
 */
int cmd_printUDP(const char *fmt, ...);

#endif /* __USER_REQUEST_H__ */

