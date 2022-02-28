
#include <string.h>
#include <math.h>

#include "msg.h"
#include "log.h"
#include "socket.h"
#include "device_msg.h"
#include "data.h"

int device_rspErr(const void *req, int errorCode)
{
    char buf[16] = {0}; //the length 16 is enough for the error code
    int length = 0;
    MSG_DEVICE_RSP *msg = 0;

    snprintf(buf, 16, "{\"code\":%d}", errorCode);
    length = sizeof(MSG_DEVICE_RSP) + strlen(buf);

    msg = alloc_device_msg(req, length);
    if(!msg)
    {
        LOG_ERROR("device inner error");
        return -1;
    }
    strncpy(msg->data, buf, strlen(buf));

    if((msg->header.signature & 0xffff) == 0xA5A5)
    {
        socket_sendDatawithUDP(msg, length);
    }
    else
    {
        socket_sendDataDirectly(msg, length);
    }
    return 0;
}

int device_responseOK(const void *req)
{
    return device_rspErr(req, ERR_SUCCESS);
}

int device_responseData(const void *req, char *data)
{
    int length = sizeof(MSG_DEVICE_RSP) + strlen(data);

    MSG_DEVICE_RSP *msg = alloc_device_msg(req, length);
    if(!msg)
    {
        LOG_ERROR("device inner error");
        return -1;
    }

    strncpy(msg->data, data, strlen(data));

    if((msg->header.signature & 0xffff) == 0xA5A5)
    {
        socket_sendDatawithUDP(msg, length);
    }
    else
    {
        socket_sendDataDirectly(msg, length);
    }
    return 0;
}

int device_responseJSONData(const void *req, cJSON *jsonData)
{
    char *buffer = cJSON_PrintUnformatted(jsonData);
    if(!buffer)
    {
        cJSON_Delete(jsonData);
        device_rspErr(req, ERR_MEMORY_NOT_ENOUGH);
        return -1;
    }

    cJSON_Delete(jsonData);
    device_responseData(req, buffer);

    Free(buffer);
    return 0;
}

#define MAX_MSG_PROC_NUM 128
static DEVICE_MSG_PROC deviceProcs[MAX_MSG_PROC_NUM] =
{
    {0, 0}
};

int device_new_handler(const void *msg)
{
    cJSON *json_root = NULL;
    cJSON *json_imei = NULL;
    MSG_DEVICE_REQ *req = (MSG_DEVICE_REQ *)msg;

    json_root = cJSON_Parse(req->data);
    if(!json_root)
    {
        LOG_ERROR("content is not json type");
        return -1;
    }

    json_imei = cJSON_GetObjectItem(json_root, "imei");
    if(!json_imei)
    {
        cJSON_Delete(json_root);
        LOG_ERROR("no imei in content");
        return -1;
    }

    if(memcmp(setting_getIMEI(), json_imei->valuestring, MAX_IMEI_LENGTH))
    {
        cJSON_Delete(json_root);
        LOG_ERROR("imei check error, realImei: %s, getImei: %s", setting_getIMEI(), json_imei->valuestring);
        return -1;
    }

    cJSON_Delete(json_root);
    return device_msg_handler(msg); //imei检查通过后再走正常device流程
}

int device_msg_handler(const void *msg)
{
#define MAX_CMD_TIMEOUT (15) //s

    int i =0;
    char cmd = 0;
    cJSON *json_tm = NULL;
    cJSON *json_cmd = NULL;
    cJSON *json_root = NULL;
    cJSON *json_param = NULL;
    MSG_DEVICE_REQ *req = (MSG_DEVICE_REQ *)msg;

    json_root = cJSON_Parse(req->data);
    if(!json_root)
    {
        LOG_ERROR("content is not json type");
        return -1;
    }

    json_cmd = cJSON_GetObjectItem(json_root, "c");
    if(!json_cmd)
    {
        cJSON_Delete(json_root);
        LOG_ERROR("no cmd in content");
        return -1;
    }
    cmd = json_cmd->valueint;
    json_tm = cJSON_GetObjectItem(json_root, "tm");
    if(json_tm)
    {
        int32_t diffTime = 0;
        uint32_t time = json_tm->valueint;
        uint32_t timestamp = (uint32_t)rtc_getTimestamp();
        cJSON *json_diff = cJSON_GetObjectItem(json_root, "dt");
        if(json_diff)
        {
            diffTime = json_diff->valueint;
        }
        else
        {
            diffTime = MAX_CMD_TIMEOUT;
        }

        if(((time > timestamp) ? (time - timestamp) : (timestamp - time)) > diffTime)
        {
            cJSON_Delete(json_root);
            device_rspErr(req, ERR_OUT_OF_TIME);
            LOG_ERROR("cmd out of time time:%d  timestap:%d",time,timestamp);
            return -1;
        }
    }
	data_setAwakeTime(SLEEP_SOCKET_WAKE);
    json_param = cJSON_GetObjectItem(json_root, "param");
    for (i = 0; i < sizeof(deviceProcs) / sizeof(deviceProcs[0]); i++)
    {
        if (deviceProcs[i].cmd == json_cmd->valueint)
        {
            DEVICE_PROC pfn = deviceProcs[i].pfn;
            if (pfn)
            {
                pfn(msg, json_param);
                cJSON_Delete(json_root);
                return 0;
            }
            else
            {
                LOG_ERROR("Message %d not processed!", cmd);
                cJSON_Delete(json_root);
                return -1;
            }
        }
    }
    LOG_ERROR("unsupported cmd %d!", cmd);
    cJSON_Delete(json_root);
    device_rspErr(req, ERR_CMD_NOT_SUPPORTED);
    return -1;
}

int device_msg_regist(uint8_t cmd, DEVICE_PROC action)
{
    int i = 0;

    //寻找第一个空位命令,或者命令字相同,或者函数指针相同
    while (i < MAX_MSG_PROC_NUM && deviceProcs[i].cmd != cmd &&(deviceProcs[i].pfn && deviceProcs[i].pfn != action))
    {
        i++;
    }

    if ( i >= MAX_MSG_PROC_NUM)
    {
        LOG_ERROR("exceed MAX command number: %d", 64);
        return -1;
    }

    deviceProcs[i].cmd = cmd;
    deviceProcs[i].pfn = action;
    return 0;
}

