/*
 * fence.c
 *
 *  Created on: 2018/04/23
 *      Author: lc
 */
#include <stdbool.h>

#include "fibo_opencpu.h"

#include "log.h"
#include "msg.h"
#include "types.h"
#include "fence.h"
#include "user_fs.h"

L_BOOL fence_getFenceFromFile(FENCE **ppFence)//获取本地围栏信息
{
    uint8_t *pos = 0;
    int i = 0, rc = 0;
    L_BOOL ret = L_TRUE;
    FENCE *newFence = NULL;

    do
    {
        int filesize = fs_getFileSize(FILE_FENCE_CONF);
        if(filesize < 0)
        {
            LOG_DEBUG("no fence.conf history");
            ret = L_FALSE;
            break;
        }

        // 如果之前有申请内存 先释放了再申请.
        if(*ppFence)
        {
            Free((*ppFence));
            *ppFence = NULL;
        }

        //如果文件大小大于20K 认为有问题
        if(filesize > 20 *1024)
        {
            LOG_ERROR("fileSize error: %d", filesize);
            ret = L_FALSE;
            break;
        }

        *ppFence = Malloc(filesize);
        if(!(*ppFence))
        {
            LOG_ERROR("inner memory error: %d", filesize);
            ret = L_FALSE;
            break;
        }

        newFence = *ppFence;

        rc = fs_getFileData(FILE_FENCE_CONF, newFence, filesize);
        if (0 > rc)
        {
            LOG_ERROR("read fence file error: %d", rc);
            ret = L_FALSE;
            break;
        }

        if(newFence->fenceNum == 0)
        {
            ret = L_FALSE;
            break;
        }

        /* 计算到第一个围栏区的地址 */
        pos = ((uint8_t *)newFence) + sizeof(FENCE);
        newFence->fencePoly[0].fencePoint = (FENCE_POINT *)pos;

        for(i = 1; i < newFence->fenceNum; i++)
        {
            /* 计算接下来几个围栏区的地址 */
            pos = pos + (newFence->fencePoly[i - 1].nodeNum * sizeof(FENCE_POINT));
            newFence->fencePoly[i].fencePoint = (FENCE_POINT *)pos;
        }
    }while(L_FALSE);

    if(ret == L_FALSE)
    {
        if(*ppFence)
        {
            Free((*ppFence));
            *ppFence = NULL;
        }
    }
    return ret;
}

L_BOOL fence_saveFenceFromData(FENCE *pFence)
{
    L_BOOL ret = L_FALSE;
    uint32_t dataLen = sizeof(FENCE);

    if(!pFence || pFence->fenceNum == 0)
    {
        fs_deleteFile(FILE_FENCE_CONF);// 如果fence为空或者fenceNum为0 不做存储
    }
    else
    {
        int i = 0;
        for(i = 0; i < pFence->fenceNum; i++)
        {
            dataLen = dataLen + (pFence->fencePoly[i].nodeNum * sizeof(FENCE_POINT));
        }

        if(dataLen >= 20 * 1024)// 计算出围栏文件大于20K 认为围栏有问题 不做存储
        {
            fs_deleteFile(FILE_FENCE_CONF);
        }

        int rc = fs_saveFileData(FILE_FENCE_CONF, (void *)pFence, dataLen + 1);
        if(rc < 0)
        {
            ret = L_FALSE;
        }
        else
        {
            ret = L_TRUE;
            LOG_DEBUG("save fence file success.");
        }
    }
    return ret;
}

/*
* function: 射线法计算坐标是否在围栏内部, 射线方向: 正南
*
* parameters:
*    polyNodes: 围栏的顶点数
*    *polyLat:  围栏顶点的纬度数组
*    *polyLon:  围栏定点的经度数组
*    lat:       坐标的纬度
*    lon:       坐标的经度
*
* return:
*    true: 在围栏内
*    false: 在围栏外
*
* Note:
*    围栏的定点数应该是多边形的定点数, 围栏应该是首尾相连的顺序坐标点组成
*/
static bool fence_isPointInPolygon(int polyNodes, FENCE_POINT *poly, float lat, float lon)
{
    bool isOddSides = false;
    int i = 0, j = polyNodes - 1;// 先判断最后一个顶点->第一个顶点的边

    for (; i < polyNodes; i++)
    {
        if(((poly[i].longitude < lon && poly[j].longitude >= lon )|| (poly[j].longitude < lon && poly[i].longitude >= lon))// 保证这个边在点的射线区域
        && (poly[i].latitude <= lat || poly[j].latitude <= lat))// 保证这个边有可能被点的射线射中
        {
            if(poly[i].latitude+(lon-poly[i].longitude)/(poly[j].longitude-poly[i].longitude)*(poly[j].latitude-poly[i].latitude)<lat)
            {
                // f(lon) < lat, 射中了
                isOddSides = !isOddSides;
            }
        }
        j = i;
    }

    return isOddSides;
}

CAR_RELATIVE_FENCE_POSITION fence_isPointInServicePolygon(FENCE *pFence, float lat, float lon)
{
    int i = 0;
    L_BOOL isInSercieArea = L_TRUE, isInWarningArea = L_TRUE;
    if(fence_checkData(pFence) == L_FALSE)
    {
        return RIDING_AREA;
    }

    for(i = 0; i < pFence->fenceNum; i++)
    {
        LOG_DEBUG("pFence->fencePoly[%d].mode = %d", i, pFence->fencePoly[i].mode);
        if(pFence->fencePoly[i].mode == 0) //如果是服务区围栏
        {
            if(fence_isPointInPolygon(pFence->fencePoly[i].nodeNum, pFence->fencePoly[i].fencePoint, lat, lon))
            {
                isInSercieArea = L_TRUE;
            }
            else
            {
                isInSercieArea = L_FALSE;
            }
        }
        else if(pFence->fencePoly[i].mode == 2) //如果是告警区围栏
        {
            if(fence_isPointInPolygon(pFence->fencePoly[i].nodeNum, pFence->fencePoly[i].fencePoint, lat, lon))
            {
                isInWarningArea = L_TRUE;
            }
            else
            {
                isInWarningArea = L_FALSE;
            }
        }
    }

    LOG_DEBUG("isInSercieArea = %d, isInWarningArea = %d", isInSercieArea, isInWarningArea);
    if(isInSercieArea == L_TRUE && isInWarningArea == L_TRUE)  //在服务区围栏内，在告警区围栏内
    {
        return RIDING_AREA;
    }
    else if(isInSercieArea == L_TRUE && isInWarningArea == L_FALSE) //在服务区围栏内，告警区围栏外
    {
        return ALARM_AREA;
    }
    else if(isInSercieArea == L_FALSE) //服务区围栏外
    {
        return OUTSERVICE_AREA;
    }
    else
    {
        return ERROR_AREA;
    }
}

L_BOOL fence_checkData(FENCE *pFence)
{
    if(!pFence || memcmp(pFence->signature, "XiaoanTech", 10))
    {
        return L_FALSE;
    }
    return L_TRUE;
}
