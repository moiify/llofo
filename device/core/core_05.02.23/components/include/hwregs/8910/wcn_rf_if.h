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

#ifndef _WCN_RF_IF_H_
#define _WCN_RF_IF_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'wcn_rf_if'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// WCN_RF_IF_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_WCN_RF_IF_BASE 0x15005000

typedef volatile struct
{
    REG32 revision;              //0x00000000
    REG32 sys_control;           //0x00000004
    REG32 bt_control;            //0x00000008
    REG32 wf_control;            //0x0000000C
    REG32 fm_control;            //0x00000010
    REG32 inter_freq_setting;    //0x00000014
    REG32 bandgap_setting;       //0x00000018
    REG32 lna_rmx_setting;       //0x0000001C
    REG32 pga_setting0;          //0x00000020
    REG32 pga_setting1;          //0x00000024
    REG32 rxflt_setting;         //0x00000028
    REG32 adc_setting0;          //0x0000002C
    REG32 adc_setting1;          //0x00000030
    REG32 bt_dac_setting;        //0x00000034
    REG32 bt_txrf_setting;       //0x00000038
    REG32 fm_dsp_setting;        //0x0000003C
    REG32 vco_setting;           //0x00000040
    REG32 pll_setting0;          //0x00000044
    REG32 pll_setting1;          //0x00000048
    REG32 pll_setting2;          //0x0000004C
    REG32 pll_status;            //0x00000050
    REG32 adpll_setting0;        //0x00000054
    REG32 adpll_setting1;        //0x00000058
    REG32 adpll_status;          //0x0000005C
    REG32 mdll_setting;          //0x00000060
    REG32 pll_sdm_setting0;      //0x00000064
    REG32 pll_sdm_setting1;      //0x00000068
    REG32 adpll_sdm_setting0;    //0x0000006C
    REG32 adpll_sdm_setting1;    //0x00000070
    REG32 adpll_sdm_setting2;    //0x00000074
    REG32 rxflt_cal_setting0;    //0x00000078
    REG32 rxflt_cal_setting1;    //0x0000007C
    REG32 rxflt_cal_setting2;    //0x00000080
    REG32 rxflt_cal_setting3;    //0x00000084
    REG32 vco_pkd_cal_setting;   //0x00000088
    REG32 pll_cal_setting0;      //0x0000008C
    REG32 pll_cal_setting1;      //0x00000090
    REG32 adc_cal_setting;       //0x00000094
    REG32 cal_dr_setting;        //0x00000098
    REG32 cal_status;            //0x0000009C
    REG32 cal_results0;          //0x000000A0
    REG32 cal_results1;          //0x000000A4
    REG32 power_dr;              //0x000000A8
    REG32 power_reg;             //0x000000AC
    REG32 power_status;          //0x000000B0
    REG32 bt_gain_table_0;       //0x000000B4
    REG32 bt_gain_table_1;       //0x000000B8
    REG32 bt_gain_table_2;       //0x000000BC
    REG32 bt_gain_table_3;       //0x000000C0
    REG32 bt_gain_table_4;       //0x000000C4
    REG32 bt_gain_table_5;       //0x000000C8
    REG32 bt_gain_table_6;       //0x000000CC
    REG32 bt_gain_table_7;       //0x000000D0
    REG32 bt_gain_table_8;       //0x000000D4
    REG32 bt_gain_table_9;       //0x000000D8
    REG32 bt_gain_table_a;       //0x000000DC
    REG32 bt_gain_table_b;       //0x000000E0
    REG32 bt_gain_table_c;       //0x000000E4
    REG32 bt_gain_table_d;       //0x000000E8
    REG32 bt_gain_table_e;       //0x000000EC
    REG32 bt_gain_table_f;       //0x000000F0
    REG32 wf_gain_table_0;       //0x000000F4
    REG32 wf_gain_table_1;       //0x000000F8
    REG32 wf_gain_table_2;       //0x000000FC
    REG32 wf_gain_table_3;       //0x00000100
    REG32 wf_gain_table_4;       //0x00000104
    REG32 wf_gain_table_5;       //0x00000108
    REG32 wf_gain_table_6;       //0x0000010C
    REG32 wf_gain_table_7;       //0x00000110
    REG32 wf_gain_table_8;       //0x00000114
    REG32 wf_gain_table_9;       //0x00000118
    REG32 wf_gain_table_a;       //0x0000011C
    REG32 wf_gain_table_b;       //0x00000120
    REG32 wf_gain_table_c;       //0x00000124
    REG32 wf_gain_table_d;       //0x00000128
    REG32 wf_gain_table_e;       //0x0000012C
    REG32 wf_gain_table_f;       //0x00000130
    REG32 bt_tx_gain_table_0;    //0x00000134
    REG32 bt_tx_gain_table_1;    //0x00000138
    REG32 bt_tx_gain_table_2;    //0x0000013C
    REG32 bt_tx_gain_table_3;    //0x00000140
    REG32 fm_gain_table_0;       //0x00000144
    REG32 fm_gain_table_1;       //0x00000148
    REG32 fm_gain_table_2;       //0x0000014C
    REG32 fm_gain_table_3;       //0x00000150
    REG32 fm_gain_table_4;       //0x00000154
    REG32 fm_gain_table_5;       //0x00000158
    REG32 fm_gain_table_6;       //0x0000015C
    REG32 fm_gain_table_7;       //0x00000160
    REG32 direct_gain_setting;   //0x00000164
    REG32 bt_rxflt_cal_bit_reg0; //0x00000168
    REG32 bt_rxflt_cal_bit_reg1; //0x0000016C
    REG32 bt_rxflt_cal_bit_reg2; //0x00000170
    REG32 bt_rxflt_cal_bit_reg3; //0x00000174
    REG32 bt_rxflt_cal_bit_reg4; //0x00000178
    REG32 bt_rxflt_cal_bit_reg5; //0x0000017C
    REG32 bt_rxflt_cal_bit_reg6; //0x00000180
    REG32 bt_rxflt_cal_bit_reg7; //0x00000184
    REG32 bt_rxflt_cal_bit_reg8; //0x00000188
    REG32 bt_rxflt_cal_bit_reg9; //0x0000018C
    REG32 bt_rxflt_cal_bit_rega; //0x00000190
    REG32 bt_rxflt_cal_bit_regb; //0x00000194
    REG32 wf_rxflt_cal_bit_reg0; //0x00000198
    REG32 wf_rxflt_cal_bit_reg1; //0x0000019C
    REG32 wf_rxflt_cal_bit_reg2; //0x000001A0
    REG32 wf_rxflt_cal_bit_reg3; //0x000001A4
    REG32 wf_rxflt_cal_bit_reg4; //0x000001A8
    REG32 wf_rxflt_cal_bit_reg5; //0x000001AC
    REG32 wf_rxflt_cal_bit_reg6; //0x000001B0
    REG32 wf_rxflt_cal_bit_reg7; //0x000001B4
    REG32 wf_rxflt_cal_bit_reg8; //0x000001B8
    REG32 wf_rxflt_cal_bit_reg9; //0x000001BC
    REG32 wf_rxflt_cal_bit_rega; //0x000001C0
    REG32 wf_rxflt_cal_bit_regb; //0x000001C4
    REG32 fm_rxflt_cal_bit_reg0; //0x000001C8
    REG32 fm_rxflt_cal_bit_reg1; //0x000001CC
    REG32 fm_rxflt_cal_bit_reg2; //0x000001D0
    REG32 fm_rxflt_cal_bit_reg3; //0x000001D4
    REG32 fm_rxflt_cal_bit_reg4; //0x000001D8
    REG32 fm_rxflt_cal_bit_reg5; //0x000001DC
    REG32 fm_rxflt_cal_bit_reg6; //0x000001E0
    REG32 fm_rxflt_cal_bit_reg7; //0x000001E4
    REG32 test_buf;              //0x000001E8
    REG32 ana_reserved;          //0x000001EC
    REG32 dig_reserved;          //0x000001F0
    REG32 new_add;               //0x000001F4
} HWP_WCN_RF_IF_T;

#define hwp_wcnRfIf ((HWP_WCN_RF_IF_T *)REG_ACCESS_ADDRESS(REG_WCN_RF_IF_BASE))

//revision
typedef union {
    REG32 v;
    struct
    {
        REG32 revid : 4; // [3:0], read only
        REG32 __31_4 : 28;
    } b;
} REG_WCN_RF_IF_REVISION_T;

//sys_control
typedef union {
    REG32 v;
    struct
    {
        REG32 soft_resetn : 1;            // [0]
        REG32 chip_self_cal_enable : 1;   // [1]
        REG32 rf_mode : 2;                // [3:2]
        REG32 clk_digital_enable_reg : 1; // [4]
        REG32 bt_tune_diff_en : 1;        // [5]
        REG32 bt_hopping_en : 1;          // [6]
        REG32 fm_adc_clk_mode : 1;        // [7]
        REG32 bt_ch_ctrl_src_sel : 1;     // [8]
        REG32 bt_tx_type : 1;             // [9]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_RF_IF_SYS_CONTROL_T;

//bt_control
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_arfcn : 7;   // [6:0]
        REG32 bt_ch_type : 1; // [7]
        REG32 __31_8 : 24;
    } b;
} REG_WCN_RF_IF_BT_CONTROL_T;

//wf_control
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_tune : 1;         // [0]
        REG32 wf_chn : 4;          // [4:1]
        REG32 wf_freq_mode : 1;    // [5]
        REG32 wf_freq_direct : 17; // [22:6]
        REG32 __31_23 : 9;
    } b;
} REG_WCN_RF_IF_WF_CONTROL_T;

//fm_control
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_tune : 1;      // [0]
        REG32 fm_chan_reg : 11; // [11:1]
        REG32 fm_freq_mode : 1; // [12]
        REG32 fm_band_sel : 2;  // [14:13]
        REG32 __15_15 : 1;
        REG32 fm_freq_direct : 16; // [31:16]
    } b;
} REG_WCN_RF_IF_FM_CONTROL_T;

//inter_freq_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_if : 11;    // [10:0]
        REG32 bt_imgrej : 1; // [11]
        REG32 bt_zif : 1;    // [12]
        REG32 __15_13 : 3;
        REG32 fm_if : 11;    // [26:16]
        REG32 fm_imgrej : 1; // [27]
        REG32 __31_28 : 4;
    } b;
} REG_WCN_RF_IF_INTER_FREQ_SETTING_T;

//bandgap_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 sel_bg : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_WCN_RF_IF_BANDGAP_SETTING_T;

//lna_rmx_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rmx_rshort_en : 1;   // [0]
        REG32 fm_rmx_reg_bit : 3;     // [3:1]
        REG32 fm_rmx_lobias_bit : 2;  // [5:4]
        REG32 fm_rmx_harm_rej_en : 1; // [6]
        REG32 fm_lna_port_sel : 2;    // [8:7]
        REG32 __11_9 : 3;
        REG32 fm_lna_reg_ictrl : 1;      // [12]
        REG32 bt_rmx_lo_vcom_bit : 2;    // [14:13]
        REG32 bt_tia_rin_bit : 2;        // [16:15]
        REG32 wf_tia_rin_bit : 2;        // [18:17]
        REG32 bt_rmx_disable : 1;        // [19]
        REG32 bt_tia_bypass : 1;         // [20]
        REG32 bt_lna_vcas_bit : 2;       // [22:21]
        REG32 bt_lna_en : 1;             // [23]
        REG32 bt_lna_input_short_tx : 1; // [24]
        REG32 bt_lna_input_short_rx : 1; // [25]
        REG32 __31_26 : 6;
    } b;
} REG_WCN_RF_IF_LNA_RMX_SETTING_T;

//pga_setting0
typedef union {
    REG32 v;
    struct
    {
        REG32 pga_rs_bit : 5;     // [4:0]
        REG32 pga_iq_sw : 1;      // [5]
        REG32 pga_cf_bit : 5;     // [10:6]
        REG32 pga_bw_tun_bit : 3; // [13:11]
        REG32 pga_blk_mode : 1;   // [14]
        REG32 pga_fm_en_reg : 1;  // [15]
        REG32 pga_fm_en_dr : 1;   // [16]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_PGA_SETTING0_T;

//pga_setting1
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_pga_if_mode : 2;    // [1:0]
        REG32 wf_pga_if_mode : 2;    // [3:2]
        REG32 bt_pga_if_mode : 2;    // [5:4]
        REG32 fm_pga_ibit : 2;       // [7:6]
        REG32 wf_pga_ibit : 2;       // [9:8]
        REG32 bt_pga_ibit : 2;       // [11:10]
        REG32 fm_pga_bw_mode : 2;    // [13:12]
        REG32 wf_pga_bw_mode : 2;    // [15:14]
        REG32 bt_pga_bw_mode_2m : 2; // [17:16]
        REG32 bt_pga_bw_mode_1m : 2; // [19:18]
        REG32 fm_pga_gain_bit : 3;   // [22:20]
        REG32 __31_23 : 9;
    } b;
} REG_WCN_RF_IF_PGA_SETTING1_T;

//rxflt_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_wifi_hp : 1;     // [0]
        REG32 wf_rxflt_wifi_hp : 1;     // [1]
        REG32 bt_rxflt_wifi_hp : 1;     // [2]
        REG32 fm_rxflt_if_mode : 2;     // [4:3]
        REG32 wf_rxflt_if_mode : 2;     // [6:5]
        REG32 bt_rxflt_if_mode : 2;     // [8:7]
        REG32 fm_rxflt_ibit : 2;        // [10:9]
        REG32 wf_rxflt_ibit : 2;        // [12:11]
        REG32 bt_rxflt_ibit : 2;        // [14:13]
        REG32 fm_rxflt_mode_sel : 2;    // [16:15]
        REG32 wf_rxflt_mode_sel : 2;    // [18:17]
        REG32 bt_rxflt_mode_sel_2m : 2; // [20:19]
        REG32 bt_rxflt_mode_sel_1m : 2; // [22:21]
        REG32 rxflt_cap_bit : 4;        // [26:23]
        REG32 rxflt_iqswap : 1;         // [27]
        REG32 rxflt_aux_en : 1;         // [28]
        REG32 rxflt_rstn_reg : 1;       // [29]
        REG32 rxflt_rstn_dr : 1;        // [30]
        REG32 __31_31 : 1;
    } b;
} REG_WCN_RF_IF_RXFLT_SETTING_T;

//adc_setting0
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_clk_sel_reg : 3; // [2:0]
        REG32 adc_clk_sel_dr : 1;  // [3]
        REG32 adc_clk_div2 : 1;    // [4]
        REG32 adc_clk_edge : 1;    // [5]
        REG32 adc_vcm_sel : 2;     // [7:6]
        REG32 adc_dly_in_ctrl : 1; // [8]
        REG32 adc_delay_bit : 4;   // [12:9]
        REG32 __31_13 : 19;
    } b;
} REG_WCN_RF_IF_ADC_SETTING0_T;

//adc_setting1
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_adc_reg_ibit : 3;    // [2:0]
        REG32 wf_adc_reg_ibit : 3;    // [5:3]
        REG32 bt_adc_reg_ibit_2m : 3; // [8:6]
        REG32 bt_adc_reg_ibit_1m : 3; // [11:9]
        REG32 fm_adc_ref_ibit : 3;    // [14:12]
        REG32 wf_adc_ref_ibit : 3;    // [17:15]
        REG32 bt_adc_ref_ibit_2m : 3; // [20:18]
        REG32 bt_adc_ref_ibit_1m : 3; // [23:21]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_RF_IF_ADC_SETTING1_T;

//bt_dac_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_dac_range_bit : 2;        // [1:0]
        REG32 bt_dac_mux_en : 1;           // [2]
        REG32 bt_dac_lpwr_mode : 1;        // [3]
        REG32 bt_dac_iout_enable : 1;      // [4]
        REG32 bt_dac_core_bit : 3;         // [7:5]
        REG32 bt_dac_cm_bit : 2;           // [9:8]
        REG32 bt_dac_auxout_en : 3;        // [12:10]
        REG32 bt_dac_vtr_sel : 1;          // [13]
        REG32 bt_dac_vlow_ctrl_bit : 3;    // [16:14]
        REG32 bt_dac_clk_edge : 1;         // [17]
        REG32 bt_dac_rstn_reg : 1;         // [18]
        REG32 bt_dac_rstn_dr : 1;          // [19]
        REG32 bt_dac_low_mag : 1;          // [20]
        REG32 bt_dac_filter_ibias_bit : 2; // [22:21]
        REG32 bt_dac_bw_tune_bit_2m : 4;   // [26:23]
        REG32 bt_dac_bw_tune_bit_1m : 4;   // [30:27]
        REG32 bt_tmx_cal_clk_edge : 1;     // [31]
    } b;
} REG_WCN_RF_IF_BT_DAC_SETTING_T;

//bt_txrf_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 txrf_captune_bit_tx_hi : 4; // [3:0]
        REG32 txrf_captune_bit_tx_md : 4; // [7:4]
        REG32 txrf_captune_bit_tx_lo : 4; // [11:8]
        REG32 txrf_captune_bit_rx_hi : 4; // [15:12]
        REG32 txrf_captune_bit_rx_md : 4; // [19:16]
        REG32 txrf_captune_bit_rx_lo : 4; // [23:20]
        REG32 bt_delay_padrv : 8;         // [31:24]
    } b;
} REG_WCN_RF_IF_BT_TXRF_SETTING_T;

//fm_dsp_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_dsp_resetn_reg : 1;   // [0]
        REG32 fm_dsp_resetn_dr : 1;    // [1]
        REG32 fm_dsp_resetn_delay : 2; // [3:2]
        REG32 __31_4 : 28;
    } b;
} REG_WCN_RF_IF_FM_DSP_SETTING_T;

//vco_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_vco_vmode : 1;      // [0]
        REG32 wf_vco_vmode : 1;      // [1]
        REG32 bt_vco_vmode : 1;      // [2]
        REG32 fm_vco_imode : 1;      // [3]
        REG32 wf_vco_imode : 1;      // [4]
        REG32 bt_vco_imode : 1;      // [5]
        REG32 vco_vmode_bit : 3;     // [8:6]
        REG32 vco_var_vcom : 3;      // [11:9]
        REG32 vco_var_short : 1;     // [12]
        REG32 vco_var_reverse : 1;   // [13]
        REG32 vco_var_bit : 3;       // [16:14]
        REG32 vco_buf_bias_bit : 2;  // [18:17]
        REG32 vco_div2_bias_bit : 3; // [21:19]
        REG32 vco_buf_ibit : 4;      // [25:22]
        REG32 vco_regcap_selh : 1;   // [26]
        REG32 __31_27 : 5;
    } b;
} REG_WCN_RF_IF_VCO_SETTING_T;

//pll_setting0
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_div_fm_adc_clk_reg : 5; // [4:0]
        REG32 pll_div_fm_adc_clk_dr : 1;  // [5]
        REG32 pll_div_fm_lo_clk_reg : 4;  // [9:6]
        REG32 pll_div_fm_lo_clk_dr : 1;   // [10]
        REG32 pll_bypass_notch : 1;       // [11]
        REG32 pll_xfer_aux_en : 1;        // [12]
        REG32 pll_sinc_mode : 3;          // [15:13]
        REG32 pll_fbc_sel : 3;            // [18:16]
        REG32 pll_open_en : 1;            // [19]
        REG32 pll_reg_presc_rc : 2;       // [21:20]
        REG32 pll_reg_presc : 4;          // [25:22]
        REG32 pll_reg_peri_bit : 4;       // [29:26]
        REG32 pll_test_en : 1;            // [30]
        REG32 __31_31 : 1;
    } b;
} REG_WCN_RF_IF_PLL_SETTING0_T;

//pll_setting1
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_refmulti2_en_tx : 1; // [0]
        REG32 pll_refmulti2_en_rx : 1; // [1]
        REG32 pll_r_bit_tx : 2;        // [3:2]
        REG32 pll_r_bit_rx : 2;        // [5:4]
        REG32 pll_lpf_gain_tx : 4;     // [9:6]
        REG32 pll_lpf_gain_rx : 4;     // [13:10]
        REG32 pll_gain_bit_tx : 4;     // [17:14]
        REG32 pll_gain_bit_rx : 4;     // [21:18]
        REG32 pll_cp_r_bit_tx : 4;     // [25:22]
        REG32 pll_cp_r_bit_rx : 4;     // [29:26]
        REG32 pll_lowpwr_mode_tx : 1;  // [30]
        REG32 pll_lowpwr_mode_rx : 1;  // [31]
    } b;
} REG_WCN_RF_IF_PLL_SETTING1_T;

//pll_setting2
typedef union {
    REG32 v;
    struct
    {
        REG32 mdll_div_tx : 4;            // [3:0]
        REG32 mdll_div_rx : 4;            // [7:4]
        REG32 pll_phase_ctrl_dly_tx : 2;  // [9:8]
        REG32 pll_phase_ctrl_dly_rx : 2;  // [11:10]
        REG32 pll_pfd_res_bit_tx : 6;     // [17:12]
        REG32 pll_pfd_res_bit_rx : 6;     // [23:18]
        REG32 pll_ref_mode_tx : 1;        // [24]
        REG32 pll_ref_mode_rx : 1;        // [25]
        REG32 pll_mdll_refclk_en_reg : 1; // [26]
        REG32 pll_mdll_refclk_en_dr : 1;  // [27]
        REG32 pll_clk_dig52m_en_reg : 1;  // [28]
        REG32 pll_clk_dig52m_en_dr : 1;   // [29]
        REG32 pll_bt_adc_clk_en_reg : 1;  // [30]
        REG32 pll_bt_adc_clk_en_dr : 1;   // [31]
    } b;
} REG_WCN_RF_IF_PLL_SETTING2_T;

//pll_status
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_lock_det : 1;                  // [0], read only
        REG32 pll_lock_flag : 1;                 // [1], read only
        REG32 pll_lock_det_timer_delay_sel : 2;  // [3:2]
        REG32 pll_lock_flag_timer_delay_sel : 2; // [5:4]
        REG32 __31_6 : 26;
    } b;
} REG_WCN_RF_IF_PLL_STATUS_T;

//adpll_setting0
typedef union {
    REG32 v;
    struct
    {
        REG32 adpll_sdm_clk_test_en : 1;         // [0]
        REG32 adpll_vco_low_test : 1;            // [1]
        REG32 adpll_vco_high_test : 1;           // [2]
        REG32 adpll_refmulti2_en : 1;            // [3]
        REG32 adpll_pcon_mode : 1;               // [4]
        REG32 adpll_vreg_bit : 4;                // [8:5]
        REG32 adpll_test_en : 1;                 // [9]
        REG32 adpll_res_bit : 2;                 // [11:10]
        REG32 adpll_reg_res_bit : 2;             // [13:12]
        REG32 adpll_cp_ibit : 3;                 // [16:14]
        REG32 adpll_rstn_reg : 1;                // [17]
        REG32 adpll_rstn_dr : 1;                 // [18]
        REG32 adpll_clk_en_timer_delay : 1;      // [19]
        REG32 adpll_rstn_timer_delay : 7;        // [26:20]
        REG32 adpll_sdm_clk_sel_timer_delay : 3; // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_ADPLL_SETTING0_T;

//adpll_setting1
typedef union {
    REG32 v;
    struct
    {
        REG32 adpll_clk2wf_dig_sel_reg : 1;   // [0]
        REG32 adpll_clk2wf_dig_sel_dr : 1;    // [1]
        REG32 adpll_clk2wf_dig_en_reg : 1;    // [2]
        REG32 adpll_clk2wf_dig_en_dr : 1;     // [3]
        REG32 adpll_clk2fmwf_adc_sel_reg : 1; // [4]
        REG32 adpll_clk2fmwf_adc_sel_dr : 1;  // [5]
        REG32 adpll_clk2fmwf_adc_en_reg : 1;  // [6]
        REG32 adpll_clk2fmwf_adc_en_dr : 1;   // [7]
        REG32 adpll_clk2bt_adc_sel_reg : 1;   // [8]
        REG32 adpll_clk2bt_adc_sel_dr : 1;    // [9]
        REG32 adpll_clk2bt_adc_en_reg : 1;    // [10]
        REG32 adpll_clk2bt_adc_en_dr : 1;     // [11]
        REG32 adpll_clk2bt_dig_sel : 1;       // [12]
        REG32 adpll_clk2bt_dig_en : 1;        // [13]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_RF_IF_ADPLL_SETTING1_T;

//adpll_status
typedef union {
    REG32 v;
    struct
    {
        REG32 adpll_lock_det : 1;                  // [0], read only
        REG32 adpll_lock_flag : 1;                 // [1], read only
        REG32 adpll_lock_det_timer_delay_sel : 2;  // [3:2]
        REG32 adpll_lock_flag_timer_delay_sel : 2; // [5:4]
        REG32 __31_6 : 26;
    } b;
} REG_WCN_RF_IF_ADPLL_STATUS_T;

//mdll_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 mdll_div_bit : 5;       // [4:0]
        REG32 mdll_band_sel : 1;      // [5]
        REG32 mdll_band_bit : 3;      // [8:6]
        REG32 mdll_cp_ibit : 3;       // [11:9]
        REG32 mdll_startup_bit : 3;   // [14:12]
        REG32 disable_refclk_pll : 1; // [15]
        REG32 mdll_rstn_reg : 1;      // [16]
        REG32 mdll_rstn_dr : 1;       // [17]
        REG32 __31_18 : 14;
    } b;
} REG_WCN_RF_IF_MDLL_SETTING_T;

//pll_sdm_setting0
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_sdm_delay_sel : 4;         // [3:0]
        REG32 pll_sdm_dither_bypass : 1;     // [4]
        REG32 pll_sdm_int_dec_sel : 2;       // [6:5]
        REG32 pll_sdm_clk_edge : 1;          // [7]
        REG32 pll_sdm_resetn_reg : 1;        // [8]
        REG32 pll_sdm_resetn_dr : 1;         // [9]
        REG32 reset_pll_sdm_timer_delay : 4; // [13:10]
        REG32 pll_sdm_clk_sel_1 : 1;         // [14]
        REG32 pll_sdm_clk_sel_0 : 1;         // [15]
        REG32 pll_div_dr : 1;                // [16]
        REG32 pll_freq_former_bypass : 1;    // [17]
        REG32 pll_freq_former_shift_ct : 3;  // [20:18]
        REG32 __31_21 : 11;
    } b;
} REG_WCN_RF_IF_PLL_SDM_SETTING0_T;

//pll_sdm_setting1
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_div_reg : 31; // [30:0]
        REG32 __31_31 : 1;
    } b;
} REG_WCN_RF_IF_PLL_SDM_SETTING1_T;

//adpll_sdm_setting0
typedef union {
    REG32 v;
    struct
    {
        REG32 adpll_sdm_dither_bypass : 1;     // [0]
        REG32 adpll_sdm_int_dec_sel : 3;       // [3:1]
        REG32 adpll_sdm_clk_fbc_inv : 1;       // [4]
        REG32 adpll_sdm_resetn_reg : 1;        // [5]
        REG32 adpll_sdm_resetn_dr : 1;         // [6]
        REG32 reset_adpll_sdm_timer_delay : 4; // [10:7]
        REG32 adpll_sdm_clk_sel_1 : 1;         // [11]
        REG32 adpll_sdm_clk_sel_0 : 1;         // [12]
        REG32 adpll_sdm_freq_dr : 1;           // [13]
        REG32 __31_14 : 18;
    } b;
} REG_WCN_RF_IF_ADPLL_SDM_SETTING0_T;

//adpll_sdm_setting2
typedef union {
    REG32 v;
    struct
    {
        REG32 adpll_sdm_ss_devi_step : 16; // [15:0]
        REG32 adpll_sdm_ss_devi : 12;      // [27:16]
        REG32 adpll_sdm_ss_en : 1;         // [28]
        REG32 __31_29 : 3;
    } b;
} REG_WCN_RF_IF_ADPLL_SDM_SETTING2_T;

//rxflt_cal_setting0
typedef union {
    REG32 v;
    struct
    {
        REG32 rxflt_cal_init_delay : 4;    // [3:0]
        REG32 rxflt_cal_cnt : 4;           // [7:4]
        REG32 rxflt_cal_iqswap : 1;        // [8]
        REG32 rxflt_cal_polarity : 1;      // [9]
        REG32 rxflt_cal_mode_sel : 2;      // [11:10]
        REG32 rxflt_cal_clk_edge_sel : 1;  // [12]
        REG32 rxflt_cal_clk_edge : 1;      // [13]
        REG32 rxflt_cal_cycles : 2;        // [15:14]
        REG32 wf_rxflt_cal_loop_coef : 15; // [30:16]
        REG32 __31_31 : 1;
    } b;
} REG_WCN_RF_IF_RXFLT_CAL_SETTING0_T;

//rxflt_cal_setting1
typedef union {
    REG32 v;
    struct
    {
        REG32 rxflt_cal_q_bit_reg : 8;         // [7:0]
        REG32 rxflt_cal_i_bit_reg : 8;         // [15:8]
        REG32 wf_rxflt_cal_loop_adc_rng : 10;  // [25:16]
        REG32 wf_rxflt_cal_loop_pol : 1;       // [26]
        REG32 wf_rxflt_cal_loop_en : 1;        // [27]
        REG32 fm_rxflt_cal_resolv_enhance : 1; // [28]
        REG32 wf_rxflt_cal_resolv_enhance : 1; // [29]
        REG32 bt_rxflt_cal_resolv_enhance : 1; // [30]
        REG32 rxflt_cal_bit_dr : 1;            // [31]
    } b;
} REG_WCN_RF_IF_RXFLT_CAL_SETTING1_T;

//rxflt_cal_setting2
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_chn_md : 7;                  // [6:0]
        REG32 bt_rxflt_cal_inter_en : 1;      // [7]
        REG32 wf_rxflt_cal_inter_coef_hi : 8; // [15:8]
        REG32 wf_rxflt_cal_inter_coef_lo : 8; // [23:16]
        REG32 wf_chn_md : 4;                  // [27:24]
        REG32 wf_rxflt_cal_inter_en : 1;      // [28]
        REG32 rxflt_cal_range_bit : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_WCN_RF_IF_RXFLT_CAL_SETTING2_T;

//rxflt_cal_setting3
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_inter_coef_hi : 15; // [14:0]
        REG32 __15_15 : 1;
        REG32 bt_rxflt_cal_inter_coef_lo : 15; // [30:16]
        REG32 __31_31 : 1;
    } b;
} REG_WCN_RF_IF_RXFLT_CAL_SETTING3_T;

//vco_pkd_cal_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 vco_pkd_cal_polarity : 1;   // [0]
        REG32 vco_pkd_cal_init_delay : 4; // [4:1]
        REG32 vco_pkd_ref_bit : 3;        // [7:5]
        REG32 vco_vbit_reg : 4;           // [11:8]
        REG32 vco_vbit_dr : 1;            // [12]
        REG32 vco_ibit_reg : 4;           // [16:13]
        REG32 vco_ibit_dr : 1;            // [17]
        REG32 __31_18 : 14;
    } b;
} REG_WCN_RF_IF_VCO_PKD_CAL_SETTING_T;

//pll_cal_setting0
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_init_delay : 3;        // [2:0]
        REG32 pll_cal_cnt_sel : 3;       // [5:3]
        REG32 pll_cal_opt : 1;           // [6]
        REG32 pll_vco_bit_hold_time : 3; // [9:7]
        REG32 pll_cal_freq_dr : 1;       // [10]
        REG32 vco_band_reg : 10;         // [20:11]
        REG32 vco_band_dr : 1;           // [21]
        REG32 pll_cal_bit : 2;           // [23:22]
        REG32 pll_cal_clk_sel : 1;       // [24]
        REG32 __31_25 : 7;
    } b;
} REG_WCN_RF_IF_PLL_CAL_SETTING0_T;

//pll_cal_setting1
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_cal_freq_reg : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_RF_IF_PLL_CAL_SETTING1_T;

//adc_cal_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_vreg_vbit_reg : 3;      // [2:0]
        REG32 adc_vreg_vbit_dr : 1;       // [3]
        REG32 adc_reg_cal_polarity : 1;   // [4]
        REG32 adc_reg_cal_init_delay : 4; // [8:5]
        REG32 adc_vref_vbit_reg : 3;      // [11:9]
        REG32 adc_vref_vbit_dr : 1;       // [12]
        REG32 adc_ref_cal_polarity : 1;   // [13]
        REG32 adc_ref_cal_init_delay : 4; // [17:14]
        REG32 adc_cal_rstn_reg : 1;       // [18]
        REG32 adc_cal_rstn_dr : 1;        // [19]
        REG32 __31_20 : 12;
    } b;
} REG_WCN_RF_IF_ADC_CAL_SETTING_T;

//cal_dr_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_cal_en_reg : 1;     // [0]
        REG32 pll_cal_en_dr : 1;      // [1]
        REG32 rxflt_cal_en_reg : 1;   // [2]
        REG32 rxflt_cal_en_dr : 1;    // [3]
        REG32 adc_reg_cal_en_reg : 1; // [4]
        REG32 adc_reg_cal_en_dr : 1;  // [5]
        REG32 adc_ref_cal_en_reg : 1; // [6]
        REG32 adc_ref_cal_en_dr : 1;  // [7]
        REG32 vco_pkd_cal_en_reg : 1; // [8]
        REG32 vco_pkd_cal_en_dr : 1;  // [9]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_RF_IF_CAL_DR_SETTING_T;

//cal_status
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_self_cal_ready : 1; // [0], read only
        REG32 wf_self_cal_ready : 1; // [1], read only
        REG32 fm_self_cal_ready : 1; // [2], read only
        REG32 pll_cal_ready : 1;     // [3], read only
        REG32 rxflt_cal_ready : 1;   // [4], read only
        REG32 adc_reg_cal_ready : 1; // [5], read only
        REG32 adc_ref_cal_ready : 1; // [6], read only
        REG32 vco_pkd_cal_ready : 1; // [7], read only
        REG32 __31_8 : 24;
    } b;
} REG_WCN_RF_IF_CAL_STATUS_T;

//cal_results0
typedef union {
    REG32 v;
    struct
    {
        REG32 rxflt_cal_q_bit : 8; // [7:0], read only
        REG32 rxflt_cal_i_bit : 8; // [15:8], read only
        REG32 adc_vreg_vbit : 3;   // [18:16], read only
        REG32 adc_vref_vbit : 3;   // [21:19], read only
        REG32 vco_vbit : 4;        // [25:22], read only
        REG32 vco_ibit : 4;        // [29:26], read only
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_CAL_RESULTS0_T;

//cal_results1
typedef union {
    REG32 v;
    struct
    {
        REG32 vco_band : 10;       // [9:0], read only
        REG32 rxflt_cal_out_q : 1; // [10], read only
        REG32 rxflt_cal_out_i : 1; // [11], read only
        REG32 adc_cal_ref_out : 1; // [12], read only
        REG32 adc_cal_reg_out : 1; // [13], read only
        REG32 vco_pkd_cal_out : 1; // [14], read only
        REG32 __31_15 : 17;
    } b;
} REG_WCN_RF_IF_CAL_RESULTS1_T;

//power_dr
typedef union {
    REG32 v;
    struct
    {
        REG32 pu_mdll_dr : 1;           // [0]
        REG32 pu_adpll_dr : 1;          // [1]
        REG32 pu_pll_fm_adc_clk_dr : 1; // [2]
        REG32 pu_pll_fm_lo_clk_dr : 1;  // [3]
        REG32 pu_pll_presc_dr : 1;      // [4]
        REG32 pu_pll_peri_dr : 1;       // [5]
        REG32 pu_vco_pkd_dr : 1;        // [6]
        REG32 pu_vco_rxlo_dr : 1;       // [7]
        REG32 pu_vco_txlo_dr : 1;       // [8]
        REG32 pu_vco_dr : 1;            // [9]
        REG32 pu_bt_txrf_dr : 1;        // [10]
        REG32 pu_bt_tmx_dr : 1;         // [11]
        REG32 pu_bt_padrv_dr : 1;       // [12]
        REG32 pu_bt_dac_dr : 1;         // [13]
        REG32 pu_adc_dr : 1;            // [14]
        REG32 pu_rxflt_dr : 1;          // [15]
        REG32 pu_pga_dr : 1;            // [16]
        REG32 pu_bt_tia_dr : 1;         // [17]
        REG32 pu_bt_lna_dr : 1;         // [18]
        REG32 pu_fm_rmx_dr : 1;         // [19]
        REG32 pu_fm_lna_dr : 1;         // [20]
        REG32 pu_bg_dr : 1;             // [21]
        REG32 __31_22 : 10;
    } b;
} REG_WCN_RF_IF_POWER_DR_T;

//power_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pu_mdll_reg : 1;           // [0]
        REG32 pu_adpll_reg : 1;          // [1]
        REG32 pu_pll_fm_adc_clk_reg : 1; // [2]
        REG32 pu_pll_fm_lo_clk_reg : 1;  // [3]
        REG32 pu_pll_presc_reg : 1;      // [4]
        REG32 pu_pll_peri_reg : 1;       // [5]
        REG32 pu_vco_pkd_reg : 1;        // [6]
        REG32 pu_vco_rxlo_reg : 1;       // [7]
        REG32 pu_vco_txlo_reg : 1;       // [8]
        REG32 pu_vco_reg : 1;            // [9]
        REG32 pu_bt_txrf_reg : 1;        // [10]
        REG32 pu_bt_tmx_reg : 1;         // [11]
        REG32 pu_bt_padrv_reg : 1;       // [12]
        REG32 pu_bt_dac_reg : 1;         // [13]
        REG32 pu_adc_reg : 1;            // [14]
        REG32 pu_rxflt_reg : 1;          // [15]
        REG32 pu_pga_reg : 1;            // [16]
        REG32 pu_bt_tia_reg : 1;         // [17]
        REG32 pu_bt_lna_reg : 1;         // [18]
        REG32 pu_fm_rmx_reg : 1;         // [19]
        REG32 pu_fm_lna_reg : 1;         // [20]
        REG32 pu_bg_reg : 1;             // [21]
        REG32 __31_22 : 10;
    } b;
} REG_WCN_RF_IF_POWER_REG_T;

//power_status
typedef union {
    REG32 v;
    struct
    {
        REG32 pu_mdll : 1;           // [0], read only
        REG32 pu_adpll : 1;          // [1], read only
        REG32 pu_pll_fm_adc_clk : 1; // [2], read only
        REG32 pu_pll_fm_lo_clk : 1;  // [3], read only
        REG32 pu_pll_presc : 1;      // [4], read only
        REG32 pu_pll_peri : 1;       // [5], read only
        REG32 pu_vco_pkd : 1;        // [6], read only
        REG32 pu_vco_rxlo : 1;       // [7], read only
        REG32 pu_vco_txlo : 1;       // [8], read only
        REG32 pu_vco : 1;            // [9], read only
        REG32 pu_bt_txrf : 1;        // [10], read only
        REG32 pu_bt_tmx : 1;         // [11], read only
        REG32 pu_bt_padrv : 1;       // [12], read only
        REG32 pu_bt_dac : 1;         // [13], read only
        REG32 pu_adc : 1;            // [14], read only
        REG32 pu_rxflt : 1;          // [15], read only
        REG32 pu_pga : 1;            // [16], read only
        REG32 pu_bt_tia : 1;         // [17], read only
        REG32 pu_bt_lna : 1;         // [18], read only
        REG32 pu_fm_rmx : 1;         // [19], read only
        REG32 pu_fm_lna : 1;         // [20], read only
        REG32 pu_bg : 1;             // [21], read only
        REG32 __31_22 : 10;
    } b;
} REG_WCN_RF_IF_POWER_STATUS_T;

//bt_gain_table_0
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_0 : 4; // [3:0]
        REG32 bt_pga_gain_bit_0 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_0 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_0 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_0 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_0 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_0_T;

//bt_gain_table_1
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_1 : 4; // [3:0]
        REG32 bt_pga_gain_bit_1 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_1 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_1 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_1 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_1 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_1_T;

//bt_gain_table_2
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_2 : 4; // [3:0]
        REG32 bt_pga_gain_bit_2 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_2 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_2 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_2 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_2 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_2_T;

//bt_gain_table_3
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_3 : 4; // [3:0]
        REG32 bt_pga_gain_bit_3 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_3 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_3 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_3 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_3 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_3_T;

//bt_gain_table_4
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_4 : 4; // [3:0]
        REG32 bt_pga_gain_bit_4 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_4 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_4 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_4 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_4 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_4_T;

//bt_gain_table_5
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_5 : 4; // [3:0]
        REG32 bt_pga_gain_bit_5 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_5 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_5 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_5 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_5 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_5_T;

//bt_gain_table_6
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_6 : 4; // [3:0]
        REG32 bt_pga_gain_bit_6 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_6 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_6 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_6 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_6 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_6_T;

//bt_gain_table_7
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_7 : 4; // [3:0]
        REG32 bt_pga_gain_bit_7 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_7 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_7 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_7 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_7 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_7_T;

//bt_gain_table_8
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_8 : 4; // [3:0]
        REG32 bt_pga_gain_bit_8 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_8 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_8 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_8 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_8 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_8_T;

//bt_gain_table_9
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_9 : 4; // [3:0]
        REG32 bt_pga_gain_bit_9 : 3;      // [6:4]
        REG32 bt_lna_resf_bit_9 : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_9 : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_9 : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_9 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_9_T;

//bt_gain_table_a
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_a : 4; // [3:0]
        REG32 bt_pga_gain_bit_a : 3;      // [6:4]
        REG32 bt_lna_resf_bit_a : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_a : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_a : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_a : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_A_T;

//bt_gain_table_b
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_b : 4; // [3:0]
        REG32 bt_pga_gain_bit_b : 3;      // [6:4]
        REG32 bt_lna_resf_bit_b : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_b : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_b : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_b : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_B_T;

//bt_gain_table_c
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_c : 4; // [3:0]
        REG32 bt_pga_gain_bit_c : 3;      // [6:4]
        REG32 bt_lna_resf_bit_c : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_c : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_c : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_c : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_C_T;

//bt_gain_table_d
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_d : 4; // [3:0]
        REG32 bt_pga_gain_bit_d : 3;      // [6:4]
        REG32 bt_lna_resf_bit_d : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_d : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_d : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_d : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_D_T;

//bt_gain_table_e
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_e : 4; // [3:0]
        REG32 bt_pga_gain_bit_e : 3;      // [6:4]
        REG32 bt_lna_resf_bit_e : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_e : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_e : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_e : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_E_T;

//bt_gain_table_f
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_bt_gain_bit_f : 4; // [3:0]
        REG32 bt_pga_gain_bit_f : 3;      // [6:4]
        REG32 bt_lna_resf_bit_f : 4;      // [10:7]
        REG32 bt_lna_gain3_bit_f : 2;     // [12:11]
        REG32 bt_lna_gain2_bit_f : 2;     // [14:13]
        REG32 bt_lna_gain1_bit_f : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_BT_GAIN_TABLE_F_T;

//wf_gain_table_0
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_0 : 4; // [3:0]
        REG32 wf_pga_gain_bit_0 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_0 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_0 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_0 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_0 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_0_T;

//wf_gain_table_1
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_1 : 4; // [3:0]
        REG32 wf_pga_gain_bit_1 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_1 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_1 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_1 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_1 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_1_T;

//wf_gain_table_2
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_2 : 4; // [3:0]
        REG32 wf_pga_gain_bit_2 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_2 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_2 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_2 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_2 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_2_T;

//wf_gain_table_3
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_3 : 4; // [3:0]
        REG32 wf_pga_gain_bit_3 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_3 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_3 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_3 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_3 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_3_T;

//wf_gain_table_4
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_4 : 4; // [3:0]
        REG32 wf_pga_gain_bit_4 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_4 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_4 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_4 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_4 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_4_T;

//wf_gain_table_5
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_5 : 4; // [3:0]
        REG32 wf_pga_gain_bit_5 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_5 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_5 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_5 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_5 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_5_T;

//wf_gain_table_6
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_6 : 4; // [3:0]
        REG32 wf_pga_gain_bit_6 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_6 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_6 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_6 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_6 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_6_T;

//wf_gain_table_7
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_7 : 4; // [3:0]
        REG32 wf_pga_gain_bit_7 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_7 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_7 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_7 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_7 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_7_T;

//wf_gain_table_8
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_8 : 4; // [3:0]
        REG32 wf_pga_gain_bit_8 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_8 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_8 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_8 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_8 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_8_T;

//wf_gain_table_9
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_9 : 4; // [3:0]
        REG32 wf_pga_gain_bit_9 : 3;      // [6:4]
        REG32 wf_lna_resf_bit_9 : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_9 : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_9 : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_9 : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_9_T;

//wf_gain_table_a
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_a : 4; // [3:0]
        REG32 wf_pga_gain_bit_a : 3;      // [6:4]
        REG32 wf_lna_resf_bit_a : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_a : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_a : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_a : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_A_T;

//wf_gain_table_b
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_b : 4; // [3:0]
        REG32 wf_pga_gain_bit_b : 3;      // [6:4]
        REG32 wf_lna_resf_bit_b : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_b : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_b : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_b : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_B_T;

//wf_gain_table_c
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_c : 4; // [3:0]
        REG32 wf_pga_gain_bit_c : 3;      // [6:4]
        REG32 wf_lna_resf_bit_c : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_c : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_c : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_c : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_C_T;

//wf_gain_table_d
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_d : 4; // [3:0]
        REG32 wf_pga_gain_bit_d : 3;      // [6:4]
        REG32 wf_lna_resf_bit_d : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_d : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_d : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_d : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_D_T;

//wf_gain_table_e
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_e : 4; // [3:0]
        REG32 wf_pga_gain_bit_e : 3;      // [6:4]
        REG32 wf_lna_resf_bit_e : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_e : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_e : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_e : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_E_T;

//wf_gain_table_f
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_bt_gain_bit_f : 4; // [3:0]
        REG32 wf_pga_gain_bit_f : 3;      // [6:4]
        REG32 wf_lna_resf_bit_f : 4;      // [10:7]
        REG32 wf_lna_gain3_bit_f : 2;     // [12:11]
        REG32 wf_lna_gain2_bit_f : 2;     // [14:13]
        REG32 wf_lna_gain1_bit_f : 2;     // [16:15]
        REG32 __31_17 : 15;
    } b;
} REG_WCN_RF_IF_WF_GAIN_TABLE_F_T;

//bt_tx_gain_table_0
typedef union {
    REG32 v;
    struct
    {
        REG32 txrf_pad_cas_vbit_1 : 2;  // [1:0]
        REG32 txrf_pad_aux_vbit_1 : 2;  // [3:2]
        REG32 txrf_pad_bias_ibit_1 : 2; // [5:4]
        REG32 txrf_att_en_1 : 2;        // [7:6]
        REG32 txrf_gain_bit_1 : 4;      // [11:8]
        REG32 txrf_pad_mode_1 : 1;      // [12]
        REG32 __15_13 : 3;
        REG32 txrf_pad_cas_vbit_0 : 2;  // [17:16]
        REG32 txrf_pad_aux_vbit_0 : 2;  // [19:18]
        REG32 txrf_pad_bias_ibit_0 : 2; // [21:20]
        REG32 txrf_att_en_0 : 2;        // [23:22]
        REG32 txrf_gain_bit_0 : 4;      // [27:24]
        REG32 txrf_pad_mode_0 : 1;      // [28]
        REG32 __31_29 : 3;
    } b;
} REG_WCN_RF_IF_BT_TX_GAIN_TABLE_0_T;

//bt_tx_gain_table_1
typedef union {
    REG32 v;
    struct
    {
        REG32 txrf_pad_cas_vbit_3 : 2;  // [1:0]
        REG32 txrf_pad_aux_vbit_3 : 2;  // [3:2]
        REG32 txrf_pad_bias_ibit_3 : 2; // [5:4]
        REG32 txrf_att_en_3 : 2;        // [7:6]
        REG32 txrf_gain_bit_3 : 4;      // [11:8]
        REG32 txrf_pad_mode_3 : 1;      // [12]
        REG32 __15_13 : 3;
        REG32 txrf_pad_cas_vbit_2 : 2;  // [17:16]
        REG32 txrf_pad_aux_vbit_2 : 2;  // [19:18]
        REG32 txrf_pad_bias_ibit_2 : 2; // [21:20]
        REG32 txrf_att_en_2 : 2;        // [23:22]
        REG32 txrf_gain_bit_2 : 4;      // [27:24]
        REG32 txrf_pad_mode_2 : 1;      // [28]
        REG32 __31_29 : 3;
    } b;
} REG_WCN_RF_IF_BT_TX_GAIN_TABLE_1_T;

//bt_tx_gain_table_2
typedef union {
    REG32 v;
    struct
    {
        REG32 txrf_pad_cas_vbit_5 : 2;  // [1:0]
        REG32 txrf_pad_aux_vbit_5 : 2;  // [3:2]
        REG32 txrf_pad_bias_ibit_5 : 2; // [5:4]
        REG32 txrf_att_en_5 : 2;        // [7:6]
        REG32 txrf_gain_bit_5 : 4;      // [11:8]
        REG32 txrf_pad_mode_5 : 1;      // [12]
        REG32 __15_13 : 3;
        REG32 txrf_pad_cas_vbit_4 : 2;  // [17:16]
        REG32 txrf_pad_aux_vbit_4 : 2;  // [19:18]
        REG32 txrf_pad_bias_ibit_4 : 2; // [21:20]
        REG32 txrf_att_en_4 : 2;        // [23:22]
        REG32 txrf_gain_bit_4 : 4;      // [27:24]
        REG32 txrf_pad_mode_4 : 1;      // [28]
        REG32 __31_29 : 3;
    } b;
} REG_WCN_RF_IF_BT_TX_GAIN_TABLE_2_T;

//bt_tx_gain_table_3
typedef union {
    REG32 v;
    struct
    {
        REG32 txrf_pad_cas_vbit_7 : 2;  // [1:0]
        REG32 txrf_pad_aux_vbit_7 : 2;  // [3:2]
        REG32 txrf_pad_bias_ibit_7 : 2; // [5:4]
        REG32 txrf_att_en_7 : 2;        // [7:6]
        REG32 txrf_gain_bit_7 : 4;      // [11:8]
        REG32 txrf_pad_mode_7 : 1;      // [12]
        REG32 __15_13 : 3;
        REG32 txrf_pad_cas_vbit_6 : 2;  // [17:16]
        REG32 txrf_pad_aux_vbit_6 : 2;  // [19:18]
        REG32 txrf_pad_bias_ibit_6 : 2; // [21:20]
        REG32 txrf_att_en_6 : 2;        // [23:22]
        REG32 txrf_gain_bit_6 : 4;      // [27:24]
        REG32 txrf_pad_mode_6 : 1;      // [28]
        REG32 __31_29 : 3;
    } b;
} REG_WCN_RF_IF_BT_TX_GAIN_TABLE_3_T;

//fm_gain_table_0
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_bt_gain_bit_1 : 4; // [3:0]
        REG32 fm_rmx_gain_bit_1 : 3;      // [6:4]
        REG32 fm_lna_rload_bit_1 : 2;     // [8:7]
        REG32 fm_lna_gain_bit_1 : 2;      // [10:9]
        REG32 fm_lna_reg_ibit_1 : 3;      // [13:11]
        REG32 __15_14 : 2;
        REG32 fm_rxflt_bt_gain_bit_0 : 4; // [19:16]
        REG32 fm_rmx_gain_bit_0 : 3;      // [22:20]
        REG32 fm_lna_rload_bit_0 : 2;     // [24:23]
        REG32 fm_lna_gain_bit_0 : 2;      // [26:25]
        REG32 fm_lna_reg_ibit_0 : 3;      // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_FM_GAIN_TABLE_0_T;

//fm_gain_table_1
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_bt_gain_bit_3 : 4; // [3:0]
        REG32 fm_rmx_gain_bit_3 : 3;      // [6:4]
        REG32 fm_lna_rload_bit_3 : 2;     // [8:7]
        REG32 fm_lna_gain_bit_3 : 2;      // [10:9]
        REG32 fm_lna_reg_ibit_3 : 3;      // [13:11]
        REG32 __15_14 : 2;
        REG32 fm_rxflt_bt_gain_bit_2 : 4; // [19:16]
        REG32 fm_rmx_gain_bit_2 : 3;      // [22:20]
        REG32 fm_lna_rload_bit_2 : 2;     // [24:23]
        REG32 fm_lna_gain_bit_2 : 2;      // [26:25]
        REG32 fm_lna_reg_ibit_2 : 3;      // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_FM_GAIN_TABLE_1_T;

//fm_gain_table_2
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_bt_gain_bit_5 : 4; // [3:0]
        REG32 fm_rmx_gain_bit_5 : 3;      // [6:4]
        REG32 fm_lna_rload_bit_5 : 2;     // [8:7]
        REG32 fm_lna_gain_bit_5 : 2;      // [10:9]
        REG32 fm_lna_reg_ibit_5 : 3;      // [13:11]
        REG32 __15_14 : 2;
        REG32 fm_rxflt_bt_gain_bit_4 : 4; // [19:16]
        REG32 fm_rmx_gain_bit_4 : 3;      // [22:20]
        REG32 fm_lna_rload_bit_4 : 2;     // [24:23]
        REG32 fm_lna_gain_bit_4 : 2;      // [26:25]
        REG32 fm_lna_reg_ibit_4 : 3;      // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_FM_GAIN_TABLE_2_T;

//fm_gain_table_3
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_bt_gain_bit_7 : 4; // [3:0]
        REG32 fm_rmx_gain_bit_7 : 3;      // [6:4]
        REG32 fm_lna_rload_bit_7 : 2;     // [8:7]
        REG32 fm_lna_gain_bit_7 : 2;      // [10:9]
        REG32 fm_lna_reg_ibit_7 : 3;      // [13:11]
        REG32 __15_14 : 2;
        REG32 fm_rxflt_bt_gain_bit_6 : 4; // [19:16]
        REG32 fm_rmx_gain_bit_6 : 3;      // [22:20]
        REG32 fm_lna_rload_bit_6 : 2;     // [24:23]
        REG32 fm_lna_gain_bit_6 : 2;      // [26:25]
        REG32 fm_lna_reg_ibit_6 : 3;      // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_FM_GAIN_TABLE_3_T;

//fm_gain_table_4
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_bt_gain_bit_9 : 4; // [3:0]
        REG32 fm_rmx_gain_bit_9 : 3;      // [6:4]
        REG32 fm_lna_rload_bit_9 : 2;     // [8:7]
        REG32 fm_lna_gain_bit_9 : 2;      // [10:9]
        REG32 fm_lna_reg_ibit_9 : 3;      // [13:11]
        REG32 __15_14 : 2;
        REG32 fm_rxflt_bt_gain_bit_8 : 4; // [19:16]
        REG32 fm_rmx_gain_bit_8 : 3;      // [22:20]
        REG32 fm_lna_rload_bit_8 : 2;     // [24:23]
        REG32 fm_lna_gain_bit_8 : 2;      // [26:25]
        REG32 fm_lna_reg_ibit_8 : 3;      // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_FM_GAIN_TABLE_4_T;

//fm_gain_table_5
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_bt_gain_bit_b : 4; // [3:0]
        REG32 fm_rmx_gain_bit_b : 3;      // [6:4]
        REG32 fm_lna_rload_bit_b : 2;     // [8:7]
        REG32 fm_lna_gain_bit_b : 2;      // [10:9]
        REG32 fm_lna_reg_ibit_b : 3;      // [13:11]
        REG32 __15_14 : 2;
        REG32 fm_rxflt_bt_gain_bit_a : 4; // [19:16]
        REG32 fm_rmx_gain_bit_a : 3;      // [22:20]
        REG32 fm_lna_rload_bit_a : 2;     // [24:23]
        REG32 fm_lna_gain_bit_a : 2;      // [26:25]
        REG32 fm_lna_reg_ibit_a : 3;      // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_FM_GAIN_TABLE_5_T;

//fm_gain_table_6
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_bt_gain_bit_d : 4; // [3:0]
        REG32 fm_rmx_gain_bit_d : 3;      // [6:4]
        REG32 fm_lna_rload_bit_d : 2;     // [8:7]
        REG32 fm_lna_gain_bit_d : 2;      // [10:9]
        REG32 fm_lna_reg_ibit_d : 3;      // [13:11]
        REG32 __15_14 : 2;
        REG32 fm_rxflt_bt_gain_bit_c : 4; // [19:16]
        REG32 fm_rmx_gain_bit_c : 3;      // [22:20]
        REG32 fm_lna_rload_bit_c : 2;     // [24:23]
        REG32 fm_lna_gain_bit_c : 2;      // [26:25]
        REG32 fm_lna_reg_ibit_c : 3;      // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_FM_GAIN_TABLE_6_T;

//fm_gain_table_7
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_bt_gain_bit_f : 4; // [3:0]
        REG32 fm_rmx_gain_bit_f : 3;      // [6:4]
        REG32 fm_lna_rload_bit_f : 2;     // [8:7]
        REG32 fm_lna_gain_bit_f : 2;      // [10:9]
        REG32 fm_lna_reg_ibit_f : 3;      // [13:11]
        REG32 __15_14 : 2;
        REG32 fm_rxflt_bt_gain_bit_e : 4; // [19:16]
        REG32 fm_rmx_gain_bit_e : 3;      // [22:20]
        REG32 fm_lna_rload_bit_e : 2;     // [24:23]
        REG32 fm_lna_gain_bit_e : 2;      // [26:25]
        REG32 fm_lna_reg_ibit_e : 3;      // [29:27]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_RF_IF_FM_GAIN_TABLE_7_T;

//direct_gain_setting
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_agc_gain_reg : 4; // [3:0]
        REG32 fm_agc_gain_dr : 1;  // [4]
        REG32 __7_5 : 3;
        REG32 wf_agc_gain_reg : 4; // [11:8]
        REG32 wf_agc_gain_dr : 1;  // [12]
        REG32 __15_13 : 3;
        REG32 bt_agc_gain_reg : 4; // [19:16]
        REG32 bt_agc_gain_dr : 1;  // [20]
        REG32 __31_21 : 11;
    } b;
} REG_WCN_RF_IF_DIRECT_GAIN_SETTING_T;

//bt_rxflt_cal_bit_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_1 : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_1 : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_0 : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_0 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG0_T;

//bt_rxflt_cal_bit_reg1
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_3 : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_3 : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_2 : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_2 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG1_T;

//bt_rxflt_cal_bit_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_5 : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_5 : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_4 : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_4 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG2_T;

//bt_rxflt_cal_bit_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_7 : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_7 : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_6 : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_6 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG3_T;

//bt_rxflt_cal_bit_reg4
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_9 : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_9 : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_8 : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_8 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG4_T;

//bt_rxflt_cal_bit_reg5
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_b : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_b : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_a : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_a : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG5_T;

//bt_rxflt_cal_bit_reg6
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_d : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_d : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_c : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_c : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG6_T;

//bt_rxflt_cal_bit_reg7
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_f : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_f : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_e : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_e : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG7_T;

//bt_rxflt_cal_bit_reg8
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_d_lo : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_d_lo : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_c_lo : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_c_lo : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG8_T;

//bt_rxflt_cal_bit_reg9
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_f_lo : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_f_lo : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_e_lo : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_e_lo : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REG9_T;

//bt_rxflt_cal_bit_rega
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_d_hi : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_d_hi : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_c_hi : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_c_hi : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REGA_T;

//bt_rxflt_cal_bit_regb
typedef union {
    REG32 v;
    struct
    {
        REG32 bt_rxflt_cal_q_bit_f_hi : 8; // [7:0]
        REG32 bt_rxflt_cal_i_bit_f_hi : 8; // [15:8]
        REG32 bt_rxflt_cal_q_bit_e_hi : 8; // [23:16]
        REG32 bt_rxflt_cal_i_bit_e_hi : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_BT_RXFLT_CAL_BIT_REGB_T;

//wf_rxflt_cal_bit_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_1 : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_1 : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_0 : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_0 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG0_T;

//wf_rxflt_cal_bit_reg1
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_3 : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_3 : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_2 : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_2 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG1_T;

//wf_rxflt_cal_bit_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_5 : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_5 : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_4 : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_4 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG2_T;

//wf_rxflt_cal_bit_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_7 : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_7 : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_6 : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_6 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG3_T;

//wf_rxflt_cal_bit_reg4
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_9 : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_9 : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_8 : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_8 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG4_T;

//wf_rxflt_cal_bit_reg5
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_b : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_b : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_a : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_a : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG5_T;

//wf_rxflt_cal_bit_reg6
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_d : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_d : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_c : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_c : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG6_T;

//wf_rxflt_cal_bit_reg7
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_f : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_f : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_e : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_e : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG7_T;

//wf_rxflt_cal_bit_reg8
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_d_lo : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_d_lo : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_c_lo : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_c_lo : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG8_T;

//wf_rxflt_cal_bit_reg9
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_f_lo : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_f_lo : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_e_lo : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_e_lo : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REG9_T;

//wf_rxflt_cal_bit_rega
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_d_hi : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_d_hi : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_c_hi : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_c_hi : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REGA_T;

//wf_rxflt_cal_bit_regb
typedef union {
    REG32 v;
    struct
    {
        REG32 wf_rxflt_cal_q_bit_f_hi : 8; // [7:0]
        REG32 wf_rxflt_cal_i_bit_f_hi : 8; // [15:8]
        REG32 wf_rxflt_cal_q_bit_e_hi : 8; // [23:16]
        REG32 wf_rxflt_cal_i_bit_e_hi : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_WF_RXFLT_CAL_BIT_REGB_T;

//fm_rxflt_cal_bit_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_cal_q_bit_1 : 8; // [7:0]
        REG32 fm_rxflt_cal_i_bit_1 : 8; // [15:8]
        REG32 fm_rxflt_cal_q_bit_0 : 8; // [23:16]
        REG32 fm_rxflt_cal_i_bit_0 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_FM_RXFLT_CAL_BIT_REG0_T;

//fm_rxflt_cal_bit_reg1
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_cal_q_bit_3 : 8; // [7:0]
        REG32 fm_rxflt_cal_i_bit_3 : 8; // [15:8]
        REG32 fm_rxflt_cal_q_bit_2 : 8; // [23:16]
        REG32 fm_rxflt_cal_i_bit_2 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_FM_RXFLT_CAL_BIT_REG1_T;

//fm_rxflt_cal_bit_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_cal_q_bit_5 : 8; // [7:0]
        REG32 fm_rxflt_cal_i_bit_5 : 8; // [15:8]
        REG32 fm_rxflt_cal_q_bit_4 : 8; // [23:16]
        REG32 fm_rxflt_cal_i_bit_4 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_FM_RXFLT_CAL_BIT_REG2_T;

//fm_rxflt_cal_bit_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_cal_q_bit_7 : 8; // [7:0]
        REG32 fm_rxflt_cal_i_bit_7 : 8; // [15:8]
        REG32 fm_rxflt_cal_q_bit_6 : 8; // [23:16]
        REG32 fm_rxflt_cal_i_bit_6 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_FM_RXFLT_CAL_BIT_REG3_T;

//fm_rxflt_cal_bit_reg4
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_cal_q_bit_9 : 8; // [7:0]
        REG32 fm_rxflt_cal_i_bit_9 : 8; // [15:8]
        REG32 fm_rxflt_cal_q_bit_8 : 8; // [23:16]
        REG32 fm_rxflt_cal_i_bit_8 : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_FM_RXFLT_CAL_BIT_REG4_T;

//fm_rxflt_cal_bit_reg5
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_cal_q_bit_b : 8; // [7:0]
        REG32 fm_rxflt_cal_i_bit_b : 8; // [15:8]
        REG32 fm_rxflt_cal_q_bit_a : 8; // [23:16]
        REG32 fm_rxflt_cal_i_bit_a : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_FM_RXFLT_CAL_BIT_REG5_T;

//fm_rxflt_cal_bit_reg6
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_cal_q_bit_d : 8; // [7:0]
        REG32 fm_rxflt_cal_i_bit_d : 8; // [15:8]
        REG32 fm_rxflt_cal_q_bit_c : 8; // [23:16]
        REG32 fm_rxflt_cal_i_bit_c : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_FM_RXFLT_CAL_BIT_REG6_T;

//fm_rxflt_cal_bit_reg7
typedef union {
    REG32 v;
    struct
    {
        REG32 fm_rxflt_cal_q_bit_f : 8; // [7:0]
        REG32 fm_rxflt_cal_i_bit_f : 8; // [15:8]
        REG32 fm_rxflt_cal_q_bit_e : 8; // [23:16]
        REG32 fm_rxflt_cal_i_bit_e : 8; // [31:24]
    } b;
} REG_WCN_RF_IF_FM_RXFLT_CAL_BIT_REG7_T;

//test_buf
typedef union {
    REG32 v;
    struct
    {
        REG32 pll_test_out_en : 1; // [0]
        REG32 dac_out_en : 1;      // [1]
        REG32 tx_if_en : 1;        // [2]
        REG32 refclk_lvds_en : 1;  // [3]
        REG32 __31_4 : 28;
    } b;
} REG_WCN_RF_IF_TEST_BUF_T;

//ana_reserved
typedef union {
    REG32 v;
    struct
    {
        REG32 bw_rsvd_in : 16;   // [15:0]
        REG32 adpll_rsvd_in : 8; // [23:16]
        REG32 bw_rsvd_out : 8;   // [31:24], read only
    } b;
} REG_WCN_RF_IF_ANA_RESERVED_T;

//dig_reserved
typedef union {
    REG32 v;
    struct
    {
        REG32 dig_rsvd : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_RF_IF_DIG_RESERVED_T;

//new_add
typedef union {
    REG32 v;
    struct
    {
        REG32 txrf_capbank_en_reg : 1; // [0]
        REG32 txrf_capbank_en_dr : 1;  // [1]
        REG32 pll_reg_digi_bit : 4;    // [5:2]
        REG32 bt_dac_lp_mode2 : 2;     // [7:6]
        REG32 __31_8 : 24;
    } b;
} REG_WCN_RF_IF_NEW_ADD_T;

#endif
