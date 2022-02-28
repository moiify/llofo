/*
 * agps.h
 *
 *  Created on: 2017/12/16
 *      Author: wyb
 */

#ifndef _AGPS_H_
#define _AGPS_H_

void agps_initail(void);
void agps_tryOnce(void);
void agps_getIsGPSFixed(u8 *isFix);
void agps_getIsLogined(u8 *isLogin);
int  agps_NeedAGPS(void);


#endif // !_AGPS_H_

