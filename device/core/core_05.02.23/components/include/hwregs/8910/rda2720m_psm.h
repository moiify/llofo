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

#ifndef _RDA2720M_PSM_H_
#define _RDA2720M_PSM_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_psm'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_PSM_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_PSM_BASE 0x50308900

typedef volatile struct
{
    REG32 psm_reg_wr_protect;     //0x00000000
    REG32 psm_32k_cal_th;         //0x00000004
    REG32 psm_26m_cal_dn_th;      //0x00000008
    REG32 psm_26m_cal_up_th;      //0x0000000C
    REG32 psm_ctrl;               //0x00000010
    REG32 rtc_pwr_off_th1;        //0x00000014
    REG32 rtc_pwr_off_th2;        //0x00000018
    REG32 rtc_pwr_off_th3;        //0x0000001C
    REG32 rtc_pwr_on_th1;         //0x00000020
    REG32 rtc_pwr_on_th2;         //0x00000024
    REG32 rtc_pwr_on_th3;         //0x00000028
    REG32 psm_cnt_l_th;           //0x0000002C
    REG32 psm_cnt_h_th;           //0x00000030
    REG32 psm_alarm_cnt_l_th;     //0x00000034
    REG32 psm_alarm_cnt_h_th;     //0x00000038
    REG32 psm_cnt_interval_th;    //0x0000003C
    REG32 psm_cnt_interval_phase; //0x00000040
    REG32 dcxo;                   //0x00000044
    REG32 psm_rc_clk_div;         //0x00000048
    REG32 reserved_2;             //0x0000004C
    REG32 reserved_3;             //0x00000050
    REG32 reserved_4;             //0x00000054
    REG32 reserved_5;             //0x00000058
    REG32 reserved_6;             //0x0000005C
    REG32 psm_cnt_update_l_value; //0x00000060
    REG32 psm_cnt_update_h_value; //0x00000064
    REG32 psm_status;             //0x00000068
    REG32 psm_fsm_status;         //0x0000006C
    REG32 psm_cal_cnt;            //0x00000070
} HWP_RDA2720M_PSM_T;

#define hwp_rda2720mPsm ((HWP_RDA2720M_PSM_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_PSM_BASE))

//psm_reg_wr_protect
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_reg_wr : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_REG_WR_PROTECT_T;

//psm_32k_cal_th
typedef union {
    REG32 v;
    struct
    {
        REG32 rc_32k_cal_cnt_n : 4; // [3:0]
        REG32 __7_4 : 4;
        REG32 rc_32k_cal_pre_th : 4; // [11:8]
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_PSM_PSM_32K_CAL_TH_T;

//psm_26m_cal_dn_th
typedef union {
    REG32 v;
    struct
    {
        REG32 rc_26m_cal_cnt_dn_th : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_26M_CAL_DN_TH_T;

//psm_26m_cal_up_th
typedef union {
    REG32 v;
    struct
    {
        REG32 rc_26m_cal_cnt_up_th : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_26M_CAL_UP_TH_T;

//psm_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_en : 1;                // [0]
        REG32 rtc_pwr_on_timeout_en : 1; // [1]
        REG32 ext_int_pwr_en : 1;        // [2]
        REG32 pbint1_pwr_en : 1;         // [3]
        REG32 pbint2_pwr_en : 1;         // [4]
        REG32 charger_pwr_en : 1;        // [5]
        REG32 psm_cnt_alarm_en : 1;      // [6]
        REG32 psm_cnt_alm_en : 1;        // [7]
        REG32 psm_software_reset : 1;    // [8]
        REG32 psm_cnt_update : 1;        // [9]
        REG32 psm_cnt_en : 1;            // [10]
        REG32 psm_status_clr : 1;        // [11]
        REG32 psm_cal_en : 1;            // [12]
        REG32 __14_13 : 2;
        REG32 rtc_32k_clk_sel : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_CTRL_T;

//rtc_pwr_off_th1
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_pwr_off_clk_en_th : 8; // [7:0]
        REG32 rtc_pwr_off_hold_th : 8;   // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_RTC_PWR_OFF_TH1_T;

//rtc_pwr_off_th2
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_pwr_off_rstn_th : 8; // [7:0]
        REG32 rtc_pwr_off_pd_th : 8;   // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_RTC_PWR_OFF_TH2_T;

//rtc_pwr_off_th3
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_pwr_off_done_th : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_PSM_RTC_PWR_OFF_TH3_T;

//rtc_pwr_on_th1
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_pwr_on_pd_th : 8;   // [7:0]
        REG32 rtc_pwr_on_rstn_th : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_RTC_PWR_ON_TH1_T;

//rtc_pwr_on_th2
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_pwr_on_hold_th : 8;   // [7:0]
        REG32 rtc_pwr_on_clk_en_th : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_RTC_PWR_ON_TH2_T;

//rtc_pwr_on_th3
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_pwr_on_done_th : 8;    // [7:0]
        REG32 rtc_pwr_on_timeout_th : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_RTC_PWR_ON_TH3_T;

//psm_cnt_l_th
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_cnt_th_15_0_ : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_CNT_L_TH_T;

//psm_cnt_h_th
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_cnt_th_31_16_ : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_CNT_H_TH_T;

//psm_alarm_cnt_l_th
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_alarm_cnt_th_15_0_ : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_ALARM_CNT_L_TH_T;

//psm_alarm_cnt_h_th
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_alarm_cnt_th_31_16_ : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_ALARM_CNT_H_TH_T;

//psm_cnt_interval_th
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_cnt_interval_th_15_0_ : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_CNT_INTERVAL_TH_T;

//psm_cnt_interval_phase
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_cnt_interval_phase_15_0_ : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_CNT_INTERVAL_PHASE_T;

//DCXO
typedef union {
    REG32 v;
    struct
    {
        REG32 ldo_dcxo_v : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 ldo_dcxo_cl_adj : 1;   // [8]
        REG32 ldo_dcxo_shpt_adj : 1; // [9]
        REG32 ldo_dcxo_stb : 2;      // [11:10]
        REG32 ldo_dcxo_cap_sel : 1;  // [12]
        REG32 ldo_dcxo_shpt_pd : 1;  // [13]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_PSM_DCXO_T;

//psm_rc_clk_div
typedef union {
    REG32 v;
    struct
    {
        REG32 wdg_rst_clk_sel_en : 1; // [0]
        REG32 __3_1 : 3;
        REG32 clk_cal_64k_div_th : 3; // [6:4]
        REG32 __7_7 : 1;
        REG32 rc_32k_cal_cnt_p : 4; // [11:8]
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_PSM_PSM_RC_CLK_DIV_T;

//psm_cnt_update_l_value
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_cnt_update_value_15_0_ : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_CNT_UPDATE_L_VALUE_T;

//psm_cnt_update_h_value
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_cnt_update_value_31_16_ : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_CNT_UPDATE_H_VALUE_T;

//psm_status
typedef union {
    REG32 v;
    struct
    {
        REG32 ext_int : 1;            // [0], read only
        REG32 pbint1_int : 1;         // [1], read only
        REG32 pbint2_int : 1;         // [2], read only
        REG32 charger_int : 1;        // [3], read only
        REG32 psm_req_int : 1;        // [4], read only
        REG32 alarm_req_int : 1;      // [5], read only
        REG32 psm_cnt_update_vld : 1; // [6], read only
        REG32 __7_7 : 1;
        REG32 ext_int_mask : 1;       // [8]
        REG32 pbint1_int_mask : 1;    // [9]
        REG32 pbint2_int_mask : 1;    // [10]
        REG32 charger_int_mask : 1;   // [11]
        REG32 psm_req_int_mask : 1;   // [12]
        REG32 alarm_req_int_mask : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_PSM_PSM_STATUS_T;

//psm_fsm_status
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_fsm : 15; // [14:0], read only
        REG32 __31_15 : 17;
    } b;
} REG_RDA2720M_PSM_PSM_FSM_STATUS_T;

//psm_cal_cnt
typedef union {
    REG32 v;
    struct
    {
        REG32 psm_cal_cnt : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_PSM_PSM_CAL_CNT_T;

#endif
