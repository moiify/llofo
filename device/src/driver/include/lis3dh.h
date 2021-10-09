/* Copyright (C) Xiaoan Technology Co., Ltd - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Tom Chiang <jiangtao@xiaoantech.com>, Sep 2017
 *
 * lis3dh.h
 *
 * lis3dh驱动
 */

#ifndef __LIS3DH_H_
#define __LIS3DH_H_

#include <stdint.h>
#include <stdbool.h>

#define LIS3DH_I2C_ADDR				(0x32 >> 1) //7-bit I2C address 右移是因为硬件IIC会补最低RW位

#define I2C_SPEED_FAST_MODE         (400)
#define I2C_SPEED_NORMAL_MODE       (100)

#define LIS3DH_DEVICE_ID        0x33

#define LIS3DH_REG_STATUS_AUX  0x07
#define LIS3DH_REG_OUT_ADC1_L  0x08
#define LIS3DH_REG_OUT_ADC1_H  0x09
#define LIS3DH_REG_OUT_ADC2_L  0x0a
#define LIS3DH_REG_OUT_ADC2_H  0x0b
#define LIS3DH_REG_OUT_ADC3_L  0x0c
#define LIS3DH_REG_OUT_ADC3_H  0x0d
#define LIS3DH_REG_INT_COUNTER_REG  0x0e
#define LIS3DH_REG_WHO_AM_I  0x0f
#define LIS3DH_REG_TEMP_CFG_REG  0x1f
#define LIS3DH_REG_CTRL_REG1  0x20
#define LIS3DH_REG_CTRL_REG2  0x21
#define LIS3DH_REG_CTRL_REG3  0x22
#define LIS3DH_REG_CTRL_REG4  0x23
#define LIS3DH_REG_CTRL_REG5  0x24
#define LIS3DH_REG_CTRL_REG6  0x25
#define LIS3DH_REG_REFERENCE  0x26
#define LIS3DH_REG_STATUS_REG  0x27
#define LIS3DH_REG_OUT_X_L  0x28
#define LIS3DH_REG_OUT_X_H  0x29
#define LIS3DH_REG_OUT_Y_L  0x2a
#define LIS3DH_REG_OUT_Y_H  0x2b
#define LIS3DH_REG_OUT_Z_L  0x2c
#define LIS3DH_REG_OUT_Z_H  0x2d
#define LIS3DH_REG_FIFO_CTRL_REG  0x2e
#define LIS3DH_REG_FIFO_SRC_REG  0x2f
#define LIS3DH_REG_INT1_CFG  0x30
#define LIS3DH_REG_INT1_SRC  0x31
#define LIS3DH_REG_INT1_THS  0x32
#define LIS3DH_REG_INT1_DURATION  0x33
#define LIS3DH_REG_CLICK_CFG  0x38
#define LIS3DH_REG_CLICK_SRC  0x39
#define LIS3DH_REG_CLICK_THS  0x3a
#define LIS3DH_REG_TIME_LIMIT  0x3b
#define LIS3DH_REG_TIME_LATENCY  0x3c
#define LIS3DH_REG_TIME_WINDOW  0x3d

#define LIS3DH_STATUS_AUX_321OR  0x80
#define LIS3DH_STATUS_AUX_3OR  0x40
#define LIS3DH_STATUS_AUX_2OR  0x20
#define LIS3DH_STATUS_AUX_1OR  0x10
#define LIS3DH_STATUS_AUX_321DA  0x08
#define LIS3DH_STATUS_AUX_3DA  0x04
#define LIS3DH_STATUS_AUX_2DA  0x02
#define LIS3DH_STATUS_AUX_1DA  0x01

#define LIS3DH_CTRL_REG1_ODR3  0x80
#define LIS3DH_CTRL_REG1_ODR2  0x40
#define LIS3DH_CTRL_REG1_ODR1  0x20
#define LIS3DH_CTRL_REG1_ODR0  0x10
#define LIS3DH_CTRL_REG1_LPEN  0x08
#define LIS3DH_CTRL_REG1_ZEN  0x04
#define LIS3DH_CTRL_REG1_YEN  0x02
#define LIS3DH_CTRL_REG1_XEN  0x01

#define LIS3DH_RATE_1_HZ    0x10
#define LIS3DH_RATE_10_HZ   0x20
#define LIS3DH_RATE_25_HZ   0x30
#define LIS3DH_RATE_50_HZ   0x40
#define LIS3DH_RATE_100_HZ  0x50
#define LIS3DH_RATE_200_HZ  0x60
#define LIS3DH_RATE_400_HZ  0x70

#define LIS3DH_CTRL_REG2_HPM1  0x80
#define LIS3DH_CTRL_REG2_HPM0  0x40
#define LIS3DH_CTRL_REG2_HPCF2  0x20
#define LIS3DH_CTRL_REG2_HPCF1  0x10
#define LIS3DH_CTRL_REG2_FDS  0x08
#define LIS3DH_CTRL_REG2_HPCLICK  0x04
#define LIS3DH_CTRL_REG2_HPIS2  0x02
#define LIS3DH_CTRL_REG2_HPIS1  0x01


#define LIS3DH_CTRL_REG3_I1_CLICK  0x80
#define LIS3DH_CTRL_REG3_I1_INT1  0x40
#define LIS3DH_CTRL_REG3_I1_DRDY  0x10
#define LIS3DH_CTRL_REG3_I1_WTM  0x04
#define LIS3DH_CTRL_REG3_I1_OVERRUN  0x02

#define LIS3DH_CTRL_REG4_BDU  0x80
#define LIS3DH_CTRL_REG4_BLE  0x40
#define LIS3DH_CTRL_REG4_FS1  0x20
#define LIS3DH_CTRL_REG4_FS0  0x10
#define LIS3DH_CTRL_REG4_HR  0x08
#define LIS3DH_CTRL_REG4_ST1  0x04
#define LIS3DH_CTRL_REG4_ST0  0x02
#define LIS3DH_CTRL_REG4_SIM  0x01


#define LIS3DH_CTRL_REG5_BOOT  0x80
#define LIS3DH_CTRL_REG5_FIFO_EN  0x40
#define LIS3DH_CTRL_REG5_LIR_INT1  0x08
#define LIS3DH_CTRL_REG5_D4D_INT1  0x04

#define LIS3DH_CTRL_REG6_I2_CLICK  0x80
#define LIS3DH_CTRL_REG6_I2_INT2  0x40
#define LIS3DH_CTRL_REG6_BOOT_I2  0x10
#define LIS3DH_CTRL_REG6_H_LACTIVE  0x02
 
#define LIS3DH_INT1_CFG_AOI  0x80
#define LIS3DH_INT1_CFG_6D  0x40
#define LIS3DH_INT1_CFG_ZHIE_ZUPE  0x20
#define LIS3DH_INT1_CFG_ZLIE_ZDOWNE  0x10
#define LIS3DH_INT1_CFG_YHIE_YUPE  0x08
#define LIS3DH_INT1_CFG_YLIE_YDOWNE  0x04
#define LIS3DH_INT1_CFG_XHIE_XUPE  0x02
#define LIS3DH_INT1_CFG_XLIE_XDOWNE  0x01

#define LIS3DH_INT1_SRC_IA  0x40
#define LIS3DH_INT1_SRC_ZH  0x20
#define LIS3DH_INT1_SRC_ZL  0x10
#define LIS3DH_INT1_SRC_YH  0x08
#define LIS3DH_INT1_SRC_YL  0x04
#define LIS3DH_INT1_SRC_XH  0x02
#define LIS3DH_INT1_SRC_XL  0x01

#define LIS3DH_TEMP_CFG_ADC_PD  0x80
#define LIS3DH_TEMP_CFG_TEMP_EN  0x40

#define LIS3DH_FIFO_CTRL_BYPASS  0x00
#define LIS3DH_FIFO_CTRL_FIFO  0x40
#define LIS3DH_FIFO_CTRL_STREAM  0x80
#define LIS3DH_FIFO_CTRL_STREAM_TO_FIFO  0xc0

#define LIS3DH_FIFO_SRC_WTM  0x80
#define LIS3DH_FIFO_SRC_OVRN  0x40
#define LIS3DH_FIFO_SRC_EMPTY  0x20
#define LIS3DH_FIFO_SRC_FSS_MASK  0x1f

bool lis3dh_printRegister(uint8_t registers);

bool lis3dh_init(void);

bool lis3dh_config(void);

bool lis3dh_verify_device_id(void);

bool lis3dh_isINThappened(void);

bool lis3dh_readOutputXYZ(short * x_data, short * y_data, short * z_data);

bool lis3dh_initial(void);



#endif //__LIS3DH_H_
