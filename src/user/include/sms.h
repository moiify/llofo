/*
 * sms.h
 *
 *  Created on: 2019/4/16
 *      Author: lc
 */
#ifndef __SMS_H__
#define __SMS_H__

void sms_recvMessage(uint8_t *buf, uint16_t len);
void sms_sendMessage(uint8_t *buf, uint16_t len);
void sms_sendMessage_end(uint8_t *buf, uint16_t len);
void sms_writeMessage(char *p, char *number);

#endif //__SMS_H__

