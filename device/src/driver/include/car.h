/*
 * car.h
 *
 *  Created on: 2017/1/10
 *      Author: lc
 */
#ifndef __CAR_H__
#define __CAR_H__
#include "types.h"
#include "user_gpio.h"

#define HELMET_CHECK_TIME 2
#define HELMET_TIME 1000

enum
{
    CAR_REDLED = 1,
    CAR_GREENLED = 2,
    CAR_BLUELED = 3,
};

enum
{
    CAR_LIGHTON = 0,
    CAR_BLINKFAST = 1,
    CAR_BLINKSLOW = 2,
};

typedef enum
{
    YAKETEB06_SIGNAL_DETECT       = 0, //头盔锁到位信号及感应信号检测
    YAKETEB06_NOTIFY_DETECT       = 1, //故障判断
    YAKETEB06_LOCK                = 2, //执行开锁动作
    YAKETEB06_UNLOCK              = 3, //执行关锁动作
    YAKETEB06_WAIT                = 4, //等待执行结束
}YAKETEB06_STATE;

typedef enum
{
    HELMET_UNLOCK_FAULT           = 1, //头盔锁开锁故障
    HELMET_LOCK_FAULT             = 2, //头盔锁关锁故障
}HELMET_FALUT;

void control595(uint8_t PIN_MASK, GpioLevel_enum level);

void car_lock(void);
void car_lockAndGetSoc(void);
int car_unlock(void);
uint8_t car_isCarLocking(void);

void car_accOn(void);
void car_accOff(void);
void car_accAction(void);
L_BOOL car_isAccOn(void);

void car_lockElectricalBrake(void);
void car_unlockElectricalBrake(void);
void car_lightOperate(u8 sw);

void car_lockSaddle(void);
int  car_checkSaddle(void);
void car_unlockSaddle(void);
void car_lockSaddleHalf(void);
void car_unlockSaddleHalf(void);
L_BOOL car_isSaddleLocked(void);

void car_lockBackWheel(void);
void car_unlockBackWheel(void);
L_BOOL car_isBackWheelLocked(void);

void car_blinkLight(void);

L_BOOL car_isPowerExistence(void);

void car_rebootDA14580(void);
int car_lockHelmet(void);
int car_unlockHelmet(void);
L_BOOL car_isHelmetLocked(void);
int car_checkHelmet(void);

L_BOOL car_isSpeedSingal(void);
L_BOOL car_isOverSpeed(void);
L_BOOL car_isMagneticKick(void);

L_BOOL car_setHandlebarsLED(u8 sw);
int car_close_RFIDPower(void);
int car_open_RFIDPower(void);
void car_openRFIDPower_SetDeffend(void);
void car_closeRFIDPower_SetDeffend(void);
void car_open_RFID485(void);
void car_close_RFID485(void);
L_BOOL car_isHelmetConnected(void);
L_BOOL car_isHelmetAtPos(void);
L_BOOL car_setRGBLed(u8 ledType, u8 onoff);
L_BOOL car_isHelmetClose(void);

int car_unlockHelmet_sync(u8 isAutoLock);
int car_lockHelmet_sync(u8 isAutoOpen);

int car_unlockYaKeTe06Helmet(void);
void car_lockYaKeTe06Helmet(void);

#endif/*__CAR_H__*/

