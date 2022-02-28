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

#ifndef _DEBUG_HOST_H_
#define _DEBUG_HOST_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'debug_host'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// DEBUG_HOST_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_DEBUG_HOST_BASE 0x0517F000
#else
#define REG_DEBUG_HOST_BASE 0x5017F000
#endif

typedef volatile struct
{
    REG32 cmd;            //0x00000000
    REG32 data_reg;       //0x00000004
    REG32 event;          //0x00000008
    REG32 mode;           //0x0000000C
    REG32 h2p_status_reg; //0x00000010
    REG32 p2h_status_reg; //0x00000014
    REG32 irq;            //0x00000018
} HWP_DEBUG_HOST_T;

#define hwp_debugHost ((HWP_DEBUG_HOST_T *)REG_ACCESS_ADDRESS(REG_DEBUG_HOST_BASE))

//cmd
typedef union {
    REG32 v;
    struct
    {
        REG32 addr : 29;   // [28:0], read only
        REG32 size : 2;    // [30:29], read only
        REG32 write_h : 1; // [31], read only
    } b;
} REG_DEBUG_HOST_CMD_T;

//event
typedef union {
    REG32 v;
    struct
    {
        REG32 event0_sema : 1; // [0]
        REG32 event31_1 : 31;  // [31:1]
    } b;
} REG_DEBUG_HOST_EVENT_T;

//mode
typedef union {
    REG32 v;
    struct
    {
        REG32 force_on : 1;    // [0]
        REG32 clk_host_on : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_DEBUG_HOST_MODE_T;

//h2p_status_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 h2p_status : 8; // [7:0], read only
        REG32 __15_8 : 8;
        REG32 h2p_status_rst : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_DEBUG_HOST_H2P_STATUS_REG_T;

//p2h_status_REG
typedef union {
    REG32 v;
    struct
    {
        REG32 p2h_status : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_DEBUG_HOST_P2H_STATUS_REG_T;

//irq
typedef union {
    REG32 v;
    struct
    {
        REG32 xcpu_irq : 1; // [0], read only
        REG32 bcpu_irq : 1; // [1], read only
        REG32 __31_2 : 30;
    } b;
} REG_DEBUG_HOST_IRQ_T;

#endif
