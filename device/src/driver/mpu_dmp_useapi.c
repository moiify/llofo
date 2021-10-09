/**
 *   @defgroup  eMPL
 *   @brief     Embedded Motion Processing Library
 *
 *   @{
 *       @file      motion_driver_test.c
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "dmpKey.h"
#include "dmpmap.h"
#include "inv_mpu.h"
#include "mpu_dmp_api.h"
#include "inv_mpu_dmp_motion_driver.h"

#include "fibo_opencpu.h"

#include "log.h"
#include "types.h"
#include "i2c_wrapper.h"

volatile u8 g_mpuAddr = 0x68;

/* Data requested by client. */
#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)

#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)

#define MOTION          (0)
#define NO_MOTION       (1)

#define SUCCESS         (0)

/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (20)

#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)

struct rx_s {
    unsigned char header[3];
    unsigned char cmd;
};
struct hal_s {
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned short report;
    unsigned short dmp_features;
    unsigned char motion_int_mode;
    struct rx_s rx;
};
static struct hal_s hal = {0};

/* USB RX binary semaphore. Actually, it's just a flag. Not included in struct
 * because it's declared extern elsewhere.
 */
volatile unsigned char rx_new;

/* The sensors can be mounted onto the board in any orientation. The mounting
 * matrix seen below tells the MPL how to rotate the raw data from thei
 * driver(s).
 * TODO: The following matrices refer to the configuration on an internal test
 * board at Invensense. If needed, please modify the matrices to match the
 * chip-to-body matrix for your particular set up.
 */
static signed char gyro_orientation[9] = { 1, 0, 0,
						                   0, 1, 0,
						                   0, 0, 1};

u8 mpu_iic_write_byte(u8 slave_addr, u8 reg, u8 byte_num, u8 *data)
{
    int ret = i2c_send_data((u32)g_mpuAddr, (u32)reg, false, data, byte_num);
    if(ret < 0)
    {
        if(g_mpuAddr == 0x68)
        {
            g_mpuAddr = 0x69;
        }
        else
        {
            g_mpuAddr = 0x68;
        }
        int ret = i2c_send_data((u32)g_mpuAddr, (u32)reg, false, data, byte_num);
        if(ret < 0)
        {
            return 1;
        }
    }
    return 0;	
}

u8 mpu_iic_read_byte(u8 slave_addr, u8 reg, uint8_t num_bytes, uint8_t *p_destination)
{
    int ret = i2c_get_data((u32)g_mpuAddr, (u32)reg, false, p_destination, num_bytes);
    if(ret < 0)
    {
        if(g_mpuAddr == 0x68)
        {
            g_mpuAddr = 0x69;
        }
        else
        {
            g_mpuAddr = 0x68;
        }
        int ret = i2c_get_data((u32)g_mpuAddr, (u32)reg, false, p_destination, num_bytes);
        if(ret < 0)
        {
            return 1;
        }
    }
    return 0;	
}

/* These next two functions converts the orientation matrix (see
 * gyro_orientation) to a scalar representation for use by the DMP.
 * NOTE: These functions are borrowed from Invensense's MPL.
 */
static unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
    unsigned short scalar;

    /*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
     */

    scalar =  inv_row_2_scale(mtx);
    scalar |= inv_row_2_scale(mtx + 3) << 3;
    scalar |= inv_row_2_scale(mtx + 6) << 6;

    return scalar;
}

static void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x7) {
        /* Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
		//LOG_DEBUG("gyro[0]:%ld, gyro[1]:%ld, gyro[2]:%ld", gyro[0], gyro[1], gyro[2]);
		gyro[0]= 555681;
		gyro[1]= 867150;
		gyro[2]= 384809;
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
		
		accel[0]= 47251456;
		accel[1]= -22757376;
		accel[2]= -105349120;

        dmp_set_accel_bias(accel);
		LOG_DEBUG("self test sucess");
    }
	else
	{
		LOG_DEBUG("self test failed, result %d",result);
	}
}

/* Every time new gyro data is available, this function is called in an
 * ISR context. In this example, it sets a flag protecting the FIFO read
 * function.
 */
static void gyro_data_ready_cb(void)
{
    hal.new_gyro = 1;
}

u8 mpu_dmp_init(void)
{
    if(false == i2c_init(0x68))
    {
		LOG_DEBUG("i2c init error");
		return 1;
    }
    
    if(SUCCESS != mpu_init()) 
    {
		LOG_DEBUG("mpu init error");
		return 1;
	}

	if(SUCCESS != mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
	{
		LOG_DEBUG("mpu_set_sensors error");
		return 2;
	}
	
	if(SUCCESS != mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))		  //mpu_configure_fifo
	{
		LOG_DEBUG("mpu_configure_fifo error");
		return 3;
	}
	
	if(SUCCESS != mpu_set_sample_rate(DEFAULT_MPU_HZ))		  //mpu_set_sample_rate
	{
		LOG_DEBUG("mpu_set_sample_rate error");
		return 4;
	}

    hal.sensors = ACCEL_ON | GYRO_ON;
	hal.dmp_on = 0;

	if(SUCCESS != dmp_load_motion_driver_firmware())
	{
		LOG_DEBUG("dmp_load_motion_driver_firmware error");
		return 5;
	}
	
	if(SUCCESS != dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)))    //12.推送陀螺仪和加速度计的方向矩阵到DMP
	{
		LOG_DEBUG("dmp_set_orientation error");
		return 6;
	}
	
    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT |
        DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
        DMP_FEATURE_GYRO_CAL;
    if(SUCCESS != dmp_enable_feature(hal.dmp_features))				//14.使能上述功能
	{
		LOG_DEBUG("dmp_enable_feature error");
		return 7;
	}

    if(SUCCESS != dmp_set_fifo_rate(DEFAULT_MPU_HZ)) 					//15.配置DMP的FIFO速率
	{
		LOG_DEBUG("dmp_set_fifo_rate error");
		return 8;
	}	
    mpu_set_dmp_state(1); 									//16.开启DMP
    hal.dmp_on = 1;											//17.标志位-"DMP状态"为开启
			
	run_self_test();										//18.DMP的自检，就是标定现在的状态为坐标原点

	return 0;
}

float yaw_cal;

static short x_acc = 0, y_acc = 0, z_acc = 0;
short get_xaccel_data(void)
{
	return x_acc;
}
short get_yaccel_data(void)
{
	return y_acc;
}
short get_zaccel_data(void)
{
	return z_acc;
}

u8 mpu_dmp_getData(void)
{
    u8 more = 0;
    short gyro[3] = {0}, accel[3] = {0}, sensors = 0;
    unsigned long sensor_timestamp;

    long quat[4] = {0};
    float q30 = 1073741824;
    float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
    float pitch = 0.0f, roll = 0.0f, yaw = 0.0f;
    
    gyro_data_ready_cb(); 				  //数据采集结束标志位
    if (hal.new_gyro && hal.dmp_on)		  //用于计算四元数函数
    {
        if(dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,&more))
        {
            return 1;
        }

        if (!more)
        {
            hal.new_gyro = 0;
        }

        if(sensors & INV_WXYZ_QUAT)
        {
            q0=quat[0]/q30;
            q1=quat[1]/q30;
            q2=quat[2]/q30;
            q3=quat[3]/q30;

            pitch=asin((-2)*q1*q3+2*q0*q2)*57.3;
            roll=atan2(2*q2*q3+2*q0*q1,(-2)*q1*q1-2*q2*q2+1)*57.3;
            yaw=atan2(2*(q1*q2+q0*q3),q0*q0+q1*q1-q2*q2-q3*q3)*57.3;
            yaw_cal = (yaw>0)?(360 - yaw):(-yaw);
        }

        if(sensors & INV_XYZ_ACCEL) 
        {
            x_acc = accel[0];
            y_acc = accel[1];
            z_acc = accel[2];
        }
    }		  
    return 0;
}

