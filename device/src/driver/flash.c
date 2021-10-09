/*
 * flash.c
 *
 *  Created on: 2019/4/8
 *      Author: lc
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "fibo_opencpu.h"
#include "msg.h"
#include "log.h"
#include "types.h"
#include "flash.h"

#define FLASH_APPIMG_BASE           0x60000000 //unused, read write base

#if defined(COREVERSION06)
#define FLASH_APPIMG_FLASH_OFFSET   0x334000
#define FLASH_APPIMG_FLASH_SIZE     0x12c000
//setting擦除地址 0x60000000 + (0x334000 + 0x12c000 - 0x2000) = 0x6045E000
#else
#define FLASH_APPIMG_FLASH_OFFSET   0x2c0000
#define FLASH_APPIMG_FLASH_SIZE     0x80000
//setting擦除地址 0x60000000 + (0x2c0000 + 0x80000 - 0x2000) = 0x6033E000
#endif

#define SETTING_DATA_SIZE   (4 * 1024)
#define SETTING_DATA_OFFSET (-8 * 1024)     //倒数8K   

#define FLASH_INNERFLASH_STARTADDRESS   ( FLASH_APPIMG_FLASH_OFFSET + FLASH_APPIMG_FLASH_SIZE + SETTING_DATA_OFFSET )
#define FLASH_INNERFLASH_ENDADDRESS 	( FLASH_APPIMG_FLASH_OFFSET + FLASH_APPIMG_FLASH_SIZE ) 

#define FLASH_SETTING_DATA_A ( FLASH_INNERFLASH_STARTADDRESS  )    //大小4K 
#define FLASH_SETTING_DATA_B ( FLASH_INNERFLASH_STARTADDRESS + SETTING_DATA_SIZE ) //大小4K  紧跟A后

static bool flash_write(u32 faddr, u8 *data, u32 size)
{
    uint8_t ret = 0 ;
    uint16_t offset = 0;
    uint16_t pages = 0;
    uint16_t remain = 0;
    uint32_t remainsize = 0;
    LOG_DEBUG("start faddr:0x%x offect:%d size:%d", faddr, offset, size);
    
    if(faddr > FLASH_INNERFLASH_ENDADDRESS || faddr < FLASH_INNERFLASH_STARTADDRESS)
    {	
        LOG_DEBUG("addr invalid! faddr:0x%x", faddr);
        return L_FALSE;
    }
    if((faddr + size) > FLASH_INNERFLASH_ENDADDRESS)
    {	
        LOG_DEBUG("no enough space size:%d", size);
        return L_FALSE;
    }
    offset = faddr % 4096 ;    //得到偏移量
    remain = 4096 - offset;    //本页剩余大小
    if(size < remain )  //不需要跨页写
    {	
        ret = fibo_inner_flash_erase(faddr-offset,4096);
        ret |= fibo_inner_flash_write(faddr,data,size);
    }
    else 
    {	
        LOG_DEBUG("**need faddr:0x%x offect:0x%x  size:%d",faddr,offset,size);
        ret |= fibo_inner_flash_erase(faddr-offset,4096);
        ret |= fibo_inner_flash_write(faddr,data,remain);  //先把第一页写完
        remainsize = size - remain ;
        pages = remainsize /4096;
        if ((remainsize % 4096) != 0 )
        {
            pages ++;
        }
        ret |= fibo_inner_flash_erase(faddr+remain, 4096 *pages);
        ret |= fibo_inner_flash_write(faddr+remain,data+remain,remainsize);
    }
    if(ret != 0)
    {
        return L_FALSE;
    }
    return L_TRUE;
}

static bool flash_read(uint32_t faddr,uint8_t *data,uint32_t size)
{
    return fibo_inner_flash_read(faddr,data,size);
}

static bool flash_isCheckPass(const ST_FLASH_DATA_HEADER *flashData)
{
    uint16_t i = 0;
    uint8_t *pos = NULL;
    uint8_t checksum = 0;
    
    if(flashData->signature != 0xAA)
    {
        return false;
    }
    
    //计算checksum
    pos = (uint8_t *)flashData;
    for(; i < flashData->payloadLen + 3; i++)
    {
        checksum += pos[i];
    }

    if(flashData->payload[flashData->payloadLen] != checksum)
    {
        return false;
    }

    return true;
}

/*
* DATA: SIGNATURE PAYLOADLEN ***PAYLOAD*** CHECKSUM
* PAYLOAD: TYPE VALUELEN VALUE
**/
const ST_FLASH_DATA_HEADER *flash_getBlockData(void)
{   	
    ST_FLASH_DATA_HEADER *flashData = (ST_FLASH_DATA_HEADER *)Malloc (1024);
//	LOG_DEBUG("flash_read");
//	LOG_DEBUG("FLASH_INNERFLASH_STARTADDRESS:0x%x  FLASH_INNERFLASH_ENDADDRESS:0x%x",FLASH_INNERFLASH_STARTADDRESS,FLASH_INNERFLASH_ENDADDRESS);
//	LOG_DEBUG("FLASH_SETTING_DATA_A:0x%x  FLASH_SETTING_DATA_B:0x%x",FLASH_SETTING_DATA_A,FLASH_SETTING_DATA_B);

    flash_read(FLASH_SETTING_DATA_A , (uint8_t *)flashData , 1024);
    if(flash_isCheckPass(flashData))
    {
        return flashData;
    }

    flash_read(FLASH_SETTING_DATA_B , (uint8_t *)flashData , 1024);
    if(flash_isCheckPass(flashData))
    {
        return flashData;
    }
    Free(flashData);
    return NULL;
}

/*
* function：将flag存在flash中 进行双份保存
**/
bool flash_save2Block(const ST_FLASH_DATA_HEADER *pData, unsigned int len)
{
    bool rcA = L_FALSE;
    bool rcB = L_FALSE;

    if(!pData || len > SETTING_DATA_SIZE)
    {
        return L_FALSE;
    }
    rcA = flash_write(FLASH_SETTING_DATA_A, (u8 *)pData, len);//erase the flash to write new app_data_storage

    rcB = flash_write(FLASH_SETTING_DATA_B, (u8 *)pData, len);

    LOG_DEBUG("[FLASH] Save Firmware Info, rcA:%d rcB:%d", rcA, rcB);
    return (rcA || rcB) ? true : false;
}

