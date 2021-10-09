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

#ifndef _WCN_WLAN_H_
#define _WCN_WLAN_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'wcn_wlan'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// WCN_WLAN_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_WCN_WLAN_BASE 0x15007000

typedef volatile struct
{
    REG32 Reserved_00000000;     //0x00000000
    REG32 phy_reg_bank_addr;     //0x00000004
    REG32 phy_reg_offset_addr;   //0x00000008
    REG32 phy_reg_write_data;    //0x0000000C
    REG32 phy_reg_read_data;     //0x00000010
    REG32 protocol_version;      //0x00000014
    REG32 type;                  //0x00000018
    REG32 sub_type;              //0x0000001C
    REG32 desaddr_l;             //0x00000020
    REG32 desaddr_h;             //0x00000024
    REG32 srcaddr_l;             //0x00000028
    REG32 srcaddr_h;             //0x0000002C
    REG32 bssidaddr_l;           //0x00000030
    REG32 bssidaddr_h;           //0x00000034
    REG32 seqcontrol;            //0x00000038
    REG32 rssival;               //0x0000003C
    REG32 Reserved_00000040[16]; //0x00000040
    REG32 config_reg;            //0x00000080
    REG32 datardyint;            //0x00000084
    REG32 phy_sel_set0;          //0x00000088
    REG32 phy_sel_set2;          //0x0000008C
    REG32 phy_sel_set3;          //0x00000090
    REG32 phy_sel_set4;          //0x00000094
    REG32 phy_sel_set5;          //0x00000098
    REG32 phy_sel_set6;          //0x0000009C
    REG32 phy_sel_set7;          //0x000000A0
    REG32 phy_sel_set8;          //0x000000A4
} HWP_WCN_WLAN_T;

#define hwp_wcnWlan ((HWP_WCN_WLAN_T *)REG_ACCESS_ADDRESS(REG_WCN_WLAN_BASE))

//protocol_version
typedef union {
    REG32 v;
    struct
    {
        REG32 protocol_version : 2; // [1:0], read only
        REG32 __31_2 : 30;
    } b;
} REG_WCN_WLAN_PROTOCOL_VERSION_T;

//type
typedef union {
    REG32 v;
    struct
    {
        REG32 tp : 2; // [1:0], read only
        REG32 __31_2 : 30;
    } b;
} REG_WCN_WLAN_TYPE_T;

//sub_type
typedef union {
    REG32 v;
    struct
    {
        REG32 sub_type : 4; // [3:0], read only
        REG32 __31_4 : 28;
    } b;
} REG_WCN_WLAN_SUB_TYPE_T;

//desaddr_h
typedef union {
    REG32 v;
    struct
    {
        REG32 desaddr_h : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_WLAN_DESADDR_H_T;

//srcaddr_h
typedef union {
    REG32 v;
    struct
    {
        REG32 srcaddr_h : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_WLAN_SRCADDR_H_T;

//bssidaddr_h
typedef union {
    REG32 v;
    struct
    {
        REG32 bssidaddr_h : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_WLAN_BSSIDADDR_H_T;

//seqcontrol
typedef union {
    REG32 v;
    struct
    {
        REG32 seqcontrol : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_WLAN_SEQCONTROL_T;

//rssival
typedef union {
    REG32 v;
    struct
    {
        REG32 rssival : 8; // [7:0], read only
        REG32 __31_8 : 24;
    } b;
} REG_WCN_WLAN_RSSIVAL_T;

//config_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 apb_clear : 1; // [0]
        REG32 apb_hold : 1;  // [1]
        REG32 __7_2 : 6;
        REG32 subtype_config_reg : 4; // [11:8]
        REG32 type_config_reg : 2;    // [13:12]
        REG32 __15_14 : 2;
        REG32 phyrx_en_b : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_WLAN_CONFIG_REG_T;

//datardyint
typedef union {
    REG32 v;
    struct
    {
        REG32 datardyint : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_WCN_WLAN_DATARDYINT_T;

//phy_sel_set0
typedef union {
    REG32 v;
    struct
    {
        REG32 phy_sel_0_reg : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 phy_sel_1_reg : 6; // [13:8]
        REG32 __15_14 : 2;
        REG32 phy_sel_2_reg : 6; // [21:16]
        REG32 __23_22 : 2;
        REG32 phy_sel_3_reg : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_WLAN_PHY_SEL_SET0_T;

//phy_sel_set2
typedef union {
    REG32 v;
    struct
    {
        REG32 phy_sel_4_reg : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 phy_sel_5_reg : 6; // [13:8]
        REG32 __15_14 : 2;
        REG32 phy_sel_6_reg : 6; // [21:16]
        REG32 __23_22 : 2;
        REG32 phy_sel_7_reg : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_WLAN_PHY_SEL_SET2_T;

//phy_sel_set3
typedef union {
    REG32 v;
    struct
    {
        REG32 phy_sel_8_reg : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 phy_sel_9_reg : 6; // [13:8]
        REG32 __15_14 : 2;
        REG32 phy_sel_10_reg : 6; // [21:16]
        REG32 __23_22 : 2;
        REG32 phy_sel_11_reg : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_WLAN_PHY_SEL_SET3_T;

//phy_sel_set4
typedef union {
    REG32 v;
    struct
    {
        REG32 phy_sel_12_reg : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 phy_sel_13_reg : 6; // [13:8]
        REG32 __15_14 : 2;
        REG32 phy_sel_14_reg : 6; // [21:16]
        REG32 __23_22 : 2;
        REG32 phy_sel_15_reg : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_WLAN_PHY_SEL_SET4_T;

//phy_sel_set5
typedef union {
    REG32 v;
    struct
    {
        REG32 phy_sel_16_reg : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 phy_sel_17_reg : 6; // [13:8]
        REG32 __15_14 : 2;
        REG32 phy_sel_18_reg : 6; // [21:16]
        REG32 __23_22 : 2;
        REG32 phy_sel_19_reg : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_WLAN_PHY_SEL_SET5_T;

//phy_sel_set6
typedef union {
    REG32 v;
    struct
    {
        REG32 phy_sel_20_reg : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 phy_sel_21_reg : 6; // [13:8]
        REG32 __15_14 : 2;
        REG32 phy_sel_22_reg : 6; // [21:16]
        REG32 __23_22 : 2;
        REG32 phy_sel_23_reg : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_WLAN_PHY_SEL_SET6_T;

//phy_sel_set7
typedef union {
    REG32 v;
    struct
    {
        REG32 phy_sel_24_reg : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 phy_sel_25_reg : 6; // [13:8]
        REG32 __15_14 : 2;
        REG32 phy_sel_26_reg : 6; // [21:16]
        REG32 __23_22 : 2;
        REG32 phy_sel_27_reg : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_WLAN_PHY_SEL_SET7_T;

//phy_sel_set8
typedef union {
    REG32 v;
    struct
    {
        REG32 phy_sel_28_reg : 6; // [5:0]
        REG32 __7_6 : 2;
        REG32 phy_sel_29_reg : 6; // [13:8]
        REG32 __15_14 : 2;
        REG32 phy_sel_30_reg : 6; // [21:16]
        REG32 __23_22 : 2;
        REG32 phy_sel_31_reg : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_WLAN_PHY_SEL_SET8_T;

#endif
