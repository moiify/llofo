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

#ifndef _WCN_BT_LINK_H_
#define _WCN_BT_LINK_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'wcn_bt_link'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// WCN_BT_LINK_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_WCN_BT_REG_BASE 0x14100000

typedef volatile struct
{
    REG32 rwbtcnt;               //0x00000000
    REG32 version;               //0x00000004
    REG32 rwbtconf;              //0x00000008
    REG32 intcntl;               //0x0000000C
    REG32 intstat;               //0x00000010
    REG32 intrawstat;            //0x00000014
    REG32 intack;                //0x00000018
    REG32 slotclk;               //0x0000001C
    REG32 finetimecnt;           //0x00000020
    REG32 abtraincnt;            //0x00000024
    REG32 edrcntl_nwinsize;      //0x00000028
    REG32 et_currentrxdescptr;   //0x0000002C
    REG32 deepslcntl;            //0x00000030
    REG32 deepslwkup;            //0x00000034
    REG32 deepslstat;            //0x00000038
    REG32 enbpreset;             //0x0000003C
    REG32 finecntcorr;           //0x00000040
    REG32 clkncntcorr;           //0x00000044
    REG32 tokencntl;             //0x00000048
    REG32 Reserved_0000004C;     //0x0000004C
    REG32 diagcntl;              //0x00000050
    REG32 diagstat;              //0x00000054
    REG32 debugaddmax;           //0x00000058
    REG32 debugaddmin;           //0x0000005C
    REG32 errortypestat;         //0x00000060
    REG32 swprofiling;           //0x00000064
    REG32 Reserved_00000068[2];  //0x00000068
    REG32 radiocntl0;            //0x00000070
    REG32 radiocntl1;            //0x00000074
    REG32 radiocntl2;            //0x00000078
    REG32 radiocntl3;            //0x0000007C
    REG32 radiopwrupdn;          //0x00000080
    REG32 Reserved_00000084[3];  //0x00000084
    REG32 txmicval;              //0x00000090
    REG32 rxmicval;              //0x00000094
    REG32 e0ptr;                 //0x00000098
    REG32 Reserved_0000009C;     //0x0000009C
    REG32 rftestcntl;            //0x000000A0
    REG32 rftestfreq;            //0x000000A4
    REG32 Reserved_000000A8[2];  //0x000000A8
    REG32 timgencntl;            //0x000000B0
    REG32 grosstimtgt;           //0x000000B4
    REG32 finetimtgt;            //0x000000B8
    REG32 sketclkn;              //0x000000BC
    REG32 pcacntl0;              //0x000000C0
    REG32 pcacntl1;              //0x000000C4
    REG32 pcastat;               //0x000000C8
    REG32 Reserved_000000CC[29]; //0x000000CC
    REG32 escochancntl0;         //0x00000140
    REG32 escomutecntl0;         //0x00000144
    REG32 escocurrenttxptr0;     //0x00000148
    REG32 escocurrentrxptr0;     //0x0000014C
    REG32 escoltcntl0;           //0x00000150
    REG32 escotrcntl0;           //0x00000154
    REG32 escodaycnt0;           //0x00000158
    REG32 Reserved_0000015C;     //0x0000015C
    REG32 escochancntl1;         //0x00000160
    REG32 escomutecntl1;         //0x00000164
    REG32 escocurrenttxptr1;     //0x00000168
    REG32 escocurrentrxptr1;     //0x0000016C
    REG32 escoltcntl1;           //0x00000170
    REG32 escotrcntl1;           //0x00000174
    REG32 escodaycnt1;           //0x00000178
    REG32 Reserved_0000017C;     //0x0000017C
    REG32 escochancntl2;         //0x00000180
    REG32 escomutecntl2;         //0x00000184
    REG32 escocurrenttxptr2;     //0x00000188
    REG32 escocurrentrxptr2;     //0x0000018C
    REG32 escoltcntl2;           //0x00000190
    REG32 escotrcntl2;           //0x00000194
    REG32 escodaycnt2;           //0x00000198
    REG32 Reserved_0000019C;     //0x0000019C
    REG32 audiocntl0;            //0x000001A0
    REG32 audiocntl1;            //0x000001A4
    REG32 audiocntl2;            //0x000001A8
    REG32 Reserved_000001AC;     //0x000001AC
    REG32 pcmgencntl;            //0x000001B0
    REG32 pcmphyscntl0;          //0x000001B4
    REG32 pcmphyscntl1;          //0x000001B8
    REG32 pcmpadding;            //0x000001BC
    REG32 pcmpllcntl0;           //0x000001C0
    REG32 pcmpllcntl1;           //0x000001C4
    REG32 pcmpllcntl2;           //0x000001C8
    REG32 pcmsourceptr;          //0x000001CC
    REG32 pcmsinkptr;            //0x000001D0
    REG32 Reserved_000001D4[3];  //0x000001D4
    REG32 bredrprioscharb;       //0x000001E0
    REG32 plcaddr01;             //0x000001E4
    REG32 plcaddr23;             //0x000001E8
    REG32 plcaddr45;             //0x000001EC
    REG32 plcaddr67;             //0x000001F0
    REG32 plcaddr89;             //0x000001F4
    REG32 plcaddrb;              //0x000001F8
    REG32 plcconf;               //0x000001FC
} HWP_WCN_BT_LINK_T;

#define hwp_wcnBtReg ((HWP_WCN_BT_LINK_T *)REG_ACCESS_ADDRESS(REG_WCN_BT_REG_BASE))

//rwbtcnt
typedef union {
    REG32 v;
    struct
    {
        REG32 syncerr : 4; // [3:0]
        REG32 __7_4 : 4;
        REG32 rwbten : 1; // [8]
        REG32 __11_9 : 3;
        REG32 cx_dnabort : 1;  // [12]
        REG32 cx_rxbsyena : 1; // [13]
        REG32 cx_txbsyena : 1; // [14]
        REG32 seqndsb : 1;     // [15]
        REG32 hopdsb : 1;      // [16]
        REG32 crcdsb : 1;      // [17]
        REG32 arqndsb : 1;     // [18]
        REG32 whitdsb : 1;     // [19]
        REG32 cryptdsb : 1;    // [20]
        REG32 lmpflowdsb : 1;  // [21]
        REG32 __22_22 : 1;
        REG32 flowdsb : 1;           // [23]
        REG32 sniff_abort : 1;       // [24]
        REG32 pageinq_abort : 1;     // [25]
        REG32 rftest_abort : 1;      // [26]
        REG32 scan_abort : 1;        // [27]
        REG32 swint_req : 1;         // [28]
        REG32 reg_soft_rst : 1;      // [29]
        REG32 master_tgsoft_rst : 1; // [30]
        REG32 master_soft_rst : 1;   // [31]
    } b;
} REG_WCN_BT_LINK_RWBTCNT_T;

//version
typedef union {
    REG32 v;
    struct
    {
        REG32 build_num : 8; // [7:0], read only
        REG32 upg : 8;       // [15:8], read only
        REG32 rel : 8;       // [23:16], read only
        REG32 typ : 8;       // [31:24], read only
    } b;
} REG_WCN_BT_LINK_VERSION_T;

//rwbtconf
typedef union {
    REG32 v;
    struct
    {
        REG32 addr_width : 5; // [4:0], read only
        REG32 data_width : 1; // [5], read only
        REG32 bus_type : 1;   // [6], read only
        REG32 intmode : 1;    // [7], read only
        REG32 clk_sel : 6;    // [13:8], read only
        REG32 usecrypt : 1;   // [14], read only
        REG32 usedbg : 1;     // [15], read only
        REG32 rfif : 5;       // [20:16], read only
        REG32 wlancoex : 1;   // [21], read only
        REG32 mwscoex : 1;    // [22], read only
        REG32 pcm : 1;        // [23], read only
        REG32 vxportnb : 2;   // [25:24], read only
        REG32 mwswci1 : 1;    // [26], read only
        REG32 mwswci2 : 1;    // [27], read only
        REG32 __30_28 : 3;
        REG32 dmmode : 1; // [31], read only
    } b;
} REG_WCN_BT_LINK_RWBTCONF_T;

//intcntl
typedef union {
    REG32 v;
    struct
    {
        REG32 clknintmsk : 1;      // [0]
        REG32 rxintmsk : 1;        // [1]
        REG32 slpintmsk : 1;       // [2]
        REG32 audioint0msk : 1;    // [3]
        REG32 audioint1msk : 1;    // [4]
        REG32 audioint2msk : 1;    // [5]
        REG32 frsyncintmsk : 1;    // [6]
        REG32 mtoffint0msk : 1;    // [7]
        REG32 mtoffint1msk : 1;    // [8]
        REG32 finetgtintmsk : 1;   // [9]
        REG32 grosstgtintmsk : 1;  // [10]
        REG32 errorintmsk : 1;     // [11]
        REG32 mwswcitxintmsk : 1;  // [12]
        REG32 mwswcirxintmsk : 1;  // [13]
        REG32 frameintmsk : 1;     // [14]
        REG32 frameapfaintmsk : 1; // [15]
        REG32 swintmsk : 1;        // [16]
        REG32 sketintmsk : 1;      // [17]
        REG32 __31_18 : 14;
    } b;
} REG_WCN_BT_LINK_INTCNTL_T;

//intstat
typedef union {
    REG32 v;
    struct
    {
        REG32 clknintstat : 1;      // [0], read only
        REG32 rxintstat : 1;        // [1], read only
        REG32 slpintstat : 1;       // [2], read only
        REG32 audioint0stat : 1;    // [3], read only
        REG32 audioint1stat : 1;    // [4], read only
        REG32 audioint2stat : 1;    // [5], read only
        REG32 frsyncintstat : 1;    // [6], read only
        REG32 mtoffint0stat : 1;    // [7], read only
        REG32 mtoffint1stat : 1;    // [8], read only
        REG32 finetgtintstat : 1;   // [9], read only
        REG32 grosstgtintstat : 1;  // [10], read only
        REG32 errorintstat : 1;     // [11], read only
        REG32 mwswcitxintstat : 1;  // [12], read only
        REG32 mwswcirxintstat : 1;  // [13], read only
        REG32 frameintstat : 1;     // [14], read only
        REG32 frameapfaintstat : 1; // [15], read only
        REG32 swintstat : 1;        // [16], read only
        REG32 sketintstat : 1;      // [17], read only
        REG32 __31_18 : 14;
    } b;
} REG_WCN_BT_LINK_INTSTAT_T;

//intrawstat
typedef union {
    REG32 v;
    struct
    {
        REG32 clknintrawstat : 1;      // [0], read only
        REG32 rxintrawstat : 1;        // [1], read only
        REG32 slpintrawstat : 1;       // [2], read only
        REG32 audioint0rawstat : 1;    // [3], read only
        REG32 audioint1rawstat : 1;    // [4], read only
        REG32 audioint2rawstat : 1;    // [5], read only
        REG32 frsyncintrawstat : 1;    // [6], read only
        REG32 mtoffint0rawstat : 1;    // [7], read only
        REG32 mtoffint1rawstat : 1;    // [8], read only
        REG32 finetgtintrawstat : 1;   // [9], read only
        REG32 grosstgtintrawstat : 1;  // [10], read only
        REG32 errorintrawstat : 1;     // [11], read only
        REG32 mwswcitxintrawstat : 1;  // [12], read only
        REG32 mwswcirxintrawstat : 1;  // [13], read only
        REG32 frameintrawstat : 1;     // [14], read only
        REG32 frameapfaintrawstat : 1; // [15], read only
        REG32 swintrawstat : 1;        // [16], read only
        REG32 sketintrawstat : 1;      // [17], read only
        REG32 __31_18 : 14;
    } b;
} REG_WCN_BT_LINK_INTRAWSTAT_T;

//intack
typedef union {
    REG32 v;
    struct
    {
        REG32 clknintack : 1;      // [0], write set
        REG32 rxintack : 1;        // [1], write set
        REG32 slpintack : 1;       // [2], write set
        REG32 audioint0ack : 1;    // [3], write set
        REG32 audioint1ack : 1;    // [4], write set
        REG32 audioint2ack : 1;    // [5], write set
        REG32 frsyncintack : 1;    // [6], write set
        REG32 mtoffint0ack : 1;    // [7], write set
        REG32 mtoffint1ack : 1;    // [8], write set
        REG32 finetgtintack : 1;   // [9], write set
        REG32 grosstgtintack : 1;  // [10], write set
        REG32 errorintack : 1;     // [11], write set
        REG32 mwswcitxintack : 1;  // [12], write set
        REG32 mwswcirxintack : 1;  // [13], write set
        REG32 frameintack : 1;     // [14], write set
        REG32 frameapfaintack : 1; // [15], write set
        REG32 swintack : 1;        // [16], write set
        REG32 sketintack : 1;      // [17], write set
        REG32 __31_18 : 14;
    } b;
} REG_WCN_BT_LINK_INTACK_T;

//slotclk
typedef union {
    REG32 v;
    struct
    {
        REG32 sclk : 28; // [27:0]
        REG32 __29_28 : 2;
        REG32 clkn_upd : 1; // [30]
        REG32 samp : 1;     // [31]
    } b;
} REG_WCN_BT_LINK_SLOTCLK_T;

//finetimecnt
typedef union {
    REG32 v;
    struct
    {
        REG32 finecnt : 10; // [9:0], read only
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_LINK_FINETIMECNT_T;

//abtraincnt
typedef union {
    REG32 v;
    struct
    {
        REG32 abtinqtime : 11; // [10:0]
        REG32 __11_11 : 1;
        REG32 abtinqload : 1; // [12]
        REG32 __13_13 : 1;
        REG32 abtinqstartvalue : 1; // [14]
        REG32 abtinqen : 1;         // [15]
        REG32 abtpagetime : 11;     // [26:16]
        REG32 __27_27 : 1;
        REG32 abtpageload : 1; // [28]
        REG32 __29_29 : 1;
        REG32 abtpagestartvalue : 1; // [30]
        REG32 abtpageen : 1;         // [31]
    } b;
} REG_WCN_BT_LINK_ABTRAINCNT_T;

//edrcntl_nwinsize
typedef union {
    REG32 v;
    struct
    {
        REG32 rxgrd_timeout : 10; // [9:0]
        REG32 __12_10 : 3;
        REG32 rx_swap : 1;    // [13]
        REG32 tx_swap : 1;    // [14]
        REG32 rxguarddsb : 1; // [15]
        REG32 edrbcast : 1;   // [16]
        REG32 __23_17 : 7;
        REG32 nwinsize : 8; // [31:24]
    } b;
} REG_WCN_BT_LINK_EDRCNTL_NWINSIZE_T;

//et_currentrxdescptr
typedef union {
    REG32 v;
    struct
    {
        REG32 currentrxdescptr : 15; // [14:0]
        REG32 __15_15 : 1;
        REG32 etptr : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_ET_CURRENTRXDESCPTR_T;

//deepslcntl
typedef union {
    REG32 v;
    struct
    {
        REG32 osc_sleep_en : 1;       // [0]
        REG32 radio_sleep_en : 1;     // [1]
        REG32 deep_sleep_on : 1;      // [2]
        REG32 deep_sleep_corr_en : 1; // [3]
        REG32 soft_wakeup_req : 1;    // [4]
        REG32 __14_5 : 10;
        REG32 deep_sleep_stat : 1; // [15], read only
        REG32 __27_16 : 12;
        REG32 ext_activity_wakeup_en : 1; // [28]
        REG32 ext_low_wakeup_en : 1;      // [29]
        REG32 ext_high_wakeup_en : 1;     // [30]
        REG32 extwkupdsb : 1;             // [31]
    } b;
} REG_WCN_BT_LINK_DEEPSLCNTL_T;

//enbpreset
typedef union {
    REG32 v;
    struct
    {
        REG32 twrm : 10;  // [9:0]
        REG32 twosc : 11; // [20:10]
        REG32 twext : 11; // [31:21]
    } b;
} REG_WCN_BT_LINK_ENBPRESET_T;

//finecntcorr
typedef union {
    REG32 v;
    struct
    {
        REG32 finecntcorr : 10; // [9:0]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_LINK_FINECNTCORR_T;

//clkncntcorr
typedef union {
    REG32 v;
    struct
    {
        REG32 clkncntcorr : 28; // [27:0]
        REG32 __30_28 : 3;
        REG32 abs_delta : 1; // [31]
    } b;
} REG_WCN_BT_LINK_CLKNCNTCORR_T;

//tokencntl
typedef union {
    REG32 v;
    struct
    {
        REG32 observer_en : 1;     // [0]
        REG32 observer_active : 1; // [1]
        REG32 arbiter_en : 1;      // [2]
        REG32 arbiter_bypass : 1;  // [3]
        REG32 __7_4 : 4;
        REG32 token_rxwin : 7;      // [14:8]
        REG32 token_quick_sync : 1; // [15]
        REG32 token_rx_delay : 6;   // [21:16]
        REG32 __23_22 : 2;
        REG32 token_tx_delay : 6; // [29:24]
        REG32 __31_30 : 2;
    } b;
} REG_WCN_BT_LINK_TOKENCNTL_T;

//diagcntl
typedef union {
    REG32 v;
    struct
    {
        REG32 diag0 : 6; // [5:0]
        REG32 __6_6 : 1;
        REG32 diag0_en : 1; // [7]
        REG32 diag1 : 6;    // [13:8]
        REG32 __14_14 : 1;
        REG32 diag1_en : 1; // [15]
        REG32 diag2 : 6;    // [21:16]
        REG32 __22_22 : 1;
        REG32 diag2_en : 1; // [23]
        REG32 diag3 : 6;    // [29:24]
        REG32 __30_30 : 1;
        REG32 diag3_en : 1; // [31]
    } b;
} REG_WCN_BT_LINK_DIAGCNTL_T;

//diagstat
typedef union {
    REG32 v;
    struct
    {
        REG32 diag0stat : 8; // [7:0], read only
        REG32 diag1stat : 8; // [15:8], read only
        REG32 diag2stat : 8; // [23:16], read only
        REG32 diag3stat : 8; // [31:24], read only
    } b;
} REG_WCN_BT_LINK_DIAGSTAT_T;

//debugaddmax
typedef union {
    REG32 v;
    struct
    {
        REG32 em_addmax : 16;  // [15:0]
        REG32 reg_addmax : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_DEBUGADDMAX_T;

//debugaddmin
typedef union {
    REG32 v;
    struct
    {
        REG32 em_addmin : 16;  // [15:0]
        REG32 reg_addmin : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_DEBUGADDMIN_T;

//errortypestat
typedef union {
    REG32 v;
    struct
    {
        REG32 txcrypt_error : 1;         // [0], read only
        REG32 rxcrypt_error : 1;         // [1], read only
        REG32 cryptmode_error : 1;       // [2], read only
        REG32 pktcntl_emacc_error : 1;   // [3], read only
        REG32 radiocntl_emacc_error : 1; // [4], read only
        REG32 audio_emacc_error : 1;     // [5], read only
        REG32 pcm_emacc_error : 1;       // [6], read only
        REG32 frm_schdl_emacc_error : 1; // [7], read only
        REG32 mwswci_emacc_error : 1;    // [8], read only
        REG32 frm_schdl_entry_error : 1; // [9], read only
        REG32 frm_schdl_apfm_error : 1;  // [10], read only
        REG32 frm_cntl_apfm_error : 1;   // [11], read only
        REG32 frm_cntl_emacc_error : 1;  // [12], read only
        REG32 frm_cntl_timer_error : 1;  // [13], read only
        REG32 hopunderrun_error : 1;     // [14], read only
        REG32 chmap_error : 1;           // [15], read only
        REG32 csformat_error : 1;        // [16], read only
        REG32 csattnb_error : 1;         // [17], read only
        REG32 txdesc_empty_error : 1;    // [18], read only
        REG32 rxdesc_empty_error : 1;    // [19], read only
        REG32 txbuf_ptr_error : 1;       // [20], read only
        REG32 rxbuf_ptr_error : 1;       // [21], read only
        REG32 __31_22 : 10;
    } b;
} REG_WCN_BT_LINK_ERRORTYPESTAT_T;

//radiocntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 spigo : 1;   // [0]
        REG32 spicomp : 1; // [1], read only
        REG32 __4_2 : 3;
        REG32 spifreq : 2; // [6:5]
        REG32 __20_7 : 14;
        REG32 forceagc_en : 1;     // [21]
        REG32 dpcorr_en : 1;       // [22]
        REG32 sync_pulse_mode : 1; // [23]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_BT_LINK_RADIOCNTL0_T;

//radiocntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 spiptr : 16; // [15:0]
        REG32 xrfsel : 5;  // [20:16]
        REG32 __31_21 : 11;
    } b;
} REG_WCN_BT_LINK_RADIOCNTL1_T;

//radiocntl2
typedef union {
    REG32 v;
    struct
    {
        REG32 forceagc_length : 12; // [11:0]
        REG32 __15_12 : 4;
        REG32 sync_position : 7; // [22:16]
        REG32 __23_23 : 1;
        REG32 tx_delay : 8; // [31:24]
    } b;
} REG_WCN_BT_LINK_RADIOCNTL2_T;

//radiocntl3
typedef union {
    REG32 v;
    struct
    {
        REG32 freqtable_ptr : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_LINK_RADIOCNTL3_T;

//radiopwrupdn
typedef union {
    REG32 v;
    struct
    {
        REG32 txpwrupct : 8; // [7:0]
        REG32 txpwrdnct : 5; // [12:8]
        REG32 __15_13 : 3;
        REG32 rxpwrupct : 8;   // [23:16]
        REG32 rtrip_delay : 7; // [30:24]
        REG32 __31_31 : 1;
    } b;
} REG_WCN_BT_LINK_RADIOPWRUPDN_T;

//e0ptr
typedef union {
    REG32 v;
    struct
    {
        REG32 e0ptr : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_LINK_E0PTR_T;

//rftestcntl
typedef union {
    REG32 v;
    struct
    {
        REG32 txpldsrc : 1;       // [0]
        REG32 prbstype : 1;       // [1]
        REG32 infinitetx : 1;     // [2]
        REG32 infinite_entry : 1; // [3]
        REG32 __6_4 : 3;
        REG32 infiniterx : 1; // [7]
        REG32 __15_8 : 8;
        REG32 herrren : 1;  // [16]
        REG32 sserrren : 1; // [17]
        REG32 __31_18 : 14;
    } b;
} REG_WCN_BT_LINK_RFTESTCNTL_T;

//rftestfreq
typedef union {
    REG32 v;
    struct
    {
        REG32 txfreq : 7; // [6:0]
        REG32 __7_7 : 1;
        REG32 rxfreq : 7; // [14:8]
        REG32 __15_15 : 1;
        REG32 testmodeen : 1;      // [16]
        REG32 directlopbacken : 1; // [17]
        REG32 __31_18 : 14;
    } b;
} REG_WCN_BT_LINK_RFTESTFREQ_T;

//timgencntl
typedef union {
    REG32 v;
    struct
    {
        REG32 prefetch_time : 9; // [8:0]
        REG32 __15_9 : 7;
        REG32 prefetchabort_time : 10; // [25:16]
        REG32 __30_26 : 5;
        REG32 apfm_en : 1; // [31]
    } b;
} REG_WCN_BT_LINK_TIMGENCNTL_T;

//grosstimtgt
typedef union {
    REG32 v;
    struct
    {
        REG32 grosstarget : 23; // [22:0]
        REG32 __31_23 : 9;
    } b;
} REG_WCN_BT_LINK_GROSSTIMTGT_T;

//finetimtgt
typedef union {
    REG32 v;
    struct
    {
        REG32 finetarget : 27; // [26:0]
        REG32 __31_27 : 5;
    } b;
} REG_WCN_BT_LINK_FINETIMTGT_T;

//sketclkn
typedef union {
    REG32 v;
    struct
    {
        REG32 sketclkn : 28; // [27:0], read only
        REG32 __31_28 : 4;
    } b;
} REG_WCN_BT_LINK_SKETCLKN_T;

//pcacntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 phase_shift_en : 1; // [0]
        REG32 sync_source : 1;    // [1]
        REG32 frsync_pol : 1;     // [2]
        REG32 blindcorr_en : 1;   // [3]
        REG32 corr_step : 4;      // [7:4]
        REG32 slvlbl : 5;         // [12:8]
        REG32 __15_13 : 3;
        REG32 target_offset : 11; // [26:16]
        REG32 __31_27 : 5;
    } b;
} REG_WCN_BT_LINK_PCACNTL0_T;

//pcacntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 clock_shift : 11; // [10:0]
        REG32 __11_11 : 1;
        REG32 clock_shift_en : 1; // [12]
        REG32 __15_13 : 3;
        REG32 corr_interval : 8; // [23:16]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_BT_LINK_PCACNTL1_T;

//pcastat
typedef union {
    REG32 v;
    struct
    {
        REG32 moment_offset : 11; // [10:0], read only
        REG32 __15_11 : 5;
        REG32 shift_phase : 11; // [26:16], read only
        REG32 __31_27 : 5;
    } b;
} REG_WCN_BT_LINK_PCASTAT_T;

//escochancntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 tesco0 : 8;        // [7:0]
        REG32 intdelay0 : 5;     // [12:8]
        REG32 itmode0 : 1;       // [13]
        REG32 escochanen0 : 1;   // [14]
        REG32 escochanswen0 : 1; // [15]
        REG32 __30_16 : 15;
        REG32 tog0 : 1; // [31], read only
    } b;
} REG_WCN_BT_LINK_ESCOCHANCNTL0_T;

//escomutecntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 mutepatt0 : 16; // [15:0]
        REG32 invl0_0 : 2;    // [17:16]
        REG32 invl0_1 : 2;    // [19:18]
        REG32 __21_20 : 2;
        REG32 mute_source0 : 1; // [22]
        REG32 mute_sink0 : 1;   // [23]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_BT_LINK_ESCOMUTECNTL0_T;

//escocurrenttxptr0
typedef union {
    REG32 v;
    struct
    {
        REG32 esco0ptrtx0 : 16; // [15:0]
        REG32 esco0ptrtx1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_ESCOCURRENTTXPTR0_T;

//escocurrentrxptr0
typedef union {
    REG32 v;
    struct
    {
        REG32 esco0ptrrx0 : 16; // [15:0]
        REG32 esco0ptrrx1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_ESCOCURRENTRXPTR0_T;

//escoltcntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 synltaddr0 : 3; // [2:0]
        REG32 syntype0 : 1;   // [3]
        REG32 escoedrtx0 : 1; // [4]
        REG32 escoedrrx0 : 1; // [5]
        REG32 __15_6 : 10;
        REG32 retxnb0 : 8; // [23:16]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_BT_LINK_ESCOLTCNTL0_T;

//escotrcntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 rxtype0 : 4; // [3:0]
        REG32 rxlen0 : 10; // [13:4]
        REG32 __15_14 : 2;
        REG32 txtype0 : 4; // [19:16]
        REG32 txlen0 : 10; // [29:20]
        REG32 __30_30 : 1;
        REG32 txseqn0 : 1; // [31]
    } b;
} REG_WCN_BT_LINK_ESCOTRCNTL0_T;

//escodaycnt0
typedef union {
    REG32 v;
    struct
    {
        REG32 daycounter0 : 11; // [10:0]
        REG32 __31_11 : 21;
    } b;
} REG_WCN_BT_LINK_ESCODAYCNT0_T;

//escochancntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 tesco1 : 8;        // [7:0]
        REG32 intdelay1 : 5;     // [12:8]
        REG32 itmode1 : 1;       // [13]
        REG32 escochanen1 : 1;   // [14]
        REG32 escochanswen1 : 1; // [15]
        REG32 __30_16 : 15;
        REG32 tog1 : 1; // [31], read only
    } b;
} REG_WCN_BT_LINK_ESCOCHANCNTL1_T;

//escomutecntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 mutepatt1 : 16; // [15:0]
        REG32 invl1_0 : 2;    // [17:16]
        REG32 invl1_1 : 2;    // [19:18]
        REG32 __21_20 : 2;
        REG32 mute_source1 : 1; // [22]
        REG32 mute_sink1 : 1;   // [23]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_BT_LINK_ESCOMUTECNTL1_T;

//escocurrenttxptr1
typedef union {
    REG32 v;
    struct
    {
        REG32 esco1ptrtx0 : 16; // [15:0]
        REG32 esco1ptrtx1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_ESCOCURRENTTXPTR1_T;

//escocurrentrxptr1
typedef union {
    REG32 v;
    struct
    {
        REG32 esco1ptrrx0 : 16; // [15:0]
        REG32 esco1ptrrx1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_ESCOCURRENTRXPTR1_T;

//escoltcntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 syntaddr1 : 3;  // [2:0]
        REG32 syntype1 : 1;   // [3]
        REG32 escoedrtx1 : 1; // [4]
        REG32 escoedrrx1 : 1; // [5]
        REG32 __15_6 : 10;
        REG32 retxnb1 : 8; // [23:16]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_BT_LINK_ESCOLTCNTL1_T;

//escotrcntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 rxtype1 : 4; // [3:0]
        REG32 rxlen1 : 10; // [13:4]
        REG32 __15_14 : 2;
        REG32 txtype1 : 4; // [19:16]
        REG32 txlen1 : 10; // [29:20]
        REG32 __30_30 : 1;
        REG32 txseqn1 : 1; // [31]
    } b;
} REG_WCN_BT_LINK_ESCOTRCNTL1_T;

//escodaycnt1
typedef union {
    REG32 v;
    struct
    {
        REG32 daycounter1 : 11; // [10:0]
        REG32 __31_11 : 21;
    } b;
} REG_WCN_BT_LINK_ESCODAYCNT1_T;

//escochancntl2
typedef union {
    REG32 v;
    struct
    {
        REG32 tesco2 : 8;        // [7:0]
        REG32 intdelay2 : 5;     // [12:8]
        REG32 itmode2 : 1;       // [13]
        REG32 escochanen2 : 1;   // [14]
        REG32 escochanswen2 : 1; // [15]
        REG32 __30_16 : 15;
        REG32 tog2 : 1; // [31], read only
    } b;
} REG_WCN_BT_LINK_ESCOCHANCNTL2_T;

//escomutecntl2
typedef union {
    REG32 v;
    struct
    {
        REG32 mutepatt2 : 16; // [15:0]
        REG32 invl2_0 : 2;    // [17:16]
        REG32 invl2_1 : 2;    // [19:18]
        REG32 __21_20 : 2;
        REG32 mute_source2 : 1; // [22]
        REG32 mute_sink2 : 1;   // [23]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_BT_LINK_ESCOMUTECNTL2_T;

//escocurrenttxptr2
typedef union {
    REG32 v;
    struct
    {
        REG32 esco2ptrtx0 : 16; // [15:0]
        REG32 esco2ptrtx1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_ESCOCURRENTTXPTR2_T;

//escocurrentrxptr2
typedef union {
    REG32 v;
    struct
    {
        REG32 esco2ptrrx0 : 16; // [15:0]
        REG32 esco2ptrrx1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_ESCOCURRENTRXPTR2_T;

//escoltcntl2
typedef union {
    REG32 v;
    struct
    {
        REG32 syntaddr2 : 3;  // [2:0]
        REG32 syntype2 : 1;   // [3]
        REG32 escoedrtx2 : 1; // [4]
        REG32 escoedrrx2 : 1; // [5]
        REG32 __15_6 : 10;
        REG32 retxnb2 : 8; // [23:16]
        REG32 __31_24 : 8;
    } b;
} REG_WCN_BT_LINK_ESCOLTCNTL2_T;

//escotrcntl2
typedef union {
    REG32 v;
    struct
    {
        REG32 rxtype2 : 4; // [3:0]
        REG32 rxlen2 : 10; // [13:4]
        REG32 __15_14 : 2;
        REG32 txtype2 : 4; // [19:16]
        REG32 txlen2 : 10; // [29:20]
        REG32 __30_30 : 1;
        REG32 txseqn2 : 1; // [31]
    } b;
} REG_WCN_BT_LINK_ESCOTRCNTL2_T;

//escodaycnt2
typedef union {
    REG32 v;
    struct
    {
        REG32 daycounter2 : 11; // [10:0]
        REG32 __31_11 : 21;
    } b;
} REG_WCN_BT_LINK_ESCODAYCNT2_T;

//audiocntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 cvsd_bitorder0 : 1; // [0]
        REG32 __6_1 : 6;
        REG32 cvsden0 : 1;     // [7]
        REG32 aulaw_code0 : 4; // [11:8]
        REG32 __14_12 : 3;
        REG32 aulawen0 : 1;     // [15]
        REG32 sample_type0 : 2; // [17:16]
        REG32 __19_18 : 2;
        REG32 linear_format0 : 2; // [21:20]
        REG32 __31_22 : 10;
    } b;
} REG_WCN_BT_LINK_AUDIOCNTL0_T;

//audiocntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 cvsd_bitorder1 : 1; // [0]
        REG32 __6_1 : 6;
        REG32 cvsden1 : 1;     // [7]
        REG32 aulaw_code1 : 4; // [11:8]
        REG32 __14_12 : 3;
        REG32 aulawen1 : 1;     // [15]
        REG32 sample_type1 : 2; // [17:16]
        REG32 __19_18 : 2;
        REG32 linear_format1 : 2; // [21:20]
        REG32 __31_22 : 10;
    } b;
} REG_WCN_BT_LINK_AUDIOCNTL1_T;

//audiocntl2
typedef union {
    REG32 v;
    struct
    {
        REG32 cvsd_bitorder2 : 1; // [0]
        REG32 __6_1 : 6;
        REG32 cvsden2 : 1;     // [7]
        REG32 aulaw_code2 : 4; // [11:8]
        REG32 __14_12 : 3;
        REG32 aulawen2 : 1;     // [15]
        REG32 sample_type2 : 2; // [17:16]
        REG32 __19_18 : 2;
        REG32 linear_format2 : 2; // [21:20]
        REG32 __31_22 : 10;
    } b;
} REG_WCN_BT_LINK_AUDIOCNTL2_T;

//pcmgencntl
typedef union {
    REG32 v;
    struct
    {
        REG32 pcmen : 1;       // [0]
        REG32 lrswap : 1;      // [1]
        REG32 byteswap : 1;    // [2]
        REG32 mstslv : 1;      // [3]
        REG32 mono_stereo : 1; // [4]
        REG32 mono_lr_sel : 1; // [5]
        REG32 loopback : 1;    // [6]
        REG32 __7_7 : 1;
        REG32 vxchsel : 2; // [9:8]
        REG32 __31_10 : 22;
    } b;
} REG_WCN_BT_LINK_PCMGENCNTL_T;

//pcmphyscntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 fsyncshp : 3; // [2:0]
        REG32 __3_3 : 1;
        REG32 doutcfg : 2; // [5:4]
        REG32 __7_6 : 2;
        REG32 lrchpol : 1; // [8]
        REG32 pcm_iom : 1; // [9]
        REG32 lsb1st : 1;  // [10]
        REG32 __11_11 : 1;
        REG32 sampsz : 1;   // [12]
        REG32 samptype : 1; // [13]
        REG32 __15_14 : 2;
        REG32 slotnb : 3; // [18:16]
        REG32 __19_19 : 1;
        REG32 firstactslot : 2; // [21:20]
        REG32 __31_22 : 10;
    } b;
} REG_WCN_BT_LINK_PCMPHYSCNTL0_T;

//pcmphyscntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 pcmclkval : 9; // [8:0]
        REG32 __15_9 : 7;
        REG32 pcmclklimit : 8; // [23:16]
        REG32 __30_24 : 7;
        REG32 clkinv : 1; // [31]
    } b;
} REG_WCN_BT_LINK_PCMPHYSCNTL1_T;

//pcmpadding
typedef union {
    REG32 v;
    struct
    {
        REG32 lsamppad : 16; // [15:0]
        REG32 rsamppad : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_PCMPADDING_T;

//pcmpllcntl0
typedef union {
    REG32 v;
    struct
    {
        REG32 rl : 20; // [19:0]
        REG32 __31_20 : 12;
    } b;
} REG_WCN_BT_LINK_PCMPLLCNTL0_T;

//pcmpllcntl1
typedef union {
    REG32 v;
    struct
    {
        REG32 a : 19; // [18:0]
        REG32 __19_19 : 1;
        REG32 olc : 11; // [30:20]
        REG32 __31_31 : 1;
    } b;
} REG_WCN_BT_LINK_PCMPLLCNTL1_T;

//pcmpllcntl2
typedef union {
    REG32 v;
    struct
    {
        REG32 w : 19; // [18:0]
        REG32 __31_19 : 13;
    } b;
} REG_WCN_BT_LINK_PCMPLLCNTL2_T;

//pcmsourceptr
typedef union {
    REG32 v;
    struct
    {
        REG32 pcmsourceptr0 : 16; // [15:0]
        REG32 pcmsourceptr1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_PCMSOURCEPTR_T;

//pcmsinkptr
typedef union {
    REG32 v;
    struct
    {
        REG32 pcmsinkptr0 : 16; // [15:0]
        REG32 pcmsinkptr1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_PCMSINKPTR_T;

//bredrprioscharb
typedef union {
    REG32 v;
    struct
    {
        REG32 bredrmargin : 8; // [7:0]
        REG32 __14_8 : 7;
        REG32 bredrpriomode : 1; // [15]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_LINK_BREDRPRIOSCHARB_T;

//plcaddr01
typedef union {
    REG32 v;
    struct
    {
        REG32 plcbaseaddr0 : 16; // [15:0]
        REG32 plcbaseaddr1 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_PLCADDR01_T;

//plcaddr23
typedef union {
    REG32 v;
    struct
    {
        REG32 plcbaseaddr2 : 16; // [15:0]
        REG32 plcbaseaddr3 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_PLCADDR23_T;

//plcaddr45
typedef union {
    REG32 v;
    struct
    {
        REG32 plcbaseaddr4 : 16; // [15:0]
        REG32 plcbaseaddr5 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_PLCADDR45_T;

//plcaddr67
typedef union {
    REG32 v;
    struct
    {
        REG32 plcbaseaddr6 : 16; // [15:0]
        REG32 plcbaseaddr7 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_PLCADDR67_T;

//plcaddr89
typedef union {
    REG32 v;
    struct
    {
        REG32 plcbaseaddr8 : 16; // [15:0]
        REG32 plcbaseaddr9 : 16; // [31:16]
    } b;
} REG_WCN_BT_LINK_PLCADDR89_T;

//plcaddrb
typedef union {
    REG32 v;
    struct
    {
        REG32 plcbufaddr : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_WCN_BT_LINK_PLCADDRB_T;

//plcconf
typedef union {
    REG32 v;
    struct
    {
        REG32 conf_no_pitch_find_ref_threshold_dist : 14; // [13:0]
        REG32 conf_pool_mem_word_swap : 1;                // [14]
        REG32 conf_plc_except : 1;                        // [15]
        REG32 conf_plc_en : 1;                            // [16]
        REG32 conf_plc_type : 1;                          // [17]
        REG32 conf_frame_mode : 2;                        // [19:18]
        REG32 conf_scaling_mode : 1;                      // [20]
        REG32 conf_diag0_sel : 2;                         // [22:21]
        REG32 conf_plc_int_mask : 1;                      // [23]
        REG32 conf_plc_ctrl_sw : 1;                       // [24]
        REG32 conf_plc_start : 1;                         // [25], write set
        REG32 plc_fsm_state : 4;                          // [29:26], read only
        REG32 plc_int : 1;                                // [30], read only
        REG32 plc_int_clr : 1;                            // [31], write set
    } b;
} REG_WCN_BT_LINK_PLCCONF_T;

#endif
