/*
 * hardware.h
 *
 *  Created on: 2017/04/21
 *      Author: Tom Chiang
 *
 *  Copyright (c) 2015 Wuhan Xiaoan Technology Co., Ltd. All rights reserved.
 *
 *  Define the hardware specific settings
 *
 */
#ifndef __USER_HARDWARE_COMMON_H__
#define __USER_HARDWARE_COMMON_H__

#include "uart.h"
#include "user_gpio.h"

#define UART_DEBUG   UART_PORT_UART2    //调试信息通道

#define UART_BLE     UART_PORT_UART1
#define UART_BMS     UART_PORT_UART1
#define UART_STM_DIA UART_PORT_UART1
#define UART_GPS     UART_PORT_UART3    //Ublox通信

#define PIN_ADCPWR_DETECT       PIN_ADC0_45         //电量检测
#define PIN_ADCCOMM_DETECT      PIN_ADC1_44         //检测

#define PIN_BLE_INT             PIN_GPIO_1          //蓝牙中断
#define PIN_LED_DRIVER          PIN_GPIO_2          //LED驱动控制
#define PIN_GNSSRTS_DRIVER      PIN_GPIO_3          //UBLOX8130复位控制
#define PIN_MPU6500_DRIVER      PIN_GPIO_4          //MPU6500使能控制
#define PIN_LIS_INT             PIN_GPIO_23         //加速度计中断
#define PIN_SPK_CTRL            PIN_GPIO_24         //喇叭驱动控制
#define PIN_SADDLE_DETECT       PIN_GPIO_29         //电池仓锁到位检测
#define PIN_BACKWHEEL_DETECT    PIN_GPIO_30         //后轮锁到位检测

#define PIN_OVERSPEED_DETECT    PIN_GPIO_31         //超速状态检测

#define PIN_ACC_DETECT          PIN_GPIO_33         //电门检测
#define PIN_SPEED_DETECT        PIN_GPIO_37         //轮动检测
#define PIN_CHARGE_DRIVER       PIN_GPIO_38         //充电使能控制
#define PIN_PWR_DETECT          PIN_GPIO_39         //断电检测
#define PIN_LED_GPS_DRIVER      PIN_GPIO_40         //GPS LED驱动控制
#define PIN_LED_NETWORK_DRIVER  PIN_GPIO_5          //LED灯控驱动
#define PIN_595_CLR             PIN_GPIO_28         //D触发器使能595OE
#define PIN_595_DATA_DRIVER     PIN_GPIO_27         //595DATA
#define PIN_595_LATCH_CLK       PIN_GPIO_26         //595LATCH
#define PIN_595_SHIFT_CLK       PIN_GPIO_25         //595SHIFT

#define PIN_HELMET4_LOCK_DETECT PIN_GPIO_30         //4芯头盔锁锁销到位检测
#define PIN_HELMET6_LOCK_DETECT PIN_GPIO_31         //6芯头盔锁锁销到位检测
#define PIN_HELMET6_EXIS_DETECT PIN_GPIO_30         //6芯头盔锁头盔在位检测

/*分别对应595的Q0->Q7*/
#define PIN_MASK_BLERST_DRIVER          (1 << 0)
#define PIN_MASK_SADDLE_P_DRIVER        (1 << 1)
#define PIN_MASK_BACKWHEEL_N_DRIVER     (1 << 2)
#define PIN_MASK_BACKWHEEL_P_DRIVER     (1 << 3)
#define PIN_MASK_ACC_DRIVER             (1 << 4)
#define PIN_MASK_SADDLE_N_DRIVER        (1 << 5)
#define PIN_MASK_BRAKE_DRIVER           (1 << 6)
#define PIN_MASK_VBUS_EN_DRIVER         (1 << 7)
#define PIN_MASK_HELMET_N_DRIVER        (1 << 2) //头盔锁解锁
#define PIN_MASK_HELMET_P_DRIVER        (1 << 3) //头盔锁上锁 
#define PIN_MASK_LIGHT_DRIVER           (1 << 6) //电平大灯

#define AUDIO_FILE_VOLUME (100)

void hardware_initial(void);
void gpio_init_595_CLR(void);

#endif/*__USER_HARDWARE_COMMON_H__*/

