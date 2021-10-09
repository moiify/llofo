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

#ifndef _RDA2720M_WDG_H_
#define _RDA2720M_WDG_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_wdg'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_WDG_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_WDG_BASE 0x50308040

typedef volatile struct
{
    REG32 wdg_load_low;      //0x00000000
    REG32 wdg_load_high;     //0x00000004
    REG32 wdg_ctrl;          //0x00000008
    REG32 wdg_int_clr;       //0x0000000C
    REG32 wdg_int_raw;       //0x00000010
    REG32 wdg_int_mask;      //0x00000014
    REG32 wdg_cnt_low;       //0x00000018
    REG32 wdg_cnt_high;      //0x0000001C
    REG32 wdg_lock;          //0x00000020
    REG32 wdg_cnt_rd_low;    //0x00000024
    REG32 wdg_cnt_rd_high;   //0x00000028
    REG32 wdg_irqvalue_low;  //0x0000002C
    REG32 wdg_irqvalue_high; //0x00000030
} HWP_RDA2720M_WDG_T;

#define hwp_rda2720mWdg ((HWP_RDA2720M_WDG_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_WDG_BASE))

//WDG_LOAD_LOW
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_load_low : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_LOAD_LOW_T;

//WDG_LOAD_HIGH
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_load_high : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_LOAD_HIGH_T;

//WDG_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_irq_en : 1; // [0]
        REG32 wdg_run : 1;    // [1]
        REG32 wdg_new : 1;    // [2]
        REG32 wdg_rst_en : 1; // [3]
        REG32 __31_4 : 28;
    } b;
} REG_RDA2720M_WDG_WDG_CTRL_T;

//WDG_INT_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_int_clr : 1; // [0]
        REG32 __2_1 : 2;
        REG32 wdg_rst_clr : 1; // [3]
        REG32 __31_4 : 28;
    } b;
} REG_RDA2720M_WDG_WDG_INT_CLR_T;

//WDG_INT_RAW
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_int_raw : 1; // [0], read only
        REG32 __2_1 : 2;
        REG32 wdg_rst_raw : 1; // [3], read only
        REG32 wdg_ld_busy : 1; // [4], read only
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_WDG_WDG_INT_RAW_T;

//WDG_INT_MASK
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_int_mask : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_WDG_WDG_INT_MASK_T;

//WDG_CNT_LOW
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_cnt_low : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_CNT_LOW_T;

//WDG_CNT_HIGH
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_cnt_high : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_CNT_HIGH_T;

//WDG_LOCK
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_lock : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_LOCK_T;

//WDG_CNT_RD_LOW
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_cnt_rd_low : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_CNT_RD_LOW_T;

//WDG_CNT_RD_HIGH
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_cnt_rd_high : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_CNT_RD_HIGH_T;

//WDG_IRQVALUE_LOW
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_irqvalue_low : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_IRQVALUE_LOW_T;

//WDG_IRQVALUE_HIGH
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_irqvalue_high : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_WDG_WDG_IRQVALUE_HIGH_T;

#endif
