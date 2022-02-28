/*
 * log.c
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */

#include "log.h"
#include "uart.h"
#include "msg.h"
#include "utils.h"
#include "data.h"

/*
 * The hex log is in the following format:
 *
 *     0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F      0123456789ABCDEF
 * 01  aa 55 01 00 00 00 25 00 38 36 35 30 36 37 30 32     .U....%.86506702
 * 02  30 34 39 30 31 36 38 30 00 00 00 00 00 00 00 00     04901680........
 * 03  00 00 00 00 00 00 00 00 00 00 00 00                 ............
 *
 */
void log_hex(const void *buf, int length)
{
    if(length > 1024)
    {
        uart_print("log hex over length.");
        return;
    }
    char *hexMsg = (char *)Malloc(10 * 1024);//10K内存 本地释放
    if(!hexMsg)
    {
        uart_print("log hex malloc error.");
        return;
    }
    memset(hexMsg, 0, 10 * 1024);

    
    int i = 0, j = 0;
    const char *data = (const char *)buf;

    
    sprintf(hexMsg + strlen(hexMsg), "    ");
    for (i  = 0; i < 16; i++)
    {
        sprintf(hexMsg + strlen(hexMsg), "%X  ", i);
    }
        sprintf(hexMsg + strlen(hexMsg), "    ");
    for (i = 0; i < 16; i++)
    {
        sprintf(hexMsg + strlen(hexMsg), "%X", i);
    }

    sprintf(hexMsg + strlen(hexMsg), "\r\n");

    for (i = 0; i < length; i += 16)
    {
        sprintf(hexMsg + strlen(hexMsg), "%02d  ", i / 16 + 1);
        for (j = i; j < i + 16 && j < length; j++)
        {
            sprintf(hexMsg + strlen(hexMsg), "%02x ", data[j] & 0xff);
        }
        if (j == length && length % 16)
        {
            for (j = 0; j < (16 - length % 16); j++)
            {
                sprintf(hexMsg + strlen(hexMsg), "    ");
            }
        }
        sprintf(hexMsg + strlen(hexMsg), "    ");
        for (j = i; j < i + 16 && j < length; j++)
        {
            if (data[j] < 32 || data[j] >= 127)
            {
                sprintf(hexMsg + strlen(hexMsg), ".");
            }
            else
            {
                sprintf(hexMsg + strlen(hexMsg), "%c", data[j] & 0xff);
            }
        }

        sprintf(hexMsg + strlen(hexMsg), "\r\n");
    }
    uart_print("%s", hexMsg);
    Free(hexMsg);
}

/*
 * 打印二进制数据接口
 * 当前仅支持打印前32个字节的二进制数据
 */
#define MAX_PRINTED_BIN_LENGTH (64)
void log_binary(const char* data, int length)
{
    char buf[MAX_PRINTED_BIN_LENGTH * 3 + 12] = {0};
    int i = 0;

    for (i = 0; i < length && i < MAX_PRINTED_BIN_LENGTH; i++)
    {
        sprintf(buf + i * 3, "%02X", data[i]);
        buf[i * 3 + 2] = ' ';   //because sprintf will add a terminating null character at the end
    }

    if (i >= MAX_PRINTED_BIN_LENGTH)
    {
        sprintf(buf + i * 3, "%s", "......\n");
    }

    uart_print("%s\r\n", buf);
}

