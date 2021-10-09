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

#ifndef _LZMA_H_
#define _LZMA_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'lzma'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// LZMA_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_LZMA_BASE 0x08805000

typedef volatile struct
{
    REG32 lzma_cmd_reg;            //0x00000000
    REG32 lzma_status_reg;         //0x00000004
    REG32 lzma_irq_mask;           //0x00000008
    REG32 reserve0;                //0x0000000C
    REG32 lzma_config_reg1;        //0x00000010
    REG32 lzma_config_reg2;        //0x00000014
    REG32 lzma_config_reg3;        //0x00000018
    REG32 lzma_status_reg2;        //0x0000001C
    REG32 lzma_status_reg3;        //0x00000020
    REG32 lzma_error_type;         //0x00000024
    REG32 reserve1;                //0x00000028
    REG32 reserve2;                //0x0000002C
    REG32 lzma_input_crc;          //0x00000030
    REG32 lzma_output_crc;         //0x00000034
    REG32 reserve3;                //0x00000038
    REG32 reserve4;                //0x0000003C
    REG32 lzma_dma_raddr_reg;      //0x00000040
    REG32 lzma_dma_waddr_reg;      //0x00000044
    REG32 lzma_inbuf_rwmargin_reg; //0x00000048
} HWP_LZMA_T;

#define hwp_lzma ((HWP_LZMA_T *)REG_ACCESS_ADDRESS(REG_LZMA_BASE))

//lzma_cmd_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_LZMA_LZMA_CMD_REG_T;

//lzma_status_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 dec_done : 1; // [0]
        REG32 dec_err : 1;  // [1]
        REG32 axi_err : 1;  // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LZMA_LZMA_STATUS_REG_T;

//lzma_irq_mask
typedef union {
    REG32 v;
    struct
    {
        REG32 dec_doneirqmask : 1; // [0]
        REG32 dec_errirqmask : 1;  // [1]
        REG32 axi_errirqmask : 1;  // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LZMA_LZMA_IRQ_MASK_T;

//lzma_config_reg1
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_block_size : 17; // [16:0]
        REG32 reg_dict_size : 13;  // [29:17]
        REG32 __31_30 : 2;
    } b;
} REG_LZMA_LZMA_CONFIG_REG1_T;

//lzma_config_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_stream_len : 17; // [16:0]
        REG32 __31_17 : 15;
    } b;
} REG_LZMA_LZMA_CONFIG_REG2_T;

//lzma_config_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 reg_cabac_totalbits : 1; // [0]
        REG32 reg_cabac_movebits : 1;  // [1]
        REG32 reg_refbyte_en : 1;      // [2]
        REG32 __31_3 : 29;
    } b;
} REG_LZMA_LZMA_CONFIG_REG3_T;

//lzma_status_reg2
typedef union {
    REG32 v;
    struct
    {
        REG32 stream_byte_pos : 17; // [16:0], read only
        REG32 __31_17 : 15;
    } b;
} REG_LZMA_LZMA_STATUS_REG2_T;

//lzma_status_reg3
typedef union {
    REG32 v;
    struct
    {
        REG32 dict_byte_pos : 17; // [16:0], read only
        REG32 __31_17 : 15;
    } b;
} REG_LZMA_LZMA_STATUS_REG3_T;

//lzma_error_type
typedef union {
    REG32 v;
    struct
    {
        REG32 inbuf_overflow : 1;   // [0], read only
        REG32 symbol_type_err : 1;  // [1], read only
        REG32 symbol_reps_err1 : 1; // [2], read only
        REG32 symbol_reps_err0 : 1; // [3], read only
        REG32 symbol_len_err : 1;   // [4], read only
        REG32 outbuf_overflow : 1;  // [5], read only
        REG32 inbuf_underflow : 1;  // [6], read only
        REG32 __31_7 : 25;
    } b;
} REG_LZMA_LZMA_ERROR_TYPE_T;

//lzma_inbuf_rwmargin_reg
typedef union {
    REG32 v;
    struct
    {
        REG32 inbuf_rwmargin_reg : 6; // [5:0]
        REG32 __31_6 : 26;
    } b;
} REG_LZMA_LZMA_INBUF_RWMARGIN_REG_T;

#endif
