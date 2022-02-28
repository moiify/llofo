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

#ifndef _GPIO_H_
#define _GPIO_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'gpio'."
#endif

// =============================================================================
//  MACROS
// =============================================================================
#define IDX_GPIO_DCON (0)
#define IDX_GPO_CHG (0)

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// GPIO_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_GPIO1_BASE 0x05107000
#else
#define REG_GPIO1_BASE 0x50107000
#endif

typedef volatile struct
{
    REG32 gpio_oen_val;         //0x00000000
    REG32 gpio_oen_set_out;     //0x00000004
    REG32 gpio_oen_set_in;      //0x00000008
    REG32 gpio_val_reg;         //0x0000000C
    REG32 gpio_set_reg;         //0x00000010
    REG32 gpio_clr_reg;         //0x00000014
    REG32 gpint_ctrl_r_set_reg; //0x00000018
    REG32 gpint_ctrl_r_clr_reg; //0x0000001C
    REG32 int_clr;              //0x00000020
    REG32 int_status;           //0x00000024
    REG32 chg_ctrl;             //0x00000028
    REG32 chg_cmd;              //0x0000002C
    REG32 gpo_set_reg;          //0x00000030
    REG32 gpo_clr_reg;          //0x00000034
    REG32 gpint_ctrl_f_set_reg; //0x00000038
    REG32 gpint_ctrl_f_clr_reg; //0x0000003C
    REG32 dbn_en_set_reg;       //0x00000040
    REG32 dbn_en_clr_reg;       //0x00000044
    REG32 gpint_mode_set_reg;   //0x00000048
    REG32 gpint_mode_clr_reg;   //0x0000004C
} HWP_GPIO_T;

#define hwp_gpio1 ((HWP_GPIO_T *)REG_ACCESS_ADDRESS(REG_GPIO1_BASE))

//chg_ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 out_time : 4;  // [3:0]
        REG32 wait_time : 6; // [9:4]
        REG32 __15_10 : 6;
        REG32 int_mode : 2; // [17:16]
        REG32 __31_18 : 14;
    } b;
} REG_GPIO_CHG_CTRL_T;

//chg_cmd
typedef union {
    REG32 v;
    struct
    {
        REG32 dcon_mode_set : 1; // [0], write set
        REG32 __3_1 : 3;
        REG32 chg_mode_set : 1; // [4], write set
        REG32 __7_5 : 3;
        REG32 dcon_mode_clr : 1; // [8], write clear
        REG32 __11_9 : 3;
        REG32 chg_mode_clr : 1; // [12], write clear
        REG32 __23_13 : 11;
        REG32 chg_down : 1; // [24], write set
        REG32 __31_25 : 7;
    } b;
} REG_GPIO_CHG_CMD_T;

//gpo_set_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 gpo_set : 8; // [7:0], write set
        REG32 __31_8 : 24;
    } b;
} REG_GPIO_GPO_SET_REG_T;

//gpo_clr_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 gpo_clr : 8; // [7:0], write clear
        REG32 __31_8 : 24;
    } b;
} REG_GPIO_GPO_CLR_REG_T;

//gpio_oen_val
#define GPIO_OEN_VAL_V_INPUT (0x1)
#define GPIO_OEN_VAL_V_OUTPUT (0x0)

//chg_ctrl
#define GPIO_INT_MODE_V_L2H (0)
#define GPIO_INT_MODE_V_H2L (1)
#define GPIO_INT_MODE_V_RR (3)

#endif
