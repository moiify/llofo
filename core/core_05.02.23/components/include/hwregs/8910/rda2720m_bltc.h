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

#ifndef _RDA2720M_BLTC_H_
#define _RDA2720M_BLTC_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_bltc'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_BLTC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_BLTC_BASE 0x50308180

typedef volatile struct
{
    REG32 bltc_ctrl;        //0x00000000
    REG32 bltc_r_prescl;    //0x00000004
    REG32 bltc_r_duty;      //0x00000008
    REG32 bltc_r_curve0;    //0x0000000C
    REG32 bltc_r_curve1;    //0x00000010
    REG32 bltc_g_prescl;    //0x00000014
    REG32 bltc_g_duty;      //0x00000018
    REG32 bltc_g_curve0;    //0x0000001C
    REG32 bltc_g_curve1;    //0x00000020
    REG32 bltc_b_prescl;    //0x00000024
    REG32 bltc_b_duty;      //0x00000028
    REG32 bltc_b_curve0;    //0x0000002C
    REG32 bltc_b_curve1;    //0x00000030
    REG32 bltc_sts;         //0x00000034
    REG32 rg_rgb_v0;        //0x00000038
    REG32 rg_rgb_v1;        //0x0000003C
    REG32 rg_rgb_v2;        //0x00000040
    REG32 rg_rgb_v3;        //0x00000044
    REG32 bltc_wled_prescl; //0x00000048
    REG32 bltc_wled_duty;   //0x0000004C
    REG32 bltc_wled_curve0; //0x00000050
    REG32 bltc_wled_curve1; //0x00000054
    REG32 bltc_pd_ctrl;     //0x00000058
    REG32 bltc_version;     //0x0000005C
} HWP_RDA2720M_BLTC_T;

#define hwp_rda2720mBltc ((HWP_RDA2720M_BLTC_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_BLTC_BASE))

//BLTC_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 r_run : 1;     // [0]
        REG32 r_type : 1;    // [1]
        REG32 r_sel : 1;     // [2]
        REG32 r_sw : 1;      // [3]
        REG32 g_run : 1;     // [4]
        REG32 g_type : 1;    // [5]
        REG32 g_sel : 1;     // [6]
        REG32 g_sw : 1;      // [7]
        REG32 b_run : 1;     // [8]
        REG32 b_type : 1;    // [9]
        REG32 b_sel : 1;     // [10]
        REG32 b_sw : 1;      // [11]
        REG32 wled_run : 1;  // [12]
        REG32 wled_type : 1; // [13]
        REG32 wled_sel : 1;  // [14]
        REG32 wled_sw : 1;   // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_CTRL_T;

//BLTC_R_PRESCL
typedef union {
    REG32 v;
    struct
    {
        REG32 prescl : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_BLTC_BLTC_R_PRESCL_T;

//BLTC_R_DUTY
typedef union {
    REG32 v;
    struct
    {
        REG32 mod : 8;  // [7:0]
        REG32 duty : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_R_DUTY_T;

//BLTC_R_CURVE0
typedef union {
    REG32 v;
    struct
    {
        REG32 trise : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 tfall : 6; // [13:8]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_BLTC_BLTC_R_CURVE0_T;

//BLTC_R_CURVE1
typedef union {
    REG32 v;
    struct
    {
        REG32 thigh : 8; // [7:0]
        REG32 tlow : 8;  // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_R_CURVE1_T;

//BLTC_G_PRESCL
typedef union {
    REG32 v;
    struct
    {
        REG32 prescl : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_BLTC_BLTC_G_PRESCL_T;

//BLTC_G_DUTY
typedef union {
    REG32 v;
    struct
    {
        REG32 mod : 8;  // [7:0]
        REG32 duty : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_G_DUTY_T;

//BLTC_G_CURVE0
typedef union {
    REG32 v;
    struct
    {
        REG32 trise : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 tfall : 6; // [13:8]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_BLTC_BLTC_G_CURVE0_T;

//BLTC_G_CURVE1
typedef union {
    REG32 v;
    struct
    {
        REG32 thigh : 8; // [7:0]
        REG32 tlow : 8;  // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_G_CURVE1_T;

//BLTC_B_PRESCL
typedef union {
    REG32 v;
    struct
    {
        REG32 prescl : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_BLTC_BLTC_B_PRESCL_T;

//BLTC_B_DUTY
typedef union {
    REG32 v;
    struct
    {
        REG32 mod : 8;  // [7:0]
        REG32 duty : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_B_DUTY_T;

//BLTC_B_CURVE0
typedef union {
    REG32 v;
    struct
    {
        REG32 trise : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 tfall : 6; // [13:8]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_BLTC_BLTC_B_CURVE0_T;

//BLTC_B_CURVE1
typedef union {
    REG32 v;
    struct
    {
        REG32 thigh : 8; // [7:0]
        REG32 tlow : 8;  // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_B_CURVE1_T;

//BLTC_STS
typedef union {
    REG32 v;
    struct
    {
        REG32 bltc_r_busy : 1;    // [0], read only
        REG32 bltc_g_busy : 1;    // [1], read only
        REG32 bltc_b_busy : 1;    // [2], read only
        REG32 bltc_wled_busy : 1; // [3], read only
        REG32 __31_4 : 28;
    } b;
} REG_RDA2720M_BLTC_BLTC_STS_T;

//RG_RGB_V0
typedef union {
    REG32 v;
    struct
    {
        REG32 rg_rgb_v0 : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_BLTC_RG_RGB_V0_T;

//RG_RGB_V1
typedef union {
    REG32 v;
    struct
    {
        REG32 rg_rgb_v1 : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_BLTC_RG_RGB_V1_T;

//RG_RGB_V2
typedef union {
    REG32 v;
    struct
    {
        REG32 rg_rgb_v2 : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_BLTC_RG_RGB_V2_T;

//RG_RGB_V3
typedef union {
    REG32 v;
    struct
    {
        REG32 rg_rgb_v3 : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_BLTC_RG_RGB_V3_T;

//BLTC_WLED_PRESCL
typedef union {
    REG32 v;
    struct
    {
        REG32 prescl : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_BLTC_BLTC_WLED_PRESCL_T;

//BLTC_WLED_DUTY
typedef union {
    REG32 v;
    struct
    {
        REG32 mod : 8;  // [7:0]
        REG32 duty : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_WLED_DUTY_T;

//BLTC_WLED_CURVE0
typedef union {
    REG32 v;
    struct
    {
        REG32 trise : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 tfall : 6; // [13:8]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_BLTC_BLTC_WLED_CURVE0_T;

//BLTC_WLED_CURVE1
typedef union {
    REG32 v;
    struct
    {
        REG32 thigh : 8; // [7:0]
        REG32 tlow : 8;  // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_WLED_CURVE1_T;

//BLTC_PD_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 sw_pd : 1; // [0]
        REG32 hw_pd : 1; // [1]
        REG32 __31_2 : 30;
    } b;
} REG_RDA2720M_BLTC_BLTC_PD_CTRL_T;

//BLTC_VERSION
typedef union {
    REG32 v;
    struct
    {
        REG32 bltc_version : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_BLTC_BLTC_VERSION_T;

#endif
