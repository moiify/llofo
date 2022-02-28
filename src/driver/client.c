#include <stdio.h>
#include <string.h>

#include "log.h"
#include "client.h"
#include "msg.h"
#include "data.h"
#include "setting.h"

static int g_msgUdpProcsNum = 0;
static MC_MSG_PROC *g_msgUdpProcs = NULL;
int client_udp_proc(const void *m, int msgLen)
{
    int i = 0;
    const MSG_HEADER *msg = (const MSG_HEADER *)m;

    LOG_HEX(m, msgLen);

    if(msgLen < MSG_HEADER_LEN)
    {
        LOG_ERROR("message length not enough: %zu(at least(%zu)", msgLen, sizeof(MSG_HEADER));
        return -1;
    }

    if(_ntohs(msg->signature) != START_FLAG_UDP)
    {
        LOG_ERROR("receive message header signature error:%#x", (unsigned)_ntohs(msg->signature));
        return -1;
    }

    for(i = 0; i < g_msgUdpProcsNum; i++)
    {
        if(g_msgUdpProcs[i].cmd == msg->cmd)
        {
            MSG_PROC pfn = g_msgUdpProcs[i].pfn;
            if(pfn)
            {
                return pfn(msg);
            }
            else
            {
                LOG_ERROR("Message %d not processed!", msg->cmd);
                return -1;
            }
        }
    }
    return -1;
}

static int g_msgProcsNum = 0;
static MC_MSG_PROC *g_msgProcs = NULL;
int client_handleOnePkt(const void *m, int msgLen)
{
    MSG_HEADER *msg = (MSG_HEADER *)m;
    size_t i = 0;

    for(i = 0; i < g_msgProcsNum; i++)
    {
        if(g_msgProcs[i].cmd == msg->cmd)
        {
            MSG_PROC pfn = g_msgProcs[i].pfn;
            if(pfn)
            {
                return pfn(msg);
            }
            else
            {
                LOG_ERROR("Message %d not processed!", msg->cmd);
                return -1;
            }
        }
    }

    LOG_ERROR("unknown message %d!", msg->cmd);
    return -1;
}

static CLIENT_PROC client_procEXT = NULL;
int client_proc(const void *m, int msgLen)
{
    s16 leftLen = 0;
    const MSG_HEADER *msg = (const MSG_HEADER *)m;

    if(client_procEXT)
    {
        return client_procEXT(m, msgLen);
    }

    LOG_HEX(m, msgLen);

    if(msgLen < MSG_HEADER_LEN)
    {
        LOG_ERROR("message length not enough: %zu(at least(%zu)", msgLen, sizeof(MSG_HEADER));
        return -1;
    }

    leftLen = msgLen;
    while(leftLen >= _ntohs(msg->length) + MSG_HEADER_LEN)
    {
        if (_ntohs(msg->signature) != START_FLAG)
        {
            LOG_ERROR("receive message header signature error:%#x", (unsigned)_ntohs(msg->signature));
            return -1;
        }
        client_handleOnePkt(msg, _ntohs(msg->length) + MSG_HEADER_LEN);
        leftLen = leftLen - MSG_HEADER_LEN - _ntohs(msg->length);
        msg = (const MSG_HEADER *)((const char *)m + msgLen - leftLen);
    }
    return 0;
}

void client_initailEXT(CLIENT_PROC procHandler)
{
    client_procEXT = procHandler;
}

void client_initail(void *responseArray, int responseArraySize)
{
    g_msgProcs = responseArray;
    g_msgProcsNum = responseArraySize;
}

void client_initailUDP(void *responseArray, int responseArraySize)
{
    g_msgUdpProcs = responseArray;
    g_msgUdpProcsNum = responseArraySize;
}

