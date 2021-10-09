/*
 * http.c
 *
 *  Created on: 2020/03/24
 *      Author: lc
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fibo_opencpu.h"

#include "log.h"
#include "msg.h"
#include "http.h"
#include "types.h"
#include "protocol.h"
#include "utils.h"
#include "user_at.h"
#include "user_timer.h"

#define MAX_HTTPREAD_DATA_LEN (500*1024)
#define HTTP_SETTIMEOUT  30
#define HTTP_ACTTIMEOUT  30
#define HTTP_HEADTIMEOUT 30
#define HTTP_READTIMEOUT 30       //HTTP READ 单次请求超时时间
#define AT_STACKMAXLEN   360000
#define HTTP_HOSTLEN     64

char cmd[MAX_HTTPCMD_LEN] = {0};
char get_url[MAX_HTTPURL_LEN] = {0};
static char user_header[MAX_HTTPGET_HEAD_LEN];

typedef struct
{
    int code;
    L_BOOL isProcing;

    uint8_t *downData;
    int downDataLen;
    int respContentLen;
    u8 Packindex;

    http_callback_proc cb;
} HTTP_STATUS;

static ATResult_enum http_HTTPSET_cb(uint8_t isTimeout, char *buf, uint16_t len);
static ATResult_enum http_HTTPGETACTION_cb(uint8_t isTimeout, char *buf, uint16_t len);
static ATResult_enum http_HTTPREAD_cb(uint8_t isTimeout, char *buf, uint16_t len);

static HTTP_STATUS http_status = {L_FALSE, L_FALSE, NULL, 0, 0, .Packindex = 1, NULL};
static http_callback_proc http_getdataCb = NULL;

static void http_getfinish(void)
{
    http_status.isProcing = 0;
    if(http_status.downData)
    {
        Free(http_status.downData);
        http_status.downData = NULL;
    }
    http_status.downDataLen = 0;
    http_status.code = 0;
    http_getdataCb = NULL;
    http_status.Packindex = 1;
}

static int http_delayCB(void)
{
    http_getdataCb(http_status.code, http_status.downData, http_status.downDataLen);  //执行http_get()的回调函数
    http_getfinish();
    return 0;
}

static ATResult_enum http_HTTPHEAD_cb(uint8_t isTimeout, char *buf, uint16_t len)
{
    if(isTimeout || strstr((const char *)buf, ">"))
    {
        at_run(user_header, http_HTTPSET_cb);
        return AT_RES_FINISHED;
    }
    return AT_RES_CONTRINUE; // need ERROR or OK
}

static ATResult_enum http_HTTPREAD_cb(uint8_t isTimeout, char *buf, uint16_t len)
{
    static int datalen = 0;
    static u16 head_len = 0;
    int rt = 0;
    static u8 headDataPack = 0;

    if(isTimeout)
    {
        LOG_DEBUG("[http] HTTREAD timeout");
        http_getdataCb(ERR_OPERATION_TIMEOUT, NULL, 0);
        http_getfinish();
        headDataPack = 0;
        return AT_RES_FINISHED;
    }

    if(headDataPack == 0)
    {
        if(strstr((const char *)http_status.downData, "ERROR"))
        {
            http_getdataCb(ERR_OPERATION_ERROR, NULL, 0);
            http_getfinish();
            headDataPack = 0;
            return AT_RES_FINISHED;
        }
        u8 *pos = (u8 *)string_bypass((const char *)http_status.downData + http_status.downDataLen, "+HTTPREAD:");
//      LOG_DEBUG("[http] +HTTPREAD:");
//      LOG_DEBUG("%s",http_status.downData + http_status.downDataLen);
        if(pos)  //处理第一个带HTTP头的包
        {
            headDataPack = 1;
            LOG_DEBUG("[http] +HTTPREAD Return OK");
            u8 *pos_len = (u8 *)string_bypass((const char *)http_status.downData + http_status.downDataLen, "Content-Length:");
            if(pos_len)
            {
                if(http_status.Packindex == 1)
                {
                    rt = sscanf((char *)pos_len, "%d", &datalen); //第一次请求需要得到整个包的数据长度
                }

                if(rt == 1 || http_status.Packindex != 1)
                {
                    //http_status.downDataLen = 0;
                    LOG_DEBUG("[http] >>>> package len = %d", datalen);
                    if(datalen > MAX_HTTPREAD_DATA_LEN) //加一个内存保护
                    {
                        http_getdataCb(ERR_MEMORY_NOT_ENOUGH, NULL, 0);
                        http_getfinish();
                        headDataPack = 0;
                        return AT_RES_FINISHED;
                    }
                    u8 *pos_data = (u8 *)string_bypass((const char *)http_status.downData + http_status.downDataLen, "\r\n\r\n");  //判断空行
                    if( pos_data)
                    {
                        head_len = pos_data - http_status.downData - http_status.downDataLen;
                        LOG_DEBUG("[http] >>>> head len = %d", head_len);
                        if(head_len <= len)
                        {
                            memcpy(http_status.downData + http_status.downDataLen, http_status.downData + http_status.downDataLen + head_len, len - head_len); //拷贝头包中的数据
                            http_status.downDataLen += len - head_len;
                            if(http_status.downDataLen == datalen)
                            {
                                http_getdataCb(http_status.code, http_status.downData, http_status.downDataLen);
                                http_getfinish();
                                headDataPack = 0;
                                return AT_RES_FINISHED;
                            }
                            return AT_RES_CONTRINUE;
                        }
                    }
                }
            }
        }
        else
        {
            return AT_RES_CONTRINUE; //如果没有等到+HTTPREAD: 返回继续
        }
        http_getdataCb(ERR_OPERATION_ERROR, NULL, 0);
        http_getfinish();
        headDataPack = 0;
        return AT_RES_FINISHED;
    }
    else if(headDataPack == 1)
    {
        //receive the data pack
        http_status.downDataLen += len;
        //LOG_DEBUG(" http_status.downDataLen = %d", http_status.downDataLen);
        if(http_status.Packindex == 1 && datalen > AT_STACKMAXLEN - head_len + 19) //如果不可以通过一次AT指令下载完(AT单次最大360000byte,包含头部)
        {
            if(http_status.downDataLen == AT_STACKMAXLEN - head_len + 19) //第一次AT都下完了 19为READ返回AT命令 固定
            {
                //int remainlen = datalen - http_status.downDataLen; //得到剩余还需要下载的数据包大小
                u8 host[HTTP_HOSTLEN] = {0};
                snprintf(cmd, MAX_HTTPCMD_LEN, "AT+HTTPSET=\"URL\",\"%s\"" CR, (char *)get_url);
                at_runwithTimeout(cmd, at_default_cb, HTTP_SETTIMEOUT);
				getHostfromUrl((const unsigned char *)get_url, host, (unsigned char *)get_url);
                sprintf(user_header,"GET %s HTTP/1.1\r\nRange: bytes=%d-%d\r\nUser-Agent: \r\nAccept: */*\r\nREDIR: 0\r\nx-oss-range-behavior: standard\r\nConnection: Keep-Alive\r\nHOST: %s\r\n\r\n", get_url, http_status.downDataLen, datalen, host);
                snprintf(cmd, MAX_HTTPCMD_LEN, "AT+HTTPHEAD=%d" CR, strlen(user_header));
                at_runwithTimeout(cmd, http_HTTPHEAD_cb, HTTP_HEADTIMEOUT);
                http_status.Packindex++;
                headDataPack = 0;
                return AT_RES_FINISHED;
            }
        }
        if(http_status.downDataLen == datalen)
        {
            LOG_DEBUG(" [http] http get success ! http_status.code = %d", http_status.code);
            timer_start(TIMER_HTTPCBDELAY, TIMER_MS, 10, http_delayCB);
            headDataPack = 0;
            return AT_RES_FINISHED;
        }
        return AT_RES_CONTRINUE;
    }
    return AT_RES_FINISHED;
}

void http_header_cb(const unsigned char *name, const unsigned char *value)
{
}

static void http_ACTION_Error(int code)
{
    switch (code)
    {
        case 301:
            http_status.code = ERR_HTTP_MOVEDPERMANENTLY;
            break;

        case 404:
            http_status.code = ERR_HTTP_NOTFOUND;
            break;

        case 408:
            http_status.code = ERR_HTTP_REQUESTTIMEOUT;
            break;

        case 500:
            http_status.code = ERR_HTTP_INTERNALSERVERERROR;
            break;

        case 504:
            http_status.code = ERR_HTTP_GATEWAYTIMEOUT;
            break;

        case 601:
            http_status.code = ERR_HTTP_NETWORKERROR;
            break;

        case 603:
            http_status.code = ERR_HTTP_DNSERROR;
            break;

        default:
            http_status.code = ERR_HTTP_ACTION; //其他情况都算在这种错误码里面
    }
}

static ATResult_enum http_HTTPGETACTION_cb(uint8_t isTimeout, char *buf, uint16_t len)
{
    if(isTimeout)
    {
        LOG_DEBUG("[http] HTTPACT timeout");

        http_getfinish();
        return AT_RES_FINISHED;
    }
    if(strstr((const char *)buf, "OK") && strstr((const char *)buf, "HTTPRES:")) //两个包带URC
    {
        int return_code = 0;
        sscanf(buf, "%*[^,],%d,%d", &return_code, &http_status.respContentLen);
        if(return_code != 200 && return_code != 206)
        {
            http_ACTION_Error(return_code);
            LOG_ERROR("[http] ERROR ! get_retcode = %d ,errorcode = %d", return_code, http_status.code);
            http_getdataCb(http_status.code, NULL, 0);
            http_getfinish();
            return AT_RES_FINISHED;
        }
        LOG_DEBUG("http_HTTPGETACTION_cb  OK");
        snprintf(cmd, MAX_HTTPCMD_LEN, "AT+HTTPREAD" CR);   //从模块中读取收到的服务器数据
        at_runwithTimeout(cmd, http_HTTPREAD_cb, HTTP_READTIMEOUT);
        return AT_RES_FINISHED;
    }
    else if(strstr((const char *)buf, "ERROR"))
    {
        LOG_DEBUG("http_HTTPGETACTION_cb  ERROR");
        http_getdataCb(ERR_OPERATION_ERROR, NULL, 0);
        http_getfinish();
        return AT_RES_FINISHED;//
    }
    return AT_RES_CONTRINUE;
}

static ATResult_enum http_HTTPSET_cb(uint8_t isTimeout, char *buf, uint16_t len) //uint8_t isTimeout,char *buf, u16 len
{
    if(isTimeout)
    {
        LOG_DEBUG("[http] HTTPSET timeout");
        http_getdataCb(ERR_OPERATION_TIMEOUT, NULL, 0);
        http_getfinish();
        return AT_RES_FINISHED;
    }
    if(strstr((const char *)buf, "ERROR") || strstr((const char *)buf, "OK"))
    {
        if(strstr((const char *)buf, "ERROR"))
        {
            LOG_ERROR("[http] HTTPSET ERROR");
            http_getdataCb(ERR_OPERATION_ERROR, NULL, 0);
            http_getfinish();
            return AT_RES_FINISHED;
        }
        snprintf(cmd, MAX_HTTPCMD_LEN, "AT+HTTPACT=0" CR);  //  0表示get方式 1表示post方式
        at_runwithTimeout(cmd, http_HTTPGETACTION_cb, HTTP_ACTTIMEOUT);
        return AT_RES_FINISHED;
    }
    return AT_RES_CONTRINUE; // need ERROR or OK
}

int http_get(uint8_t *url, http_callback_proc cb)
{
    int rc = -1;

    if(!url || !cb || !strstr((const char *)url, "http") || strlen((const char *)url) > OC_HTTP_URL_LEN)
    {
        if(cb)
        {
            cb(ERR_HTTP_URL, NULL, 0);
        }
        return -1;
    }

    if(http_status.isProcing)
    {
        return -1;
    }

    http_status.isProcing = 1;
    http_status.code = 0;
    http_status.downDataLen = 0;
    if(http_status.downData)
    {
        Free(http_status.downData);
        http_status.downData = NULL;
    }
    http_status.downData = Malloc(MAX_HTTPREAD_DATA_LEN);
    memset(http_status.downData, 0, MAX_HTTPREAD_DATA_LEN);
    do
    {
        snprintf(cmd, MAX_HTTPCMD_LEN, "AT+HTTPSET=\"RANGE\",\"bytes=0-720000\"" CR);
        at_runwithTimeout(cmd, at_default_cb, 2);
        snprintf(cmd, MAX_HTTPCMD_LEN, "AT+HTTPSET=\"URL\",\"%s\"" CR, url);
        strcpy(get_url, (const char *)url);
        at_runwithTimeout(cmd, http_HTTPSET_cb, HTTP_SETTIMEOUT);
        http_getdataCb = cb;
    }
    while(L_FALSE);

    //结算返回值
    if(http_status.code != 0)
    {
        rc = -1;
    }
    else
    {
        rc = 0;
    }

    return rc;
}

int http_post(uint8_t *url, uint8_t *postData, uint16_t postDatalen, http_callback_proc cb)
{
    int rc = -1;
    oc_http_param_t *pstHttpParam = NULL;

    if(!url || !cb || !strstr((const char *)url, "http") || strlen((const char *)url) > OC_HTTP_URL_LEN)
    {
        if(cb)
        {
            cb(ERR_HTTP_URL, NULL, 0);
        }
        return -1;
    }

    if(!postData || strlen((const char *)postData) != postDatalen)
    {
        if(cb)
        {
            cb(ERR_HTTP_USERDATA, NULL, 0);
        }
        return -1;
    }

    if(http_status.isProcing)
    {
        return -1;
    }

    http_status.isProcing = 1;
    http_status.code = 0;
    http_status.downDataLen = 0;
    if(http_status.downData)
    {
        Free(http_status.downData);
        http_status.downData = NULL;
    }
    http_status.downData = Malloc(MAX_HTTPREAD_DATA_LEN);
    do
    {
        u8 url[64] = {0};
        u8 host[64] = {0};
        u8 header[256] = {0};
        pstHttpParam = fibo_http_new();
        if(!pstHttpParam)
        {
            http_status.code = ERR_HTTP_ACTION;
            break;
        }

        pstHttpParam->timeout = 10;
        pstHttpParam->cbReadBody = (http_read_body_callback)http_HTTPREAD_cb;
        pstHttpParam->respCode = 500;
        pstHttpParam->enHttpReadMethod = OC_USER_CALLBACK;
        memset(pstHttpParam->url, 0, OC_HTTP_URL_LEN + 1);
        strncpy((char *)pstHttpParam->url,(const char *)url, strlen((const char *)url));
        getHostfromUrl(url, host, url);
        snprintf((char *)header, 256, "POST %s HTTP/1.1\r\nHost: %s\r\nUser-Agent: curl/7.47.0\r\nAccept: */*\r\nContent-Type: application/json\r\nContent-Length: %d\r\n",
                 url, host, postDatalen);
        LOG_DEBUG("url: %s", pstHttpParam->url);
        LOG_DEBUG("postData: %s", postData);
        LOG_DEBUG("header: %s", header);
        rc = fibo_http_post(pstHttpParam, (u8 *)postData, (u8 *)header);
        LOG_DEBUG("rc: %d", rc);
        switch(pstHttpParam->respCode)
        {
            case 200:
                http_status.code = ERR_SUCCESS;
                break;

            case 301:
                http_status.code = ERR_HTTP_MOVEDPERMANENTLY;
                break;

            case 404:
                http_status.code = ERR_HTTP_NOTFOUND;
                break;

            case 408:
                http_status.code = ERR_HTTP_REQUESTTIMEOUT;
                break;

            case 500:
                http_status.code = ERR_HTTP_INTERNALSERVERERROR;
                break;

            case 504:
                http_status.code = ERR_HTTP_GATEWAYTIMEOUT;
                break;

            case 601:
                http_status.code = ERR_HTTP_NETWORKERROR;
                break;

            case 603:
                http_status.code = ERR_HTTP_DNSERROR;
                break;

            default:
                http_status.code = ERR_HTTP_ACTION;
                break;
        }
        if(rc != 0)break;
        fibo_http_response_header_foreach(pstHttpParam, http_header_cb);
        if(pstHttpParam->respContentLen != 0 && pstHttpParam->respContentLen != http_status.downDataLen)
        {
            http_status.code = ERR_HTTP_ACTION;
            break;
        }
    }
    while(L_FALSE);

    //结算返回值
    if(http_status.code != 0)
    {
        rc = -1;
    }
    else
    {
        rc = 0;
    }

    //清楚http进程
    if(pstHttpParam)
    {
        fibo_http_delete(pstHttpParam);
    }

    //执行http回调
    cb(http_status.code, http_status.downData, http_status.downDataLen);

    //清除http状态
    http_status.isProcing = 0;
    if(http_status.downData)
    {
        Free(http_status.downData);
        http_status.downData = NULL;
    }
    http_status.code = 0;
    http_status.downDataLen = 0;
    return rc;
}

uint8_t *http_get_data(void)
{
    return http_status.downData;
}

int http_get_datalen(void)
{
    return http_status.downDataLen;
}

L_BOOL http_isProcing(void)
{
    return http_status.isProcing;
}

