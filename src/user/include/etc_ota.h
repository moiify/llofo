#ifndef _ETC_OTA_H_
#define _ETC_OTA_H_

#include "types.h"

int etcOta_upgardeTimerHandler(void);
u8  etcOta_getUpgrading(void);
u8  etcOta_setUpgrading(u8 isUpgrading);

#endif

