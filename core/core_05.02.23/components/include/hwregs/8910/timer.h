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

#ifndef _TIMER_H_
#define _TIMER_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'timer'."
#endif

// =============================================================================
//  MACROS
// =============================================================================
#define NB_INTERVAL (1)
#define INT_TIMER_NB_BITS (24)
#define WD_TIMER_NB_BITS (24)
#define HW_TIMER_NB_BITS (32)
#define TIM_MAXVAL (0XFFFFFF)

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// TIMER_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_TIMER1_BASE 0x08808000
#define REG_TIMER2_BASE 0x08809000

typedef volatile struct
{
    REG32 ostimer_ctrl;       //0x00000000
    REG32 ostimer_curval;     //0x00000004
    REG32 wdtimer_ctrl;       //0x00000008
    REG32 wdtimer_loadval;    //0x0000000C
    REG32 hwtimer_ctrl;       //0x00000010
    REG32 hwtimer_curval;     //0x00000014
    REG32 timer_irq_mask_set; //0x00000018
    REG32 timer_irq_mask_clr; //0x0000001C
    REG32 timer_irq_clr;      //0x00000020
    REG32 timer_irq_cause;    //0x00000024
} HWP_TIMER_T;

#define hwp_timer1 ((HWP_TIMER_T *)REG_ACCESS_ADDRESS(REG_TIMER1_BASE))
#define hwp_timer2 ((HWP_TIMER_T *)REG_ACCESS_ADDRESS(REG_TIMER2_BASE))

//OSTimer_Ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 loadval : 24; // [23:0]
        REG32 enable : 1;   // [24]
        REG32 enabled : 1;  // [25], read only
        REG32 cleared : 1;  // [26], read only
        REG32 __27_27 : 1;
        REG32 repeat : 1; // [28]
        REG32 wrap : 1;   // [29]
        REG32 load : 1;   // [30]
        REG32 __31_31 : 1;
    } b;
} REG_TIMER_OSTIMER_CTRL_T;

//WDTimer_Ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1; // [0], write set
        REG32 __3_1 : 3;
        REG32 stop : 1; // [4], write clear
        REG32 __7_5 : 3;
        REG32 wdenabled : 1; // [8], read only
        REG32 __15_9 : 7;
        REG32 reload : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_TIMER_WDTIMER_CTRL_T;

//WDTimer_LoadVal
typedef union {
    REG32 v;
    struct
    {
        REG32 wdloadval : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_TIMER_WDTIMER_LOADVAL_T;

//HWTimer_Ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 interval : 2; // [1:0]
        REG32 __7_2 : 6;
        REG32 interval_en : 1; // [8]
        REG32 __31_9 : 23;
    } b;
} REG_TIMER_HWTIMER_CTRL_T;

//Timer_Irq_Mask_Set
typedef union {
    REG32 v;
    struct
    {
        REG32 ostimer_mask : 1;      // [0], write set
        REG32 hwtimer_wrap_mask : 1; // [1], write set
        REG32 hwtimer_itv_mask : 1;  // [2], write set
        REG32 __31_3 : 29;
    } b;
} REG_TIMER_TIMER_IRQ_MASK_SET_T;

//Timer_Irq_Mask_Clr
typedef union {
    REG32 v;
    struct
    {
        REG32 ostimer_mask : 1;      // [0], write clear
        REG32 hwtimer_wrap_mask : 1; // [1], write clear
        REG32 hwtimer_itv_mask : 1;  // [2], write clear
        REG32 __31_3 : 29;
    } b;
} REG_TIMER_TIMER_IRQ_MASK_CLR_T;

//Timer_Irq_Clr
typedef union {
    REG32 v;
    struct
    {
        REG32 ostimer_clr : 1;      // [0], write clear
        REG32 hwtimer_wrap_clr : 1; // [1], write clear
        REG32 hwtimer_itv_clr : 1;  // [2], write clear
        REG32 __31_3 : 29;
    } b;
} REG_TIMER_TIMER_IRQ_CLR_T;

//Timer_Irq_Cause
typedef union {
    REG32 v;
    struct
    {
        REG32 ostimer_cause : 1;      // [0], read only
        REG32 hwtimer_wrap_cause : 1; // [1], read only
        REG32 hwtimer_itv_cause : 1;  // [2], read only
        REG32 __15_3 : 13;
        REG32 ostimer_status : 1;      // [16], read only
        REG32 hwtimer_wrap_status : 1; // [17], read only
        REG32 hwtimer_itv_status : 1;  // [18], read only
        REG32 __31_19 : 13;
    } b;
} REG_TIMER_TIMER_IRQ_CAUSE_T;

#endif
