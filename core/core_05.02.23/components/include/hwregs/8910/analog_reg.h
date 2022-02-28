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

#ifndef _ANALOG_REG_H_
#define _ANALOG_REG_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'analog_reg'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// ANALOG_REG_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_ANALOG_REG_BASE 0x05109000
#else
#define REG_ANALOG_REG_BASE 0x50109000
#endif

typedef volatile struct
{
    REG32 apll_reg0;                //0x00000000
    REG32 apll_reg1;                //0x00000004
    REG32 apll_reg2;                //0x00000008
    REG32 sdm_apll_reg0;            //0x0000000C
    REG32 sdm_apll_reg1;            //0x00000010
    REG32 sdm_apll_reg2;            //0x00000014
    REG32 sdm_apll_reg3;            //0x00000018
    REG32 sdm_apll_reg4;            //0x0000001C
    REG32 Reserved_00000020[8];     //0x00000020
    REG32 mempll_reg0;              //0x00000040
    REG32 mempll_reg1;              //0x00000044
    REG32 mempll_reg2;              //0x00000048
    REG32 sdm_mempll_reg0;          //0x0000004C
    REG32 sdm_mempll_reg1;          //0x00000050
    REG32 sdm_mempll_reg2;          //0x00000054
    REG32 sdm_mempll_reg3;          //0x00000058
    REG32 sdm_mempll_reg4;          //0x0000005C
    REG32 Reserved_00000060[8];     //0x00000060
    REG32 usb_reg0;                 //0x00000080
    REG32 usb_reg1;                 //0x00000084
    REG32 usb_reg2;                 //0x00000088
    REG32 usb_reg3;                 //0x0000008C
    REG32 usb_reg4;                 //0x00000090
    REG32 usb_pll1;                 //0x00000094
    REG32 usb_pll2;                 //0x00000098
    REG32 usb_suspend;              //0x0000009C
    REG32 usb11_reg;                //0x000000A0
    REG32 usb_mon;                  //0x000000A4
    REG32 usb_reserved;             //0x000000A8
    REG32 sdm_usbpll_reg0;          //0x000000AC
    REG32 sdm_usbpll_reg1;          //0x000000B0
    REG32 sdm_usbpll_reg2;          //0x000000B4
    REG32 sdm_usbpll_reg3;          //0x000000B8
    REG32 sdm_usbpll_reg4;          //0x000000BC
    REG32 usb_digphy_ana1;          //0x000000C0
    REG32 usb_digphy_ana2;          //0x000000C4
    REG32 usb_digphy_ana3;          //0x000000C8
    REG32 usb_digphy_ana4;          //0x000000CC
    REG32 usb11_digphy_ana_reg;     //0x000000D0
    REG32 Reserved_000000D4[11];    //0x000000D4
    REG32 ddr_pad_cfg;              //0x00000100
    REG32 psram_pad_cfg;            //0x00000104
    REG32 Reserved_00000108[14];    //0x00000108
    REG32 sdm_dsipll_reg0;          //0x00000140
    REG32 sdm_dsipll_reg1;          //0x00000144
    REG32 sdm_dsipll_reg2;          //0x00000148
    REG32 sdm_dsipll_reg3;          //0x0000014C
    REG32 sdm_dsipll_reg4;          //0x00000150
    REG32 mipi_lvds_phy_reg;        //0x00000154
    REG32 Reserved_00000158[10];    //0x00000158
    REG32 pad_ctrl_resv;            //0x00000180
    REG32 pad_resetb_cfg;           //0x00000184
    REG32 pad_adi_cfg;              //0x00000188
    REG32 pad_ap_jtag_cfg;          //0x0000018C
    REG32 pad_spi_camera_cfg;       //0x00000190
    REG32 pad_camera_cfg;           //0x00000194
    REG32 pad_debug_host_cfg;       //0x00000198
    REG32 pad_gpio_cfg1;            //0x0000019C
    REG32 pad_gpio_cfg2;            //0x000001A0
    REG32 pad_gpo_cfg;              //0x000001A4
    REG32 pad_i2c_cfg;              //0x000001A8
    REG32 pad_aud_ad_cfg;           //0x000001AC
    REG32 pad_keyin_cfg;            //0x000001B0
    REG32 pad_keyout_cfg;           //0x000001B4
    REG32 pad_lcd_cfg;              //0x000001B8
    REG32 pad_gpio13_cfg;           //0x000001BC
    REG32 pad_rfdig_gpio_cfg1;      //0x000001C0
    REG32 pad_rfdig_gpio_cfg2;      //0x000001C4
    REG32 pad_sdmmc1_others_cfg;    //0x000001C8
    REG32 pad_sdmmc1_data_cfg;      //0x000001CC
    REG32 pad_sim_1_cfg;            //0x000001D0
    REG32 pad_sim_2_cfg;            //0x000001D4
    REG32 pad_spi_flash_cfg1;       //0x000001D8
    REG32 pad_spi_flash_cfg2;       //0x000001DC
    REG32 pad_spi_lcd_cfg1;         //0x000001E0
    REG32 pad_spi_lcd_cfg2;         //0x000001E4
    REG32 pad_tst_cfg;              //0x000001E8
    REG32 pad_uart_1_cfg;           //0x000001EC
    REG32 pad_uart_2_cfg;           //0x000001F0
    REG32 pad_secure_boot_mode_cfg; //0x000001F4
    REG32 Reserved_000001F8[2];     //0x000001F8
    REG32 resv0;                    //0x00000200
    REG32 resv1;                    //0x00000204
    REG32 resv2;                    //0x00000208
    REG32 resv3;                    //0x0000020C
    REG32 resv4;                    //0x00000210
    REG32 resv5;                    //0x00000214
    REG32 resv6;                    //0x00000218
    REG32 resv7;                    //0x0000021C
    REG32 resv8;                    //0x00000220
    REG32 resv9;                    //0x00000224
    REG32 resv10;                   //0x00000228
    REG32 resv11;                   //0x0000022C
    REG32 resv12;                   //0x00000230
    REG32 resv13;                   //0x00000234
    REG32 resv14;                   //0x00000238
    REG32 resv15;                   //0x0000023C
} HWP_ANALOG_REG_T;

#define hwp_analogReg ((HWP_ANALOG_REG_T *)REG_ACCESS_ADDRESS(REG_ANALOG_REG_BASE))

//APLL_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 apll_clk_ap_en : 1;  // [0]
        REG32 apll_lp_mode_en : 1; // [1]
        REG32 apll_lock : 1;       // [2], read only
        REG32 __31_3 : 29;
    } b;
} REG_ANALOG_REG_APLL_REG0_T;

//APLL_reg1
typedef union {
    REG32 v;
    struct
    {
        REG32 apll_refmulti2_en : 1; // [0]
        REG32 apll_pcon_mode : 1;    // [1]
        REG32 apll_cpr2_ibit : 3;    // [4:2]
        REG32 apll_cpc2_ibit : 3;    // [7:5]
        REG32 apll_cpbias_ibit : 3;  // [10:8]
        REG32 apll_reg_res_bit : 2;  // [12:11]
        REG32 apll_vreg_bit : 4;     // [16:13]
        REG32 apll_pfd_dly_num : 3;  // [19:17]
        REG32 __31_20 : 12;
    } b;
} REG_ANALOG_REG_APLL_REG1_T;

//APLL_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 apll_vco_low_test : 1;    // [0]
        REG32 apll_vco_high_test : 1;   // [1]
        REG32 apll_sdm_clk_test_en : 1; // [2]
        REG32 apll_test_en : 1;         // [3]
        REG32 __31_4 : 28;
    } b;
} REG_ANALOG_REG_APLL_REG2_T;

//SDM_APLL_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_apll_int_dec_sel : 3;     // [2:0]
        REG32 sdm_apll_pu_pll_reg : 1;      // [3]
        REG32 sdm_apll_pu_pll_dr : 1;       // [4]
        REG32 sdm_apll_sdm_clk_sel_nor : 1; // [5]
        REG32 sdm_apll_sdm_clk_sel_rst : 1; // [6]
        REG32 sdm_apll_pu : 1;              // [7]
        REG32 sdm_apll_fbc_inv : 1;         // [8]
        REG32 __31_9 : 23;
    } b;
} REG_ANALOG_REG_SDM_APLL_REG0_T;

//SDM_APLL_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_apll_lock_counter_sel : 2;      // [1:0]
        REG32 sdm_apll_clkout_en_counter_sel : 2; // [3:2]
        REG32 sdm_apll_clk_gen_en_reg : 1;        // [4]
        REG32 sdm_apll_sdmclk_sel_time_sel : 2;   // [6:5]
        REG32 sdm_apll_sdm_reset_time_sel : 2;    // [8:7]
        REG32 sdm_apll_sdm_resetn_reg : 1;        // [9]
        REG32 sdm_apll_sdm_resetn_dr : 1;         // [10]
        REG32 sdm_apll_dither_bypass : 1;         // [11]
        REG32 __31_12 : 20;
    } b;
} REG_ANALOG_REG_SDM_APLL_REG2_T;

//SDM_APLL_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_apll_clk_ready : 1;   // [0], read only
        REG32 sdm_apll_lock_steady : 1; // [1], read only
        REG32 sdm_apll_sdm_resetn : 1;  // [2], read only
        REG32 __31_3 : 29;
    } b;
} REG_ANALOG_REG_SDM_APLL_REG3_T;

//SDM_APLL_reg4
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_apll_ss_devi_step : 16; // [15:0]
        REG32 sdm_apll_ss_devi : 12;      // [27:16]
        REG32 sdm_apll_ss_en : 1;         // [28]
        REG32 sdm_apll_sdm_en : 1;        // [29]
        REG32 __31_30 : 2;
    } b;
} REG_ANALOG_REG_SDM_APLL_REG4_T;

//MEMPLL_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 mempll_clk_mem_en : 1; // [0]
        REG32 mempll_lp_mode_en : 1; // [1]
        REG32 mempll_lock : 1;       // [2], read only
        REG32 __31_3 : 29;
    } b;
} REG_ANALOG_REG_MEMPLL_REG0_T;

//MEMPLL_reg1
typedef union {
    REG32 v;
    struct
    {
        REG32 mempll_refmulti2_en : 1; // [0]
        REG32 mempll_pcon_mode : 1;    // [1]
        REG32 mempll_cpr2_ibit : 3;    // [4:2]
        REG32 mempll_cpc2_ibit : 3;    // [7:5]
        REG32 mempll_cpbias_ibit : 3;  // [10:8]
        REG32 mempll_reg_res_bit : 2;  // [12:11]
        REG32 mempll_vreg_bit : 4;     // [16:13]
        REG32 mempll_pfd_dly_num : 3;  // [19:17]
        REG32 __31_20 : 12;
    } b;
} REG_ANALOG_REG_MEMPLL_REG1_T;

//MEMPLL_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 mempll_vco_low_test : 1;    // [0]
        REG32 mempll_vco_high_test : 1;   // [1]
        REG32 mempll_sdm_clk_test_en : 1; // [2]
        REG32 mempll_test_en : 1;         // [3]
        REG32 __31_4 : 28;
    } b;
} REG_ANALOG_REG_MEMPLL_REG2_T;

//SDM_MEMPLL_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_mempll_int_dec_sel : 3;     // [2:0]
        REG32 sdm_mempll_pu_pll_reg : 1;      // [3]
        REG32 sdm_mempll_pu_pll_dr : 1;       // [4]
        REG32 sdm_mempll_sdm_clk_sel_nor : 1; // [5]
        REG32 sdm_mempll_sdm_clk_sel_rst : 1; // [6]
        REG32 sdm_mempll_pu : 1;              // [7]
        REG32 sdm_mempll_fbc_inv : 1;         // [8]
        REG32 __31_9 : 23;
    } b;
} REG_ANALOG_REG_SDM_MEMPLL_REG0_T;

//SDM_MEMPLL_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_mempll_lock_counter_sel : 2;      // [1:0]
        REG32 sdm_mempll_clkout_en_counter_sel : 2; // [3:2]
        REG32 sdm_mempll_clk_gen_en_reg : 1;        // [4]
        REG32 sdm_mempll_sdmclk_sel_time_sel : 2;   // [6:5]
        REG32 sdm_mempll_sdm_reset_time_sel : 2;    // [8:7]
        REG32 sdm_mempll_sdm_resetn_reg : 1;        // [9]
        REG32 sdm_mempll_sdm_resetn_dr : 1;         // [10]
        REG32 sdm_mempll_dither_bypass : 1;         // [11]
        REG32 __31_12 : 20;
    } b;
} REG_ANALOG_REG_SDM_MEMPLL_REG2_T;

//SDM_MEMPLL_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_mempll_clk_ready : 1;   // [0], read only
        REG32 sdm_mempll_lock_steady : 1; // [1], read only
        REG32 sdm_mempll_sdm_resetn : 1;  // [2], read only
        REG32 __31_3 : 29;
    } b;
} REG_ANALOG_REG_SDM_MEMPLL_REG3_T;

//SDM_MEMPLL_reg4
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_mempll_ss_devi_step : 16; // [15:0]
        REG32 sdm_mempll_ss_devi : 12;      // [27:16]
        REG32 sdm_mempll_ss_en : 1;         // [28]
        REG32 sdm_mempll_sdm_en : 1;        // [29]
        REG32 __31_30 : 2;
    } b;
} REG_ANALOG_REG_SDM_MEMPLL_REG4_T;

//usb_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_cdr_gain : 4;         // [3:0]
        REG32 usb_phase_sel : 2;        // [5:4]
        REG32 usb_updn_mode : 1;        // [6]
        REG32 usb_rst_intp_enable : 1;  // [7]
        REG32 usb_cdr_clk_edge_bit : 1; // [8]
        REG32 usb_tx_rstn : 1;          // [9]
        REG32 __31_10 : 22;
    } b;
} REG_ANALOG_REG_USB_REG0_T;

//usb_reg1
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_hs_lvlout_bit : 4; // [3:0]
        REG32 usb_v125m_sel_bit : 3; // [6:4]
        REG32 usb_v575m_sel_bit : 3; // [9:7]
        REG32 usb_vref_vbit : 3;     // [12:10]
        REG32 usb_vref_ibit : 2;     // [14:13]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_USB_REG1_T;

//usb_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_pu_lptx : 1;           // [0]
        REG32 usb_pu_hstx : 1;           // [1]
        REG32 usb_pu_hsrx : 1;           // [2]
        REG32 usb_pu_iref : 1;           // [3]
        REG32 usb_pu_1v2 : 1;            // [4]
        REG32 usb_pu_1v8 : 1;            // [5]
        REG32 usb_pu_pkd : 1;            // [6]
        REG32 usb_pwr_on : 1;            // [7]
        REG32 usb_pu_usb_dev : 1;        // [8]
        REG32 usb_vbusvld_bit : 1;       // [9]
        REG32 usb_pu_otg : 1;            // [10]
        REG32 usb_vbg_sel : 1;           // [11]
        REG32 usb_squelch_mode_sel : 1;  // [12]
        REG32 usb_discnnxt_mode_sel : 1; // [13]
        REG32 usb_squelch_aux : 1;       // [14]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_USB_REG2_T;

//usb_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_pattern : 10;   // [9:0]
        REG32 usb_en_pattern : 1; // [10]
        REG32 usb_loopback : 1;   // [11]
        REG32 usb_det_en : 1;     // [12]
        REG32 __31_13 : 19;
    } b;
} REG_ANALOG_REG_USB_REG3_T;

//usb_reg4
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_lptx_drv_sel : 8; // [7:0]
        REG32 usb_res_term_bit : 2; // [9:8]
        REG32 usb_io33_enable : 1;  // [10]
        REG32 __31_11 : 21;
    } b;
} REG_ANALOG_REG_USB_REG4_T;

//usb_pll1
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_pll_cpr2_ibit : 3;   // [2:0]
        REG32 usb_pll_cpc2_ibit : 3;   // [5:3]
        REG32 usb_pll_cpbias_ibit : 3; // [8:6]
        REG32 usb_reg_res_bit : 2;     // [10:9]
        REG32 usb_pll_vreg_bit : 4;    // [14:11]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_USB_PLL1_T;

//usb_pll2
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_pll_clk_960m_en : 1; // [0]
        REG32 usb_vco_low_test : 1;    // [1]
        REG32 usb_vco_high_test : 1;   // [2]
        REG32 usb_sdm_clk_test_en : 1; // [3]
        REG32 usb_pll_test_en : 1;     // [4]
        REG32 usb_refmulti2_en : 1;    // [5]
        REG32 usb_pcon_mode : 1;       // [6]
        REG32 __31_7 : 25;
    } b;
} REG_ANALOG_REG_USB_PLL2_T;

//usb_suspend
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_pu_hstx_suspend : 1;   // [0]
        REG32 usb_pu_hsrx_suspend : 1;   // [1]
        REG32 usb_pu_iref_suspend : 1;   // [2]
        REG32 usb_pu_pkd_suspend : 1;    // [3]
        REG32 usb_pu_otg_suspend : 1;    // [4]
        REG32 usb_pu_suspend_bypass : 1; // [5]
        REG32 __31_6 : 26;
    } b;
} REG_ANALOG_REG_USB_SUSPEND_T;

//usb11_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 usb11_lptx_drvsel : 8;    // [7:0]
        REG32 usb11_io_bias_en : 1;     // [8]
        REG32 usb11_pu_usb : 1;         // [9]
        REG32 usb11_usb_ctrl : 3;       // [12:10]
        REG32 usb11_usb_standby : 1;    // [13]
        REG32 usb11_suspend_bypass : 1; // [14]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_USB11_REG_T;

//usb_mon
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_pll_lock : 1; // [0], read only
        REG32 usb_lock : 1;     // [1], read only
        REG32 usb_correct : 1;  // [2], read only
        REG32 usb_dm_chr : 1;   // [3], read only
        REG32 usb_dp_chr : 1;   // [4], read only
        REG32 __31_5 : 27;
    } b;
} REG_ANALOG_REG_USB_MON_T;

//usb_reserved
typedef union {
    REG32 v;
    struct
    {
        REG32 usb_reg_resv : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ANALOG_REG_USB_RESERVED_T;

//SDM_USBPLL_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_usbpll_int_dec_sel : 3;     // [2:0]
        REG32 sdm_usbpll_pu_pll_reg : 1;      // [3]
        REG32 sdm_usbpll_pu_pll_dr : 1;       // [4]
        REG32 sdm_usbpll_sdm_clk_sel_nor : 1; // [5]
        REG32 sdm_usbpll_sdm_clk_sel_rst : 1; // [6]
        REG32 sdm_usbpll_pu : 1;              // [7]
        REG32 sdm_usbpll_fbc_inv : 1;         // [8]
        REG32 __31_9 : 23;
    } b;
} REG_ANALOG_REG_SDM_USBPLL_REG0_T;

//SDM_USBPLL_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_usbpll_lock_counter_sel : 2;      // [1:0]
        REG32 sdm_usbpll_clkout_en_counter_sel : 2; // [3:2]
        REG32 sdm_usbpll_clk_gen_en_reg : 1;        // [4]
        REG32 sdm_usbpll_sdmclk_sel_time_sel : 2;   // [6:5]
        REG32 sdm_usbpll_sdm_reset_time_sel : 2;    // [8:7]
        REG32 sdm_usbpll_sdm_resetn_reg : 1;        // [9]
        REG32 sdm_usbpll_sdm_resetn_dr : 1;         // [10]
        REG32 sdm_usbpll_dither_bypass : 1;         // [11]
        REG32 __31_12 : 20;
    } b;
} REG_ANALOG_REG_SDM_USBPLL_REG2_T;

//SDM_USBPLL_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_usbpll_clk_ready : 1;   // [0], read only
        REG32 sdm_usbpll_lock_steady : 1; // [1], read only
        REG32 sdm_usbpll_sdm_resetn : 1;  // [2], read only
        REG32 __31_3 : 29;
    } b;
} REG_ANALOG_REG_SDM_USBPLL_REG3_T;

//SDM_USBPLL_reg4
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_usbpll_ss_devi_step : 16; // [15:0]
        REG32 sdm_usbpll_ss_devi : 12;      // [27:16]
        REG32 sdm_usbpll_ss_en : 1;         // [28]
        REG32 sdm_usbpll_sdm_en : 1;        // [29]
        REG32 __31_30 : 2;
    } b;
} REG_ANALOG_REG_SDM_USBPLL_REG4_T;

//ddr_pad_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 ddr_latch : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ANALOG_REG_DDR_PAD_CFG_T;

//psram_pad_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 psram_latch : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ANALOG_REG_PSRAM_PAD_CFG_T;

//SDM_DSIPLL_reg0
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_dsipll_int_dec_sel : 3;     // [2:0]
        REG32 sdm_dsipll_pu_pll_reg : 1;      // [3]
        REG32 sdm_dsipll_pu_pll_dr : 1;       // [4]
        REG32 sdm_dsipll_sdm_clk_sel_nor : 1; // [5]
        REG32 sdm_dsipll_sdm_clk_sel_rst : 1; // [6]
        REG32 sdm_dsipll_pu : 1;              // [7]
        REG32 sdm_dsipll_fbc_inv : 1;         // [8]
        REG32 __31_9 : 23;
    } b;
} REG_ANALOG_REG_SDM_DSIPLL_REG0_T;

//SDM_DSIPLL_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_dsipll_lock_counter_sel : 2;      // [1:0]
        REG32 sdm_dsipll_clkout_en_counter_sel : 2; // [3:2]
        REG32 sdm_dsipll_clk_gen_en_reg : 1;        // [4]
        REG32 sdm_dsipll_sdmclk_sel_time_sel : 2;   // [6:5]
        REG32 sdm_dsipll_sdm_reset_time_sel : 2;    // [8:7]
        REG32 sdm_dsipll_sdm_resetn_reg : 1;        // [9]
        REG32 sdm_dsipll_sdm_resetn_dr : 1;         // [10]
        REG32 sdm_dsipll_dither_bypass : 1;         // [11]
        REG32 __31_12 : 20;
    } b;
} REG_ANALOG_REG_SDM_DSIPLL_REG2_T;

//SDM_DSIPLL_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_dsipll_clk_ready : 1;   // [0], read only
        REG32 sdm_dsipll_lock_steady : 1; // [1], read only
        REG32 sdm_dsipll_sdm_resetn : 1;  // [2], read only
        REG32 __31_3 : 29;
    } b;
} REG_ANALOG_REG_SDM_DSIPLL_REG3_T;

//SDM_DSIPLL_reg4
typedef union {
    REG32 v;
    struct
    {
        REG32 sdm_dsipll_ss_devi_step : 16; // [15:0]
        REG32 sdm_dsipll_ss_devi : 12;      // [27:16]
        REG32 sdm_dsipll_ss_en : 1;         // [28]
        REG32 sdm_dsipll_sdm_en : 1;        // [29]
        REG32 __31_30 : 2;
    } b;
} REG_ANALOG_REG_SDM_DSIPLL_REG4_T;

//MIPI_LVDS_PHY_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 csi_lvds_mode : 1;           // [0]
        REG32 lvds_rx_terminal_enable : 1; // [1]
        REG32 lvdspll_sdm_sel : 1;         // [2]
        REG32 lvdspll_refmulti2_en : 1;    // [3]
        REG32 __31_4 : 28;
    } b;
} REG_ANALOG_REG_MIPI_LVDS_PHY_REG_T;

//pad_RESETB_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_resetb_wpus : 1; // [0]
        REG32 pad_resetb_se : 1;   // [1]
        REG32 pad_resetb_ie : 1;   // [2]
        REG32 pad_resetb_drv : 2;  // [4:3]
        REG32 __31_5 : 27;
    } b;
} REG_ANALOG_REG_PAD_RESETB_CFG_T;

//pad_adi_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_adi_sync_wpus : 1; // [0]
        REG32 pad_adi_sync_se : 1;   // [1]
        REG32 pad_adi_sync_ie : 1;   // [2]
        REG32 pad_adi_sync_drv : 2;  // [4:3]
        REG32 pad_adi_sda_wpus : 1;  // [5]
        REG32 pad_adi_sda_se : 1;    // [6]
        REG32 pad_adi_sda_ie : 1;    // [7]
        REG32 pad_adi_sda_drv : 2;   // [9:8]
        REG32 pad_adi_scl_wpus : 1;  // [10]
        REG32 pad_adi_scl_se : 1;    // [11]
        REG32 pad_adi_scl_ie : 1;    // [12]
        REG32 pad_adi_scl_drv : 2;   // [14:13]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_PAD_ADI_CFG_T;

//pad_ap_jtag_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_ap_jtag_trst_wpus : 1; // [0]
        REG32 pad_ap_jtag_trst_se : 1;   // [1]
        REG32 pad_ap_jtag_trst_ie : 1;   // [2]
        REG32 pad_ap_jtag_trst_drv : 2;  // [4:3]
        REG32 pad_ap_jtag_tms_wpus : 1;  // [5]
        REG32 pad_ap_jtag_tms_se : 1;    // [6]
        REG32 pad_ap_jtag_tms_ie : 1;    // [7]
        REG32 pad_ap_jtag_tms_drv : 2;   // [9:8]
        REG32 pad_ap_jtag_tdo_wpus : 1;  // [10]
        REG32 pad_ap_jtag_tdo_se : 1;    // [11]
        REG32 pad_ap_jtag_tdo_ie : 1;    // [12]
        REG32 pad_ap_jtag_tdo_drv : 2;   // [14:13]
        REG32 pad_ap_jtag_tdi_wpus : 1;  // [15]
        REG32 pad_ap_jtag_tdi_se : 1;    // [16]
        REG32 pad_ap_jtag_tdi_ie : 1;    // [17]
        REG32 pad_ap_jtag_tdi_drv : 2;   // [19:18]
        REG32 pad_ap_jtag_tck_wpus : 1;  // [20]
        REG32 pad_ap_jtag_tck_se : 1;    // [21]
        REG32 pad_ap_jtag_tck_ie : 1;    // [22]
        REG32 pad_ap_jtag_tck_drv : 2;   // [24:23]
        REG32 __31_25 : 7;
    } b;
} REG_ANALOG_REG_PAD_AP_JTAG_CFG_T;

//pad_spi_camera_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_camera_si_1_wpus : 1; // [0]
        REG32 pad_spi_camera_si_1_se : 1;   // [1]
        REG32 pad_spi_camera_si_1_ie : 1;   // [2]
        REG32 pad_spi_camera_si_1_drv : 2;  // [4:3]
        REG32 pad_spi_camera_si_0_wpus : 1; // [5]
        REG32 pad_spi_camera_si_0_se : 1;   // [6]
        REG32 pad_spi_camera_si_0_ie : 1;   // [7]
        REG32 pad_spi_camera_si_0_drv : 2;  // [9:8]
        REG32 pad_spi_camera_sck_wpus : 1;  // [10]
        REG32 pad_spi_camera_sck_se : 1;    // [11]
        REG32 pad_spi_camera_sck_ie : 1;    // [12]
        REG32 pad_spi_camera_sck_drv : 2;   // [14:13]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_PAD_SPI_CAMERA_CFG_T;

//pad_camera_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_camera_rst_l_wpus : 1;   // [0]
        REG32 pad_camera_rst_l_se : 1;     // [1]
        REG32 pad_camera_rst_l_ie : 1;     // [2]
        REG32 pad_camera_rst_l_drv : 2;    // [4:3]
        REG32 pad_camera_ref_clk_wpus : 1; // [5]
        REG32 pad_camera_ref_clk_se : 1;   // [6]
        REG32 pad_camera_ref_clk_ie : 1;   // [7]
        REG32 pad_camera_ref_clk_drv : 2;  // [9:8]
        REG32 pad_camera_pwdn_wpus : 1;    // [10]
        REG32 pad_camera_pwdn_se : 1;      // [11]
        REG32 pad_camera_pwdn_ie : 1;      // [12]
        REG32 pad_camera_pwdn_drv : 2;     // [14:13]
        REG32 pad_camera_wpdi : 1;         // [15]
        REG32 __31_16 : 16;
    } b;
} REG_ANALOG_REG_PAD_CAMERA_CFG_T;

//pad_debug_host_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_debug_host_tx_wpus : 1;  // [0]
        REG32 pad_debug_host_tx_se : 1;    // [1]
        REG32 pad_debug_host_tx_ie : 1;    // [2]
        REG32 pad_debug_host_tx_drv : 2;   // [4:3]
        REG32 pad_debug_host_rx_wpus : 1;  // [5]
        REG32 pad_debug_host_rx_se : 1;    // [6]
        REG32 pad_debug_host_rx_ie : 1;    // [7]
        REG32 pad_debug_host_rx_drv : 2;   // [9:8]
        REG32 pad_debug_host_clk_wpus : 1; // [10]
        REG32 pad_debug_host_clk_se : 1;   // [11]
        REG32 pad_debug_host_clk_ie : 1;   // [12]
        REG32 pad_debug_host_clk_drv : 2;  // [14:13]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_PAD_DEBUG_HOST_CFG_T;

//pad_gpio_cfg1
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_3_wpus : 1; // [0]
        REG32 pad_gpio_3_se : 1;   // [1]
        REG32 pad_gpio_3_ie : 1;   // [2]
        REG32 pad_gpio_3_drv : 2;  // [4:3]
        REG32 pad_gpio_2_wpus : 1; // [5]
        REG32 pad_gpio_2_se : 1;   // [6]
        REG32 pad_gpio_2_ie : 1;   // [7]
        REG32 pad_gpio_2_drv : 2;  // [9:8]
        REG32 pad_gpio_1_wpus : 1; // [10]
        REG32 pad_gpio_1_se : 1;   // [11]
        REG32 pad_gpio_1_ie : 1;   // [12]
        REG32 pad_gpio_1_drv : 2;  // [14:13]
        REG32 pad_gpio_0_wpus : 1; // [15]
        REG32 pad_gpio_0_se : 1;   // [16]
        REG32 pad_gpio_0_ie : 1;   // [17]
        REG32 pad_gpio_0_drv : 2;  // [19:18]
        REG32 __31_20 : 12;
    } b;
} REG_ANALOG_REG_PAD_GPIO_CFG1_T;

//pad_gpio_cfg2
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_7_wpus : 1; // [0]
        REG32 pad_gpio_7_se : 1;   // [1]
        REG32 pad_gpio_7_ie : 1;   // [2]
        REG32 pad_gpio_7_drv : 2;  // [4:3]
        REG32 pad_gpio_5_wpus : 1; // [5]
        REG32 pad_gpio_5_se : 1;   // [6]
        REG32 pad_gpio_5_ie : 1;   // [7]
        REG32 pad_gpio_5_drv : 2;  // [9:8]
        REG32 pad_gpio_4_wpus : 1; // [10]
        REG32 pad_gpio_4_se : 1;   // [11]
        REG32 pad_gpio_4_ie : 1;   // [12]
        REG32 pad_gpio_4_drv : 2;  // [14:13]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_PAD_GPIO_CFG2_T;

//pad_gpo_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_12_wpus : 1; // [0]
        REG32 pad_gpio_12_se : 1;   // [1]
        REG32 pad_gpio_12_ie : 1;   // [2]
        REG32 pad_gpio_12_drv : 2;  // [4:3]
        REG32 pad_gpio_11_wpus : 1; // [5]
        REG32 pad_gpio_11_se : 1;   // [6]
        REG32 pad_gpio_11_ie : 1;   // [7]
        REG32 pad_gpio_11_drv : 2;  // [9:8]
        REG32 pad_gpio_10_wpus : 1; // [10]
        REG32 pad_gpio_10_se : 1;   // [11]
        REG32 pad_gpio_10_ie : 1;   // [12]
        REG32 pad_gpio_10_drv : 2;  // [14:13]
        REG32 pad_gpio_9_wpus : 1;  // [15]
        REG32 pad_gpio_9_se : 1;    // [16]
        REG32 pad_gpio_9_ie : 1;    // [17]
        REG32 pad_gpio_9_drv : 2;   // [19:18]
        REG32 pad_gpio_8_wpus : 1;  // [20]
        REG32 pad_gpio_8_se : 1;    // [21]
        REG32 pad_gpio_8_ie : 1;    // [22]
        REG32 pad_gpio_8_drv : 2;   // [24:23]
        REG32 __31_25 : 7;
    } b;
} REG_ANALOG_REG_PAD_GPO_CFG_T;

//pad_i2c_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_15_wpus : 1;    // [0]
        REG32 pad_gpio_15_se : 1;      // [1]
        REG32 pad_gpio_15_ie : 1;      // [2]
        REG32 pad_gpio_15_drv : 2;     // [4:3]
        REG32 pad_gpio_14_wpus : 1;    // [5]
        REG32 pad_gpio_14_se : 1;      // [6]
        REG32 pad_gpio_14_ie : 1;      // [7]
        REG32 pad_gpio_14_drv : 2;     // [9:8]
        REG32 pad_i2c_m1_sda_wpus : 1; // [10]
        REG32 pad_i2c_m1_sda_se : 1;   // [11]
        REG32 pad_i2c_m1_sda_ie : 1;   // [12]
        REG32 pad_i2c_m1_sda_drv : 2;  // [14:13]
        REG32 pad_i2c_m1_scl_wpus : 1; // [15]
        REG32 pad_i2c_m1_scl_se : 1;   // [16]
        REG32 pad_i2c_m1_scl_ie : 1;   // [17]
        REG32 pad_i2c_m1_scl_drv : 2;  // [19:18]
        REG32 __31_20 : 12;
    } b;
} REG_ANALOG_REG_PAD_I2C_CFG_T;

//pad_aud_ad_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_aud_sclk_wpus : 1;    // [0]
        REG32 pad_aud_sclk_se : 1;      // [1]
        REG32 pad_aud_sclk_ie : 1;      // [2]
        REG32 pad_aud_sclk_drv : 2;     // [4:3]
        REG32 pad_aud_da_sync_wpus : 1; // [5]
        REG32 pad_aud_da_sync_se : 1;   // [6]
        REG32 pad_aud_da_sync_ie : 1;   // [7]
        REG32 pad_aud_da_sync_drv : 2;  // [9:8]
        REG32 pad_aud_da_d1_wpus : 1;   // [10]
        REG32 pad_aud_da_d1_se : 1;     // [11]
        REG32 pad_aud_da_d1_ie : 1;     // [12]
        REG32 pad_aud_da_d1_drv : 2;    // [14:13]
        REG32 pad_aud_da_d0_wpus : 1;   // [15]
        REG32 pad_aud_da_d0_se : 1;     // [16]
        REG32 pad_aud_da_d0_ie : 1;     // [17]
        REG32 pad_aud_da_d0_drv : 2;    // [19:18]
        REG32 pad_aud_ad_sync_wpus : 1; // [20]
        REG32 pad_aud_ad_sync_se : 1;   // [21]
        REG32 pad_aud_ad_sync_ie : 1;   // [22]
        REG32 pad_aud_ad_sync_drv : 2;  // [24:23]
        REG32 pad_aud_ad_d0_wpus : 1;   // [25]
        REG32 pad_aud_ad_d0_se : 1;     // [26]
        REG32 pad_aud_ad_d0_ie : 1;     // [27]
        REG32 pad_aud_ad_d0_drv : 2;    // [29:28]
        REG32 __31_30 : 2;
    } b;
} REG_ANALOG_REG_PAD_AUD_AD_CFG_T;

//pad_keyin_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyin_5_wpus : 1; // [0]
        REG32 pad_keyin_5_se : 1;   // [1]
        REG32 pad_keyin_5_ie : 1;   // [2]
        REG32 pad_keyin_5_drv : 2;  // [4:3]
        REG32 pad_keyin_4_wpus : 1; // [5]
        REG32 pad_keyin_4_se : 1;   // [6]
        REG32 pad_keyin_4_ie : 1;   // [7]
        REG32 pad_keyin_4_drv : 2;  // [9:8]
        REG32 pad_keyin_3_wpus : 1; // [10]
        REG32 pad_keyin_3_se : 1;   // [11]
        REG32 pad_keyin_3_ie : 1;   // [12]
        REG32 pad_keyin_3_drv : 2;  // [14:13]
        REG32 pad_keyin_2_wpus : 1; // [15]
        REG32 pad_keyin_2_se : 1;   // [16]
        REG32 pad_keyin_2_ie : 1;   // [17]
        REG32 pad_keyin_2_drv : 2;  // [19:18]
        REG32 pad_keyin_1_wpus : 1; // [20]
        REG32 pad_keyin_1_se : 1;   // [21]
        REG32 pad_keyin_1_ie : 1;   // [22]
        REG32 pad_keyin_1_drv : 2;  // [24:23]
        REG32 pad_keyin_0_wpus : 1; // [25]
        REG32 pad_keyin_0_se : 1;   // [26]
        REG32 pad_keyin_0_ie : 1;   // [27]
        REG32 pad_keyin_0_drv : 2;  // [29:28]
        REG32 pad_key_wpdi : 1;     // [30]
        REG32 __31_31 : 1;
    } b;
} REG_ANALOG_REG_PAD_KEYIN_CFG_T;

//pad_keyout_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyout_5_wpus : 1; // [0]
        REG32 pad_keyout_5_se : 1;   // [1]
        REG32 pad_keyout_5_ie : 1;   // [2]
        REG32 pad_keyout_5_drv : 2;  // [4:3]
        REG32 pad_keyout_4_wpus : 1; // [5]
        REG32 pad_keyout_4_se : 1;   // [6]
        REG32 pad_keyout_4_ie : 1;   // [7]
        REG32 pad_keyout_4_drv : 2;  // [9:8]
        REG32 pad_keyout_3_wpus : 1; // [10]
        REG32 pad_keyout_3_se : 1;   // [11]
        REG32 pad_keyout_3_ie : 1;   // [12]
        REG32 pad_keyout_3_drv : 2;  // [14:13]
        REG32 pad_keyout_2_wpus : 1; // [15]
        REG32 pad_keyout_2_se : 1;   // [16]
        REG32 pad_keyout_2_ie : 1;   // [17]
        REG32 pad_keyout_2_drv : 2;  // [19:18]
        REG32 pad_keyout_1_wpus : 1; // [20]
        REG32 pad_keyout_1_se : 1;   // [21]
        REG32 pad_keyout_1_ie : 1;   // [22]
        REG32 pad_keyout_1_drv : 2;  // [24:23]
        REG32 pad_keyout_0_wpus : 1; // [25]
        REG32 pad_keyout_0_se : 1;   // [26]
        REG32 pad_keyout_0_ie : 1;   // [27]
        REG32 pad_keyout_0_drv : 2;  // [29:28]
        REG32 __31_30 : 2;
    } b;
} REG_ANALOG_REG_PAD_KEYOUT_CFG_T;

//pad_lcd_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_lcd_rstb_spu : 1;  // [0]
        REG32 pad_lcd_rstb_se : 1;   // [1]
        REG32 pad_lcd_rstb_ie : 1;   // [2]
        REG32 pad_lcd_rstb_drv : 4;  // [6:3]
        REG32 pad_lcd_fmark_spu : 1; // [7]
        REG32 pad_lcd_fmark_se : 1;  // [8]
        REG32 pad_lcd_fmark_ie : 1;  // [9]
        REG32 pad_lcd_fmark_drv : 4; // [13:10]
        REG32 pad_lcd_ms : 1;        // [14]
        REG32 pad_lcd_msen : 1;      // [15]
        REG32 __31_16 : 16;
    } b;
} REG_ANALOG_REG_PAD_LCD_CFG_T;

//pad_gpio13_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_13_wpus : 1; // [0]
        REG32 pad_gpio_13_se : 1;   // [1]
        REG32 pad_gpio_13_ie : 1;   // [2]
        REG32 pad_gpio_13_drv : 2;  // [4:3]
        REG32 pad_misc_r_wpdi : 1;  // [5]
        REG32 pad_misc_l_wpdi : 1;  // [6]
        REG32 pad_mipidsi_wpdi : 1; // [7]
        REG32 __31_8 : 24;
    } b;
} REG_ANALOG_REG_PAD_GPIO13_CFG_T;

//pad_rfdig_gpio_cfg1
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_4_wpus : 1; // [0]
        REG32 pad_rfdig_gpio_4_se : 1;   // [1]
        REG32 pad_rfdig_gpio_4_ie : 1;   // [2]
        REG32 pad_rfdig_gpio_4_drv : 2;  // [4:3]
        REG32 pad_rfdig_gpio_3_wpus : 1; // [5]
        REG32 pad_rfdig_gpio_3_se : 1;   // [6]
        REG32 pad_rfdig_gpio_3_ie : 1;   // [7]
        REG32 pad_rfdig_gpio_3_drv : 2;  // [9:8]
        REG32 pad_rfdig_gpio_2_wpus : 1; // [10]
        REG32 pad_rfdig_gpio_2_se : 1;   // [11]
        REG32 pad_rfdig_gpio_2_ie : 1;   // [12]
        REG32 pad_rfdig_gpio_2_drv : 2;  // [14:13]
        REG32 pad_rfdig_gpio_1_wpus : 1; // [15]
        REG32 pad_rfdig_gpio_1_se : 1;   // [16]
        REG32 pad_rfdig_gpio_1_ie : 1;   // [17]
        REG32 pad_rfdig_gpio_1_drv : 2;  // [19:18]
        REG32 pad_rfdig_gpio_0_wpus : 1; // [20]
        REG32 pad_rfdig_gpio_0_se : 1;   // [21]
        REG32 pad_rfdig_gpio_0_ie : 1;   // [22]
        REG32 pad_rfdig_gpio_0_drv : 2;  // [24:23]
        REG32 pad_rf_wpdi : 1;           // [25]
        REG32 __31_26 : 6;
    } b;
} REG_ANALOG_REG_PAD_RFDIG_GPIO_CFG1_T;

//pad_rfdig_gpio_cfg2
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_7_wpus : 1; // [0]
        REG32 pad_rfdig_gpio_7_se : 1;   // [1]
        REG32 pad_rfdig_gpio_7_ie : 1;   // [2]
        REG32 pad_rfdig_gpio_7_drv : 2;  // [4:3]
        REG32 pad_rfdig_gpio_6_wpus : 1; // [5]
        REG32 pad_rfdig_gpio_6_se : 1;   // [6]
        REG32 pad_rfdig_gpio_6_ie : 1;   // [7]
        REG32 pad_rfdig_gpio_6_drv : 2;  // [9:8]
        REG32 pad_rfdig_gpio_5_wpus : 1; // [10]
        REG32 pad_rfdig_gpio_5_se : 1;   // [11]
        REG32 pad_rfdig_gpio_5_ie : 1;   // [12]
        REG32 pad_rfdig_gpio_5_drv : 2;  // [14:13]
        REG32 __31_15 : 17;
    } b;
} REG_ANALOG_REG_PAD_RFDIG_GPIO_CFG2_T;

//pad_sdmmc1_others_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sdmmc1_cmd_spu : 1; // [0]
        REG32 pad_sdmmc1_cmd_se : 1;  // [1]
        REG32 pad_sdmmc1_cmd_ie : 1;  // [2]
        REG32 pad_sdmmc1_cmd_drv : 4; // [6:3]
        REG32 pad_sdmmc1_clk_spu : 1; // [7]
        REG32 pad_sdmmc1_clk_se : 1;  // [8]
        REG32 pad_sdmmc1_clk_ie : 1;  // [9]
        REG32 pad_sdmmc1_clk_drv : 4; // [13:10]
        REG32 pad_sdmmc1_msen : 1;    // [14]
        REG32 pad_sdmmc1_ms : 1;      // [15]
        REG32 __31_16 : 16;
    } b;
} REG_ANALOG_REG_PAD_SDMMC1_OTHERS_CFG_T;

//pad_sdmmc1_data_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sdmmc1_data_3_spu : 1; // [0]
        REG32 pad_sdmmc1_data_3_se : 1;  // [1]
        REG32 pad_sdmmc1_data_3_ie : 1;  // [2]
        REG32 pad_sdmmc1_data_3_drv : 4; // [6:3]
        REG32 pad_sdmmc1_data_2_spu : 1; // [7]
        REG32 pad_sdmmc1_data_2_se : 1;  // [8]
        REG32 pad_sdmmc1_data_2_ie : 1;  // [9]
        REG32 pad_sdmmc1_data_2_drv : 4; // [13:10]
        REG32 pad_sdmmc1_data_1_spu : 1; // [14]
        REG32 pad_sdmmc1_data_1_se : 1;  // [15]
        REG32 pad_sdmmc1_data_1_ie : 1;  // [16]
        REG32 pad_sdmmc1_data_1_drv : 4; // [20:17]
        REG32 pad_sdmmc1_data_0_spu : 1; // [21]
        REG32 pad_sdmmc1_data_0_se : 1;  // [22]
        REG32 pad_sdmmc1_data_0_ie : 1;  // [23]
        REG32 pad_sdmmc1_data_0_drv : 4; // [27:24]
        REG32 __31_28 : 4;
    } b;
} REG_ANALOG_REG_PAD_SDMMC1_DATA_CFG_T;

//pad_sim_1_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sim_1_rst_spu : 1; // [0]
        REG32 pad_sim_1_rst_se : 1;  // [1]
        REG32 pad_sim_1_rst_ie : 1;  // [2]
        REG32 pad_sim_1_rst_drv : 4; // [6:3]
        REG32 pad_sim_1_dio_spu : 1; // [7]
        REG32 pad_sim_1_dio_se : 1;  // [8]
        REG32 pad_sim_1_dio_ie : 1;  // [9]
        REG32 pad_sim_1_dio_drv : 4; // [13:10]
        REG32 pad_sim_1_clk_spu : 1; // [14]
        REG32 pad_sim_1_clk_se : 1;  // [15]
        REG32 pad_sim_1_clk_ie : 1;  // [16]
        REG32 pad_sim_1_clk_drv : 4; // [20:17]
        REG32 pad_sim_1_msen : 1;    // [21]
        REG32 pad_sim_1_ms : 1;      // [22]
        REG32 __31_23 : 9;
    } b;
} REG_ANALOG_REG_PAD_SIM_1_CFG_T;

//pad_sim_2_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sim_2_rst_spu : 1; // [0]
        REG32 pad_sim_2_rst_se : 1;  // [1]
        REG32 pad_sim_2_rst_ie : 1;  // [2]
        REG32 pad_sim_2_rst_drv : 4; // [6:3]
        REG32 pad_sim_2_dio_spu : 1; // [7]
        REG32 pad_sim_2_dio_se : 1;  // [8]
        REG32 pad_sim_2_dio_ie : 1;  // [9]
        REG32 pad_sim_2_dio_drv : 4; // [13:10]
        REG32 pad_sim_2_clk_spu : 1; // [14]
        REG32 pad_sim_2_clk_se : 1;  // [15]
        REG32 pad_sim_2_clk_ie : 1;  // [16]
        REG32 pad_sim_2_clk_drv : 4; // [20:17]
        REG32 pad_sim_2_msen : 1;    // [21]
        REG32 pad_sim_2_ms : 1;      // [22]
        REG32 __31_23 : 9;
    } b;
} REG_ANALOG_REG_PAD_SIM_2_CFG_T;

//pad_spi_flash_cfg1
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_cs_spu : 1;    // [0]
        REG32 pad_spi_flash_cs_se : 1;     // [1]
        REG32 pad_spi_flash_cs_ie : 1;     // [2]
        REG32 pad_spi_flash_cs_drv : 4;    // [6:3]
        REG32 pad_spi_flash_clk_spu : 1;   // [7]
        REG32 pad_spi_flash_clk_se : 1;    // [8]
        REG32 pad_spi_flash_clk_ie : 1;    // [9]
        REG32 pad_spi_flash_clk_drv : 4;   // [13:10]
        REG32 pad_spi_flash_sel_spu : 1;   // [14]
        REG32 pad_spi_flash_sel_se : 1;    // [15]
        REG32 pad_spi_flash_sel_ie : 1;    // [16]
        REG32 pad_spi_flash_sel_drv : 4;   // [20:17]
        REG32 pad_nand_flash_sel_wpus : 1; // [21]
        REG32 pad_nand_flash_sel_se : 1;   // [22]
        REG32 pad_nand_flash_sel_ie : 1;   // [23]
        REG32 pad_nand_flash_sel_drv : 2;  // [25:24]
        REG32 __31_26 : 6;
    } b;
} REG_ANALOG_REG_PAD_SPI_FLASH_CFG1_T;

//pad_spi_flash_cfg2
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_sio_3_spu : 1; // [0]
        REG32 pad_spi_flash_sio_3_se : 1;  // [1]
        REG32 pad_spi_flash_sio_3_ie : 1;  // [2]
        REG32 pad_spi_flash_sio_3_drv : 4; // [6:3]
        REG32 pad_spi_flash_sio_2_spu : 1; // [7]
        REG32 pad_spi_flash_sio_2_se : 1;  // [8]
        REG32 pad_spi_flash_sio_2_ie : 1;  // [9]
        REG32 pad_spi_flash_sio_2_drv : 4; // [13:10]
        REG32 pad_spi_flash_sio_1_spu : 1; // [14]
        REG32 pad_spi_flash_sio_1_se : 1;  // [15]
        REG32 pad_spi_flash_sio_1_ie : 1;  // [16]
        REG32 pad_spi_flash_sio_1_drv : 4; // [20:17]
        REG32 pad_spi_flash_sio_0_spu : 1; // [21]
        REG32 pad_spi_flash_sio_0_se : 1;  // [22]
        REG32 pad_spi_flash_sio_0_ie : 1;  // [23]
        REG32 pad_spi_flash_sio_0_drv : 4; // [27:24]
        REG32 pad_spi_flash_msen : 1;      // [28]
        REG32 pad_spi_flash_ms : 1;        // [29]
        REG32 __31_30 : 2;
    } b;
} REG_ANALOG_REG_PAD_SPI_FLASH_CFG2_T;

//pad_spi_lcd_cfg1
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_lcd_cs_spu : 1;  // [0]
        REG32 pad_spi_lcd_cs_se : 1;   // [1]
        REG32 pad_spi_lcd_cs_ie : 1;   // [2]
        REG32 pad_spi_lcd_cs_drv : 4;  // [6:3]
        REG32 pad_spi_lcd_clk_spu : 1; // [7]
        REG32 pad_spi_lcd_clk_se : 1;  // [8]
        REG32 pad_spi_lcd_clk_ie : 1;  // [9]
        REG32 pad_spi_lcd_clk_drv : 4; // [13:10]
        REG32 __31_14 : 18;
    } b;
} REG_ANALOG_REG_PAD_SPI_LCD_CFG1_T;

//pad_spi_lcd_cfg2
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_lcd_sio_spu : 1;    // [0]
        REG32 pad_spi_lcd_sio_se : 1;     // [1]
        REG32 pad_spi_lcd_sio_ie : 1;     // [2]
        REG32 pad_spi_lcd_sio_drv : 4;    // [6:3]
        REG32 pad_spi_lcd_select_spu : 1; // [7]
        REG32 pad_spi_lcd_select_se : 1;  // [8]
        REG32 pad_spi_lcd_select_ie : 1;  // [9]
        REG32 pad_spi_lcd_select_drv : 4; // [13:10]
        REG32 pad_spi_lcd_sdc_spu : 1;    // [14]
        REG32 pad_spi_lcd_sdc_se : 1;     // [15]
        REG32 pad_spi_lcd_sdc_ie : 1;     // [16]
        REG32 pad_spi_lcd_sdc_drv : 4;    // [20:17]
        REG32 __31_21 : 11;
    } b;
} REG_ANALOG_REG_PAD_SPI_LCD_CFG2_T;

//pad_tst_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_tst_h_wpus : 1; // [0]
        REG32 pad_tst_h_se : 1;   // [1]
        REG32 pad_tst_h_ie : 1;   // [2]
        REG32 pad_tst_h_drv : 2;  // [4:3]
        REG32 __31_5 : 27;
    } b;
} REG_ANALOG_REG_PAD_TST_CFG_T;

//pad_uart_1_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_19_wpus : 1; // [0]
        REG32 pad_gpio_19_se : 1;   // [1]
        REG32 pad_gpio_19_ie : 1;   // [2]
        REG32 pad_gpio_19_drv : 2;  // [4:3]
        REG32 pad_gpio_18_wpus : 1; // [5]
        REG32 pad_gpio_18_se : 1;   // [6]
        REG32 pad_gpio_18_ie : 1;   // [7]
        REG32 pad_gpio_18_drv : 2;  // [9:8]
        REG32 __31_10 : 22;
    } b;
} REG_ANALOG_REG_PAD_UART_1_CFG_T;

//pad_uart_2_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_21_wpus : 1; // [0]
        REG32 pad_gpio_21_se : 1;   // [1]
        REG32 pad_gpio_21_ie : 1;   // [2]
        REG32 pad_gpio_21_drv : 2;  // [4:3]
        REG32 pad_gpio_20_wpus : 1; // [5]
        REG32 pad_gpio_20_se : 1;   // [6]
        REG32 pad_gpio_20_ie : 1;   // [7]
        REG32 pad_gpio_20_drv : 2;  // [9:8]
        REG32 pad_gpio_23_wpus : 1; // [10]
        REG32 pad_gpio_23_se : 1;   // [11]
        REG32 pad_gpio_23_ie : 1;   // [12]
        REG32 pad_gpio_23_drv : 2;  // [14:13]
        REG32 pad_gpio_22_wpus : 1; // [15]
        REG32 pad_gpio_22_se : 1;   // [16]
        REG32 pad_gpio_22_ie : 1;   // [17]
        REG32 pad_gpio_22_drv : 2;  // [19:18]
        REG32 __31_20 : 12;
    } b;
} REG_ANALOG_REG_PAD_UART_2_CFG_T;

//pad_secure_boot_mode_cfg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_secure_boot_mode_wpus : 1; // [0]
        REG32 pad_secure_boot_mode_se : 1;   // [1]
        REG32 pad_secure_boot_mode_ie : 1;   // [2]
        REG32 pad_secure_boot_mode_drv : 2;  // [4:3]
        REG32 __31_5 : 27;
    } b;
} REG_ANALOG_REG_PAD_SECURE_BOOT_MODE_CFG_T;

#endif
