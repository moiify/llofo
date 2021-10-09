/*
 * msg.c
 *
 *  Created on: 2015??7??8??
 *      Author: jk
 */
#include "fibo_opencpu.h"

#include <string.h>

#include "msg.h"
#include "log.h"
#include "data.h"

static char seq = 0;

void * myTestMalloc(unsigned int size)
{
    data_getData()->malloctimes++;
    return fibo_malloc(size);
}

int32_t Free(void *buffer)
{
    if(buffer)
    {	
        data_getData()->malloctimes--;
        return fibo_free(buffer);
    }
    return -1;
}

void* alloc_msg(char cmd, size_t length)
{
    MSG_HEADER* msg = myTestMalloc(length);
    if (msg)
    {
        memset(msg, 0, length);
        msg->signature = _htons(START_FLAG);
        msg->cmd = cmd;
        msg->seq = seq++;
        msg->length = _htons(length - MSG_HEADER_LEN);
    }

    return msg;
}

void* alloc_device_msg(const MSG_HEADER* pMsg, size_t length)
{
    MSG_HEADER* msg = myTestMalloc(length);
    if (msg)
    {
        memset(msg, 0, length);
        msg->signature = pMsg->signature;
        msg->cmd = pMsg->cmd;
        msg->seq = pMsg->seq;
        msg->length = _htons(length - MSG_HEADER_LEN);
    }

    return msg;
}

void free_msg(void* msg)
{	
    data_getData()->malloctimes--;
    fibo_free(msg);
}

