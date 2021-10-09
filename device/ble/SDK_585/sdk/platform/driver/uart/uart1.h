
#ifndef _USER_UART1_H_
#define _USER_UART1_H_

/**
 ****************************************************************************************
 * @defgroup UART UART
 * @ingroup DRIVERS
 *
 * @brief UART driver
 *
 * @{
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>       // integer definition
#include <stdbool.h>      // boolean definition

#include "app_easy_timer.h" 

#include "hardware.h"
/*
 * DEFINES
 *****************************************************************************************
 */

//#define UART_BAUDRATE_115K2         9
//#define UART_BAUDRATE_9K6           104

// uart1 <-> 800c
//UART1 PIN CONFIG
#define 	UART1_TX_PORT           GPIO_PORT_0
#define 	UART1_TX_PIN            GPIO_PIN_2
#define 	UART1_RX_PORT           GPIO_PORT_0
#define 	UART1_RX_PIN            GPIO_PIN_3

// uart2 <-> bms/controller
//UART2 PIN CONFIG
#define 	UART2_TX_PORT           GPIO_PORT_0
#define 	UART2_TX_PIN            GPIO_PIN_4
#define 	UART2_RX_PORT           GPIO_PORT_0
#define 	UART2_RX_PIN            GPIO_PIN_5

#define     UART2_485_EN_PORT       GPIO_PORT_2
#define     UART2_485_EN_PIN        GPIO_PIN_1

// 旧的配置 （留存备份
//// uart1 -> 800c
////UART1 PIN CONDIG
//#define 	UART1_TX_PORT           GPIO_PORT_0
//#define 	UART1_TX_PIN            GPIO_PIN_2
//#define 	UART1_RX_PORT           GPIO_PORT_0
//#define 	UART1_RX_PIN            GPIO_PIN_3

////UART2 PIN CONFIG
//#define 	UART2_TX_PORT           GPIO_PORT_0
//#define 	UART2_TX_PIN            GPIO_PIN_0
//#define 	UART2_RX_PORT           GPIO_PORT_0
//#define 	UART2_RX_PIN            GPIO_PIN_1

//#define     UART2_485_EN_PORT       GPIO_PORT_2
//#define     UART2_485_EN_PIN        GPIO_PIN_1

//#define     UART2_485_EN_PORT2       GPIO_PORT_0
//#define     UART2_485_EN_PIN2        GPIO_PIN_4


/*
 * ENUMERATION DEFINITIONS
 *****************************************************************************************
 */

/// Generic enable/disable enum for UART driver
typedef enum
{
    /// uart disable
    UART_DISABLE = 0,
    /// uart enable
    UART_ENABLE  = 1
}ENUM_UART1_1;

/// Character format
typedef enum
{
    /// char format 5
    UART_CHARFORMAT_5 = 0,
    /// char format 6
    UART_CHARFORMAT_6 = 1,
    /// char format 7
    UART_CHARFORMAT_7 = 2,
    /// char format 8
    UART_CHARFORMAT_8 = 3
}ENUM_UART1_2;

/// Stop bit
typedef enum
{
    /// stop bit 1
    UART_STOPBITS_1 = 0,
    /* Note: The number of stop bits is 1.5 if a
     * character format with 5 bit is chosen */
    /// stop bit 2
    UART_STOPBITS_2 = 1
}ENUM_UART1_3;

/// Parity bit
typedef enum
{
    /// even parity
    UART_PARITYBIT_EVEN  = 0,
    /// odd parity
    UART_PARITYBIT_ODD   = 1,
    /// space parity
    UART_PARITYBIT_SPACE = 2, // The parity bit is always 0.
    /// mark parity
    UART_PARITYBIT_MARK  = 3  // The parity bit is always 1.
}ENUM_UART1_4;

/* Error detection */
typedef enum
{
    /// error detection disabled
    UART_ERROR_DETECT_DISABLED = 0,
    /// error detection enabled
    UART_ERROR_DETECT_ENABLED  = 1
}ENUM_UART1_5;

/// status values
typedef enum
{
    /// status ok
    UART_STATUS_OK,
    /// status not ok
    UART_STATUS_ERROR,
		UART_STATUS_TIMEOUT
}ENUM_UART1_6;

typedef enum UART_ID
{
    MODEM_STAT      = 0,
    NO_INT_PEND     = 1,
    THR_EMPTY       = 2,
    RECEIVED_AVAILABLE  = 4,
    UART_TIMEOUT        = 12
}ENUM_UART1_7;

/* / RX_LVL values */
typedef enum UART_RXLVL
{
    UART_RXLVL_1,
    UART_RXLVL_4,
    UART_RXLVL_8,
    UART_RXLVL_14
}ENUM_UART1_8;

/* / WORD_LEN values */
typedef enum UART_WORDLEN
{
    UART_WORDLEN_5,
    UART_WORDLEN_6,
    UART_WORDLEN_7,
    UART_WORDLEN_8
}ENUM_UART1_9;

/* / FIFO_SZ values */
typedef enum UART_FIFOSIZE
{
    UART_FIFOSIZE_16,
    UART_FIFOSIZE_32,
    UART_FIFOSIZE_64,
    UART_FIFOSIZE_128
}ENUM_UART1_10;

/// flow control states
typedef enum
{
    /// just data send or received
    UART_NONE 	= (uint8_t)0x00,
    /// 
    UART_XON 	= (uint8_t)0x01,
	/// 
	UART_XOFF 	= (uint8_t)0x02,
}ENUM_UART1_11;

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
void app_uart1_init(void);
void uart1_configPIN(void);
void uart1_reserve_gpio(void);
void uart1_sendData(uint8_t *data, uint16_t length);
void uart1_enqueneData(const uint8_t *data, uint16_t length);
void uart1_launch(void);
uint8_t uart1_isUartBusy(void);

void app_uart2_init(void);
void uart2_configPIN(void);
void uart2_reserve_gpio(void);
void uart2_sendData(uint8_t *data, uint16_t length);
void uart2_launch(void);
uint8_t uart2_isUartBusy(void);

void app_timer0_init(void);

#define UART_BUFFER_LEN (500)
    
struct UART_TX_EN {
    uint8_t busyFlag;
    int16_t remain;
    int16_t pos;
    uint8_t buffer[UART_BUFFER_LEN];
};

struct UART_RX_EN {
    int16_t length;
    uint8_t buffer[UART_BUFFER_LEN];
};

extern struct UART_RX_EN *uart1_rx;
extern struct UART_RX_EN *uart2_rx;


#endif /* _USER_UART1_H_ */

