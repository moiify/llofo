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

#ifndef _I2C_MASTER_H_
#define _I2C_MASTER_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'i2c_master'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// I2C_MASTER_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_I2C_MASTER1_BASE 0x0880A000
#define REG_I2C_MASTER3_BASE 0x0880B000
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_I2C_MASTER2_BASE 0x05103000
#else
#define REG_I2C_MASTER2_BASE 0x50103000
#endif

typedef volatile struct
{
    REG32 ctrl;        //0x00000000
    REG32 status;      //0x00000004
    REG32 txrx_buffer; //0x00000008
    REG32 cmd;         //0x0000000C
    REG32 irq_clr;     //0x00000010
} HWP_I2C_MASTER_T;

#define hwp_i2cMaster1 ((HWP_I2C_MASTER_T *)REG_ACCESS_ADDRESS(REG_I2C_MASTER1_BASE))
#define hwp_i2cMaster3 ((HWP_I2C_MASTER_T *)REG_ACCESS_ADDRESS(REG_I2C_MASTER3_BASE))
#define hwp_i2cMaster2 ((HWP_I2C_MASTER_T *)REG_ACCESS_ADDRESS(REG_I2C_MASTER2_BASE))

//CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 en : 1; // [0]
        REG32 __7_1 : 7;
        REG32 irq_mask : 1; // [8]
        REG32 __15_9 : 7;
        REG32 clock_prescale : 16; // [31:16]
    } b;
} REG_I2C_MASTER_CTRL_T;

//STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 irq_cause : 1; // [0], read only
        REG32 __3_1 : 3;
        REG32 irq_status : 1; // [4], read only
        REG32 __7_5 : 3;
        REG32 tip : 1; // [8], read only
        REG32 __11_9 : 3;
        REG32 al : 1; // [12], read only
        REG32 __15_13 : 3;
        REG32 busy : 1; // [16], read only
        REG32 __19_17 : 3;
        REG32 rxack : 1; // [20], read only
        REG32 __31_21 : 11;
    } b;
} REG_I2C_MASTER_STATUS_T;

//TXRX_BUFFER
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_data : 8; // [7:0]
        REG32 rx_data : 8; // [7:0], read only
        REG32 __31_8 : 24;
    } b;
} REG_I2C_MASTER_TXRX_BUFFER_T;

//CMD
typedef union {
    REG32 v;
    struct
    {
        REG32 ack : 1; // [0]
        REG32 __3_1 : 3;
        REG32 rd : 1; // [4]
        REG32 __7_5 : 3;
        REG32 sto : 1; // [8]
        REG32 __11_9 : 3;
        REG32 rw : 1; // [12]
        REG32 __15_13 : 3;
        REG32 sta : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_I2C_MASTER_CMD_T;

//IRQ_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 irq_clr : 1; // [0], write clear
        REG32 __31_1 : 31;
    } b;
} REG_I2C_MASTER_IRQ_CLR_T;

#endif
