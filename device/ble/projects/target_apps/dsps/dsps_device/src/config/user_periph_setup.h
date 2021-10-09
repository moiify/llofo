/**
 ****************************************************************************************
 *
 * @file user_periph_setup.h
 *
 * @brief Peripherals setup header file. 
 *
 * Copyright (C) 2016 Dialog Semiconductor.
 * This computer program includes Confidential, Proprietary Information  
 * of Dialog Semiconductor. All Rights Reserved.
 *
 ****************************************************************************************
 */
 
#ifndef _USER_PERIPH_SETUP_H_
    #define _USER_PERIPH_SETUP_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

    #include "rwip_config.h"
//    #include "global_io.h"
    #include "arch.h"
    #include "da1458x_periph_setup.h"
    #include "i2c_eeprom.h"
/*
 * DEFINES
 ****************************************************************************************
 */
//*** <<< Use Configuration Wizard in Context Menu >>> ***
// <o> Flow Control selection <0=> HW RTS/CTS  <1=> SW XON/XOFF
#define FLOW_CONTROL_CONFIG 0

#define CFG_UART_HW_FLOW_CTRL (FLOW_CONTROL_CONFIG==0)
#define CFG_UART_SW_FLOW_CTRL (FLOW_CONTROL_CONFIG==1) 

#if CFG_UART_SW_FLOW_CTRL
#define UART_SW_FLOW_ENABLED        1
#else
#define UART_SW_FLOW_ENABLED        0
#endif

#if CFG_UART_HW_FLOW_CTRL
#define UART_HW_FLOW_ENABLED        1
#else
#define UART_HW_FLOW_ENABLED        0
#endif


// <o> Baud Rate selection <1=> 9600 <2=> 19200 <3=> 38400 <4=> 57600 <5=> 115200
#define BAUDRATE_CONFIG 5
#define BAUDRATE_9K6 (BAUDRATE_CONFIG==1)
#define BAUDRATE_19K2 (BAUDRATE_CONFIG==2)
#define BAUDRATE_38K4 (BAUDRATE_CONFIG==3)
#define BAUDRATE_57K6 (BAUDRATE_CONFIG==4)
#define BAUDRATE_115K2 (BAUDRATE_CONFIG==5)
#define BAUDRATE_230K4 (BAUDRATE_CONFIG==6)
#define BAUDRATE_460K8 (BAUDRATE_CONFIG==7)
#define BAUDRATE_921K6 (BAUDRATE_CONFIG==8)


#if BAUDRATE_9K6
#define CFG_UART_SPS_BAUDRATE            UART_BAUDRATE_9K6
#define CFG_UART_SPS_FRAC_BAUDRATE       UART_FRAC_BAUDRATE_9K6
#endif

#if BAUDRATE_19K2
#define CFG_UART_SPS_BAUDRATE            UART_BAUDRATE_19K2
#define CFG_UART_SPS_FRAC_BAUDRATE       UART_FRAC_BAUDRATE_19K2
#endif

#if BAUDRATE_38K4
#define CFG_UART_SPS_BAUDRATE            UART_BAUDRATE_38K4
#define CFG_UART_SPS_FRAC_BAUDRATE       UART_FRAC_BAUDRATE_38K4
#endif

#if BAUDRATE_57K6
#define CFG_UART_SPS_BAUDRATE            UART_BAUDRATE_57K6
#define CFG_UART_SPS_FRAC_BAUDRATE       UART_FRAC_BAUDRATE_57K6
#endif

#if BAUDRATE_115K2
#define CFG_UART_SPS_BAUDRATE            UART_BAUDRATE_115K2
#define CFG_UART_SPS_FRAC_BAUDRATE       UART_FRAC_BAUDRATE_115K2
#endif

#if BAUDRATE_230K4
#warning "BAUD RATE NOT SUPPORTED, EXPERIMENTAL FEATURE"
#define CFG_UART_SPS_BAUDRATE            UART_BAUDRATE_230K4
#define CFG_UART_SPS_FRAC_BAUDRATE       UART_FRAC_BAUDRATE_230K4
#endif

#if BAUDRATE_460K8
#warning "BAUD RATE NOT SUPPORTED, EXPERIMENTAL FEATURE"
#define CFG_UART_SPS_BAUDRATE            UART_BAUDRATE_460K8
#define CFG_UART_SPS_FRAC_BAUDRATE       UART_FRAC_BAUDRATE_460K8
#endif

#if BAUDRATE_921K6
#warning "BAUD RATE NOT SUPPORTED, EXPERIMENTAL FEATURE"
#define CFG_UART_SPS_BAUDRATE            UART_BAUDRATE_921K6
#define CFG_UART_SPS_FRAC_BAUDRATE       UART_FRAC_BAUDRATE_921K6
#endif

#define UART_WAIT_BYTE_TIME             (CFG_UART_SPS_BAUDRATE * 10)        // time in uSec
#if UART_SW_FLOW_ENABLED
    #define UART_WAIT_BYTE_COUNTER          (UART_WAIT_BYTE_TIME * 8) + 30      //convert in for loop counter 
#else
    #define UART_WAIT_BYTE_COUNTER          (UART_WAIT_BYTE_TIME * 4) + 30      //convert in for loop counter 
#endif

/****************************************************************************************/ 
/* UART configuration                                                                   */
/****************************************************************************************/  

/*
#define GPIO_UART1_TX_PORT   GPIO_PORT_0
#define GPIO_UART1_TX_PIN    GPIO_PIN_4
#define GPIO_UART1_RX_PORT   GPIO_PORT_0
#define GPIO_UART1_RX_PIN    GPIO_PIN_5
#define GPIO_UART1_RTS_PORT  GPIO_PORT_0
#define GPIO_UART1_RTS_PIN   GPIO_PIN_6
#define GPIO_UART1_CTS_PORT  GPIO_PORT_0
#define GPIO_UART1_CTS_PIN   GPIO_PIN_7
*/

/****************************************************************************************/ 
/* UART2 GPIO configuration                                                             */
/****************************************************************************************/ 

/*
#ifdef CFG_PRINTF_UART2
#define  GPIO_UART2_TX_PORT     GPIO_PORT_0
#define  GPIO_UART2_TX_PIN      GPIO_PIN_1

#define  GPIO_UART2_RX_PORT     GPIO_PORT_0
#define  GPIO_UART2_RX_PIN      GPIO_PIN_2
#endif
*/

#define GPIO_DBG1_PORT   GPIO_PORT_1
#define GPIO_DBG1_PIN    GPIO_PIN_1
#define GPIO_DBG2_PORT   GPIO_PORT_1
#define GPIO_DBG2_PIN    GPIO_PIN_0
 
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
 
void periph_init(void);

void GPIO_reservations(void);



#endif // _USER_PERIPH_SETUP_H_
