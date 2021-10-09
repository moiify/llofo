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

#ifndef _RDA2720M_INT_H_
#define _RDA2720M_INT_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_int'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_INT_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_INT_BASE 0x503080C0

typedef volatile struct
{
    REG32 int_mask_status; //0x00000000
    REG32 int_raw_status;  //0x00000004
    REG32 int_en;          //0x00000008
} HWP_RDA2720M_INT_T;

#define hwp_rda2720mInt ((HWP_RDA2720M_INT_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_INT_BASE))

//INT_MASK_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_int_mask_status : 1;         // [0], read only
        REG32 rtc_int_mask_status : 1;         // [1], read only
        REG32 wdg_int_mask_status : 1;         // [2], read only
        REG32 fgu_int_mask_status : 1;         // [3], read only
        REG32 eic_int_mask_status : 1;         // [4], read only
        REG32 aud_protect_int_mask_status : 1; // [5], read only
        REG32 tmr_int_mask_status : 1;         // [6], read only
        REG32 cal_int_mask_status : 1;         // [7], read only
        REG32 typec_int_mask_status : 1;       // [8], read only
        REG32 __31_9 : 23;
    } b;
} REG_RDA2720M_INT_INT_MASK_STATUS_T;

//INT_RAW_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_int_raw_status : 1;         // [0], read only
        REG32 rtc_int_raw_status : 1;         // [1], read only
        REG32 wdg_int_raw_status : 1;         // [2], read only
        REG32 fgu_int_raw_status : 1;         // [3], read only
        REG32 eic_int_raw_status : 1;         // [4], read only
        REG32 aud_protect_int_raw_status : 1; // [5], read only
        REG32 tmr_int_raw_status : 1;         // [6], read only
        REG32 cal_int_raw_status : 1;         // [7], read only
        REG32 typec_int_raw_status : 1;       // [8], read only
        REG32 __31_9 : 23;
    } b;
} REG_RDA2720M_INT_INT_RAW_STATUS_T;

//INT_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_int_en : 1;         // [0]
        REG32 rtc_int_en : 1;         // [1]
        REG32 wdg_int_en : 1;         // [2]
        REG32 fgu_int_en : 1;         // [3]
        REG32 eic_int_en : 1;         // [4]
        REG32 aud_protect_int_en : 1; // [5]
        REG32 tmr_int_en : 1;         // [6]
        REG32 cal_int_en : 1;         // [7]
        REG32 typec_int_en : 1;       // [8]
        REG32 __31_9 : 23;
    } b;
} REG_RDA2720M_INT_INT_EN_T;

#endif
