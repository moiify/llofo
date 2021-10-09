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

#ifndef _IOMUX_H_
#define _IOMUX_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'iomux'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// IOMUX_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_IOMUX_BASE 0x0510C000
#else
#define REG_IOMUX_BASE 0x5010C000
#endif

typedef volatile struct
{
    REG32 pad_spi_flash_clk_cfg_reg;    //0x00000000
    REG32 pad_spi_flash_cs_cfg_reg;     //0x00000004
    REG32 pad_spi_flash_sel_cfg_reg;    //0x00000008
    REG32 pad_spi_flash_sio_0_cfg_reg;  //0x0000000C
    REG32 pad_spi_flash_sio_1_cfg_reg;  //0x00000010
    REG32 pad_spi_flash_sio_2_cfg_reg;  //0x00000014
    REG32 pad_spi_flash_sio_3_cfg_reg;  //0x00000018
    REG32 pad_sdmmc1_clk_cfg_reg;       //0x0000001C
    REG32 pad_sdmmc1_cmd_cfg_reg;       //0x00000020
    REG32 pad_sdmmc1_data_0_cfg_reg;    //0x00000024
    REG32 pad_sdmmc1_data_1_cfg_reg;    //0x00000028
    REG32 pad_sdmmc1_data_2_cfg_reg;    //0x0000002C
    REG32 pad_sdmmc1_data_3_cfg_reg;    //0x00000030
    REG32 pad_aud_da_sync_cfg_reg;      //0x00000034
    REG32 pad_aud_da_d1_cfg_reg;        //0x00000038
    REG32 pad_aud_da_d0_cfg_reg;        //0x0000003C
    REG32 pad_aud_ad_sync_cfg_reg;      //0x00000040
    REG32 pad_aud_ad_d0_cfg_reg;        //0x00000044
    REG32 pad_aud_sclk_cfg_reg;         //0x00000048
    REG32 pad_adi_sda_cfg_reg;          //0x0000004C
    REG32 pad_adi_sync_cfg_reg;         //0x00000050
    REG32 pad_adi_scl_cfg_reg;          //0x00000054
    REG32 pad_spi_lcd_sio_cfg_reg;      //0x00000058
    REG32 pad_spi_lcd_sdc_cfg_reg;      //0x0000005C
    REG32 pad_spi_lcd_clk_cfg_reg;      //0x00000060
    REG32 pad_spi_lcd_cs_cfg_reg;       //0x00000064
    REG32 pad_spi_lcd_select_cfg_reg;   //0x00000068
    REG32 pad_lcd_fmark_cfg_reg;        //0x0000006C
    REG32 pad_lcd_rstb_cfg_reg;         //0x00000070
    REG32 pad_i2c_m1_scl_cfg_reg;       //0x00000074
    REG32 pad_i2c_m1_sda_cfg_reg;       //0x00000078
    REG32 pad_camera_rst_l_cfg_reg;     //0x0000007C
    REG32 pad_camera_pwdn_cfg_reg;      //0x00000080
    REG32 pad_camera_ref_clk_cfg_reg;   //0x00000084
    REG32 pad_spi_camera_si_0_cfg_reg;  //0x00000088
    REG32 pad_spi_camera_si_1_cfg_reg;  //0x0000008C
    REG32 pad_spi_camera_sck_cfg_reg;   //0x00000090
    REG32 pad_gpio_13_cfg_reg;          //0x00000094
    REG32 pad_gpio_0_cfg_reg;           //0x00000098
    REG32 pad_gpio_1_cfg_reg;           //0x0000009C
    REG32 pad_gpio_2_cfg_reg;           //0x000000A0
    REG32 pad_gpio_3_cfg_reg;           //0x000000A4
    REG32 pad_gpio_4_cfg_reg;           //0x000000A8
    REG32 pad_gpio_5_cfg_reg;           //0x000000AC
    REG32 pad_gpio_7_cfg_reg;           //0x000000B0
    REG32 pad_ap_jtag_tck_cfg_reg;      //0x000000B4
    REG32 pad_ap_jtag_trst_cfg_reg;     //0x000000B8
    REG32 pad_ap_jtag_tms_cfg_reg;      //0x000000BC
    REG32 pad_ap_jtag_tdi_cfg_reg;      //0x000000C0
    REG32 pad_ap_jtag_tdo_cfg_reg;      //0x000000C4
    REG32 pad_gpio_14_cfg_reg;          //0x000000C8
    REG32 pad_gpio_15_cfg_reg;          //0x000000CC
    REG32 pad_gpio_18_cfg_reg;          //0x000000D0
    REG32 pad_gpio_19_cfg_reg;          //0x000000D4
    REG32 pad_gpio_20_cfg_reg;          //0x000000D8
    REG32 pad_gpio_21_cfg_reg;          //0x000000DC
    REG32 pad_gpio_22_cfg_reg;          //0x000000E0
    REG32 pad_gpio_23_cfg_reg;          //0x000000E4
    REG32 pad_gpio_8_cfg_reg;           //0x000000E8
    REG32 pad_gpio_9_cfg_reg;           //0x000000EC
    REG32 pad_gpio_10_cfg_reg;          //0x000000F0
    REG32 pad_gpio_11_cfg_reg;          //0x000000F4
    REG32 pad_gpio_12_cfg_reg;          //0x000000F8
    REG32 pad_keyin_0_cfg_reg;          //0x000000FC
    REG32 pad_keyin_1_cfg_reg;          //0x00000100
    REG32 pad_keyin_2_cfg_reg;          //0x00000104
    REG32 pad_keyin_3_cfg_reg;          //0x00000108
    REG32 pad_keyin_4_cfg_reg;          //0x0000010C
    REG32 pad_keyin_5_cfg_reg;          //0x00000110
    REG32 pad_keyout_0_cfg_reg;         //0x00000114
    REG32 pad_keyout_1_cfg_reg;         //0x00000118
    REG32 pad_keyout_2_cfg_reg;         //0x0000011C
    REG32 pad_keyout_3_cfg_reg;         //0x00000120
    REG32 pad_keyout_4_cfg_reg;         //0x00000124
    REG32 pad_keyout_5_cfg_reg;         //0x00000128
    REG32 pad_debug_host_rx_cfg_reg;    //0x0000012C
    REG32 pad_debug_host_tx_cfg_reg;    //0x00000130
    REG32 pad_debug_host_clk_cfg_reg;   //0x00000134
    REG32 pad_sim_1_clk_cfg_reg;        //0x00000138
    REG32 pad_sim_1_dio_cfg_reg;        //0x0000013C
    REG32 pad_sim_1_rst_cfg_reg;        //0x00000140
    REG32 pad_sim_2_clk_cfg_reg;        //0x00000144
    REG32 pad_sim_2_dio_cfg_reg;        //0x00000148
    REG32 pad_sim_2_rst_cfg_reg;        //0x0000014C
    REG32 pad_rfdig_gpio_0_cfg_reg;     //0x00000150
    REG32 pad_rfdig_gpio_1_cfg_reg;     //0x00000154
    REG32 pad_rfdig_gpio_2_cfg_reg;     //0x00000158
    REG32 pad_rfdig_gpio_3_cfg_reg;     //0x0000015C
    REG32 pad_rfdig_gpio_4_cfg_reg;     //0x00000160
    REG32 pad_rfdig_gpio_5_cfg_reg;     //0x00000164
    REG32 pad_rfdig_gpio_6_cfg_reg;     //0x00000168
    REG32 pad_rfdig_gpio_7_cfg_reg;     //0x0000016C
    REG32 pad_secure_boot_mode_cfg_reg; //0x00000170
    REG32 pad_nand_flash_sel_cfg_reg;   //0x00000174
} HWP_IOMUX_T;

#define hwp_iomux ((HWP_IOMUX_T *)REG_ACCESS_ADDRESS(REG_IOMUX_BASE))

//pad_spi_flash_clk_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_clk_sel : 4;     // [3:0]
        REG32 pad_spi_flash_clk_ana : 4;     // [7:4]
        REG32 pad_spi_flash_clk_pull_dn : 1; // [8]
        REG32 pad_spi_flash_clk_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_flash_clk_pull_frc : 1;     // [16]
        REG32 pad_spi_flash_clk_oen_reg : 1;      // [17]
        REG32 pad_spi_flash_clk_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_flash_clk_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_flash_clk_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_flash_clk_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_FLASH_CLK_CFG_REG_T;

//pad_spi_flash_cs_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_cs_sel : 4;     // [3:0]
        REG32 pad_spi_flash_cs_ana : 4;     // [7:4]
        REG32 pad_spi_flash_cs_pull_dn : 1; // [8]
        REG32 pad_spi_flash_cs_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_flash_cs_pull_frc : 1;     // [16]
        REG32 pad_spi_flash_cs_oen_reg : 1;      // [17]
        REG32 pad_spi_flash_cs_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_flash_cs_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_flash_cs_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_flash_cs_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_FLASH_CS_CFG_REG_T;

//pad_spi_flash_sel_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_sel_sel : 4;     // [3:0]
        REG32 pad_spi_flash_sel_ana : 4;     // [7:4]
        REG32 pad_spi_flash_sel_pull_dn : 1; // [8]
        REG32 pad_spi_flash_sel_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_flash_sel_pull_frc : 1;     // [16]
        REG32 pad_spi_flash_sel_oen_reg : 1;      // [17]
        REG32 pad_spi_flash_sel_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_flash_sel_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_flash_sel_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_flash_sel_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_FLASH_SEL_CFG_REG_T;

//pad_spi_flash_sio_0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_sio_0_sel : 4;     // [3:0]
        REG32 pad_spi_flash_sio_0_ana : 4;     // [7:4]
        REG32 pad_spi_flash_sio_0_pull_dn : 1; // [8]
        REG32 pad_spi_flash_sio_0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_flash_sio_0_pull_frc : 1;     // [16]
        REG32 pad_spi_flash_sio_0_oen_reg : 1;      // [17]
        REG32 pad_spi_flash_sio_0_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_flash_sio_0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_flash_sio_0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_flash_sio_0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_FLASH_SIO_0_CFG_REG_T;

//pad_spi_flash_sio_1_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_sio_1_sel : 4;     // [3:0]
        REG32 pad_spi_flash_sio_1_ana : 4;     // [7:4]
        REG32 pad_spi_flash_sio_1_pull_dn : 1; // [8]
        REG32 pad_spi_flash_sio_1_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_flash_sio_1_pull_frc : 1;     // [16]
        REG32 pad_spi_flash_sio_1_oen_reg : 1;      // [17]
        REG32 pad_spi_flash_sio_1_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_flash_sio_1_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_flash_sio_1_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_flash_sio_1_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_FLASH_SIO_1_CFG_REG_T;

//pad_spi_flash_sio_2_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_sio_2_sel : 4;     // [3:0]
        REG32 pad_spi_flash_sio_2_ana : 4;     // [7:4]
        REG32 pad_spi_flash_sio_2_pull_dn : 1; // [8]
        REG32 pad_spi_flash_sio_2_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_flash_sio_2_pull_frc : 1;     // [16]
        REG32 pad_spi_flash_sio_2_oen_reg : 1;      // [17]
        REG32 pad_spi_flash_sio_2_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_flash_sio_2_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_flash_sio_2_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_flash_sio_2_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_FLASH_SIO_2_CFG_REG_T;

//pad_spi_flash_sio_3_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_flash_sio_3_sel : 4;     // [3:0]
        REG32 pad_spi_flash_sio_3_ana : 4;     // [7:4]
        REG32 pad_spi_flash_sio_3_pull_dn : 1; // [8]
        REG32 pad_spi_flash_sio_3_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_flash_sio_3_pull_frc : 1;     // [16]
        REG32 pad_spi_flash_sio_3_oen_reg : 1;      // [17]
        REG32 pad_spi_flash_sio_3_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_flash_sio_3_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_flash_sio_3_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_flash_sio_3_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_FLASH_SIO_3_CFG_REG_T;

//pad_sdmmc1_clk_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sdmmc1_clk_sel : 4;     // [3:0]
        REG32 pad_sdmmc1_clk_ana : 4;     // [7:4]
        REG32 pad_sdmmc1_clk_pull_dn : 1; // [8]
        REG32 pad_sdmmc1_clk_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sdmmc1_clk_pull_frc : 1;     // [16]
        REG32 pad_sdmmc1_clk_oen_reg : 1;      // [17]
        REG32 pad_sdmmc1_clk_drv_strength : 2; // [19:18], write set
        REG32 pad_sdmmc1_clk_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sdmmc1_clk_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sdmmc1_clk_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SDMMC1_CLK_CFG_REG_T;

//pad_sdmmc1_cmd_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sdmmc1_cmd_sel : 4;     // [3:0]
        REG32 pad_sdmmc1_cmd_ana : 4;     // [7:4]
        REG32 pad_sdmmc1_cmd_pull_dn : 1; // [8]
        REG32 pad_sdmmc1_cmd_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sdmmc1_cmd_pull_frc : 1;     // [16]
        REG32 pad_sdmmc1_cmd_oen_reg : 1;      // [17]
        REG32 pad_sdmmc1_cmd_drv_strength : 2; // [19:18], write set
        REG32 pad_sdmmc1_cmd_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sdmmc1_cmd_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sdmmc1_cmd_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SDMMC1_CMD_CFG_REG_T;

//pad_sdmmc1_data_0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sdmmc1_data_0_sel : 4;     // [3:0]
        REG32 pad_sdmmc1_data_0_ana : 4;     // [7:4]
        REG32 pad_sdmmc1_data_0_pull_dn : 1; // [8]
        REG32 pad_sdmmc1_data_0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sdmmc1_data_0_pull_frc : 1;     // [16]
        REG32 pad_sdmmc1_data_0_oen_reg : 1;      // [17]
        REG32 pad_sdmmc1_data_0_drv_strength : 2; // [19:18], write set
        REG32 pad_sdmmc1_data_0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sdmmc1_data_0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sdmmc1_data_0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SDMMC1_DATA_0_CFG_REG_T;

//pad_sdmmc1_data_1_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sdmmc1_data_1_sel : 4;     // [3:0]
        REG32 pad_sdmmc1_data_1_ana : 4;     // [7:4]
        REG32 pad_sdmmc1_data_1_pull_dn : 1; // [8]
        REG32 pad_sdmmc1_data_1_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sdmmc1_data_1_pull_frc : 1;     // [16]
        REG32 pad_sdmmc1_data_1_oen_reg : 1;      // [17]
        REG32 pad_sdmmc1_data_1_drv_strength : 2; // [19:18], write set
        REG32 pad_sdmmc1_data_1_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sdmmc1_data_1_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sdmmc1_data_1_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SDMMC1_DATA_1_CFG_REG_T;

//pad_sdmmc1_data_2_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sdmmc1_data_2_sel : 4;     // [3:0]
        REG32 pad_sdmmc1_data_2_ana : 4;     // [7:4]
        REG32 pad_sdmmc1_data_2_pull_dn : 1; // [8]
        REG32 pad_sdmmc1_data_2_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sdmmc1_data_2_pull_frc : 1;     // [16]
        REG32 pad_sdmmc1_data_2_oen_reg : 1;      // [17]
        REG32 pad_sdmmc1_data_2_drv_strength : 2; // [19:18], write set
        REG32 pad_sdmmc1_data_2_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sdmmc1_data_2_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sdmmc1_data_2_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SDMMC1_DATA_2_CFG_REG_T;

//pad_sdmmc1_data_3_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sdmmc1_data_3_sel : 4;     // [3:0]
        REG32 pad_sdmmc1_data_3_ana : 4;     // [7:4]
        REG32 pad_sdmmc1_data_3_pull_dn : 1; // [8]
        REG32 pad_sdmmc1_data_3_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sdmmc1_data_3_pull_frc : 1;     // [16]
        REG32 pad_sdmmc1_data_3_oen_reg : 1;      // [17]
        REG32 pad_sdmmc1_data_3_drv_strength : 2; // [19:18], write set
        REG32 pad_sdmmc1_data_3_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sdmmc1_data_3_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sdmmc1_data_3_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SDMMC1_DATA_3_CFG_REG_T;

//pad_aud_da_sync_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_aud_da_sync_sel : 4;     // [3:0]
        REG32 pad_aud_da_sync_ana : 4;     // [7:4]
        REG32 pad_aud_da_sync_pull_dn : 1; // [8]
        REG32 pad_aud_da_sync_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_aud_da_sync_pull_frc : 1;     // [16]
        REG32 pad_aud_da_sync_oen_reg : 1;      // [17]
        REG32 pad_aud_da_sync_drv_strength : 2; // [19:18], write set
        REG32 pad_aud_da_sync_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_aud_da_sync_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_aud_da_sync_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AUD_DA_SYNC_CFG_REG_T;

//pad_aud_da_d1_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_aud_da_d1_sel : 4;     // [3:0]
        REG32 pad_aud_da_d1_ana : 4;     // [7:4]
        REG32 pad_aud_da_d1_pull_dn : 1; // [8]
        REG32 pad_aud_da_d1_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_aud_da_d1_pull_frc : 1;     // [16]
        REG32 pad_aud_da_d1_oen_reg : 1;      // [17]
        REG32 pad_aud_da_d1_drv_strength : 2; // [19:18], write set
        REG32 pad_aud_da_d1_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_aud_da_d1_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_aud_da_d1_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AUD_DA_D1_CFG_REG_T;

//pad_aud_da_d0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_aud_da_d0_sel : 4;     // [3:0]
        REG32 pad_aud_da_d0_ana : 4;     // [7:4]
        REG32 pad_aud_da_d0_pull_dn : 1; // [8]
        REG32 pad_aud_da_d0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_aud_da_d0_pull_frc : 1;     // [16]
        REG32 pad_aud_da_d0_oen_reg : 1;      // [17]
        REG32 pad_aud_da_d0_drv_strength : 2; // [19:18], write set
        REG32 pad_aud_da_d0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_aud_da_d0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_aud_da_d0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AUD_DA_D0_CFG_REG_T;

//pad_aud_ad_sync_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_aud_ad_sync_sel : 4;     // [3:0]
        REG32 pad_aud_ad_sync_ana : 4;     // [7:4]
        REG32 pad_aud_ad_sync_pull_dn : 1; // [8]
        REG32 pad_aud_ad_sync_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_aud_ad_sync_pull_frc : 1;     // [16]
        REG32 pad_aud_ad_sync_oen_reg : 1;      // [17]
        REG32 pad_aud_ad_sync_drv_strength : 2; // [19:18], write set
        REG32 pad_aud_ad_sync_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_aud_ad_sync_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_aud_ad_sync_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AUD_AD_SYNC_CFG_REG_T;

//pad_aud_ad_d0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_aud_ad_d0_sel : 4;     // [3:0]
        REG32 pad_aud_ad_d0_ana : 4;     // [7:4]
        REG32 pad_aud_ad_d0_pull_dn : 1; // [8]
        REG32 pad_aud_ad_d0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_aud_ad_d0_pull_frc : 1;     // [16]
        REG32 pad_aud_ad_d0_oen_reg : 1;      // [17]
        REG32 pad_aud_ad_d0_drv_strength : 2; // [19:18], write set
        REG32 pad_aud_ad_d0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_aud_ad_d0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_aud_ad_d0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AUD_AD_D0_CFG_REG_T;

//pad_aud_sclk_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_aud_sclk_sel : 4;     // [3:0]
        REG32 pad_aud_sclk_ana : 4;     // [7:4]
        REG32 pad_aud_sclk_pull_dn : 1; // [8]
        REG32 pad_aud_sclk_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_aud_sclk_pull_frc : 1;     // [16]
        REG32 pad_aud_sclk_oen_reg : 1;      // [17]
        REG32 pad_aud_sclk_drv_strength : 2; // [19:18], write set
        REG32 pad_aud_sclk_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_aud_sclk_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_aud_sclk_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AUD_SCLK_CFG_REG_T;

//pad_adi_sda_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_adi_sda_sel : 4;     // [3:0]
        REG32 pad_adi_sda_ana : 4;     // [7:4]
        REG32 pad_adi_sda_pull_dn : 1; // [8]
        REG32 pad_adi_sda_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_adi_sda_pull_frc : 1;     // [16]
        REG32 pad_adi_sda_oen_reg : 1;      // [17]
        REG32 pad_adi_sda_drv_strength : 2; // [19:18], write set
        REG32 pad_adi_sda_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_adi_sda_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_adi_sda_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_ADI_SDA_CFG_REG_T;

//pad_adi_sync_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_adi_sync_sel : 4;     // [3:0]
        REG32 pad_adi_sync_ana : 4;     // [7:4]
        REG32 pad_adi_sync_pull_dn : 1; // [8]
        REG32 pad_adi_sync_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_adi_sync_pull_frc : 1;     // [16]
        REG32 pad_adi_sync_oen_reg : 1;      // [17]
        REG32 pad_adi_sync_drv_strength : 2; // [19:18], write set
        REG32 pad_adi_sync_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_adi_sync_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_adi_sync_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_ADI_SYNC_CFG_REG_T;

//pad_adi_scl_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_adi_scl_sel : 4;     // [3:0]
        REG32 pad_adi_scl_ana : 4;     // [7:4]
        REG32 pad_adi_scl_pull_dn : 1; // [8]
        REG32 pad_adi_scl_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_adi_scl_pull_frc : 1;     // [16]
        REG32 pad_adi_scl_oen_reg : 1;      // [17]
        REG32 pad_adi_scl_drv_strength : 2; // [19:18], write set
        REG32 pad_adi_scl_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_adi_scl_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_adi_scl_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_ADI_SCL_CFG_REG_T;

//pad_spi_lcd_sio_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_lcd_sio_sel : 4;     // [3:0]
        REG32 pad_spi_lcd_sio_ana : 4;     // [7:4]
        REG32 pad_spi_lcd_sio_pull_dn : 1; // [8]
        REG32 pad_spi_lcd_sio_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_lcd_sio_pull_frc : 1;     // [16]
        REG32 pad_spi_lcd_sio_oen_reg : 1;      // [17]
        REG32 pad_spi_lcd_sio_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_lcd_sio_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_lcd_sio_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_lcd_sio_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_LCD_SIO_CFG_REG_T;

//pad_spi_lcd_sdc_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_lcd_sdc_sel : 4;     // [3:0]
        REG32 pad_spi_lcd_sdc_ana : 4;     // [7:4]
        REG32 pad_spi_lcd_sdc_pull_dn : 1; // [8]
        REG32 pad_spi_lcd_sdc_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_lcd_sdc_pull_frc : 1;     // [16]
        REG32 pad_spi_lcd_sdc_oen_reg : 1;      // [17]
        REG32 pad_spi_lcd_sdc_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_lcd_sdc_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_lcd_sdc_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_lcd_sdc_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_LCD_SDC_CFG_REG_T;

//pad_spi_lcd_clk_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_lcd_clk_sel : 4;     // [3:0]
        REG32 pad_spi_lcd_clk_ana : 4;     // [7:4]
        REG32 pad_spi_lcd_clk_pull_dn : 1; // [8]
        REG32 pad_spi_lcd_clk_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_lcd_clk_pull_frc : 1;     // [16]
        REG32 pad_spi_lcd_clk_oen_reg : 1;      // [17]
        REG32 pad_spi_lcd_clk_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_lcd_clk_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_lcd_clk_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_lcd_clk_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_LCD_CLK_CFG_REG_T;

//pad_spi_lcd_cs_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_lcd_cs_sel : 4;     // [3:0]
        REG32 pad_spi_lcd_cs_ana : 4;     // [7:4]
        REG32 pad_spi_lcd_cs_pull_dn : 1; // [8]
        REG32 pad_spi_lcd_cs_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_lcd_cs_pull_frc : 1;     // [16]
        REG32 pad_spi_lcd_cs_oen_reg : 1;      // [17]
        REG32 pad_spi_lcd_cs_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_lcd_cs_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_lcd_cs_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_lcd_cs_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_LCD_CS_CFG_REG_T;

//pad_spi_lcd_select_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_lcd_select_sel : 4;     // [3:0]
        REG32 pad_spi_lcd_select_ana : 4;     // [7:4]
        REG32 pad_spi_lcd_select_pull_dn : 1; // [8]
        REG32 pad_spi_lcd_select_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_lcd_select_pull_frc : 1;     // [16]
        REG32 pad_spi_lcd_select_oen_reg : 1;      // [17]
        REG32 pad_spi_lcd_select_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_lcd_select_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_lcd_select_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_lcd_select_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_LCD_SELECT_CFG_REG_T;

//pad_lcd_fmark_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_lcd_fmark_sel : 4;     // [3:0]
        REG32 pad_lcd_fmark_ana : 4;     // [7:4]
        REG32 pad_lcd_fmark_pull_dn : 1; // [8]
        REG32 pad_lcd_fmark_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_lcd_fmark_pull_frc : 1;     // [16]
        REG32 pad_lcd_fmark_oen_reg : 1;      // [17]
        REG32 pad_lcd_fmark_drv_strength : 2; // [19:18], write set
        REG32 pad_lcd_fmark_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_lcd_fmark_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_lcd_fmark_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_LCD_FMARK_CFG_REG_T;

//pad_lcd_rstb_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_lcd_rstb_sel : 4;     // [3:0]
        REG32 pad_lcd_rstb_ana : 4;     // [7:4]
        REG32 pad_lcd_rstb_pull_dn : 1; // [8]
        REG32 pad_lcd_rstb_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_lcd_rstb_pull_frc : 1;     // [16]
        REG32 pad_lcd_rstb_oen_reg : 1;      // [17]
        REG32 pad_lcd_rstb_drv_strength : 2; // [19:18], write set
        REG32 pad_lcd_rstb_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_lcd_rstb_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_lcd_rstb_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_LCD_RSTB_CFG_REG_T;

//pad_i2c_m1_scl_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_i2c_m1_scl_sel : 4;     // [3:0]
        REG32 pad_i2c_m1_scl_ana : 4;     // [7:4]
        REG32 pad_i2c_m1_scl_pull_dn : 1; // [8]
        REG32 pad_i2c_m1_scl_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_i2c_m1_scl_pull_frc : 1;     // [16]
        REG32 pad_i2c_m1_scl_oen_reg : 1;      // [17]
        REG32 pad_i2c_m1_scl_drv_strength : 2; // [19:18], write set
        REG32 pad_i2c_m1_scl_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_i2c_m1_scl_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_i2c_m1_scl_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_I2C_M1_SCL_CFG_REG_T;

//pad_i2c_m1_sda_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_i2c_m1_sda_sel : 4;     // [3:0]
        REG32 pad_i2c_m1_sda_ana : 4;     // [7:4]
        REG32 pad_i2c_m1_sda_pull_dn : 1; // [8]
        REG32 pad_i2c_m1_sda_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_i2c_m1_sda_pull_frc : 1;     // [16]
        REG32 pad_i2c_m1_sda_oen_reg : 1;      // [17]
        REG32 pad_i2c_m1_sda_drv_strength : 2; // [19:18], write set
        REG32 pad_i2c_m1_sda_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_i2c_m1_sda_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_i2c_m1_sda_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_I2C_M1_SDA_CFG_REG_T;

//pad_camera_rst_l_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_camera_rst_l_sel : 4;     // [3:0]
        REG32 pad_camera_rst_l_ana : 4;     // [7:4]
        REG32 pad_camera_rst_l_pull_dn : 1; // [8]
        REG32 pad_camera_rst_l_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_camera_rst_l_pull_frc : 1;     // [16]
        REG32 pad_camera_rst_l_oen_reg : 1;      // [17]
        REG32 pad_camera_rst_l_drv_strength : 2; // [19:18], write set
        REG32 pad_camera_rst_l_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_camera_rst_l_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_camera_rst_l_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_CAMERA_RST_L_CFG_REG_T;

//pad_camera_pwdn_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_camera_pwdn_sel : 4;     // [3:0]
        REG32 pad_camera_pwdn_ana : 4;     // [7:4]
        REG32 pad_camera_pwdn_pull_dn : 1; // [8]
        REG32 pad_camera_pwdn_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_camera_pwdn_pull_frc : 1;     // [16]
        REG32 pad_camera_pwdn_oen_reg : 1;      // [17]
        REG32 pad_camera_pwdn_drv_strength : 2; // [19:18], write set
        REG32 pad_camera_pwdn_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_camera_pwdn_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_camera_pwdn_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_CAMERA_PWDN_CFG_REG_T;

//pad_camera_ref_clk_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_camera_ref_clk_sel : 4;     // [3:0]
        REG32 pad_camera_ref_clk_ana : 4;     // [7:4]
        REG32 pad_camera_ref_clk_pull_dn : 1; // [8]
        REG32 pad_camera_ref_clk_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_camera_ref_clk_pull_frc : 1;     // [16]
        REG32 pad_camera_ref_clk_oen_reg : 1;      // [17]
        REG32 pad_camera_ref_clk_drv_strength : 2; // [19:18], write set
        REG32 pad_camera_ref_clk_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_camera_ref_clk_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_camera_ref_clk_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_CAMERA_REF_CLK_CFG_REG_T;

//pad_spi_camera_si_0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_camera_si_0_sel : 4;     // [3:0]
        REG32 pad_spi_camera_si_0_ana : 4;     // [7:4]
        REG32 pad_spi_camera_si_0_pull_dn : 1; // [8]
        REG32 pad_spi_camera_si_0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_camera_si_0_pull_frc : 1;     // [16]
        REG32 pad_spi_camera_si_0_oen_reg : 1;      // [17]
        REG32 pad_spi_camera_si_0_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_camera_si_0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_camera_si_0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_camera_si_0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_CAMERA_SI_0_CFG_REG_T;

//pad_spi_camera_si_1_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_camera_si_1_sel : 4;     // [3:0]
        REG32 pad_spi_camera_si_1_ana : 4;     // [7:4]
        REG32 pad_spi_camera_si_1_pull_dn : 1; // [8]
        REG32 pad_spi_camera_si_1_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_camera_si_1_pull_frc : 1;     // [16]
        REG32 pad_spi_camera_si_1_oen_reg : 1;      // [17]
        REG32 pad_spi_camera_si_1_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_camera_si_1_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_camera_si_1_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_camera_si_1_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_CAMERA_SI_1_CFG_REG_T;

//pad_spi_camera_sck_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_spi_camera_sck_sel : 4;     // [3:0]
        REG32 pad_spi_camera_sck_ana : 4;     // [7:4]
        REG32 pad_spi_camera_sck_pull_dn : 1; // [8]
        REG32 pad_spi_camera_sck_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_spi_camera_sck_pull_frc : 1;     // [16]
        REG32 pad_spi_camera_sck_oen_reg : 1;      // [17]
        REG32 pad_spi_camera_sck_drv_strength : 2; // [19:18], write set
        REG32 pad_spi_camera_sck_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_spi_camera_sck_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_spi_camera_sck_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SPI_CAMERA_SCK_CFG_REG_T;

//pad_gpio_13_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_13_sel : 4;     // [3:0]
        REG32 pad_gpio_13_ana : 4;     // [7:4]
        REG32 pad_gpio_13_pull_dn : 1; // [8]
        REG32 pad_gpio_13_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_13_pull_frc : 1;     // [16]
        REG32 pad_gpio_13_oen_reg : 1;      // [17]
        REG32 pad_gpio_13_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_13_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_13_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_13_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_13_CFG_REG_T;

//pad_gpio_0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_0_sel : 4;     // [3:0]
        REG32 pad_gpio_0_ana : 4;     // [7:4]
        REG32 pad_gpio_0_pull_dn : 1; // [8]
        REG32 pad_gpio_0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_0_pull_frc : 1;     // [16]
        REG32 pad_gpio_0_oen_reg : 1;      // [17]
        REG32 pad_gpio_0_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_0_CFG_REG_T;

//pad_gpio_1_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_1_sel : 4;     // [3:0]
        REG32 pad_gpio_1_ana : 4;     // [7:4]
        REG32 pad_gpio_1_pull_dn : 1; // [8]
        REG32 pad_gpio_1_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_1_pull_frc : 1;     // [16]
        REG32 pad_gpio_1_oen_reg : 1;      // [17]
        REG32 pad_gpio_1_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_1_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_1_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_1_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_1_CFG_REG_T;

//pad_gpio_2_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_2_sel : 4;     // [3:0]
        REG32 pad_gpio_2_ana : 4;     // [7:4]
        REG32 pad_gpio_2_pull_dn : 1; // [8]
        REG32 pad_gpio_2_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_2_pull_frc : 1;     // [16]
        REG32 pad_gpio_2_oen_reg : 1;      // [17]
        REG32 pad_gpio_2_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_2_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_2_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_2_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_2_CFG_REG_T;

//pad_gpio_3_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_3_sel : 4;     // [3:0]
        REG32 pad_gpio_3_ana : 4;     // [7:4]
        REG32 pad_gpio_3_pull_dn : 1; // [8]
        REG32 pad_gpio_3_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_3_pull_frc : 1;     // [16]
        REG32 pad_gpio_3_oen_reg : 1;      // [17]
        REG32 pad_gpio_3_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_3_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_3_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_3_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_3_CFG_REG_T;

//pad_gpio_4_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_4_sel : 4;     // [3:0]
        REG32 pad_gpio_4_ana : 4;     // [7:4]
        REG32 pad_gpio_4_pull_dn : 1; // [8]
        REG32 pad_gpio_4_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_4_pull_frc : 1;     // [16]
        REG32 pad_gpio_4_oen_reg : 1;      // [17]
        REG32 pad_gpio_4_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_4_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_4_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_4_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_4_CFG_REG_T;

//pad_gpio_5_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_5_sel : 4;     // [3:0]
        REG32 pad_gpio_5_ana : 4;     // [7:4]
        REG32 pad_gpio_5_pull_dn : 1; // [8]
        REG32 pad_gpio_5_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_5_pull_frc : 1;     // [16]
        REG32 pad_gpio_5_oen_reg : 1;      // [17]
        REG32 pad_gpio_5_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_5_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_5_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_5_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_5_CFG_REG_T;

//pad_gpio_7_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_7_sel : 4;     // [3:0]
        REG32 pad_gpio_7_ana : 4;     // [7:4]
        REG32 pad_gpio_7_pull_dn : 1; // [8]
        REG32 pad_gpio_7_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_7_pull_frc : 1;     // [16]
        REG32 pad_gpio_7_oen_reg : 1;      // [17]
        REG32 pad_gpio_7_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_7_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_7_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_7_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_7_CFG_REG_T;

//pad_ap_jtag_tck_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_ap_jtag_tck_sel : 4;     // [3:0]
        REG32 pad_ap_jtag_tck_ana : 4;     // [7:4]
        REG32 pad_ap_jtag_tck_pull_dn : 1; // [8]
        REG32 pad_ap_jtag_tck_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_ap_jtag_tck_pull_frc : 1;     // [16]
        REG32 pad_ap_jtag_tck_oen_reg : 1;      // [17]
        REG32 pad_ap_jtag_tck_drv_strength : 2; // [19:18], write set
        REG32 pad_ap_jtag_tck_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_ap_jtag_tck_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_ap_jtag_tck_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AP_JTAG_TCK_CFG_REG_T;

//pad_ap_jtag_trst_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_ap_jtag_trst_sel : 4;     // [3:0]
        REG32 pad_ap_jtag_trst_ana : 4;     // [7:4]
        REG32 pad_ap_jtag_trst_pull_dn : 1; // [8]
        REG32 pad_ap_jtag_trst_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_ap_jtag_trst_pull_frc : 1;     // [16]
        REG32 pad_ap_jtag_trst_oen_reg : 1;      // [17]
        REG32 pad_ap_jtag_trst_drv_strength : 2; // [19:18], write set
        REG32 pad_ap_jtag_trst_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_ap_jtag_trst_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_ap_jtag_trst_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AP_JTAG_TRST_CFG_REG_T;

//pad_ap_jtag_tms_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_ap_jtag_tms_sel : 4;     // [3:0]
        REG32 pad_ap_jtag_tms_ana : 4;     // [7:4]
        REG32 pad_ap_jtag_tms_pull_dn : 1; // [8]
        REG32 pad_ap_jtag_tms_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_ap_jtag_tms_pull_frc : 1;     // [16]
        REG32 pad_ap_jtag_tms_oen_reg : 1;      // [17]
        REG32 pad_ap_jtag_tms_drv_strength : 2; // [19:18], write set
        REG32 pad_ap_jtag_tms_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_ap_jtag_tms_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_ap_jtag_tms_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AP_JTAG_TMS_CFG_REG_T;

//pad_ap_jtag_tdi_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_ap_jtag_tdi_sel : 4;     // [3:0]
        REG32 pad_ap_jtag_tdi_ana : 4;     // [7:4]
        REG32 pad_ap_jtag_tdi_pull_dn : 1; // [8]
        REG32 pad_ap_jtag_tdi_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_ap_jtag_tdi_pull_frc : 1;     // [16]
        REG32 pad_ap_jtag_tdi_oen_reg : 1;      // [17]
        REG32 pad_ap_jtag_tdi_drv_strength : 2; // [19:18], write set
        REG32 pad_ap_jtag_tdi_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_ap_jtag_tdi_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_ap_jtag_tdi_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AP_JTAG_TDI_CFG_REG_T;

//pad_ap_jtag_tdo_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_ap_jtag_tdo_sel : 4;     // [3:0]
        REG32 pad_ap_jtag_tdo_ana : 4;     // [7:4]
        REG32 pad_ap_jtag_tdo_pull_dn : 1; // [8]
        REG32 pad_ap_jtag_tdo_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_ap_jtag_tdo_pull_frc : 1;     // [16]
        REG32 pad_ap_jtag_tdo_oen_reg : 1;      // [17]
        REG32 pad_ap_jtag_tdo_drv_strength : 2; // [19:18], write set
        REG32 pad_ap_jtag_tdo_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_ap_jtag_tdo_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_ap_jtag_tdo_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_AP_JTAG_TDO_CFG_REG_T;

//pad_gpio_14_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_14_sel : 4;     // [3:0]
        REG32 pad_gpio_14_ana : 4;     // [7:4]
        REG32 pad_gpio_14_pull_dn : 1; // [8]
        REG32 pad_gpio_14_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_14_pull_frc : 1;     // [16]
        REG32 pad_gpio_14_oen_reg : 1;      // [17]
        REG32 pad_gpio_14_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_14_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_14_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_14_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_14_CFG_REG_T;

//pad_gpio_15_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_15_sel : 4;     // [3:0]
        REG32 pad_gpio_15_ana : 4;     // [7:4]
        REG32 pad_gpio_15_pull_dn : 1; // [8]
        REG32 pad_gpio_15_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_15_pull_frc : 1;     // [16]
        REG32 pad_gpio_15_oen_reg : 1;      // [17]
        REG32 pad_gpio_15_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_15_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_15_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_15_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_15_CFG_REG_T;

//pad_gpio_18_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_18_sel : 4;     // [3:0]
        REG32 pad_gpio_18_ana : 4;     // [7:4]
        REG32 pad_gpio_18_pull_dn : 1; // [8]
        REG32 pad_gpio_18_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_18_pull_frc : 1;     // [16]
        REG32 pad_gpio_18_oen_reg : 1;      // [17]
        REG32 pad_gpio_18_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_18_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_18_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_18_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_18_CFG_REG_T;

//pad_gpio_19_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_19_sel : 4;     // [3:0]
        REG32 pad_gpio_19_ana : 4;     // [7:4]
        REG32 pad_gpio_19_pull_dn : 1; // [8]
        REG32 pad_gpio_19_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_19_pull_frc : 1;     // [16]
        REG32 pad_gpio_19_oen_reg : 1;      // [17]
        REG32 pad_gpio_19_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_19_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_19_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_19_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_19_CFG_REG_T;

//pad_gpio_20_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_20_sel : 4;     // [3:0]
        REG32 pad_gpio_20_ana : 4;     // [7:4]
        REG32 pad_gpio_20_pull_dn : 1; // [8]
        REG32 pad_gpio_20_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_20_pull_frc : 1;     // [16]
        REG32 pad_gpio_20_oen_reg : 1;      // [17]
        REG32 pad_gpio_20_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_20_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_20_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_20_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_20_CFG_REG_T;

//pad_gpio_21_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_21_sel : 4;     // [3:0]
        REG32 pad_gpio_21_ana : 4;     // [7:4]
        REG32 pad_gpio_21_pull_dn : 1; // [8]
        REG32 pad_gpio_21_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_21_pull_frc : 1;     // [16]
        REG32 pad_gpio_21_oen_reg : 1;      // [17]
        REG32 pad_gpio_21_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_21_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_21_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_21_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_21_CFG_REG_T;

//pad_gpio_22_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_22_sel : 4;     // [3:0]
        REG32 pad_gpio_22_ana : 4;     // [7:4]
        REG32 pad_gpio_22_pull_dn : 1; // [8]
        REG32 pad_gpio_22_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_22_pull_frc : 1;     // [16]
        REG32 pad_gpio_22_oen_reg : 1;      // [17]
        REG32 pad_gpio_22_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_22_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_22_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_22_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_22_CFG_REG_T;

//pad_gpio_23_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_23_sel : 4;     // [3:0]
        REG32 pad_gpio_23_ana : 4;     // [7:4]
        REG32 pad_gpio_23_pull_dn : 1; // [8]
        REG32 pad_gpio_23_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_23_pull_frc : 1;     // [16]
        REG32 pad_gpio_23_oen_reg : 1;      // [17]
        REG32 pad_gpio_23_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_23_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_23_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_23_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_23_CFG_REG_T;

//pad_gpio_8_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_8_sel : 4;     // [3:0]
        REG32 pad_gpio_8_ana : 4;     // [7:4]
        REG32 pad_gpio_8_pull_dn : 1; // [8]
        REG32 pad_gpio_8_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_8_pull_frc : 1;     // [16]
        REG32 pad_gpio_8_oen_reg : 1;      // [17]
        REG32 pad_gpio_8_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_8_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_8_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_8_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_8_CFG_REG_T;

//pad_gpio_9_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_9_sel : 4;     // [3:0]
        REG32 pad_gpio_9_ana : 4;     // [7:4]
        REG32 pad_gpio_9_pull_dn : 1; // [8]
        REG32 pad_gpio_9_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_9_pull_frc : 1;     // [16]
        REG32 pad_gpio_9_oen_reg : 1;      // [17]
        REG32 pad_gpio_9_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_9_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_9_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_9_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_9_CFG_REG_T;

//pad_gpio_10_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_10_sel : 4;     // [3:0]
        REG32 pad_gpio_10_ana : 4;     // [7:4]
        REG32 pad_gpio_10_pull_dn : 1; // [8]
        REG32 pad_gpio_10_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_10_pull_frc : 1;     // [16]
        REG32 pad_gpio_10_oen_reg : 1;      // [17]
        REG32 pad_gpio_10_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_10_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_10_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_10_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_10_CFG_REG_T;

//pad_gpio_11_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_11_sel : 4;     // [3:0]
        REG32 pad_gpio_11_ana : 4;     // [7:4]
        REG32 pad_gpio_11_pull_dn : 1; // [8]
        REG32 pad_gpio_11_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_11_pull_frc : 1;     // [16]
        REG32 pad_gpio_11_oen_reg : 1;      // [17]
        REG32 pad_gpio_11_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_11_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_11_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_11_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_11_CFG_REG_T;

//pad_gpio_12_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_gpio_12_sel : 4;     // [3:0]
        REG32 pad_gpio_12_ana : 4;     // [7:4]
        REG32 pad_gpio_12_pull_dn : 1; // [8]
        REG32 pad_gpio_12_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_gpio_12_pull_frc : 1;     // [16]
        REG32 pad_gpio_12_oen_reg : 1;      // [17]
        REG32 pad_gpio_12_drv_strength : 2; // [19:18], write set
        REG32 pad_gpio_12_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_gpio_12_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_gpio_12_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_GPIO_12_CFG_REG_T;

//pad_keyin_0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyin_0_sel : 4;     // [3:0]
        REG32 pad_keyin_0_ana : 4;     // [7:4]
        REG32 pad_keyin_0_pull_dn : 1; // [8]
        REG32 pad_keyin_0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyin_0_pull_frc : 1;     // [16]
        REG32 pad_keyin_0_oen_reg : 1;      // [17]
        REG32 pad_keyin_0_drv_strength : 2; // [19:18], write set
        REG32 pad_keyin_0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyin_0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyin_0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYIN_0_CFG_REG_T;

//pad_keyin_1_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyin_1_sel : 4;     // [3:0]
        REG32 pad_keyin_1_ana : 4;     // [7:4]
        REG32 pad_keyin_1_pull_dn : 1; // [8]
        REG32 pad_keyin_1_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyin_1_pull_frc : 1;     // [16]
        REG32 pad_keyin_1_oen_reg : 1;      // [17]
        REG32 pad_keyin_1_drv_strength : 2; // [19:18], write set
        REG32 pad_keyin_1_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyin_1_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyin_1_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYIN_1_CFG_REG_T;

//pad_keyin_2_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyin_2_sel : 4;     // [3:0]
        REG32 pad_keyin_2_ana : 4;     // [7:4]
        REG32 pad_keyin_2_pull_dn : 1; // [8]
        REG32 pad_keyin_2_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyin_2_pull_frc : 1;     // [16]
        REG32 pad_keyin_2_oen_reg : 1;      // [17]
        REG32 pad_keyin_2_drv_strength : 2; // [19:18], write set
        REG32 pad_keyin_2_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyin_2_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyin_2_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYIN_2_CFG_REG_T;

//pad_keyin_3_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyin_3_sel : 4;     // [3:0]
        REG32 pad_keyin_3_ana : 4;     // [7:4]
        REG32 pad_keyin_3_pull_dn : 1; // [8]
        REG32 pad_keyin_3_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyin_3_pull_frc : 1;     // [16]
        REG32 pad_keyin_3_oen_reg : 1;      // [17]
        REG32 pad_keyin_3_drv_strength : 2; // [19:18], write set
        REG32 pad_keyin_3_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyin_3_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyin_3_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYIN_3_CFG_REG_T;

//pad_keyin_4_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyin_4_sel : 4;     // [3:0]
        REG32 pad_keyin_4_ana : 4;     // [7:4]
        REG32 pad_keyin_4_pull_dn : 1; // [8]
        REG32 pad_keyin_4_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyin_4_pull_frc : 1;     // [16]
        REG32 pad_keyin_4_oen_reg : 1;      // [17]
        REG32 pad_keyin_4_drv_strength : 2; // [19:18], write set
        REG32 pad_keyin_4_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyin_4_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyin_4_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYIN_4_CFG_REG_T;

//pad_keyin_5_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyin_5_sel : 4;     // [3:0]
        REG32 pad_keyin_5_ana : 4;     // [7:4]
        REG32 pad_keyin_5_pull_dn : 1; // [8]
        REG32 pad_keyin_5_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyin_5_pull_frc : 1;     // [16]
        REG32 pad_keyin_5_oen_reg : 1;      // [17]
        REG32 pad_keyin_5_drv_strength : 2; // [19:18], write set
        REG32 pad_keyin_5_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyin_5_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyin_5_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYIN_5_CFG_REG_T;

//pad_keyout_0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyout_0_sel : 4;     // [3:0]
        REG32 pad_keyout_0_ana : 4;     // [7:4]
        REG32 pad_keyout_0_pull_dn : 1; // [8]
        REG32 pad_keyout_0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyout_0_pull_frc : 1;     // [16]
        REG32 pad_keyout_0_oen_reg : 1;      // [17]
        REG32 pad_keyout_0_drv_strength : 2; // [19:18], write set
        REG32 pad_keyout_0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyout_0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyout_0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYOUT_0_CFG_REG_T;

//pad_keyout_1_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyout_1_sel : 4;     // [3:0]
        REG32 pad_keyout_1_ana : 4;     // [7:4]
        REG32 pad_keyout_1_pull_dn : 1; // [8]
        REG32 pad_keyout_1_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyout_1_pull_frc : 1;     // [16]
        REG32 pad_keyout_1_oen_reg : 1;      // [17]
        REG32 pad_keyout_1_drv_strength : 2; // [19:18], write set
        REG32 pad_keyout_1_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyout_1_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyout_1_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYOUT_1_CFG_REG_T;

//pad_keyout_2_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyout_2_sel : 4;     // [3:0]
        REG32 pad_keyout_2_ana : 4;     // [7:4]
        REG32 pad_keyout_2_pull_dn : 1; // [8]
        REG32 pad_keyout_2_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyout_2_pull_frc : 1;     // [16]
        REG32 pad_keyout_2_oen_reg : 1;      // [17]
        REG32 pad_keyout_2_drv_strength : 2; // [19:18], write set
        REG32 pad_keyout_2_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyout_2_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyout_2_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYOUT_2_CFG_REG_T;

//pad_keyout_3_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyout_3_sel : 4;     // [3:0]
        REG32 pad_keyout_3_ana : 4;     // [7:4]
        REG32 pad_keyout_3_pull_dn : 1; // [8]
        REG32 pad_keyout_3_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyout_3_pull_frc : 1;     // [16]
        REG32 pad_keyout_3_oen_reg : 1;      // [17]
        REG32 pad_keyout_3_drv_strength : 2; // [19:18], write set
        REG32 pad_keyout_3_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyout_3_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyout_3_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYOUT_3_CFG_REG_T;

//pad_keyout_4_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyout_4_sel : 4;     // [3:0]
        REG32 pad_keyout_4_ana : 4;     // [7:4]
        REG32 pad_keyout_4_pull_dn : 1; // [8]
        REG32 pad_keyout_4_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyout_4_pull_frc : 1;     // [16]
        REG32 pad_keyout_4_oen_reg : 1;      // [17]
        REG32 pad_keyout_4_drv_strength : 2; // [19:18], write set
        REG32 pad_keyout_4_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyout_4_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyout_4_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYOUT_4_CFG_REG_T;

//pad_keyout_5_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_keyout_5_sel : 4;     // [3:0]
        REG32 pad_keyout_5_ana : 4;     // [7:4]
        REG32 pad_keyout_5_pull_dn : 1; // [8]
        REG32 pad_keyout_5_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_keyout_5_pull_frc : 1;     // [16]
        REG32 pad_keyout_5_oen_reg : 1;      // [17]
        REG32 pad_keyout_5_drv_strength : 2; // [19:18], write set
        REG32 pad_keyout_5_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_keyout_5_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_keyout_5_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_KEYOUT_5_CFG_REG_T;

//pad_debug_host_rx_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_debug_host_rx_sel : 4;     // [3:0]
        REG32 pad_debug_host_rx_ana : 4;     // [7:4]
        REG32 pad_debug_host_rx_pull_dn : 1; // [8]
        REG32 pad_debug_host_rx_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_debug_host_rx_pull_frc : 1;     // [16]
        REG32 pad_debug_host_rx_oen_reg : 1;      // [17]
        REG32 pad_debug_host_rx_drv_strength : 2; // [19:18], write set
        REG32 pad_debug_host_rx_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_debug_host_rx_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_debug_host_rx_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_DEBUG_HOST_RX_CFG_REG_T;

//pad_debug_host_tx_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_debug_host_tx_sel : 4;     // [3:0]
        REG32 pad_debug_host_tx_ana : 4;     // [7:4]
        REG32 pad_debug_host_tx_pull_dn : 1; // [8]
        REG32 pad_debug_host_tx_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_debug_host_tx_pull_frc : 1;     // [16]
        REG32 pad_debug_host_tx_oen_reg : 1;      // [17]
        REG32 pad_debug_host_tx_drv_strength : 2; // [19:18], write set
        REG32 pad_debug_host_tx_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_debug_host_tx_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_debug_host_tx_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_DEBUG_HOST_TX_CFG_REG_T;

//pad_debug_host_clk_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_debug_host_clk_sel : 4;     // [3:0]
        REG32 pad_debug_host_clk_ana : 4;     // [7:4]
        REG32 pad_debug_host_clk_pull_dn : 1; // [8]
        REG32 pad_debug_host_clk_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_debug_host_clk_pull_frc : 1;     // [16]
        REG32 pad_debug_host_clk_oen_reg : 1;      // [17]
        REG32 pad_debug_host_clk_drv_strength : 2; // [19:18], write set
        REG32 pad_debug_host_clk_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_debug_host_clk_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_debug_host_clk_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_DEBUG_HOST_CLK_CFG_REG_T;

//pad_sim_1_clk_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sim_1_clk_sel : 4;     // [3:0]
        REG32 pad_sim_1_clk_ana : 4;     // [7:4]
        REG32 pad_sim_1_clk_pull_dn : 1; // [8]
        REG32 pad_sim_1_clk_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sim_1_clk_pull_frc : 1;     // [16]
        REG32 pad_sim_1_clk_oen_reg : 1;      // [17]
        REG32 pad_sim_1_clk_drv_strength : 2; // [19:18], write set
        REG32 pad_sim_1_clk_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sim_1_clk_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sim_1_clk_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SIM_1_CLK_CFG_REG_T;

//pad_sim_1_dio_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sim_1_dio_sel : 4;     // [3:0]
        REG32 pad_sim_1_dio_ana : 4;     // [7:4]
        REG32 pad_sim_1_dio_pull_dn : 1; // [8]
        REG32 pad_sim_1_dio_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sim_1_dio_pull_frc : 1;     // [16]
        REG32 pad_sim_1_dio_oen_reg : 1;      // [17]
        REG32 pad_sim_1_dio_drv_strength : 2; // [19:18], write set
        REG32 pad_sim_1_dio_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sim_1_dio_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sim_1_dio_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SIM_1_DIO_CFG_REG_T;

//pad_sim_1_rst_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sim_1_rst_sel : 4;     // [3:0]
        REG32 pad_sim_1_rst_ana : 4;     // [7:4]
        REG32 pad_sim_1_rst_pull_dn : 1; // [8]
        REG32 pad_sim_1_rst_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sim_1_rst_pull_frc : 1;     // [16]
        REG32 pad_sim_1_rst_oen_reg : 1;      // [17]
        REG32 pad_sim_1_rst_drv_strength : 2; // [19:18], write set
        REG32 pad_sim_1_rst_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sim_1_rst_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sim_1_rst_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SIM_1_RST_CFG_REG_T;

//pad_sim_2_clk_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sim_2_clk_sel : 4;     // [3:0]
        REG32 pad_sim_2_clk_ana : 4;     // [7:4]
        REG32 pad_sim_2_clk_pull_dn : 1; // [8]
        REG32 pad_sim_2_clk_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sim_2_clk_pull_frc : 1;     // [16]
        REG32 pad_sim_2_clk_oen_reg : 1;      // [17]
        REG32 pad_sim_2_clk_drv_strength : 2; // [19:18], write set
        REG32 pad_sim_2_clk_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sim_2_clk_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sim_2_clk_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SIM_2_CLK_CFG_REG_T;

//pad_sim_2_dio_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sim_2_dio_sel : 4;     // [3:0]
        REG32 pad_sim_2_dio_ana : 4;     // [7:4]
        REG32 pad_sim_2_dio_pull_dn : 1; // [8]
        REG32 pad_sim_2_dio_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sim_2_dio_pull_frc : 1;     // [16]
        REG32 pad_sim_2_dio_oen_reg : 1;      // [17]
        REG32 pad_sim_2_dio_drv_strength : 2; // [19:18], write set
        REG32 pad_sim_2_dio_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sim_2_dio_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sim_2_dio_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SIM_2_DIO_CFG_REG_T;

//pad_sim_2_rst_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_sim_2_rst_sel : 4;     // [3:0]
        REG32 pad_sim_2_rst_ana : 4;     // [7:4]
        REG32 pad_sim_2_rst_pull_dn : 1; // [8]
        REG32 pad_sim_2_rst_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_sim_2_rst_pull_frc : 1;     // [16]
        REG32 pad_sim_2_rst_oen_reg : 1;      // [17]
        REG32 pad_sim_2_rst_drv_strength : 2; // [19:18], write set
        REG32 pad_sim_2_rst_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_sim_2_rst_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_sim_2_rst_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SIM_2_RST_CFG_REG_T;

//pad_rfdig_gpio_0_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_0_sel : 4;     // [3:0]
        REG32 pad_rfdig_gpio_0_ana : 4;     // [7:4]
        REG32 pad_rfdig_gpio_0_pull_dn : 1; // [8]
        REG32 pad_rfdig_gpio_0_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_rfdig_gpio_0_pull_frc : 1;     // [16]
        REG32 pad_rfdig_gpio_0_oen_reg : 1;      // [17]
        REG32 pad_rfdig_gpio_0_drv_strength : 2; // [19:18], write set
        REG32 pad_rfdig_gpio_0_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_rfdig_gpio_0_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_rfdig_gpio_0_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_RFDIG_GPIO_0_CFG_REG_T;

//pad_rfdig_gpio_1_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_1_sel : 4;     // [3:0]
        REG32 pad_rfdig_gpio_1_ana : 4;     // [7:4]
        REG32 pad_rfdig_gpio_1_pull_dn : 1; // [8]
        REG32 pad_rfdig_gpio_1_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_rfdig_gpio_1_pull_frc : 1;     // [16]
        REG32 pad_rfdig_gpio_1_oen_reg : 1;      // [17]
        REG32 pad_rfdig_gpio_1_drv_strength : 2; // [19:18], write set
        REG32 pad_rfdig_gpio_1_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_rfdig_gpio_1_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_rfdig_gpio_1_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_RFDIG_GPIO_1_CFG_REG_T;

//pad_rfdig_gpio_2_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_2_sel : 4;     // [3:0]
        REG32 pad_rfdig_gpio_2_ana : 4;     // [7:4]
        REG32 pad_rfdig_gpio_2_pull_dn : 1; // [8]
        REG32 pad_rfdig_gpio_2_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_rfdig_gpio_2_pull_frc : 1;     // [16]
        REG32 pad_rfdig_gpio_2_oen_reg : 1;      // [17]
        REG32 pad_rfdig_gpio_2_drv_strength : 2; // [19:18], write set
        REG32 pad_rfdig_gpio_2_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_rfdig_gpio_2_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_rfdig_gpio_2_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_RFDIG_GPIO_2_CFG_REG_T;

//pad_rfdig_gpio_3_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_3_sel : 4;     // [3:0]
        REG32 pad_rfdig_gpio_3_ana : 4;     // [7:4]
        REG32 pad_rfdig_gpio_3_pull_dn : 1; // [8]
        REG32 pad_rfdig_gpio_3_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_rfdig_gpio_3_pull_frc : 1;     // [16]
        REG32 pad_rfdig_gpio_3_oen_reg : 1;      // [17]
        REG32 pad_rfdig_gpio_3_drv_strength : 2; // [19:18], write set
        REG32 pad_rfdig_gpio_3_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_rfdig_gpio_3_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_rfdig_gpio_3_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_RFDIG_GPIO_3_CFG_REG_T;

//pad_rfdig_gpio_4_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_4_sel : 4;     // [3:0]
        REG32 pad_rfdig_gpio_4_ana : 4;     // [7:4]
        REG32 pad_rfdig_gpio_4_pull_dn : 1; // [8]
        REG32 pad_rfdig_gpio_4_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_rfdig_gpio_4_pull_frc : 1;     // [16]
        REG32 pad_rfdig_gpio_4_oen_reg : 1;      // [17]
        REG32 pad_rfdig_gpio_4_drv_strength : 2; // [19:18], write set
        REG32 pad_rfdig_gpio_4_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_rfdig_gpio_4_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_rfdig_gpio_4_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_RFDIG_GPIO_4_CFG_REG_T;

//pad_rfdig_gpio_5_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_5_sel : 4;     // [3:0]
        REG32 pad_rfdig_gpio_5_ana : 4;     // [7:4]
        REG32 pad_rfdig_gpio_5_pull_dn : 1; // [8]
        REG32 pad_rfdig_gpio_5_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_rfdig_gpio_5_pull_frc : 1;     // [16]
        REG32 pad_rfdig_gpio_5_oen_reg : 1;      // [17]
        REG32 pad_rfdig_gpio_5_drv_strength : 2; // [19:18], write set
        REG32 pad_rfdig_gpio_5_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_rfdig_gpio_5_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_rfdig_gpio_5_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_RFDIG_GPIO_5_CFG_REG_T;

//pad_rfdig_gpio_6_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_6_sel : 4;     // [3:0]
        REG32 pad_rfdig_gpio_6_ana : 4;     // [7:4]
        REG32 pad_rfdig_gpio_6_pull_dn : 1; // [8]
        REG32 pad_rfdig_gpio_6_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_rfdig_gpio_6_pull_frc : 1;     // [16]
        REG32 pad_rfdig_gpio_6_oen_reg : 1;      // [17]
        REG32 pad_rfdig_gpio_6_drv_strength : 2; // [19:18], write set
        REG32 pad_rfdig_gpio_6_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_rfdig_gpio_6_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_rfdig_gpio_6_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_RFDIG_GPIO_6_CFG_REG_T;

//pad_rfdig_gpio_7_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_rfdig_gpio_7_sel : 4;     // [3:0]
        REG32 pad_rfdig_gpio_7_ana : 4;     // [7:4]
        REG32 pad_rfdig_gpio_7_pull_dn : 1; // [8]
        REG32 pad_rfdig_gpio_7_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_rfdig_gpio_7_pull_frc : 1;     // [16]
        REG32 pad_rfdig_gpio_7_oen_reg : 1;      // [17]
        REG32 pad_rfdig_gpio_7_drv_strength : 2; // [19:18], write set
        REG32 pad_rfdig_gpio_7_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_rfdig_gpio_7_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_rfdig_gpio_7_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_RFDIG_GPIO_7_CFG_REG_T;

//pad_secure_boot_mode_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_secure_boot_mode_sel : 4;     // [3:0]
        REG32 pad_secure_boot_mode_ana : 4;     // [7:4]
        REG32 pad_secure_boot_mode_pull_dn : 1; // [8]
        REG32 pad_secure_boot_mode_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_secure_boot_mode_pull_frc : 1;     // [16]
        REG32 pad_secure_boot_mode_oen_reg : 1;      // [17]
        REG32 pad_secure_boot_mode_drv_strength : 2; // [19:18], write set
        REG32 pad_secure_boot_mode_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_secure_boot_mode_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_secure_boot_mode_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_SECURE_BOOT_MODE_CFG_REG_T;

//pad_nand_flash_sel_cfg_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_nand_flash_sel_sel : 4;     // [3:0]
        REG32 pad_nand_flash_sel_ana : 4;     // [7:4]
        REG32 pad_nand_flash_sel_pull_dn : 1; // [8]
        REG32 pad_nand_flash_sel_pull_up : 1; // [9]
        REG32 __15_10 : 6;
        REG32 pad_nand_flash_sel_pull_frc : 1;     // [16]
        REG32 pad_nand_flash_sel_oen_reg : 1;      // [17]
        REG32 pad_nand_flash_sel_drv_strength : 2; // [19:18], write set
        REG32 pad_nand_flash_sel_out_reg : 1;      // [20]
        REG32 __23_21 : 3;
        REG32 pad_nand_flash_sel_out_frc : 1; // [24]
        REG32 __27_25 : 3;
        REG32 pad_nand_flash_sel_oen_frc : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_IOMUX_PAD_NAND_FLASH_SEL_CFG_REG_T;

//pad_spi_flash_clk_cfg_reg
#define IOMUX_PAD_SPI_FLASH_CLK_SEL_V_FUN_SPI_FLASH_CLK_SEL (0)

//pad_spi_flash_cs_cfg_reg
#define IOMUX_PAD_SPI_FLASH_CS_SEL_V_FUN_SPI_FLASH_CS_SEL (0)

//pad_spi_flash_sel_cfg_reg
#define IOMUX_PAD_SPI_FLASH_SEL_SEL_V_FUN_SPI_FLASH_SEL_SEL (0)

//pad_spi_flash_sio_0_cfg_reg
#define IOMUX_PAD_SPI_FLASH_SIO_0_SEL_V_FUN_SPI_FLASH_SIO_0_SEL (0)

//pad_spi_flash_sio_1_cfg_reg
#define IOMUX_PAD_SPI_FLASH_SIO_1_SEL_V_FUN_SPI_FLASH_SIO_1_SEL (0)
#define IOMUX_PAD_SPI_FLASH_SIO_1_SEL_V_FUN_GPIO_29_SEL (1)

//pad_spi_flash_sio_2_cfg_reg
#define IOMUX_PAD_SPI_FLASH_SIO_2_SEL_V_FUN_SPI_FLASH_SIO_2_SEL (0)
#define IOMUX_PAD_SPI_FLASH_SIO_2_SEL_V_FUN_GPIO_30_SEL (1)

//pad_spi_flash_sio_3_cfg_reg
#define IOMUX_PAD_SPI_FLASH_SIO_3_SEL_V_FUN_SPI_FLASH_SIO_3_SEL (0)
#define IOMUX_PAD_SPI_FLASH_SIO_3_SEL_V_FUN_GPIO_31_SEL (1)

//pad_sdmmc1_clk_cfg_reg
#define IOMUX_PAD_SDMMC1_CLK_SEL_V_FUN_SDMMC1_CLK_SEL (0)
#define IOMUX_PAD_SDMMC1_CLK_SEL_V_FUN_CAMERA_REF_CLK_SEL (2)
#define IOMUX_PAD_SDMMC1_CLK_SEL_V_FUN_SPI_2_CS_0_SEL (7)

//pad_sdmmc1_cmd_cfg_reg
#define IOMUX_PAD_SDMMC1_CMD_SEL_V_FUN_SDMMC1_CMD_SEL (0)
#define IOMUX_PAD_SDMMC1_CMD_SEL_V_FUN_GPIO_24_SEL (1)
#define IOMUX_PAD_SDMMC1_CMD_SEL_V_FUN_CAMERA_RST_L_SEL (2)
#define IOMUX_PAD_SDMMC1_CMD_SEL_V_FUN_I2C_M3_SCL_SEL (3)

//pad_sdmmc1_data_0_cfg_reg
#define IOMUX_PAD_SDMMC1_DATA_0_SEL_V_FUN_SDMMC1_DATA_0_SEL (0)
#define IOMUX_PAD_SDMMC1_DATA_0_SEL_V_FUN_GPIO_25_SEL (1)
#define IOMUX_PAD_SDMMC1_DATA_0_SEL_V_FUN_CAMERA_PWDN_SEL (2)
#define IOMUX_PAD_SDMMC1_DATA_0_SEL_V_FUN_I2C_M3_SDA_SEL (3)
#define IOMUX_PAD_SDMMC1_DATA_0_SEL_V_FUN_UART_2_RXD_SEL (5)
#define IOMUX_PAD_SDMMC1_DATA_0_SEL_V_FUN_UART_3_CTS_SEL (6)

//pad_sdmmc1_data_1_cfg_reg
#define IOMUX_PAD_SDMMC1_DATA_1_SEL_V_FUN_SDMMC1_DATA_1_SEL (0)
#define IOMUX_PAD_SDMMC1_DATA_1_SEL_V_FUN_GPIO_26_SEL (1)
#define IOMUX_PAD_SDMMC1_DATA_1_SEL_V_FUN_SPI_CAMERA_SI_0_SEL (2)
#define IOMUX_PAD_SDMMC1_DATA_1_SEL_V_FUN_SPI_CAMERA_SI_1_SEL (3)
#define IOMUX_PAD_SDMMC1_DATA_1_SEL_V_FUN_UART_2_TXD_SEL (5)
#define IOMUX_PAD_SDMMC1_DATA_1_SEL_V_FUN_UART_3_RTS_SEL (6)
#define IOMUX_PAD_SDMMC1_DATA_1_SEL_V_FUN_SPI_2_CLK_SEL (7)

//pad_sdmmc1_data_2_cfg_reg
#define IOMUX_PAD_SDMMC1_DATA_2_SEL_V_FUN_SDMMC1_DATA_2_SEL (0)
#define IOMUX_PAD_SDMMC1_DATA_2_SEL_V_FUN_GPIO_27_SEL (1)
#define IOMUX_PAD_SDMMC1_DATA_2_SEL_V_FUN_SPI_CAMERA_SI_1_SEL (2)
#define IOMUX_PAD_SDMMC1_DATA_2_SEL_V_FUN_SPI_CAMERA_SI_0_SEL (3)
#define IOMUX_PAD_SDMMC1_DATA_2_SEL_V_FUN_SPI_CAMERA_SSN_SEL (4)
#define IOMUX_PAD_SDMMC1_DATA_2_SEL_V_FUN_UART_2_CTS_SEL (5)
#define IOMUX_PAD_SDMMC1_DATA_2_SEL_V_FUN_UART_3_RXD_SEL (6)
#define IOMUX_PAD_SDMMC1_DATA_2_SEL_V_FUN_SPI_2_DIO_0_SEL (7)

//pad_sdmmc1_data_3_cfg_reg
#define IOMUX_PAD_SDMMC1_DATA_3_SEL_V_FUN_SDMMC1_DATA_3_SEL (0)
#define IOMUX_PAD_SDMMC1_DATA_3_SEL_V_FUN_GPIO_28_SEL (1)
#define IOMUX_PAD_SDMMC1_DATA_3_SEL_V_FUN_SPI_CAMERA_SCK_SEL (2)
#define IOMUX_PAD_SDMMC1_DATA_3_SEL_V_FUN_UART_2_RTS_SEL (5)
#define IOMUX_PAD_SDMMC1_DATA_3_SEL_V_FUN_UART_3_TXD_SEL (6)
#define IOMUX_PAD_SDMMC1_DATA_3_SEL_V_FUN_SPI_2_DI_1_SEL (7)

//pad_aud_da_sync_cfg_reg
#define IOMUX_PAD_AUD_DA_SYNC_SEL_V_FUN_AUD_DA_SYNC_SEL (0)
#define IOMUX_PAD_AUD_DA_SYNC_SEL_V_FUN_I2S1_BCK_SEL (1)
#define IOMUX_PAD_AUD_DA_SYNC_SEL_V_FUN_GPIO_27_SEL (2)

//pad_aud_da_d1_cfg_reg
#define IOMUX_PAD_AUD_DA_D1_SEL_V_FUN_AUD_DA_D1_SEL (0)
#define IOMUX_PAD_AUD_DA_D1_SEL_V_FUN_I2S1_LRCK_SEL (1)
#define IOMUX_PAD_AUD_DA_D1_SEL_V_FUN_GPIO_28_SEL (2)

//pad_aud_da_d0_cfg_reg
#define IOMUX_PAD_AUD_DA_D0_SEL_V_FUN_AUD_DA_D0_SEL (0)
#define IOMUX_PAD_AUD_DA_D0_SEL_V_FUN_I2S1_SDAT_I_SEL (1)
#define IOMUX_PAD_AUD_DA_D0_SEL_V_FUN_GPIO_29_SEL (2)

//pad_aud_ad_sync_cfg_reg
#define IOMUX_PAD_AUD_AD_SYNC_SEL_V_FUN_AUD_AD_SYNC_SEL (0)
#define IOMUX_PAD_AUD_AD_SYNC_SEL_V_FUN_I2S1_SDAT_O_SEL (1)
#define IOMUX_PAD_AUD_AD_SYNC_SEL_V_FUN_GPIO_30_SEL (2)

//pad_aud_ad_d0_cfg_reg
#define IOMUX_PAD_AUD_AD_D0_SEL_V_FUN_AUD_AD_D0_SEL (0)
#define IOMUX_PAD_AUD_AD_D0_SEL_V_FUN_GPIO_31_SEL (2)

//pad_aud_sclk_cfg_reg
#define IOMUX_PAD_AUD_SCLK_SEL_V_FUN_AUD_SCLK_SEL (0)

//pad_adi_sda_cfg_reg
#define IOMUX_PAD_ADI_SDA_SEL_V_FUN_ADI_SDA_SEL (0)

//pad_adi_sync_cfg_reg
#define IOMUX_PAD_ADI_SYNC_SEL_V_FUN_ADI_SYNC_SEL (0)

//pad_adi_scl_cfg_reg
#define IOMUX_PAD_ADI_SCL_SEL_V_FUN_ADI_SCL_SEL (0)

//pad_spi_lcd_sio_cfg_reg
#define IOMUX_PAD_SPI_LCD_SIO_SEL_V_FUN_SPI_LCD_SIO_SEL (0)
#define IOMUX_PAD_SPI_LCD_SIO_SEL_V_FUN_GPIO_0_SEL (1)
#define IOMUX_PAD_SPI_LCD_SIO_SEL_V_FUN_SPI_FLASH1_CLK_SEL (2)
#define IOMUX_PAD_SPI_LCD_SIO_SEL_V_FUN_DEBUG_BUS_5_SEL (7)

//pad_spi_lcd_sdc_cfg_reg
#define IOMUX_PAD_SPI_LCD_SDC_SEL_V_FUN_SPI_LCD_SDC_SEL (0)
#define IOMUX_PAD_SPI_LCD_SDC_SEL_V_FUN_GPIO_1_SEL (1)
#define IOMUX_PAD_SPI_LCD_SDC_SEL_V_FUN_SPI_FLASH1_CS_SEL (2)
#define IOMUX_PAD_SPI_LCD_SDC_SEL_V_FUN_I2C_M3_SDA_SEL (3)
#define IOMUX_PAD_SPI_LCD_SDC_SEL_V_FUN_DEBUG_BUS_6_SEL (7)

//pad_spi_lcd_clk_cfg_reg
#define IOMUX_PAD_SPI_LCD_CLK_SEL_V_FUN_SPI_LCD_CLK_SEL (0)
#define IOMUX_PAD_SPI_LCD_CLK_SEL_V_FUN_GPIO_2_SEL (1)
#define IOMUX_PAD_SPI_LCD_CLK_SEL_V_FUN_SPI_FLASH1_SIO_0_SEL (2)
#define IOMUX_PAD_SPI_LCD_CLK_SEL_V_FUN_DEBUG_BUS_7_SEL (7)

//pad_spi_lcd_cs_cfg_reg
#define IOMUX_PAD_SPI_LCD_CS_SEL_V_FUN_SPI_LCD_CS_SEL (0)
#define IOMUX_PAD_SPI_LCD_CS_SEL_V_FUN_GPIO_3_SEL (1)
#define IOMUX_PAD_SPI_LCD_CS_SEL_V_FUN_SPI_FLASH1_SIO_1_SEL (2)
#define IOMUX_PAD_SPI_LCD_CS_SEL_V_FUN_DEBUG_BUS_8_SEL (7)

//pad_spi_lcd_select_cfg_reg
#define IOMUX_PAD_SPI_LCD_SELECT_SEL_V_FUN_SPI_LCD_SELECT_SEL (0)
#define IOMUX_PAD_SPI_LCD_SELECT_SEL_V_FUN_GPIO_4_SEL (1)
#define IOMUX_PAD_SPI_LCD_SELECT_SEL_V_FUN_SPI_FLASH1_SIO_2_SEL (2)
#define IOMUX_PAD_SPI_LCD_SELECT_SEL_V_FUN_DEBUG_BUS_9_SEL (7)

//pad_lcd_fmark_cfg_reg
#define IOMUX_PAD_LCD_FMARK_SEL_V_FUN_LCD_FMARK_SEL (0)
#define IOMUX_PAD_LCD_FMARK_SEL_V_FUN_GPIO_5_SEL (1)
#define IOMUX_PAD_LCD_FMARK_SEL_V_FUN_SPI_FLASH1_SIO_3_SEL (2)
#define IOMUX_PAD_LCD_FMARK_SEL_V_FUN_UART_2_TXD_SEL (4)
#define IOMUX_PAD_LCD_FMARK_SEL_V_FUN_DEBUG_BUS_10_SEL (7)

//pad_lcd_rstb_cfg_reg
#define IOMUX_PAD_LCD_RSTB_SEL_V_FUN_LCD_RSTB_SEL (0)
#define IOMUX_PAD_LCD_RSTB_SEL_V_FUN_GPIO_6_SEL (1)
#define IOMUX_PAD_LCD_RSTB_SEL_V_FUN_I2C_M3_SCL_SEL (3)
#define IOMUX_PAD_LCD_RSTB_SEL_V_FUN_UART_2_RXD_SEL (4)
#define IOMUX_PAD_LCD_RSTB_SEL_V_FUN_DEBUG_BUS_11_SEL (7)

//pad_i2c_m1_scl_cfg_reg
#define IOMUX_PAD_I2C_M1_SCL_SEL_V_FUN_I2C_M1_SCL_SEL (0)
#define IOMUX_PAD_I2C_M1_SCL_SEL_V_FUN_GPIO_16_SEL (4)
#define IOMUX_PAD_I2C_M1_SCL_SEL_V_FUN_DEBUG_BUS_0_SEL (7)

//pad_i2c_m1_sda_cfg_reg
#define IOMUX_PAD_I2C_M1_SDA_SEL_V_FUN_I2C_M1_SDA_SEL (0)
#define IOMUX_PAD_I2C_M1_SDA_SEL_V_FUN_GPIO_17_SEL (4)
#define IOMUX_PAD_I2C_M1_SDA_SEL_V_FUN_DEBUG_BUS_1_SEL (7)

//pad_camera_rst_l_cfg_reg
#define IOMUX_PAD_CAMERA_RST_L_SEL_V_FUN_CAMERA_RST_L_SEL (0)
#define IOMUX_PAD_CAMERA_RST_L_SEL_V_FUN_I2C_M1_SCL_SEL (1)
#define IOMUX_PAD_CAMERA_RST_L_SEL_V_FUN_GPIO_18_SEL (4)
#define IOMUX_PAD_CAMERA_RST_L_SEL_V_FUN_DEBUG_BUS_2_SEL (7)

//pad_camera_pwdn_cfg_reg
#define IOMUX_PAD_CAMERA_PWDN_SEL_V_FUN_CAMERA_PWDN_SEL (0)
#define IOMUX_PAD_CAMERA_PWDN_SEL_V_FUN_I2C_M1_SDA_SEL (1)
#define IOMUX_PAD_CAMERA_PWDN_SEL_V_FUN_GPIO_19_SEL (4)
#define IOMUX_PAD_CAMERA_PWDN_SEL_V_FUN_DEBUG_BUS_3_SEL (7)

//pad_camera_ref_clk_cfg_reg
#define IOMUX_PAD_CAMERA_REF_CLK_SEL_V_FUN_CAMERA_REF_CLK_SEL (0)
#define IOMUX_PAD_CAMERA_REF_CLK_SEL_V_FUN_SPI_LVDS_DI_SEL (3)
#define IOMUX_PAD_CAMERA_REF_CLK_SEL_V_FUN_GPIO_20_SEL (4)
#define IOMUX_PAD_CAMERA_REF_CLK_SEL_V_FUN_DEBUG_BUS_4_SEL (7)

//pad_spi_camera_si_0_cfg_reg
#define IOMUX_PAD_SPI_CAMERA_SI_0_SEL_V_FUN_SPI_CAMERA_SI_0_SEL (0)
#define IOMUX_PAD_SPI_CAMERA_SI_0_SEL_V_FUN_SPI_CAMERA_SI_1_SEL (1)
#define IOMUX_PAD_SPI_CAMERA_SI_0_SEL_V_FUN_SPI_LVDS_DO_SEL (3)
#define IOMUX_PAD_SPI_CAMERA_SI_0_SEL_V_FUN_GPIO_21_SEL (4)
#define IOMUX_PAD_SPI_CAMERA_SI_0_SEL_V_FUN_DEBUG_BUS_5_SEL (7)

//pad_spi_camera_si_1_cfg_reg
#define IOMUX_PAD_SPI_CAMERA_SI_1_SEL_V_FUN_SPI_CAMERA_SI_1_SEL (0)
#define IOMUX_PAD_SPI_CAMERA_SI_1_SEL_V_FUN_SPI_CAMERA_SI_0_SEL (1)
#define IOMUX_PAD_SPI_CAMERA_SI_1_SEL_V_FUN_SPI_CAMERA_SSN_SEL (2)
#define IOMUX_PAD_SPI_CAMERA_SI_1_SEL_V_FUN_SPI_LVDS_CS_SEL (3)
#define IOMUX_PAD_SPI_CAMERA_SI_1_SEL_V_FUN_GPIO_22_SEL (4)
#define IOMUX_PAD_SPI_CAMERA_SI_1_SEL_V_FUN_DEBUG_BUS_6_SEL (7)

//pad_spi_camera_sck_cfg_reg
#define IOMUX_PAD_SPI_CAMERA_SCK_SEL_V_FUN_SPI_CAMERA_SCK_SEL (0)
#define IOMUX_PAD_SPI_CAMERA_SCK_SEL_V_FUN_SPI_LVDS_CLK_SEL (3)
#define IOMUX_PAD_SPI_CAMERA_SCK_SEL_V_FUN_GPIO_23_SEL (4)
#define IOMUX_PAD_SPI_CAMERA_SCK_SEL_V_FUN_DEBUG_BUS_7_SEL (7)

//pad_gpio_13_cfg_reg
#define IOMUX_PAD_GPIO_13_SEL_V_FUN_GPIO_13_SEL (0)
#define IOMUX_PAD_GPIO_13_SEL_V_FUN_PWM_LPG_OUT_SEL (1)

//pad_gpio_0_cfg_reg
#define IOMUX_PAD_GPIO_0_SEL_V_FUN_GPIO_0_SEL (0)
#define IOMUX_PAD_GPIO_0_SEL_V_FUN_SPI_FLASH1_CLK_SEL (1)
#define IOMUX_PAD_GPIO_0_SEL_V_FUN_SPI_2_CLK_SEL (2)
#define IOMUX_PAD_GPIO_0_SEL_V_FUN_I2S2_BCK_SEL (3)
#define IOMUX_PAD_GPIO_0_SEL_V_FUN_WCN_JTAG_TCK_SEL (4)
#define IOMUX_PAD_GPIO_0_SEL_V_FUN_UART_RXD_RF_SEL (5)
#define IOMUX_PAD_GPIO_0_SEL_V_FUN_DEBUG_CLK_SEL (7)
#define IOMUX_PAD_GPIO_0_SEL_V_FUN_WCN_EXT_M_BB_SENB_SEL (8)

//pad_gpio_1_cfg_reg
#define IOMUX_PAD_GPIO_1_SEL_V_FUN_GPIO_1_SEL (0)
#define IOMUX_PAD_GPIO_1_SEL_V_FUN_SPI_FLASH1_CS_SEL (1)
#define IOMUX_PAD_GPIO_1_SEL_V_FUN_SPI_2_CS_0_SEL (2)
#define IOMUX_PAD_GPIO_1_SEL_V_FUN_I2S2_LRCK_SEL (3)
#define IOMUX_PAD_GPIO_1_SEL_V_FUN_WCN_JTAG_TRST_SEL (4)
#define IOMUX_PAD_GPIO_1_SEL_V_FUN_UART_TXD_RF_SEL (5)
#define IOMUX_PAD_GPIO_1_SEL_V_FUN_DEBUG_BUS_0_SEL (7)
#define IOMUX_PAD_GPIO_1_SEL_V_FUN_WCN_EXT_M_BB_SCLK_SEL (8)

//pad_gpio_2_cfg_reg
#define IOMUX_PAD_GPIO_2_SEL_V_FUN_GPIO_2_SEL (0)
#define IOMUX_PAD_GPIO_2_SEL_V_FUN_SPI_FLASH1_SIO_0_SEL (1)
#define IOMUX_PAD_GPIO_2_SEL_V_FUN_SPI_2_DIO_0_SEL (2)
#define IOMUX_PAD_GPIO_2_SEL_V_FUN_I2S2_SDAT_I_SEL (3)
#define IOMUX_PAD_GPIO_2_SEL_V_FUN_WCN_JTAG_TMS_SEL (4)
#define IOMUX_PAD_GPIO_2_SEL_V_FUN_WCN_HST_TXD_SEL (5)
#define IOMUX_PAD_GPIO_2_SEL_V_FUN_DEBUG_BUS_1_SEL (7)

//pad_gpio_3_cfg_reg
#define IOMUX_PAD_GPIO_3_SEL_V_FUN_GPIO_3_SEL (0)
#define IOMUX_PAD_GPIO_3_SEL_V_FUN_SPI_FLASH1_SIO_1_SEL (1)
#define IOMUX_PAD_GPIO_3_SEL_V_FUN_SPI_2_DI_1_SEL (2)
#define IOMUX_PAD_GPIO_3_SEL_V_FUN_I2S2_SDAT_O_SEL (3)
#define IOMUX_PAD_GPIO_3_SEL_V_FUN_WCN_JTAG_TDI_SEL (4)
#define IOMUX_PAD_GPIO_3_SEL_V_FUN_WCN_HST_RXD_SEL (5)
#define IOMUX_PAD_GPIO_3_SEL_V_FUN_DEBUG_BUS_2_SEL (7)

//pad_gpio_4_cfg_reg
#define IOMUX_PAD_GPIO_4_SEL_V_FUN_GPIO_4_SEL (0)
#define IOMUX_PAD_GPIO_4_SEL_V_FUN_SPI_FLASH1_SIO_2_SEL (1)
#define IOMUX_PAD_GPIO_4_SEL_V_FUN_SPI_2_CS_1_SEL (2)
#define IOMUX_PAD_GPIO_4_SEL_V_FUN_PWL_OUT_0_SEL (3)
#define IOMUX_PAD_GPIO_4_SEL_V_FUN_WCN_JTAG_TDO_SEL (4)
#define IOMUX_PAD_GPIO_4_SEL_V_FUN_I2C_M3_SCL_SEL (6)
#define IOMUX_PAD_GPIO_4_SEL_V_FUN_DEBUG_BUS_3_SEL (7)
#define IOMUX_PAD_GPIO_4_SEL_V_FUN_WCN_EXT_M_BB_SDO_SEL (8)

//pad_gpio_5_cfg_reg
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_GPIO_5_SEL (0)
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_SPI_FLASH1_SIO_3_SEL (1)
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_PWT_OUT_SEL (2)
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_LCD_FMARK_SEL (3)
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_WCN_UART_RTS_SEL (4)
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_WCN_UART_TXD_SEL (5)
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_I2C_M3_SDA_SEL (6)
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_DEBUG_BUS_4_SEL (7)
#define IOMUX_PAD_GPIO_5_SEL_V_FUN_WCN_EXT_M_BB_SDI_SEL (8)

//pad_gpio_7_cfg_reg
#define IOMUX_PAD_GPIO_7_SEL_V_FUN_GPIO_7_SEL (0)
#define IOMUX_PAD_GPIO_7_SEL_V_FUN_SDMMC2_CLK_SEL (1)
#define IOMUX_PAD_GPIO_7_SEL_V_FUN_SPI_1_CLK_SEL (2)
#define IOMUX_PAD_GPIO_7_SEL_V_FUN_PWL_OUT_1_SEL (3)
#define IOMUX_PAD_GPIO_7_SEL_V_FUN_WCN_UART_CTS_SEL (4)
#define IOMUX_PAD_GPIO_7_SEL_V_FUN_WCN_UART_RXD_SEL (5)

//pad_ap_jtag_tck_cfg_reg
#define IOMUX_PAD_AP_JTAG_TCK_SEL_V_FUN_AP_JTAG_TCK_SEL (0)
#define IOMUX_PAD_AP_JTAG_TCK_SEL_V_FUN_SDMMC2_CMD_SEL (1)
#define IOMUX_PAD_AP_JTAG_TCK_SEL_V_FUN_SPI_1_CS_0_SEL (2)
#define IOMUX_PAD_AP_JTAG_TCK_SEL_V_FUN_ZSP_JTAG_TCK_SEL (3)
#define IOMUX_PAD_AP_JTAG_TCK_SEL_V_FUN_RFDIG_JTAG_TCK_SEL (4)
#define IOMUX_PAD_AP_JTAG_TCK_SEL_V_FUN_GPIO_8_SEL (5)

//pad_ap_jtag_trst_cfg_reg
#define IOMUX_PAD_AP_JTAG_TRST_SEL_V_FUN_AP_JTAG_TRST_SEL (0)
#define IOMUX_PAD_AP_JTAG_TRST_SEL_V_FUN_SDMMC2_DATA_0_SEL (1)
#define IOMUX_PAD_AP_JTAG_TRST_SEL_V_FUN_SPI_1_DIO_0_SEL (2)
#define IOMUX_PAD_AP_JTAG_TRST_SEL_V_FUN_ZSP_JTAG_TRST_SEL (3)
#define IOMUX_PAD_AP_JTAG_TRST_SEL_V_FUN_RFDIG_JTAG_TRST_SEL (4)
#define IOMUX_PAD_AP_JTAG_TRST_SEL_V_FUN_GPIO_9_SEL (5)

//pad_ap_jtag_tms_cfg_reg
#define IOMUX_PAD_AP_JTAG_TMS_SEL_V_FUN_AP_JTAG_TMS_SEL (0)
#define IOMUX_PAD_AP_JTAG_TMS_SEL_V_FUN_SDMMC2_DATA_1_SEL (1)
#define IOMUX_PAD_AP_JTAG_TMS_SEL_V_FUN_SPI_1_DI_1_SEL (2)
#define IOMUX_PAD_AP_JTAG_TMS_SEL_V_FUN_ZSP_JTAG_TMS_SEL (3)
#define IOMUX_PAD_AP_JTAG_TMS_SEL_V_FUN_RFDIG_JTAG_TMS_SEL (4)
#define IOMUX_PAD_AP_JTAG_TMS_SEL_V_FUN_GPIO_10_SEL (5)

//pad_ap_jtag_tdi_cfg_reg
#define IOMUX_PAD_AP_JTAG_TDI_SEL_V_FUN_AP_JTAG_TDI_SEL (0)
#define IOMUX_PAD_AP_JTAG_TDI_SEL_V_FUN_SDMMC2_DATA_2_SEL (1)
#define IOMUX_PAD_AP_JTAG_TDI_SEL_V_FUN_SPI_1_CS_1_SEL (2)
#define IOMUX_PAD_AP_JTAG_TDI_SEL_V_FUN_ZSP_JTAG_TDI_SEL (3)
#define IOMUX_PAD_AP_JTAG_TDI_SEL_V_FUN_RFDIG_JTAG_TDI_SEL (4)
#define IOMUX_PAD_AP_JTAG_TDI_SEL_V_FUN_GPIO_11_SEL (5)

//pad_ap_jtag_tdo_cfg_reg
#define IOMUX_PAD_AP_JTAG_TDO_SEL_V_FUN_AP_JTAG_TDO_SEL (0)
#define IOMUX_PAD_AP_JTAG_TDO_SEL_V_FUN_SDMMC2_DATA_3_SEL (1)
#define IOMUX_PAD_AP_JTAG_TDO_SEL_V_FUN_ZSP_JTAG_TDO_SEL (3)
#define IOMUX_PAD_AP_JTAG_TDO_SEL_V_FUN_RFDIG_JTAG_TDO_SEL (4)
#define IOMUX_PAD_AP_JTAG_TDO_SEL_V_FUN_GPIO_12_SEL (5)

//pad_gpio_14_cfg_reg
#define IOMUX_PAD_GPIO_14_SEL_V_FUN_GPIO_14_SEL (0)
#define IOMUX_PAD_GPIO_14_SEL_V_FUN_I2C_M2_SCL_SEL (1)

//pad_gpio_15_cfg_reg
#define IOMUX_PAD_GPIO_15_SEL_V_FUN_GPIO_15_SEL (0)
#define IOMUX_PAD_GPIO_15_SEL_V_FUN_I2C_M2_SDA_SEL (1)

//pad_gpio_18_cfg_reg
#define IOMUX_PAD_GPIO_18_SEL_V_FUN_GPIO_18_SEL (0)
#define IOMUX_PAD_GPIO_18_SEL_V_FUN_UART_1_CTS_SEL (1)
#define IOMUX_PAD_GPIO_18_SEL_V_FUN_ZSP_UART_TXD_SEL (3)
#define IOMUX_PAD_GPIO_18_SEL_V_FUN_WCN_UART_RXD_SEL (4)
#define IOMUX_PAD_GPIO_18_SEL_V_FUN_WCN_UART_CTS_SEL (5)

//pad_gpio_19_cfg_reg
#define IOMUX_PAD_GPIO_19_SEL_V_FUN_GPIO_19_SEL (0)
#define IOMUX_PAD_GPIO_19_SEL_V_FUN_UART_1_RTS_SEL (1)
#define IOMUX_PAD_GPIO_19_SEL_V_FUN_ZSP_UART_CTS_SEL (2)
#define IOMUX_PAD_GPIO_19_SEL_V_FUN_UART_3_TXD_SEL (3)
#define IOMUX_PAD_GPIO_19_SEL_V_FUN_WCN_UART_TXD_SEL (4)
#define IOMUX_PAD_GPIO_19_SEL_V_FUN_WCN_UART_RTS_SEL (5)

//pad_gpio_20_cfg_reg
#define IOMUX_PAD_GPIO_20_SEL_V_FUN_GPIO_20_SEL (0)
#define IOMUX_PAD_GPIO_20_SEL_V_FUN_UART_2_RXD_SEL (1)
#define IOMUX_PAD_GPIO_20_SEL_V_FUN_UART_3_RXD_SEL (2)
#define IOMUX_PAD_GPIO_20_SEL_V_FUN_ZSP_UART_RXD_SEL (3)
#define IOMUX_PAD_GPIO_20_SEL_V_FUN_UART_3_CTS_SEL (4)
#define IOMUX_PAD_GPIO_20_SEL_V_FUN_ZSP_UART_RTS_SEL (5)
#define IOMUX_PAD_GPIO_20_SEL_V_FUN_DEBUG_BUS_12_SEL (7)

//pad_gpio_21_cfg_reg
#define IOMUX_PAD_GPIO_21_SEL_V_FUN_GPIO_21_SEL (0)
#define IOMUX_PAD_GPIO_21_SEL_V_FUN_UART_2_TXD_SEL (1)
#define IOMUX_PAD_GPIO_21_SEL_V_FUN_UART_3_TXD_SEL (2)
#define IOMUX_PAD_GPIO_21_SEL_V_FUN_ZSP_UART_TXD_SEL (3)
#define IOMUX_PAD_GPIO_21_SEL_V_FUN_UART_3_RTS_SEL (4)
#define IOMUX_PAD_GPIO_21_SEL_V_FUN_ZSP_UART_CTS_SEL (5)
#define IOMUX_PAD_GPIO_21_SEL_V_FUN_DEBUG_BUS_13_SEL (7)

//pad_gpio_22_cfg_reg
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_GPIO_22_SEL (0)
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_UART_2_CTS_SEL (1)
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_UART_3_CTS_SEL (2)
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_ZSP_UART_CTS_SEL (3)
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_UART_3_RXD_SEL (4)
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_ZSP_UART_TXD_SEL (5)
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_ZSP_UART_CTS_SEL_X1 (6)
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_DEBUG_BUS_14_SEL (7)
#define IOMUX_PAD_GPIO_22_SEL_V_FUN_I2C_M3_SCL_SEL (8)

//pad_gpio_23_cfg_reg
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_GPIO_23_SEL (0)
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_UART_2_RTS_SEL (1)
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_UART_3_RTS_SEL (2)
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_ZSP_UART_RTS_SEL (3)
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_UART_3_TXD_SEL (4)
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_ZSP_UART_RXD_SEL (5)
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_UART_3_CTS_SEL (6)
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_DEBUG_BUS_15_SEL (7)
#define IOMUX_PAD_GPIO_23_SEL_V_FUN_I2C_M3_SDA_SEL (8)

//pad_gpio_8_cfg_reg
#define IOMUX_PAD_GPIO_8_SEL_V_FUN_GPIO_8_SEL (0)
#define IOMUX_PAD_GPIO_8_SEL_V_FUN_SPI_1_CS_1_SEL (1)
#define IOMUX_PAD_GPIO_8_SEL_V_FUN_RFDIG_GPIO_8_SEL (2)
#define IOMUX_PAD_GPIO_8_SEL_V_FUN_LTE_GPO_6_SEL (3)
#define IOMUX_PAD_GPIO_8_SEL_V_FUN_DIGRF_STROBE_M_I_SEL (5)
#define IOMUX_PAD_GPIO_8_SEL_V_FUN_GPO_0_SEL (6)
#define IOMUX_PAD_GPIO_8_SEL_V_FUN_DIGRF_STROBE_S_O_SEL (7)

//pad_gpio_9_cfg_reg
#define IOMUX_PAD_GPIO_9_SEL_V_FUN_GPIO_9_SEL (0)
#define IOMUX_PAD_GPIO_9_SEL_V_FUN_SPI_1_CLK_SEL (1)
#define IOMUX_PAD_GPIO_9_SEL_V_FUN_RFDIG_GPIO_9_SEL (2)
#define IOMUX_PAD_GPIO_9_SEL_V_FUN_LTE_GPO_9_SEL (3)
#define IOMUX_PAD_GPIO_9_SEL_V_FUN_LTE_SPI_SDO_SEL (4)
#define IOMUX_PAD_GPIO_9_SEL_V_FUN_GPO_1_SEL (6)

//pad_gpio_10_cfg_reg
#define IOMUX_PAD_GPIO_10_SEL_V_FUN_GPIO_10_SEL (0)
#define IOMUX_PAD_GPIO_10_SEL_V_FUN_SPI_1_CS_0_SEL (1)
#define IOMUX_PAD_GPIO_10_SEL_V_FUN_LTE_SPI_CS_SEL (2)
#define IOMUX_PAD_GPIO_10_SEL_V_FUN_GPO_2_SEL (6)

//pad_gpio_11_cfg_reg
#define IOMUX_PAD_GPIO_11_SEL_V_FUN_GPIO_11_SEL (0)
#define IOMUX_PAD_GPIO_11_SEL_V_FUN_SPI_1_DIO_0_SEL (1)
#define IOMUX_PAD_GPIO_11_SEL_V_FUN_LTE_SPI_SCLK_SEL (2)
#define IOMUX_PAD_GPIO_11_SEL_V_FUN_GPO_3_SEL (6)

//pad_gpio_12_cfg_reg
#define IOMUX_PAD_GPIO_12_SEL_V_FUN_GPIO_12_SEL (0)
#define IOMUX_PAD_GPIO_12_SEL_V_FUN_SPI_1_DI_1_SEL (1)
#define IOMUX_PAD_GPIO_12_SEL_V_FUN_LTE_SPI_SDIO_SEL (2)
#define IOMUX_PAD_GPIO_12_SEL_V_FUN_GPO_4_SEL (6)

//pad_keyin_0_cfg_reg
#define IOMUX_PAD_KEYIN_0_SEL_V_FUN_KEYIN_0_SEL (0)
#define IOMUX_PAD_KEYIN_0_SEL_V_FUN_DEBUG_BUS_8_SEL (7)
#define IOMUX_PAD_KEYIN_0_SEL_V_FUN_WCN_RF_M_BT_TX_52M_SEL (8)

//pad_keyin_1_cfg_reg
#define IOMUX_PAD_KEYIN_1_SEL_V_FUN_KEYIN_1_SEL (0)
#define IOMUX_PAD_KEYIN_1_SEL_V_FUN_DEBUG_BUS_9_SEL (7)
#define IOMUX_PAD_KEYIN_1_SEL_V_FUN_WCN_RF_AGC_INDEX_OUT_0_SEL (8)

//pad_keyin_2_cfg_reg
#define IOMUX_PAD_KEYIN_2_SEL_V_FUN_KEYIN_2_SEL (0)
#define IOMUX_PAD_KEYIN_2_SEL_V_FUN_DEBUG_BUS_10_SEL (7)
#define IOMUX_PAD_KEYIN_2_SEL_V_FUN_WCN_RF_AGC_INDEX_OUT_1_SEL (8)

//pad_keyin_3_cfg_reg
#define IOMUX_PAD_KEYIN_3_SEL_V_FUN_KEYIN_3_SEL (0)
#define IOMUX_PAD_KEYIN_3_SEL_V_FUN_DEBUG_BUS_11_SEL (7)
#define IOMUX_PAD_KEYIN_3_SEL_V_FUN_WCN_RF_AGC_INDEX_OUT_2_SEL (8)

//pad_keyin_4_cfg_reg
#define IOMUX_PAD_KEYIN_4_SEL_V_FUN_KEYIN_4_SEL (0)
#define IOMUX_PAD_KEYIN_4_SEL_V_FUN_UART_2_RXD_SEL (3)
#define IOMUX_PAD_KEYIN_4_SEL_V_FUN_UART_3_CTS_SEL (4)
#define IOMUX_PAD_KEYIN_4_SEL_V_FUN_DEBUG_BUS_12_SEL (7)
#define IOMUX_PAD_KEYIN_4_SEL_V_FUN_WCN_RF_AGC_INDEX_OUT_3_SEL (8)

//pad_keyin_5_cfg_reg
#define IOMUX_PAD_KEYIN_5_SEL_V_FUN_KEYIN_5_SEL (0)
#define IOMUX_PAD_KEYIN_5_SEL_V_FUN_UART_2_TXD_SEL (3)
#define IOMUX_PAD_KEYIN_5_SEL_V_FUN_UART_3_RTS_SEL (4)
#define IOMUX_PAD_KEYIN_5_SEL_V_FUN_DEBUG_BUS_13_SEL (7)
#define IOMUX_PAD_KEYIN_5_SEL_V_FUN_WCN_RF_RXON_OUT_SEL (8)

//pad_keyout_0_cfg_reg
#define IOMUX_PAD_KEYOUT_0_SEL_V_FUN_KEYOUT_0_SEL (0)
#define IOMUX_PAD_KEYOUT_0_SEL_V_FUN_DEBUG_BUS_14_SEL (7)
#define IOMUX_PAD_KEYOUT_0_SEL_V_FUN_WCN_RF_TXON_OUT_SEL (8)

//pad_keyout_1_cfg_reg
#define IOMUX_PAD_KEYOUT_1_SEL_V_FUN_KEYOUT_1_SEL (0)
#define IOMUX_PAD_KEYOUT_1_SEL_V_FUN_DEBUG_BUS_15_SEL (7)
#define IOMUX_PAD_KEYOUT_1_SEL_V_FUN_WCN_RF_APC_OUT_0_SEL (8)

//pad_keyout_2_cfg_reg
#define IOMUX_PAD_KEYOUT_2_SEL_V_FUN_KEYOUT_2_SEL (0)
#define IOMUX_PAD_KEYOUT_2_SEL_V_FUN_DEBUG_CLK_SEL (7)
#define IOMUX_PAD_KEYOUT_2_SEL_V_FUN_WCN_RF_APC_OUT_1_SEL (8)

//pad_keyout_3_cfg_reg
#define IOMUX_PAD_KEYOUT_3_SEL_V_FUN_KEYOUT_3_SEL (0)
#define IOMUX_PAD_KEYOUT_3_SEL_V_FUN_WCN_RF_APC_OUT_2_SEL (8)

//pad_keyout_4_cfg_reg
#define IOMUX_PAD_KEYOUT_4_SEL_V_FUN_KEYOUT_4_SEL (0)
#define IOMUX_PAD_KEYOUT_4_SEL_V_FUN_UART_2_CTS_SEL (3)
#define IOMUX_PAD_KEYOUT_4_SEL_V_FUN_UART_3_RXD_SEL (4)
#define IOMUX_PAD_KEYOUT_4_SEL_V_FUN_WCN_BT_CH_TYPE_IN_SEL (8)

//pad_keyout_5_cfg_reg
#define IOMUX_PAD_KEYOUT_5_SEL_V_FUN_KEYOUT_5_SEL (0)
#define IOMUX_PAD_KEYOUT_5_SEL_V_FUN_UART_2_RTS_SEL (3)
#define IOMUX_PAD_KEYOUT_5_SEL_V_FUN_UART_3_TXD_SEL (4)

//pad_debug_host_rx_cfg_reg
#define IOMUX_PAD_DEBUG_HOST_RX_SEL_V_FUN_DEBUG_HOST_RX_SEL (0)
#define IOMUX_PAD_DEBUG_HOST_RX_SEL_V_FUN_GPIO_16_SEL (1)

//pad_debug_host_tx_cfg_reg
#define IOMUX_PAD_DEBUG_HOST_TX_SEL_V_FUN_DEBUG_HOST_TX_SEL (0)

//pad_debug_host_clk_cfg_reg
#define IOMUX_PAD_DEBUG_HOST_CLK_SEL_V_FUN_DEBUG_HOST_CLK_SEL (0)
#define IOMUX_PAD_DEBUG_HOST_CLK_SEL_V_FUN_GPIO_17_SEL (1)

//pad_sim_1_clk_cfg_reg
#define IOMUX_PAD_SIM_1_CLK_SEL_V_FUN_SIM_1_CLK_SEL (0)

//pad_sim_1_dio_cfg_reg
#define IOMUX_PAD_SIM_1_DIO_SEL_V_FUN_SIM_1_DIO_SEL (0)

//pad_sim_1_rst_cfg_reg
#define IOMUX_PAD_SIM_1_RST_SEL_V_FUN_SIM_1_RST_SEL (0)

//pad_sim_2_clk_cfg_reg
#define IOMUX_PAD_SIM_2_CLK_SEL_V_FUN_SIM_2_CLK_SEL (0)
#define IOMUX_PAD_SIM_2_CLK_SEL_V_FUN_GPO_5_SEL (1)
#define IOMUX_PAD_SIM_2_CLK_SEL_V_FUN_GPIO_29_SEL (2)

//pad_sim_2_dio_cfg_reg
#define IOMUX_PAD_SIM_2_DIO_SEL_V_FUN_SIM_2_DIO_SEL (0)
#define IOMUX_PAD_SIM_2_DIO_SEL_V_FUN_GPO_6_SEL (1)
#define IOMUX_PAD_SIM_2_DIO_SEL_V_FUN_GPIO_30_SEL (2)
#define IOMUX_PAD_SIM_2_DIO_SEL_V_FUN_UART_1_CTS_SEL (3)

//pad_sim_2_rst_cfg_reg
#define IOMUX_PAD_SIM_2_RST_SEL_V_FUN_SIM_2_RST_SEL (0)
#define IOMUX_PAD_SIM_2_RST_SEL_V_FUN_GPO_7_SEL (1)
#define IOMUX_PAD_SIM_2_RST_SEL_V_FUN_GPIO_31_SEL (2)
#define IOMUX_PAD_SIM_2_RST_SEL_V_FUN_UART_1_RTS_SEL (3)

//pad_rfdig_gpio_0_cfg_reg
#define IOMUX_PAD_RFDIG_GPIO_0_SEL_V_FUN_RFDIG_GPIO_0_SEL (0)
#define IOMUX_PAD_RFDIG_GPIO_0_SEL_V_FUN_RFFE_SCLK_SEL (1)
#define IOMUX_PAD_RFDIG_GPIO_0_SEL_V_FUN_LTE_GPO_0_SEL (2)

//pad_rfdig_gpio_1_cfg_reg
#define IOMUX_PAD_RFDIG_GPIO_1_SEL_V_FUN_RFDIG_GPIO_1_SEL (0)
#define IOMUX_PAD_RFDIG_GPIO_1_SEL_V_FUN_RFFE_SDATA_SEL (1)
#define IOMUX_PAD_RFDIG_GPIO_1_SEL_V_FUN_LTE_GPO_1_SEL (2)

//pad_rfdig_gpio_2_cfg_reg
#define IOMUX_PAD_RFDIG_GPIO_2_SEL_V_FUN_RFDIG_GPIO_2_SEL (0)
#define IOMUX_PAD_RFDIG_GPIO_2_SEL_V_FUN_LTE_GPO_2_SEL (2)
#define IOMUX_PAD_RFDIG_GPIO_2_SEL_V_FUN_DFE_RX_ENABLE_M_I_SEL (5)
#define IOMUX_PAD_RFDIG_GPIO_2_SEL_V_FUN_DFE_RX_ENABLE_S_O_SEL (7)

//pad_rfdig_gpio_3_cfg_reg
#define IOMUX_PAD_RFDIG_GPIO_3_SEL_V_FUN_RFDIG_GPIO_3_SEL (0)
#define IOMUX_PAD_RFDIG_GPIO_3_SEL_V_FUN_LTE_GPO_3_SEL (2)
#define IOMUX_PAD_RFDIG_GPIO_3_SEL_V_FUN_DIGRF_CP_26M_M_O_SEL (5)
#define IOMUX_PAD_RFDIG_GPIO_3_SEL_V_FUN_DIGRF_CP_26M_S_I_SEL (7)

//pad_rfdig_gpio_4_cfg_reg
#define IOMUX_PAD_RFDIG_GPIO_4_SEL_V_FUN_RFDIG_GPIO_4_SEL (0)
#define IOMUX_PAD_RFDIG_GPIO_4_SEL_V_FUN_LTE_GPO_4_SEL (2)
#define IOMUX_PAD_RFDIG_GPIO_4_SEL_V_FUN_DIGRF_TX_EN_M_I_SEL (5)
#define IOMUX_PAD_RFDIG_GPIO_4_SEL_V_FUN_DIGRF_TX_EN_S_O_SEL (7)

//pad_rfdig_gpio_5_cfg_reg
#define IOMUX_PAD_RFDIG_GPIO_5_SEL_V_FUN_RFDIG_GPIO_5_SEL (0)
#define IOMUX_PAD_RFDIG_GPIO_5_SEL_V_FUN_LTE_GPO_5_SEL (2)
#define IOMUX_PAD_RFDIG_GPIO_5_SEL_V_FUN_DIGRF_TX_DATA_M_I_SEL (5)
#define IOMUX_PAD_RFDIG_GPIO_5_SEL_V_FUN_DIGRF_TX_DATA_S_O_SEL (7)

//pad_rfdig_gpio_6_cfg_reg
#define IOMUX_PAD_RFDIG_GPIO_6_SEL_V_FUN_RFDIG_GPIO_6_SEL (0)
#define IOMUX_PAD_RFDIG_GPIO_6_SEL_V_FUN_LTE_GPO_7_SEL (2)
#define IOMUX_PAD_RFDIG_GPIO_6_SEL_V_FUN_DIGRF_RX_EN_M_O_SEL (5)
#define IOMUX_PAD_RFDIG_GPIO_6_SEL_V_FUN_DIGRF_RX_EN_S_I_SEL (7)

//pad_rfdig_gpio_7_cfg_reg
#define IOMUX_PAD_RFDIG_GPIO_7_SEL_V_FUN_RFDIG_GPIO_7_SEL (0)
#define IOMUX_PAD_RFDIG_GPIO_7_SEL_V_FUN_LTE_GPO_8_SEL (2)
#define IOMUX_PAD_RFDIG_GPIO_7_SEL_V_FUN_DIGRF_RX_DATA_M_O_SEL (5)
#define IOMUX_PAD_RFDIG_GPIO_7_SEL_V_FUN_DIGRF_RX_DATA_S_I_SEL (7)

//pad_secure_boot_mode_cfg_reg
#define IOMUX_PAD_SECURE_BOOT_MODE_SEL_V_FUN_SECURE_BOOT_MODE_SEL (0)

//pad_nand_flash_sel_cfg_reg
#define IOMUX_PAD_NAND_FLASH_SEL_SEL_V_FUN_NAND_FLASH_SEL_SEL (0)

#endif
