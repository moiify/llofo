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

#ifndef _ARM_UART_H_
#define _ARM_UART_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'arm_uart'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// ARM_UART_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_UART2_BASE 0x08817000
#define REG_UART3_BASE 0x08818000
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_UART1_BASE 0x05098000
#else
#define REG_UART1_BASE 0x50098000
#endif

typedef volatile struct
{
    REG32 uart_tx;          //0x00000000
    REG32 uart_rx;          //0x00000004
    REG32 uart_baud;        //0x00000008
    REG32 uart_conf;        //0x0000000C
    REG32 uart_rxtrig;      //0x00000010
    REG32 uart_txtrig;      //0x00000014
    REG32 uart_delay;       //0x00000018
    REG32 uart_status;      //0x0000001C
    REG32 uart_rxfifo_stat; //0x00000020
    REG32 uart_txfifo_stat; //0x00000024
    REG32 uart_rxfifo_hdlc; //0x00000028
    REG32 uart_at_status;   //0x0000002C
    REG32 uart_swfc_cc;     //0x00000030
} HWP_ARM_UART_T;

#define hwp_uart2 ((HWP_ARM_UART_T *)REG_ACCESS_ADDRESS(REG_UART2_BASE))
#define hwp_uart3 ((HWP_ARM_UART_T *)REG_ACCESS_ADDRESS(REG_UART3_BASE))
#define hwp_uart1 ((HWP_ARM_UART_T *)REG_ACCESS_ADDRESS(REG_UART1_BASE))

//UART_TX
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_data : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_ARM_UART_UART_TX_T;

//UART_RX
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_data : 8; // [7:0], read only
        REG32 __31_8 : 24;
    } b;
} REG_ARM_UART_UART_RX_T;

//UART_BAUD
typedef union {
    REG32 v;
    struct
    {
        REG32 baud_div : 16;  // [15:0]
        REG32 baud_const : 4; // [19:16]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_UART_UART_BAUD_T;

//UART_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 check : 1;         // [0]
        REG32 parity : 1;        // [1]
        REG32 stop_bit : 1;      // [2]
        REG32 st_check : 1;      // [3]
        REG32 rx_ie : 1;         // [4]
        REG32 tx_ie : 1;         // [5]
        REG32 tout_ie : 1;       // [6]
        REG32 hwfc : 1;          // [7]
        REG32 rx_trig_hwfc : 1;  // [8]
        REG32 tout_hwfc : 1;     // [9]
        REG32 hdlc : 1;          // [10]
        REG32 frm_stp : 1;       // [11]
        REG32 trail : 1;         // [12]
        REG32 txrst : 1;         // [13]
        REG32 rxrst : 1;         // [14]
        REG32 at_parity_en : 1;  // [15]
        REG32 at_parity_sel : 2; // [17:16]
        REG32 __18_18 : 1;
        REG32 at_verify_2byte : 1; // [19]
        REG32 at_div_mode : 1;     // [20]
        REG32 at_enable : 1;       // [21]
        REG32 swfc_xoff_ie : 1;    // [22]
        REG32 swfc_xon_ie : 1;     // [23]
        REG32 swfc_en : 1;         // [24]
        REG32 at_lock_ie : 1;      // [25]
        REG32 st_parity : 1;       // [26]
        REG32 __31_27 : 5;
    } b;
} REG_ARM_UART_UART_CONF_T;

//UART_RXTRIG
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_trig : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_ARM_UART_UART_RXTRIG_T;

//UART_TXTRIG
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_trig : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_ARM_UART_UART_TXTRIG_T;

//UART_DELAY
typedef union {
    REG32 v;
    struct
    {
        REG32 toutcnt : 8;      // [7:0]
        REG32 two_tx_delay : 4; // [11:8]
        REG32 __31_12 : 20;
    } b;
} REG_ARM_UART_UART_DELAY_T;

//UART_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_int : 1;      // [0], write clear
        REG32 rx_int : 1;      // [1], write clear
        REG32 timeout_int : 1; // [2], write clear
        REG32 frame_int : 1;   // [3], write clear
        REG32 p_error : 1;     // [4], write clear
        REG32 st_error : 1;    // [5], write clear
        REG32 cts : 1;         // [6], write clear
        REG32 rts : 1;         // [7], write clear
        REG32 swfc_status : 1; // [8], read only
        REG32 xoff_status : 1; // [9], write clear
        REG32 xon_status : 1;  // [10], write clear
        REG32 __31_11 : 21;
    } b;
} REG_ARM_UART_UART_STATUS_T;

//UART_RXFIFO_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_fifo_cnt : 8; // [7:0], read only
        REG32 __31_8 : 24;
    } b;
} REG_ARM_UART_UART_RXFIFO_STAT_T;

//UART_TXFIFO_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_fifo_cnt : 8; // [7:0], read only
        REG32 __31_8 : 24;
    } b;
} REG_ARM_UART_UART_TXFIFO_STAT_T;

//UART_RXFIFO_HDLC
typedef union {
    REG32 v;
    struct
    {
        REG32 hdlc_rxfifo_cnt : 8; // [7:0], read only
        REG32 __31_8 : 24;
    } b;
} REG_ARM_UART_UART_RXFIFO_HDLC_T;

//UART_AT_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 at_baud_div : 16;         // [15:0], read only
        REG32 character_miscompare : 1; // [16], read only
        REG32 auto_baud_locked : 1;     // [17], read only
        REG32 character_status : 1;     // [18], read only
        REG32 __31_19 : 13;
    } b;
} REG_ARM_UART_UART_AT_STATUS_T;

//UART_SWFC_CC
typedef union {
    REG32 v;
    struct
    {
        REG32 xoff_cc : 8; // [7:0]
        REG32 xon_cc : 8;  // [15:8]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_UART_UART_SWFC_CC_T;

#endif
