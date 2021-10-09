/*
 * async.h
 *
 *  Created on: 2018/06/03
 *      Author: lc
 */

#ifndef _ASYNC_H_
#define _ASYNC_H_

#include "types.h"

typedef enum
{
    RESULT_OK,
    RESULT_TIMEOUT,
} ASYNC_RESULT;

typedef int (*ASYNC_PROC)(void);
typedef int (*ASYNC_MSG_PROC)(uint8_t *data);
//typedef int (*ASYNC_MSG_PROC)(uint8_t* data, u16 dataLen);

typedef int (*ASYNC_RESPONSE_PROC)(int result, void *param);

#define ASYNC_PRO_MAP_ITEM(ADDRESS, CMD, MSG_PROC, ISWAITRSP) {ADDRESS, CMD, NULL, MSG_PROC, NULL, ISWAITRSP, 0, NULL},

typedef struct
{
    u8 address;
    u8 cmd;
    ASYNC_PROC action;
    ASYNC_MSG_PROC msgProc;
    ASYNC_RESPONSE_PROC responseAction;
    u8 isWaitRsp;
    s8 time; //needTimes
    s8 actionTimes;
    void *param;
} ASYNC_PROC_MAP;

int async_procTimeout(ASYNC_PROC_MAP eventProcs[], int size);
int async_procMsg(uint8_t *data,ASYNC_PROC_MAP eventProcs[], int size);


#endif // !_ASYNC_H_

