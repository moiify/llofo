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

#ifndef _RDA2720M_EIC_H_
#define _RDA2720M_EIC_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_eic'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_EIC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_EIC_BASE 0x50308280

typedef volatile struct
{
    REG32 eicdata;   //0x00000000
    REG32 eicdmsk;   //0x00000004
    REG32 reserved1; //0x00000008
    REG32 reserved2; //0x0000000C
    REG32 reserved3; //0x00000010
    REG32 eiciev;    //0x00000014
    REG32 eicie;     //0x00000018
    REG32 eicris;    //0x0000001C
    REG32 eicmis;    //0x00000020
    REG32 eicic;     //0x00000024
    REG32 eictrig;   //0x00000028
    REG32 reserved4; //0x0000002C
    REG32 reserved5; //0x00000030
    REG32 reserved6; //0x00000034
    REG32 reserved7; //0x00000038
    REG32 reserved8; //0x0000003C
    REG32 eic0ctrl;  //0x00000040
    REG32 eic1ctrl;  //0x00000044
    REG32 eic2ctrl;  //0x00000048
    REG32 eic3ctrl;  //0x0000004C
    REG32 eic4ctrl;  //0x00000050
    REG32 eic5ctrl;  //0x00000054
    REG32 eic6ctrl;  //0x00000058
    REG32 eic7ctrl;  //0x0000005C
    REG32 eic8ctrl;  //0x00000060
    REG32 eic9ctrl;  //0x00000064
    REG32 eic10ctrl; //0x00000068
    REG32 eic11ctrl; //0x0000006C
    REG32 eic12ctrl; //0x00000070
    REG32 eic13ctrl; //0x00000074
    REG32 eic14ctrl; //0x00000078
    REG32 eic15ctrl; //0x0000007C
} HWP_RDA2720M_EIC_T;

#define hwp_rda2720mEic ((HWP_RDA2720M_EIC_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_EIC_BASE))

//EICDATA
typedef union {
    REG32 v;
    struct
    {
        REG32 eicdata : 13; // [12:0], read only
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_EIC_EICDATA_T;

//EICDMSK
typedef union {
    REG32 v;
    struct
    {
        REG32 eicdmsk : 13; // [12:0]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_EIC_EICDMSK_T;

//EICIEV
typedef union {
    REG32 v;
    struct
    {
        REG32 eiciev : 13; // [12:0]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_EIC_EICIEV_T;

//EICIE
typedef union {
    REG32 v;
    struct
    {
        REG32 eicie : 13; // [12:0]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_EIC_EICIE_T;

//EICRIS
typedef union {
    REG32 v;
    struct
    {
        REG32 eicris : 13; // [12:0], read only
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_EIC_EICRIS_T;

//EICMIS
typedef union {
    REG32 v;
    struct
    {
        REG32 eicmis : 13; // [12:0], read only
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_EIC_EICMIS_T;

//EICIC
typedef union {
    REG32 v;
    struct
    {
        REG32 eicic : 13; // [12:0]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_EIC_EICIC_T;

//EICTRIG
typedef union {
    REG32 v;
    struct
    {
        REG32 eictrig : 13; // [12:0]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_EIC_EICTRIG_T;

//EIC0CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC0CTRL_T;

//EIC1CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC1CTRL_T;

//EIC2CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC2CTRL_T;

//EIC3CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC3CTRL_T;

//EIC4CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC4CTRL_T;

//EIC5CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC5CTRL_T;

//EIC6CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC6CTRL_T;

//EIC7CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC7CTRL_T;

//EIC8CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC8CTRL_T;

//EIC9CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC9CTRL_T;

//EIC10CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC10CTRL_T;

//EIC11CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC11CTRL_T;

//EIC12CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC12CTRL_T;

//EIC13CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC13CTRL_T;

//EIC14CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC14CTRL_T;

//EIC15CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dbnc_cnt : 12; // [11:0]
        REG32 __13_12 : 2;
        REG32 dbnc_en : 1;        // [14]
        REG32 force_clk_dbnc : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EIC_EIC15CTRL_T;

#endif
