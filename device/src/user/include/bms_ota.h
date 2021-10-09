#ifndef _BMS_OTA_H_
#define _BMS_OTA_H_

#include "types.h"

u8  bmsOta_GetUpgrading(void);
u8  bmsOta_SetUpgrading(u8 isUpgrading);
int bmsOta_upgardeTimerHandler(void);

#endif

