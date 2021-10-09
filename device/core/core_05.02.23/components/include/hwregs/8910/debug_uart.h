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

#ifndef _DEBUG_UART_H_
#define _DEBUG_UART_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'debug_uart'."
#endif

// =============================================================================
//  MACROS
// =============================================================================
#define DEBUG_UART_RX_FIFO_SIZE (16)
#define DEBUG_UART_TX_FIFO_SIZE (16)
#define DEBUG_UART_NB_RX_FIFO_BITS (4)
#define DEBUG_UART_NB_TX_FIFO_BITS (4)
#define ESC_DAT (92)

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// DEBUG_UART_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_DEBUG_UART_BASE 0x05110000
#else
#define REG_DEBUG_UART_BASE 0x50110000
#endif

typedef volatile struct
{
    REG32 ctrl;        //0x00000000
    REG32 status;      //0x00000004
    REG32 rxtx_buffer; //0x00000008
    REG32 irq_mask;    //0x0000000C
    REG32 irq_cause;   //0x00000010
    REG32 triggers;    //0x00000014
    /// These characters must respect following constraints: They must be
    /// different if used in software control, if BackSlash_En='1', they cannot
    /// be '\' and they cannot be complementary to each other, for example
    /// neither XON1 = ~XOFF1 nor XON1 = ~'\' is permitted.
    REG32 xchar; //0x00000018
} HWP_DEBUG_UART_T;

#define hwp_debugUart ((HWP_DEBUG_UART_T *)REG_ACCESS_ADDRESS(REG_DEBUG_UART_BASE))

//ctrl
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1;           // [0]
        REG32 data_bits : 1;        // [1]
        REG32 tx_stop_bits : 1;     // [2]
        REG32 parity_enable : 1;    // [3]
        REG32 parity_select : 2;    // [5:4]
        REG32 tx_break_control : 1; // [6]
        REG32 rx_fifo_reset : 1;    // [7]
        REG32 tx_fifo_reset : 1;    // [8]
        REG32 dma_mode : 1;         // [9]
        REG32 __11_10 : 2;
        REG32 swrx_flow_ctrl : 2; // [13:12]
        REG32 swtx_flow_ctrl : 2; // [15:14]
        REG32 backslash_en : 1;   // [16]
        REG32 send_xon : 1;       // [17]
        REG32 __18_18 : 1;
        REG32 tx_finish_n_wait : 1;  // [19]
        REG32 divisor_mode : 1;      // [20]
        REG32 irda_enable : 1;       // [21]
        REG32 rx_rts : 1;            // [22]
        REG32 auto_flow_control : 1; // [23]
        REG32 loop_back_mode : 1;    // [24]
        REG32 rx_lock_err : 1;       // [25]
        REG32 hst_txd_oen : 1;       // [26]
        REG32 __27_27 : 1;
        REG32 rx_break_length : 4; // [31:28]
    } b;
} REG_DEBUG_UART_CTRL_T;

//status
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_fifo_level : 5; // [4:0], read only
        REG32 __7_5 : 3;
        REG32 tx_fifo_level : 5; // [12:8], read only
        REG32 tx_active : 1;     // [13], read only
        REG32 rx_active : 1;     // [14], read only
        REG32 __15_15 : 1;
        REG32 rx_overflow_err : 1; // [16], read only
        REG32 tx_overflow_err : 1; // [17], read only
        REG32 rx_parity_err : 1;   // [18], read only
        REG32 rx_framing_err : 1;  // [19], read only
        REG32 rx_break_int : 1;    // [20], read only
        REG32 __23_21 : 3;
        REG32 tx_dcts : 1; // [24], read only
        REG32 tx_cts : 1;  // [25], read only
        REG32 __27_26 : 2;
        REG32 tx_fifo_rsted_l : 1;   // [28], read only
        REG32 rx_fifo_rsted_l : 1;   // [29], read only
        REG32 enable_n_finished : 1; // [30], read only
        REG32 clk_enabled : 1;       // [31], read only
    } b;
} REG_DEBUG_UART_STATUS_T;

//rxtx_buffer
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_data : 8; // [7:0], read only
        REG32 tx_data : 8; // [7:0]
        REG32 __31_8 : 24;
    } b;
} REG_DEBUG_UART_RXTX_BUFFER_T;

//irq_mask
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_modem_status : 1;   // [0]
        REG32 rx_data_available : 1; // [1]
        REG32 tx_data_needed : 1;    // [2]
        REG32 rx_timeout : 1;        // [3]
        REG32 rx_line_err : 1;       // [4]
        REG32 tx_dma_done : 1;       // [5]
        REG32 rx_dma_done : 1;       // [6]
        REG32 rx_dma_timeout : 1;    // [7]
        REG32 xoff_detected : 1;     // [8]
        REG32 __31_9 : 23;
    } b;
} REG_DEBUG_UART_IRQ_MASK_T;

//irq_cause
typedef union {
    REG32 v;
    struct
    {
        REG32 tx_modem_status : 1;   // [0], read only
        REG32 rx_data_available : 1; // [1], read only
        REG32 tx_data_needed : 1;    // [2], read only
        REG32 rx_timeout : 1;        // [3], read only
        REG32 rx_line_err : 1;       // [4], read only
        REG32 tx_dma_done : 1;       // [5]
        REG32 rx_dma_done : 1;       // [6]
        REG32 rx_dma_timeout : 1;    // [7]
        REG32 xoff_detected : 1;     // [8], read only
        REG32 __15_9 : 7;
        REG32 tx_modem_status_u : 1;   // [16], read only
        REG32 rx_data_available_u : 1; // [17], read only
        REG32 tx_data_needed_u : 1;    // [18], read only
        REG32 rx_timeout_u : 1;        // [19], read only
        REG32 rx_line_err_u : 1;       // [20], read only
        REG32 tx_dma_done_u : 1;       // [21], read only
        REG32 rx_dma_done_u : 1;       // [22], read only
        REG32 rx_dma_timeout_u : 1;    // [23], read only
        REG32 xoff_detected_u : 1;     // [24], read only
        REG32 __31_25 : 7;
    } b;
} REG_DEBUG_UART_IRQ_CAUSE_T;

//triggers
typedef union {
    REG32 v;
    struct
    {
        REG32 rx_trigger : 4; // [3:0]
        REG32 tx_trigger : 4; // [7:4]
        REG32 afc_level : 4;  // [11:8]
        REG32 __31_12 : 20;
    } b;
} REG_DEBUG_UART_TRIGGERS_T;

//XChar
typedef union {
    REG32 v;
    struct
    {
        REG32 xon1 : 8;  // [7:0]
        REG32 xoff1 : 8; // [15:8]
        REG32 xon2 : 8;  // [23:16]
        REG32 xoff2 : 8; // [31:24]
    } b;
} REG_DEBUG_UART_XCHAR_T;

//ctrl
#define DEBUG_UART_ENABLE_V_DISABLE (0)
#define DEBUG_UART_ENABLE_V_ENABLE (1)
#define DEBUG_UART_DATA_BITS_V_7_BITS (0)
#define DEBUG_UART_DATA_BITS_V_8_BITS (1)
#define DEBUG_UART_TX_STOP_BITS_V_1_BIT (0)
#define DEBUG_UART_TX_STOP_BITS_V_2_BITS (1)
#define DEBUG_UART_PARITY_ENABLE_V_NO (0)
#define DEBUG_UART_PARITY_ENABLE_V_YES (1)
#define DEBUG_UART_PARITY_SELECT_V_ODD (0)
#define DEBUG_UART_PARITY_SELECT_V_EVEN (1)
#define DEBUG_UART_PARITY_SELECT_V_SPACE (2)
#define DEBUG_UART_PARITY_SELECT_V_MARK (3)
#define DEBUG_UART_TX_BREAK_CONTROL_V_OFF (0)
#define DEBUG_UART_TX_BREAK_CONTROL_V_ON (1)
#define DEBUG_UART_DMA_MODE_V_DISABLE (0)
#define DEBUG_UART_DMA_MODE_V_ENABLE (1)
#define DEBUG_UART_RX_RTS_V_INACTIVE (0)
#define DEBUG_UART_RX_RTS_V_ACTIVE (1)
#define DEBUG_UART_AUTO_FLOW_CONTROL_V_ENABLE (1)
#define DEBUG_UART_AUTO_FLOW_CONTROL_V_DISABLE (0)
#define DEBUG_UART_RX_LOCK_ERR_V_DISABLE (0)
#define DEBUG_UART_RX_LOCK_ERR_V_ENABLE (1)
#define DEBUG_UART_HST_TXD_OEN_V_DISABLE (1)
#define DEBUG_UART_HST_TXD_OEN_V_ENABLE (0)

#endif
