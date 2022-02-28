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

#ifndef _RDA2720M_GLOBAL_H_
#define _RDA2720M_GLOBAL_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_global'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_GLOBAL_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_GLOBAL_BASE 0x50308C00

typedef volatile struct
{
    REG32 chip_id_low;          //0x00000000
    REG32 chip_id_high;         //0x00000004
    REG32 module_en0;           //0x00000008
    REG32 arm_clk_en0;          //0x0000000C
    REG32 rtc_clk_en0;          //0x00000010
    REG32 soft_rst0;            //0x00000014
    REG32 soft_rst1;            //0x00000018
    REG32 power_pd_sw;          //0x0000001C
    REG32 power_pd_hw;          //0x00000020
    REG32 soft_rst_hw;          //0x00000024
    REG32 reserved_reg1;        //0x00000028
    REG32 reserved_reg2;        //0x0000002C
    REG32 reserved_reg3;        //0x00000030
    REG32 dcdc_clk_reg0;        //0x00000034
    REG32 dcdc_core_reg0;       //0x00000038
    REG32 dcdc_core_reg1;       //0x0000003C
    REG32 dcdc_core_reg2;       //0x00000040
    REG32 dcdc_core_vol;        //0x00000044
    REG32 dcdc_gen_reg0;        //0x00000048
    REG32 dcdc_gen_reg1;        //0x0000004C
    REG32 dcdc_gen_reg2;        //0x00000050
    REG32 dcdc_gen_vol;         //0x00000054
    REG32 dcdc_wpa_reg0;        //0x00000058
    REG32 dcdc_wpa_reg1;        //0x0000005C
    REG32 dcdc_wpa_reg2;        //0x00000060
    REG32 dcdc_wpa_vol;         //0x00000064
    REG32 dcdc_wpa_dcm_hw;      //0x00000068
    REG32 dcdc_ch_ctrl;         //0x0000006C
    REG32 reserved_reg4;        //0x00000070
    REG32 reserved_reg5;        //0x00000074
    REG32 reserved_reg6;        //0x00000078
    REG32 reserved_reg7;        //0x0000007C
    REG32 reserved_reg8;        //0x00000080
    REG32 ldo_ana_reg0;         //0x00000084
    REG32 ldo_ana_reg1;         //0x00000088
    REG32 reserved_reg9;        //0x0000008C
    REG32 reserved_reg10;       //0x00000090
    REG32 ldo_rf15_reg0;        //0x00000094
    REG32 ldo_rf15_reg1;        //0x00000098
    REG32 reserved_reg11;       //0x0000009C
    REG32 reserved_reg12;       //0x000000A0
    REG32 ldo_camd_reg0;        //0x000000A4
    REG32 ldo_camd_reg1;        //0x000000A8
    REG32 ldo_con_reg0;         //0x000000AC
    REG32 ldo_con_reg1;         //0x000000B0
    REG32 ldo_mem_reg0;         //0x000000B4
    REG32 ldo_mem_reg1;         //0x000000B8
    REG32 ldo_sim0_reg0;        //0x000000BC
    REG32 ldo_sim0_pd_reg;      //0x000000C0
    REG32 ldo_sim0_reg1;        //0x000000C4
    REG32 ldo_sim1_reg0;        //0x000000C8
    REG32 ldo_sim1_pd_reg;      //0x000000CC
    REG32 ldo_sim1_reg1;        //0x000000D0
    REG32 reserved_reg13;       //0x000000D4
    REG32 reserved_reg14;       //0x000000D8
    REG32 reserved_reg15;       //0x000000DC
    REG32 ldo_cama_reg0;        //0x000000E0
    REG32 ldo_cama_reg1;        //0x000000E4
    REG32 ldo_lcd_reg0;         //0x000000E8
    REG32 ldo_lcd_reg1;         //0x000000EC
    REG32 ldo_mmc_reg0;         //0x000000F0
    REG32 ldo_mmc_pd_reg;       //0x000000F4
    REG32 ldo_mmc_reg1;         //0x000000F8
    REG32 ldo_sd_reg0;          //0x000000FC
    REG32 ldo_sd_pd_reg;        //0x00000100
    REG32 ldo_sd_reg1;          //0x00000104
    REG32 ldo_ddr12_reg0;       //0x00000108
    REG32 ldo_ddr12_pd_reg;     //0x0000010C
    REG32 ldo_ddr12_reg1;       //0x00000110
    REG32 ldo_vdd28_reg0;       //0x00000114
    REG32 ldo_vdd28_reg1;       //0x00000118
    REG32 ldo_spimem_reg0;      //0x0000011C
    REG32 ldo_spimem_reg1;      //0x00000120
    REG32 ldo_dcxo_reg0;        //0x00000124
    REG32 ldo_dcxo_reg1;        //0x00000128
    REG32 ldo_usb_reg0;         //0x0000012C
    REG32 ldo_usb_pd_reg;       //0x00000130
    REG32 ldo_usb_reg1;         //0x00000134
    REG32 reserved_reg17;       //0x00000138
    REG32 reserved_reg18;       //0x0000013C
    REG32 reserved_reg19;       //0x00000140
    REG32 reserved_reg20;       //0x00000144
    REG32 ldo_trim_reg;         //0x00000148
    REG32 ldo_rtc_ctrl;         //0x0000014C
    REG32 ldo_ch_ctrl;          //0x00000150
    REG32 reserved_reg23;       //0x00000154
    REG32 reserved_reg24;       //0x00000158
    REG32 reserved_reg25;       //0x0000015C
    REG32 reserved_reg26;       //0x00000160
    REG32 reserved_reg27;       //0x00000164
    REG32 slp_ctrl;             //0x00000168
    REG32 slp_dcdc_pd_ctrl;     //0x0000016C
    REG32 slp_ldo_pd_ctrl0;     //0x00000170
    REG32 slp_ldo_pd_ctrl1;     //0x00000174
    REG32 slp_dcdc_lp_ctrl;     //0x00000178
    REG32 slp_ldo_lp_ctrl0;     //0x0000017C
    REG32 slp_ldo_lp_ctrl1;     //0x00000180
    REG32 dcdc_core_slp_ctrl0;  //0x00000184
    REG32 dcdc_core_slp_ctrl1;  //0x00000188
    REG32 dcdc_xtl_en0;         //0x0000018C
    REG32 reseved_dcdc_xtl_en4; //0x00000190
    REG32 ldo_xtl_en0;          //0x00000194
    REG32 ldo_xtl_en1;          //0x00000198
    REG32 ldo_xtl_en2;          //0x0000019C
    REG32 ldo_xtl_en3;          //0x000001A0
    REG32 ldo_xtl_en4;          //0x000001A4
    REG32 ldo_xtl_en5;          //0x000001A8
    REG32 ldo_xtl_en6;          //0x000001AC
    REG32 ldo_xtl_en7;          //0x000001B0
    REG32 ldo_xtl_en8;          //0x000001B4
    REG32 ldo_xtl_en9;          //0x000001B8
    REG32 ldo_xtl_en10;         //0x000001BC
    REG32 reserved_reg30;       //0x000001C0
    REG32 reserved_reg31;       //0x000001C4
    REG32 reserved_reg32;       //0x000001C8
    REG32 reserved_reg_core;    //0x000001CC
    REG32 reserved_reg_rtc;     //0x000001D0
    REG32 bg_ctrl;              //0x000001D4
    REG32 dcdc_vlg_sel;         //0x000001D8
    REG32 ldo_vlg_sel0;         //0x000001DC
    REG32 clk32kless_ctrl0;     //0x000001E0
    REG32 clk32kless_ctrl1;     //0x000001E4
    REG32 xtl_wait_ctrl0;       //0x000001E8
    REG32 rgb_ctrl;             //0x000001EC
    REG32 ib_ctrl;              //0x000001F0
    REG32 flash_ctrl;           //0x000001F4
    REG32 kpled_ctrl0;          //0x000001F8
    REG32 kpled_ctrl1;          //0x000001FC
    REG32 vibr_ctrl0;           //0x00000200
    REG32 vibr_ctrl1;           //0x00000204
    REG32 audio_ctrl0;          //0x00000208
    REG32 chgr_ctrl0;           //0x0000020C
    REG32 chgr_ctrl1;           //0x00000210
    REG32 chgr_status;          //0x00000214
    REG32 chgr_det_fgu_ctrl;    //0x00000218
    REG32 ovlo_ctrl;            //0x0000021C
    REG32 mixed_ctrl;           //0x00000220
    REG32 por_rst_monitor;      //0x00000224
    REG32 wdg_rst_monitor;      //0x00000228
    REG32 por_pin_rst_monitor;  //0x0000022C
    REG32 por_src_flag;         //0x00000230
    REG32 por_off_flag;         //0x00000234
    REG32 por_7s_ctrl;          //0x00000238
    REG32 hwrst_rtc;            //0x0000023C
    REG32 arch_en;              //0x00000240
    REG32 mcu_wr_prot_value;    //0x00000244
    REG32 pwr_wr_prot_value;    //0x00000248
    REG32 smpl_ctrl0;           //0x0000024C
    REG32 smpl_ctrl1;           //0x00000250
    REG32 rtc_rst0;             //0x00000254
    REG32 rtc_rst1;             //0x00000258
    REG32 rtc_rst2;             //0x0000025C
    REG32 rtc_clk_stop;         //0x00000260
    REG32 vbat_drop_cnt;        //0x00000264
    REG32 swrst_ctrl0;          //0x00000268
    REG32 swrst_ctrl1;          //0x0000026C
    REG32 otp_ctrl;             //0x00000270
    REG32 free_timer_low;       //0x00000274
    REG32 free_timer_high;      //0x00000278
    REG32 vol_tune_ctrl_core;   //0x0000027C
} HWP_RDA2720M_GLOBAL_T;

#define hwp_rda2720mGlobal ((HWP_RDA2720M_GLOBAL_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_GLOBAL_BASE))

//CHIP_ID_LOW
typedef union {
    REG32 v;
    struct
    {
        REG32 chip_ip_low : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_CHIP_ID_LOW_T;

//CHIP_ID_HIGH
typedef union {
    REG32 v;
    struct
    {
        REG32 chip_id_high : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_CHIP_ID_HIGH_T;

//MODULE_EN0
typedef union {
    REG32 v;
    struct
    {
        REG32 cal_en : 1;    // [0]
        REG32 rtc_en : 1;    // [1]
        REG32 wdg_en : 1;    // [2]
        REG32 eic_en : 1;    // [3]
        REG32 aud_en : 1;    // [4]
        REG32 adc_en : 1;    // [5]
        REG32 efs_en : 1;    // [6]
        REG32 fgu_en : 1;    // [7]
        REG32 pinreg_en : 1; // [8]
        REG32 bltc_en : 1;   // [9]
        REG32 psm_en : 1;    // [10]
        REG32 __11_11 : 1;
        REG32 tmr_en : 1; // [12]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_GLOBAL_MODULE_EN0_T;

//ARM_CLK_EN0
typedef union {
    REG32 v;
    struct
    {
        REG32 clk_aud_if_en : 1;      // [0]
        REG32 clk_aud_if_6p5m_en : 1; // [1]
        REG32 clk_cal_en : 1;         // [2]
        REG32 clk_cal_src_sel : 2;    // [4:3]
        REG32 clk_auxadc_en : 1;      // [5]
        REG32 clk_auxad_en : 1;       // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_ARM_CLK_EN0_T;

//RTC_CLK_EN0
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_arch_en : 1; // [0]
        REG32 rtc_rtc_en : 1;  // [1]
        REG32 rtc_wdg_en : 1;  // [2]
        REG32 rtc_eic_en : 1;  // [3]
        REG32 __5_4 : 2;
        REG32 rtc_fgu_en : 1;  // [6]
        REG32 rtc_bltc_en : 1; // [7]
        REG32 __10_8 : 3;
        REG32 rtc_efs_en : 1;   // [11]
        REG32 rtc_flash_en : 1; // [12]
        REG32 rtc_tmr_en : 1;   // [13]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_GLOBAL_RTC_CLK_EN0_T;

//SOFT_RST0
typedef union {
    REG32 v;
    struct
    {
        REG32 cal_soft_rst : 1;    // [0]
        REG32 rtc_soft_rst : 1;    // [1]
        REG32 wdg_soft_rst : 1;    // [2]
        REG32 eic_soft_rst : 1;    // [3]
        REG32 fgu_soft_rst : 1;    // [4]
        REG32 psm_soft_rst : 1;    // [5]
        REG32 adc_soft_rst : 1;    // [6]
        REG32 efs_soft_rst : 1;    // [7]
        REG32 aud_if_soft_rst : 1; // [8]
        REG32 bltc_soft_rst : 1;   // [9]
        REG32 __11_10 : 2;
        REG32 audtx_soft_rst : 1; // [12]
        REG32 audrx_soft_rst : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_GLOBAL_SOFT_RST0_T;

//SOFT_RST1
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 tmr_soft_rst : 1; // [1]
        REG32 __31_2 : 30;
    } b;
} REG_RDA2720M_GLOBAL_SOFT_RST1_T;

//POWER_PD_SW
typedef union {
    REG32 v;
    struct
    {
        REG32 bg_pd : 1;        // [0]
        REG32 ldo_vdd28_pd : 1; // [1]
        REG32 ldo_ana_pd : 1;   // [2]
        REG32 ldo_mem_pd : 1;   // [3]
        REG32 osc3m_en : 1;     // [4]
        REG32 dcdc_core_pd : 1; // [5]
        REG32 __6_6 : 1;
        REG32 dcdc_gen_pd : 1; // [7]
        REG32 ldo_cp_pd : 1;   // [8]
        REG32 ldo_emm_pd : 1;  // [9]
        REG32 ldo_dcxo_pd : 1; // [10]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_GLOBAL_POWER_PD_SW_T;

//POWER_PD_HW
typedef union {
    REG32 v;
    struct
    {
        REG32 pwr_off_seq_en : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_POWER_PD_HW_T;

//SOFT_RST_HW
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_soft_rst : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_SOFT_RST_HW_T;

//DCDC_CLK_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 osc3m_freq : 4;       // [3:0]
        REG32 dcdc_gen_clk_rst : 1; // [4]
        REG32 __6_5 : 2;
        REG32 clkout_sel : 3;      // [9:7]
        REG32 clkout_uniphase : 1; // [10]
        REG32 clk3m_out_en : 1;    // [11]
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_CLK_REG0_T;

//DCDC_CORE_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 zx_offset_vcore : 2;  // [1:0]
        REG32 sr_ls_vcore : 2;      // [3:2]
        REG32 sr_hs_vcore : 2;      // [5:4]
        REG32 slope_vcore : 2;      // [7:6]
        REG32 rcomp_vcore : 2;      // [9:8]
        REG32 pfm_vh_vcore : 2;     // [11:10]
        REG32 curses_r_vcore : 2;   // [13:12]
        REG32 curlimit_r_vcore : 2; // [15:14]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_CORE_REG0_T;

//DCDC_CORE_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 anriting_en_vcore : 1; // [0]
        REG32 force_pwm_vcore : 1;   // [1]
        REG32 zx_disable_vcore : 1;  // [2]
        REG32 votrim_vcore : 3;      // [5:3]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_CORE_REG1_T;

//DCDC_CORE_REG2
typedef union {
    REG32 v;
    struct
    {
        REG32 div_base_vcore : 6;   // [5:0]
        REG32 phase_sel_vcore : 6;  // [11:6]
        REG32 div_clk_vcore_en : 1; // [12]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_CORE_REG2_T;

//DCDC_CORE_VOL
typedef union {
    REG32 v;
    struct
    {
        REG32 vosel_vcore : 9; // [8:0]
        REG32 __31_9 : 23;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_CORE_VOL_T;

//DCDC_GEN_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 zx_offset_vgen : 2;  // [1:0]
        REG32 sr_ls_vgen : 2;      // [3:2]
        REG32 sr_hs_vgen : 2;      // [5:4]
        REG32 slope_vgen : 2;      // [7:6]
        REG32 rcomp_vgen : 2;      // [9:8]
        REG32 pfm_vh_vgen : 2;     // [11:10]
        REG32 curses_r_vgen : 2;   // [13:12]
        REG32 curlimit_r_vgen : 2; // [15:14]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_GEN_REG0_T;

//DCDC_GEN_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 anriting_en_vgen : 1; // [0]
        REG32 force_pwm_vgen : 1;   // [1]
        REG32 maxduty_sel_vgen : 1; // [2]
        REG32 zx_disable_vgen : 1;  // [3]
        REG32 __31_4 : 28;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_GEN_REG1_T;

//DCDC_GEN_REG2
typedef union {
    REG32 v;
    struct
    {
        REG32 div_base_vgen : 6;   // [5:0]
        REG32 phase_sel_vgen : 6;  // [11:6]
        REG32 div_clk_vgen_en : 1; // [12]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_GEN_REG2_T;

//DCDC_GEN_VOL
typedef union {
    REG32 v;
    struct
    {
        REG32 vosel_vgen : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_GEN_VOL_T;

//DCDC_WPA_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 sr_hs_vpa : 2;          // [1:0]
        REG32 sawtooth_slope_vpa : 2; // [3:2]
        REG32 rcomp3_vpa : 2;         // [5:4]
        REG32 rcomp2_vpa : 2;         // [7:6]
        REG32 pfm_threshold_vpa : 2;  // [9:8]
        REG32 ccomp3_vpa : 2;         // [11:10]
        REG32 curses_m_vpa : 2;       // [13:12]
        REG32 curlimit_r_vpa : 2;     // [15:14]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_WPA_REG0_T;

//DCDC_WPA_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 maxduty_sel_vpa : 1;      // [0]
        REG32 dvs_on_vpa : 1;           // [1]
        REG32 bypass_threshold_vpa : 2; // [3:2]
        REG32 bypass_forceon_vpa : 1;   // [4]
        REG32 bypass_disable_vpa : 1;   // [5]
        REG32 apc_ramp_sel_vpa : 1;     // [6]
        REG32 apc_enable_vpa : 1;       // [7]
        REG32 anriting_en_vpa : 1;      // [8]
        REG32 zx_offset_vpa : 2;        // [10:9]
        REG32 votrim_vpa : 3;           // [13:11]
        REG32 sr_ls_vpa : 2;            // [15:14]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_WPA_REG1_T;

//DCDC_WPA_REG2
typedef union {
    REG32 v;
    struct
    {
        REG32 pd_buck_vpa : 1;         // [0]
        REG32 sawtoothcal_rst_vpa : 1; // [1]
        REG32 zx_disable_vpa : 1;      // [2]
        REG32 div_base_vpa : 6;        // [8:3]
        REG32 phase_sel_vpa : 6;       // [14:9]
        REG32 div_clk_vpa_en : 1;      // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_WPA_REG2_T;

//DCDC_WPA_VOL
typedef union {
    REG32 v;
    struct
    {
        REG32 vosel_vpa : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_WPA_VOL_T;

//DCDC_WPA_DCM_HW
typedef union {
    REG32 v;
    struct
    {
        REG32 force_pwm_vpa : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_WPA_DCM_HW_T;

//DCDC_CH_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dcdc_auxtrim_sel : 3; // [2:0]
        REG32 __31_3 : 29;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_CH_CTRL_T;

//LDO_ANA_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_ana_cl_adj : 1;   // [1]
        REG32 ldo_ana_shpt_adj : 1; // [2]
        REG32 ldo_ana_stb : 2;      // [4:3]
        REG32 ldo_ana_bp : 1;       // [5]
        REG32 ldo_ana_cap_sel : 1;  // [6]
        REG32 ldo_ana_shpt_pd : 1;  // [7]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_GLOBAL_LDO_ANA_REG0_T;

//LDO_ANA_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_ana_v : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_LDO_ANA_REG1_T;

//LDO_RF15_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_rf15_pd : 1;       // [0]
        REG32 ldo_rf15_cl_adj : 1;   // [1]
        REG32 ldo_rf15_shpt_adj : 1; // [2]
        REG32 ldo_rf15_stb : 2;      // [4:3]
        REG32 ldo_rf15_bp : 1;       // [5]
        REG32 ldo_rf15_cap_sel : 1;  // [6]
        REG32 ldo_rf15_shpt_pd : 1;  // [7]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_GLOBAL_LDO_RF15_REG0_T;

//LDO_RF15_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_rf15_v : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_LDO_RF15_REG1_T;

//LDO_CAMD_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_camd_pd : 1;       // [0]
        REG32 ldo_camd_cl_adj : 1;   // [1]
        REG32 ldo_camd_shpt_adj : 1; // [2]
        REG32 ldo_camd_stb : 2;      // [4:3]
        REG32 ldo_camd_bp : 1;       // [5]
        REG32 ldo_camd_cap_sel : 1;  // [6]
        REG32 ldo_camd_shpt_pd : 1;  // [7]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_GLOBAL_LDO_CAMD_REG0_T;

//LDO_CAMD_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_camd_v : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_LDO_CAMD_REG1_T;

//LDO_CON_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_con_pd : 1;       // [0]
        REG32 ldo_con_cl_adj : 1;   // [1]
        REG32 ldo_con_shpt_adj : 1; // [2]
        REG32 ldo_con_stb : 2;      // [4:3]
        REG32 ldo_con_bp : 1;       // [5]
        REG32 ldo_con_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_CON_REG0_T;

//LDO_CON_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_con_v : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_LDO_CON_REG1_T;

//LDO_MEM_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_mem_cl_adj : 1;   // [1]
        REG32 ldo_mem_shpt_adj : 1; // [2]
        REG32 ldo_mem_stb : 2;      // [4:3]
        REG32 ldo_mem_bp : 1;       // [5]
        REG32 ldo_mem_cap_sel : 1;  // [6]
        REG32 ldo_mem_shpt_pd : 1;  // [7]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_GLOBAL_LDO_MEM_REG0_T;

//LDO_MEM_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_mem_v : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_LDO_MEM_REG1_T;

//LDO_SIM0_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_sim0_cl_adj : 1;   // [1]
        REG32 ldo_sim0_shpt_adj : 1; // [2]
        REG32 ldo_sim0_stb : 2;      // [4:3]
        REG32 ldo_sim0_cap_sel : 1;  // [5]
        REG32 ldo_sim0_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SIM0_REG0_T;

//LDO_SIM0_PD_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_sim0_pd : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SIM0_PD_REG_T;

//LDO_SIM0_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_sim0_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SIM0_REG1_T;

//LDO_SIM1_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_sim1_cl_adj : 1;   // [1]
        REG32 ldo_sim1_shpt_adj : 1; // [2]
        REG32 ldo_sim1_stb : 2;      // [4:3]
        REG32 ldo_sim1_cap_sel : 1;  // [5]
        REG32 ldo_sim1_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SIM1_REG0_T;

//LDO_SIM1_PD_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_sim1_pd : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SIM1_PD_REG_T;

//LDO_SIM1_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_sim1_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SIM1_REG1_T;

//LDO_CAMA_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_cama_pd : 1;       // [0]
        REG32 ldo_cama_cl_adj : 1;   // [1]
        REG32 ldo_cama_shpt_adj : 1; // [2]
        REG32 ldo_cama_stb : 2;      // [4:3]
        REG32 ldo_cama_cap_sel : 1;  // [5]
        REG32 ldo_cama_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_CAMA_REG0_T;

//LDO_CAMA_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_cama_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_CAMA_REG1_T;

//LDO_LCD_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_lcd_pd : 1;       // [0]
        REG32 ldo_lcd_cl_adj : 1;   // [1]
        REG32 ldo_lcd_shpt_adj : 1; // [2]
        REG32 ldo_lcd_stb : 2;      // [4:3]
        REG32 ldo_lcd_cap_sel : 1;  // [5]
        REG32 ldo_lcd_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_LCD_REG0_T;

//LDO_LCD_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_lcd_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_LCD_REG1_T;

//LDO_MMC_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_mmc_cl_adj : 1;   // [1]
        REG32 ldo_mmc_shpt_adj : 1; // [2]
        REG32 ldo_mmc_stb : 2;      // [4:3]
        REG32 ldo_mmc_cap_sel : 1;  // [5]
        REG32 ldo_mmc_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_MMC_REG0_T;

//LDO_MMC_PD_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_mmc_pd : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_LDO_MMC_PD_REG_T;

//LDO_MMC_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_mmc_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_MMC_REG1_T;

//LDO_SD_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_vio18_cl_adj : 1;   // [1]
        REG32 ldo_vio18_shpt_adj : 1; // [2]
        REG32 ldo_vio18_stb : 2;      // [4:3]
        REG32 ldo_vio18_cap_sel : 1;  // [5]
        REG32 ldo_vio18_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SD_REG0_T;

//LDO_SD_PD_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_vio18_pd : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SD_PD_REG_T;

//LDO_SD_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_vio18_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SD_REG1_T;

//LDO_DDR12_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_ddr12_cl_adj : 1;   // [1]
        REG32 ldo_ddr12_shpt_adj : 1; // [2]
        REG32 ldo_ddr12_stb : 2;      // [4:3]
        REG32 ldo_ddr12_cap_sel : 1;  // [5]
        REG32 ldo_ddr12_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_DDR12_REG0_T;

//LDO_DDR12_PD_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_ddr12_pd : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_LDO_DDR12_PD_REG_T;

//LDO_DDR12_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_ddr12_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_DDR12_REG1_T;

//LDO_VDD28_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_vdd28_cl_adj : 1;   // [1]
        REG32 ldo_vdd28_shpt_adj : 1; // [2]
        REG32 ldo_vdd28_stb : 2;      // [4:3]
        REG32 ldo_vdd28_cap_sel : 1;  // [5]
        REG32 ldo_vdd28_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_VDD28_REG0_T;

//LDO_VDD28_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_vdd28_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_VDD28_REG1_T;

//LDO_SPIMEM_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_spimem_pd : 1;       // [0]
        REG32 ldo_spimem_cl_adj : 1;   // [1]
        REG32 ldo_spimem_shpt_adj : 1; // [2]
        REG32 ldo_spimem_stb : 2;      // [4:3]
        REG32 ldo_spimem_cap_sel : 1;  // [5]
        REG32 ldo_spimem_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SPIMEM_REG0_T;

//LDO_SPIMEM_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_spimem_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_SPIMEM_REG1_T;

//LDO_DCXO_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_dcxo_cl_adj : 1;   // [1]
        REG32 ldo_dcxo_shpt_adj : 1; // [2]
        REG32 ldo_dcxo_stb : 2;      // [4:3]
        REG32 ldo_dcxo_cap_sel : 1;  // [5]
        REG32 ldo_dcxo_shpt_pd : 1;  // [6]
        REG32 ldo_dcxo_trim : 5;     // [11:7]
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_GLOBAL_LDO_DCXO_REG0_T;

//LDO_DCXO_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_dcxo_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_DCXO_REG1_T;

//LDO_USB_REG0
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 ldo_usb33_cl_adj : 1;   // [1]
        REG32 ldo_usb33_shpt_adj : 1; // [2]
        REG32 ldo_usb33_stb : 2;      // [4:3]
        REG32 ldo_usb33_cap_sel : 1;  // [5]
        REG32 ldo_usb33_shpt_pd : 1;  // [6]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_USB_REG0_T;

//LDO_USB_PD_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_usb33_pd : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_LDO_USB_PD_REG_T;

//LDO_USB_REG1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_usb33_v : 7; // [6:0]
        REG32 __31_7 : 25;
    } b;
} REG_RDA2720M_GLOBAL_LDO_USB_REG1_T;

//LDO_TRIM_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_trim_a : 5; // [4:0]
        REG32 ldo_trim_b : 5; // [9:5]
        REG32 __31_10 : 22;
    } b;
} REG_RDA2720M_GLOBAL_LDO_TRIM_REG_T;

//LDO_RTC_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 vbatbk_v : 2;    // [1:0]
        REG32 ldo_rtc_v : 2;   // [3:2]
        REG32 ldo_rtc_cal : 5; // [8:4]
        REG32 __31_9 : 23;
    } b;
} REG_RDA2720M_GLOBAL_LDO_RTC_CTRL_T;

//LDO_CH_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_cal : 3; // [2:0]
        REG32 __4_3 : 2;
        REG32 ldo_cal1 : 3; // [7:5]
        REG32 ldo_cal2 : 3; // [10:8]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_GLOBAL_LDO_CH_CTRL_T;

//SLP_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 slp_ldo_pd_en : 1; // [0]
        REG32 slp_io_en : 1;     // [1]
        REG32 ldo_xtl_en : 1;    // [2]
        REG32 __31_3 : 29;
    } b;
} REG_RDA2720M_GLOBAL_SLP_CTRL_T;

//SLP_DCDC_PD_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 slp_vddio1v8_pd_en : 1;   // [1]
        REG32 slp_dcdcwpa_pd_en : 1;    // [2]
        REG32 slp_dcdccore_drop_en : 1; // [3]
        REG32 slp_dcdccore_pd_en : 1;   // [4]
        REG32 __5_5 : 1;
        REG32 slp_dcdccore_pu_rstn_th : 6; // [11:6]
        REG32 slp_dcdccore_pd_rstn_th : 4; // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_SLP_DCDC_PD_CTRL_T;

//SLP_LDO_PD_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 slp_ldosim1_pd_en : 1; // [0]
        REG32 __1_1 : 1;
        REG32 slp_ldocama_pd_en : 1;   // [2]
        REG32 slp_ldocamd_pd_en : 1;   // [3]
        REG32 slp_ldocamio_pd_en : 1;  // [4]
        REG32 slp_ldolcd_pd_en : 1;    // [5]
        REG32 slp_ldousb33_pd_en : 1;  // [6]
        REG32 slp_ldoddr12_pd_en : 1;  // [7]
        REG32 slp_ldovio18_pd_en : 1;  // [8]
        REG32 slp_ldovdd28_pd_en : 1;  // [9]
        REG32 slp_ldospimem_pd_en : 1; // [10]
        REG32 slp_ldodcxo_pd_en : 1;   // [11]
        REG32 slp_ldommc_pd_en : 1;    // [12]
        REG32 __13_13 : 1;
        REG32 slp_ldorf15_pd_en : 1; // [14]
        REG32 __31_15 : 17;
    } b;
} REG_RDA2720M_GLOBAL_SLP_LDO_PD_CTRL0_T;

//SLP_LDO_PD_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 slp_ldomem_pd_en : 1;  // [0]
        REG32 slp_ldoana_pd_en : 1;  // [1]
        REG32 slp_ldosim0_pd_en : 1; // [2]
        REG32 slp_ldocon_pd_en : 1;  // [3]
        REG32 slp_ldocp_pd_en : 1;   // [4]
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_GLOBAL_SLP_LDO_PD_CTRL1_T;

//SLP_DCDC_LP_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 slp_dcdcwpa_lp_en : 1; // [0]
        REG32 slp_dcdcgen_lp_en : 1; // [1]
        REG32 __3_2 : 2;
        REG32 slp_dcdccore_lp_en : 1; // [4]
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_GLOBAL_SLP_DCDC_LP_CTRL_T;

//SLP_LDO_LP_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 slp_ldosim1_lp_en : 1; // [0]
        REG32 __1_1 : 1;
        REG32 slp_ldocama_lp_en : 1;   // [2]
        REG32 slp_ldocamd_lp_en : 1;   // [3]
        REG32 slp_ldocamio_lp_en : 1;  // [4]
        REG32 slp_ldolcd_lp_en : 1;    // [5]
        REG32 slp_ldousb33_lp_en : 1;  // [6]
        REG32 slp_ldoddr12_lp_en : 1;  // [7]
        REG32 slp_ldovio18_lp_en : 1;  // [8]
        REG32 slp_ldovdd28_lp_en : 1;  // [9]
        REG32 slp_ldospimem_lp_en : 1; // [10]
        REG32 slp_ldodcxo_lp_en : 1;   // [11]
        REG32 slp_ldommc_lp_en : 1;    // [12]
        REG32 __13_13 : 1;
        REG32 slp_ldorf15_lp_en : 1; // [14]
        REG32 __31_15 : 17;
    } b;
} REG_RDA2720M_GLOBAL_SLP_LDO_LP_CTRL0_T;

//SLP_LDO_LP_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 slp_ldomem_lp_en : 1;  // [0]
        REG32 slp_ldoana_lp_en : 1;  // [1]
        REG32 slp_ldosim0_lp_en : 1; // [2]
        REG32 slp_ldocon_lp_en : 1;  // [3]
        REG32 __31_4 : 28;
    } b;
} REG_RDA2720M_GLOBAL_SLP_LDO_LP_CTRL1_T;

//DCDC_CORE_SLP_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 dcdc_core_slp_step_en : 1; // [0]
        REG32 __2_1 : 2;
        REG32 dcdc_core_slp_step_vol : 5;   // [7:3]
        REG32 dcdc_core_slp_step_num : 4;   // [11:8]
        REG32 dcdc_core_slp_step_delay : 2; // [13:12]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_CORE_SLP_CTRL0_T;

//DCDC_CORE_SLP_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 dcdc_core_vosel_ds_sw : 9; // [8:0]
        REG32 __31_9 : 23;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_CORE_SLP_CTRL1_T;

//DCDC_XTL_EN0
typedef union {
    REG32 v;
    struct
    {
        REG32 dcdc_wpa_ext_xtl3_en : 1; // [0]
        REG32 dcdc_wpa_ext_xtl2_en : 1; // [1]
        REG32 dcdc_wpa_ext_xtl1_en : 1; // [2]
        REG32 dcdc_wpa_ext_xtl0_en : 1; // [3]
        REG32 dcdc_gen_ext_xtl3_en : 1; // [4]
        REG32 dcdc_gen_ext_xtl2_en : 1; // [5]
        REG32 dcdc_gen_ext_xtl1_en : 1; // [6]
        REG32 dcdc_gen_ext_xtl0_en : 1; // [7]
        REG32 __11_8 : 4;
        REG32 dcdc_core_ext_xtl3_en : 1; // [12]
        REG32 dcdc_core_ext_xtl2_en : 1; // [13]
        REG32 dcdc_core_ext_xtl1_en : 1; // [14]
        REG32 dcdc_core_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_XTL_EN0_T;

//LDO_XTL_EN0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_vdd28_ext_xtl3_en : 1; // [0]
        REG32 ldo_vdd28_ext_xtl2_en : 1; // [1]
        REG32 ldo_vdd28_ext_xtl1_en : 1; // [2]
        REG32 ldo_vdd28_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_dcxo_ext_xtl3_en : 1; // [12]
        REG32 ldo_dcxo_ext_xtl2_en : 1; // [13]
        REG32 ldo_dcxo_ext_xtl1_en : 1; // [14]
        REG32 ldo_dcxo_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN0_T;

//LDO_XTL_EN1
typedef union {
    REG32 v;
    struct
    {
        REG32 __11_0 : 12;
        REG32 ldo_rf15_ext_xtl3_en : 1; // [12]
        REG32 ldo_rf15_ext_xtl2_en : 1; // [13]
        REG32 ldo_rf15_ext_xtl1_en : 1; // [14]
        REG32 ldo_rf15_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN1_T;

//LDO_XTL_EN2
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_sim1_ext_xtl3_en : 1; // [0]
        REG32 ldo_sim1_ext_xtl2_en : 1; // [1]
        REG32 ldo_sim1_ext_xtl1_en : 1; // [2]
        REG32 ldo_sim1_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_sim0_ext_xtl3_en : 1; // [12]
        REG32 ldo_sim0_ext_xtl2_en : 1; // [13]
        REG32 ldo_sim0_ext_xtl1_en : 1; // [14]
        REG32 ldo_sim0_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN2_T;

//LDO_XTL_EN3
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_mem_ext_xtl3_en : 1; // [0]
        REG32 ldo_mem_ext_xtl2_en : 1; // [1]
        REG32 ldo_mem_ext_xtl1_en : 1; // [2]
        REG32 ldo_mem_ext_xtl0_en : 1; // [3]
        REG32 __31_4 : 28;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN3_T;

//LDO_XTL_EN4
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_camio_ext_xtl3_en : 1; // [0]
        REG32 ldo_camio_ext_xtl2_en : 1; // [1]
        REG32 ldo_camio_ext_xtl1_en : 1; // [2]
        REG32 ldo_camio_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_lcd_ext_xtl3_en : 1; // [12]
        REG32 ldo_lcd_ext_xtl2_en : 1; // [13]
        REG32 ldo_lcd_ext_xtl1_en : 1; // [14]
        REG32 ldo_lcd_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN4_T;

//LDO_XTL_EN5
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_camd_ext_xtl3_en : 1; // [0]
        REG32 ldo_camd_ext_xtl2_en : 1; // [1]
        REG32 ldo_camd_ext_xtl1_en : 1; // [2]
        REG32 ldo_camd_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_cama_ext_xtl3_en : 1; // [12]
        REG32 ldo_cama_ext_xtl2_en : 1; // [13]
        REG32 ldo_cama_ext_xtl1_en : 1; // [14]
        REG32 ldo_cama_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN5_T;

//LDO_XTL_EN6
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_vio18_ext_xtl3_en : 1; // [0]
        REG32 ldo_vio18_ext_xtl2_en : 1; // [1]
        REG32 ldo_vio18_ext_xtl1_en : 1; // [2]
        REG32 ldo_vio18_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_ddr12_ext_xtl3_en : 1; // [12]
        REG32 ldo_ddr12_ext_xtl2_en : 1; // [13]
        REG32 ldo_ddr12_ext_xtl1_en : 1; // [14]
        REG32 ldo_ddr12_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN6_T;

//LDO_XTL_EN7
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_usb33_ext_xtl3_en : 1; // [0]
        REG32 ldo_usb33_ext_xtl2_en : 1; // [1]
        REG32 ldo_usb33_ext_xtl1_en : 1; // [2]
        REG32 ldo_usb33_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_mmc_ext_xtl3_en : 1; // [12]
        REG32 ldo_mmc_ext_xtl2_en : 1; // [13]
        REG32 ldo_mmc_ext_xtl1_en : 1; // [14]
        REG32 ldo_mmc_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN7_T;

//LDO_XTL_EN8
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_vibr_ext_xtl3_en : 1; // [0]
        REG32 ldo_vibr_ext_xtl2_en : 1; // [1]
        REG32 ldo_vibr_ext_xtl1_en : 1; // [2]
        REG32 ldo_vibr_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_kpled_ext_xtl3_en : 1; // [12]
        REG32 ldo_kpled_ext_xtl2_en : 1; // [13]
        REG32 ldo_kpled_ext_xtl1_en : 1; // [14]
        REG32 ldo_kpled_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN8_T;

//LDO_XTL_EN9
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_ana_ext_xtl3_en : 1; // [0]
        REG32 ldo_ana_ext_xtl2_en : 1; // [1]
        REG32 ldo_ana_ext_xtl1_en : 1; // [2]
        REG32 ldo_ana_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_con_ext_xtl3_en : 1; // [12]
        REG32 ldo_con_ext_xtl2_en : 1; // [13]
        REG32 ldo_con_ext_xtl1_en : 1; // [14]
        REG32 ldo_con_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN9_T;

//LDO_XTL_EN10
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_spimem_ext_xtl3_en : 1; // [0]
        REG32 ldo_spimem_ext_xtl2_en : 1; // [1]
        REG32 ldo_spimem_ext_xtl1_en : 1; // [2]
        REG32 ldo_spimem_ext_xtl0_en : 1; // [3]
        REG32 __11_4 : 8;
        REG32 ldo_cp_ext_xtl3_en : 1; // [12]
        REG32 ldo_cp_ext_xtl2_en : 1; // [13]
        REG32 ldo_cp_ext_xtl1_en : 1; // [14]
        REG32 ldo_cp_ext_xtl0_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_LDO_XTL_EN10_T;

//BG_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 bg_chop_en : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_BG_CTRL_T;

//DCDC_VLG_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 dcdc_core_nor_sw_sel : 1;    // [0]
        REG32 dcdc_core_slp_sw_sel : 1;    // [1]
        REG32 dcdc_core_votrim_sw_sel : 1; // [2]
        REG32 dcdc_gen_sw_sel : 1;         // [3]
        REG32 dcdc_wpa_sw_sel : 1;         // [4]
        REG32 dcdc_wpa_votrim_sw_sel : 1;  // [5]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_DCDC_VLG_SEL_T;

//LDO_VLG_SEL0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_trim_b_sw_sel : 1;  // [0]
        REG32 ldo_trim_a_sw_sel : 1;  // [1]
        REG32 ldo_dcxo_sw_sel : 1;    // [2]
        REG32 ldo_rtc_cal_sw_sel : 1; // [3]
        REG32 ldo_vibr_sw_sel : 1;    // [4]
        REG32 ldo_kpled_sw_sel : 1;   // [5]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_LDO_VLG_SEL0_T;

//CLK32KLESS_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 rc_32k_en : 1;  // [0]
        REG32 rc_32k_sel : 1; // [1]
        REG32 __3_2 : 2;
        REG32 rtc_mode : 1; // [4], read only
        REG32 __5_5 : 1;
        REG32 ldo_dcxo_lp_en_rtcclr : 1; // [6]
        REG32 ldo_dcxo_lp_en_rtcset : 1; // [7]
        REG32 __9_8 : 2;
        REG32 rc_mode_wr_ack_flag_clr : 1; // [10], write clear
        REG32 __13_11 : 3;
        REG32 rc_mode_wr_ack_flag : 1; // [14], read only
        REG32 __31_15 : 17;
    } b;
} REG_RDA2720M_GLOBAL_CLK32KLESS_CTRL0_T;

//CLK32KLESS_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 rc_mode : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_CLK32KLESS_CTRL1_T;

//XTL_WAIT_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 xtl_wait : 8;            // [7:0]
        REG32 xtl_en : 1;              // [8]
        REG32 slp_xtlbuf_pd_en : 1;    // [9]
        REG32 ext_xtl0_for_26m_en : 1; // [10]
        REG32 ext_xtl1_for_26m_en : 1; // [11]
        REG32 ext_xtl2_for_26m_en : 1; // [12]
        REG32 ext_xtl3_for_26m_en : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_GLOBAL_XTL_WAIT_CTRL0_T;

//RGB_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 rgb_pd_sw : 1;     // [0]
        REG32 rgb_pd_hw_en : 1;  // [1]
        REG32 slp_rgb_pd_en : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_RDA2720M_GLOBAL_RGB_CTRL_T;

//IB_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 ib_rex_en : 1;      // [0]
        REG32 ib_trim_em_sel : 1; // [1]
        REG32 ib_trim : 7;        // [8:2]
        REG32 batdet_cur_i : 3;   // [11:9]
        REG32 __12_12 : 1;
        REG32 batdet_cur_en : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_GLOBAL_IB_CTRL_T;

//FLASH_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 flash_v_sw : 4;      // [3:0]
        REG32 flash_v_hw_step : 2; // [5:4]
        REG32 flash_v_hw_en : 1;   // [6]
        REG32 __14_7 : 8;
        REG32 flash_pon : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_FLASH_CTRL_T;

//KPLED_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_kpled_cl_adj : 1;   // [0]
        REG32 ldo_kpled_shpt_adj : 1; // [1]
        REG32 ldo_kpled_stb : 2;      // [3:2]
        REG32 ldo_kpled_cap_sel : 1;  // [4]
        REG32 __8_5 : 4;
        REG32 slp_ldokpled_pd_en : 1; // [9]
        REG32 kpled_pulldown_en : 1;  // [10]
        REG32 kpled_pd : 1;           // [11]
        REG32 kpled_v : 4;            // [15:12]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_KPLED_CTRL0_T;

//KPLED_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_kpled_shpt_pd : 1; // [0]
        REG32 __1_1 : 1;
        REG32 ldo_kpled_reftrim : 5; // [6:2]
        REG32 ldo_kpled_v : 3;       // [9:7]
        REG32 __14_10 : 5;
        REG32 ldo_kpled_pd : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_KPLED_CTRL1_T;

//VIBR_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_vibr_v : 3; // [2:0]
        REG32 __7_3 : 5;
        REG32 ldo_vibr_pd : 1;       // [8]
        REG32 slp_ldovibr_pd_en : 1; // [9]
        REG32 ldo_vibr_shpt_pd : 1;  // [10]
        REG32 ldo_vibr_cl_adj : 1;   // [11]
        REG32 ldo_vibr_shpt_adj : 1; // [12]
        REG32 ldo_vibr_stb : 2;      // [14:13]
        REG32 ldo_vibr_cap_sel : 1;  // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_VIBR_CTRL0_T;

//VIBR_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_vibr_eadbias_en : 1; // [0]
        REG32 ldo_vibr_reftrim : 5;    // [5:1]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_GLOBAL_VIBR_CTRL1_T;

//AUDIO_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 clk_aud_if_6p5m_rx_inv_en : 1; // [0]
        REG32 clk_aud_if_6p5m_tx_inv_en : 1; // [1]
        REG32 clk_aud_if_rx_inv_en : 1;      // [2]
        REG32 clk_aud_if_tx_inv_en : 1;      // [3]
        REG32 __31_4 : 28;
    } b;
} REG_RDA2720M_GLOBAL_AUDIO_CTRL0_T;

//CHGR_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 chgr_pd : 1;    // [0]
        REG32 chgr_iterm : 2; // [2:1]
        REG32 chgr_end_v : 2; // [4:3]
        REG32 chgr_cv_v : 6;  // [10:5]
        REG32 __11_11 : 1;
        REG32 chgr_cc_en : 1; // [12]
        REG32 chgr_dpm : 2;   // [14:13]
        REG32 __31_15 : 17;
    } b;
} REG_RDA2720M_GLOBAL_CHGR_CTRL0_T;

//CHGR_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 vchg_ovp_v : 2; // [1:0]
        REG32 __9_2 : 8;
        REG32 chgr_cc_i : 4; // [13:10]
        REG32 __14_14 : 1;
        REG32 chgr_expower_device : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_CHGR_CTRL1_T;

//CHGR_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 vchg_ovi : 1;       // [0], read only
        REG32 dcp_switch_en : 1;  // [1]
        REG32 chgr_int : 1;       // [2], read only
        REG32 chgr_on : 1;        // [3], read only
        REG32 chgr_cv_status : 1; // [4], read only
        REG32 cdp_int : 1;        // [5], read only
        REG32 dcp_int : 1;        // [6], read only
        REG32 sdp_int : 1;        // [7], read only
        REG32 chg_det : 1;        // [8], read only
        REG32 dcp_det : 1;        // [9], read only
        REG32 dp_low : 1;         // [10], read only
        REG32 chg_det_done : 1;   // [11], read only
        REG32 non_dcp_int : 1;    // [12], read only
        REG32 chgr_int_en : 1;    // [13]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_GLOBAL_CHGR_STATUS_T;

//CHGR_DET_FGU_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 dp_dm_bc_enb : 1;     // [0]
        REG32 dp_dm_aux_en : 1;     // [1]
        REG32 sd_dcoffset_a_en : 1; // [2]
        REG32 sd_dcoffset_b_en : 1; // [3]
        REG32 sd_chop_en : 1;       // [4]
        REG32 sd_adc0_rc_pd : 1;    // [5]
        REG32 sd_clk_p : 2;         // [7:6]
        REG32 sd_chop_cap_en : 1;   // [8]
        REG32 chg_int_delay : 3;    // [11:9]
        REG32 ldo_fgu_pd : 1;       // [12]
        REG32 fgua_soft_rst : 1;    // [13]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_GLOBAL_CHGR_DET_FGU_CTRL_T;

//OVLO_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 ovlo_t : 2; // [1:0]
        REG32 ovlo_v : 2; // [3:2]
        REG32 __8_4 : 5;
        REG32 ovlo_en : 1;      // [9]
        REG32 vbat_crash_v : 2; // [11:10]
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_GLOBAL_OVLO_CTRL_T;

//MIXED_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 int_debug_en : 1; // [0]
        REG32 all_int_deb : 1;  // [1]
        REG32 gpi_debug_en : 1; // [2]
        REG32 all_gpi_deb : 1;  // [3]
        REG32 vbat_ok : 1;      // [4], read only
        REG32 __7_5 : 3;
        REG32 batdet_ok : 1;   // [8], read only
        REG32 vpp_5v_sel : 1;  // [9]
        REG32 baton_t : 2;     // [11:10]
        REG32 xosc32k_ctl : 1; // [12]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_GLOBAL_MIXED_CTRL_T;

//POR_RST_MONITOR
typedef union {
    REG32 v;
    struct
    {
        REG32 por_rst_monitor : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_POR_RST_MONITOR_T;

//WDG_RST_MONITOR
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_rst_monitor : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_WDG_RST_MONITOR_T;

//POR_PIN_RST_MONITOR
typedef union {
    REG32 v;
    struct
    {
        REG32 pro_pin_rst_monitor : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_POR_PIN_RST_MONITOR_T;

//POR_SRC_FLAG
typedef union {
    REG32 v;
    struct
    {
        REG32 por_src_flag : 14;        // [13:0], read only
        REG32 reg_soft_rst_flg_clr : 1; // [14], write clear
        REG32 por_sw_force_on : 1;      // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_POR_SRC_FLAG_T;

//POR_OFF_FLAG
typedef union {
    REG32 v;
    struct
    {
        REG32 __1_0 : 2;
        REG32 otp_chip_pd_flag_clr : 1;     // [2], write clear
        REG32 otp_chip_pd_flag : 1;         // [3], read only
        REG32 hw_chip_pd_flag_clr : 1;      // [4], write clear
        REG32 hw_chip_pd_flag : 1;          // [5], read only
        REG32 sw_chip_pd_flag_clr : 1;      // [6], write clear
        REG32 sw_chip_pd_flag : 1;          // [7], read only
        REG32 hard_7s_chip_pd_flag_clr : 1; // [8], write clear
        REG32 hard_7s_chip_pd_flag : 1;     // [9], read only
        REG32 uvlo_chip_pd_flag_clr : 1;    // [10], write clear
        REG32 uvlo_chip_pd_flag : 1;        // [11], read only
        REG32 por_chip_pd_flag_clr : 1;     // [12], write clear
        REG32 por_chip_pd_flag : 1;         // [13], read only
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_GLOBAL_POR_OFF_FLAG_T;

//POR_7S_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 pbint_7s_rst_mode : 1;      // [0]
        REG32 pbint_7s_rst_disable : 1;   // [1]
        REG32 pbint_7s_auto_on_en : 1;    // [2]
        REG32 ext_rstn_mode : 1;          // [3]
        REG32 pbint_7s_rst_threshold : 4; // [7:4]
        REG32 pbint_7s_rst_swmode : 1;    // [8]
        REG32 key2_7s_rst_en : 1;         // [9]
        REG32 __10_10 : 1;
        REG32 pbint_flag_clr : 1;    // [11]
        REG32 pbint2_flag_clr : 1;   // [12]
        REG32 chgr_int_flag_clr : 1; // [13]
        REG32 ext_rstn_flag_clr : 1; // [14]
        REG32 pbint_7s_flag_clr : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_POR_7S_CTRL_T;

//HWRST_RTC
typedef union {
    REG32 v;
    struct
    {
        REG32 hwrst_rtc_reg_set : 8; // [7:0]
        REG32 hwrst_rtc_reg_sts : 8; // [15:8], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_HWRST_RTC_T;

//ARCH_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 arch_en : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_GLOBAL_ARCH_EN_T;

//MCU_WR_PROT_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 mcu_wr_prot_value : 15; // [14:0]
        REG32 mcu_wr_prot : 1;        // [15], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_MCU_WR_PROT_VALUE_T;

//PWR_WR_PROT_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 pwr_wr_prot_value : 15; // [14:0]
        REG32 pwr_wr_prot : 1;        // [15], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_PWR_WR_PROT_VALUE_T;

//SMPL_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 smpl_mode : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_SMPL_CTRL0_T;

//SMPL_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 smpl_en : 1; // [0], read only
        REG32 __10_1 : 10;
        REG32 smpl_pwr_on_set : 1;           // [11], read only
        REG32 smpl_mode_wr_ack_flag_clr : 1; // [12], write clear
        REG32 smpl_pwr_on_flag_clr : 1;      // [13], write clear
        REG32 smpl_mode_wr_ack_flag : 1;     // [14], read only
        REG32 smpl_pwr_on_flag : 1;          // [15], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_SMPL_CTRL1_T;

//RTC_RST0
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_clk_flag_set : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_RTC_RST0_T;

//RTC_RST1
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_clk_flag_clr : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_RTC_RST1_T;

//RTC_RST2
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_clk_flag_rtc : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_RTC_RST2_T;

//RTC_CLK_STOP
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_clk_stop_threshold : 7; // [6:0]
        REG32 rtc_clk_stop_flag : 1;      // [7], read only
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_GLOBAL_RTC_CLK_STOP_T;

//VBAT_DROP_CNT
typedef union {
    REG32 v;
    struct
    {
        REG32 vbat_drop_cnt : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_GLOBAL_VBAT_DROP_CNT_T;

//SWRST_CTRL0
typedef union {
    REG32 v;
    struct
    {
        REG32 sw_rst_pd_threshold : 4; // [3:0]
        REG32 reg_rst_en : 1;          // [4]
        REG32 __6_5 : 2;
        REG32 wdg_rst_pd_en : 1;   // [7]
        REG32 reg_rst_pd_en : 1;   // [8]
        REG32 pb_7s_rst_pd_en : 1; // [9]
        REG32 ext_rstn_pd_en : 1;  // [10]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_GLOBAL_SWRST_CTRL0_T;

//SWRST_CTRL1
typedef union {
    REG32 v;
    struct
    {
        REG32 sw_rst_vio18_pd_en : 1;    // [0]
        REG32 sw_rst_ddr12_pd_en : 1;    // [1]
        REG32 sw_rst_mmc_pd_en : 1;      // [2]
        REG32 sw_rst_usb33_pd_en : 1;    // [3]
        REG32 sw_rst_rf15_pd_en : 1;     // [4]
        REG32 sw_rst_ana_pd_en : 1;      // [5]
        REG32 sw_rst_vdd28_pd_en : 1;    // [6]
        REG32 sw_rst_dcxo_pd_en : 1;     // [7]
        REG32 sw_rst_mem_pd_en : 1;      // [8]
        REG32 sw_rst_dcdccore_pd_en : 1; // [9]
        REG32 sw_rst_dcdcgen_pd_en : 1;  // [10]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_GLOBAL_SWRST_CTRL1_T;

//OTP_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 otp_en : 1; // [0]
        REG32 otp_op : 2; // [2:1]
        REG32 __31_3 : 29;
    } b;
} REG_RDA2720M_GLOBAL_OTP_CTRL_T;

//FREE_TIMER_LOW
typedef union {
    REG32 v;
    struct
    {
        REG32 timer_low : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_FREE_TIMER_LOW_T;

//FREE_TIMER_HIGH
typedef union {
    REG32 v;
    struct
    {
        REG32 timer_high : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_GLOBAL_FREE_TIMER_HIGH_T;

//VOL_TUNE_CTRL_CORE
typedef union {
    REG32 v;
    struct
    {
        REG32 core_vol_tune_en : 1;    // [0]
        REG32 core_vol_tune_flag : 1;  // [1], read only
        REG32 core_vol_tune_start : 1; // [2], write clear
        REG32 core_step_vol : 5;       // [7:3]
        REG32 core_step_num : 4;       // [11:8]
        REG32 core_step_delay : 2;     // [13:12]
        REG32 core_clk_sel : 1;        // [14]
        REG32 __31_15 : 17;
    } b;
} REG_RDA2720M_GLOBAL_VOL_TUNE_CTRL_CORE_T;

#endif
