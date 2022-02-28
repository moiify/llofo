/* Copyright (C) 2018 RDA Technologies Limited and/or its affiliates("RDA").
 * All rights reserved.
 *
 * This software is supplied "AS IS" without any warranties.
 * RDA assumes no responsibility or liability for the use of the software,
 * conveys no license or title under any patent, copyright, or mask work
 * right to the product. RDA reserves the right to make changes in the
 * software without notification.  RDA also make no representation or
 * warranty that such application will be suitable for the specified use
 * without further testing or modification.
 */

#ifndef _DRV_NAMES_H_
#define _DRV_NAMES_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "osi_compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

#define DRV_NAME_INVALID 0

#define DRV_NAME_DEBUGUART OSI_MAKE_TAG('D', 'U', 'R', 'T')
#define DRV_NAME_CP OSI_MAKE_TAG('C', 'P', ' ', ' ')
#define DRV_NAME_SCI1 OSI_MAKE_TAG('S', 'C', 'I', '1')
#define DRV_NAME_SCI2 OSI_MAKE_TAG('S', 'C', 'I', '2')
#define DRV_NAME_SPI1 OSI_MAKE_TAG('S', 'P', 'I', '1')
#define DRV_NAME_SPI2 OSI_MAKE_TAG('S', 'P', 'I', '2')
#define DRV_NAME_SPI3 OSI_MAKE_TAG('S', 'P', 'I', '3')
#define DRV_NAME_UART1 OSI_MAKE_TAG('U', 'R', 'T', '1')
#define DRV_NAME_UART2 OSI_MAKE_TAG('U', 'R', 'T', '2')
#define DRV_NAME_UART3 OSI_MAKE_TAG('U', 'R', 'T', '3')
#define DRV_NAME_UART4 OSI_MAKE_TAG('U', 'R', 'T', '4')
#define DRV_NAME_SPI_FLASH OSI_MAKE_TAG('S', 'F', 'L', '1')
#define DRV_NAME_SPI_FLASH_EXT OSI_MAKE_TAG('S', 'F', 'L', '2')
#define DRV_NAME_AON_WDT OSI_MAKE_TAG('A', 'O', 'W', 'D')
#define DRV_NAME_USB11 OSI_MAKE_TAG('U', 'S', 'B', '1')
#define DRV_NAME_USB20 OSI_MAKE_TAG('U', 'S', 'B', '2')
#define DRV_NAME_USRL_COM0 OSI_MAKE_TAG('U', 'S', 'L', '0')
#define DRV_NAME_USRL_COM1 OSI_MAKE_TAG('U', 'S', 'L', '1')
#define DRV_NAME_USRL_COM2 OSI_MAKE_TAG('U', 'S', 'L', '2')
#define DRV_NAME_USRL_COM3 OSI_MAKE_TAG('U', 'S', 'L', '3')
#define DRV_NAME_USRL_COM4 OSI_MAKE_TAG('U', 'S', 'L', '4')
#define DRV_NAME_USRL_COM5 OSI_MAKE_TAG('U', 'S', 'L', '5')
#define DRV_NAME_USRL_COM6 OSI_MAKE_TAG('U', 'S', 'L', '6')
#define DRV_NAME_USRL_COM7 OSI_MAKE_TAG('U', 'S', 'L', '7')
#define DRV_NAME_SDMMC1 OSI_MAKE_TAG('S', 'D', 'C', '1')
#define DRV_NAME_SDMMC2 OSI_MAKE_TAG('S', 'D', 'C', '2')
#define DRV_NAME_CAMERA1 OSI_MAKE_TAG('C', 'A', 'M', '1')
#define DRV_NAME_I2C1 OSI_MAKE_TAG('I', '2', 'C', '1')
#define DRV_NAME_I2C2 OSI_MAKE_TAG('I', '2', 'C', '2')
#define DRV_NAME_I2C3 OSI_MAKE_TAG('I', '2', 'C', '3')
#define DRV_NAME_WCN OSI_MAKE_TAG('W', 'C', 'N', ' ')
#define DRV_NAME_PWM1 OSI_MAKE_TAG('P', 'W', 'M', '1')

#ifdef __cplusplus
}
#endif

#endif
