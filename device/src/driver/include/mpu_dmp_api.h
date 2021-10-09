#ifndef _MPU_DMP_API_H_
#define _MPU_DMP_API_H_

#include "types.h"

extern float yaw_cal;

short get_xaccel_data(void);
short get_yaccel_data(void);
short get_zaccel_data(void);

u8 mpu_dmp_init(void);
u8 mpu_dmp_getData(void);
u8 mpu_iic_write_byte(u8 slave_addr, u8 reg, u8 byte_num, u8 *data);
u8 mpu_iic_read_byte(u8 slave_addr, u8 reg, u8 num_bytes, u8 * p_destination);

#endif



