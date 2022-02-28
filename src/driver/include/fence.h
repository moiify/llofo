/*
 * fence.h
 *
 *  Created on: 2018/04/23
 *      Author: lc
 */
#ifndef __USER_FENCE_H__
#define __USER_FENCE_H__
#include <stdbool.h>

#include <fibo_opencpu.h>

#include "types.h"

#pragma pack(push, 1)

typedef struct
{
    float longitude;
    float latitude;
}__attribute__((__packed__)) FENCE_POINT;

typedef struct
{
    uint8_t mode;
    uint16_t nodeNum;
    FENCE_POINT *fencePoint;
}__attribute__((__packed__)) FENCE_POLY;

typedef struct
{   
    uint8_t signature[10];
    uint32_t version;
    uint8_t fenceNum;
    FENCE_POLY fencePoly[16];
}__attribute__((__packed__)) FENCE;

typedef enum
{
    RIDING_AREA         = 0,        // 正常骑行区域
    ALARM_AREA          = 1,        // 需要告警的区域
    OUTSERVICE_AREA     = 2,        // 服务区外
    FORBIDSTOP_AREA     = 3,        // 禁停区域
    ERROR_AREA          = 4,        // 相对围栏位置信息判断错误
} CAR_RELATIVE_FENCE_POSITION;

#pragma pack(pop)

//获取本地围栏信息
L_BOOL fence_getFenceFromFile(FENCE **ppFence);

//存储当前围栏信息
L_BOOL fence_saveFenceFromData(FENCE *pFence);

//判断坐标是否在服务区
CAR_RELATIVE_FENCE_POSITION fence_isPointInServicePolygon(FENCE *pFence, float lat, float lon);

L_BOOL fence_checkData(FENCE *pFence);

#endif/*__USER_FENCE_H__*/


