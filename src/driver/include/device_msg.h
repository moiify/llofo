
#ifndef __DEVICE_MSG_H__
#define __DEVICE_MSG_H__

#include "cJSON/cJSON.h"

typedef int (*DEVICE_PROC)(const void*, cJSON*);
typedef struct
{
    char cmd;
    DEVICE_PROC pfn;
}DEVICE_MSG_PROC;

int device_rspErr(const void* req, int errorCode);

int device_responseOK(const void *req);

/* 
 * function: device通道回复数据
 * params:
 *      req: 命令请求的header
 *      data: 需要回复的json字符串
 * 备注：
 *      data不会在该函数内释放, 所以如果需要释放, 请调用函数后自行释放
 */
int device_responseData(const void *req, char *data);

/* 
 * function: device通道回复数据(JSON)
 * params:
 *      req: 命令请求的header
 *      jsonData: json object
 * 备注：
 *      jsonData会在该函数JSON_Delete掉, 所以入参必须是创建的JSON object
 */
int device_responseJSONData(const void *req, cJSON *jsonData);

/*
 * function: device通道的数据处理函数
 */
int device_msg_handler(const void *msg);
int device_new_handler(const void *msg);

/*
 * function: 注册device通道的数据处理函数
 * params:
 *      cmd: 命令字
 *      action: 处理函数
 * 备注:
 *      如果命令字或者函数相同的话, 会覆盖之前的注册
 */
int device_msg_regist(uint8_t cmd, DEVICE_PROC action);


#endif //__DEVICE_MSG_H__
