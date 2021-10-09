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

#ifndef _CP_PWRCTRL_H_
#define _CP_PWRCTRL_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'cp_pwrctrl'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// CP_PWRCTRL_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_PWRCTRL_BASE 0x050A0000
#else
#define REG_PWRCTRL_BASE 0x500A0000
#endif

typedef volatile struct
{
    REG32 pwr_hwen;              //0x00000000
    REG32 ap_pwr_ctrl;           //0x00000004
    REG32 zsp_pwr_ctrl;          //0x00000008
    REG32 lte_pwr_ctrl;          //0x0000000C
    REG32 gge_pwr_ctrl;          //0x00000010
    REG32 rf_pwr_ctrl;           //0x00000014
    REG32 btfm_pwr_ctrl;         //0x00000018
    REG32 aon_lp_pwr_ctrl;       //0x0000001C
    REG32 ap_pwr_stat;           //0x00000020
    REG32 zsp_pwr_stat;          //0x00000024
    REG32 lte_pwr_stat;          //0x00000028
    REG32 gge_pwr_stat;          //0x0000002C
    REG32 rf_pwr_stat;           //0x00000030
    REG32 btfm_pwr_stat;         //0x00000034
    REG32 aon_lp_pwr_stat;       //0x00000038
    REG32 state_delay;           //0x0000003C
    REG32 prepgc_delay;          //0x00000040
    REG32 allpgc_delay;          //0x00000044
    REG32 ddr_hold_ctrl;         //0x00000048
    REG32 zsp_pd_poll;           //0x0000004C
    REG32 zsp_pd_poll_set;       //0x00000050
    REG32 zsp_pd_poll_clr;       //0x00000054
    REG32 Reserved_00000058[14]; //0x00000058
    REG32 wcn_lps;               //0x00000090
    REG32 arm_slp_req_sw;        //0x00000094
    REG32 arm_slp_ack;           //0x00000098
    REG32 arm_slp_req_hwen;      //0x0000009C
    REG32 zsp_slp_req_sw;        //0x000000A0
    REG32 zsp_slp_ack;           //0x000000A4
    REG32 zsp_slp_req_hwen;      //0x000000A8
    REG32 ddr_slp_req_sw;        //0x000000AC
    REG32 ddr_slp_ack;           //0x000000B0
    REG32 ddr_slp_req_hwen;      //0x000000B4
    REG32 timeout_flag;          //0x000000B8
    REG32 power_state;           //0x000000BC
    REG32 pwrctrl_mode;          //0x000000C0
    REG32 pwrctrl_sw;            //0x000000C4
    REG32 pwrctrl_sw_set;        //0x000000C8
    REG32 pwrctrl_sw_clr;        //0x000000CC
    REG32 pwrctrl_sw1;           //0x000000D0
    REG32 pwrctrl_sw1_set;       //0x000000D4
    REG32 pwrctrl_sw1_clr;       //0x000000D8
} HWP_CP_PWRCTRL_T;

#define hwp_pwrctrl ((HWP_CP_PWRCTRL_T *)REG_ACCESS_ADDRESS(REG_PWRCTRL_BASE))

//PWR_HWEN
typedef union {
    REG32 v;
    struct
    {
        REG32 ap_pwr_en : 1;     // [0]
        REG32 zsp_pon_en : 1;    // [1]
        REG32 lte_pon_en : 1;    // [2]
        REG32 gge_pon_en : 1;    // [3]
        REG32 rf_pon_en : 1;     // [4]
        REG32 btfm_pon_en : 1;   // [5]
        REG32 aon_lp_pon_en : 1; // [6]
        REG32 __31_7 : 25;
    } b;
} REG_CP_PWRCTRL_PWR_HWEN_T;

//AP_PWR_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 ap_poff : 1; // [0]
        REG32 ap_pon : 1;  // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_AP_PWR_CTRL_T;

//ZSP_PWR_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 zsp_poff : 1; // [0]
        REG32 zsp_pon : 1;  // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_ZSP_PWR_CTRL_T;

//LTE_PWR_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 lte_poff : 1; // [0]
        REG32 lte_pon : 1;  // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_LTE_PWR_CTRL_T;

//GGE_PWR_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 gge_poff : 1; // [0]
        REG32 gge_pon : 1;  // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_GGE_PWR_CTRL_T;

//RF_PWR_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_poff : 1; // [0]
        REG32 rf_pon : 1;  // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_RF_PWR_CTRL_T;

//BTFM_PWR_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 btfm_poff : 1; // [0]
        REG32 btfm_pon : 1;  // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_BTFM_PWR_CTRL_T;

//AON_LP_PWR_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 aon_lp_poff : 1; // [0]
        REG32 aon_lp_pon : 1;  // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_AON_LP_PWR_CTRL_T;

//AP_PWR_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 ap_pstat : 1;  // [0], read only
        REG32 ap_stable : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_AP_PWR_STAT_T;

//ZSP_PWR_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 zsp_pstat : 1;  // [0], read only
        REG32 zsp_stable : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_ZSP_PWR_STAT_T;

//LTE_PWR_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 lte_pstat : 1;  // [0], read only
        REG32 lte_stable : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_LTE_PWR_STAT_T;

//GGE_PWR_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 gge_pstat : 1;  // [0], read only
        REG32 gge_stable : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_GGE_PWR_STAT_T;

//RF_PWR_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 rf_pstat : 1;  // [0], read only
        REG32 rf_stable : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_RF_PWR_STAT_T;

//BTFM_PWR_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 btfm_pstat : 1;  // [0], read only
        REG32 btfm_stable : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_BTFM_PWR_STAT_T;

//AON_LP_PWR_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 aon_lp_pstat : 1;  // [0], read only
        REG32 aon_lp_stable : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_CP_PWRCTRL_AON_LP_PWR_STAT_T;

//STATE_DELAY
typedef union {
    REG32 v;
    struct
    {
        REG32 delay : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_CP_PWRCTRL_STATE_DELAY_T;

//PREPGC_DELAY
typedef union {
    REG32 v;
    struct
    {
        REG32 delay : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_PWRCTRL_PREPGC_DELAY_T;

//ALLPGC_DELAY
typedef union {
    REG32 v;
    struct
    {
        REG32 delay : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_PWRCTRL_ALLPGC_DELAY_T;

//DDR_HOLD_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 hold_ctrl : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_DDR_HOLD_CTRL_T;

//ZSP_PD_POLL
typedef union {
    REG32 v;
    struct
    {
        REG32 ap_poll : 1;  // [0]
        REG32 cp_poll : 1;  // [1]
        REG32 zsp_poll : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_CP_PWRCTRL_ZSP_PD_POLL_T;

//ZSP_PD_POLL_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 zsppollset : 3; // [2:0], write set
        REG32 __31_3 : 29;
    } b;
} REG_CP_PWRCTRL_ZSP_PD_POLL_SET_T;

//ZSP_PD_POLL_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 zsppollclr : 3; // [2:0], write clear
        REG32 __31_3 : 29;
    } b;
} REG_CP_PWRCTRL_ZSP_PD_POLL_CLR_T;

//WCN_LPS
typedef union {
    REG32 v;
    struct
    {
        REG32 sys2wcn_wakeup : 1; // [0]
        REG32 wcn2sys_wakeup : 1; // [1], read only
        REG32 wcn2sys_osc_en : 1; // [2], read only
        REG32 wcn2sys_sleep : 1;  // [3], read only
        REG32 __31_4 : 28;
    } b;
} REG_CP_PWRCTRL_WCN_LPS_T;

//ARM_SLP_REQ_SW
typedef union {
    REG32 v;
    struct
    {
        REG32 armslpreq : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_ARM_SLP_REQ_SW_T;

//ARM_SLP_ACK
typedef union {
    REG32 v;
    struct
    {
        REG32 armslpack : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_ARM_SLP_ACK_T;

//ARM_SLP_REQ_HWEN
typedef union {
    REG32 v;
    struct
    {
        REG32 armslpreq_hwen : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_ARM_SLP_REQ_HWEN_T;

//ZSP_SLP_REQ_SW
typedef union {
    REG32 v;
    struct
    {
        REG32 zspslpreq : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_ZSP_SLP_REQ_SW_T;

//ZSP_SLP_ACK
typedef union {
    REG32 v;
    struct
    {
        REG32 zspslpack : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_ZSP_SLP_ACK_T;

//ZSP_SLP_REQ_HWEN
typedef union {
    REG32 v;
    struct
    {
        REG32 zspslpreq_hwen : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_ZSP_SLP_REQ_HWEN_T;

//DDR_SLP_REQ_SW
typedef union {
    REG32 v;
    struct
    {
        REG32 ddrslpreq : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_DDR_SLP_REQ_SW_T;

//DDR_SLP_ACK
typedef union {
    REG32 v;
    struct
    {
        REG32 ddrslpack : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_DDR_SLP_ACK_T;

//DDR_SLP_REQ_HWEN
typedef union {
    REG32 v;
    struct
    {
        REG32 ddrslpreq_hwen : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_DDR_SLP_REQ_HWEN_T;

//TIMEOUT_FLAG
typedef union {
    REG32 v;
    struct
    {
        REG32 armbusslptimeout : 1; // [0]
        REG32 zspbusslptimeout : 1; // [1]
        REG32 ddrslptimeout : 1;    // [2]
        REG32 __31_3 : 29;
    } b;
} REG_CP_PWRCTRL_TIMEOUT_FLAG_T;

//POWER_STATE
typedef union {
    REG32 v;
    struct
    {
        REG32 armpowerstate : 4;   // [3:0], read only
        REG32 zsppowerstate : 4;   // [7:4], read only
        REG32 ltepowerstate : 4;   // [11:8], read only
        REG32 ggepowerstate : 4;   // [15:12], read only
        REG32 rfpowerstate : 4;    // [19:16], read only
        REG32 btfmpowerstate : 4;  // [23:20], read only
        REG32 aonlppowerstate : 4; // [27:24], read only
        REG32 corepowerstate : 4;  // [31:28], read only
    } b;
} REG_CP_PWRCTRL_POWER_STATE_T;

//PWRCTRL_MODE
typedef union {
    REG32 v;
    struct
    {
        REG32 pwr_mode : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_PWRCTRL_PWRCTRL_MODE_T;

//PWRCTRL_SW
typedef union {
    REG32 v;
    struct
    {
        REG32 ap_clk_ctrl : 1;       // [0]
        REG32 ap_rst_ctrl : 1;       // [1]
        REG32 ap_hold : 1;           // [2]
        REG32 ap_pwr_ctrl_pre : 1;   // [3]
        REG32 ap_pwr_ctrl : 1;       // [4]
        REG32 zsp_clk_ctrl : 1;      // [5]
        REG32 zsp_rst_ctrl : 1;      // [6]
        REG32 zsp_hold : 1;          // [7]
        REG32 zsp_pwr_ctrl_pre : 1;  // [8]
        REG32 zsp_pwr_ctrl : 1;      // [9]
        REG32 lte_clk_ctrl : 1;      // [10]
        REG32 lte_rst_ctrl : 1;      // [11]
        REG32 lte_hold : 1;          // [12]
        REG32 lte_pwr_ctrl_pre : 1;  // [13]
        REG32 lte_pwr_ctrl : 1;      // [14]
        REG32 gge_clk_ctrl : 1;      // [15]
        REG32 gge_rst_ctrl : 1;      // [16]
        REG32 gge_hold : 1;          // [17]
        REG32 gge_pwr_ctrl_pre : 1;  // [18]
        REG32 gge_pwr_ctrl : 1;      // [19]
        REG32 rf_clk_ctrl : 1;       // [20]
        REG32 rf_rst_ctrl : 1;       // [21]
        REG32 rf_hold : 1;           // [22]
        REG32 rf_pwr_ctrl_pre : 1;   // [23]
        REG32 rf_pwr_ctrl : 1;       // [24]
        REG32 btfm_clk_ctrl : 1;     // [25]
        REG32 btfm_rst_ctrl : 1;     // [26]
        REG32 btfm_hold : 1;         // [27]
        REG32 btfm_pwr_ctrl_pre : 1; // [28]
        REG32 btfm_pwr_ctrl : 1;     // [29]
        REG32 __31_30 : 2;
    } b;
} REG_CP_PWRCTRL_PWRCTRL_SW_T;

//PWRCTRL_SW_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 set : 30; // [29:0], write set
        REG32 __31_30 : 2;
    } b;
} REG_CP_PWRCTRL_PWRCTRL_SW_SET_T;

//PWRCTRL_SW_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 clear : 30; // [29:0], write clear
        REG32 __31_30 : 2;
    } b;
} REG_CP_PWRCTRL_PWRCTRL_SW_CLR_T;

//PWRCTRL_SW1
typedef union {
    REG32 v;
    struct
    {
        REG32 aon_lp_clk_ctrl : 1;     // [0]
        REG32 aon_lp_rst_ctrl : 1;     // [1]
        REG32 aon_lp_hold : 1;         // [2]
        REG32 aon_lp_pwr_ctrl_pre : 1; // [3]
        REG32 aon_lp_pwr_ctrl : 1;     // [4]
        REG32 __31_5 : 27;
    } b;
} REG_CP_PWRCTRL_PWRCTRL_SW1_T;

//PWRCTRL_SW1_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 set : 5; // [4:0], write set
        REG32 __31_5 : 27;
    } b;
} REG_CP_PWRCTRL_PWRCTRL_SW1_SET_T;

//PWRCTRL_SW1_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 clear : 5; // [4:0], write clear
        REG32 __31_5 : 27;
    } b;
} REG_CP_PWRCTRL_PWRCTRL_SW1_CLR_T;

#endif
