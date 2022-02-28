#include "fibo_opencpu.h"
#include "lis3dh.h"
#include "hardware.h"
#include "mpu_dmp_api.h"
#include "inv_mpu.h"
#include "detect.h"
#include "setting.h"
#include "data.h"
#include "log.h"
#include "user_timer.h"
#include "accelerometer.h"
#include "park.h"

bool accelerometer_check(void)
{
    if(setting.settingConf.accleType == ACCLE_LIS3DH)
    {
        return lis3dh_verify_device_id();
    }
    else if(setting.settingConf.accleType == ACCLE_MPU6500)
    {
        if(mpu_whoami() == 0)
        {
            return true;
        }
    }
    return false;
}

bool accelerometer_readOutputXYZ(short *x_data, short *y_data, short *z_data)
{
    if(setting.settingConf.accleType == ACCLE_LIS3DH)
    {
        return lis3dh_readOutputXYZ(x_data, y_data, z_data);
    }
    else if(setting.settingConf.accleType == ACCLE_MPU6500)
    {
        if(!timer_isTimerStart(TIEMR_PARK_DIR)) //如果定向停车定时器不断在刷新mpus数据,直接读
        {
            if(mpu_dmp_getData())
            {
                return false;
            }
        }

        *x_data = get_xaccel_data();
        *y_data = get_yaccel_data();
        *z_data = get_zaccel_data();
        return true;
    }
    return false;
}

bool accelerometer_initial(void)
{
    if(setting.settingConf.accleType == ACCLE_MPU6500)
    {
        if(0 != mpu_dmp_init())
        {
            LOG_DEBUG("mpu_dmp_init error");
            data_getData()->isAccelerateInitFault = 1;

            //避让机制 最长3个小时
            setting.settingConf.mpuAvoidanceRatio = setting.settingConf.mpuAvoidanceRatio * 2;
            if(setting.settingConf.mpuAvoidanceRatio > 36)setting.settingConf.mpuAvoidanceRatio = 36;
            settingConf_save();
            return false;
        }
        else
        {
            LOG_DEBUG("mpu_dmp_init success");
            data_getData()->isAccelerateInitFault = 0;
            if(setting.settingConf.mpuAvoidanceRatio != 1)
            {
                setting.settingConf.mpuAvoidanceRatio = 1;
                settingConf_save();
            }
            park_initial();
            return true;
        }
    }
    else if(setting.settingConf.accleType == ACCLE_LIS3DH)//lis3dh初始化加速度中断,上升沿触发
    {
        oc_isr_t isrt;
        isrt.is_debounce = L_TRUE;
        isrt.intr_enable = L_TRUE;
        isrt.intr_level = L_FALSE;
        isrt.inte_rising = L_TRUE;
        isrt.callback = (ISR_CB) detect_int_handler;
        fibo_gpio_isr_init(PIN_LIS_INT, &isrt);

        return lis3dh_initial();                       //加速度计初始化 型号lis3dh
    }
    return false;
}

bool accelerometer_reset(void)
{
    if(setting.settingConf.accleType == ACCLE_MPU6500)
    {
        if(0 != mpu_dmp_init())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else if(setting.settingConf.accleType == ACCLE_LIS3DH)//lis3dh初始化加速度中断,上升沿触发
    {
        return lis3dh_initial();                       //加速度计初始化 型号lis3dh
    }
    return false;
}

