/* Copyright (C) Xiaoan Technology Co., Ltd - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Tom Chiang <jiangtao@xiaoantech.com>, Seq 2017
 *
 * i2c_wrapper.c
 *
 * i2c驱动
 */
#include "fibo_opencpu.h"
#include <stdint.h>
#include <stdbool.h>

#include "i2c_wrapper.h"
#include "log.h"


static uint8_t g_chipID = 0;
bool i2c_init(uint8_t chipID)
{
    HAL_I2C_BPS_T i2c_config = {
        .i2c_name = 2,//I2C2
        .value = 1
    };
    i2c_close();
    int ret = i2c_open(i2c_config);
    if(ret < 0)
    {
        return false;
    }
    LOG_DEBUG("IIC init success");
    g_chipID = chipID;
    return true;
}

bool i2c_register_write(uint8_t register_address, uint8_t value)
{
    int ret = i2c_send_data(g_chipID, register_address, false, &value, 1);
    if(ret < 0)
    {
        return false;
    }
    return true;
}
bool i2c_register_write_num(uint8_t register_address, uint8_t *values, int num_bytes)
{
    int ret = i2c_send_data(g_chipID, register_address, false, values, num_bytes);
    if(ret < 0)
    {
        return false;
    }
    return true;
}

bool i2c_register_read(uint8_t first_reg_address, uint8_t *p_destination, uint8_t num_bytes)
{
    static u16 i2cErrorCn = 0;
    if(i2cErrorCn < 50)
    {
        int ret = i2c_get_data(g_chipID, first_reg_address, false,p_destination, num_bytes);
        if(ret < 0)
        {
            i2cErrorCn++;
            return false;
        }
		i2cErrorCn = 0;
		return true;
    }
	return false;   //IIC读有异常了,上报加速度计错误靠detect检测
}

