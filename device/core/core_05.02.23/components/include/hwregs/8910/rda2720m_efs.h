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

#ifndef _RDA2720M_EFS_H_
#define _RDA2720M_EFS_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'rda2720m_efs'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// RDA2720M_EFS_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_RDA2720M_EFS_BASE 0x50308300

typedef volatile struct
{
    REG32 efuse_glb_ctrl;           //0x00000000
    REG32 efuse_data_rd;            //0x00000004
    REG32 efuse_data_wr;            //0x00000008
    REG32 efuse_addr_index;         //0x0000000C
    REG32 efuse_mode_ctrl;          //0x00000010
    REG32 efuse_status;             //0x00000014
    REG32 efuse_magic_number;       //0x00000018
    REG32 efuse_magin_magic_number; //0x0000001C
    REG32 efuse_wr_timing_ctrl;     //0x00000020
    REG32 efuse_rd_timing_ctrl;     //0x00000024
    REG32 efuse_version;            //0x00000028
} HWP_RDA2720M_EFS_T;

#define hwp_rda2720mEfs ((HWP_RDA2720M_EFS_T *)REG_ACCESS_ADDRESS(REG_RDA2720M_EFS_BASE))

//EFUSE_GLB_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_pgm_enable : 1; // [0]
        REG32 efuse_type : 2;       // [2:1]
        REG32 margin_mode : 1;      // [3]
        REG32 __31_4 : 28;
    } b;
} REG_RDA2720M_EFS_EFUSE_GLB_CTRL_T;

//EFUSE_DATA_RD
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_data_rd : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EFS_EFUSE_DATA_RD_T;

//EFUSE_DATA_WR
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_data_wr : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EFS_EFUSE_DATA_WR_T;

//EFUSE_ADDR_INDEX
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_addr_index : 5; // [4:0]
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_EFS_EFUSE_ADDR_INDEX_T;

//EFUSE_MODE_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_pg_start : 1;           // [0]
        REG32 efuse_rd_start : 1;           // [1]
        REG32 efuse_normal_rd_flag_clr : 1; // [2]
        REG32 __31_3 : 29;
    } b;
} REG_RDA2720M_EFS_EFUSE_MODE_CTRL_T;

//EFUSE_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 pgm_busy : 1;             // [0], read only
        REG32 read_busy : 1;            // [1], read only
        REG32 standby_busy : 1;         // [2], read only
        REG32 efuse_global_prot : 1;    // [3], read only
        REG32 efuse_normal_rd_done : 1; // [4], read only
        REG32 __31_5 : 27;
    } b;
} REG_RDA2720M_EFS_EFUSE_STATUS_T;

//EFUSE_MAGIC_NUMBER
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_magin_magic_number : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EFS_EFUSE_MAGIC_NUMBER_T;

//EFUSE_MAGIN_MAGIC_NUMBER
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_magin_magic_number : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EFS_EFUSE_MAGIN_MAGIC_NUMBER_T;

//EFUSE_WR_TIMING_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_wr_timing_ctrl : 14; // [13:0], read only
        REG32 __31_14 : 18;
    } b;
} REG_RDA2720M_EFS_EFUSE_WR_TIMING_CTRL_T;

//EFUSE_RD_TIMING_CTRL
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_rd_timing_ctrl : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_RDA2720M_EFS_EFUSE_RD_TIMING_CTRL_T;

//EFUSE_VERSION
typedef union {
    REG32 v;
    struct
    {
        REG32 efuse_version : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_RDA2720M_EFS_EFUSE_VERSION_T;

#endif
