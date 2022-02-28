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

#ifndef _RDA2720M_ADC_H_
#define _RDA2720M_ADC_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_adc'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_ADC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_ADC_BASE 0x50308400

typedef volatile struct
{
    REG32 adc_version;                  //0x00000000
    REG32 adc_cfg_ctrl;                 //0x00000004
    REG32 adc_sw_ch_cfg;                //0x00000008
    REG32 adc_fast_hw_ch0_cfg;          //0x0000000C
    REG32 adc_fast_hw_ch1_cfg;          //0x00000010
    REG32 adc_fast_hw_ch2_cfg;          //0x00000014
    REG32 adc_fast_hw_ch3_cfg;          //0x00000018
    REG32 adc_fast_hw_ch4_cfg;          //0x0000001C
    REG32 adc_fast_hw_ch5_cfg;          //0x00000020
    REG32 adc_fast_hw_ch6_cfg;          //0x00000024
    REG32 adc_fast_hw_ch7_cfg;          //0x00000028
    REG32 adc_slow_hw_ch0_cfg;          //0x0000002C
    REG32 adc_slow_hw_ch1_cfg;          //0x00000030
    REG32 adc_slow_hw_ch2_cfg;          //0x00000034
    REG32 adc_slow_hw_ch3_cfg;          //0x00000038
    REG32 adc_slow_hw_ch4_cfg;          //0x0000003C
    REG32 adc_slow_hw_ch5_cfg;          //0x00000040
    REG32 adc_slow_hw_ch6_cfg;          //0x00000044
    REG32 adc_slow_hw_ch7_cfg;          //0x00000048
    REG32 adc_hw_ch_delay;              //0x0000004C
    REG32 adc_dat;                      //0x00000050
    REG32 adc_cfg_int_en;               //0x00000054
    REG32 adc_cfg_int_clr;              //0x00000058
    REG32 adc_cfg_int_sts;              //0x0000005C
    REG32 adc_cfg_int_raw;              //0x00000060
    REG32 adc_debug;                    //0x00000064
    REG32 adc_fast_hw_timer_en;         //0x00000068
    REG32 adc_fast_hw_timer_div;        //0x0000006C
    REG32 adc_fast_hw_ch0_timer_thresh; //0x00000070
    REG32 adc_fast_hw_ch1_timer_thresh; //0x00000074
    REG32 adc_fast_hw_ch2_timer_thresh; //0x00000078
    REG32 adc_fast_hw_ch3_timer_thresh; //0x0000007C
    REG32 adc_fast_hw_ch4_timer_thresh; //0x00000080
    REG32 adc_fast_hw_ch5_timer_thresh; //0x00000084
    REG32 adc_fast_hw_ch6_timer_thresh; //0x00000088
    REG32 adc_fast_hw_ch7_timer_thresh; //0x0000008C
    REG32 adc_fast_hw_ch0_dat;          //0x00000090
    REG32 adc_fast_hw_ch1_dat;          //0x00000094
    REG32 adc_fast_hw_ch2_dat;          //0x00000098
    REG32 adc_fast_hw_ch3_dat;          //0x0000009C
    REG32 adc_fast_hw_ch4_dat;          //0x000000A0
    REG32 adc_fast_hw_ch5_dat;          //0x000000A4
    REG32 adc_fast_hw_ch6_dat;          //0x000000A8
    REG32 adc_fast_hw_ch7_dat;          //0x000000AC
    REG32 auxad_ctl0;                   //0x000000B0
    REG32 auxad_ctl1;                   //0x000000B4
} HWP_RDA2720M_ADC_T;

#define hwp_rda2720mAdc ((HWP_RDA2720M_ADC_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_ADC_BASE))

//ADC_VERSION
typedef union {
    REG32 v;
    struct
    {
        REG32 auxadc_version : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_VERSION_T;

//ADC_CFG_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_en : 1;    // [0]
        REG32 sw_ch_run : 1; // [1]
        REG32 adc_12b : 1;   // [2]
        REG32 __3_3 : 1;
        REG32 sw_ch_run_num : 4;    // [7:4]
        REG32 rg_auxad_average : 3; // [10:8]
        REG32 __11_11 : 1;
        REG32 adc_offset_cal_en : 1; // [12]
        REG32 __31_13 : 19;
    } b;
} REG_RDA2720M_ADC_ADC_CFG_CTRL_T;

//ADC_SW_CH_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 adc_slow : 1; // [6]
        REG32 __8_7 : 2;
        REG32 adc_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SW_CH_CFG_T;

//ADC_FAST_HW_CH0_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 frq_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 frq_slow : 1;     // [6]
        REG32 frq_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 frq_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH0_CFG_T;

//ADC_FAST_HW_CH1_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 frq_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 frq_slow : 1;     // [6]
        REG32 frq_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 frq_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH1_CFG_T;

//ADC_FAST_HW_CH2_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 frq_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 frq_slow : 1;     // [6]
        REG32 frq_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 frq_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH2_CFG_T;

//ADC_FAST_HW_CH3_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 frq_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 frq_slow : 1;     // [6]
        REG32 frq_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 frq_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH3_CFG_T;

//ADC_FAST_HW_CH4_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 frq_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 frq_slow : 1;     // [6]
        REG32 frq_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 frq_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH4_CFG_T;

//ADC_FAST_HW_CH5_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 frq_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 frq_slow : 1;     // [6]
        REG32 frq_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 frq_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH5_CFG_T;

//ADC_FAST_HW_CH6_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 frq_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 frq_slow : 1;     // [6]
        REG32 frq_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 frq_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH6_CFG_T;

//ADC_FAST_HW_CH7_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 frq_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 frq_slow : 1;     // [6]
        REG32 frq_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 frq_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH7_CFG_T;

//ADC_SLOW_HW_CH0_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 req_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 req_slow : 1;     // [6]
        REG32 req_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 req_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SLOW_HW_CH0_CFG_T;

//ADC_SLOW_HW_CH1_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 req_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 req_slow : 1;     // [6]
        REG32 req_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 req_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SLOW_HW_CH1_CFG_T;

//ADC_SLOW_HW_CH2_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 req_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 req_slow : 1;     // [6]
        REG32 req_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 req_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SLOW_HW_CH2_CFG_T;

//ADC_SLOW_HW_CH3_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 req_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 req_slow : 1;     // [6]
        REG32 req_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 req_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SLOW_HW_CH3_CFG_T;

//ADC_SLOW_HW_CH4_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 req_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 req_slow : 1;     // [6]
        REG32 req_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 req_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SLOW_HW_CH4_CFG_T;

//ADC_SLOW_HW_CH5_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 req_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 req_slow : 1;     // [6]
        REG32 req_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 req_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SLOW_HW_CH5_CFG_T;

//ADC_SLOW_HW_CH6_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 req_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 req_slow : 1;     // [6]
        REG32 req_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 req_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SLOW_HW_CH6_CFG_T;

//ADC_SLOW_HW_CH7_CFG
typedef union {
    REG32 v;
    struct
    {
        REG32 req_cs : 5; // [4:0]
        REG32 __5_5 : 1;
        REG32 req_slow : 1;     // [6]
        REG32 req_delay_en : 1; // [7]
        REG32 __8_8 : 1;
        REG32 req_scale : 2; // [10:9]
        REG32 __31_11 : 21;
    } b;
} REG_RDA2720M_ADC_ADC_SLOW_HW_CH7_CFG_T;

//ADC_HW_CH_DELAY
typedef union {
    REG32 v;
    struct
    {
        REG32 hw_ch_delay : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_ADC_ADC_HW_CH_DELAY_T;

//ADC_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_DAT_T;

//ADC_CFG_INT_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_irq_en : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_ADC_ADC_CFG_INT_EN_T;

//ADC_CFG_INT_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_irq_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_ADC_ADC_CFG_INT_CLR_T;

//ADC_CFG_INT_STS
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_irq_sts : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_ADC_ADC_CFG_INT_STS_T;

//ADC_CFG_INT_RAW
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_irq_raw : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_RDA2720M_ADC_ADC_CFG_INT_RAW_T;

//ADC_DEBUG
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_dbg_cnt : 8;   // [7:0], read only
        REG32 adc_dbg_state : 3; // [10:8], read only
        REG32 adc_dbg_ch : 5;    // [15:11], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_DEBUG_T;

//ADC_FAST_HW_TIMER_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch0_timer_en : 1; // [0]
        REG32 adc_fast_hw_ch1_timer_en : 1; // [1]
        REG32 adc_fast_hw_ch2_timer_en : 1; // [2]
        REG32 adc_fast_hw_ch3_timer_en : 1; // [3]
        REG32 adc_fast_hw_ch4_timer_en : 1; // [4]
        REG32 adc_fast_hw_ch5_timer_en : 1; // [5]
        REG32 adc_fast_hw_ch6_timer_en : 1; // [6]
        REG32 adc_fast_hw_ch7_timer_en : 1; // [7]
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_TIMER_EN_T;

//ADC_FAST_HW_TIMER_DIV
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_timer_div : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_TIMER_DIV_T;

//ADC_FAST_HW_CH0_TIMER_THRESH
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch0_timer_thresh : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH0_TIMER_THRESH_T;

//ADC_FAST_HW_CH1_TIMER_THRESH
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch1_timer_thresh : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH1_TIMER_THRESH_T;

//ADC_FAST_HW_CH2_TIMER_THRESH
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch2_timer_thresh : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH2_TIMER_THRESH_T;

//ADC_FAST_HW_CH3_TIMER_THRESH
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch3_timer_thresh : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH3_TIMER_THRESH_T;

//ADC_FAST_HW_CH4_TIMER_THRESH
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch4_timer_thresh : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH4_TIMER_THRESH_T;

//ADC_FAST_HW_CH5_TIMER_THRESH
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch5_timer_thresh : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH5_TIMER_THRESH_T;

//ADC_FAST_HW_CH6_TIMER_THRESH
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch6_timer_thresh : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH6_TIMER_THRESH_T;

//ADC_FAST_HW_CH7_TIMER_THRESH
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch7_timer_thresh : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH7_TIMER_THRESH_T;

//ADC_FAST_HW_CH0_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch0_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH0_DAT_T;

//ADC_FAST_HW_CH1_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch1_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH1_DAT_T;

//ADC_FAST_HW_CH2_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch2_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH2_DAT_T;

//ADC_FAST_HW_CH3_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch3_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH3_DAT_T;

//ADC_FAST_HW_CH4_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch4_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH4_DAT_T;

//ADC_FAST_HW_CH5_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch5_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH5_DAT_T;

//ADC_FAST_HW_CH6_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch6_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH6_DAT_T;

//ADC_FAST_HW_CH7_DAT
typedef union {
    REG32 v;
    struct
    {
        REG32 adc_fast_hw_ch7_dat : 12; // [11:0], read only
        REG32 __31_12 : 20;
    } b;
} REG_RDA2720M_ADC_ADC_FAST_HW_CH7_DAT_T;

//AUXAD_CTL0
typedef union {
    REG32 v;
    struct
    {
        REG32 rg_auxad_currentsen_en : 1; // [0]
        REG32 __3_1 : 3;
        REG32 rg_auxad_thm_cal : 1; // [4]
        REG32 rg_auxad_ref_sel : 1; // [5]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_ADC_AUXAD_CTL0_T;

//AUXAD_CTL1
typedef union {
    REG32 v;
    struct
    {
        REG32 rg_adc_fast_hw_ch0_dvld : 1; // [0], read only
        REG32 rg_adc_fast_hw_ch1_dvld : 1; // [1], read only
        REG32 rg_adc_fast_hw_ch2_dvld : 1; // [2], read only
        REG32 rg_adc_fast_hw_ch3_dvld : 1; // [3], read only
        REG32 rg_adc_fast_hw_ch4_dvld : 1; // [4], read only
        REG32 rg_adc_fast_hw_ch5_dvld : 1; // [5], read only
        REG32 rg_adc_fast_hw_ch6_dvld : 1; // [6], read only
        REG32 rg_adc_fast_hw_ch7_dvld : 1; // [7], read only
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_ADC_AUXAD_CTL1_T;

#endif
