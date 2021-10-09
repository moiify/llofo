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

#ifndef _AP_IFC_H_
#define _AP_IFC_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'ap_ifc'."
#endif

// =============================================================================
//  MACROS
// =============================================================================
#define AP_IFC_ADDR_ALIGN (0)
#define AP_IFC_TC_LEN (23)
#define AP_IFC_STD_CHAN_NB (AP_IFC_NB_STD_CHANNEL)
#define AP_IFC_RFSPI_CHAN (0)
#define AP_APB1_IFC_AHB_MAXSPACE (20)
#define AP_APB1_IFC_ADDR_ALIGN (2)

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// AP_IFC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_AP_IFC_BASE 0x0880F000

typedef volatile struct
{
    REG32 get_ch;            //0x00000000
    REG32 dma_status;        //0x00000004
    REG32 debug_status;      //0x00000008
    REG32 Reserved_0000000C; //0x0000000C
    struct
    {
        REG32 control;    //0x00000010
        REG32 status;     //0x00000014
        REG32 start_addr; //0x00000018
        REG32 tc;         //0x0000001C
    } std_ch[AP_IFC_STD_CHAN_NB];
    REG32 ch_rfspi_control;      //0x00000080
    REG32 ch_rfspi_status;       //0x00000084
    REG32 ch_rfspi_start_addr;   //0x00000088
    REG32 ch_rfspi_end_addr;     //0x0000008C
    REG32 ch_rfspi_tc;           //0x00000090
    REG32 Reserved_00000094[27]; //0x00000094
} HWP_AP_IFC_T;

#define hwp_apIfc ((HWP_AP_IFC_T *)REG_ACCESS_ADDRESS(REG_AP_IFC_BASE))

//get_ch
typedef union {
    REG32 v;
    struct
    {
        REG32 ch_to_use : 4; // [3:0], read only
        REG32 __31_4 : 28;
    } b;
} REG_AP_IFC_GET_CH_T;

//dma_status
typedef union {
    REG32 v;
    struct
    {
        REG32 ch_enable : 7; // [6:0], read only
        REG32 __15_7 : 9;
        REG32 ch_busy : 7; // [22:16], read only
        REG32 __31_23 : 9;
    } b;
} REG_AP_IFC_DMA_STATUS_T;

//debug_status
typedef union {
    REG32 v;
    struct
    {
        REG32 dbg_status : 1; // [0], read only
        REG32 __31_1 : 31;
    } b;
} REG_AP_IFC_DEBUG_STATUS_T;

//control
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1;      // [0]
        REG32 disable : 1;     // [1]
        REG32 rd_hw_exch : 1;  // [2]
        REG32 wr_hw_exch : 1;  // [3]
        REG32 autodisable : 1; // [4]
        REG32 size : 1;        // [5]
        REG32 __7_6 : 2;
        REG32 req_src : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 flush : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_AP_IFC_CONTROL_T;

//status
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1; // [0], read only
        REG32 __3_1 : 3;
        REG32 fifo_empty : 1; // [4], read only
        REG32 __31_5 : 27;
    } b;
} REG_AP_IFC_STATUS_T;

//tc
typedef union {
    REG32 v;
    struct
    {
        REG32 tc : 23; // [22:0]
        REG32 __31_23 : 9;
    } b;
} REG_AP_IFC_TC_T;

//ch_rfspi_control
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1;  // [0], write set
        REG32 disable : 1; // [1], write clear
        REG32 __31_2 : 30;
    } b;
} REG_AP_IFC_CH_RFSPI_CONTROL_T;

//ch_rfspi_status
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1; // [0], read only
        REG32 __3_1 : 3;
        REG32 fifo_empty : 1; // [4], read only
        REG32 __7_5 : 3;
        REG32 fifo_level : 5; // [12:8], read only
        REG32 __31_13 : 19;
    } b;
} REG_AP_IFC_CH_RFSPI_STATUS_T;

//ch_rfspi_tc
typedef union {
    REG32 v;
    struct
    {
        REG32 tc : 14; // [13:0]
        REG32 __31_14 : 18;
    } b;
} REG_AP_IFC_CH_RFSPI_TC_T;

//control
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SDMMC1_TX (0)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SDMMC1_RX (1)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SDMMC2_TX (2)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SDMMC2_RX (3)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SPI_1_TX (4)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SPI_1_RX (5)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SPI_2_TX (6)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SPI_2_RX (7)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SCI_1_TX (8)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SCI_1_RX (9)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SCI_2_TX (10)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_SCI_2_RX (11)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_FREE_TX (18)
#define AP_IFC_REQ_SRC_V_AP_APB_DMA_ID_CAMERA_RX (19)

// ============================================================================
// AUDIO_IFC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_AUDIO_IFC_BASE 0x0880F100

typedef volatile struct
{
    /// The Channel 0 conveys data from the AIF to the memory.
    /// The Channel 1 conveys data from the memory to the AIF.
    /// These Channels only exist with Voice Option.
    struct
    {
        REG32 control;           //0x00000000
        REG32 status;            //0x00000004
        REG32 start_addr;        //0x00000008
        REG32 fifo_size;         //0x0000000C
        REG32 Reserved_00000010; //0x00000010
        REG32 int_mask;          //0x00000014
        REG32 int_clear;         //0x00000018
        REG32 cur_ahb_addr;      //0x0000001C
    } ch[NB_AIF_IFC_CHANNEL];
} HWP_AUDIO_IFC_T;

#define hwp_audioIfc ((HWP_AUDIO_IFC_T *)REG_ACCESS_ADDRESS(REG_AUDIO_IFC_BASE))

//control
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1;  // [0]
        REG32 disable : 1; // [1]
        REG32 __3_2 : 2;
        REG32 auto_disable : 1; // [4]
        REG32 __31_5 : 27;
    } b;
} REG_AUDIO_IFC_CONTROL_T;

//status
typedef union {
    REG32 v;
    struct
    {
        REG32 enable : 1; // [0], read only
        REG32 __3_1 : 3;
        REG32 fifo_empty : 1; // [4], read only
        REG32 __7_5 : 3;
        REG32 cause_ief : 1;       // [8], read only
        REG32 cause_ihf : 1;       // [9], read only
        REG32 cause_i4f : 1;       // [10], read only
        REG32 cause_i3_4f : 1;     // [11], read only
        REG32 cause_ahb_error : 1; // [12], read only
        REG32 __15_13 : 3;
        REG32 ief : 1;       // [16], read only
        REG32 ihf : 1;       // [17], read only
        REG32 i4f : 1;       // [18], read only
        REG32 i3_4f : 1;     // [19], read only
        REG32 ahb_error : 1; // [20], read only
        REG32 ch_idle : 1;   // [21], read only
        REG32 __31_22 : 10;
    } b;
} REG_AUDIO_IFC_STATUS_T;

//start_addr
typedef union {
    REG32 v;
    struct
    {
        REG32 __1_0 : 2;
        REG32 start_addr : 30; // [31:2]
    } b;
} REG_AUDIO_IFC_START_ADDR_T;

//Fifo_Size
typedef union {
    REG32 v;
    struct
    {
        REG32 __3_0 : 4;
        REG32 fifo_size : 16; // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_AUDIO_IFC_FIFO_SIZE_T;

//int_mask
typedef union {
    REG32 v;
    struct
    {
        REG32 __7_0 : 8;
        REG32 end_fifo : 1;           // [8]
        REG32 half_fifo : 1;          // [9]
        REG32 quarter_fifo : 1;       // [10]
        REG32 three_quarter_fifo : 1; // [11]
        REG32 ahb_error : 1;          // [12]
        REG32 __31_13 : 19;
    } b;
} REG_AUDIO_IFC_INT_MASK_T;

//int_clear
typedef union {
    REG32 v;
    struct
    {
        REG32 __7_0 : 8;
        REG32 end_fifo : 1;           // [8], write clear
        REG32 half_fifo : 1;          // [9], write clear
        REG32 quarter_fifo : 1;       // [10], write clear
        REG32 three_quarter_fifo : 1; // [11], write clear
        REG32 ahb_error : 1;          // [12], write clear
        REG32 __31_13 : 19;
    } b;
} REG_AUDIO_IFC_INT_CLEAR_T;

#endif
