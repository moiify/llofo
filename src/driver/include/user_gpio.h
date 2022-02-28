/*
 * user_gpio.h
 *
 *  Created on:  2020.04.03
 *      Author: lc
 */
#ifndef __USER_GPIO_H__
#define __USER_GPIO_H__
#include "fibo_opencpu.h"

enum
{
    PIN_GPIO_1 = 1,
    PIN_GPIO_2 = 2,
    PIN_GPIO_3 = 3,
    PIN_GPIO_4 = 4,
    PIN_GPIO_5 = 5,
    PIN_GPIO_6 = 6,
    PIN_GPIO_13 = 13,
    PIN_GPIO_23 = 23,
    PIN_GPIO_24 = 24,
    PIN_GPIO_25 = 25,
    PIN_GPIO_26 = 26,
    PIN_GPIO_27 = 27,
    PIN_GPIO_28 = 28,
    PIN_GPIO_29 = 29,
    PIN_GPIO_30 = 30,
    PIN_GPIO_31 = 31,
    PIN_GPIO_32 = 32,
    PIN_GPIO_33 = 33,
    PIN_GPIO_37 = 37,
    PIN_GPIO_38 = 38,
    PIN_GPIO_39 = 39,
    PIN_GPIO_40 = 40,
    PIN_GPIO_41 = 41,
    PIN_GPIO_42 = 42,
    PIN_ADC1_44 = 44,
    PIN_ADC0_45 = 45,
    PIN_GPIO_61 = 61,
    PIN_GPIO_62 = 62,
    PIN_GPIO_63 = 63,
    PIN_GPIO_64 = 64,
    PIN_GPIO_65 = 65,
    PIN_GPIO_66 = 66,
    PIN_GPIO_81 = 81,
    PIN_GPIO_82 = 82,
    PIN_UART1TX_67 = 67,
    PIN_UART1RX_68 = 68,
    PIN_GPIO_127    = 127,
    PIN_UART2RX_136 = 136,
    PIN_UART3RX_137 = 137,
    PIN_UART3TX_138 = 138,
    PIN_UART2TX_139 = 139,
    PIN_I2CSCL_141 = 141,
    PIN_I2CSDA_142 = 142,
    
    PIN_MAX
};

enum
{
    GPIO_DIR_INPUT=0,
    GPIO_DIR_OUTPUT,
};

typedef enum
{
    GPIO_LEVEL_LOW=0,
    GPIO_LEVEL_HIGH,
}GpioLevel_enum;


#endif /* __USER_GPIO_H__ */

