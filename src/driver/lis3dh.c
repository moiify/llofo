#include "i2c_wrapper.h"
#include "lis3dh.h"
#include "log.h"

bool lis3dh_printRegister(uint8_t registers)
{
    uint8_t value1 = 0;
    i2c_register_read(registers, &value1, 1);
    LOG_DEBUG("%x: %x", registers, value1);
    return true;
}

bool lis3dh_init(void)
{
    i2c_init(LIS3DH_I2C_ADDR);
    return lis3dh_verify_device_id();
}

bool lis3dh_verify_device_id(void)
{
    uint8_t device_id = 0;
    
    lis3dh_printRegister(LIS3DH_REG_WHO_AM_I);

    if (!i2c_register_read(LIS3DH_REG_WHO_AM_I, &device_id, 1))
    {
        LOG_ERROR("failed to read lis3dh device ID");
        return false;
    }
    LOG_INFO("LIS3DH device id = %#X", device_id);

    return (device_id == LIS3DH_DEVICE_ID) ? true : false;
}

bool lis3dh_config(void)
{
    uint8_t value_reg;
    bool result = true;

    // ODR:50Hz  低功耗模式 XYZ三轴使能
    result = result && i2c_register_write(LIS3DH_REG_CTRL_REG1, LIS3DH_RATE_200_HZ | LIS3DH_CTRL_REG1_ZEN | LIS3DH_CTRL_REG1_YEN | LIS3DH_CTRL_REG1_XEN);

    // 滤波正常模式
    result = result && i2c_register_write(LIS3DH_REG_CTRL_REG2, LIS3DH_CTRL_REG2_HPM1 | LIS3DH_CTRL_REG2_HPIS1);
        
    // ZYXDA 三轴中断绑定在INT1管脚
    result = result && i2c_register_write(LIS3DH_REG_CTRL_REG3, LIS3DH_CTRL_REG3_I1_INT1);

    // 使能高精度模式
    result = result && i2c_register_write(LIS3DH_REG_CTRL_REG4, LIS3DH_CTRL_REG4_HR);
    
    //设置中断阈值
    result = result && i2c_register_write(LIS3DH_REG_INT1_THS, 7); // 7*16mg = 112mg
    
    //读取reference 进行比较
    result = result && i2c_register_read(LIS3DH_REG_REFERENCE, &value_reg, 1);
    
    //使能三轴高位中断
    result = result && i2c_register_write(LIS3DH_REG_INT1_CFG, LIS3DH_INT1_SRC_ZH | LIS3DH_INT1_SRC_YH | LIS3DH_INT1_SRC_XH);        
    return result ? true : false;
}

bool lis3dh_isINThappened(void)
{
    uint8_t int_src = 0;

    bool rc = i2c_register_read(LIS3DH_REG_INT1_SRC, &int_src, sizeof(int_src));
    if (!rc)
    {
        LOG_ERROR("IIC read %d error", LIS3DH_REG_INT1_SRC);
        return false;
    }

    //根据不同的中断源分别处理
    if (int_src & LIS3DH_INT1_SRC_IA)
    {
        return true;
    }

    return false;
}

bool lis3dh_readOutputXYZ(short *x_data, short *y_data, short *z_data)
{
    short tmp = 0;
    uint8_t *valueL = ((u8 *)&tmp);
    uint8_t *valueH = (((u8 *)&tmp) + 1);

    tmp = 0;
    u8 ret = i2c_register_read(LIS3DH_REG_OUT_X_L, valueL, 1);
    ret &=i2c_register_read(LIS3DH_REG_OUT_X_H, valueH, 1);
	*x_data = tmp;
    
    tmp = 0;
    ret &=i2c_register_read(LIS3DH_REG_OUT_Y_L, valueL, 1);    
    ret &=i2c_register_read(LIS3DH_REG_OUT_Y_H, valueH, 1);
    *y_data = tmp;
    
    tmp = 0;
    ret &=i2c_register_read(LIS3DH_REG_OUT_Z_L, valueL, 1);    
    ret &=i2c_register_read(LIS3DH_REG_OUT_Z_H, valueH, 1);
    *z_data = tmp;
    
    return ret;
}

bool lis3dh_initial(void)
{
    if(lis3dh_init())
    {
        if(lis3dh_config())
        {
			return true;
        }
    }
	LOG_ERROR("[lis3dh] Config Failed");
	return false;
}

