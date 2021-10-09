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

#ifndef _RDA2720M_RTC_H_
#define _RDA2720M_RTC_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_rtc'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_RTC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_RTC_BASE 0x50308200

typedef volatile struct
{
    REG32 rtc_sec_cnt_value;  //0x00000000
    REG32 rtc_min_cnt_value;  //0x00000004
    REG32 rtc_hrs_cnt_value;  //0x00000008
    REG32 rtc_day_cnt_value;  //0x0000000C
    REG32 rtc_sec_cnt_upd;    //0x00000010
    REG32 rtc_min_cnt_upd;    //0x00000014
    REG32 rtc_hrs_cnt_upd;    //0x00000018
    REG32 rtc_day_cnt_upd;    //0x0000001C
    REG32 rtc_sec_alm_upd;    //0x00000020
    REG32 rtc_min_alm_upd;    //0x00000024
    REG32 rtc_hrs_alm_upd;    //0x00000028
    REG32 rtc_day_alm_upd;    //0x0000002C
    REG32 rtc_int_en;         //0x00000030
    REG32 rtc_int_raw_sts;    //0x00000034
    REG32 rtc_int_clr;        //0x00000038
    REG32 rtc_int_mask_sts;   //0x0000003C
    REG32 rtc_sec_alm_value;  //0x00000040
    REG32 rtc_min_alm_value;  //0x00000044
    REG32 rtc_hrs_alm_value;  //0x00000048
    REG32 rtc_day_alm_value;  //0x0000004C
    REG32 rtc_spg_value;      //0x00000050
    REG32 rtc_spg_upd;        //0x00000054
    REG32 rtc_pwr_flag_ctrl;  //0x00000058
    REG32 rtc_pwr_flag_sts;   //0x0000005C
    REG32 rtc_sec_auxalm_upd; //0x00000060
    REG32 rtc_min_auxalm_upd; //0x00000064
    REG32 rtc_hrs_auxalm_upd; //0x00000068
    REG32 rtc_day_auxalm_upd; //0x0000006C
    REG32 rtc_sec_cnt_raw;    //0x00000070
    REG32 rtc_min_cnt_raw;    //0x00000074
    REG32 rtc_hrs_cnt_raw;    //0x00000078
    REG32 rtc_day_cnt_raw;    //0x0000007C
} HWP_RDA2720M_RTC_T;

#define hwp_rda2720mRtc ((HWP_RDA2720M_RTC_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_RTC_BASE))

//RTC_SEC_CNT_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_cnt_value : 6; // [5:0], read only
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_SEC_CNT_VALUE_T;

//RTC_MIN_CNT_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_min_cnt_value : 6; // [5:0], read only
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_MIN_CNT_VALUE_T;

//RTC_HRS_CNT_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_hrs_cnt_value : 5; // [4:0], read only
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_RTC_RTC_HRS_CNT_VALUE_T;

//RTC_DAY_CNT_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_day_cnt_value : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_DAY_CNT_VALUE_T;

//RTC_SEC_CNT_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_cnt_upd : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_SEC_CNT_UPD_T;

//RTC_MIN_CNT_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_min_cnt_upd : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_MIN_CNT_UPD_T;

//RTC_HRS_CNT_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_hrs_cnt_upd : 5; // [4:0]
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_RTC_RTC_HRS_CNT_UPD_T;

//RTC_DAY_CNT_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_day_cnt_upd : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_DAY_CNT_UPD_T;

//RTC_SEC_ALM_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_alm_upd : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_SEC_ALM_UPD_T;

//RTC_MIN_ALM_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_min_alm_upd : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_MIN_ALM_UPD_T;

//RTC_HRS_ALM_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_hrs_alm_upd : 5; // [4:0]
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_RTC_RTC_HRS_ALM_UPD_T;

//RTC_DAY_ALM_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_day_alm_upd : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_DAY_ALM_UPD_T;

//RTC_INT_EN
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_int_en : 1;         // [0]
        REG32 rtc_min_int_en : 1;         // [1]
        REG32 rtc_hrs_int_en : 1;         // [2]
        REG32 rtc_day_int_en : 1;         // [3]
        REG32 rtc_alm_int_en : 1;         // [4]
        REG32 rtc_hrs_format_sel : 1;     // [5]
        REG32 rtc_auxalm_int_en : 1;      // [6]
        REG32 rtc_spg_upd_int_en : 1;     // [7]
        REG32 rtc_sec_cnt_upd_int_en : 1; // [8]
        REG32 rtc_min_cnt_upd_int_en : 1; // [9]
        REG32 rtc_hrs_cnt_upd_int_en : 1; // [10]
        REG32 rtc_day_cnt_upd_int_en : 1; // [11]
        REG32 rtc_sec_alm_upd_int_en : 1; // [12]
        REG32 rtc_min_alm_upd_int_en : 1; // [13]
        REG32 rtc_hrs_alm_upd_int_en : 1; // [14]
        REG32 rtc_day_alm_upd_int_en : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_INT_EN_T;

//RTC_INT_RAW_STS
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_int_raw_sts : 1;         // [0], read only
        REG32 rtc_min_int_raw_sts : 1;         // [1], read only
        REG32 rtc_hrs_int_raw_sts : 1;         // [2], read only
        REG32 rtc_day_int_raw_sts : 1;         // [3], read only
        REG32 rtc_alm_int_raw_sts : 1;         // [4], read only
        REG32 rtc_alm_int0_raw_sts : 1;        // [5], read only
        REG32 rtc_auxalm_int_raw_sts : 1;      // [6], read only
        REG32 rtc_spg_upd_int_raw_sts : 1;     // [7], read only
        REG32 rtc_sec_cnt_upd_int_raw_sts : 1; // [8], read only
        REG32 rtc_min_cnt_upd_int_raw_sts : 1; // [9], read only
        REG32 rtc_hrs_cnt_upd_int_raw_sts : 1; // [10], read only
        REG32 rtc_day_cnt_upd_int_raw_sts : 1; // [11], read only
        REG32 rtc_sec_alm_upd_int_raw_sts : 1; // [12], read only
        REG32 rtc_min_alm_upd_int_raw_sts : 1; // [13], read only
        REG32 rtc_hrs_alm_upd_int_raw_sts : 1; // [14], read only
        REG32 rtc_day_alm_upd_int_raw_sts : 1; // [15], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_INT_RAW_STS_T;

//RTC_INT_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_int_clr : 1; // [0]
        REG32 rtc_min_int_clr : 1; // [1]
        REG32 rtc_hrs_int_clr : 1; // [2]
        REG32 rtc_day_int_clr : 1; // [3]
        REG32 rtc_alm_int_clr : 1; // [4]
        REG32 __5_5 : 1;
        REG32 rtc_auxalm_int_clr : 1;       // [6]
        REG32 rtc_spg_upd_int_clr : 1;      // [7]
        REG32 rtc_sec_cnt_upd_int_clr : 1;  // [8]
        REG32 rtc_min_cnt_upd_int_clr : 1;  // [9]
        REG32 rtc_hour_cnt_upd_int_clr : 1; // [10]
        REG32 rtc_day_cnt_upd_int_clr : 1;  // [11]
        REG32 rtc_sec_alm_upd_int_clr : 1;  // [12]
        REG32 rtc_min_alm_upd_int_clr : 1;  // [13]
        REG32 rtc_hour_alm_upd_int_clr : 1; // [14]
        REG32 rtc_day_alm_upd_int_clr : 1;  // [15]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_INT_CLR_T;

//RTC_INT_MASK_STS
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_int_mask_sts : 1; // [0], read only
        REG32 rtc_min_int_mask_sts : 1; // [1], read only
        REG32 rtc_hrs_int_mask_sts : 1; // [2], read only
        REG32 rtc_day_int_mask_sts : 1; // [3], read only
        REG32 rtc_alm_int_mask_sts : 1; // [4], read only
        REG32 __5_5 : 1;
        REG32 rtc_auxalm_int_mask_sts : 1;      // [6], read only
        REG32 rtc_spg_upd_int_mask_sts : 1;     // [7], read only
        REG32 rtc_sec_cnt_upd_int_mask_sts : 1; // [8], read only
        REG32 rtc_min_cnt_upd_int_mask_sts : 1; // [9], read only
        REG32 rtc_hrs_cnt_upd_int_mask_sts : 1; // [10], read only
        REG32 rtc_day_cnt_upd_int_mask_sts : 1; // [11], read only
        REG32 rtc_sec_alm_upd_int_mask_sts : 1; // [12], read only
        REG32 rtc_min_alm_upd_int_mask_sts : 1; // [13], read only
        REG32 rtc_hrs_alm_upd_int_mask_sts : 1; // [14], read only
        REG32 rtc_day_alm_upd_int_mask_sts : 1; // [15], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_INT_MASK_STS_T;

//RTC_SEC_ALM_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_alm_value : 6; // [5:0], read only
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_SEC_ALM_VALUE_T;

//RTC_MIN_ALM_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_min_alm_value : 6; // [5:0], read only
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_MIN_ALM_VALUE_T;

//RTC_HRS_ALM_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_hrs_alm_value : 5; // [4:0], read only
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_RTC_RTC_HRS_ALM_VALUE_T;

//RTC_DAY_ALM_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_day_alm_value : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_DAY_ALM_VALUE_T;

//RTC_SPG_VALUE
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_almlock_value : 8; // [7:0], read only
        REG32 rtc_spg_value : 8;     // [15:8], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_SPG_VALUE_T;

//RTC_SPG_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_almlock_upd : 8; // [7:0]
        REG32 rtc_spg_upd : 8;     // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_SPG_UPD_T;

//RTC_PWR_FLAG_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_pwr_flag_clr : 8; // [7:0]
        REG32 rtc_pwr_flag_set : 8; // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_PWR_FLAG_CTRL_T;

//RTC_PWR_FLAG_STS
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_pwr_flag_sts : 8; // [7:0], read only
        REG32 __31_8 : 24;
    } b;
} REG_RDA2720M_RTC_RTC_PWR_FLAG_STS_T;

//RTC_SEC_AUXALM_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_auxalm_upd : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_SEC_AUXALM_UPD_T;

//RTC_MIN_AUXALM_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_min_auxalm_upd : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_MIN_AUXALM_UPD_T;

//RTC_HRS_AUXALM_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_hrs_auxalm_upd : 5; // [4:0]
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_RTC_RTC_HRS_AUXALM_UPD_T;

//RTC_DAY_AUXALM_UPD
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_day_auxalm_upd : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_DAY_AUXALM_UPD_T;

//RTC_SEC_CNT_RAW
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_sec_cnt_raw : 6; // [5:0], read only
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_SEC_CNT_RAW_T;

//RTC_MIN_CNT_RAW
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_min_cnt_raw : 6; // [5:0], read only
        REG32 __31_6 : 26;
    } b;
} REG_RDA2720M_RTC_RTC_MIN_CNT_RAW_T;

//RTC_HRS_CNT_RAW
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_hrs_cnt_raw : 5; // [4:0], read only
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_RTC_RTC_HRS_CNT_RAW_T;

//RTC_DAY_CNT_RAW
typedef union {
    REG32 v;
    struct
    {
        REG32 rtc_day_cnt_raw : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_RTC_RTC_DAY_CNT_RAW_T;

#endif
