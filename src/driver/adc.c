/*
 * adc.c
 *
 *  Created on: 2018/06/03
 *      Author: lc
 */
#include "fibo_opencpu.h"
#include <math.h>
#include "adc.h"
#include "log.h"
#include "types.h"
#include "data.h"
#include "user_timer.h"
#include "car.h"

#define ADC_DETECT_PERIOD       (1000)          //AD检测周期: 1000ms
#define ADC_CARBAT_FAILTER      (200)           //过滤小于200的大电池电压AD值 1 = 34.33mv
#define ADC2BATVALUE(x)         ( x * 103 / 3 ) //单位: mV, 3K & 100k divider
#define ADC2SMBVALUE(x)         ( x * 133 / 33) //单位: mV, 33K & 100k divider
#define SAMPLE_NUM              (8)
#define SAMPLE_DEVIATION_STD    (500)//偏差大于500mv小于3v认为不准
#define SAMPLE_DEVIATION_MAX_STD   (3000)//均值偏差大于3v认为均值不可信

//返回是否使用计算的均值
static int adc_sampleAvg_deviation(u32 *data, u8 len, u32 *avg)
{
    u32 sum = 0;
    int ret = 0;
    int i = 0;
    u32 diff = 0;
    u32 max_diff = 0;

    for(i = 0; i < len; i++) //计算均值
    {
        sum += data[i];
    }
    *avg = sum / len;

    for(i = 0; i < len; i++) //遍历最大偏差
    {
        diff = abs((s32)(data[i] - *avg));
        if(diff > max_diff)
        {
            max_diff = diff;
        }
    }

    if(max_diff > SAMPLE_DEVIATION_MAX_STD)
    {
        ret = -1; //超过则不再采纳平均值
        data_getData()->voltageState = BATTRY_INACCURATE;
    }
    else if(max_diff > SAMPLE_DEVIATION_STD)
    {
        data_getData()->voltageState = BATTRY_INACCURATE;
    }
    else
    {
        if(setting_isAccOn())
        {
            data_getData()->voltageState = MOTION_ACCURATE;
        }
        else
        {
            data_getData()->voltageState = STATIC_ACCURATE;
        }
    }
    return ret;
}

static int adc_proc_cb(void)
{
    static u32 sample_batteryVoltage[SAMPLE_NUM] = {0};
    static u8 point = 0;
    u32 sampleAvg = 0;
    L_BOOL ret = 0;
    int isUseAvg = 0;

    ret = adc_getVoltageSync(&data_getData()->vehicleBattery_mV, ADC_PWR_DETECT);
    if(ret != L_TRUE)
    {
        fibo_hal_adc_init();
        return -1;
    }
    //滑动窗口赋值，计算有效和方差，如满足则更新
    LOG_DEBUG("[ADC] vehicleBattery_mV: %d", data_getData()->vehicleBattery_mV);

    if(point < SAMPLE_NUM)
    {
        sample_batteryVoltage[point] = data_getData()->vehicleBattery_mV;
    }
    if(point < SAMPLE_NUM - 1)
    {
        point++;
    }
    else
    {
        point = 0;
    }
    
    isUseAvg = adc_sampleAvg_deviation(sample_batteryVoltage, SAMPLE_NUM, &sampleAvg);
    if(isUseAvg == 0)
    {
        data_getData()->vehicleBattery_mV = sampleAvg;
    }

    ret = adc_getVoltageSync(&data_getData()->smallBattery_mV, ADC_COMM_DETECT);
    if(ret != L_TRUE)
    {
        fibo_hal_adc_init();
        return -1;
    }
    LOG_DEBUG("[ADC] smallBattery_mV: %d", data_getData()->smallBattery_mV);

    if(!car_isPowerExistence())
    {
        data_getData()->vehicleBattery_mV = 0;
        data_getData()->staticBikeBat_mV = 0;
        memset(sample_batteryVoltage, 0, sizeof(sample_batteryVoltage));
        LOG_DEBUG("[ADC]car power not exist, empty adc to zero");
    }
    return 0;
}

void adc_start(void)
{
    timer_startRepeat(TIMER_ADC, TIMER_MS, ADC_DETECT_PERIOD, adc_proc_cb);
}

void adc_stop(void)
{
    timer_stop(TIMER_ADC);
}

L_BOOL adc_getVoltageSync(u32 *voltage_mV, u8 channel)
{
    INT32 voltage_ADC = 0;

    if(channel == ADC_PWR_DETECT)
    {
        voltage_ADC = fibo_hal_adc_get_data(ADC_PWR_DETECT, 2); //3.23V量程
        if(voltage_ADC < 0)
        {
            return L_FALSE;
        }
        if(voltage_ADC < ADC_CARBAT_FAILTER)
        {
            voltage_ADC = 0;
        }
        *voltage_mV = (u32)ADC2BATVALUE(voltage_ADC);
    }
    
    if(channel == ADC_COMM_DETECT)
    {
        voltage_ADC = fibo_hal_adc_get_data(ADC_COMM_DETECT, 0); //1.25V量程
        if(voltage_ADC < 0)
        {
            return L_FALSE;
        }
        *voltage_mV = (u32)ADC2SMBVALUE(voltage_ADC);
    }

    return L_TRUE;
}

void adc_enable(u8 flag)
{
    if(flag)
    {
        fibo_hal_adc_init();
    }
    else
    {
        fibo_hal_adc_deinit();
    }
}

void adc_initial(void)
{
    adc_start();
    fibo_hal_adc_init();
}

