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

#ifndef _ADI_MST_H_
#define _ADI_MST_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'adi_mst'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// ADI_MST_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_ADI_MST_BASE 0x05300000
#else
#define REG_ADI_MST_BASE 0x50300000
#endif

typedef volatile struct
{
    REG32 adi_version;       //0x00000000
    REG32 adi_ctrl;          //0x00000004
    REG32 adi_pril;          //0x00000008
    REG32 Reserved_0000000C; //0x0000000C
    REG32 adi_int_en;        //0x00000010
    REG32 adi_int_raw;       //0x00000014
    REG32 adi_int_status;    //0x00000018
    REG32 adi_int_clear;     //0x0000001C
    REG32 adi_cfg0;          //0x00000020
    REG32 adi_cfg1;          //0x00000024
    REG32 arm_rd_cmd;        //0x00000028
    REG32 arm_rd_data;       //0x0000002C
    REG32 arm_cmd_status;    //0x00000030
    REG32 adi_chanel_en;     //0x00000034
    REG32 adi_cmd_wr;        //0x00000038
    REG32 adi_dat_wr;        //0x0000003C
    REG32 event0_waddr;      //0x00000040
    REG32 event1_waddr;      //0x00000044
    REG32 event2_waddr;      //0x00000048
    REG32 event3_waddr;      //0x0000004C
    REG32 event0_wdata;      //0x00000050
    REG32 event1_wdata;      //0x00000054
    REG32 event2_wdata;      //0x00000058
    REG32 event3_wdata;      //0x0000005C
} HWP_ADI_MST_T;

#define hwp_adiMst ((HWP_ADI_MST_T *)REG_ACCESS_ADDRESS(REG_ADI_MST_BASE))

//adi_version
typedef union {
    REG32 v;
    struct
    {
        REG32 adi_version_low : 4;   // [3:0]
        REG32 adi_version_high : 12; // [15:4], read only
        REG32 __31_16 : 16;
    } b;
} REG_ADI_MST_ADI_VERSION_T;

//adi_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 addr_byte_sel : 2; // [1:0]
        REG32 wr_bit_flag : 1;   // [2]
        REG32 addr_bits_sel : 2; // [4:3]
        REG32 wr_cmd_en : 1;     // [5]
        REG32 __31_6 : 26;
    } b;
} REG_ADI_MST_ADI_CTRL_T;

//adi_pril
typedef union {
    REG32 v;
    struct
    {
        REG32 chnl0_pri : 3;  // [2:0]
        REG32 chnl1_pri : 3;  // [5:3]
        REG32 event0_pri : 3; // [8:6]
        REG32 event1_pri : 3; // [11:9]
        REG32 event2_pri : 3; // [14:12]
        REG32 event3_pri : 3; // [17:15]
        REG32 __31_18 : 14;
    } b;
} REG_ADI_MST_ADI_PRIL_T;

//adi_int_en
typedef union {
    REG32 v;
    struct
    {
        REG32 wfifo_en : 1; // [0]
        REG32 __2_1 : 2;
        REG32 fifo_overflow_int_en : 1; // [3]
        REG32 __31_4 : 28;
    } b;
} REG_ADI_MST_ADI_INT_EN_T;

//adi_int_raw
typedef union {
    REG32 v;
    struct
    {
        REG32 __2_0 : 3;
        REG32 fifo_overflow_raw : 1; // [3], read only
        REG32 __31_4 : 28;
    } b;
} REG_ADI_MST_ADI_INT_RAW_T;

//adi_int_status
typedef union {
    REG32 v;
    struct
    {
        REG32 __2_0 : 3;
        REG32 fifo_overflow_status : 1; // [3], read only
        REG32 __31_4 : 28;
    } b;
} REG_ADI_MST_ADI_INT_STATUS_T;

//adi_int_clear
typedef union {
    REG32 v;
    struct
    {
        REG32 __2_0 : 3;
        REG32 fifo_overflow_clear : 1; // [3]
        REG32 __31_4 : 28;
    } b;
} REG_ADI_MST_ADI_INT_CLEAR_T;

//adi_cfg0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_gssi_frame_len : 6;    // [5:0]
        REG32 rf_gssi_cmd_len : 5;      // [10:6]
        REG32 rf_gssi_data_len : 5;     // [15:11]
        REG32 rf_gssi_wr_pos : 5;       // [20:16]
        REG32 rf_gssi_wr_pol : 1;       // [21]
        REG32 rf_gssi_sync_sel : 1;     // [22]
        REG32 rf_gssi_sync_mode : 1;    // [23]
        REG32 rf_gssi_sync : 1;         // [24]
        REG32 rf_gssi_sck_rev : 1;      // [25]
        REG32 rf_gssi_oe_cfg : 1;       // [26]
        REG32 rf_gssi_ie_cfg : 1;       // [27]
        REG32 rf_gssi_dummy_clk_en : 1; // [28]
        REG32 rf_gssi_fast_mode : 1;    // [29]
        REG32 rf_gssi_sck_all_on : 1;   // [30]
        REG32 rf_gssi_wr_disable : 1;   // [31]
    } b;
} REG_ADI_MST_ADI_CFG0_T;

//adi_cfg1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_gssi_ng_tx : 1;         // [0]
        REG32 rf_gssi_ng_rx : 1;         // [1]
        REG32 rf_gssi_clk_div : 8;       // [9:2]
        REG32 rf_gssi_sync_head_len : 3; // [12:10]
        REG32 rf_gssi_sync_end_len : 3;  // [15:13]
        REG32 rf_gssi_dummy_len : 4;     // [19:16]
        REG32 rf_gssi_sample_delay : 1;  // [20]
        REG32 rf_gssi_scc_len : 3;       // [23:21]
        REG32 rf_gssi_wbp_len : 3;       // [26:24]
        REG32 __27_27 : 1;
        REG32 rf_gssi_rbp_len : 3;      // [30:28]
        REG32 rf_gssi_strtbit_mode : 1; // [31]
    } b;
} REG_ADI_MST_ADI_CFG1_T;

//arm_rd_cmd
typedef union {
    REG32 v;
    struct
    {
        REG32 arm_rd_cmd : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_ADI_MST_ARM_RD_CMD_T;

//arm_rd_data
typedef union {
    REG32 v;
    struct
    {
        REG32 arm_rd_cmd : 16;     // [15:0], read only
        REG32 arm_rd_addr : 15;    // [30:16], read only
        REG32 arm_rd_cmd_busy : 1; // [31], read only
    } b;
} REG_ADI_MST_ARM_RD_DATA_T;

//arm_cmd_status
typedef union {
    REG32 v;
    struct
    {
        REG32 arm_wr_status : 1; // [0], read only
        REG32 arm_rd_status : 1; // [1], read only
        REG32 __3_2 : 2;
        REG32 adi_busy : 1; // [4], read only
        REG32 __7_5 : 3;
        REG32 wfifo_full : 1;  // [8], read only
        REG32 wfifo_empty : 1; // [9], read only
        REG32 __11_10 : 2;
        REG32 wfifo_fill_data_level : 3; // [14:12], read only
        REG32 __15_15 : 1;
        REG32 adi_fsm_status : 4;   // [19:16], read only
        REG32 event0_wr_status : 1; // [20], read only
        REG32 event1_wr_status : 1; // [21], read only
        REG32 event2_wr_status : 1; // [22], read only
        REG32 event3_wr_status : 1; // [23], read only
        REG32 __31_24 : 8;
    } b;
} REG_ADI_MST_ARM_CMD_STATUS_T;

//adi_chanel_en
typedef union {
    REG32 v;
    struct
    {
        REG32 event0_trigger_negedge_en : 1; // [0]
        REG32 event0_trigger_posedge_en : 1; // [1]
        REG32 event1_trigger_negedge_en : 1; // [2]
        REG32 event1_trigger_posedge_en : 1; // [3]
        REG32 event2_trigger_negedge_en : 1; // [4]
        REG32 event2_trigger_posedge_en : 1; // [5]
        REG32 event3_trigger_negedge_en : 1; // [6]
        REG32 event3_trigger_posedge_en : 1; // [7]
        REG32 __31_8 : 24;
    } b;
} REG_ADI_MST_ADI_CHANEL_EN_T;

//adi_cmd_wr
typedef union {
    REG32 v;
    struct
    {
        REG32 adi_cmd_wr : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_ADI_MST_ADI_CMD_WR_T;

//adi_dat_wr
typedef union {
    REG32 v;
    struct
    {
        REG32 adi_dat_wr : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ADI_MST_ADI_DAT_WR_T;

//event0_waddr
typedef union {
    REG32 v;
    struct
    {
        REG32 event0_waddr : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_ADI_MST_EVENT0_WADDR_T;

//event1_waddr
typedef union {
    REG32 v;
    struct
    {
        REG32 event1_waddr : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_ADI_MST_EVENT1_WADDR_T;

//event2_waddr
typedef union {
    REG32 v;
    struct
    {
        REG32 event2_waddr : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_ADI_MST_EVENT2_WADDR_T;

//event3_waddr
typedef union {
    REG32 v;
    struct
    {
        REG32 event3_waddr : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_ADI_MST_EVENT3_WADDR_T;

//event0_wdata
typedef union {
    REG32 v;
    struct
    {
        REG32 event0_neg_wdata : 16; // [15:0]
        REG32 event0_pos_wdata : 16; // [31:16]
    } b;
} REG_ADI_MST_EVENT0_WDATA_T;

//event1_wdata
typedef union {
    REG32 v;
    struct
    {
        REG32 event1_neg_wdata : 16; // [15:0]
        REG32 event1_pos_wdata : 16; // [31:16]
    } b;
} REG_ADI_MST_EVENT1_WDATA_T;

//event2_wdata
typedef union {
    REG32 v;
    struct
    {
        REG32 event2_neg_wdata : 16; // [15:0]
        REG32 event2_pos_wdata : 16; // [31:16]
    } b;
} REG_ADI_MST_EVENT2_WDATA_T;

//event3_wdata
typedef union {
    REG32 v;
    struct
    {
        REG32 event3_neg_wdata : 16; // [15:0]
        REG32 event3_pos_wdata : 16; // [31:16]
    } b;
} REG_ADI_MST_EVENT3_WDATA_T;

#endif
