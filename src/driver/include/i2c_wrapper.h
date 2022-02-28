/*
 * i2c_wrapper.h
 *
 *  Created on: 2018/06/03
 *      Author: lc
 */
#ifndef _IIC_WRAPPER_H_
#define _IIC_WRAPPER_H_

#include <stdint.h>
#include <stdbool.h>

bool i2c_init(uint8_t chipID);
bool i2c_register_write(uint8_t register_address, uint8_t value);
bool i2c_register_read(uint8_t first_reg_address, uint8_t * p_destination, uint8_t num_bytes);
bool i2c_register_write_num(uint8_t register_address, uint8_t *values, int num_bytes);

#endif/*_IIC_WRAPPER_H_*/
