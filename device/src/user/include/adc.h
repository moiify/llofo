/*
 * adc.h
 *
 *  Created on: 2020.04.09
 *      Author: lc
 */

#ifndef USER_ELECTROMBILE_ADC_H_
#define USER_ELECTROMBILE_ADC_H_
#include "stdint.h"

#include "types.h"

#define ADC_PWR_DETECT  2
#define ADC_COMM_DETECT 3

void adc_stop(void);
void adc_start(void);
void adc_initial(void);
L_BOOL adc_getVoltageSync(u32 *voltage_mV, u8 channel);
void adc_enable(u8 flag);
void adc_getSmallBetTemp(void);

#endif /* USER_ELECTROMBILE_ADC_H_ */

