
#ifndef __USER_DA14580_BOOT_H__
#define __USER_DA14580_BOOT_H__

#include <stdint.h>

#include "types.h"

void da14580_bootStart(void);
void da14580_bootHandler(uint8_t *data, uint16_t dataLen);

#endif/*__USER_DA14580_BOOT_H__*/

