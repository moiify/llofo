/*
 * detect.h
 *
 *  Created on: 2020/4/9
 *      Author: lc
 */
#ifndef ELECTROMBILE_FIRMWARE_DETECT_H
#define ELECTROMBILE_FIRMWARE_DETECT_H

#include "types.h"

#define DETECT_CORE_PERIOD  60        //内核升级检测周期

void detect_initail(void);
void detect_int_handler(void);
int  detect_systemCore_handler(void);
u8 detect_getKickState(void);
int detect_sendBmsComFault(void);          //上报三次BMS故障

extern u8 g_buckctrl;
int detect_5v_ctrl_cb(void);
int car_checkBuckHelmetState(void);

#endif //ELECTROMBILE_FIRMWARE_DETECT_H

