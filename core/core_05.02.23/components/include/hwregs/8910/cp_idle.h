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

#ifndef _CP_IDLE_H_
#define _CP_IDLE_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'cp_idle'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// CP_IDLE_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_IDLE_BASE 0x05090000
#else
#define REG_IDLE_BASE 0x50090000
#endif

typedef volatile struct
{
    REG32 idl_ctrl_sys1;           //0x00000000
    REG32 idl_ctrl_sys2;           //0x00000004
    REG32 idl_en;                  //0x00000008
    REG32 idl_m_timer;             //0x0000000C
    REG32 idl_wcn_en;              //0x00000010
    REG32 idl_ctrl_timer;          //0x00000014
    REG32 idl_m2_sys;              //0x00000018
    REG32 idl_tc_start;            //0x0000001C
    REG32 idl_tc_end;              //0x00000020
    REG32 idl_awk_timer;           //0x00000024
    REG32 gsm_lp_pu_done;          //0x00000028
    REG32 gsm_frame_inten;         //0x0000002C
    REG32 gsm_frame_int_sta;       //0x00000030
    REG32 ltem1_frame_inten;       //0x00000034
    REG32 ltem1_frame_int_sta;     //0x00000038
    REG32 ltem2_frame_inten;       //0x0000003C
    REG32 ltem2_frame_int_sta;     //0x00000040
    REG32 idl_sta;                 //0x00000044
    REG32 idl_h_ctrl;              //0x00000048
    REG32 idl_h_val;               //0x0000004C
    REG32 idl_h_gsm;               //0x00000050
    REG32 idl_h_ltem;              //0x00000054
    REG32 idl_awk_en;              //0x00000058
    REG32 idl_awk_st;              //0x0000005C
    REG32 idl_awk_self;            //0x00000060
    REG32 idl_osw1_en;             //0x00000064
    REG32 idl_osw1_cont;           //0x00000068
    REG32 idl_fn_gsm;              //0x0000006C
    REG32 idl_fn_ltem1;            //0x00000070
    REG32 idl_fn_ltem2;            //0x00000074
    REG32 idl_ltem_rfl;            //0x00000078
    REG32 idl_ltem_sfl;            //0x0000007C
    REG32 idl_sig_en;              //0x00000080
    REG32 idl_sig_timer;           //0x00000084
    REG32 idl_32k_ref;             //0x00000088
    REG32 cp_inten;                //0x0000008C
    REG32 cp_inten_set;            //0x00000090
    REG32 cp_inten_clr;            //0x00000094
    REG32 cp_int_sta;              //0x00000098
    REG32 ap_inten;                //0x0000009C
    REG32 ap_inten_set;            //0x000000A0
    REG32 ap_inten_clr;            //0x000000A4
    REG32 ap_int_sta;              //0x000000A8
    REG32 ltem1_cfsr_hfn;          //0x000000AC
    REG32 ltem1_cfsr_fn;           //0x000000B0
    REG32 ltem1_cfsrs;             //0x000000B4
    REG32 ltem1_cfsr_rdh;          //0x000000B8
    REG32 ltem1_cfsr_rdl;          //0x000000BC
    REG32 ltem1_framc;             //0x000000C0
    REG32 ltem1_framl;             //0x000000C4
    REG32 ltem1_framls;            //0x000000C8
    REG32 ltem1_cfsr_tph;          //0x000000CC
    REG32 ltem1_cfsr_tpl;          //0x000000D0
    REG32 ltem1_framc_tp;          //0x000000D4
    REG32 ltem2_cfsr_hfn;          //0x000000D8
    REG32 ltem2_cfsr_fn;           //0x000000DC
    REG32 ltem2_cfsrs;             //0x000000E0
    REG32 ltem2_cfsr_rdh;          //0x000000E4
    REG32 ltem2_cfsr_rdl;          //0x000000E8
    REG32 ltem2_framc;             //0x000000EC
    REG32 ltem2_framl;             //0x000000F0
    REG32 ltem2_framls;            //0x000000F4
    REG32 ltem2_cfsr_tph;          //0x000000F8
    REG32 ltem2_cfsr_tpl;          //0x000000FC
    REG32 ltem2_framc_tp;          //0x00000100
    REG32 gsm_cfsr;                //0x00000104
    REG32 gsm_cfsrs;               //0x00000108
    REG32 gsm_cfsro;               //0x0000010C
    REG32 ltem1_fhl;               //0x00000110
    REG32 ltem1_fll;               //0x00000114
    REG32 ltem1_fcl;               //0x00000118
    REG32 ltem2_fhl;               //0x0000011C
    REG32 ltem2_fll;               //0x00000120
    REG32 ltem2_fcl;               //0x00000124
    REG32 gsm_fl;                  //0x00000128
    REG32 gsm_fcl;                 //0x0000012C
    REG32 tpctrl;                  //0x00000130
    REG32 layoutt;                 //0x00000134
    REG32 layoutctrl;              //0x00000138
    REG32 ltem1_fint_dly1;         //0x0000013C
    REG32 ltem1_fint_dly2;         //0x00000140
    REG32 ltem2_fint_dly1;         //0x00000144
    REG32 ltem2_fint_dly2;         //0x00000148
    REG32 fint_en;                 //0x0000014C
    REG32 timer_en;                //0x00000150
    REG32 idle_frame_sta;          //0x00000154
    REG32 idle_frame_ltem1;        //0x00000158
    REG32 idle_frame_ltem2;        //0x0000015C
    REG32 idle_frame_gsm;          //0x00000160
    REG32 idle_frame_lte;          //0x00000164
    REG32 idle_frame_lte_conf;     //0x00000168
    REG32 ltem_ref_fn;             //0x0000016C
    REG32 ltem_ref_fnl;            //0x00000170
    REG32 ltem_ref_fcl;            //0x00000174
    REG32 ref_32k_fnl;             //0x00000178
    REG32 ltem_ref_fc;             //0x0000017C
    REG32 gsm_framl;               //0x00000180
    REG32 idl_osw2_en;             //0x00000184
    REG32 idl_osw2_cont;           //0x00000188
    REG32 idle_framc_gsm;          //0x0000018C
    REG32 ltem1_fint_dly3;         //0x00000190
    REG32 ltem2_fint_dly3;         //0x00000194
    REG32 idle_time_sel;           //0x00000198
    REG32 idle_time;               //0x0000019C
    REG32 idl_h_gsm_lp;            //0x000001A0
    REG32 idl_h_ltem_lp;           //0x000001A4
    REG32 idl_tc_start_nb;         //0x000001A8
    REG32 idl_tc_end_nb;           //0x000001AC
    REG32 nb_lp_pu_done;           //0x000001B0
    REG32 idl_h_nb;                //0x000001B4
    REG32 idl_h_nb_lp;             //0x000001B8
    REG32 idl_fn_nb;               //0x000001BC
    REG32 nb_frame_inten;          //0x000001C0
    REG32 nb_frame_int_sta;        //0x000001C4
    REG32 nb_cfsr;                 //0x000001C8
    REG32 nb_framl;                //0x000001CC
    REG32 nb_cfsrs;                //0x000001D0
    REG32 nb_cfsro;                //0x000001D4
    REG32 nb_fl;                   //0x000001D8
    REG32 nb_fcl;                  //0x000001DC
    REG32 idle_frame_nb;           //0x000001E0
    REG32 idle_framc_nb;           //0x000001E4
    REG32 idl_awk_en_set;          //0x000001E8
    REG32 idl_awk_en_clr;          //0x000001EC
    REG32 gsm_framc;               //0x000001F0
    REG32 nb_framc;                //0x000001F4
    REG32 eliminat_jitter;         //0x000001F8
    REG32 gsm_en_sel;              //0x000001FC
    REG32 nb_en_sel;               //0x00000200
    REG32 pd_pll_sw;               //0x00000204
    REG32 pd_pll_sw_set;           //0x00000208
    REG32 pd_pll_sw_clr;           //0x0000020C
    REG32 pd_pll_sel;              //0x00000210
    REG32 pd_pll_sel_set;          //0x00000214
    REG32 pd_pll_sel_clr;          //0x00000218
    REG32 idle_cg_sw;              //0x0000021C
    REG32 idle_cg_sw_set;          //0x00000220
    REG32 idle_cg_sw_clr;          //0x00000224
    REG32 idle_cg_sel;             //0x00000228
    REG32 idle_cg_sel_set;         //0x0000022C
    REG32 idle_cg_sel_clr;         //0x00000230
    REG32 rf_idle_enable_sw;       //0x00000234
    REG32 rf_idle_enable_sel;      //0x00000238
    REG32 Reserved_0000023C[8];    //0x0000023C
    REG32 mem_ema_cfg;             //0x0000025C
    REG32 uart_ctrl;               //0x00000260
    REG32 ddr_latch;               //0x00000264
    REG32 pad_ctrl;                //0x00000268
    REG32 Reserved_0000026C[4];    //0x0000026C
    REG32 pad_ctrl_uart_txd;       //0x0000027C
    REG32 mon_sel;                 //0x00000280
    REG32 mon_sel_set;             //0x00000284
    REG32 mon_sel_clr;             //0x00000288
    REG32 target_timer;            //0x0000028C
    REG32 target_timer_en;         //0x00000290
    REG32 target_value_lock;       //0x00000294
    REG32 target_timer_stat;       //0x00000298
    REG32 slow_sys_clk_sel_hwen;   //0x0000029C
    REG32 slow_clk_sel_hwen;       //0x000002A0
    REG32 sleep_prot_time;         //0x000002A4
    REG32 Reserved_000002A8[3926]; //0x000002A8
    REG32 idle_res0;               //0x00004000
    REG32 idle_res1;               //0x00004004
    REG32 idle_res2;               //0x00004008
    REG32 idle_res3;               //0x0000400C
    REG32 idle_res4;               //0x00004010
    REG32 idle_res5;               //0x00004014
    REG32 idle_res6;               //0x00004018
    REG32 idle_res7;               //0x0000401C
    REG32 idle_res8;               //0x00004020
    REG32 idle_res9;               //0x00004024
    REG32 idle_res10;              //0x00004028
    REG32 idle_res11;              //0x0000402C
} HWP_CP_IDLE_T;

#define hwp_idle ((HWP_CP_IDLE_T *)REG_ACCESS_ADDRESS(REG_IDLE_BASE))

//IDL_CTRL_SYS1
typedef union {
    REG32 v;
    struct
    {
        REG32 idct_ctrl_sys1 : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_IDL_CTRL_SYS1_T;

//IDL_CTRL_SYS2
typedef union {
    REG32 v;
    struct
    {
        REG32 idct_ctrl_sys2 : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_IDL_CTRL_SYS2_T;

//IDL_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 idl_cp_en : 1; // [0]
        REG32 idl_ap_en : 1; // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_IDLE_IDL_EN_T;

//IDL_WCN_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 wcn_chip_pd : 1; // [0]
        REG32 wcn_pd_xtal : 1; // [1]
        REG32 wcn_pd_pll : 1;  // [2]
        REG32 wcn_idle_cg : 1; // [3]
        REG32 wcn_res_val : 1; // [4]
        REG32 __31_5 : 27;
    } b;
} REG_CP_IDLE_IDL_WCN_EN_T;

//IDL_CTRL_TIMER
typedef union {
    REG32 v;
    struct
    {
        REG32 idct_ctrl_timer : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_IDL_CTRL_TIMER_T;

//IDL_M2_SYS
typedef union {
    REG32 v;
    struct
    {
        REG32 m2_sys : 16; // [15:0]
        REG32 m1_sys : 16; // [31:16]
    } b;
} REG_CP_IDLE_IDL_M2_SYS_T;

//IDL_TC_START
typedef union {
    REG32 v;
    struct
    {
        REG32 tc_start_mod : 2; // [1:0]
        REG32 __31_2 : 30;
    } b;
} REG_CP_IDLE_IDL_TC_START_T;

//IDL_TC_END
typedef union {
    REG32 v;
    struct
    {
        REG32 tc_end_mod : 2; // [1:0]
        REG32 __3_2 : 2;
        REG32 tc_end_framc : 17; // [20:4]
        REG32 __31_21 : 11;
    } b;
} REG_CP_IDLE_IDL_TC_END_T;

//IDL_AWK_TIMER
typedef union {
    REG32 v;
    struct
    {
        REG32 wake_timer : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_IDL_AWK_TIMER_T;

//GSM_LP_PU_DONE
typedef union {
    REG32 v;
    struct
    {
        REG32 lp_pu_done : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_GSM_LP_PU_DONE_T;

//GSM_FRAME_INTEN
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_frame_irq_en : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_GSM_FRAME_INTEN_T;

//GSM_FRAME_INT_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_frame_int_sta : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_GSM_FRAME_INT_STA_T;

//LTEM1_FRAME_INTEN
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem1_frame1_irq_en : 1; // [0]
        REG32 ltem1_frame2_irq_en : 1; // [1]
        REG32 ltem1_frame3_irq_en : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_CP_IDLE_LTEM1_FRAME_INTEN_T;

//LTEM1_FRAME_INT_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem1_frame_int_sta : 3; // [2:0], write clear
        REG32 __31_3 : 29;
    } b;
} REG_CP_IDLE_LTEM1_FRAME_INT_STA_T;

//LTEM2_FRAME_INTEN
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem2_frame1_irq_en : 1; // [0]
        REG32 ltem2_frame2_irq_en : 1; // [1]
        REG32 ltem2_frame3_irq_en : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_CP_IDLE_LTEM2_FRAME_INTEN_T;

//LTEM2_FRAME_INT_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem2_frame_int_sta : 3; // [2:0], write clear
        REG32 __31_3 : 29;
    } b;
} REG_CP_IDLE_LTEM2_FRAME_INT_STA_T;

//IDL_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 idle_sys_stat : 1;         // [0], read only
        REG32 idle_gsm_timer_stat : 1;   // [1], read only
        REG32 idle_ltem1_timer_stat : 1; // [2], read only
        REG32 idle_ltem2_timer_stat : 1; // [3], read only
        REG32 h_stat : 1;                // [4], read only
        REG32 idle_nb_timer_stat : 1;    // [5], read only
        REG32 __31_6 : 26;
    } b;
} REG_CP_IDLE_IDL_STA_T;

//IDL_H_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 reserved2_1 : 1;  // [0], read only
        REG32 h_ctrl_en : 1;    // [1]
        REG32 h_auto_en : 1;    // [2]
        REG32 h_run_time : 4;   // [6:3]
        REG32 reserved1_0 : 25; // [31:7], read only
    } b;
} REG_CP_IDLE_IDL_H_CTRL_T;

//IDL_H_VAL
typedef union {
    REG32 v;
    struct
    {
        REG32 h_value : 27; // [26:0]
        REG32 __31_27 : 5;
    } b;
} REG_CP_IDLE_IDL_H_VAL_T;

//IDL_H_GSM
typedef union {
    REG32 v;
    struct
    {
        REG32 h_value : 27; // [26:0]
        REG32 __31_27 : 5;
    } b;
} REG_CP_IDLE_IDL_H_GSM_T;

//IDL_H_LTEM
typedef union {
    REG32 v;
    struct
    {
        REG32 h_value : 27; // [26:0]
        REG32 __31_27 : 5;
    } b;
} REG_CP_IDLE_IDL_H_LTEM_T;

//IDL_AWK_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 awk0_en : 1;            // [0]
        REG32 awk1_en : 1;            // [1]
        REG32 awk2_en : 1;            // [2]
        REG32 awk3_en : 1;            // [3]
        REG32 awk4_en : 1;            // [4]
        REG32 awk5_en : 1;            // [5]
        REG32 awk6_en : 1;            // [6]
        REG32 awk7_en : 1;            // [7]
        REG32 awk_osw1_en : 1;        // [8]
        REG32 awk_osw2_en : 1;        // [9]
        REG32 awk_self_en : 1;        // [10]
        REG32 gsm_lp_pu_reach_en : 1; // [11]
        REG32 nb_lp_pu_reach_en : 1;  // [12]
        REG32 __31_13 : 19;
    } b;
} REG_CP_IDLE_IDL_AWK_EN_T;

//IDL_AWK_ST
typedef union {
    REG32 v;
    struct
    {
        REG32 awk0_awk_stat : 1;        // [0], write clear
        REG32 awk1_awk_stat : 1;        // [1], write clear
        REG32 awk2_awk_stat : 1;        // [2], write clear
        REG32 awk3_awk_stat : 1;        // [3], write clear
        REG32 awk4_awk_stat : 1;        // [4], write clear
        REG32 awk5_awk_stat : 1;        // [5], write clear
        REG32 awk6_awk_stat : 1;        // [6], write clear
        REG32 awk7_awk_stat : 1;        // [7], write clear
        REG32 awk_osw1_stat : 1;        // [8], write clear
        REG32 awk_osw2_stat : 1;        // [9], write clear
        REG32 awk_self_stat : 1;        // [10], write clear
        REG32 gsm_lp_pu_reach_stat : 1; // [11], write clear
        REG32 nb_lp_pu_reach_stat : 1;  // [12], write clear
        REG32 __15_13 : 3;
        REG32 awk_up_stat : 1; // [16], write clear
        REG32 __19_17 : 3;
        REG32 idle_stat : 1; // [20], write clear
        REG32 __23_21 : 3;
        REG32 pow_sta : 1;     // [24], write clear
        REG32 thr_sta : 1;     // [25], write clear
        REG32 pow_dfe_sta : 1; // [26], read only
        REG32 __31_27 : 5;
    } b;
} REG_CP_IDLE_IDL_AWK_ST_T;

//IDL_AWK_SELF
typedef union {
    REG32 v;
    struct
    {
        REG32 wake_self : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_IDL_AWK_SELF_T;

//IDL_OSW1_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 osw1_time : 31; // [30:0]
        REG32 osw1_en : 1;    // [31]
    } b;
} REG_CP_IDLE_IDL_OSW1_EN_T;

//IDL_FN_LTEM1
typedef union {
    REG32 v;
    struct
    {
        REG32 idfn_sub_ltem : 4;  // [3:0], read only
        REG32 idfn_rad_ltem : 28; // [31:4], read only
    } b;
} REG_CP_IDLE_IDL_FN_LTEM1_T;

//IDL_FN_LTEM2
typedef union {
    REG32 v;
    struct
    {
        REG32 idfn_sub_ltem : 4;  // [3:0], read only
        REG32 idfn_rad_ltem : 28; // [31:4], read only
    } b;
} REG_CP_IDLE_IDL_FN_LTEM2_T;

//IDL_LTEM_RFL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_idle_radioframe_parameter : 21; // [20:0]
        REG32 __31_21 : 11;
    } b;
} REG_CP_IDLE_IDL_LTEM_RFL_T;

//IDL_LTEM_SFL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_idle_frame_parameter : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_IDL_LTEM_SFL_T;

//IDL_SIG_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 chip_pd_en : 1; // [0]
        REG32 pd_xtal_en : 1; // [1]
        REG32 pd_pll_en : 1;  // [2]
        REG32 idle_cg_en : 1; // [3]
        REG32 __31_4 : 28;
    } b;
} REG_CP_IDLE_IDL_SIG_EN_T;

//IDL_SIG_TIMER
typedef union {
    REG32 v;
    struct
    {
        REG32 t1 : 8; // [7:0]
        REG32 t2 : 8; // [15:8]
        REG32 t3 : 8; // [23:16]
        REG32 t4 : 8; // [31:24]
    } b;
} REG_CP_IDLE_IDL_SIG_TIMER_T;

//CP_INTEN
typedef union {
    REG32 v;
    struct
    {
        REG32 layout_irq : 1;       // [0]
        REG32 idle_h_irq : 1;       // [1]
        REG32 idle_frame_irq : 1;   // [2]
        REG32 tstamp_irq : 1;       // [3]
        REG32 osw1_irq : 1;         // [4]
        REG32 gsm_tc_start_irq : 1; // [5]
        REG32 gsm_tc_end_irq : 1;   // [6]
        REG32 gsm_pu_reach_irq : 1; // [7]
        REG32 timer_awk_irq : 1;    // [8]
        REG32 sys_wak_irq : 1;      // [9]
        REG32 nb_tc_start_irq : 1;  // [10]
        REG32 nb_tc_end_irq : 1;    // [11]
        REG32 nb_pu_reach_irq : 1;  // [12]
        REG32 target_irq : 1;       // [13]
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_CP_INTEN_T;

//CP_INTEN_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 int_en_set : 14; // [13:0], write set
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_CP_INTEN_SET_T;

//CP_INTEN_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 int_en_clr : 14; // [13:0], write clear
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_CP_INTEN_CLR_T;

//CP_INT_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 cp_int_sta : 14; // [13:0], write clear
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_CP_INT_STA_T;

//AP_INTEN
typedef union {
    REG32 v;
    struct
    {
        REG32 osw2_irq : 1;         // [0]
        REG32 gsm_pu_reach_irq : 1; // [1]
        REG32 timer_awk_irq : 1;    // [2]
        REG32 sys_wak_irq : 1;      // [3]
        REG32 nb_pu_reach_irq : 1;  // [4]
        REG32 target_irq : 1;       // [5]
        REG32 __31_6 : 26;
    } b;
} REG_CP_IDLE_AP_INTEN_T;

//AP_INTEN_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 int_en_set : 6; // [5:0], write set
        REG32 __31_6 : 26;
    } b;
} REG_CP_IDLE_AP_INTEN_SET_T;

//AP_INTEN_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 int_en_clr : 6; // [5:0], write clear
        REG32 __31_6 : 26;
    } b;
} REG_CP_IDLE_AP_INTEN_CLR_T;

//AP_INT_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 ap_int_sta : 6; // [5:0], write clear
        REG32 __31_6 : 26;
    } b;
} REG_CP_IDLE_AP_INT_STA_T;

//LTEM1_CFSR_HFN
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_hfn : 22; // [21:0]
        REG32 __31_22 : 10;
    } b;
} REG_CP_IDLE_LTEM1_CFSR_HFN_T;

//LTEM1_CFSR_FN
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_sub : 4;  // [3:0]
        REG32 ltem_cfsr_rad : 10; // [13:4]
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_LTEM1_CFSR_FN_T;

//LTEM1_CFSRS
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsrs : 24;   // [23:0]
        REG32 adjust_direct : 1; // [24]
        REG32 active_time : 1;   // [25]
        REG32 __31_26 : 6;
    } b;
} REG_CP_IDLE_LTEM1_CFSRS_T;

//LTEM1_CFSR_RDH
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_rdh : 22; // [21:0], read only
        REG32 __31_22 : 10;
    } b;
} REG_CP_IDLE_LTEM1_CFSR_RDH_T;

//LTEM1_CFSR_RDL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_rdl_sub : 4;  // [3:0], read only
        REG32 ltem_cfsr_rdl_rad : 10; // [13:4], read only
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_LTEM1_CFSR_RDL_T;

//LTEM1_FRAMC
typedef union {
    REG32 v;
    struct
    {
        REG32 lframc : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM1_FRAMC_T;

//LTEM1_FRAML
typedef union {
    REG32 v;
    struct
    {
        REG32 lframl : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM1_FRAML_T;

//LTEM1_FRAMLS
typedef union {
    REG32 v;
    struct
    {
        REG32 lframls : 16;    // [15:0]
        REG32 active_time : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_LTEM1_FRAMLS_T;

//LTEM1_CFSR_TPH
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_tph : 22; // [21:0]
        REG32 __31_22 : 10;
    } b;
} REG_CP_IDLE_LTEM1_CFSR_TPH_T;

//LTEM1_CFSR_TPL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_tpl : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_LTEM1_CFSR_TPL_T;

//LTEM1_FRAMC_TP
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_framc_tp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM1_FRAMC_TP_T;

//LTEM2_CFSR_HFN
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_hfn : 22; // [21:0]
        REG32 __31_22 : 10;
    } b;
} REG_CP_IDLE_LTEM2_CFSR_HFN_T;

//LTEM2_CFSR_FN
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_sub : 4;  // [3:0]
        REG32 ltem_cfsr_rad : 10; // [13:4]
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_LTEM2_CFSR_FN_T;

//LTEM2_CFSRS
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsrs : 24;   // [23:0]
        REG32 adjust_direct : 1; // [24]
        REG32 active_time : 1;   // [25]
        REG32 __31_26 : 6;
    } b;
} REG_CP_IDLE_LTEM2_CFSRS_T;

//LTEM2_CFSR_RDH
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_rdh : 22; // [21:0], read only
        REG32 __31_22 : 10;
    } b;
} REG_CP_IDLE_LTEM2_CFSR_RDH_T;

//LTEM2_CFSR_RDL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_rdl_sub : 4;  // [3:0], read only
        REG32 ltem_cfsr_rdl_rad : 10; // [13:4], read only
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_LTEM2_CFSR_RDL_T;

//LTEM2_FRAMC
typedef union {
    REG32 v;
    struct
    {
        REG32 lframc : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM2_FRAMC_T;

//LTEM2_FRAML
typedef union {
    REG32 v;
    struct
    {
        REG32 lframl : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM2_FRAML_T;

//LTEM2_FRAMLS
typedef union {
    REG32 v;
    struct
    {
        REG32 lframls : 16;    // [15:0]
        REG32 active_time : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_LTEM2_FRAMLS_T;

//LTEM2_CFSR_TPH
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_tph : 22; // [21:0]
        REG32 __31_22 : 10;
    } b;
} REG_CP_IDLE_LTEM2_CFSR_TPH_T;

//LTEM2_CFSR_TPL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_cfsr_tpl : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_LTEM2_CFSR_TPL_T;

//LTEM2_FRAMC_TP
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_framc_tp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM2_FRAMC_TP_T;

//GSM_CFSR
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_cfsr_gsm_cfsr : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_CP_IDLE_GSM_CFSR_T;

//GSM_CFSRS
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_cfsrs_gsm_cfsrs : 24; // [23:0]
        REG32 adjust_direct : 1;        // [24]
        REG32 __31_25 : 7;
    } b;
} REG_CP_IDLE_GSM_CFSRS_T;

//GSM_CFSRO
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_cfsr_overflow : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_CP_IDLE_GSM_CFSRO_T;

//LTEM1_FHL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_fhl : 22; // [21:0], read only
        REG32 __31_22 : 10;
    } b;
} REG_CP_IDLE_LTEM1_FHL_T;

//LTEM1_FLL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_fll : 14; // [13:0], read only
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_LTEM1_FLL_T;

//LTEM1_FCL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_fcl : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM1_FCL_T;

//LTEM2_FHL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_fhl : 22; // [21:0], read only
        REG32 __31_22 : 10;
    } b;
} REG_CP_IDLE_LTEM2_FHL_T;

//LTEM2_FLL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_fll : 14; // [13:0], read only
        REG32 __31_14 : 18;
    } b;
} REG_CP_IDLE_LTEM2_FLL_T;

//LTEM2_FCL
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_fcl : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM2_FCL_T;

//GSM_FL
typedef union {
    REG32 v;
    struct
    {
        REG32 fl : 24; // [23:0], read only
        REG32 __31_24 : 8;
    } b;
} REG_CP_IDLE_GSM_FL_T;

//GSM_FCL
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_fcl_gsm_fcl : 17; // [16:0], read only
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_GSM_FCL_T;

//TPCTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 inner_ctrl : 1;   // [0]
        REG32 reserved3_2 : 3;  // [3:1], read only
        REG32 inner_confg : 2;  // [5:4]
        REG32 reserved2_1 : 2;  // [7:6], read only
        REG32 mod_sel : 3;      // [10:8]
        REG32 reserved1_0 : 21; // [31:11], read only
    } b;
} REG_CP_IDLE_TPCTRL_T;

//LAYOUTCTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1;       // [0]
        REG32 timer_select : 1; // [1]
        REG32 reserved2_1 : 6;  // [7:2], read only
        REG32 chip_count : 15;  // [22:8]
        REG32 reserved1_0 : 9;  // [31:23], read only
    } b;
} REG_CP_IDLE_LAYOUTCTRL_T;

//LTEM1_FINT_DLY1
typedef union {
    REG32 v;
    struct
    {
        REG32 delay_time : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM1_FINT_DLY1_T;

//LTEM1_FINT_DLY2
typedef union {
    REG32 v;
    struct
    {
        REG32 delay_time : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM1_FINT_DLY2_T;

//LTEM2_FINT_DLY1
typedef union {
    REG32 v;
    struct
    {
        REG32 delay_time : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM2_FINT_DLY1_T;

//LTEM2_FINT_DLY2
typedef union {
    REG32 v;
    struct
    {
        REG32 delay_time : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM2_FINT_DLY2_T;

//FINT_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 lte_m1_fint_enable : 10; // [9:0]
        REG32 reserved2_1 : 2;         // [11:10], read only
        REG32 lte_m2_fint_enable : 10; // [21:12]
        REG32 reserved1_0 : 10;        // [31:22], read only
    } b;
} REG_CP_IDLE_FINT_EN_T;

//TIMER_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 lte_m1_timer_enable : 1; // [0]
        REG32 lte_m2_timer_enable : 1; // [1]
        REG32 gsm_timer_enable : 1;    // [2]
        REG32 ltem_timer_enable : 1;   // [3]
        REG32 nb_timer_enable : 1;     // [4]
        REG32 __31_5 : 27;
    } b;
} REG_CP_IDLE_TIMER_EN_T;

//IDLE_FRAME_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 lte_m1_frame_state : 1; // [0], write clear
        REG32 lte_m2_frame_state : 1; // [1], write clear
        REG32 gsm_frame_state : 1;    // [2], write clear
        REG32 lte_m_frame_state : 1;  // [3], write clear
        REG32 nb_frame_state : 1;     // [4], write clear
        REG32 __31_5 : 27;
    } b;
} REG_CP_IDLE_IDLE_FRAME_STA_T;

//IDLE_FRAME_LTEM1
typedef union {
    REG32 v;
    struct
    {
        REG32 frame_cfsr : 22; // [21:0]
        REG32 reserved2_1 : 2; // [23:22], read only
        REG32 frame_conf : 1;  // [24]
        REG32 reserved1_0 : 7; // [31:25], read only
    } b;
} REG_CP_IDLE_IDLE_FRAME_LTEM1_T;

//IDLE_FRAME_LTEM2
typedef union {
    REG32 v;
    struct
    {
        REG32 frame_cfsr : 22; // [21:0]
        REG32 reserved2_1 : 2; // [23:22], read only
        REG32 frame_conf : 1;  // [24]
        REG32 reserved1_0 : 7; // [31:25], read only
    } b;
} REG_CP_IDLE_IDLE_FRAME_LTEM2_T;

//IDLE_FRAME_GSM
typedef union {
    REG32 v;
    struct
    {
        REG32 frame_cfsr : 24; // [23:0]
        REG32 frame_conf : 1;  // [24]
        REG32 __31_25 : 7;
    } b;
} REG_CP_IDLE_IDLE_FRAME_GSM_T;

//IDLE_FRAME_LTE_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 frame_ref_lte_conf : 1; // [0]
        REG32 resrved : 31;           // [31:1], read only
    } b;
} REG_CP_IDLE_IDLE_FRAME_LTE_CONF_T;

//LTEM_REF_FCL
typedef union {
    REG32 v;
    struct
    {
        REG32 ref_ltem_fcl : 15; // [14:0], read only
        REG32 __31_15 : 17;
    } b;
} REG_CP_IDLE_LTEM_REF_FCL_T;

//LTEM_REF_FC
typedef union {
    REG32 v;
    struct
    {
        REG32 ltem_ref_fc_ltem_ref_fc : 15; // [14:0], read only
        REG32 __31_15 : 17;
    } b;
} REG_CP_IDLE_LTEM_REF_FC_T;

//GSM_FRAML
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_framl : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_GSM_FRAML_T;

//IDL_OSW2_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 osw2_time : 31; // [30:0]
        REG32 osw2_en : 1;    // [31]
    } b;
} REG_CP_IDLE_IDL_OSW2_EN_T;

//IDLE_FRAMC_GSM
typedef union {
    REG32 v;
    struct
    {
        REG32 framc_cfsr : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_IDLE_FRAMC_GSM_T;

//LTEM1_FINT_DLY3
typedef union {
    REG32 v;
    struct
    {
        REG32 delay_time : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM1_FINT_DLY3_T;

//LTEM2_FINT_DLY3
typedef union {
    REG32 v;
    struct
    {
        REG32 delay_time : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_LTEM2_FINT_DLY3_T;

//IDLE_TIME_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 time_sel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_IDLE_TIME_SEL_T;

//IDL_H_GSM_LP
typedef union {
    REG32 v;
    struct
    {
        REG32 h_value : 27; // [26:0]
        REG32 __31_27 : 5;
    } b;
} REG_CP_IDLE_IDL_H_GSM_LP_T;

//IDL_H_LTEM_LP
typedef union {
    REG32 v;
    struct
    {
        REG32 h_value : 27; // [26:0]
        REG32 __31_27 : 5;
    } b;
} REG_CP_IDLE_IDL_H_LTEM_LP_T;

//IDL_TC_START_NB
typedef union {
    REG32 v;
    struct
    {
        REG32 tc_start_mod : 2; // [1:0]
        REG32 __31_2 : 30;
    } b;
} REG_CP_IDLE_IDL_TC_START_NB_T;

//IDL_TC_END_NB
typedef union {
    REG32 v;
    struct
    {
        REG32 tc_end_mod : 2; // [1:0]
        REG32 __3_2 : 2;
        REG32 tc_end_framc : 17; // [20:4]
        REG32 __31_21 : 11;
    } b;
} REG_CP_IDLE_IDL_TC_END_NB_T;

//NB_LP_PU_DONE
typedef union {
    REG32 v;
    struct
    {
        REG32 lp_pu_done : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_NB_LP_PU_DONE_T;

//IDL_H_NB
typedef union {
    REG32 v;
    struct
    {
        REG32 h_value : 27; // [26:0]
        REG32 __31_27 : 5;
    } b;
} REG_CP_IDLE_IDL_H_NB_T;

//IDL_H_NB_LP
typedef union {
    REG32 v;
    struct
    {
        REG32 h_value : 27; // [26:0]
        REG32 __31_27 : 5;
    } b;
} REG_CP_IDLE_IDL_H_NB_LP_T;

//NB_FRAME_INTEN
typedef union {
    REG32 v;
    struct
    {
        REG32 nb_frame_irq_en : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_NB_FRAME_INTEN_T;

//NB_FRAME_INT_STA
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_frame_int_sta : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_NB_FRAME_INT_STA_T;

//NB_CFSR
typedef union {
    REG32 v;
    struct
    {
        REG32 gsm_cfsr : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_CP_IDLE_NB_CFSR_T;

//NB_FRAML
typedef union {
    REG32 v;
    struct
    {
        REG32 nb_framl : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_NB_FRAML_T;

//NB_CFSRS
typedef union {
    REG32 v;
    struct
    {
        REG32 nb_cfsrs_nb_cfsrs : 24; // [23:0]
        REG32 adjust_direct : 1;      // [24]
        REG32 __31_25 : 7;
    } b;
} REG_CP_IDLE_NB_CFSRS_T;

//NB_CFSRO
typedef union {
    REG32 v;
    struct
    {
        REG32 nb_cfsr_overflow : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_CP_IDLE_NB_CFSRO_T;

//NB_FL
typedef union {
    REG32 v;
    struct
    {
        REG32 fl : 24; // [23:0], read only
        REG32 __31_24 : 8;
    } b;
} REG_CP_IDLE_NB_FL_T;

//NB_FCL
typedef union {
    REG32 v;
    struct
    {
        REG32 nb_fcl_nb_fcl : 17; // [16:0], read only
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_NB_FCL_T;

//IDLE_FRAME_NB
typedef union {
    REG32 v;
    struct
    {
        REG32 frame_cfsr : 24; // [23:0]
        REG32 frame_conf : 1;  // [24]
        REG32 __31_25 : 7;
    } b;
} REG_CP_IDLE_IDLE_FRAME_NB_T;

//IDLE_FRAMC_NB
typedef union {
    REG32 v;
    struct
    {
        REG32 framc_cfsr : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_CP_IDLE_IDLE_FRAMC_NB_T;

//IDL_AWK_EN_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 awk_en_set : 13; // [12:0], write set
        REG32 __31_13 : 19;
    } b;
} REG_CP_IDLE_IDL_AWK_EN_SET_T;

//IDL_AWK_EN_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 awk_en_clear : 13; // [12:0], write clear
        REG32 __31_13 : 19;
    } b;
} REG_CP_IDLE_IDL_AWK_EN_CLR_T;

//GSM_FRAMC
typedef union {
    REG32 v;
    struct
    {
        REG32 framc : 17; // [16:0], read only
        REG32 __19_17 : 3;
        REG32 rd_enable : 1; // [20]
        REG32 __31_21 : 11;
    } b;
} REG_CP_IDLE_GSM_FRAMC_T;

//NB_FRAMC
typedef union {
    REG32 v;
    struct
    {
        REG32 framc : 17; // [16:0], read only
        REG32 __19_17 : 3;
        REG32 rd_enable : 1; // [20]
        REG32 __31_21 : 11;
    } b;
} REG_CP_IDLE_NB_FRAMC_T;

//ELIMINAT_JITTER
typedef union {
    REG32 v;
    struct
    {
        REG32 elimiate_en : 8;   // [7:0]
        REG32 eliminat_time : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_CP_IDLE_ELIMINAT_JITTER_T;

//GSM_EN_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 select : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_GSM_EN_SEL_T;

//NB_EN_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 select : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_NB_EN_SEL_T;

//PD_PLL_SW
typedef union {
    REG32 v;
    struct
    {
        REG32 bbpll1 : 1;   // [0]
        REG32 bbpll2 : 1;   // [1]
        REG32 apll : 1;     // [2]
        REG32 audiopll : 1; // [3]
        REG32 usbpll : 1;   // [4]
        REG32 mempll : 1;   // [5]
        REG32 dsipll : 1;   // [6]
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_PD_PLL_SW_T;

//PD_PLL_SW_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 pdpllswset : 7; // [6:0], write set
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_PD_PLL_SW_SET_T;

//PD_PLL_SW_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 pdpllswclr : 7; // [6:0], write clear
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_PD_PLL_SW_CLR_T;

//PD_PLL_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 bbpll1 : 1;   // [0]
        REG32 bbpll2 : 1;   // [1]
        REG32 apll : 1;     // [2]
        REG32 audiopll : 1; // [3]
        REG32 usbpll : 1;   // [4]
        REG32 mempll : 1;   // [5]
        REG32 dsipll : 1;   // [6]
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_PD_PLL_SEL_T;

//PD_PLL_SEL_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 pdpllselset : 7; // [6:0], write set
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_PD_PLL_SEL_SET_T;

//PD_PLL_SEL_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 pdpllselclr : 7; // [6:0], write clear
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_PD_PLL_SEL_CLR_T;

//IDLE_CG_SW
typedef union {
    REG32 v;
    struct
    {
        REG32 bbpll1 : 1;   // [0]
        REG32 bbpll2 : 1;   // [1]
        REG32 apll : 1;     // [2]
        REG32 audiopll : 1; // [3]
        REG32 usbpll : 1;   // [4]
        REG32 mempll : 1;   // [5]
        REG32 dsipll : 1;   // [6]
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_IDLE_CG_SW_T;

//IDLE_CG_SW_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 idlecgswset : 7; // [6:0], write set
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_IDLE_CG_SW_SET_T;

//IDLE_CG_SW_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 idlecgswclr : 7; // [6:0], write clear
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_IDLE_CG_SW_CLR_T;

//IDLE_CG_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 bbpll1 : 1;   // [0]
        REG32 bbpll2 : 1;   // [1]
        REG32 apll : 1;     // [2]
        REG32 audiopll : 1; // [3]
        REG32 usbpll : 1;   // [4]
        REG32 mempll : 1;   // [5]
        REG32 dsipll : 1;   // [6]
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_IDLE_CG_SEL_T;

//IDLE_CG_SEL_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 idlecgselset : 7; // [6:0], write set
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_IDLE_CG_SEL_SET_T;

//IDLE_CG_SEL_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 idlecgselclr : 7; // [6:0], write clear
        REG32 __31_7 : 25;
    } b;
} REG_CP_IDLE_IDLE_CG_SEL_CLR_T;

//RF_IDLE_ENABLE_SW
typedef union {
    REG32 v;
    struct
    {
        REG32 rfidleenablesw : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_RF_IDLE_ENABLE_SW_T;

//RF_IDLE_ENABLE_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 rfidleenablesel : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_RF_IDLE_ENABLE_SEL_T;

//MEM_EMA_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 rftpd_rmea : 1; // [0]
        REG32 rftpd_rma : 4;  // [4:1]
        REG32 rftpd_rmeb : 1; // [5]
        REG32 rftpd_rmb : 4;  // [9:6]
        REG32 __31_10 : 22;
    } b;
} REG_CP_IDLE_MEM_EMA_CFG_T;

//UART_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 enable_clk_uart : 1; // [0]
        REG32 rst_ctrl_uart : 1;   // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_IDLE_UART_CTRL_T;

//DDR_LATCH
typedef union {
    REG32 v;
    struct
    {
        REG32 lpddr_latch : 1; // [0]
        REG32 psram_latch : 1; // [1]
        REG32 __31_2 : 30;
    } b;
} REG_CP_IDLE_DDR_LATCH_T;

//PAD_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_uart_1_rxd_wpus : 1;      // [0]
        REG32 pad_uart_1_rxd_se : 1;        // [1]
        REG32 pad_uart_1_rxd_pull_up : 1;   // [2]
        REG32 pad_uart_1_rxd_pull_dowe : 1; // [3]
        REG32 pad_uart_1_rxd_drv : 2;       // [5:4]
        REG32 pad_uart_1_rxd_pull_frc : 1;  // [6]
        REG32 pad_chip_pd_wpus : 1;         // [7]
        REG32 pad_chip_pd_se : 1;           // [8]
        REG32 pad_chip_pd_pull_up : 1;      // [9]
        REG32 pad_chip_pd_pull_dowe : 1;    // [10]
        REG32 pad_chip_pd_drv : 2;          // [12:11]
        REG32 pad_chip_pd_pull_frc : 1;     // [13]
        REG32 pad_chip_pd_out_frc : 1;      // [14]
        REG32 pad_chip_pd_out : 1;          // [15]
        REG32 pad_gpio_6_wpus : 1;          // [16]
        REG32 pad_gpio_6_se : 1;            // [17]
        REG32 pad_gpio_6_pull_up : 1;       // [18]
        REG32 pad_gpio_6_pull_dowe : 1;     // [19]
        REG32 pad_gpio_6_drv : 2;           // [21:20]
        REG32 pad_gpio_6_pull_frc : 1;      // [22]
        REG32 pad_osc_32k_wpus : 1;         // [23]
        REG32 pad_osc_32k_se : 1;           // [24]
        REG32 pad_osc_32k_drv : 2;          // [26:25]
        REG32 pad_misc_idle_wpdi : 1;       // [27]
        REG32 __31_28 : 4;
    } b;
} REG_CP_IDLE_PAD_CTRL_T;

//PAD_CTRL_UART_TXD
typedef union {
    REG32 v;
    struct
    {
        REG32 pad_uart_1_txd_wpus : 1;      // [0]
        REG32 pad_uart_1_txd_se : 1;        // [1]
        REG32 pad_uart_1_txd_pull_up : 1;   // [2]
        REG32 pad_uart_1_txd_pull_dowe : 1; // [3]
        REG32 pad_uart_1_txd_drv : 2;       // [5:4]
        REG32 pad_uart_1_txd_pull_frc : 1;  // [6]
        REG32 pad_uart_1_txd_out_frc : 1;   // [7]
        REG32 pad_uart_1_txd_out : 1;       // [8]
        REG32 __31_9 : 23;
    } b;
} REG_CP_IDLE_PAD_CTRL_UART_TXD_T;

//MON_SEL
typedef union {
    REG32 v;
    struct
    {
        REG32 mon0_sel : 2;  // [1:0]
        REG32 mon1_sel : 2;  // [3:2]
        REG32 mon2_sel : 2;  // [5:4]
        REG32 mon3_sel : 2;  // [7:6]
        REG32 mon4_sel : 2;  // [9:8]
        REG32 mon5_sel : 2;  // [11:10]
        REG32 mon6_sel : 2;  // [13:12]
        REG32 mon7_sel : 2;  // [15:14]
        REG32 mon8_sel : 2;  // [17:16]
        REG32 mon9_sel : 2;  // [19:18]
        REG32 mon10_sel : 2; // [21:20]
        REG32 mon11_sel : 2; // [23:22]
        REG32 mon12_sel : 2; // [25:24]
        REG32 mon13_sel : 2; // [27:26]
        REG32 mon14_sel : 2; // [29:28]
        REG32 mon15_sel : 2; // [31:30]
    } b;
} REG_CP_IDLE_MON_SEL_T;

//TARGET_TIMER_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 disable_target_timer : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_TARGET_TIMER_EN_T;

//TARGET_TIMER_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 timer_stat_122m : 1; // [0], read only
        REG32 timer_stat_32k : 1;  // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_CP_IDLE_TARGET_TIMER_STAT_T;

//SLOW_SYS_CLK_SEL_HWEN
typedef union {
    REG32 v;
    struct
    {
        REG32 hwen : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_SLOW_SYS_CLK_SEL_HWEN_T;

//SLOW_CLK_SEL_HWEN
typedef union {
    REG32 v;
    struct
    {
        REG32 hwen : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_CP_IDLE_SLOW_CLK_SEL_HWEN_T;

//SLEEP_PROT_TIME
typedef union {
    REG32 v;
    struct
    {
        REG32 prot_time : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_CP_IDLE_SLEEP_PROT_TIME_T;

#endif
