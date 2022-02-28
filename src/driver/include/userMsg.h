/*
 * userMsg.h
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */
#ifndef __USER_MSG_H__
#define __USER_MSG_H__


typedef enum
{
    EVENT_ALARM,
    EVENT_SENDSTATUS,
    EVENT_SENDBMSINFO,
    EVENT_NUM,
}EVENT_TYPE;


void userMsg_initail(void);
void userMsg_setEvent(EVENT_TYPE event, u8 type);


#endif /* __USER_MSG_H__ */

