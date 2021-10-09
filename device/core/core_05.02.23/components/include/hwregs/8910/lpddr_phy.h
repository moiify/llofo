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

#ifndef _LPDDR_PHY_H_
#define _LPDDR_PHY_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'lpddr_phy'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// LPDDR_PHY_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_LPDDR_PHY_BASE 0x08801000

typedef volatile struct
{
    REG32 lpddr_rf_cfg_phy;                  //0x00000000
    REG32 lpddr_rf_cfg_clock_gate;           //0x00000004
    REG32 lpddr_rf_cfg_sample_resync;        //0x00000008
    REG32 lpddr_rf_cfg_lpi;                  //0x0000000C
    REG32 Reserved_00000010[60];             //0x00000010
    REG32 lpddr_rf_cfg_ext;                  //0x00000100
    REG32 Reserved_00000104[63];             //0x00000104
    REG32 lpddr_rfdll_cfg_dll;               //0x00000200
    REG32 lpddr_rfdll_status_cpst_idle;      //0x00000204
    REG32 lpddr_rf_cfg_dll_ac;               //0x00000208
    REG32 lpddr_rfdll_status_dll_ac;         //0x0000020C
    REG32 lpddr_rf_cfg_dll_dl_0_wr_ac;       //0x00000210
    REG32 lpddr_rf_cfg_dll_dl_1_wr_ac;       //0x00000214
    REG32 lpddr_rf_cfg_dll_dl_2_wr_ac;       //0x00000218
    REG32 lpddr_rf_cfg_dll_dl_3_wr_ac;       //0x0000021C
    REG32 lpddr_rf_cfg_dll_dl_4_wr_ac;       //0x00000220
    REG32 lpddr_rfdll_status_max_cnt_ac;     //0x00000224
    REG32 lpddr_rfdll_status_min_cnt_ac;     //0x00000228
    REG32 lpddr_rf_cfg_phy_iomux_sel_wr_ac;  //0x0000022C
    REG32 lpddr_rf_cfg_phy_iomux_ie_wr_ac;   //0x00000230
    REG32 lpddr_rf_cfg_phy_iomux_oe_wr_ac;   //0x00000234
    REG32 lpddr_rf_cfg_phy_iomux_out_wr_ac;  //0x00000238
    REG32 lpddr_rf_cfg_dll_ds0;              //0x0000023C
    REG32 lpddr_rfdll_status_dll_ds0;        //0x00000240
    REG32 lpddr_rf_cfg_dll_dl_0_wr_ds0;      //0x00000244
    REG32 lpddr_rf_cfg_dll_dl_1_wr_ds0;      //0x00000248
    REG32 lpddr_rf_cfg_dll_dl_2_wr_ds0;      //0x0000024C
    REG32 lpddr_rf_cfg_dll_dl_3_wr_ds0;      //0x00000250
    REG32 lpddr_rf_cfg_dll_dl_4_wr_ds0;      //0x00000254
    REG32 lpddr_rf_cfg_dll_dl_5_wr_ds0;      //0x00000258
    REG32 lpddr_rf_cfg_dll_dl_6_wr_ds0;      //0x0000025C
    REG32 lpddr_rf_cfg_dll_dl_7_wr_ds0;      //0x00000260
    REG32 lpddr_rf_cfg_dll_dl_8_wr_ds0;      //0x00000264
    REG32 lpddr_rfdll_status_max_cnt_ds0;    //0x00000268
    REG32 lpddr_rfdll_status_min_cnt_ds0;    //0x0000026C
    REG32 lpddr_rf_cfg_phy_iomux_sel_wr_ds0; //0x00000270
    REG32 lpddr_rf_cfg_phy_iomux_ie_wr_ds0;  //0x00000274
    REG32 lpddr_rf_cfg_phy_iomux_oe_wr_ds0;  //0x00000278
    REG32 lpddr_rf_cfg_phy_iomux_out_wr_ds0; //0x0000027C
    REG32 lpddr_rf_cfg_dll_ds1;              //0x00000280
    REG32 lpddr_rfdll_status_dll_ds1;        //0x00000284
    REG32 lpddr_rf_cfg_dll_dl_0_wr_ds1;      //0x00000288
    REG32 lpddr_rf_cfg_dll_dl_1_wr_ds1;      //0x0000028C
    REG32 lpddr_rf_cfg_dll_dl_2_wr_ds1;      //0x00000290
    REG32 lpddr_rf_cfg_dll_dl_3_wr_ds1;      //0x00000294
    REG32 lpddr_rf_cfg_dll_dl_4_wr_ds1;      //0x00000298
    REG32 lpddr_rf_cfg_dll_dl_5_wr_ds1;      //0x0000029C
    REG32 lpddr_rf_cfg_dll_dl_6_wr_ds1;      //0x000002A0
    REG32 lpddr_rf_cfg_dll_dl_7_wr_ds1;      //0x000002A4
    REG32 lpddr_rf_cfg_dll_dl_8_wr_ds1;      //0x000002A8
    REG32 lpddr_rfdll_status_max_cnt_ds1;    //0x000002AC
    REG32 lpddr_rfdll_status_min_cnt_ds1;    //0x000002B0
    REG32 lpddr_rf_cfg_phy_iomux_sel_wr_ds1; //0x000002B4
    REG32 lpddr_rf_cfg_phy_iomux_ie_wr_ds1;  //0x000002B8
    REG32 lpddr_rf_cfg_phy_iomux_oe_wr_ds1;  //0x000002BC
    REG32 lpddr_rf_cfg_phy_iomux_out_wr_ds1; //0x000002C0
    REG32 lpddr_rf_status_phy_data_in;       //0x000002C4
    REG32 Reserved_000002C8[78];             //0x000002C8
    REG32 lpddr_drf_cfg;                     //0x00000400
    REG32 lpddr_drf_cfg_reg_sel;             //0x00000404
    REG32 lpddr_drf_cfg_dqs_ie_sel_f0;       //0x00000408
    REG32 lpddr_drf_cfg_dqs_oe_sel_f0;       //0x0000040C
    REG32 lpddr_drf_cfg_dqs_out_sel_f0;      //0x00000410
    REG32 lpddr_drf_cfg_dqs_gate_sel_f0;     //0x00000414
    REG32 lpddr_drf_cfg_data_ie_sel_f0;      //0x00000418
    REG32 lpddr_drf_cfg_data_oe_sel_f0;      //0x0000041C
    REG32 lpddr_drf_cfg_read_en_sel_f0;      //0x00000420
    REG32 lpddr_drf_cfg_dqs_ie_sel_f1;       //0x00000424
    REG32 lpddr_drf_cfg_dqs_oe_sel_f1;       //0x00000428
    REG32 lpddr_drf_cfg_dqs_out_sel_f1;      //0x0000042C
    REG32 lpddr_drf_cfg_dqs_gate_sel_f1;     //0x00000430
    REG32 lpddr_drf_cfg_data_ie_sel_f1;      //0x00000434
    REG32 lpddr_drf_cfg_data_oe_sel_f1;      //0x00000438
    REG32 lpddr_drf_cfg_read_en_sel_f1;      //0x0000043C
    REG32 lpddr_drf_cfg_dqs_ie_sel_f2;       //0x00000440
    REG32 lpddr_drf_cfg_dqs_oe_sel_f2;       //0x00000444
    REG32 lpddr_drf_cfg_dqs_out_sel_f2;      //0x00000448
    REG32 lpddr_drf_cfg_dqs_gate_sel_f2;     //0x0000044C
    REG32 lpddr_drf_cfg_data_ie_sel_f2;      //0x00000450
    REG32 lpddr_drf_cfg_data_oe_sel_f2;      //0x00000454
    REG32 lpddr_drf_cfg_read_en_sel_f2;      //0x00000458
    REG32 lpddr_drf_cfg_dqs_ie_sel_f3;       //0x0000045C
    REG32 lpddr_drf_cfg_dqs_oe_sel_f3;       //0x00000460
    REG32 lpddr_drf_cfg_dqs_out_sel_f3;      //0x00000464
    REG32 lpddr_drf_cfg_dqs_gate_sel_f3;     //0x00000468
    REG32 lpddr_drf_cfg_data_ie_sel_f3;      //0x0000046C
    REG32 lpddr_drf_cfg_data_oe_sel_f3;      //0x00000470
    REG32 lpddr_drf_cfg_read_en_sel_f3;      //0x00000474
    REG32 lpddr_drf_cfg_dll_mode_f0;         //0x00000478
    REG32 lpddr_drf_cfg_dll_cnt_f0;          //0x0000047C
    REG32 lpddr_drf_cfg_dll_mode_f1;         //0x00000480
    REG32 lpddr_drf_cfg_dll_cnt_f1;          //0x00000484
    REG32 lpddr_drf_cfg_dll_mode_f2;         //0x00000488
    REG32 lpddr_drf_cfg_dll_cnt_f2;          //0x0000048C
    REG32 lpddr_drf_cfg_dll_mode_f3;         //0x00000490
    REG32 lpddr_drf_cfg_dll_cnt_f3;          //0x00000494
    REG32 Reserved_00000498[26];             //0x00000498
    REG32 lpddr_drf_train_cfg;               //0x00000500
    REG32 lpddr_drf_mr_data_0;               //0x00000504
    REG32 lpddr_drf_mr_data_1;               //0x00000508
    REG32 Reserved_0000050C[61];             //0x0000050C
    REG32 lpddr_rf_irq_ctrl;                 //0x00000600
    REG32 lpddr_rf_irq_status_clr;           //0x00000604
    REG32 lpddr_rf_irq_status;               //0x00000608
    REG32 lpddr_rf_irq_cnt_clr;              //0x0000060C
    REG32 lpddr_rf_irq_cnt_dll_unlock_ac;    //0x00000610
    REG32 lpddr_rf_irq_cnt_dll_unlock_ds0;   //0x00000614
    REG32 lpddr_rf_irq_cnt_dll_unlock_ds1;   //0x00000618
    REG32 Reserved_0000061C[57];             //0x0000061C
    REG32 io_rf_ddr_rpull_cfg;               //0x00000700
    REG32 io_rf_ddr_drv_cfg;                 //0x00000704
    REG32 io_rf_ddr_pad_cfg;                 //0x00000708
    REG32 io_rf_ddr_vref_cfg;                //0x0000070C
    REG32 io_rf_ddr_zq_cfg;                  //0x00000710
    REG32 io_rf_ddr_zq_mon;                  //0x00000714
    REG32 io_rf_ddr_odt_cfg;                 //0x00000718
    REG32 io_rf_ddr_reserved;                //0x0000071C
    REG32 io_rf_psram_drv_cfg;               //0x00000720
    REG32 io_rf_psram_pad_en_cfg;            //0x00000724
    REG32 io_rf_psram_pull_cfg;              //0x00000728
    REG32 io_rf_psram_reserved;              //0x0000072C
} HWP_LPDDR_PHY_T;

#define hwp_lpddrPhy ((HWP_LPDDR_PHY_T *)REG_ACCESS_ADDRESS(REG_LPDDR_PHY_BASE))

//lpddr_rf_cfg_phy
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_en : 1;            // [0]
        REG32 rf_phy_init_complete : 1; // [1]
        REG32 __31_2 : 30;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_T;

//lpddr_rf_cfg_clock_gate
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_clk_gate_en : 1;       // [0]
        REG32 rf_clk_gate_fg_en : 1;    // [1]
        REG32 rf_clk_gate_ag_en : 1;    // [2]
        REG32 rf_clk_gate_ag_wr_en : 1; // [3]
        REG32 rf_clk_gate_ag_rd_en : 1; // [4]
        REG32 __31_5 : 27;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_CLOCK_GATE_T;

//lpddr_rf_cfg_sample_resync
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_sample_resync : 1;         // [0]
        REG32 rf_sample_resync_auto_en : 1; // [1]
        REG32 __15_2 : 14;
        REG32 rf_data_resync_sel : 16; // [31:16]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_SAMPLE_RESYNC_T;

//lpddr_rf_cfg_lpi
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_lpi_sel_m0 : 1; // [0]
        REG32 rf_cwakeup_m0 : 1; // [1]
        REG32 rf_cwakeup_s0 : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_LPI_T;

//lpddr_rf_cfg_ext
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_data_oe_ext : 4;     // [3:0]
        REG32 rf_data_ie_ext : 4;     // [7:4]
        REG32 rf_dqs_oe_ext : 4;      // [11:8]
        REG32 rf_dqs_ie_ext : 4;      // [15:12]
        REG32 rf_dqs_gate_ext : 4;    // [19:16]
        REG32 rf_data_resync_ext : 4; // [23:20]
        REG32 __31_24 : 8;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_EXT_T;

//lpddr_rfdll_cfg_dll
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_reset : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_CFG_DLL_T;

//lpddr_rfdll_status_cpst_idle
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdl_cpst_st_idle_ac : 1;  // [0], read only
        REG32 rfdl_cpst_st_idle_ds0 : 1; // [1], read only
        REG32 rfdl_cpst_st_idle_ds1 : 1; // [2], read only
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_CPST_IDLE_T;

//lpddr_rf_cfg_dll_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 __7_0 : 8;
        REG32 rf_dll_clr_ac : 1;             // [8]
        REG32 rf_dll_auto_clr_en_ac : 1;     // [9]
        REG32 rf_dl_cpst_en_ac : 1;          // [10]
        REG32 rf_dl_cpst_start_ac : 1;       // [11]
        REG32 rf_dl_cpst_auto_ref_en_ac : 1; // [12]
        REG32 rf_dll_err_clr_ac : 1;         // [13]
        REG32 rf_dll_clk_sel_ac : 1;         // [14]
        REG32 rf_dll_en_ac : 1;              // [15]
        REG32 rf_dl_cpst_thr_ac : 8;         // [23:16]
        REG32 rf_dll_pd_cnt_ac : 3;          // [26:24]
        REG32 rf_dll_auto_err_clr_en_ac : 1; // [27]
        REG32 rf_dll_lock_wait_ac : 4;       // [31:28]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_AC_T;

//lpddr_rfdll_status_dll_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_cnt_ac : 7; // [6:0], read only
        REG32 __23_7 : 17;
        REG32 rfdl_cpst_st_ac : 1; // [24], read only
        REG32 rfdll_st_ac : 3;     // [27:25], read only
        REG32 rfdll_locked_ac : 1; // [28], read only
        REG32 rfdll_error_ac : 1;  // [29], read only
        REG32 __31_30 : 2;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_DLL_AC_T;

//lpddr_rf_cfg_dll_dl_0_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_clkwr_raw_dl_sel_ac : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_clkwr_raw_cnt_ac : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_clkwr_raw_dl_cpst_offset_ac : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_clkwr_qtr_dl_sel_ac : 2;         // [25:24]
        REG32 rfdl_clkwr_qtr_cnt_ac : 2;          // [27:26], read only
        REG32 rf_clkwr_qtr_dl_cpst_offset_ac : 2; // [29:28]
        REG32 rf_clkwr_dl_cpst_minus_ac : 1;      // [30]
        REG32 rf_clkwr_dl_cpst_en_ac : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_0_WR_AC_T;

//lpddr_rf_cfg_dll_dl_1_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_a0_dl_sel : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_a1_dl_sel : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_out_a2_dl_sel : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_out_a3_dl_sel : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_1_WR_AC_T;

//lpddr_rf_cfg_dll_dl_2_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_a4_dl_sel : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_a5_dl_sel : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_out_a6_dl_sel : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_out_a7_dl_sel : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_2_WR_AC_T;

//lpddr_rf_cfg_dll_dl_3_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_a8_dl_sel : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_a9_dl_sel : 5; // [12:8]
        REG32 __31_13 : 19;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_3_WR_AC_T;

//lpddr_rf_cfg_dll_dl_4_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_csn_dl_sel : 5; // [4:0]
        REG32 __15_5 : 11;
        REG32 rf_dly_out_cke_dl_sel : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_out_clk_dl_sel : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_4_WR_AC_T;

//lpddr_rfdll_status_max_cnt_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_max_cnt_f0_ac : 7; // [6:0], read only
        REG32 __7_7 : 1;
        REG32 rfdll_max_cnt_f1_ac : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rfdll_max_cnt_f2_ac : 7; // [22:16], read only
        REG32 __23_23 : 1;
        REG32 rfdll_max_cnt_f3_ac : 7; // [30:24], read only
        REG32 __31_31 : 1;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_MAX_CNT_AC_T;

//lpddr_rfdll_status_min_cnt_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_min_cnt_f0_ac : 7; // [6:0], read only
        REG32 __7_7 : 1;
        REG32 rfdll_min_cnt_f1_ac : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rfdll_min_cnt_f2_ac : 7; // [22:16], read only
        REG32 __23_23 : 1;
        REG32 rfdll_min_cnt_f3_ac : 7; // [30:24], read only
        REG32 __31_31 : 1;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_MIN_CNT_AC_T;

//lpddr_rf_cfg_phy_iomux_sel_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_a0_sel_ac : 1; // [0]
        REG32 rf_phy_io_a1_sel_ac : 1; // [1]
        REG32 rf_phy_io_a2_sel_ac : 1; // [2]
        REG32 rf_phy_io_a3_sel_ac : 1; // [3]
        REG32 rf_phy_io_a4_sel_ac : 1; // [4]
        REG32 rf_phy_io_a5_sel_ac : 1; // [5]
        REG32 rf_phy_io_a6_sel_ac : 1; // [6]
        REG32 rf_phy_io_a7_sel_ac : 1; // [7]
        REG32 rf_phy_io_a8_sel_ac : 1; // [8]
        REG32 rf_phy_io_a9_sel_ac : 1; // [9]
        REG32 __15_10 : 6;
        REG32 rf_phy_io_csn_sel_ac : 1; // [16]
        REG32 __19_17 : 3;
        REG32 rf_phy_io_cke0_sel_ac : 1; // [20]
        REG32 rf_phy_io_cke1_sel_ac : 1; // [21]
        REG32 __31_22 : 10;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_SEL_WR_AC_T;

//lpddr_rf_cfg_phy_iomux_ie_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_a0_ie_ac : 1; // [0]
        REG32 rf_phy_io_a1_ie_ac : 1; // [1]
        REG32 rf_phy_io_a2_ie_ac : 1; // [2]
        REG32 rf_phy_io_a3_ie_ac : 1; // [3]
        REG32 rf_phy_io_a4_ie_ac : 1; // [4]
        REG32 rf_phy_io_a5_ie_ac : 1; // [5]
        REG32 rf_phy_io_a6_ie_ac : 1; // [6]
        REG32 rf_phy_io_a7_ie_ac : 1; // [7]
        REG32 rf_phy_io_a8_ie_ac : 1; // [8]
        REG32 rf_phy_io_a9_ie_ac : 1; // [9]
        REG32 __15_10 : 6;
        REG32 rf_phy_io_csn_ie_ac : 1; // [16]
        REG32 __19_17 : 3;
        REG32 rf_phy_io_cke0_ie_ac : 1; // [20]
        REG32 rf_phy_io_cke1_ie_ac : 1; // [21]
        REG32 __31_22 : 10;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_IE_WR_AC_T;

//lpddr_rf_cfg_phy_iomux_oe_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_a0_oe_ac : 1; // [0]
        REG32 rf_phy_io_a1_oe_ac : 1; // [1]
        REG32 rf_phy_io_a2_oe_ac : 1; // [2]
        REG32 rf_phy_io_a3_oe_ac : 1; // [3]
        REG32 rf_phy_io_a4_oe_ac : 1; // [4]
        REG32 rf_phy_io_a5_oe_ac : 1; // [5]
        REG32 rf_phy_io_a6_oe_ac : 1; // [6]
        REG32 rf_phy_io_a7_oe_ac : 1; // [7]
        REG32 rf_phy_io_a8_oe_ac : 1; // [8]
        REG32 rf_phy_io_a9_oe_ac : 1; // [9]
        REG32 __15_10 : 6;
        REG32 rf_phy_io_csn_oe_ac : 1; // [16]
        REG32 __19_17 : 3;
        REG32 rf_phy_io_cke0_oe_ac : 1; // [20]
        REG32 rf_phy_io_cke1_oe_ac : 1; // [21]
        REG32 __31_22 : 10;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_OE_WR_AC_T;

//lpddr_rf_cfg_phy_iomux_out_wr_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_a0_out_ac : 1; // [0]
        REG32 rf_phy_io_a1_out_ac : 1; // [1]
        REG32 rf_phy_io_a2_out_ac : 1; // [2]
        REG32 rf_phy_io_a3_out_ac : 1; // [3]
        REG32 rf_phy_io_a4_out_ac : 1; // [4]
        REG32 rf_phy_io_a5_out_ac : 1; // [5]
        REG32 rf_phy_io_a6_out_ac : 1; // [6]
        REG32 rf_phy_io_a7_out_ac : 1; // [7]
        REG32 rf_phy_io_a8_out_ac : 1; // [8]
        REG32 rf_phy_io_a9_out_ac : 1; // [9]
        REG32 __15_10 : 6;
        REG32 rf_phy_io_csn_out_ac : 1; // [16]
        REG32 __19_17 : 3;
        REG32 rf_phy_io_cke0_out_ac : 1; // [20]
        REG32 rf_phy_io_cke1_out_ac : 1; // [21]
        REG32 __31_22 : 10;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_OUT_WR_AC_T;

//lpddr_rf_cfg_dll_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 __7_0 : 8;
        REG32 rf_dll_clr_ds0 : 1;             // [8]
        REG32 rf_dll_auto_clr_en_ds0 : 1;     // [9]
        REG32 rf_dl_cpst_en_ds0 : 1;          // [10]
        REG32 rf_dl_cpst_start_ds0 : 1;       // [11]
        REG32 rf_dl_cpst_auto_ref_en_ds0 : 1; // [12]
        REG32 rf_dll_err_clr_ds0 : 1;         // [13]
        REG32 rf_dll_clk_sel_ds0 : 1;         // [14]
        REG32 rf_dll_en_ds0 : 1;              // [15]
        REG32 rf_dl_cpst_thr_ds0 : 8;         // [23:16]
        REG32 rf_dll_pd_cnt_ds0 : 3;          // [26:24]
        REG32 rf_dll_auto_err_clr_en_ds0 : 1; // [27]
        REG32 rf_dll_lock_wait_ds0 : 4;       // [31:28]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DS0_T;

//lpddr_rfdll_status_dll_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_cnt_ds0 : 7; // [6:0], read only
        REG32 __23_7 : 17;
        REG32 rfdl_cpst_st_ds0 : 1; // [24], read only
        REG32 rfdll_st_ds0 : 3;     // [27:25], read only
        REG32 rfdll_locked_ds0 : 1; // [28], read only
        REG32 rfdll_error_ds0 : 1;  // [29], read only
        REG32 __31_30 : 2;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_DLL_DS0_T;

//lpddr_rf_cfg_dll_dl_0_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_clkwr_raw_dl_sel_ds0 : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_clkwr_raw_cnt_ds0 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_clkwr_raw_dl_cpst_offset_ds0 : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_clkwr_qtr_dl_sel_ds0 : 2;         // [25:24]
        REG32 rfdl_clkwr_qtr_cnt_ds0 : 2;          // [27:26], read only
        REG32 rf_clkwr_qtr_dl_cpst_offset_ds0 : 2; // [29:28]
        REG32 rf_clkwr_dl_cpst_minus_ds0 : 1;      // [30]
        REG32 rf_clkwr_dl_cpst_en_ds0 : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_0_WR_DS0_T;

//lpddr_rf_cfg_dll_dl_1_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dqs_in_pos_raw_dl_sel_ds0 : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_dqs_in_pos_raw_cnt_ds0 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_dqs_in_pos_raw_dl_cpst_offset_ds0 : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_dqs_in_pos_qtr_dl_sel_ds0 : 2;         // [25:24]
        REG32 rfdl_dqs_in_pos_qtr_cnt_ds0 : 2;          // [27:26], read only
        REG32 rf_dqs_in_pos_qtr_dl_cpst_offset_ds0 : 2; // [29:28]
        REG32 rf_dqs_in_pos_dl_cpst_minus_ds0 : 1;      // [30]
        REG32 rf_dqs_in_pos_dl_cpst_en_ds0 : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_1_WR_DS0_T;

//lpddr_rf_cfg_dll_dl_2_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dqs_in_neg_raw_dl_sel_ds0 : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_dqs_in_neg_raw_cnt_ds0 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_dqs_in_neg_raw_dl_cpst_offset_ds0 : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_dqs_in_neg_qtr_dl_sel_ds0 : 2;         // [25:24]
        REG32 rfdl_dqs_in_neg_qtr_cnt_ds0 : 2;          // [27:26], read only
        REG32 rf_dqs_in_neg_qtr_dl_cpst_offset_ds0 : 2; // [29:28]
        REG32 rf_dqs_in_neg_dl_cpst_minus_ds0 : 1;      // [30]
        REG32 rf_dqs_in_neg_dl_cpst_en_ds0 : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_2_WR_DS0_T;

//lpddr_rf_cfg_dll_dl_3_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dqs_gate_raw_dl_sel_ds0 : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_dqs_gate_raw_cnt_ds0 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_dqs_gate_raw_dl_cpst_offset_ds0 : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_dqs_gate_qtr_dl_sel_ds0 : 2;         // [25:24]
        REG32 rfdl_dqs_gate_qtr_cnt_ds0 : 2;          // [27:26], read only
        REG32 rf_dqs_gate_qtr_dl_cpst_offset_ds0 : 2; // [29:28]
        REG32 rf_dqs_gate_dl_cpst_minus_ds0 : 1;      // [30]
        REG32 rf_dqs_gate_dl_cpst_en_ds0 : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_3_WR_DS0_T;

//lpddr_rf_cfg_dll_dl_4_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_d0_dl_sel_ds0 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_d1_dl_sel_ds0 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_out_d2_dl_sel_ds0 : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_out_d3_dl_sel_ds0 : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_4_WR_DS0_T;

//lpddr_rf_cfg_dll_dl_5_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_d4_dl_sel_ds0 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_d5_dl_sel_ds0 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_out_d6_dl_sel_ds0 : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_out_d7_dl_sel_ds0 : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_5_WR_DS0_T;

//lpddr_rf_cfg_dll_dl_6_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_in_d0_dl_sel_ds0 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_in_d1_dl_sel_ds0 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_in_d2_dl_sel_ds0 : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_in_d3_dl_sel_ds0 : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_6_WR_DS0_T;

//lpddr_rf_cfg_dll_dl_7_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_in_d4_dl_sel_ds0 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_in_d5_dl_sel_ds0 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_in_d6_dl_sel_ds0 : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_in_d7_dl_sel_ds0 : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_7_WR_DS0_T;

//lpddr_rf_cfg_dll_dl_8_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_dqs_dl_sel_ds0 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_dqm_dl_sel_ds0 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_in_dqs_dl_sel_ds0 : 5; // [20:16]
        REG32 __31_21 : 11;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_8_WR_DS0_T;

//lpddr_rfdll_status_max_cnt_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_max_cnt_f0_ds0 : 7; // [6:0], read only
        REG32 __7_7 : 1;
        REG32 rfdll_max_cnt_f1_ds0 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rfdll_max_cnt_f2_ds0 : 7; // [22:16], read only
        REG32 __23_23 : 1;
        REG32 rfdll_max_cnt_f3_ds0 : 7; // [30:24], read only
        REG32 __31_31 : 1;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_MAX_CNT_DS0_T;

//lpddr_rfdll_status_min_cnt_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_min_cnt_f0_ds0 : 7; // [6:0], read only
        REG32 __7_7 : 1;
        REG32 rfdll_min_cnt_f1_ds0 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rfdll_min_cnt_f2_ds0 : 7; // [22:16], read only
        REG32 __23_23 : 1;
        REG32 rfdll_min_cnt_f3_ds0 : 7; // [30:24], read only
        REG32 __31_31 : 1;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_MIN_CNT_DS0_T;

//lpddr_rf_cfg_phy_iomux_sel_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_d0_sel_ds0 : 1;  // [0]
        REG32 rf_phy_io_d1_sel_ds0 : 1;  // [1]
        REG32 rf_phy_io_d2_sel_ds0 : 1;  // [2]
        REG32 rf_phy_io_d3_sel_ds0 : 1;  // [3]
        REG32 rf_phy_io_d4_sel_ds0 : 1;  // [4]
        REG32 rf_phy_io_d5_sel_ds0 : 1;  // [5]
        REG32 rf_phy_io_d6_sel_ds0 : 1;  // [6]
        REG32 rf_phy_io_d7_sel_ds0 : 1;  // [7]
        REG32 rf_phy_io_dqm_sel_ds0 : 1; // [8]
        REG32 rf_phy_io_dqs_sel_ds0 : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_SEL_WR_DS0_T;

//lpddr_rf_cfg_phy_iomux_ie_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_d0_ie_ds0 : 1;  // [0]
        REG32 rf_phy_io_d1_ie_ds0 : 1;  // [1]
        REG32 rf_phy_io_d2_ie_ds0 : 1;  // [2]
        REG32 rf_phy_io_d3_ie_ds0 : 1;  // [3]
        REG32 rf_phy_io_d4_ie_ds0 : 1;  // [4]
        REG32 rf_phy_io_d5_ie_ds0 : 1;  // [5]
        REG32 rf_phy_io_d6_ie_ds0 : 1;  // [6]
        REG32 rf_phy_io_d7_ie_ds0 : 1;  // [7]
        REG32 rf_phy_io_dqm_ie_ds0 : 1; // [8]
        REG32 rf_phy_io_dqs_ie_ds0 : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_IE_WR_DS0_T;

//lpddr_rf_cfg_phy_iomux_oe_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_d0_oe_ds0 : 1;  // [0]
        REG32 rf_phy_io_d1_oe_ds0 : 1;  // [1]
        REG32 rf_phy_io_d2_oe_ds0 : 1;  // [2]
        REG32 rf_phy_io_d3_oe_ds0 : 1;  // [3]
        REG32 rf_phy_io_d4_oe_ds0 : 1;  // [4]
        REG32 rf_phy_io_d5_oe_ds0 : 1;  // [5]
        REG32 rf_phy_io_d6_oe_ds0 : 1;  // [6]
        REG32 rf_phy_io_d7_oe_ds0 : 1;  // [7]
        REG32 rf_phy_io_dqm_oe_ds0 : 1; // [8]
        REG32 rf_phy_io_dqs_oe_ds0 : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_OE_WR_DS0_T;

//lpddr_rf_cfg_phy_iomux_out_wr_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_d0_out_ds0 : 1;  // [0]
        REG32 rf_phy_io_d1_out_ds0 : 1;  // [1]
        REG32 rf_phy_io_d2_out_ds0 : 1;  // [2]
        REG32 rf_phy_io_d3_out_ds0 : 1;  // [3]
        REG32 rf_phy_io_d4_out_ds0 : 1;  // [4]
        REG32 rf_phy_io_d5_out_ds0 : 1;  // [5]
        REG32 rf_phy_io_d6_out_ds0 : 1;  // [6]
        REG32 rf_phy_io_d7_out_ds0 : 1;  // [7]
        REG32 rf_phy_io_dqm_out_ds0 : 1; // [8]
        REG32 rf_phy_io_dqs_out_ds0 : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_OUT_WR_DS0_T;

//lpddr_rf_cfg_dll_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 __7_0 : 8;
        REG32 rf_dll_clr_ds1 : 1;             // [8]
        REG32 rf_dll_auto_clr_en_ds1 : 1;     // [9]
        REG32 rf_dl_cpst_en_ds1 : 1;          // [10]
        REG32 rf_dl_cpst_start_ds1 : 1;       // [11]
        REG32 rf_dl_cpst_auto_ref_en_ds1 : 1; // [12]
        REG32 rf_dll_err_clr_ds1 : 1;         // [13]
        REG32 rf_dll_clk_sel_ds1 : 1;         // [14]
        REG32 rf_dll_en_ds1 : 1;              // [15]
        REG32 rf_dl_cpst_thr_ds1 : 8;         // [23:16]
        REG32 rf_dll_pd_cnt_ds1 : 3;          // [26:24]
        REG32 rf_dll_auto_err_clr_en_ds1 : 1; // [27]
        REG32 rf_dll_lock_wait_ds1 : 4;       // [31:28]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DS1_T;

//lpddr_rfdll_status_dll_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_cnt_ds1 : 7; // [6:0], read only
        REG32 __23_7 : 17;
        REG32 rfdl_cpst_st_ds1 : 1; // [24], read only
        REG32 rfdll_st_ds1 : 3;     // [27:25], read only
        REG32 rfdll_locked_ds1 : 1; // [28], read only
        REG32 rfdll_error_ds1 : 1;  // [29], read only
        REG32 __31_30 : 2;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_DLL_DS1_T;

//lpddr_rf_cfg_dll_dl_0_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_clkwr_raw_dl_sel_ds1 : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_clkwr_raw_cnt_ds1 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_clkwr_raw_dl_cpst_offset_ds1 : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_clkwr_qtr_dl_sel_ds1 : 2;         // [25:24]
        REG32 rfdl_clkwr_qtr_cnt_ds1 : 2;          // [27:26], read only
        REG32 rf_clkwr_qtr_dl_cpst_offset_ds1 : 2; // [29:28]
        REG32 rf_clkwr_dl_cpst_minus_ds1 : 1;      // [30]
        REG32 rf_clkwr_dl_cpst_en_ds1 : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_0_WR_DS1_T;

//lpddr_rf_cfg_dll_dl_1_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dqs_in_pos_raw_dl_sel_ds1 : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_dqs_in_pos_raw_cnt_ds1 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_dqs_in_pos_raw_dl_cpst_offset_ds1 : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_dqs_in_pos_qtr_dl_sel_ds1 : 2;         // [25:24]
        REG32 rfdl_dqs_in_pos_qtr_cnt_ds1 : 2;          // [27:26], read only
        REG32 rf_dqs_in_pos_qtr_dl_cpst_offset_ds1 : 2; // [29:28]
        REG32 rf_dqs_in_pos_dl_cpst_minus_ds1 : 1;      // [30]
        REG32 rf_dqs_in_pos_dl_cpst_en_ds1 : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_1_WR_DS1_T;

//lpddr_rf_cfg_dll_dl_2_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dqs_in_neg_raw_dl_sel_ds1 : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_dqs_in_neg_raw_cnt_ds1 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_dqs_in_neg_raw_dl_cpst_offset_ds1 : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_dqs_in_neg_qtr_dl_sel_ds1 : 2;         // [25:24]
        REG32 rfdl_dqs_in_neg_qtr_cnt_ds1 : 2;          // [27:26], read only
        REG32 rf_dqs_in_neg_qtr_dl_cpst_offset_ds1 : 2; // [29:28]
        REG32 rf_dqs_in_neg_dl_cpst_minus_ds1 : 1;      // [30]
        REG32 rf_dqs_in_neg_dl_cpst_en_ds1 : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_2_WR_DS1_T;

//lpddr_rf_cfg_dll_dl_3_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dqs_gate_raw_dl_sel_ds1 : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rfdl_dqs_gate_raw_cnt_ds1 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rf_dqs_gate_raw_dl_cpst_offset_ds1 : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 rf_dqs_gate_qtr_dl_sel_ds1 : 2;         // [25:24]
        REG32 rfdl_dqs_gate_qtr_cnt_ds1 : 2;          // [27:26], read only
        REG32 rf_dqs_gate_qtr_dl_cpst_offset_ds1 : 2; // [29:28]
        REG32 rf_dqs_gate_dl_cpst_minus_ds1 : 1;      // [30]
        REG32 rf_dqs_gate_dl_cpst_en_ds1 : 1;         // [31]
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_3_WR_DS1_T;

//lpddr_rf_cfg_dll_dl_4_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_d0_dl_sel_ds1 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_d1_dl_sel_ds1 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_out_d2_dl_sel_ds1 : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_out_d3_dl_sel_ds1 : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_4_WR_DS1_T;

//lpddr_rf_cfg_dll_dl_5_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_d4_dl_sel_ds1 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_d5_dl_sel_ds1 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_out_d6_dl_sel_ds1 : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_out_d7_dl_sel_ds1 : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_5_WR_DS1_T;

//lpddr_rf_cfg_dll_dl_6_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_in_d0_dl_sel_ds1 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_in_d1_dl_sel_ds1 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_in_d2_dl_sel_ds1 : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_in_d3_dl_sel_ds1 : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_6_WR_DS1_T;

//lpddr_rf_cfg_dll_dl_7_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_in_d4_dl_sel_ds1 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_in_d5_dl_sel_ds1 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_in_d6_dl_sel_ds1 : 5; // [20:16]
        REG32 __23_21 : 3;
        REG32 rf_dly_in_d7_dl_sel_ds1 : 5; // [28:24]
        REG32 __31_29 : 3;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_7_WR_DS1_T;

//lpddr_rf_cfg_dll_dl_8_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_dly_out_dqs_dl_sel_ds1 : 5; // [4:0]
        REG32 __7_5 : 3;
        REG32 rf_dly_out_dqm_dl_sel_ds1 : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rf_dly_in_dqs_dl_sel_ds1 : 5; // [20:16]
        REG32 __31_21 : 11;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_DLL_DL_8_WR_DS1_T;

//lpddr_rfdll_status_max_cnt_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_max_cnt_f0_ds1 : 7; // [6:0], read only
        REG32 __7_7 : 1;
        REG32 rfdll_max_cnt_f1_ds1 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rfdll_max_cnt_f2_ds1 : 7; // [22:16], read only
        REG32 __23_23 : 1;
        REG32 rfdll_max_cnt_f3_ds1 : 7; // [30:24], read only
        REG32 __31_31 : 1;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_MAX_CNT_DS1_T;

//lpddr_rfdll_status_min_cnt_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rfdll_min_cnt_f0_ds1 : 7; // [6:0], read only
        REG32 __7_7 : 1;
        REG32 rfdll_min_cnt_f1_ds1 : 7; // [14:8], read only
        REG32 __15_15 : 1;
        REG32 rfdll_min_cnt_f2_ds1 : 7; // [22:16], read only
        REG32 __23_23 : 1;
        REG32 rfdll_min_cnt_f3_ds1 : 7; // [30:24], read only
        REG32 __31_31 : 1;
    } b;
} REG_LPDDR_PHY_LPDDR_RFDLL_STATUS_MIN_CNT_DS1_T;

//lpddr_rf_cfg_phy_iomux_sel_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_d0_sel_ds1 : 1;  // [0]
        REG32 rf_phy_io_d1_sel_ds1 : 1;  // [1]
        REG32 rf_phy_io_d2_sel_ds1 : 1;  // [2]
        REG32 rf_phy_io_d3_sel_ds1 : 1;  // [3]
        REG32 rf_phy_io_d4_sel_ds1 : 1;  // [4]
        REG32 rf_phy_io_d5_sel_ds1 : 1;  // [5]
        REG32 rf_phy_io_d6_sel_ds1 : 1;  // [6]
        REG32 rf_phy_io_d7_sel_ds1 : 1;  // [7]
        REG32 rf_phy_io_dqm_sel_ds1 : 1; // [8]
        REG32 rf_phy_io_dqs_sel_ds1 : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_SEL_WR_DS1_T;

//lpddr_rf_cfg_phy_iomux_ie_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_d0_ie_ds1 : 1;  // [0]
        REG32 rf_phy_io_d1_ie_ds1 : 1;  // [1]
        REG32 rf_phy_io_d2_ie_ds1 : 1;  // [2]
        REG32 rf_phy_io_d3_ie_ds1 : 1;  // [3]
        REG32 rf_phy_io_d4_ie_ds1 : 1;  // [4]
        REG32 rf_phy_io_d5_ie_ds1 : 1;  // [5]
        REG32 rf_phy_io_d6_ie_ds1 : 1;  // [6]
        REG32 rf_phy_io_d7_ie_ds1 : 1;  // [7]
        REG32 rf_phy_io_dqm_ie_ds1 : 1; // [8]
        REG32 rf_phy_io_dqs_ie_ds1 : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_IE_WR_DS1_T;

//lpddr_rf_cfg_phy_iomux_oe_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_d0_oe_ds1 : 1;  // [0]
        REG32 rf_phy_io_d1_oe_ds1 : 1;  // [1]
        REG32 rf_phy_io_d2_oe_ds1 : 1;  // [2]
        REG32 rf_phy_io_d3_oe_ds1 : 1;  // [3]
        REG32 rf_phy_io_d4_oe_ds1 : 1;  // [4]
        REG32 rf_phy_io_d5_oe_ds1 : 1;  // [5]
        REG32 rf_phy_io_d6_oe_ds1 : 1;  // [6]
        REG32 rf_phy_io_d7_oe_ds1 : 1;  // [7]
        REG32 rf_phy_io_dqm_oe_ds1 : 1; // [8]
        REG32 rf_phy_io_dqs_oe_ds1 : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_OE_WR_DS1_T;

//lpddr_rf_cfg_phy_iomux_out_wr_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_io_d0_out_ds1 : 1;  // [0]
        REG32 rf_phy_io_d1_out_ds1 : 1;  // [1]
        REG32 rf_phy_io_d2_out_ds1 : 1;  // [2]
        REG32 rf_phy_io_d3_out_ds1 : 1;  // [3]
        REG32 rf_phy_io_d4_out_ds1 : 1;  // [4]
        REG32 rf_phy_io_d5_out_ds1 : 1;  // [5]
        REG32 rf_phy_io_d6_out_ds1 : 1;  // [6]
        REG32 rf_phy_io_d7_out_ds1 : 1;  // [7]
        REG32 rf_phy_io_dqm_out_ds1 : 1; // [8]
        REG32 rf_phy_io_dqs_out_ds1 : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_CFG_PHY_IOMUX_OUT_WR_DS1_T;

//lpddr_rf_status_phy_data_in
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_phy_data_in : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_STATUS_PHY_DATA_IN_T;

//lpddr_drf_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_clkdmem_out_sel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_T;

//lpddr_drf_cfg_reg_sel
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_reg_sel : 2; // [1:0]
        REG32 __31_2 : 30;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_REG_SEL_T;

//lpddr_drf_cfg_dqs_ie_sel_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_ie_sel_f0 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_IE_SEL_F0_T;

//lpddr_drf_cfg_dqs_oe_sel_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_oe_sel_f0 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_OE_SEL_F0_T;

//lpddr_drf_cfg_dqs_out_sel_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_out_sel_f0 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_OUT_SEL_F0_T;

//lpddr_drf_cfg_dqs_gate_sel_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_gate_sel_f0 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_GATE_SEL_F0_T;

//lpddr_drf_cfg_data_ie_sel_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_data_ie_sel_f0 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DATA_IE_SEL_F0_T;

//lpddr_drf_cfg_data_oe_sel_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_data_oe_sel_f0 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DATA_OE_SEL_F0_T;

//lpddr_drf_cfg_read_en_sel_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_read_en_sel_f0 : 4; // [3:0]
        REG32 __31_4 : 28;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_READ_EN_SEL_F0_T;

//lpddr_drf_cfg_dqs_ie_sel_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_ie_sel_f1 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_IE_SEL_F1_T;

//lpddr_drf_cfg_dqs_oe_sel_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_oe_sel_f1 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_OE_SEL_F1_T;

//lpddr_drf_cfg_dqs_out_sel_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_out_sel_f1 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_OUT_SEL_F1_T;

//lpddr_drf_cfg_dqs_gate_sel_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_gate_sel_f1 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_GATE_SEL_F1_T;

//lpddr_drf_cfg_data_ie_sel_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_data_ie_sel_f1 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DATA_IE_SEL_F1_T;

//lpddr_drf_cfg_data_oe_sel_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_data_oe_sel_f1 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DATA_OE_SEL_F1_T;

//lpddr_drf_cfg_read_en_sel_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_read_en_sel_f1 : 4; // [3:0]
        REG32 __31_4 : 28;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_READ_EN_SEL_F1_T;

//lpddr_drf_cfg_dqs_ie_sel_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_ie_sel_f2 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_IE_SEL_F2_T;

//lpddr_drf_cfg_dqs_oe_sel_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_oe_sel_f2 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_OE_SEL_F2_T;

//lpddr_drf_cfg_dqs_out_sel_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_out_sel_f2 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_OUT_SEL_F2_T;

//lpddr_drf_cfg_dqs_gate_sel_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_gate_sel_f2 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_GATE_SEL_F2_T;

//lpddr_drf_cfg_data_ie_sel_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_data_ie_sel_f2 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DATA_IE_SEL_F2_T;

//lpddr_drf_cfg_data_oe_sel_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_data_oe_sel_f2 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DATA_OE_SEL_F2_T;

//lpddr_drf_cfg_read_en_sel_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_read_en_sel_f2 : 4; // [3:0]
        REG32 __31_4 : 28;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_READ_EN_SEL_F2_T;

//lpddr_drf_cfg_dqs_ie_sel_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_ie_sel_f3 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_IE_SEL_F3_T;

//lpddr_drf_cfg_dqs_oe_sel_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_oe_sel_f3 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_OE_SEL_F3_T;

//lpddr_drf_cfg_dqs_out_sel_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_out_sel_f3 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_OUT_SEL_F3_T;

//lpddr_drf_cfg_dqs_gate_sel_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dqs_gate_sel_f3 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DQS_GATE_SEL_F3_T;

//lpddr_drf_cfg_data_ie_sel_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_data_ie_sel_f3 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DATA_IE_SEL_F3_T;

//lpddr_drf_cfg_data_oe_sel_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_data_oe_sel_f3 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DATA_OE_SEL_F3_T;

//lpddr_drf_cfg_read_en_sel_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_read_en_sel_f3 : 4; // [3:0]
        REG32 __31_4 : 28;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_READ_EN_SEL_F3_T;

//lpddr_drf_cfg_dll_mode_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dll_clk_mode_f0 : 1;  // [0]
        REG32 drf_dll_half_mode_f0 : 1; // [1]
        REG32 drf_dll_satu_mode_f0 : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DLL_MODE_F0_T;

//lpddr_drf_cfg_dll_cnt_f0
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dll_init_cnt_f0 : 10; // [9:0]
        REG32 drf_dll_satu_cnt_f0 : 10; // [19:10]
        REG32 drf_dll_auto_cnt_f0 : 10; // [29:20]
        REG32 __31_30 : 2;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DLL_CNT_F0_T;

//lpddr_drf_cfg_dll_mode_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dll_clk_mode_f1 : 1;  // [0]
        REG32 drf_dll_half_mode_f1 : 1; // [1]
        REG32 drf_dll_satu_mode_f1 : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DLL_MODE_F1_T;

//lpddr_drf_cfg_dll_cnt_f1
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dll_init_cnt_f1 : 10; // [9:0]
        REG32 drf_dll_satu_cnt_f1 : 10; // [19:10]
        REG32 drf_dll_auto_cnt_f1 : 10; // [29:20]
        REG32 __31_30 : 2;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DLL_CNT_F1_T;

//lpddr_drf_cfg_dll_mode_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dll_clk_mode_f2 : 1;  // [0]
        REG32 drf_dll_half_mode_f2 : 1; // [1]
        REG32 drf_dll_satu_mode_f2 : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DLL_MODE_F2_T;

//lpddr_drf_cfg_dll_cnt_f2
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dll_init_cnt_f2 : 10; // [9:0]
        REG32 drf_dll_satu_cnt_f2 : 10; // [19:10]
        REG32 drf_dll_auto_cnt_f2 : 10; // [29:20]
        REG32 __31_30 : 2;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DLL_CNT_F2_T;

//lpddr_drf_cfg_dll_mode_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dll_clk_mode_f3 : 1;  // [0]
        REG32 drf_dll_half_mode_f3 : 1; // [1]
        REG32 drf_dll_satu_mode_f3 : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DLL_MODE_F3_T;

//lpddr_drf_cfg_dll_cnt_f3
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_dll_init_cnt_f3 : 10; // [9:0]
        REG32 drf_dll_satu_cnt_f3 : 10; // [19:10]
        REG32 drf_dll_auto_cnt_f3 : 10; // [29:20]
        REG32 __31_30 : 2;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_CFG_DLL_CNT_F3_T;

//lpddr_drf_train_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 drf_phyupd_en : 1;       // [0]
        REG32 drf_phyupd_type_sel : 2; // [2:1]
        REG32 __3_3 : 1;
        REG32 drf_phyupd_type_0 : 2; // [5:4]
        REG32 drf_phyupd_type_1 : 2; // [7:6]
        REG32 drf_phyupd_type_2 : 2; // [9:8]
        REG32 drf_phyupd_type_3 : 2; // [11:10]
        REG32 drf_phy_wrlvl_en : 1;  // [12]
        REG32 drf_dmc_wrlvl_en : 1;  // [13]
        REG32 __15_14 : 2;
        REG32 drf_phy_rdlvl_en : 1; // [16]
        REG32 drf_dmc_rdlvl_en : 1; // [17]
        REG32 __19_18 : 2;
        REG32 drf_phy_rdlvl_gate_en : 1; // [20]
        REG32 drf_dmc_rdlvl_gate_en : 1; // [21]
        REG32 __31_22 : 10;
    } b;
} REG_LPDDR_PHY_LPDDR_DRF_TRAIN_CFG_T;

//lpddr_rf_irq_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_irq_en_dll_unlock_ac : 1;  // [0]
        REG32 rf_irq_en_dll_unlock_ds0 : 1; // [1]
        REG32 rf_irq_en_dll_unlock_ds1 : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_IRQ_CTRL_T;

//lpddr_rf_irq_status_clr
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_irq_st_clr_dll_unlock_ac : 1;  // [0]
        REG32 rf_irq_st_clr_dll_unlock_ds0 : 1; // [1]
        REG32 rf_irq_st_clr_dll_unlock_ds1 : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_IRQ_STATUS_CLR_T;

//lpddr_rf_irq_status
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_irq_st_dll_unlock_ac : 1;  // [0], read only
        REG32 rf_irq_st_dll_unlock_ds0 : 1; // [1], read only
        REG32 rf_irq_st_dll_unlock_ds1 : 1; // [2], read only
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_IRQ_STATUS_T;

//lpddr_rf_irq_cnt_clr
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_irq_cnt_clr_dll_unlock_ac : 1;  // [0]
        REG32 rf_irq_cnt_clr_dll_unlock_ds0 : 1; // [1]
        REG32 rf_irq_cnt_clr_dll_unlock_ds1 : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_LPDDR_RF_IRQ_CNT_CLR_T;

//lpddr_rf_irq_cnt_dll_unlock_ac
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_irq_cnt_dll_unlock_ac : 31;         // [30:0], read only
        REG32 rf_irq_cnt_overflow_dll_unlock_ac : 1; // [31], read only
    } b;
} REG_LPDDR_PHY_LPDDR_RF_IRQ_CNT_DLL_UNLOCK_AC_T;

//lpddr_rf_irq_cnt_dll_unlock_ds0
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_irq_cnt_dll_unlock_ds0 : 31;         // [30:0], read only
        REG32 rf_irq_cnt_overflow_dll_unlock_ds0 : 1; // [31], read only
    } b;
} REG_LPDDR_PHY_LPDDR_RF_IRQ_CNT_DLL_UNLOCK_DS0_T;

//lpddr_rf_irq_cnt_dll_unlock_ds1
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_irq_cnt_dll_unlock_ds1 : 31;         // [30:0], read only
        REG32 rf_irq_cnt_overflow_dll_unlock_ds1 : 1; // [31], read only
    } b;
} REG_LPDDR_PHY_LPDDR_RF_IRQ_CNT_DLL_UNLOCK_DS1_T;

//io_rf_ddr_rpull_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 ddr_dqs_rpull : 2; // [1:0]
        REG32 ddr_ck_rpull : 2;  // [3:2]
        REG32 __31_4 : 28;
    } b;
} REG_LPDDR_PHY_IO_RF_DDR_RPULL_CFG_T;

//io_rf_ddr_drv_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 ddr_drvpd : 5; // [4:0]
        REG32 ddr_drvpc : 5; // [9:5]
        REG32 ddr_drvnd : 5; // [14:10]
        REG32 ddr_drvnc : 5; // [19:15]
        REG32 __31_20 : 12;
    } b;
} REG_LPDDR_PHY_IO_RF_DDR_DRV_CFG_T;

//io_rf_ddr_pad_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 ddr_lp2d : 1; // [0]
        REG32 ddr_lp2c : 1; // [1]
        REG32 __31_2 : 30;
    } b;
} REG_LPDDR_PHY_IO_RF_DDR_PAD_CFG_T;

//io_rf_ddr_vref_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 ddr_vref_en_pad : 1; // [0]
        REG32 ddr_vref_en_int : 1; // [1]
        REG32 ddr_sel_pad : 6;     // [7:2]
        REG32 ddr_sel_int : 6;     // [13:8]
        REG32 __31_14 : 18;
    } b;
} REG_LPDDR_PHY_IO_RF_DDR_VREF_CFG_T;

//io_rf_ddr_zq_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 ddr_zprog : 5;      // [4:0]
        REG32 ddr_cal_zq_pd : 1;  // [5]
        REG32 ddr_cal_zq_cal : 1; // [6]
        REG32 __31_7 : 25;
    } b;
} REG_LPDDR_PHY_IO_RF_DDR_ZQ_CFG_T;

//io_rf_ddr_zq_mon
typedef union {
    REG32 v;
    struct
    {
        REG32 ddr_calover : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_LPDDR_PHY_IO_RF_DDR_ZQ_MON_T;

//io_rf_ddr_odt_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 ddr_odt_to_pad : 1;       // [0]
        REG32 ddr_odt_write_enable : 1; // [1]
        REG32 ddr_odt_read_enable : 1;  // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LPDDR_PHY_IO_RF_DDR_ODT_CFG_T;

//io_rf_psram_drv_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 psram_fix_read0 : 1; // [0]
        REG32 psram_slewrate : 2;  // [2:1]
        REG32 psram_drvp : 5;      // [7:3]
        REG32 psram_drvn : 5;      // [12:8]
        REG32 __31_13 : 19;
    } b;
} REG_LPDDR_PHY_IO_RF_PSRAM_DRV_CFG_T;

//io_rf_psram_pad_en_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 psram_pad_clkn_en : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_LPDDR_PHY_IO_RF_PSRAM_PAD_EN_CFG_T;

//io_rf_psram_pull_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 psram_dqs_pull0_bit : 2;  // [1:0]
        REG32 psram_dq_pull0_bit : 2;   // [3:2]
        REG32 psram_dm_pull1_bit : 2;   // [5:4]
        REG32 psram_clkn_pull1_bit : 2; // [7:6]
        REG32 psram_clk_pull0_bit : 2;  // [9:8]
        REG32 psram_cen_pull1_bit : 2;  // [11:10]
        REG32 __31_12 : 20;
    } b;
} REG_LPDDR_PHY_IO_RF_PSRAM_PULL_CFG_T;

#endif
