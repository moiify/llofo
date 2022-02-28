/*
 * led.h
 *
 *  Created on: 2016年3月7日
 *      Author: jk
 */

#ifndef USER_INC_LED_H_
#define USER_INC_LED_H_

typedef enum 
{
  LED_WORK,
  LED_GNSS,
}LED_TYPE;


void LED_on(LED_TYPE ledType);

void LED_off(LED_TYPE ledType);

void LED_startFastBlink(LED_TYPE ledType);


void LED_startFastBlink(LED_TYPE ledType);


#endif /* USER_INC_LED_H_ */
