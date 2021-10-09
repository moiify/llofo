
#include <string.h>
#include <stdbool.h>

#include "msg.h"
#include "tlv.h"

bool tlv_isHeaderCheckPass(const TLV_DATA_HEADER *pTlvData)
{
    unsigned short i = 0;
    unsigned char *pos = NULL;
    unsigned char checksum = 0;
    
    if(pTlvData->signature != 0xAA)
    {
        return false;
    }
    
    //计算checksum
    pos = (unsigned char *)pTlvData;
    for(; i < pTlvData->payloadLen + 3; i++)
    {
        checksum += pos[i];
    }

    if(pTlvData->payload[pTlvData->payloadLen] != checksum)
    {
        return false;
    }

    return true;
}

TLV_DATA_HEADER *tlv_createHeader(void)
{
    TLV_DATA_HEADER *pTlvData = (TLV_DATA_HEADER *)Malloc(sizeof(TLV_DATA_HEADER) + 1);
    if(!pTlvData)
    {
        return NULL;
    }
    
    pTlvData->signature = 0xAA;
    pTlvData->payloadLen = 0;
    pTlvData->payload[pTlvData->payloadLen] = 0xAA;
    return pTlvData;
}


bool tlv_addData(TLV_DATA_HEADER **ppTlvData, unsigned char type, void *data, unsigned char len)
{
    unsigned short i = 0;
    unsigned char *pos = NULL;
    unsigned short newLen = 0;
    TLV_DATA_HEADER *newTlvData = NULL;
    TLV_DATA_HEADER *pTlvData = *ppTlvData;

    //校验数据合法性
    if(!ppTlvData)return false;
    if(!*ppTlvData)return false;
    if(!tlv_isHeaderCheckPass((const TLV_DATA_HEADER *)pTlvData))return false;
    
    //计算新的数据大小 并申请一块新的内存
    newLen = sizeof(TLV_DATA_HEADER) + pTlvData->payloadLen + 1 + sizeof(TLV_DATA) + len;
    newTlvData = (TLV_DATA_HEADER *)Malloc(newLen);
    if(!newTlvData)return false;
    
    //拷贝老的数据到新的内存 并释放老的内存
    memcpy(newTlvData, pTlvData, sizeof(TLV_DATA_HEADER) + pTlvData->payloadLen + 1);
    Free(pTlvData);

    //更新新的内存地址
    *ppTlvData = newTlvData;
    
    //计算要写的数据的位置
    pos = newTlvData->payload + newTlvData->payloadLen;

    //更新数据
    newTlvData->payloadLen = newTlvData->payloadLen + len + 2;
    pos[0] = type;
    pos[1] = len;
    memcpy(pos + 2, data, len);

    //重新计算checksum
    pos = (unsigned char *)newTlvData;
    newTlvData->payload[newTlvData->payloadLen] = 0;
    for(; i < newTlvData->payloadLen + 3; i++)
    {
        newTlvData->payload[newTlvData->payloadLen] += pos[i];
    }
    return true;
}


void tlv_deleteHeader(TLV_DATA_HEADER *pTlvData)
{
    if(pTlvData)Free(pTlvData);
}

