/*
 * user_at.c
 *
 *  Created on: 2020.04.03
 *      Author: lc
 */
#include <stdio.h>
#include <string.h>

#include "log.h"
#include "msg.h"
#include "list.h"
#include "utils.h"
#include "user_at.h"
#include "user_timer.h"
#include "audio_driver.h"
#include "sms.h"
#include "http.h"
#include "data.h"

#pragma pack(push, 1)

typedef struct
{
    AT_CB_PROC fun;
    uint16_t timeout;
    uint8_t cmd[MODEM_AT_MAX_LEN];
} ElemType;

typedef struct
{
    struct list_head list;
    ElemType elemtype;
} MODEM_NODE;

#pragma pack(pop)

static LIST_HEAD(head);

static L_BOOL at_isQueueEmpty(void)
{
    if(list_empty(&head))
    {
        return L_TRUE;
    }
    return L_FALSE;
}

static void at_enQueue(ElemType *elemtype)
{
    MODEM_NODE *new_p = Malloc(sizeof(MODEM_NODE));
    if(new_p == NULL)
    {
        return;
    }

    new_p->elemtype = *elemtype;

    list_add_tail(&new_p->list, &head);

    return;
}

static ElemType *at_deQueue(void)
{
    MODEM_NODE *pElemType = NULL;
    ElemType *elemtype = Malloc(sizeof(ElemType));

    if(!at_isQueueEmpty())
    {
        pElemType = list_first_entry(&head, MODEM_NODE, list);

        list_del(&pElemType->list); // del the first entry element

        *elemtype = pElemType->elemtype;

        Free(pElemType);
        pElemType = NULL;
    }

    return elemtype;
}

static ElemType *at_peekQueue(void)
{
    MODEM_NODE *pElemType = NULL;
    ElemType *elemtype = Malloc(sizeof(ElemType));

    if(!at_isQueueEmpty())
    {
        pElemType = list_first_entry(&head, MODEM_NODE, list);

        *elemtype = pElemType->elemtype;
    }

    return elemtype;
}

//static void at_clearQueue(void)
//{
//    MODEM_NODE *pElemType = NULL;
//    struct list_head *iter = NULL;
//
//    list_for_each(iter, &head)
//    {
//        pElemType = list_entry(iter, MODEM_NODE, list);
//
//        list_del(iter);
//
//        Free(pElemType);
//        pElemType = NULL;
//    }
//
//    return;
//}

static L_BOOL at_cmd(const unsigned char *cmd)
{
    unsigned short len = strlen((const char *)cmd);
    int32_t rc = fibo_at_send(cmd, len);
    LOG_DEBUG("[AT] fibo_at_send:%s, funRet:%d ", cmd, rc);
    if(rc < 0)
    {
        LOG_ERROR("[AT] L610 modem write AT command failed: should be %d, but ret = %d", len, rc);
		if(setting_isDefendOn() && timer_getTimerCount(TIMER_S) > 300) 
		{
			LOG_ERROR("[AT] AT ret -1, reset to fix", len, rc);
			fibo_softReset();
		}
        return L_FALSE;
    }

    return L_TRUE;
}

static int at_timeout(void);
static void at_execNext(void)
{
    timer_stop(TIMER_MODEM_TIMEOUT);

    if(at_isQueueEmpty())
    {
        LOG_DEBUG("there is no modem task now");
        return;
    }
    else
    {
        ElemType *temp = at_peekQueue();
        LOG_DEBUG("modem_peekQueue :%s", temp->cmd);
        at_cmd(temp->cmd);
        timer_start(TIMER_MODEM_TIMEOUT, TIMER_S, temp->timeout, at_timeout);
        Free(temp);
    }
}

static int at_timeout(void)
{
	static u8 isFirst = 0;
    if(!at_isQueueEmpty())
    {
        ElemType *temp = at_deQueue();
        if(temp->fun)
        {
            temp->fun(L_TRUE, NULL, 0);
        }
        LOG_ERROR("modem timeout cmd:%s time:%d, action %p", temp->cmd, temp->timeout, temp->fun);
		data_getData()->ATtimeout++;
		if(!isFirst)
		{
			isFirst = 1;
			memset(data_getData()->AT_blockCMD, 0, 20);
			memcpy(data_getData()->AT_blockCMD, temp->cmd, 19);
		}
        Free(temp);
        at_execNext();
    }
    return 0;
}

ATResult_enum at_default_cb(uint8_t isTimeout, char * buf, uint16_t len)
{
    if(isTimeout || strstr((const char *)buf, "ERROR") || strstr((const char *)buf, "OK"))
    {
        return AT_RES_FINISHED;
    }
    return AT_RES_CONTRINUE; // need ERROR or OK
}

void at_run(const char *cmd, AT_CB_PROC fun)
{
    at_runwithTimeout(cmd, fun, 30);
}

void at_runwithTimeout(const char *cmd, AT_CB_PROC fun, uint8_t timeout)
{
    if(strlen(cmd) >= MODEM_AT_MAX_LEN)
    {
        return;
    }
    
    if(cmd && cmd[0] != 0 && strchr(cmd, '\r'))
    {
        ElemType *temp = Malloc(sizeof(ElemType));
        if(!temp)
        {
            return;
        }
        temp->fun = fun;
        temp->timeout = timeout != 0 ? timeout : 80;
        memset(temp->cmd, 0 , sizeof(temp->cmd));
        strncpy((char *)temp->cmd, cmd, strlen(cmd) + 1);
        LOG_DEBUG("register run cmd: %s , action %p", temp->cmd, fun);
        if(at_isQueueEmpty())
        {
            at_enQueue(temp);// no task at this time
            at_cmd((uint8_t *)cmd);//执行队列中的第一个AT指令
            timer_start(TIMER_MODEM_TIMEOUT, TIMER_S, temp->timeout, at_timeout);
        }
        else
        {
            at_enQueue(temp);// there are some tasks at this time
        }
        Free(temp);
        return;
    }
    else
    {
        LOG_ERROR("register cmd error: %s , action %p", cmd, fun);
    }
}

void at_res_callback(uint8_t *buf, uint16_t len)
{
    static char result[MODEM_AT_MAX_LEN] = {0};

    if(strstr((const char *)buf, "+CMTI: \"SM\""))
    {
        sms_recvMessage(buf, len);
    }
    if(strstr((const char *)buf, "+CMGW:"))
    {
        sms_sendMessage(buf, len);
    }
    if(strstr((const char *)buf, "+CMSS:"))
    {
        sms_sendMessage_end(buf, len);
    }

    if(strstr((const char *)buf, "+SIM READY")) //收到sim卡信号后异步获取imsi
    {
        fibo_get_imsi_asyn(setting_obtainIMSI_cb);
    }

    ElemType *temp = at_peekQueue();
    int length = strlen(result);

    if(strstr((const char *)temp->cmd, "AT+HTTPREAD") == 0)
    {
        uart_print("%s\r\n",buf);
    }

    if(strstr((const char *)temp->cmd, "AT+HTTPREAD") != 0)
    {
    	u8 * http_DataOffect = http_get_data() + http_get_datalen();
        memcpy(http_DataOffect, buf,len);
    }
    else
    {
        memcpy(result + strlen(result), buf,len);  // suit for binary
        len += length;
    }

    if(at_isQueueEmpty())// no task at this time
    {
        memset(result, 0, MODEM_AT_MAX_LEN); // clear result
        return;
    }

    if(strstr((const char *)temp->cmd, "AT+HTTPREAD")||strstr(result, (const char *)temp->cmd) || 0 == strncmp(result, (const char *)temp->cmd, strlen((const char *)temp->cmd) - 1))// remove \r
    {
        int rc = -1;
        if(temp->fun)
        {
            rc = temp->fun(L_FALSE, result, len);
            if(rc == AT_RES_CONTRINUE)
            {
                Free(temp);
                return;   // AT_RES_CONTRINUE: the function need multi modem result
            }
        }

        LOG_DEBUG("process cmd(%s)'s ack, action %p", temp->cmd, temp->fun);
        Free(at_deQueue());
        at_execNext();
    }
    Free(temp);
    memset(result, 0, MODEM_AT_MAX_LEN); // clear result
    return;
}

