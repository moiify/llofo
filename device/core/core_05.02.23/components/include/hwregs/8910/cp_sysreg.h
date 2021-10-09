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

#ifndef _CP_SYSREG_H_
#define _CP_SYSREG_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'cp_sysreg'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// CP_SYSREG_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_SYSREG_BASE 0x05080000
#else
#define REG_SYSREG_BASE 0x50080000
#endif

typedef volatile struct
{
    REG32 zsp_svtaddr;          //0x00000000
    REG32 mem_ema_cfg_zsp;      //0x00000004
    REG32 mem_ema_cfg_lte;      //0x00000008
    REG32 rom_ema_cfg_lte;      //0x0000000C
    REG32 mem_ema_cfg_bbsys;    //0x00000010
    REG32 zsp_qos;              //0x00000014
    REG32 Reserved_00000018;    //0x00000018
    REG32 flow_para;            //0x0000001C
    REG32 rf_sel;               //0x00000020
    REG32 nb_lte_sel;           //0x00000024
    REG32 ggenb_sel;            //0x00000028
    REG32 rf_ana_26m_ctrl;      //0x0000002C
    REG32 rf_ana_26m_ctrl_set;  //0x00000030
    REG32 rf_ana_26m_ctrl_clr;  //0x00000034
    REG32 ddr_slp_ctrl_enable;  //0x00000038
    REG32 ddr_wakeup_force_en;  //0x0000003C
    REG32 ddr_wakeup_force_ack; //0x00000040
    REG32 ddr_slp_wait_number;  //0x00000044
    REG32 lvds_spi_sel;         //0x00000048
    REG32 monitor_lte_fint_sel; //0x0000004C
    REG32 rfmux_irq_sta;        //0x00000050
    REG32 apt_sel;              //0x00000054
    REG32 rfspi_mode_sel;       //0x00000058
    REG32 Reserved_0000005C;    //0x0000005C
    REG32 ggenb_sys_ctrl;       //0x00000060
    REG32 a5_standbywfi_en;     //0x00000064
} HWP_CP_SYSREG_T;

#define hwp_sysreg ((HWP_CP_SYSREG_T *)REG_ACCESS_ADDRESS(REG_SYSREG_BASE))

//ZSP_SVTADDR
typedef union {
    REG32 v;
    struct
    {
        REG32 __7_0 : 8;
        REG32 svtaddr : 24; // [31:8]
    } b;
} REG_CP_SYSREG_ZSP_SVTADDR_T;

//MEM_EMA_CFG_ZSP
typedef union {
    REG32 v;
    struct
    {
        REG32 radpd_rmea : 1; // [0]
        REG32 radpd_rma : 4;  // [4:1]
        REG32 radpd_rmeb : 1; // [5]
        REG32 radpd_rmb : 4;  // [9:6]
        REG32 raspu_rme : 1;  // [10]
        REG32 raspu_rm : 4;   // [14:11]
        REG32 rfspd_rme : 1;  // [15]
        REG32 rfspd_rm : 4;   // [19:16]
        REG32 rftpd_rmea : 1; // [20]
        REG32 rftpd_rma : 4;  // [24:21]
        REG32 rftpd_rmeb : 1; // [25]
        REG32 rftpd_rmb : 4;  // [29:26]
        REG32 __31_30 : 2;
    } b;
} REG_CP_SYSREG_MEM_EMA_CFG_ZSP_T;

//MEM_EMA_CFG_LTE
typedef union {
    REG32 v;
    struct
    {
        REG32 radpd_rmea : 1; // [0]
        REG32 radpd_rma : 4;  // [4:1]
        REG32 radpd_rmeb : 1; // [5]
        REG32 radpd_rmb : 4;  // [9:6]
        REG32 raspu_rme : 1;  // [10]
        REG32 raspu_rm : 4;   // [14:11]
        REG32 rfspd_rme : 1;  // [15]
        REG32 rfspd_rm : 4;   // [19:16]
        REG32 rftpd_rmea : 1; // [20]
        REG32 rftpd_rma : 4;  // [24:21]
        REG32 rftpd_rmeb : 1; // [25]
        REG32 rftpd_rmb : 4;  // [29:26]
        REG32 __31_30 : 2;
    } b;
} REG_CP_SYSREG_MEM_EMA_CFG_LTE_T;

//ROM_EMA_CFG_LTE
typedef union {
    REG32 v;
    struct
    {
        REG32 rom_rmea : 1; // [0]
        REG32 rom_rma : 4;  // [4:1]
        REG32 __31_5 : 27;
    } b;
} REG_CP_SYSREG_ROM_EMA_CFG_LTE_T;

//MEM_EMA_CFG_BBSYS
typedef union {
    REG32 v;
    struct
    {
        REG32 radpd_rmea : 1; // [0]
        REG32 radpd_rma : 4;  // [4:1]
        REG32 radpd_rmeb : 1; // [5]
        REG32 radpd_rmb : 4;  // [9:6]
        REG32 raspu_rme : 1;  // [10]
        REG32 raspu_rm : 4;   // [14:11]
        REG32 rfspd_rme : 1;  // [15]
        REG32 rfspd_rm : 4;   // [19:16]
        REG32 rftpd_rmea : 1; // [20]
        REG32 rftpd_rma : 4;  // [24:21]
        REG32 rftpd_rmeb : 1; // [25]
        REG32 rftpd_rmb : 4;  // [29:26]
        REG32 __31_30 : 2;
    } b;
} REG_CP_SYSREG_MEM_EMA_CFG_BBSYS_T;

//ZSP_QOS
typedef union {
    REG32 v;
    struct
    {
        REG32 arqos_zsp_dbus : 4;   // [3:0]
        REG32 awqos_zsp_dbus : 4;   // [7:4]
        REG32 arqos_zsp_ibus : 4;   // [11:8]
        REG32 awqos_zsp_ibus : 4;   // [15:12]
        REG32 arqos_zsp_axidma : 4; // [19:16]
        REG32 awqos_zsp_axidma : 4; // [23:20]
        REG32 __31_24 : 8;
    } b;
} REG_CP_SYSREG_ZSP_QOS_T;

//RF_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 rfsel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_RF_SEL_T;

//NB_LTE_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 nblte_sel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_NB_LTE_SEL_T;

//GGENB_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 gge_nb_sel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_GGENB_SEL_T;

//RF_ANA_26M_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 enable_clk_26m_usb : 1;    // [0]
        REG32 enable_clk_26m_dsi : 1;    // [1]
        REG32 enable_clk_26m_audio : 1;  // [2]
        REG32 muxsel_clk26m_audio : 1;   // [3]
        REG32 enable_clk_26m_aud2ad : 1; // [4]
        REG32 muxsel_clk26m_aud2ad : 1;  // [5]
        REG32 enable_clk_26m_vad : 1;    // [6]
        REG32 enable_clk_26m_adi : 1;    // [7]
        REG32 enable_clk_26m_wcn : 1;    // [8]
        REG32 __31_9 : 23;
    } b;
} REG_CP_SYSREG_RF_ANA_26M_CTRL_T;

//RF_ANA_26M_CTRL_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 set : 9; // [8:0], write set
        REG32 __31_9 : 23;
    } b;
} REG_CP_SYSREG_RF_ANA_26M_CTRL_SET_T;

//RF_ANA_26M_CTRL_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 clear : 9; // [8:0], write clear
        REG32 __31_9 : 23;
    } b;
} REG_CP_SYSREG_RF_ANA_26M_CTRL_CLR_T;

//DDR_SLP_CTRL_ENABLE
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_DDR_SLP_CTRL_ENABLE_T;

//DDR_WAKEUP_FORCE_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_DDR_WAKEUP_FORCE_EN_T;

//DDR_WAKEUP_FORCE_ACK
typedef union {
    REG32 v;
    struct
    {
        REG32 ack : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_DDR_WAKEUP_FORCE_ACK_T;

//DDR_SLP_WAIT_NUMBER
typedef union {
    REG32 v;
    struct
    {
        REG32 n : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_SYSREG_DDR_SLP_WAIT_NUMBER_T;

//LVDS_SPI_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 sel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_LVDS_SPI_SEL_T;

//MONITOR_LTE_FINT_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 sel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_MONITOR_LTE_FINT_SEL_T;

//RFMUX_IRQ_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 txfifo_full_irq : 1;    // [0], write clear
        REG32 rfspi_conflict_irq : 1; // [1], write clear
        REG32 __31_2 : 30;
    } b;
} REG_CP_SYSREG_RFMUX_IRQ_STA_T;

//APT_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 sel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_APT_SEL_T;

//RFSPI_MODE_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 sel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_SYSREG_RFSPI_MODE_SEL_T;

//GGENB_SYS_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 ggenb_ctrl : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_SYSREG_GGENB_SYS_CTRL_T;

//A5_STANDBYWFI_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 ap_a5_standby_en : 1; // [0]
        REG32 cp_a5_standby_en : 1; // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_SYSREG_A5_STANDBYWFI_EN_T;

#endif
