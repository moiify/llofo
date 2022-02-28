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

#ifndef _RF_RTC_H_
#define _RF_RTC_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rf_rtc'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RF_RTC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_RF_RTC_BASE 0x05034000
#else
#define REG_RF_RTC_BASE 0x50034000
#endif

typedef volatile struct
{
    REG32 Reserved_00000000[40]; //0x00000000
    REG32 reg_00_reg;            //0x000000A0
    REG32 Reserved_000000A4[2];  //0x000000A4
    REG32 reg_0c_reg;            //0x000000AC
    REG32 reg_10_reg;            //0x000000B0
    REG32 reg_14_reg;            //0x000000B4
    REG32 reg_18_reg;            //0x000000B8
    REG32 reg_1c_reg;            //0x000000BC
    REG32 reg_c0_reg;            //0x000000C0
    REG32 reg_c4_reg;            //0x000000C4
    REG32 reg_c8_reg;            //0x000000C8
    REG32 reg_cc_reg;            //0x000000CC
    REG32 reg_d0_reg;            //0x000000D0
    REG32 reg_d4_reg;            //0x000000D4
    REG32 reg_d8_reg;            //0x000000D8
} HWP_RF_RTC_T;

#define hwp_rfRtc ((HWP_RF_RTC_T *)REG_ACCESS_ADDRESS(REG_RF_RTC_BASE))

//REG_00_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_a1_bit : 8; // [7:0]
        REG32 reg_a0_bit : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_00_REG_T;

//REG_0c_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_a7_bit : 8; // [7:0]
        REG32 reg_a6_bit : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_0C_REG_T;

//REG_10_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_a9_bit : 8; // [7:0]
        REG32 reg_a8_bit : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_10_REG_T;

//REG_14_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_ab_bit : 8; // [7:0]
        REG32 reg_aa_bit : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_14_REG_T;

//REG_18_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_ad_bit : 8; // [7:0]
        REG32 reg_ac_bit : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_18_REG_T;

//REG_1c_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_af_bit : 8; // [7:0]
        REG32 reg_ae_bit : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_1C_REG_T;

//REG_c0_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 dig_afc_bit_reg : 14; // [13:0]
        REG32 enable_clk_6p5m : 1;  // [14]
        REG32 __31_15 : 17;
    } b;
} REG_RF_RTC_REG_C0_REG_T;

//REG_c4_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 xtal_osc_ibit_n : 4;   // [3:0]
        REG32 xtal_osc_ibit_l : 4;   // [7:4]
        REG32 xtal26m_pwadc_en : 1;  // [8]
        REG32 xtal_reg_bit : 4;      // [12:9]
        REG32 xtal26m_tsxadc_en : 1; // [13]
        REG32 xtal26m_plls1_en : 1;  // [14]
        REG32 xtal26m_plls2_en : 1;  // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_C4_REG_T;

//REG_c8_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 xtal_fixi_bit_n : 5;   // [4:0]
        REG32 xtal_fixi_bit_l : 5;   // [9:5]
        REG32 xtal26m_ts_en : 1;     // [10]
        REG32 xtal26m_pllcal_en : 1; // [11]
        REG32 __31_12 : 20;
    } b;
} REG_RF_RTC_REG_C8_REG_T;

//REG_cc_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 xdrv_reg_bit : 4;         // [3:0]
        REG32 xdrv_aux1_power_bit : 3;  // [6:4]
        REG32 xdrv_aux2_power_bit : 3;  // [9:7]
        REG32 xdrv_pmic_power_bit : 3;  // [12:10]
        REG32 xtal26m_interface_en : 1; // [13]
        REG32 xtal26m_pmic_en : 1;      // [14]
        REG32 __31_15 : 17;
    } b;
} REG_RF_RTC_REG_CC_REG_T;

//REG_d0_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 xtal_capbank_bit_n : 7; // [6:0]
        REG32 xtal_hsel_n : 1;        // [7]
        REG32 xtal_capbank_bit_l : 7; // [14:8]
        REG32 xtal_hsel_l : 1;        // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_D0_REG_T;

//REG_d4_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_reser_l : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_D4_REG_T;

//REG_d8_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_reser_n : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RF_RTC_REG_D8_REG_T;

#endif
