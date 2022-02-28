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

#ifndef _WCN_BT_MODEM_H_
#define _WCN_BT_MODEM_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'wcn_bt_modem'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// WCN_BT_MODEM_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_WCN_MODEM_BASE 0x15006000

typedef volatile struct
{
    REG32 bypass_ctrl;            //0x00000000
    REG32 sw_swap_dccal;          //0x00000004
    REG32 dem750_afc_freq;        //0x00000008
    REG32 dpsk_gfsk_tx_ctrl;      //0x0000000C
    REG32 tx_gain_ctrl;           //0x00000010
    REG32 rssi_out1;              //0x00000014
    REG32 sw_ctrl;                //0x00000018
    REG32 adcclk_sw_ctrl;         //0x0000001C
    REG32 dpsk_demod_sw;          //0x00000020
    REG32 min_phase_err;          //0x00000024
    REG32 afc_ctrl;               //0x00000028
    REG32 dpsk_gfsk_smp_th;       //0x0000002C
    REG32 dpsk_gfsk_smp_th_1;     //0x00000030
    REG32 gfsk_smp_ref_ctrl;      //0x00000034
    REG32 gfsk_smp_ref_ctrl_1;    //0x00000038
    REG32 rateconv_ctrl1;         //0x0000003C
    REG32 rateconv_ctrl2;         //0x00000040
    REG32 demod_smp_ctrl;         //0x00000044
    REG32 agc_ctrl;               //0x00000048
    REG32 agc_th_ctrl1;           //0x0000004C
    REG32 agc_th_ctrl2;           //0x00000050
    REG32 agc_ctrl1;              //0x00000054
    REG32 agc_ctrl2;              //0x00000058
    REG32 agc_dgc_ctrl;           //0x0000005C
    REG32 agc_dccal_ctrl;         //0x00000060
    REG32 rx_dccal_ctrl;          //0x00000064
    REG32 rx_dcofst_inuse;        //0x00000068
    REG32 tx_dc_calib;            //0x0000006C
    REG32 tx_fix_i_dcofst;        //0x00000070
    REG32 tx_fix_q_dcofst;        //0x00000074
    REG32 tx_i_dcofst_inuse;      //0x00000078
    REG32 tx_q_dcofst_inuse;      //0x0000007C
    REG32 rssi_gain_ctrl1;        //0x00000080
    REG32 rssi_gain_ctrl2;        //0x00000084
    REG32 rssi_gain_ctrl3;        //0x00000088
    REG32 rssi_gain_ctrl4;        //0x0000008C
    REG32 rssi_gain_ctrl5;        //0x00000090
    REG32 rssi_gain_ctrl6;        //0x00000094
    REG32 rssi_gain_ctrl7;        //0x00000098
    REG32 rssi_gain_ctrl8;        //0x0000009C
    REG32 modem_tpd_sel;          //0x000000A0
    REG32 demod_smp_th_ctrl;      //0x000000A4
    REG32 newpacket_byte4;        //0x000000A8
    REG32 newpacket_byte3;        //0x000000AC
    REG32 newpacket_byte2;        //0x000000B0
    REG32 newpacket_byte1;        //0x000000B4
    REG32 gfsk_mod_ctrl;          //0x000000B8
    REG32 gfsk_mod_ref_ctrl;      //0x000000BC
    REG32 sym_dly_ctrl;           //0x000000C0
    REG32 rssi_out2;              //0x000000C4
    REG32 trx_clk_ctrl;           //0x000000C8
    REG32 iq_swap_ctrl;           //0x000000CC
    REG32 gfsk_sync_ctrl;         //0x000000D0
    REG32 gfsk_demod_ctrl;        //0x000000D4
    REG32 gfsk_mod_idx;           //0x000000D8
    REG32 dpsk_gfsk_misc_ctrl;    //0x000000DC
    REG32 modem_dbm_sel;          //0x000000E0
    REG32 gfsk_mod_idx_le;        //0x000000E4
    REG32 newpacket_byte4_inuse;  //0x000000E8
    REG32 newpacket_byte3_inuse;  //0x000000EC
    REG32 newpacket_byte2_inuse;  //0x000000F0
    REG32 newpacket_byte1_inuse;  //0x000000F4
    REG32 le_mode_ctrl1;          //0x000000F8
    REG32 le_mode_ctrl2;          //0x000000FC
    REG32 le_mode_ctrl3;          //0x00000100
    REG32 le_mode_ctrl4;          //0x00000104
    REG32 le_mode_ctrl5;          //0x00000108
    REG32 rf_ctrl;                //0x0000010C
    REG32 tx_q_im;                //0x00000110
    REG32 tx_i_im;                //0x00000114
    REG32 tx_am_p0;               //0x00000118
    REG32 tx_am_p1;               //0x0000011C
    REG32 tx_am_p2;               //0x00000120
    REG32 tx_am_p3;               //0x00000124
    REG32 tx_am_p4;               //0x00000128
    REG32 tx_am_p5;               //0x0000012C
    REG32 tx_am_p6;               //0x00000130
    REG32 tx_am_p7;               //0x00000134
    REG32 tx_am_p8;               //0x00000138
    REG32 tx_am_p9;               //0x0000013C
    REG32 tx_am_p10;              //0x00000140
    REG32 tx_am_p11;              //0x00000144
    REG32 tx_am_p12;              //0x00000148
    REG32 tx_am_p13;              //0x0000014C
    REG32 tx_am_p14;              //0x00000150
    REG32 tx_am_p15;              //0x00000154
    REG32 tx_am_p16;              //0x00000158
    REG32 tx_pm_p0;               //0x0000015C
    REG32 tx_pm_p1;               //0x00000160
    REG32 tx_pm_p2;               //0x00000164
    REG32 tx_pm_p3;               //0x00000168
    REG32 tx_pm_p4;               //0x0000016C
    REG32 tx_pm_p5;               //0x00000170
    REG32 tx_pm_p6;               //0x00000174
    REG32 tx_pm_p7;               //0x00000178
    REG32 tx_pm_p8;               //0x0000017C
    REG32 tx_pm_p9;               //0x00000180
    REG32 tx_pm_p10;              //0x00000184
    REG32 tx_pm_p11;              //0x00000188
    REG32 tx_pm_p12;              //0x0000018C
    REG32 tx_pm_p13;              //0x00000190
    REG32 tx_pm_p14;              //0x00000194
    REG32 tx_pm_p15;              //0x00000198
    REG32 tx_pm_p16;              //0x0000019C
    REG32 notch_coef;             //0x000001A0
    REG32 adapt_edr3_demod;       //0x000001A4
    REG32 adapt_edr3_thresh;      //0x000001A8
    REG32 tx_auto_gain1_gfsk;     //0x000001AC
    REG32 tx_auto_gain0_gfsk;     //0x000001B0
    REG32 tx_auto_gain1_gfsk_edr; //0x000001B4
    REG32 tx_auto_gain0_gfsk_edr; //0x000001B8
    REG32 tx_auto_gain1_dpsk;     //0x000001BC
    REG32 tx_auto_gain0_dpsk;     //0x000001C0
    REG32 gfsk_mod_eql_gain;      //0x000001C4
    REG32 tx_lfp_delay_ctrl;      //0x000001C8
    REG32 tx_hfp_delay;           //0x000001CC
    REG32 tx_polar_mode_ctl;      //0x000001D0
    REG32 tx_apf_num_b1;          //0x000001D4
    REG32 tx_apf_num_b2;          //0x000001D8
    REG32 tx_apf_num_b3;          //0x000001DC
    REG32 tx_apf_num_b4;          //0x000001E0
    REG32 tx_apf_den_a2;          //0x000001E4
    REG32 tx_apf_den_a3;          //0x000001E8
    REG32 tx_apf_den_a4;          //0x000001EC
    REG32 adapt_edr3_cci;         //0x000001F0
} HWP_WCN_BT_MODEM_T;

#define hwp_wcnModem ((HWP_WCN_BT_MODEM_T *)REG_ACCESS_ADDRESS(REG_WCN_MODEM_BASE))

//bypass_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 bypass_smppt_dpsk : 1; // [1]
        REG32 bypass_patch_dpsk : 1; // [2]
        REG32 bypass_derr2_dpsk : 1; // [3]
        REG32 bypass_derr1_dpsk : 1; // [4]
        REG32 bypass_smppt_gfsk : 1; // [5]
        REG32 bypass_patch_gfsk : 1; // [6]
        REG32 bypass_derr2_gfsk : 1; // [7]
        REG32 bypass_derr1_gfsk : 1; // [8]
        REG32 __11_9 : 3;
        REG32 bypass_srrc : 1;      // [12]
        REG32 bypass_mixer : 1;     // [13]
        REG32 bypass_dccancel2 : 1; // [14]
        REG32 bypass_dccancel : 1;  // [15]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_BYPASS_CTRL_T;

//sw_swap_dccal
typedef union {
    REG32 v;
    struct
    {
        REG32 sel_sumerr_range : 3; // [2:0]
        REG32 __4_3 : 2;
        REG32 iq_sel_pol : 1;     // [5]
        REG32 swch_sign_rx : 1;   // [6]
        REG32 swch_sign_q_tx : 1; // [7]
        REG32 swch_sign_i_tx : 1; // [8]
        REG32 lpf_dwidth_sel : 2; // [10:9]
        REG32 rsvd0 : 1;          // [11]
        REG32 swch_clk_dac : 1;   // [12]
        REG32 sel_sync : 1;       // [13]
        REG32 swch_clk_adc : 1;   // [14]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_SW_SWAP_DCCAL_T;

//dem750_afc_freq
typedef union {
    REG32 v;
    struct
    {
        REG32 afc_smtif : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_DEM750_AFC_FREQ_T;

//dpsk_gfsk_tx_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 delay_dpsk : 4;   // [3:0]
        REG32 delay_gfsk : 4;   // [7:4]
        REG32 tx_gain_dpsk : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_DPSK_GFSK_TX_CTRL_T;

//tx_gain_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_gain_gfsk : 8;        // [7:0]
        REG32 tx_auto_gain_bypass : 1; // [8]
        REG32 tx_power_gain_sel : 1;   // [9]
        REG32 cnt_guard_ini : 6;       // [15:10]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_TX_GAIN_CTRL_T;

//rssi_out1
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_out_pre : 10; // [9:0], read only
        REG32 __15_10 : 6;
        REG32 rssi_out_post : 10; // [25:16], read only
        REG32 __31_26 : 6;
    } b;
} REG_WCN_BT_MODEM_RSSI_OUT1_T;

//sw_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_gain_gfsk_edr : 8;      // [7:0]
        REG32 notch_disb : 1;            // [8]
        REG32 swap_pn_q_dccl_0 : 1;      // [9]
        REG32 swap_pn_i_dccl_0 : 1;      // [10]
        REG32 swap_iq_mixer_0 : 1;       // [11]
        REG32 swap_iq_smtif_0 : 1;       // [12]
        REG32 swap_iq_dccl_0 : 1;        // [13]
        REG32 swap_iq : 1;               // [14]
        REG32 rssi_lock_by_agc_pre : 1;  // [15]
        REG32 rssi_lock_by_agc_post : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_BT_MODEM_SW_CTRL_T;

//adcclk_sw_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 ct_u_sp_gfsk : 4; // [3:0]
        REG32 ct_u_1_gfsk : 5;  // [8:4]
        REG32 ct_u_gfsk : 4;    // [12:9]
        REG32 pckt_sel : 1;     // [13]
        REG32 en_bbpkg_flg : 1; // [14]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_ADCCLK_SW_CTRL_T;

//dpsk_demod_sw
typedef union {
    REG32 v;
    struct
    {
        REG32 ct_u_sp_dpsk : 4; // [3:0]
        REG32 ct_u_1_dpsk : 5;  // [8:4]
        REG32 ct_u_dpsk : 4;    // [12:9]
        REG32 ct_u_patch : 3;   // [15:13]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_DPSK_DEMOD_SW_T;

//min_phase_err
typedef union {
    REG32 v;
    struct
    {
        REG32 min_error_th : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_MIN_PHASE_ERR_T;

//afc_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 th_gfsk_dem : 10;     // [9:0]
        REG32 rsvd1 : 2;            // [11:10]
        REG32 sel_afc_dpskseek : 2; // [13:12]
        REG32 sel_afc_gfskdem : 2;  // [15:14]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_AFC_CTRL_T;

//dpsk_gfsk_smp_th
typedef union {
    REG32 v;
    struct
    {
        REG32 th_gfsk_dem2 : 10;    // [9:0]
        REG32 sp_th_sel_gfsk : 2;   // [11:10]
        REG32 sp_th_sel_dpsk : 2;   // [13:12]
        REG32 diff_enable_gfsk : 1; // [14]
        REG32 diff_enable_dpsk : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_DPSK_GFSK_SMP_TH_T;

//dpsk_gfsk_smp_th_1
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_a2_sek : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_DPSK_GFSK_SMP_TH_1_T;

//gfsk_smp_ref_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_a3_sek : 8; // [7:0]
        REG32 ref_a1_sek : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_GFSK_SMP_REF_CTRL_T;

//gfsk_smp_ref_ctrl_1
typedef union {
    REG32 v;
    struct
    {
        REG32 dc_ct2 : 9;          // [8:0]
        REG32 guard_time_conf : 5; // [13:9]
        REG32 rsvd2 : 2;           // [15:14]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_GFSK_SMP_REF_CTRL_1_T;

//rateconv_ctrl1
typedef union {
    REG32 v;
    struct
    {
        REG32 dac_data_sel : 6; // [5:0]
        REG32 dac_test_en : 1;  // [6]
        REG32 dc_ct : 9;        // [15:7]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RATECONV_CTRL1_T;

//rateconv_ctrl2
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_tm_th_pre : 6;    // [5:0]
        REG32 dc_hold_edr_en : 1;    // [6]
        REG32 rssi_tm_th_post : 6;   // [12:7]
        REG32 rssi_sel : 2;          // [14:13]
        REG32 sel_rssi_src_pre : 1;  // [15]
        REG32 sel_rssi_src_post : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_BT_MODEM_RATECONV_CTRL2_T;

//demod_smp_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 cnt_sample_ini : 4; // [3:0]
        REG32 ref_ready_th : 6;   // [9:4]
        REG32 ini_rst_th : 6;     // [15:10]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_DEMOD_SMP_CTRL_T;

//agc_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 agc_sinc_over_th : 2; // [1:0]
        REG32 agc_sinc_over_en : 1; // [2]
        REG32 agc_mod_fix7 : 1;     // [3]
        REG32 agc_en_fix7 : 1;      // [4]
        REG32 dpsk_seek_st_cnt : 5; // [9:5]
        REG32 mix_guard_th : 6;     // [15:10]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_AGC_CTRL_T;

//agc_th_ctrl1
typedef union {
    REG32 v;
    struct
    {
        REG32 agc_th_min : 8; // [7:0]
        REG32 agc_th_max : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_AGC_TH_CTRL1_T;

//agc_th_ctrl2
typedef union {
    REG32 v;
    struct
    {
        REG32 agc_th_min_lg : 8; // [7:0]
        REG32 agc_th_max_lg : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_AGC_TH_CTRL2_T;

//agc_ctrl1
typedef union {
    REG32 v;
    struct
    {
        REG32 agc_mod_dem : 2;       // [1:0]
        REG32 agc_index_ini_dsp : 4; // [5:2]
        REG32 agc_en_dly : 3;        // [8:6]
        REG32 agc_step_over : 2;     // [10:9]
        REG32 agc_step_mode : 2;     // [12:11]
        REG32 agc_en_lg_stp : 1;     // [13]
        REG32 agc_ct_th_min : 1;     // [14]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_AGC_CTRL1_T;

//agc_ctrl2
typedef union {
    REG32 v;
    struct
    {
        REG32 agc_tm_intv_lg : 7; // [6:0]
        REG32 agc_tm_intv : 7;    // [13:7]
        REG32 agc_th_min_gn : 2;  // [15:14]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_AGC_CTRL2_T;

//agc_dgc_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 agc_mode_dsp : 3; // [2:0]
        REG32 __5_3 : 3;
        REG32 newpacket_zero_wd_cnt : 2; // [7:6]
        REG32 pass_newpacket_sel : 1;    // [8]
        REG32 dgc_index_max : 3;         // [11:9]
        REG32 dgc_index_dsp : 3;         // [14:12]
        REG32 sel_reg_agc : 1;           // [15]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_AGC_DGC_CTRL_T;

//agc_dccal_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_fix_dcofst : 1;  // [0]
        REG32 dc_cal_rx_dly : 2;  // [2:1]
        REG32 rx_dc_cal_done : 1; // [3], read only
        REG32 __5_4 : 2;
        REG32 agc_tm_hold : 5; // [10:6]
        REG32 agc_tm_wait : 5; // [15:11]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_AGC_DCCAL_CTRL_T;

//rx_dccal_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_dc_cali_q_fix : 10; // [9:0]
        REG32 __15_10 : 6;
        REG32 rx_dc_cali_i_fix : 10; // [25:16]
        REG32 __31_26 : 6;
    } b;
} REG_WCN_BT_MODEM_RX_DCCAL_CTRL_T;

//rx_dcofst_inuse
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_dcoffset_q : 10; // [9:0], read only
        REG32 __15_10 : 6;
        REG32 rx_dcoffset_i : 10; // [25:16], read only
        REG32 __31_26 : 6;
    } b;
} REG_WCN_BT_MODEM_RX_DCOFST_INUSE_T;

//tx_dc_calib
typedef union {
    REG32 v;
    struct
    {
        REG32 bypass_tx_cal : 1;  // [0]
        REG32 tx_apc : 3;         // [3:1]
        REG32 tx_cal_shift : 2;   // [5:4]
        REG32 tx_cal_sel : 2;     // [7:6]
        REG32 tx_cal_pol : 1;     // [8]
        REG32 tx_cal_cmp_pol : 1; // [9]
        REG32 tx_cal_cnt : 2;     // [11:10]
        REG32 tx_fix_dcofst : 1;  // [12]
        REG32 tx_cal_out_q : 1;   // [13], read only
        REG32 tx_cal_out_i : 1;   // [14], read only
        REG32 tx_dc_cal_done : 1; // [15], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_TX_DC_CALIB_T;

//tx_fix_i_dcofst
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_dc_idata_fix : 12; // [11:0]
        REG32 __31_12 : 20;
    } b;
} REG_WCN_BT_MODEM_TX_FIX_I_DCOFST_T;

//tx_fix_q_dcofst
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_dc_qdata_fix : 12; // [11:0]
        REG32 __31_12 : 20;
    } b;
} REG_WCN_BT_MODEM_TX_FIX_Q_DCOFST_T;

//tx_i_dcofst_inuse
typedef union {
    REG32 v;
    struct
    {
        REG32 dc_cal_tx_idata : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_WCN_BT_MODEM_TX_I_DCOFST_INUSE_T;

//tx_q_dcofst_inuse
typedef union {
    REG32 v;
    struct
    {
        REG32 dc_cal_tx_qdata : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_WCN_BT_MODEM_TX_Q_DCOFST_INUSE_T;

//rssi_gain_ctrl1
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_ana_gain0001 : 8; // [7:0]
        REG32 rssi_ana_gain0000 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RSSI_GAIN_CTRL1_T;

//rssi_gain_ctrl2
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_ana_gain0011 : 8; // [7:0]
        REG32 rssi_ana_gain0010 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RSSI_GAIN_CTRL2_T;

//rssi_gain_ctrl3
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_ana_gain0101 : 8; // [7:0]
        REG32 rssi_ana_gain0100 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RSSI_GAIN_CTRL3_T;

//rssi_gain_ctrl4
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_ana_gain0111 : 8; // [7:0]
        REG32 rssi_ana_gain0110 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RSSI_GAIN_CTRL4_T;

//rssi_gain_ctrl5
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_ana_gain1001 : 8; // [7:0]
        REG32 rssi_ana_gain1000 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RSSI_GAIN_CTRL5_T;

//rssi_gain_ctrl6
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_ana_gain1011 : 8; // [7:0]
        REG32 rssi_ana_gain1010 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RSSI_GAIN_CTRL6_T;

//rssi_gain_ctrl7
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_ana_gain1101 : 8; // [7:0]
        REG32 rssi_ana_gain1100 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RSSI_GAIN_CTRL7_T;

//rssi_gain_ctrl8
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_ana_gain1111 : 8; // [7:0]
        REG32 rssi_ana_gain1110 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_RSSI_GAIN_CTRL8_T;

//modem_tpd_sel
typedef union {
    REG32 v;
    struct
    {
        REG32 tpd_trig_sel : 4;     // [3:0]
        REG32 tpd_data_sel : 4;     // [7:4]
        REG32 tpd_clk_sel : 1;      // [8]
        REG32 dac_clk_force_en : 1; // [9]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_MODEM_TPD_SEL_T;

//demod_smp_th_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 dem_sp_th1 : 8; // [7:0]
        REG32 dem_sp_th2 : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_DEMOD_SMP_TH_CTRL_T;

//newpacket_byte4
typedef union {
    REG32 v;
    struct
    {
        REG32 newpacket_4 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_NEWPACKET_BYTE4_T;

//newpacket_byte3
typedef union {
    REG32 v;
    struct
    {
        REG32 newpacket_3 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_NEWPACKET_BYTE3_T;

//newpacket_byte2
typedef union {
    REG32 v;
    struct
    {
        REG32 newpacket_2 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_NEWPACKET_BYTE2_T;

//newpacket_byte1
typedef union {
    REG32 v;
    struct
    {
        REG32 newpacket_1 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_NEWPACKET_BYTE1_T;

//gfsk_mod_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_a2_dem : 10; // [9:0]
        REG32 __11_10 : 2;
        REG32 rssi_ct_u_pre : 3;  // [14:12]
        REG32 bt_mod : 1;         // [15]
        REG32 rssi_ct_u_post : 3; // [18:16]
        REG32 __31_19 : 13;
    } b;
} REG_WCN_BT_MODEM_GFSK_MOD_CTRL_T;

//gfsk_mod_ref_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_a3_dem : 8; // [7:0]
        REG32 ref_a1_dem : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_GFSK_MOD_REF_CTRL_T;

//sym_dly_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 delay_gfsk_1m : 3;     // [2:0]
        REG32 delay_dpsk_1m : 3;     // [5:3]
        REG32 delay_gfsk_off_1m : 3; // [8:6]
        REG32 delay_gfsk_off : 4;    // [12:9]
        REG32 ramp_speed_gfsk : 1;   // [13]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_SYM_DLY_CTRL_T;

//rssi_out2
typedef union {
    REG32 v;
    struct
    {
        REG32 rssi_noise_out_pre : 10; // [9:0], read only
        REG32 __15_10 : 6;
        REG32 rssi_noise_out_post : 10; // [25:16], read only
        REG32 __31_26 : 6;
    } b;
} REG_WCN_BT_MODEM_RSSI_OUT2_T;

//trx_clk_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 __5_0 : 6;
        REG32 apc_switch_mode : 4; // [9:6]
        REG32 __11_10 : 2;
        REG32 tx_rx_reg : 1;       // [12]
        REG32 tx_rx_dir : 1;       // [13]
        REG32 swch_clk_52m_rx : 1; // [14]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_TRX_CLK_CTRL_T;

//iq_swap_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 notch_en_0 : 1;     // [0]
        REG32 rate_conv_en_0 : 1; // [1]
        REG32 lpf_en_0 : 1;       // [2]
        REG32 __3_3 : 1;
        REG32 notch_en_1 : 1;     // [4]
        REG32 rate_conv_en_1 : 1; // [5]
        REG32 lpf_en_1 : 1;       // [6]
        REG32 __11_7 : 5;
        REG32 iq_swap_srrc : 1;    // [12]
        REG32 iq_swap_lpf : 1;     // [13]
        REG32 iq_swap_gain2 : 1;   // [14]
        REG32 swch_clk_52m_tx : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_IQ_SWAP_CTRL_T;

//gfsk_sync_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 dynamic_sync_th : 10; // [9:0]
        REG32 dynamic_sync_en : 1;  // [10]
        REG32 __31_11 : 21;
    } b;
} REG_WCN_BT_MODEM_GFSK_SYNC_CTRL_T;

//gfsk_demod_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 min_error_th2 : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_GFSK_DEMOD_CTRL_T;

//gfsk_mod_idx
typedef union {
    REG32 v;
    struct
    {
        REG32 h_gain : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_GFSK_MOD_IDX_T;

//dpsk_gfsk_misc_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 __2_0 : 3;
        REG32 dly_ct_amp : 3;  // [5:3]
        REG32 dly_ct_dpsk : 3; // [8:6]
        REG32 dly_ct_gfsk : 3; // [11:9]
        REG32 __14_12 : 3;
        REG32 iq_swap_tx : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_DPSK_GFSK_MISC_CTRL_T;

//modem_dbm_sel
typedef union {
    REG32 v;
    struct
    {
        REG32 dbm_data_sel : 5; // [4:0]
        REG32 __31_5 : 27;
    } b;
} REG_WCN_BT_MODEM_MODEM_DBM_SEL_T;

//gfsk_mod_idx_le
typedef union {
    REG32 v;
    struct
    {
        REG32 h_gain_le : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_GFSK_MOD_IDX_LE_T;

//newpacket_byte4_inuse
typedef union {
    REG32 v;
    struct
    {
        REG32 newpacket_dsp4 : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_NEWPACKET_BYTE4_INUSE_T;

//newpacket_byte3_inuse
typedef union {
    REG32 v;
    struct
    {
        REG32 newpacket_dsp3 : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_NEWPACKET_BYTE3_INUSE_T;

//newpacket_byte2_inuse
typedef union {
    REG32 v;
    struct
    {
        REG32 newpacket_dsp2 : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_NEWPACKET_BYTE2_INUSE_T;

//newpacket_byte1_inuse
typedef union {
    REG32 v;
    struct
    {
        REG32 newpacket_dsp1 : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_NEWPACKET_BYTE1_INUSE_T;

//le_mode_ctrl1
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_a1_dem_le : 8; // [7:0]
        REG32 ref_a1_sek_le : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_LE_MODE_CTRL1_T;

//le_mode_ctrl2
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_a2_dem_le : 8; // [7:0]
        REG32 ref_a2_sek_le : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_LE_MODE_CTRL2_T;

//le_mode_ctrl3
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_a3_dem_le : 8; // [7:0]
        REG32 ref_a3_sek_le : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_LE_MODE_CTRL3_T;

//le_mode_ctrl4
typedef union {
    REG32 v;
    struct
    {
        REG32 min_error_th_le : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_LE_MODE_CTRL4_T;

//le_mode_ctrl5
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_ready_th_le : 6;  // [5:0]
        REG32 mix_guard_th_le : 6;  // [11:6]
        REG32 ref_point_sel_le : 2; // [13:12]
        REG32 rsvd5 : 2;            // [15:14]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_LE_MODE_CTRL5_T;

//rf_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 sync_shift_mode : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_WCN_BT_MODEM_RF_CTRL_T;

//tx_q_im
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_iqim_phase_err : 15; // [14:0]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_TX_Q_IM_T;

//tx_i_im
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_iqim_amp_err : 15; // [14:0]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_TX_I_IM_T;

//tx_am_p0
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p0 : 10;         // [9:0]
        REG32 am_comp_bypass : 1; // [10]
        REG32 pm_comp_bypass : 1; // [11]
        REG32 pm_shift : 3;       // [14:12]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P0_T;

//tx_am_p1
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p1 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P1_T;

//tx_am_p2
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p2 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P2_T;

//tx_am_p3
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p3 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P3_T;

//tx_am_p4
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p4 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P4_T;

//tx_am_p5
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p5 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P5_T;

//tx_am_p6
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p6 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P6_T;

//tx_am_p7
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p7 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P7_T;

//tx_am_p8
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p8 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P8_T;

//tx_am_p9
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p9 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P9_T;

//tx_am_p10
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p10 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P10_T;

//tx_am_p11
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p11 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P11_T;

//tx_am_p12
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p12 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P12_T;

//tx_am_p13
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p13 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P13_T;

//tx_am_p14
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p14 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P14_T;

//tx_am_p15
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p15 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P15_T;

//tx_am_p16
typedef union {
    REG32 v;
    struct
    {
        REG32 am_p16 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_AM_P16_T;

//tx_pm_p0
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p0 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P0_T;

//tx_pm_p1
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p1 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P1_T;

//tx_pm_p2
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p2 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P2_T;

//tx_pm_p3
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p3 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P3_T;

//tx_pm_p4
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p4 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P4_T;

//tx_pm_p5
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p5 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P5_T;

//tx_pm_p6
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p6 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P6_T;

//tx_pm_p7
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p7 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P7_T;

//tx_pm_p8
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p8 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P8_T;

//tx_pm_p9
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p9 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P9_T;

//tx_pm_p10
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p10 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P10_T;

//tx_pm_p11
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p11 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P11_T;

//tx_pm_p12
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p12 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P12_T;

//tx_pm_p13
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p13 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P13_T;

//tx_pm_p14
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p14 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P14_T;

//tx_pm_p15
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p15 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P15_T;

//tx_pm_p16
typedef union {
    REG32 v;
    struct
    {
        REG32 pm_p16 : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_MODEM_TX_PM_P16_T;

//notch_coef
typedef union {
    REG32 v;
    struct
    {
        REG32 notch_b : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_NOTCH_COEF_T;

//adapt_edr3_demod
typedef union {
    REG32 v;
    struct
    {
        REG32 ct_u_1_dpsk1 : 5;  // [4:0]
        REG32 ct_u_dpsk1 : 4;    // [8:5]
        REG32 edr3_adapt_en : 1; // [9]
        REG32 __11_10 : 2;
        REG32 notch_a : 4; // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_ADAPT_EDR3_DEMOD_T;

//adapt_edr3_thresh
typedef union {
    REG32 v;
    struct
    {
        REG32 edr3_adapt_th : 12; // [11:0]
        REG32 __31_12 : 20;
    } b;
} REG_WCN_BT_MODEM_ADAPT_EDR3_THRESH_T;

//tx_auto_gain1_gfsk
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_auto_gain_gfsk4 : 4; // [3:0]
        REG32 tx_auto_gain_gfsk5 : 4; // [7:4]
        REG32 tx_auto_gain_gfsk6 : 4; // [11:8]
        REG32 tx_auto_gain_gfsk7 : 4; // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_TX_AUTO_GAIN1_GFSK_T;

//tx_auto_gain0_gfsk
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_auto_gain_gfsk0 : 4; // [3:0]
        REG32 tx_auto_gain_gfsk1 : 4; // [7:4]
        REG32 tx_auto_gain_gfsk2 : 4; // [11:8]
        REG32 tx_auto_gain_gfsk3 : 4; // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_TX_AUTO_GAIN0_GFSK_T;

//tx_auto_gain1_gfsk_edr
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_auto_gain_gfsk_edr4 : 4; // [3:0]
        REG32 tx_auto_gain_gfsk_edr5 : 4; // [7:4]
        REG32 tx_auto_gain_gfsk_edr6 : 4; // [11:8]
        REG32 tx_auto_gain_gfsk_edr7 : 4; // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_TX_AUTO_GAIN1_GFSK_EDR_T;

//tx_auto_gain0_gfsk_edr
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_auto_gain_gfsk_edr0 : 4; // [3:0]
        REG32 tx_auto_gain_gfsk_edr1 : 4; // [7:4]
        REG32 tx_auto_gain_gfsk_edr2 : 4; // [11:8]
        REG32 tx_auto_gain_gfsk_edr3 : 4; // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_TX_AUTO_GAIN0_GFSK_EDR_T;

//tx_auto_gain1_dpsk
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_auto_gain_dpsk4 : 4; // [3:0]
        REG32 tx_auto_gain_dpsk5 : 4; // [7:4]
        REG32 tx_auto_gain_dpsk6 : 4; // [11:8]
        REG32 tx_auto_gain_dpsk7 : 4; // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_TX_AUTO_GAIN1_DPSK_T;

//tx_auto_gain0_dpsk
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_auto_gain_dpsk0 : 4; // [3:0]
        REG32 tx_auto_gain_dpsk1 : 4; // [7:4]
        REG32 tx_auto_gain_dpsk2 : 4; // [11:8]
        REG32 tx_auto_gain_dpsk3 : 4; // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_TX_AUTO_GAIN0_DPSK_T;

//gfsk_mod_eql_gain
typedef union {
    REG32 v;
    struct
    {
        REG32 equ_g_gfsk : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_GFSK_MOD_EQL_GAIN_T;

//tx_lfp_delay_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 lpfil_freq_tx_bw_ct : 5;  // [4:0]
        REG32 lpfil_freq_tx_enable : 1; // [5]
        REG32 lpfil_freq_tx_bypass : 1; // [6]
        REG32 __7_7 : 1;
        REG32 dly_ct_freq1 : 3; // [10:8]
        REG32 __11_11 : 1;
        REG32 dly_ct_freq2 : 3; // [14:12]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_TX_LFP_DELAY_CTRL_T;

//tx_hfp_delay
typedef union {
    REG32 v;
    struct
    {
        REG32 dly_ct_freq_high : 3; // [2:0]
        REG32 __3_3 : 1;
        REG32 dly_ct_iq2 : 3; // [6:4]
        REG32 __7_7 : 1;
        REG32 dly_ct_iq1 : 3; // [10:8]
        REG32 __11_11 : 1;
        REG32 dly_sel_freq : 3; // [14:12]
        REG32 __31_15 : 17;
    } b;
} REG_WCN_BT_MODEM_TX_HFP_DELAY_T;

//tx_polar_mode_ctl
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_apf_bypass : 1;     // [0]
        REG32 tx_polar_mode_sel : 1; // [1]
        REG32 tx_tmp_dly : 3;        // [4:2]
        REG32 __31_5 : 27;
    } b;
} REG_WCN_BT_MODEM_TX_POLAR_MODE_CTL_T;

//tx_apf_num_b1
typedef union {
    REG32 v;
    struct
    {
        REG32 num_coe_b1 : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_TX_APF_NUM_B1_T;

//tx_apf_num_b2
typedef union {
    REG32 v;
    struct
    {
        REG32 num_coe_b2 : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_TX_APF_NUM_B2_T;

//tx_apf_num_b3
typedef union {
    REG32 v;
    struct
    {
        REG32 num_coe_b3 : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_TX_APF_NUM_B3_T;

//tx_apf_num_b4
typedef union {
    REG32 v;
    struct
    {
        REG32 num_coe_b4 : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_TX_APF_NUM_B4_T;

//tx_apf_den_a2
typedef union {
    REG32 v;
    struct
    {
        REG32 den_coe_a2 : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_TX_APF_DEN_A2_T;

//tx_apf_den_a3
typedef union {
    REG32 v;
    struct
    {
        REG32 den_coe_a3 : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_TX_APF_DEN_A3_T;

//tx_apf_den_a4
typedef union {
    REG32 v;
    struct
    {
        REG32 den_coe_a4 : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_BT_MODEM_TX_APF_DEN_A4_T;

//adapt_edr3_cci
typedef union {
    REG32 v;
    struct
    {
        REG32 ct_u_1_dpsk2 : 5; // [4:0]
        REG32 ct_u_dpsk2 : 4;   // [8:5]
        REG32 __12_9 : 4;
        REG32 ct_u_errsum : 3; // [15:13]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_MODEM_ADAPT_EDR3_CCI_T;

#endif
