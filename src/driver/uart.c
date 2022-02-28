/*
 * uart.h
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */
#include "msg.h"
#include "uart.h"
#include "hardware.h"
#include "user_gpio.h"
#include "data.h"
#include "da14580.h"
#include "request.h"

static UART_PROC uart_proc_handler[UART_PORT_MAX] = {0};

static void uart_recv(hal_uart_port_t uart_port, UINT8 *data, UINT16 len, void *arg)
{
    if(uart_proc_handler[uart_port])
    {
        if(data != NULL)
        {
            uart_proc_handler[uart_port](data, len);
        }
    }
}

static volatile u32 log_seq = 0;
static u32 log_getseq(void)
{
    return log_seq++;
}

/*
 * print message via UART
 *
 * Note:
 *      the message length is limited to 256 bytes
 */
int uart_print(const char *fmt, ...)
{
    static unsigned char *buf = NULL;
    static unsigned char *fmtAdd = NULL;
    int length = 0;

    if(!buf)
    {
        buf = Malloc(1024);
        fmtAdd = Malloc(128);
    }

    if(buf)
    {
        memset(buf, 0, 1024);
        memset(fmtAdd, 0, 128);

        va_list arg;
        va_start (arg, fmt);
        if(data_getData()->ble_workMode)
        {
            snprintf((char *)fmtAdd, 128, "%d -%s", log_getseq(), fmt);
            vsnprintf((char *)buf, 1023, (const char *)fmtAdd, arg);

            length = strlen((const char *)buf);
            fibo_hal_uart_put(UART_DEBUG, buf, length > 1024 ? 1024 : length);
            if(setting.settingConf.isBackLogOn)
            {
                cmd_printUDP("%s", buf);
            }
            da14580_sendDATA(BLE_ADDRESS, 0, buf, length > 1024 ? 1024 : length);
        }
        else
        {
            vsnprintf((char *)buf, 1024, fmt, arg);

            length = strlen((const char *)buf);
            fibo_hal_uart_put(UART_DEBUG, buf, length > 1024 ? 1024 : length);
            if(setting.settingConf.isBackLogOn)
            {
                cmd_printUDP("%s", buf);
            }
        }
        va_end(arg);
    }
    return 0;
}

int uart_registerHandler(int port, UART_PROC handler)
{
    uart_proc_handler[port] = handler;
    return 0;
}

int uart_initial(UART_PORT_enum port, int baud, int recvTimeout)
{
    hal_uart_config_t uart_config =
    {
        .baud = baud,
        .data_bits = HAL_UART_DATA_BITS_8,
        .stop_bits = HAL_UART_STOP_BITS_1,
        .rx_buf_size = UART_RX_BUF_SIZE,
        .tx_buf_size = UART_TX_BUF_SIZE,
        .parity = HAL_UART_NO_PARITY
    };
    fibo_hal_uart_deinit(port);
    if(port == UART_PORT_UART1)
    {
    
    }
    if(port == UART_PORT_UART2)
    {
        fibo_gpio_mode_set(PIN_UART2RX_136, 1);
        fibo_gpio_mode_set(PIN_UART2TX_139, 1);
    }
    if(port == UART_PORT_UART3)
    {
        fibo_gpio_mode_set(PIN_UART3RX_137, 4);
        fibo_gpio_mode_set(PIN_UART3TX_138, 4);
    }
    if(recvTimeout)
    {
        uart_config.recv_timeout = recvTimeout;
    }
    return fibo_hal_uart_init(port, &uart_config, uart_recv, NULL);//可以收发
}

int uart_deinitial(UART_PORT_enum port)
{
    fibo_hal_uart_deinit(port);
	return 0;
}

