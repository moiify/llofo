/*
 * uart.h
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */
#ifndef __USER_UART_H__
#define __USER_UART_H__
#include "fibo_opencpu.h"

#include "oc_uart.h"

typedef enum
{
    UART_PORT_UART1 = 0,
    UART_PORT_UART2 = 1,
    UART_PORT_UART3 = 2,
    UART_PORT_MAX
} UART_PORT_enum;

typedef int (*UART_PROC)(uint8_t *data, uint16_t dataLen);


int uart_initial(UART_PORT_enum port, int baud, int recvTimeout);
int uart_deinitial(UART_PORT_enum port);

int uart_print(const char* fmt, ...);

int uart_registerHandler(int port, UART_PROC handler);

#endif /* __USER_UART_H__ */


