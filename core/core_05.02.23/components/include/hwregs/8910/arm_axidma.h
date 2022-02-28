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

#ifndef _ARM_AXIDMA_H_
#define _ARM_AXIDMA_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'arm_axidma'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// ARM_AXIDMA_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_DMA_BASE 0x090C0000

typedef volatile struct
{
    REG32 axidma_conf;          //0x00000000
    REG32 axidma_delay;         //0x00000004
    REG32 axidma_status;        //0x00000008
    REG32 axidma_irq_stat;      //0x0000000C
    REG32 axidma_arm_req_stat;  //0x00000010
    REG32 axidma_arm_ack_stat;  //0x00000014
    REG32 axidma_zsp_req_stat0; //0x00000018
    REG32 axidma_zsp_req_stat1; //0x0000001C
    REG32 axidma_ch_irq_distr;  //0x00000020
    REG32 Reserved_00000024[7]; //0x00000024
    REG32 axidma_c0_conf;       //0x00000040
    REG32 axidma_c0_map;        //0x00000044
    REG32 axidma_c0_saddr;      //0x00000048
    REG32 axidma_c0_daddr;      //0x0000004C
    REG32 axidma_c0_count;      //0x00000050
    REG32 axidma_c0_countp;     //0x00000054
    REG32 axidma_c0_status;     //0x00000058
    REG32 axidma_c0_sgaddr;     //0x0000005C
    REG32 axidma_c0_sgconf;     //0x00000060
    REG32 axidma_c0_set;        //0x00000064
    REG32 axidma_c0_clr;        //0x00000068
    REG32 Reserved_0000006C[5]; //0x0000006C
    REG32 axidma_c1_conf;       //0x00000080
    REG32 axidma_c1_map;        //0x00000084
    REG32 axidma_c1_saddr;      //0x00000088
    REG32 axidma_c1_daddr;      //0x0000008C
    REG32 axidma_c1_count;      //0x00000090
    REG32 axidma_c1_countp;     //0x00000094
    REG32 axidma_c1_status;     //0x00000098
    REG32 axidma_c1_sgaddr;     //0x0000009C
    REG32 axidma_c1_sgconf;     //0x000000A0
    REG32 axidma_c1_set;        //0x000000A4
    REG32 axidma_c1_clr;        //0x000000A8
    REG32 Reserved_000000AC[5]; //0x000000AC
    REG32 axidma_c2_conf;       //0x000000C0
    REG32 axidma_c2_map;        //0x000000C4
    REG32 axidma_c2_saddr;      //0x000000C8
    REG32 axidma_c2_daddr;      //0x000000CC
    REG32 axidma_c2_count;      //0x000000D0
    REG32 axidma_c2_countp;     //0x000000D4
    REG32 axidma_c2_status;     //0x000000D8
    REG32 axidma_c2_sgaddr;     //0x000000DC
    REG32 axidma_c2_sgconf;     //0x000000E0
    REG32 axidma_c2_set;        //0x000000E4
    REG32 axidma_c2_clr;        //0x000000E8
    REG32 Reserved_000000EC[5]; //0x000000EC
    REG32 axidma_c3_conf;       //0x00000100
    REG32 axidma_c3_map;        //0x00000104
    REG32 axidma_c3_saddr;      //0x00000108
    REG32 axidma_c3_daddr;      //0x0000010C
    REG32 axidma_c3_count;      //0x00000110
    REG32 axidma_c3_countp;     //0x00000114
    REG32 axidma_c3_status;     //0x00000118
    REG32 axidma_c3_sgaddr;     //0x0000011C
    REG32 axidma_c3_sgconf;     //0x00000120
    REG32 axidma_c3_set;        //0x00000124
    REG32 axidma_c3_clr;        //0x00000128
    REG32 Reserved_0000012C[5]; //0x0000012C
    REG32 axidma_c4_conf;       //0x00000140
    REG32 axidma_c4_map;        //0x00000144
    REG32 axidma_c4_saddr;      //0x00000148
    REG32 axidma_c4_daddr;      //0x0000014C
    REG32 axidma_c4_count;      //0x00000150
    REG32 axidma_c4_countp;     //0x00000154
    REG32 axidma_c4_status;     //0x00000158
    REG32 axidma_c4_sgaddr;     //0x0000015C
    REG32 axidma_c4_sgconf;     //0x00000160
    REG32 axidma_c4_set;        //0x00000164
    REG32 axidma_c4_clr;        //0x00000168
    REG32 Reserved_0000016C[5]; //0x0000016C
    REG32 axidma_c5_conf;       //0x00000180
    REG32 axidma_c5_map;        //0x00000184
    REG32 axidma_c5_saddr;      //0x00000188
    REG32 axidma_c5_daddr;      //0x0000018C
    REG32 axidma_c5_count;      //0x00000190
    REG32 axidma_c5_countp;     //0x00000194
    REG32 axidma_c5_status;     //0x00000198
    REG32 axidma_c5_sgaddr;     //0x0000019C
    REG32 axidma_c5_sgconf;     //0x000001A0
    REG32 axidma_c5_set;        //0x000001A4
    REG32 axidma_c5_clr;        //0x000001A8
    REG32 Reserved_000001AC[5]; //0x000001AC
    REG32 axidma_c6_conf;       //0x000001C0
    REG32 axidma_c6_map;        //0x000001C4
    REG32 axidma_c6_saddr;      //0x000001C8
    REG32 axidma_c6_daddr;      //0x000001CC
    REG32 axidma_c6_count;      //0x000001D0
    REG32 axidma_c6_countp;     //0x000001D4
    REG32 axidma_c6_status;     //0x000001D8
    REG32 axidma_c6_sgaddr;     //0x000001DC
    REG32 axidma_c6_sgconf;     //0x000001E0
    REG32 axidma_c6_set;        //0x000001E4
    REG32 axidma_c6_clr;        //0x000001E8
    REG32 Reserved_000001EC[5]; //0x000001EC
    REG32 axidma_c7_conf;       //0x00000200
    REG32 axidma_c7_map;        //0x00000204
    REG32 axidma_c7_saddr;      //0x00000208
    REG32 axidma_c7_daddr;      //0x0000020C
    REG32 axidma_c7_count;      //0x00000210
    REG32 axidma_c7_countp;     //0x00000214
    REG32 axidma_c7_status;     //0x00000218
    REG32 axidma_c7_sgaddr;     //0x0000021C
    REG32 axidma_c7_sgconf;     //0x00000220
    REG32 axidma_c7_set;        //0x00000224
    REG32 axidma_c7_clr;        //0x00000228
    REG32 Reserved_0000022C[5]; //0x0000022C
    REG32 axidma_c8_conf;       //0x00000240
    REG32 axidma_c8_map;        //0x00000244
    REG32 axidma_c8_saddr;      //0x00000248
    REG32 axidma_c8_daddr;      //0x0000024C
    REG32 axidma_c8_count;      //0x00000250
    REG32 axidma_c8_countp;     //0x00000254
    REG32 axidma_c8_status;     //0x00000258
    REG32 axidma_c8_sgaddr;     //0x0000025C
    REG32 axidma_c8_sgconf;     //0x00000260
    REG32 axidma_c8_set;        //0x00000264
    REG32 axidma_c8_clr;        //0x00000268
    REG32 Reserved_0000026C[5]; //0x0000026C
    REG32 axidma_c9_conf;       //0x00000280
    REG32 axidma_c9_map;        //0x00000284
    REG32 axidma_c9_saddr;      //0x00000288
    REG32 axidma_c9_daddr;      //0x0000028C
    REG32 axidma_c9_count;      //0x00000290
    REG32 axidma_c9_countp;     //0x00000294
    REG32 axidma_c9_status;     //0x00000298
    REG32 axidma_c9_sgaddr;     //0x0000029C
    REG32 axidma_c9_sgconf;     //0x000002A0
    REG32 axidma_c9_set;        //0x000002A4
    REG32 axidma_c9_clr;        //0x000002A8
    REG32 Reserved_000002AC[5]; //0x000002AC
    REG32 axidma_c10_conf;      //0x000002C0
    REG32 axidma_c10_map;       //0x000002C4
    REG32 axidma_c10_saddr;     //0x000002C8
    REG32 axidma_c10_daddr;     //0x000002CC
    REG32 axidma_c10_count;     //0x000002D0
    REG32 axidma_c10_countp;    //0x000002D4
    REG32 axidma_c10_status;    //0x000002D8
    REG32 axidma_c10_sgaddr;    //0x000002DC
    REG32 axidma_c10_sgconf;    //0x000002E0
    REG32 axidma_c10_set;       //0x000002E4
    REG32 axidma_c10_clr;       //0x000002E8
    REG32 Reserved_000002EC[5]; //0x000002EC
    REG32 axidma_c11_conf;      //0x00000300
    REG32 axidma_c11_map;       //0x00000304
    REG32 axidma_c11_saddr;     //0x00000308
    REG32 axidma_c11_daddr;     //0x0000030C
    REG32 axidma_c11_count;     //0x00000310
    REG32 axidma_c11_countp;    //0x00000314
    REG32 axidma_c11_status;    //0x00000318
    REG32 axidma_c11_sgaddr;    //0x0000031C
    REG32 axidma_c11_sgconf;    //0x00000320
    REG32 axidma_c11_set;       //0x00000324
    REG32 axidma_c11_clr;       //0x00000328
} HWP_ARM_AXIDMA_T;

#define hwp_dma ((HWP_ARM_AXIDMA_T *)REG_ACCESS_ADDRESS(REG_DMA_BASE))

//AXIDMA_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 stop : 1;     // [0]
        REG32 stop_ie : 1;  // [1]
        REG32 priority : 1; // [2]
        REG32 outstand : 2; // [4:3]
        REG32 mode_sel : 1; // [5]
        REG32 __31_6 : 26;
    } b;
} REG_ARM_AXIDMA_AXIDMA_CONF_T;

//AXIDMA_DELAY
typedef union {
    REG32 v;
    struct
    {
        REG32 delay : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_DELAY_T;

//AXIDMA_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 ch_num : 4;      // [3:0], read only
        REG32 stop_status : 1; // [4], read only
        REG32 __31_5 : 27;
    } b;
} REG_ARM_AXIDMA_AXIDMA_STATUS_T;

//AXIDMA_IRQ_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 ch0_irq : 1;  // [0], read only
        REG32 ch1_irq : 1;  // [1], read only
        REG32 ch2_irq : 1;  // [2], read only
        REG32 ch3_irq : 1;  // [3], read only
        REG32 ch4_irq : 1;  // [4], read only
        REG32 ch5_irq : 1;  // [5], read only
        REG32 ch6_irq : 1;  // [6], read only
        REG32 ch7_irq : 1;  // [7], read only
        REG32 ch8_irq : 1;  // [8], read only
        REG32 ch9_irq : 1;  // [9], read only
        REG32 ch10_irq : 1; // [10], read only
        REG32 ch11_irq : 1; // [11], read only
        REG32 __31_12 : 20;
    } b;
} REG_ARM_AXIDMA_AXIDMA_IRQ_STAT_T;

//AXIDMA_ARM_REQ_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 irq0 : 1;  // [0], read only
        REG32 irq1 : 1;  // [1], read only
        REG32 irq2 : 1;  // [2], read only
        REG32 irq3 : 1;  // [3], read only
        REG32 irq4 : 1;  // [4], read only
        REG32 irq5 : 1;  // [5], read only
        REG32 irq6 : 1;  // [6], read only
        REG32 irq7 : 1;  // [7], read only
        REG32 irq8 : 1;  // [8], read only
        REG32 irq9 : 1;  // [9], read only
        REG32 irq10 : 1; // [10], read only
        REG32 irq11 : 1; // [11], read only
        REG32 irq12 : 1; // [12], read only
        REG32 irq13 : 1; // [13], read only
        REG32 irq14 : 1; // [14], read only
        REG32 irq15 : 1; // [15], read only
        REG32 irq16 : 1; // [16], read only
        REG32 irq17 : 1; // [17], read only
        REG32 irq18 : 1; // [18], read only
        REG32 irq19 : 1; // [19], read only
        REG32 irq20 : 1; // [20], read only
        REG32 irq21 : 1; // [21], read only
        REG32 irq22 : 1; // [22], read only
        REG32 irq23 : 1; // [23], read only
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_ARM_REQ_STAT_T;

//AXIDMA_ARM_ACK_STAT
typedef union {
    REG32 v;
    struct
    {
        REG32 ack0 : 1;  // [0], read only
        REG32 ack1 : 1;  // [1], read only
        REG32 ack2 : 1;  // [2], read only
        REG32 ack3 : 1;  // [3], read only
        REG32 ack4 : 1;  // [4], read only
        REG32 ack5 : 1;  // [5], read only
        REG32 ack6 : 1;  // [6], read only
        REG32 ack7 : 1;  // [7], read only
        REG32 ack8 : 1;  // [8], read only
        REG32 ack9 : 1;  // [9], read only
        REG32 ack10 : 1; // [10], read only
        REG32 ack11 : 1; // [11], read only
        REG32 ack12 : 1; // [12], read only
        REG32 ack13 : 1; // [13], read only
        REG32 ack14 : 1; // [14], read only
        REG32 ack15 : 1; // [15], read only
        REG32 ack16 : 1; // [16], read only
        REG32 ack17 : 1; // [17], read only
        REG32 ack18 : 1; // [18], read only
        REG32 ack19 : 1; // [19], read only
        REG32 ack20 : 1; // [20], read only
        REG32 ack21 : 1; // [21], read only
        REG32 ack22 : 1; // [22], read only
        REG32 ack23 : 1; // [23], read only
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_ARM_ACK_STAT_T;

//AXIDMA_ZSP_REQ_STAT0
typedef union {
    REG32 v;
    struct
    {
        REG32 req0 : 3;        // [2:0]
        REG32 reserved8_7 : 1; // [3], read only
        REG32 req1 : 3;        // [6:4]
        REG32 reserved7_6 : 1; // [7], read only
        REG32 req2 : 3;        // [10:8]
        REG32 reserved6_5 : 1; // [11], read only
        REG32 req3 : 3;        // [14:12]
        REG32 reserved5_4 : 1; // [15], read only
        REG32 req4 : 3;        // [18:16]
        REG32 reserved4_3 : 1; // [19], read only
        REG32 req5 : 3;        // [22:20]
        REG32 reserved3_2 : 1; // [23], read only
        REG32 req6 : 3;        // [26:24]
        REG32 reserved2_1 : 1; // [27], read only
        REG32 req7 : 3;        // [30:28]
        REG32 reserved1_0 : 1; // [31], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_ZSP_REQ_STAT0_T;

//AXIDMA_ZSP_REQ_STAT1
typedef union {
    REG32 v;
    struct
    {
        REG32 req8 : 3;         // [2:0]
        REG32 reserved4_3 : 1;  // [3], read only
        REG32 req9 : 3;         // [6:4]
        REG32 reserved3_2 : 1;  // [7], read only
        REG32 req10 : 3;        // [10:8]
        REG32 reserved2_1 : 1;  // [11], read only
        REG32 req11 : 3;        // [14:12]
        REG32 reserved1_0 : 17; // [31:15], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_ZSP_REQ_STAT1_T;

//AXIDMA_CH_IRQ_DISTR
typedef union {
    REG32 v;
    struct
    {
        REG32 ch0_irq_en0 : 1;  // [0]
        REG32 ch1_irq_en0 : 1;  // [1]
        REG32 ch2_irq_en0 : 1;  // [2]
        REG32 ch3_irq_en0 : 1;  // [3]
        REG32 ch4_irq_en0 : 1;  // [4]
        REG32 ch5_irq_en0 : 1;  // [5]
        REG32 ch6_irq_en0 : 1;  // [6]
        REG32 ch7_irq_en0 : 1;  // [7]
        REG32 ch8_irq_en0 : 1;  // [8]
        REG32 ch9_irq_en0 : 1;  // [9]
        REG32 ch10_irq_en0 : 1; // [10]
        REG32 ch11_irq_en0 : 1; // [11]
        REG32 __31_12 : 20;
    } b;
} REG_ARM_AXIDMA_AXIDMA_CH_IRQ_DISTR_T;

//AXIDMA_C0_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C0_CONF_T;

//AXIDMA_C0_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C0_MAP_T;

//AXIDMA_C0_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C0_COUNT_T;

//AXIDMA_C0_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C0_COUNTP_T;

//AXIDMA_C0_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C0_STATUS_T;

//AXIDMA_C0_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C0_SGCONF_T;

//AXIDMA_C0_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C0_SET_T;

//AXIDMA_C0_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C0_CLR_T;

//AXIDMA_C1_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C1_CONF_T;

//AXIDMA_C1_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C1_MAP_T;

//AXIDMA_C1_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C1_COUNT_T;

//AXIDMA_C1_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C1_COUNTP_T;

//AXIDMA_C1_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C1_STATUS_T;

//AXIDMA_C1_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C1_SGCONF_T;

//AXIDMA_C1_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C1_SET_T;

//AXIDMA_C1_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C1_CLR_T;

//AXIDMA_C2_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C2_CONF_T;

//AXIDMA_C2_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C2_MAP_T;

//AXIDMA_C2_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C2_COUNT_T;

//AXIDMA_C2_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C2_COUNTP_T;

//AXIDMA_C2_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C2_STATUS_T;

//AXIDMA_C2_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C2_SGCONF_T;

//AXIDMA_C2_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C2_SET_T;

//AXIDMA_C2_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C2_CLR_T;

//AXIDMA_C3_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C3_CONF_T;

//AXIDMA_C3_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C3_MAP_T;

//AXIDMA_C3_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C3_COUNT_T;

//AXIDMA_C3_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C3_COUNTP_T;

//AXIDMA_C3_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C3_STATUS_T;

//AXIDMA_C3_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C3_SGCONF_T;

//AXIDMA_C3_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C3_SET_T;

//AXIDMA_C3_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C3_CLR_T;

//AXIDMA_C4_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C4_CONF_T;

//AXIDMA_C4_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C4_MAP_T;

//AXIDMA_C4_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C4_COUNT_T;

//AXIDMA_C4_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C4_COUNTP_T;

//AXIDMA_C4_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C4_STATUS_T;

//AXIDMA_C4_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C4_SGCONF_T;

//AXIDMA_C4_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C4_SET_T;

//AXIDMA_C4_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C4_CLR_T;

//AXIDMA_C5_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C5_CONF_T;

//AXIDMA_C5_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C5_MAP_T;

//AXIDMA_C5_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C5_COUNT_T;

//AXIDMA_C5_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C5_COUNTP_T;

//AXIDMA_C5_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C5_STATUS_T;

//AXIDMA_C5_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C5_SGCONF_T;

//AXIDMA_C5_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C5_SET_T;

//AXIDMA_C5_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C5_CLR_T;

//AXIDMA_C6_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C6_CONF_T;

//AXIDMA_C6_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C6_MAP_T;

//AXIDMA_C6_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C6_COUNT_T;

//AXIDMA_C6_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C6_COUNTP_T;

//AXIDMA_C6_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C6_STATUS_T;

//AXIDMA_C6_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C6_SGCONF_T;

//AXIDMA_C6_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C6_SET_T;

//AXIDMA_C6_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C6_CLR_T;

//AXIDMA_C7_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C7_CONF_T;

//AXIDMA_C7_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C7_MAP_T;

//AXIDMA_C7_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C7_COUNT_T;

//AXIDMA_C7_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C7_COUNTP_T;

//AXIDMA_C7_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C7_STATUS_T;

//AXIDMA_C7_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C7_SGCONF_T;

//AXIDMA_C7_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C7_SET_T;

//AXIDMA_C7_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C7_CLR_T;

//AXIDMA_C8_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C8_CONF_T;

//AXIDMA_C8_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C8_MAP_T;

//AXIDMA_C8_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C8_COUNT_T;

//AXIDMA_C8_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C8_COUNTP_T;

//AXIDMA_C8_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C8_STATUS_T;

//AXIDMA_C8_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C8_SGCONF_T;

//AXIDMA_C8_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C8_SET_T;

//AXIDMA_C8_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C8_CLR_T;

//AXIDMA_C9_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C9_CONF_T;

//AXIDMA_C9_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C9_MAP_T;

//AXIDMA_C9_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C9_COUNT_T;

//AXIDMA_C9_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C9_COUNTP_T;

//AXIDMA_C9_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C9_STATUS_T;

//AXIDMA_C9_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C9_SGCONF_T;

//AXIDMA_C9_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C9_SET_T;

//AXIDMA_C9_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C9_CLR_T;

//AXIDMA_C10_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C10_CONF_T;

//AXIDMA_C10_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C10_MAP_T;

//AXIDMA_C10_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C10_COUNT_T;

//AXIDMA_C10_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C10_COUNTP_T;

//AXIDMA_C10_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C10_STATUS_T;

//AXIDMA_C10_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C10_SGCONF_T;

//AXIDMA_C10_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C10_SET_T;

//AXIDMA_C10_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C10_CLR_T;

//AXIDMA_C11_CONF
typedef union {
    REG32 v;
    struct
    {
        REG32 start : 1;            // [0]
        REG32 data_type : 2;        // [2:1]
        REG32 syn_irq : 1;          // [3]
        REG32 irq_f : 1;            // [4]
        REG32 irq_t : 1;            // [5]
        REG32 saddr_fix : 1;        // [6]
        REG32 daddr_fix : 1;        // [7]
        REG32 force_trans : 1;      // [8]
        REG32 req_sel : 1;          // [9]
        REG32 count_sel : 1;        // [10]
        REG32 zsp_dma_ack_en : 1;   // [11]
        REG32 saddr_turnaround : 1; // [12]
        REG32 daddr_turnaround : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C11_CONF_T;

//AXIDMA_C11_MAP
typedef union {
    REG32 v;
    struct
    {
        REG32 req_source : 5;   // [4:0]
        REG32 reserved2_1 : 3;  // [7:5], read only
        REG32 ack_map : 5;      // [12:8]
        REG32 reserved1_0 : 19; // [31:13], read only
    } b;
} REG_ARM_AXIDMA_AXIDMA_C11_MAP_T;

//AXIDMA_C11_COUNT
typedef union {
    REG32 v;
    struct
    {
        REG32 count : 24; // [23:0]
        REG32 __31_24 : 8;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C11_COUNT_T;

//AXIDMA_C11_COUNTP
typedef union {
    REG32 v;
    struct
    {
        REG32 countp : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C11_COUNTP_T;

//AXIDMA_C11_STATUS
typedef union {
    REG32 v;
    struct
    {
        REG32 run : 1;               // [0], write clear
        REG32 count_finish : 1;      // [1], write clear
        REG32 countp_finish : 1;     // [2], write clear
        REG32 sg_finish : 1;         // [3], write clear
        REG32 sg_count : 16;         // [19:4], write clear
        REG32 sg_suspend : 1;        // [20], write clear
        REG32 count_finish_sta : 1;  // [21], write clear
        REG32 countp_finish_sta : 1; // [22], write clear
        REG32 sg_finish_sta : 1;     // [23], write clear
        REG32 sg_suspend_sta : 1;    // [24], write clear
        REG32 __31_25 : 7;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C11_STATUS_T;

//AXIDMA_C11_SGCONF
typedef union {
    REG32 v;
    struct
    {
        REG32 sg_en : 1;         // [0], write clear
        REG32 sg_finish_ie : 1;  // [1]
        REG32 sg_suspend_ie : 1; // [2]
        REG32 desc_rd_ctrl : 1;  // [3]
        REG32 sg_num : 16;       // [19:4]
        REG32 __31_20 : 12;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C11_SGCONF_T;

//AXIDMA_C11_SET
typedef union {
    REG32 v;
    struct
    {
        REG32 run_set : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C11_SET_T;

//AXIDMA_C11_CLR
typedef union {
    REG32 v;
    struct
    {
        REG32 run_clr : 1; // [0]
        REG32 __31_1 : 31;
    } b;
} REG_ARM_AXIDMA_AXIDMA_C11_CLR_T;

#endif
