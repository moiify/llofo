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

#ifndef _USBC_H_
#define _USBC_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'usbc'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// USBC_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#define REG_USBC_BASE 0x09040000

typedef volatile struct
{
    REG32 gotgctl;                //0x00000000
    REG32 gotgint;                //0x00000004
    REG32 gahbcfg;                //0x00000008
    REG32 gusbcfg;                //0x0000000C
    REG32 grstctl;                //0x00000010
    REG32 gintsts;                //0x00000014
    REG32 gintmsk;                //0x00000018
    REG32 grxstsr;                //0x0000001C
    REG32 grxstsp;                //0x00000020
    REG32 grxfsiz;                //0x00000024
    REG32 gnptxfsiz;              //0x00000028
    REG32 gnptxsts;               //0x0000002C
    REG32 Reserved_00000030[2];   //0x00000030
    REG32 ggpio;                  //0x00000038
    REG32 guid;                   //0x0000003C
    REG32 gsnpsid;                //0x00000040
    REG32 ghwcfg1;                //0x00000044
    REG32 ghwcfg2;                //0x00000048
    REG32 ghwcfg3;                //0x0000004C
    REG32 ghwcfg4;                //0x00000050
    REG32 Reserved_00000054;      //0x00000054
    REG32 gpwrdn;                 //0x00000058
    REG32 gdfifocfg;              //0x0000005C
    REG32 gadpctl;                //0x00000060
    REG32 Reserved_00000064[39];  //0x00000064
    REG32 hptxfsiz;               //0x00000100
    REG32 dieptxf1;               //0x00000104
    REG32 dieptxf2;               //0x00000108
    REG32 dieptxf3;               //0x0000010C
    REG32 dieptxf4;               //0x00000110
    REG32 dieptxf5;               //0x00000114
    REG32 dieptxf6;               //0x00000118
    REG32 dieptxf7;               //0x0000011C
    REG32 dieptxf8;               //0x00000120
    REG32 Reserved_00000124[183]; //0x00000124
    REG32 hcfg;                   //0x00000400
    REG32 hfir;                   //0x00000404
    REG32 hfnum;                  //0x00000408
    REG32 Reserved_0000040C;      //0x0000040C
    REG32 hptxsts;                //0x00000410
    REG32 haint;                  //0x00000414
    REG32 haintmsk;               //0x00000418
    REG32 hflbaddr;               //0x0000041C
    REG32 Reserved_00000420[8];   //0x00000420
    REG32 hprt;                   //0x00000440
    REG32 Reserved_00000444[47];  //0x00000444
    REG32 hcchar0;                //0x00000500
    REG32 hcsplt0;                //0x00000504
    REG32 hcint0;                 //0x00000508
    REG32 hcintmsk0;              //0x0000050C
    REG32 hctsiz0;                //0x00000510
    REG32 hcdma0;                 //0x00000514
    REG32 Reserved_00000518;      //0x00000518
    REG32 hcdmab0;                //0x0000051C
    REG32 hcchar1;                //0x00000520
    REG32 hcsplt1;                //0x00000524
    REG32 hcint1;                 //0x00000528
    REG32 hcintmsk1;              //0x0000052C
    REG32 hctsiz1;                //0x00000530
    REG32 hcdma1;                 //0x00000534
    REG32 Reserved_00000538;      //0x00000538
    REG32 hcdmab1;                //0x0000053C
    REG32 hcchar2;                //0x00000540
    REG32 hcsplt2;                //0x00000544
    REG32 hcint2;                 //0x00000548
    REG32 hcintmsk2;              //0x0000054C
    REG32 hctsiz2;                //0x00000550
    REG32 hcdma2;                 //0x00000554
    REG32 Reserved_00000558;      //0x00000558
    REG32 hcdmab2;                //0x0000055C
    REG32 hcchar3;                //0x00000560
    REG32 hcsplt3;                //0x00000564
    REG32 hcint3;                 //0x00000568
    REG32 hcintmsk3;              //0x0000056C
    REG32 hctsiz3;                //0x00000570
    REG32 hcdma3;                 //0x00000574
    REG32 Reserved_00000578;      //0x00000578
    REG32 hcdmab3;                //0x0000057C
    REG32 hcchar4;                //0x00000580
    REG32 hcsplt4;                //0x00000584
    REG32 hcint4;                 //0x00000588
    REG32 hcintmsk4;              //0x0000058C
    REG32 hctsiz4;                //0x00000590
    REG32 hcdma4;                 //0x00000594
    REG32 Reserved_00000598;      //0x00000598
    REG32 hcdmab4;                //0x0000059C
    REG32 hcchar5;                //0x000005A0
    REG32 hcsplt5;                //0x000005A4
    REG32 hcint5;                 //0x000005A8
    REG32 hcintmsk5;              //0x000005AC
    REG32 hctsiz5;                //0x000005B0
    REG32 hcdma5;                 //0x000005B4
    REG32 Reserved_000005B8;      //0x000005B8
    REG32 hcdmab5;                //0x000005BC
    REG32 hcchar6;                //0x000005C0
    REG32 hcsplt6;                //0x000005C4
    REG32 hcint6;                 //0x000005C8
    REG32 hcintmsk6;              //0x000005CC
    REG32 hctsiz6;                //0x000005D0
    REG32 hcdma6;                 //0x000005D4
    REG32 Reserved_000005D8;      //0x000005D8
    REG32 hcdmab6;                //0x000005DC
    REG32 hcchar7;                //0x000005E0
    REG32 hcsplt7;                //0x000005E4
    REG32 hcint7;                 //0x000005E8
    REG32 hcintmsk7;              //0x000005EC
    REG32 hctsiz7;                //0x000005F0
    REG32 hcdma7;                 //0x000005F4
    REG32 Reserved_000005F8;      //0x000005F8
    REG32 hcdmab7;                //0x000005FC
    REG32 hcchar8;                //0x00000600
    REG32 hcsplt8;                //0x00000604
    REG32 hcint8;                 //0x00000608
    REG32 hcintmsk8;              //0x0000060C
    REG32 hctsiz8;                //0x00000610
    REG32 hcdma8;                 //0x00000614
    REG32 Reserved_00000618;      //0x00000618
    REG32 hcdmab8;                //0x0000061C
    REG32 hcchar9;                //0x00000620
    REG32 hcsplt9;                //0x00000624
    REG32 hcint9;                 //0x00000628
    REG32 hcintmsk9;              //0x0000062C
    REG32 hctsiz9;                //0x00000630
    REG32 hcdma9;                 //0x00000634
    REG32 Reserved_00000638;      //0x00000638
    REG32 hcdmab9;                //0x0000063C
    REG32 hcchar10;               //0x00000640
    REG32 hcsplt10;               //0x00000644
    REG32 hcint10;                //0x00000648
    REG32 hcintmsk10;             //0x0000064C
    REG32 hctsiz10;               //0x00000650
    REG32 hcdma10;                //0x00000654
    REG32 Reserved_00000658;      //0x00000658
    REG32 hcdmab10;               //0x0000065C
    REG32 hcchar11;               //0x00000660
    REG32 hcsplt11;               //0x00000664
    REG32 hcint11;                //0x00000668
    REG32 hcintmsk11;             //0x0000066C
    REG32 hctsiz11;               //0x00000670
    REG32 hcdma11;                //0x00000674
    REG32 Reserved_00000678;      //0x00000678
    REG32 hcdmab11;               //0x0000067C
    REG32 hcchar12;               //0x00000680
    REG32 hcsplt12;               //0x00000684
    REG32 hcint12;                //0x00000688
    REG32 hcintmsk12;             //0x0000068C
    REG32 hctsiz12;               //0x00000690
    REG32 hcdma12;                //0x00000694
    REG32 Reserved_00000698;      //0x00000698
    REG32 hcdmab12;               //0x0000069C
    REG32 hcchar13;               //0x000006A0
    REG32 hcsplt13;               //0x000006A4
    REG32 hcint13;                //0x000006A8
    REG32 hcintmsk13;             //0x000006AC
    REG32 hctsiz13;               //0x000006B0
    REG32 hcdma13;                //0x000006B4
    REG32 Reserved_000006B8;      //0x000006B8
    REG32 hcdmab13;               //0x000006BC
    REG32 hcchar14;               //0x000006C0
    REG32 hcsplt14;               //0x000006C4
    REG32 hcint14;                //0x000006C8
    REG32 hcintmsk14;             //0x000006CC
    REG32 hctsiz14;               //0x000006D0
    REG32 hcdma14;                //0x000006D4
    REG32 Reserved_000006D8;      //0x000006D8
    REG32 hcdmab14;               //0x000006DC
    REG32 hcchar15;               //0x000006E0
    REG32 hcsplt15;               //0x000006E4
    REG32 hcint15;                //0x000006E8
    REG32 hcintmsk15;             //0x000006EC
    REG32 hctsiz15;               //0x000006F0
    REG32 hcdma15;                //0x000006F4
    REG32 Reserved_000006F8;      //0x000006F8
    REG32 hcdmab15;               //0x000006FC
    REG32 Reserved_00000700[64];  //0x00000700
    REG32 dcfg;                   //0x00000800
    REG32 dctl;                   //0x00000804
    REG32 dsts;                   //0x00000808
    REG32 Reserved_0000080C;      //0x0000080C
    REG32 diepmsk;                //0x00000810
    REG32 doepmsk;                //0x00000814
    REG32 daint;                  //0x00000818
    REG32 daintmsk;               //0x0000081C
    REG32 Reserved_00000820[2];   //0x00000820
    REG32 dvbusdis;               //0x00000828
    REG32 dvbuspulse;             //0x0000082C
    REG32 dthrctl;                //0x00000830
    REG32 diepempmsk;             //0x00000834
    REG32 Reserved_00000838[50];  //0x00000838
    REG32 diepctl0;               //0x00000900
    REG32 Reserved_00000904;      //0x00000904
    REG32 diepint0;               //0x00000908
    REG32 Reserved_0000090C;      //0x0000090C
    REG32 dieptsiz0;              //0x00000910
    REG32 diepdma0;               //0x00000914
    REG32 dtxfsts0;               //0x00000918
    REG32 diepdmab0;              //0x0000091C
    REG32 diepctl1;               //0x00000920
    REG32 Reserved_00000924;      //0x00000924
    REG32 diepint1;               //0x00000928
    REG32 Reserved_0000092C;      //0x0000092C
    REG32 dieptsiz1;              //0x00000930
    REG32 diepdma1;               //0x00000934
    REG32 dtxfsts1;               //0x00000938
    REG32 diepdmab1;              //0x0000093C
    REG32 diepctl2;               //0x00000940
    REG32 Reserved_00000944;      //0x00000944
    REG32 diepint2;               //0x00000948
    REG32 Reserved_0000094C;      //0x0000094C
    REG32 dieptsiz2;              //0x00000950
    REG32 diepdma2;               //0x00000954
    REG32 dtxfsts2;               //0x00000958
    REG32 diepdmab2;              //0x0000095C
    REG32 diepctl3;               //0x00000960
    REG32 Reserved_00000964;      //0x00000964
    REG32 diepint3;               //0x00000968
    REG32 Reserved_0000096C;      //0x0000096C
    REG32 dieptsiz3;              //0x00000970
    REG32 diepdma3;               //0x00000974
    REG32 dtxfsts3;               //0x00000978
    REG32 diepdmab3;              //0x0000097C
    REG32 diepctl4;               //0x00000980
    REG32 Reserved_00000984;      //0x00000984
    REG32 diepint4;               //0x00000988
    REG32 Reserved_0000098C;      //0x0000098C
    REG32 dieptsiz4;              //0x00000990
    REG32 diepdma4;               //0x00000994
    REG32 dtxfsts4;               //0x00000998
    REG32 diepdmab4;              //0x0000099C
    REG32 diepctl5;               //0x000009A0
    REG32 Reserved_000009A4;      //0x000009A4
    REG32 diepint5;               //0x000009A8
    REG32 Reserved_000009AC;      //0x000009AC
    REG32 dieptsiz5;              //0x000009B0
    REG32 diepdma5;               //0x000009B4
    REG32 dtxfsts5;               //0x000009B8
    REG32 diepdmab5;              //0x000009BC
    REG32 diepctl6;               //0x000009C0
    REG32 Reserved_000009C4;      //0x000009C4
    REG32 diepint6;               //0x000009C8
    REG32 Reserved_000009CC;      //0x000009CC
    REG32 dieptsiz6;              //0x000009D0
    REG32 diepdma6;               //0x000009D4
    REG32 dtxfsts6;               //0x000009D8
    REG32 diepdmab6;              //0x000009DC
    REG32 diepctl7;               //0x000009E0
    REG32 Reserved_000009E4;      //0x000009E4
    REG32 diepint7;               //0x000009E8
    REG32 Reserved_000009EC;      //0x000009EC
    REG32 dieptsiz7;              //0x000009F0
    REG32 diepdma7;               //0x000009F4
    REG32 dtxfsts7;               //0x000009F8
    REG32 diepdmab7;              //0x000009FC
    REG32 diepctl8;               //0x00000A00
    REG32 Reserved_00000A04;      //0x00000A04
    REG32 diepint8;               //0x00000A08
    REG32 Reserved_00000A0C;      //0x00000A0C
    REG32 dieptsiz8;              //0x00000A10
    REG32 diepdma8;               //0x00000A14
    REG32 dtxfsts8;               //0x00000A18
    REG32 diepdmab8;              //0x00000A1C
    REG32 diepctl9;               //0x00000A20
    REG32 Reserved_00000A24;      //0x00000A24
    REG32 diepint9;               //0x00000A28
    REG32 Reserved_00000A2C;      //0x00000A2C
    REG32 dieptsiz9;              //0x00000A30
    REG32 diepdma9;               //0x00000A34
    REG32 dtxfsts9;               //0x00000A38
    REG32 diepdmab9;              //0x00000A3C
    REG32 diepctl10;              //0x00000A40
    REG32 Reserved_00000A44;      //0x00000A44
    REG32 diepint10;              //0x00000A48
    REG32 Reserved_00000A4C;      //0x00000A4C
    REG32 dieptsiz10;             //0x00000A50
    REG32 diepdma10;              //0x00000A54
    REG32 dtxfsts10;              //0x00000A58
    REG32 diepdmab10;             //0x00000A5C
    REG32 diepctl11;              //0x00000A60
    REG32 Reserved_00000A64;      //0x00000A64
    REG32 diepint11;              //0x00000A68
    REG32 Reserved_00000A6C;      //0x00000A6C
    REG32 dieptsiz11;             //0x00000A70
    REG32 diepdma11;              //0x00000A74
    REG32 dtxfsts11;              //0x00000A78
    REG32 diepdmab11;             //0x00000A7C
    REG32 diepctl12;              //0x00000A80
    REG32 Reserved_00000A84;      //0x00000A84
    REG32 diepint12;              //0x00000A88
    REG32 Reserved_00000A8C;      //0x00000A8C
    REG32 dieptsiz12;             //0x00000A90
    REG32 diepdma12;              //0x00000A94
    REG32 dtxfsts12;              //0x00000A98
    REG32 diepdmab12;             //0x00000A9C
    REG32 Reserved_00000AA0[24];  //0x00000AA0
    REG32 doepctl0;               //0x00000B00
    REG32 Reserved_00000B04;      //0x00000B04
    REG32 doepint0;               //0x00000B08
    REG32 Reserved_00000B0C;      //0x00000B0C
    REG32 doeptsiz0;              //0x00000B10
    REG32 doepdma0;               //0x00000B14
    REG32 Reserved_00000B18;      //0x00000B18
    REG32 doepdmab0;              //0x00000B1C
    REG32 doepctl1;               //0x00000B20
    REG32 Reserved_00000B24;      //0x00000B24
    REG32 doepint1;               //0x00000B28
    REG32 Reserved_00000B2C;      //0x00000B2C
    REG32 doeptsiz1;              //0x00000B30
    REG32 doepdma1;               //0x00000B34
    REG32 Reserved_00000B38;      //0x00000B38
    REG32 doepdmab1;              //0x00000B3C
    REG32 doepctl2;               //0x00000B40
    REG32 Reserved_00000B44;      //0x00000B44
    REG32 doepint2;               //0x00000B48
    REG32 Reserved_00000B4C;      //0x00000B4C
    REG32 doeptsiz2;              //0x00000B50
    REG32 doepdma2;               //0x00000B54
    REG32 Reserved_00000B58;      //0x00000B58
    REG32 doepdmab2;              //0x00000B5C
    REG32 doepctl3;               //0x00000B60
    REG32 Reserved_00000B64;      //0x00000B64
    REG32 doepint3;               //0x00000B68
    REG32 Reserved_00000B6C;      //0x00000B6C
    REG32 doeptsiz3;              //0x00000B70
    REG32 doepdma3;               //0x00000B74
    REG32 Reserved_00000B78;      //0x00000B78
    REG32 doepdmab3;              //0x00000B7C
    REG32 doepctl4;               //0x00000B80
    REG32 Reserved_00000B84;      //0x00000B84
    REG32 doepint4;               //0x00000B88
    REG32 Reserved_00000B8C;      //0x00000B8C
    REG32 doeptsiz4;              //0x00000B90
    REG32 doepdma4;               //0x00000B94
    REG32 Reserved_00000B98;      //0x00000B98
    REG32 doepdmab4;              //0x00000B9C
    REG32 doepctl5;               //0x00000BA0
    REG32 Reserved_00000BA4;      //0x00000BA4
    REG32 doepint5;               //0x00000BA8
    REG32 Reserved_00000BAC;      //0x00000BAC
    REG32 doeptsiz5;              //0x00000BB0
    REG32 doepdma5;               //0x00000BB4
    REG32 Reserved_00000BB8;      //0x00000BB8
    REG32 doepdmab5;              //0x00000BBC
    REG32 doepctl6;               //0x00000BC0
    REG32 Reserved_00000BC4;      //0x00000BC4
    REG32 doepint6;               //0x00000BC8
    REG32 Reserved_00000BCC;      //0x00000BCC
    REG32 doeptsiz6;              //0x00000BD0
    REG32 doepdma6;               //0x00000BD4
    REG32 Reserved_00000BD8;      //0x00000BD8
    REG32 doepdmab6;              //0x00000BDC
    REG32 doepctl7;               //0x00000BE0
    REG32 Reserved_00000BE4;      //0x00000BE4
    REG32 doepint7;               //0x00000BE8
    REG32 Reserved_00000BEC;      //0x00000BEC
    REG32 doeptsiz7;              //0x00000BF0
    REG32 doepdma7;               //0x00000BF4
    REG32 Reserved_00000BF8;      //0x00000BF8
    REG32 doepdmab7;              //0x00000BFC
    REG32 doepctl8;               //0x00000C00
    REG32 Reserved_00000C04;      //0x00000C04
    REG32 doepint8;               //0x00000C08
    REG32 Reserved_00000C0C;      //0x00000C0C
    REG32 doeptsiz8;              //0x00000C10
    REG32 doepdma8;               //0x00000C14
    REG32 Reserved_00000C18;      //0x00000C18
    REG32 doepdmab8;              //0x00000C1C
    REG32 doepctl9;               //0x00000C20
    REG32 Reserved_00000C24;      //0x00000C24
    REG32 doepint9;               //0x00000C28
    REG32 Reserved_00000C2C;      //0x00000C2C
    REG32 doeptsiz9;              //0x00000C30
    REG32 doepdma9;               //0x00000C34
    REG32 Reserved_00000C38;      //0x00000C38
    REG32 doepdmab9;              //0x00000C3C
    REG32 doepctl10;              //0x00000C40
    REG32 Reserved_00000C44;      //0x00000C44
    REG32 doepint10;              //0x00000C48
    REG32 Reserved_00000C4C;      //0x00000C4C
    REG32 doeptsiz10;             //0x00000C50
    REG32 doepdma10;              //0x00000C54
    REG32 Reserved_00000C58;      //0x00000C58
    REG32 doepdmab10;             //0x00000C5C
    REG32 doepctl11;              //0x00000C60
    REG32 Reserved_00000C64;      //0x00000C64
    REG32 doepint11;              //0x00000C68
    REG32 Reserved_00000C6C;      //0x00000C6C
    REG32 doeptsiz11;             //0x00000C70
    REG32 doepdma11;              //0x00000C74
    REG32 Reserved_00000C78;      //0x00000C78
    REG32 doepdmab11;             //0x00000C7C
    REG32 doepctl12;              //0x00000C80
    REG32 Reserved_00000C84;      //0x00000C84
    REG32 doepint12;              //0x00000C88
    REG32 Reserved_00000C8C;      //0x00000C8C
    REG32 doeptsiz12;             //0x00000C90
    REG32 doepdma12;              //0x00000C94
    REG32 Reserved_00000C98;      //0x00000C98
    REG32 doepdmab12;             //0x00000C9C
    REG32 Reserved_00000CA0[88];  //0x00000CA0
    REG32 pcgcctl;                //0x00000E00
} HWP_USBC_T;

#define hwp_usbc ((HWP_USBC_T *)REG_ACCESS_ADDRESS(REG_USBC_BASE))

//GOTGCTL
typedef union {
    REG32 v;
    struct
    {
        REG32 sesreqscs : 1;    // [0], read only
        REG32 sesreq : 1;       // [1]
        REG32 vbvalidoven : 1;  // [2]
        REG32 vbvalidovval : 1; // [3]
        REG32 avalidoven : 1;   // [4]
        REG32 avalidovval : 1;  // [5]
        REG32 bvalidoven : 1;   // [6]
        REG32 bvalidovval : 1;  // [7]
        REG32 hstnegscs : 1;    // [8], read only
        REG32 hnpreq : 1;       // [9]
        REG32 hstsethnpen : 1;  // [10]
        REG32 devhnpen : 1;     // [11]
        REG32 ehen : 1;         // [12]
        REG32 __14_13 : 2;
        REG32 dbncefltrbypass : 1; // [15]
        REG32 conidsts : 1;        // [16], read only
        REG32 dbnctime : 1;        // [17], read only
        REG32 asesvld : 1;         // [18]
        REG32 bsesvld : 1;         // [19], read only
        REG32 otgver : 1;          // [20]
        REG32 curmod : 1;          // [21], read only
        REG32 __31_22 : 10;
    } b;
} REG_USBC_GOTGCTL_T;

//GOTGINT
typedef union {
    REG32 v;
    struct
    {
        REG32 __1_0 : 2;
        REG32 sesenddet : 1; // [2], write clear
        REG32 __7_3 : 5;
        REG32 sesreqsucstschng : 1; // [8], write clear
        REG32 hstnegsucstschng : 1; // [9], write clear
        REG32 __16_10 : 7;
        REG32 hstnegdet : 1;   // [17], write clear
        REG32 adevtoutchg : 1; // [18], write clear
        REG32 dbncedone : 1;   // [19], write clear
        REG32 __31_20 : 12;
    } b;
} REG_USBC_GOTGINT_T;

//GAHBCFG
typedef union {
    REG32 v;
    struct
    {
        REG32 glblintrmsk : 1; // [0]
        REG32 hbstlen : 4;     // [4:1]
        REG32 dmaen : 1;       // [5]
        REG32 __6_6 : 1;
        REG32 nptxfemplvl : 1; // [7]
        REG32 ptxfemplvl : 1;  // [8]
        REG32 __20_9 : 12;
        REG32 remmemsupp : 1;       // [21]
        REG32 notialldmawrit : 1;   // [22]
        REG32 ahbsingle : 1;        // [23]
        REG32 invdescendianess : 1; // [24]
        REG32 __31_25 : 7;
    } b;
} REG_USBC_GAHBCFG_T;

//GUSBCFG
typedef union {
    REG32 v;
    struct
    {
        REG32 toutcal : 3;       // [2:0]
        REG32 phyif : 1;         // [3], read only
        REG32 ulpi_utmi_sel : 1; // [4]
        REG32 fsintf : 1;        // [5]
        REG32 physel : 1;        // [6]
        REG32 __7_7 : 1;
        REG32 srpcap : 1;    // [8]
        REG32 hnpcap : 1;    // [9]
        REG32 usbtrdtim : 4; // [13:10]
        REG32 __14_14 : 1;
        REG32 phylpwrclksel : 1; // [15]
        REG32 __21_16 : 6;
        REG32 termseldlpulse : 1; // [22]
        REG32 __25_23 : 3;
        REG32 ic_usbcap : 1; // [26], read only
        REG32 __27_27 : 1;
        REG32 txenddelay : 1;   // [28]
        REG32 forcehstmode : 1; // [29]
        REG32 forcedevmode : 1; // [30]
        REG32 corrupttxpkt : 1; // [31]
    } b;
} REG_USBC_GUSBCFG_T;

//GRSTCTL
typedef union {
    REG32 v;
    struct
    {
        REG32 csftrst : 1;     // [0]
        REG32 piufssftrst : 1; // [1]
        REG32 frmcntrrst : 1;  // [2]
        REG32 __3_3 : 1;
        REG32 rxfflsh : 1; // [4]
        REG32 txfflsh : 1; // [5]
        REG32 txfnum : 5;  // [10:6]
        REG32 __29_11 : 19;
        REG32 dmareq : 1;  // [30], read only
        REG32 ahbidle : 1; // [31], read only
    } b;
} REG_USBC_GRSTCTL_T;

//GINTSTS
typedef union {
    REG32 v;
    struct
    {
        REG32 curmod : 1;     // [0], read only
        REG32 modemis : 1;    // [1], write clear
        REG32 otgint : 1;     // [2]
        REG32 sof : 1;        // [3]
        REG32 rxflvl : 1;     // [4], read only
        REG32 nptxfemp : 1;   // [5], read only
        REG32 ginnakeff : 1;  // [6], read only
        REG32 goutnakeff : 1; // [7], read only
        REG32 __9_8 : 2;
        REG32 erlysusp : 1;   // [10], write clear
        REG32 usbsusp : 1;    // [11], write clear
        REG32 usbrst : 1;     // [12], write clear
        REG32 enumdone : 1;   // [13], write clear
        REG32 isooutdrop : 1; // [14], write clear
        REG32 eopf : 1;       // [15], write clear
        REG32 __16_16 : 1;
        REG32 epmis : 1;       // [17], write clear
        REG32 iepint : 1;      // [18], read only
        REG32 oepint : 1;      // [19], read only
        REG32 incompisoin : 1; // [20], write clear
        REG32 incomplp : 1;    // [21], write clear
        REG32 fetsusp : 1;     // [22], write clear
        REG32 resetdet : 1;    // [23], write clear
        REG32 prtint : 1;      // [24], read only
        REG32 hchint : 1;      // [25], read only
        REG32 ptxfemp : 1;     // [26]
        REG32 __27_27 : 1;
        REG32 conidstschng : 1; // [28]
        REG32 disconnint : 1;   // [29], write clear
        REG32 sessreqint : 1;   // [30], write clear
        REG32 wkupint : 1;      // [31], write clear
    } b;
} REG_USBC_GINTSTS_T;

//GINTMSK
typedef union {
    REG32 v;
    struct
    {
        REG32 __0_0 : 1;
        REG32 modemismsk : 1;    // [1]
        REG32 otgintmsk : 1;     // [2]
        REG32 sofmsk : 1;        // [3]
        REG32 rxflvlmsk : 1;     // [4]
        REG32 nptxfempmsk : 1;   // [5]
        REG32 ginnakeffmsk : 1;  // [6]
        REG32 goutnakeffmsk : 1; // [7]
        REG32 __9_8 : 2;
        REG32 erlysuspmsk : 1;   // [10]
        REG32 usbsuspmsk : 1;    // [11]
        REG32 usbrstmsk : 1;     // [12]
        REG32 enumdonemsk : 1;   // [13]
        REG32 isooutdropmsk : 1; // [14]
        REG32 eopfmsk : 1;       // [15]
        REG32 __16_16 : 1;
        REG32 epmismsk : 1;  // [17]
        REG32 iepintmsk : 1; // [18]
        REG32 oepintmsk : 1; // [19]
        REG32 __20_20 : 1;
        REG32 incomplpmsk : 1; // [21]
        REG32 fetsuspmsk : 1;  // [22]
        REG32 resetdetmsk : 1; // [23]
        REG32 prtintmsk : 1;   // [24]
        REG32 hchintmsk : 1;   // [25]
        REG32 ptxfempmsk : 1;  // [26]
        REG32 __27_27 : 1;
        REG32 conidstschngmsk : 1; // [28]
        REG32 disconnintmsk : 1;   // [29]
        REG32 sessreqintmsk : 1;   // [30]
        REG32 wkupintmsk : 1;      // [31]
    } b;
} REG_USBC_GINTMSK_T;

//GRXSTSR
typedef union {
    REG32 v;
    struct
    {
        REG32 chnum : 4;  // [3:0]
        REG32 bcnt : 11;  // [14:4], read only
        REG32 dpid : 2;   // [16:15], read only
        REG32 pktsts : 4; // [20:17]
        REG32 fn : 4;     // [24:21], read only
        REG32 __31_25 : 7;
    } b;
} REG_USBC_GRXSTSR_T;

//GRXSTSP
typedef union {
    REG32 v;
    struct
    {
        REG32 chnum : 4;  // [3:0]
        REG32 bcnt : 11;  // [14:4], read only
        REG32 dpid : 2;   // [16:15], read only
        REG32 pktsts : 4; // [20:17]
        REG32 fn : 4;     // [24:21], read only
        REG32 __31_25 : 7;
    } b;
} REG_USBC_GRXSTSP_T;

//GRXFSIZ
typedef union {
    REG32 v;
    struct
    {
        REG32 rxfdep : 12; // [11:0]
        REG32 __31_12 : 20;
    } b;
} REG_USBC_GRXFSIZ_T;

//GNPTXFSIZ
typedef union {
    REG32 v;
    struct
    {
        REG32 nptxfstaddr : 12; // [11:0]
        REG32 __15_12 : 4;
        REG32 nptxfdep : 12; // [27:16]
        REG32 __31_28 : 4;
    } b;
} REG_USBC_GNPTXFSIZ_T;

//GNPTXSTS
typedef union {
    REG32 v;
    struct
    {
        REG32 nptxfspcavail : 16; // [15:0], read only
        REG32 nptxqspcavail : 8;  // [23:16], read only
        REG32 nptxqtop : 7;       // [30:24], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_GNPTXSTS_T;

//GGPIO
typedef union {
    REG32 v;
    struct
    {
        REG32 gpi : 16; // [15:0], read only
        REG32 gpo : 16; // [31:16]
    } b;
} REG_USBC_GGPIO_T;

//GHWCFG2
typedef union {
    REG32 v;
    struct
    {
        REG32 otgmode : 3;         // [2:0], read only
        REG32 otgarch : 2;         // [4:3], read only
        REG32 singpnt : 1;         // [5], read only
        REG32 hsphytype : 2;       // [7:6], read only
        REG32 fsphytype : 2;       // [9:8], read only
        REG32 numdeveps : 4;       // [13:10], read only
        REG32 numhstchnl : 4;      // [17:14], read only
        REG32 periosupport : 1;    // [18], read only
        REG32 dynfifosizing : 1;   // [19], read only
        REG32 multiprocintrpt : 1; // [20], read only
        REG32 __21_21 : 1;
        REG32 nptxqdepth : 2; // [23:22], read only
        REG32 ptxqdepth : 2;  // [25:24], read only
        REG32 tknqdepth : 5;  // [30:26], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_GHWCFG2_T;

//GHWCFG3
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersizewidth : 4; // [3:0], read only
        REG32 pktsizewidth : 3;  // [6:4], read only
        REG32 otgen : 1;         // [7], read only
        REG32 i2cintsel : 1;     // [8], read only
        REG32 vndctlsupt : 1;    // [9], read only
        REG32 optfeature : 1;    // [10], read only
        REG32 rsttype : 1;       // [11], read only
        REG32 adpsupport : 1;    // [12], read only
        REG32 hsicmode : 1;      // [13], read only
        REG32 bcsupport : 1;     // [14], read only
        REG32 lpmmode : 1;       // [15], read only
        REG32 dfifodepth : 16;   // [31:16], read only
    } b;
} REG_USBC_GHWCFG3_T;

//GHWCFG4
typedef union {
    REG32 v;
    struct
    {
        REG32 numdevperioeps : 4;      // [3:0], read only
        REG32 partialpwrdn : 1;        // [4], read only
        REG32 ahbfreq : 1;             // [5], read only
        REG32 hibernation : 1;         // [6], read only
        REG32 extendedhibernation : 1; // [7], read only
        REG32 __11_8 : 4;
        REG32 acgsupt : 1;         // [12], read only
        REG32 enhancedlpmsupt : 1; // [13], read only
        REG32 phydatawidth : 2;    // [15:14], read only
        REG32 numctleps : 4;       // [19:16], read only
        REG32 iddgfltr : 1;        // [20], read only
        REG32 vbusvalidfltr : 1;   // [21], read only
        REG32 avalidfltr : 1;      // [22], read only
        REG32 bvalidfltr : 1;      // [23], read only
        REG32 sessendfltr : 1;     // [24], read only
        REG32 dedfifomode : 1;     // [25], read only
        REG32 ineps : 4;           // [29:26], read only
        REG32 descdmaenabled : 1;  // [30], read only
        REG32 descdma : 1;         // [31], read only
    } b;
} REG_USBC_GHWCFG4_T;

//GPWRDN
typedef union {
    REG32 v;
    struct
    {
        REG32 pmuintsel : 1; // [0]
        REG32 pmuactv : 1;   // [1]
        REG32 __2_2 : 1;
        REG32 pwrdnclmp : 1;   // [3]
        REG32 pwrdnrst_n : 1;  // [4]
        REG32 pwrdnswtch : 1;  // [5]
        REG32 disablevbus : 1; // [6]
        REG32 __14_7 : 8;
        REG32 srpdetect : 1;     // [15], write clear
        REG32 srpdetectmsk : 1;  // [16]
        REG32 stschngint : 1;    // [17], write clear
        REG32 stschngintmsk : 1; // [18]
        REG32 linestate : 2;     // [20:19], read only
        REG32 iddig : 1;         // [21], read only
        REG32 bsessvld : 1;      // [22], read only
        REG32 adpint : 1;        // [23], write clear
        REG32 __31_24 : 8;
    } b;
} REG_USBC_GPWRDN_T;

//GDFIFOCFG
typedef union {
    REG32 v;
    struct
    {
        REG32 gdfifocfg : 16;      // [15:0]
        REG32 epinfobaseaddr : 16; // [31:16]
    } b;
} REG_USBC_GDFIFOCFG_T;

//GADPCTL
typedef union {
    REG32 v;
    struct
    {
        REG32 prbdschg : 2;     // [1:0]
        REG32 prbdelta : 2;     // [3:2]
        REG32 prbper : 2;       // [5:4]
        REG32 rtim : 11;        // [16:6], read only
        REG32 enaprb : 1;       // [17]
        REG32 enasns : 1;       // [18]
        REG32 adpres : 1;       // [19]
        REG32 adpen : 1;        // [20]
        REG32 adpprbint : 1;    // [21], write clear
        REG32 adpsnsint : 1;    // [22], write clear
        REG32 adptoutint : 1;   // [23], write clear
        REG32 adpprbintmsk : 1; // [24]
        REG32 adpsnsintmsk : 1; // [25]
        REG32 adptoutmsk : 1;   // [26]
        REG32 ar : 2;           // [28:27]
        REG32 __31_29 : 3;
    } b;
} REG_USBC_GADPCTL_T;

//HPTXFSIZ
typedef union {
    REG32 v;
    struct
    {
        REG32 ptxfstaddr : 13; // [12:0]
        REG32 __15_13 : 3;
        REG32 ptxfsize : 12; // [27:16]
        REG32 __31_28 : 4;
    } b;
} REG_USBC_HPTXFSIZ_T;

//DIEPTXF1
typedef union {
    REG32 v;
    struct
    {
        REG32 inepntxfstaddr : 12; // [11:0]
        REG32 __15_12 : 4;
        REG32 inepntxfdep : 10; // [25:16]
        REG32 __31_26 : 6;
    } b;
} REG_USBC_DIEPTXF1_T;

//DIEPTXF2
typedef union {
    REG32 v;
    struct
    {
        REG32 inepntxfstaddr : 13; // [12:0]
        REG32 __15_13 : 3;
        REG32 inepntxfdep : 10; // [25:16]
        REG32 __31_26 : 6;
    } b;
} REG_USBC_DIEPTXF2_T;

//DIEPTXF3
typedef union {
    REG32 v;
    struct
    {
        REG32 inepntxfstaddr : 13; // [12:0]
        REG32 __15_13 : 3;
        REG32 inepntxfdep : 9; // [24:16]
        REG32 __31_25 : 7;
    } b;
} REG_USBC_DIEPTXF3_T;

//DIEPTXF4
typedef union {
    REG32 v;
    struct
    {
        REG32 inepntxfstaddr : 13; // [12:0]
        REG32 __15_13 : 3;
        REG32 inepntxfdep : 9; // [24:16]
        REG32 __31_25 : 7;
    } b;
} REG_USBC_DIEPTXF4_T;

//DIEPTXF5
typedef union {
    REG32 v;
    struct
    {
        REG32 inepntxfstaddr : 13; // [12:0]
        REG32 __15_13 : 3;
        REG32 inepntxfdep : 9; // [24:16]
        REG32 __31_25 : 7;
    } b;
} REG_USBC_DIEPTXF5_T;

//DIEPTXF6
typedef union {
    REG32 v;
    struct
    {
        REG32 inepntxfstaddr : 13; // [12:0]
        REG32 __15_13 : 3;
        REG32 inepntxfdep : 9; // [24:16]
        REG32 __31_25 : 7;
    } b;
} REG_USBC_DIEPTXF6_T;

//DIEPTXF7
typedef union {
    REG32 v;
    struct
    {
        REG32 inepntxfstaddr : 13; // [12:0]
        REG32 __15_13 : 3;
        REG32 inepntxfdep : 9; // [24:16]
        REG32 __31_25 : 7;
    } b;
} REG_USBC_DIEPTXF7_T;

//DIEPTXF8
typedef union {
    REG32 v;
    struct
    {
        REG32 inepntxfstaddr : 13; // [12:0]
        REG32 __15_13 : 3;
        REG32 inepntxfdep : 9; // [24:16]
        REG32 __31_25 : 7;
    } b;
} REG_USBC_DIEPTXF8_T;

//HCFG
typedef union {
    REG32 v;
    struct
    {
        REG32 fslspclksel : 2; // [1:0]
        REG32 fslssupp : 1;    // [2]
        REG32 __6_3 : 4;
        REG32 ena32khzs : 1; // [7]
        REG32 resvalid : 8;  // [15:8]
        REG32 __22_16 : 7;
        REG32 descdma : 1;     // [23]
        REG32 frlisten : 2;    // [25:24]
        REG32 perschedena : 1; // [26]
        REG32 __30_27 : 4;
        REG32 modechtimen : 1; // [31]
    } b;
} REG_USBC_HCFG_T;

//HFIR
typedef union {
    REG32 v;
    struct
    {
        REG32 frint : 16;      // [15:0]
        REG32 hfirrldctrl : 1; // [16]
        REG32 __31_17 : 15;
    } b;
} REG_USBC_HFIR_T;

//HFNUM
typedef union {
    REG32 v;
    struct
    {
        REG32 frnum : 16; // [15:0], read only
        REG32 frrem : 16; // [31:16], read only
    } b;
} REG_USBC_HFNUM_T;

//HPTXSTS
typedef union {
    REG32 v;
    struct
    {
        REG32 ptxfspcavail : 16; // [15:0], read only
        REG32 ptxqspcavail : 8;  // [23:16], read only
        REG32 ptxqtop : 8;       // [31:24], read only
    } b;
} REG_USBC_HPTXSTS_T;

//HAINT
typedef union {
    REG32 v;
    struct
    {
        REG32 haint : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_HAINT_T;

//HAINTMSK
typedef union {
    REG32 v;
    struct
    {
        REG32 haintmsk : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_USBC_HAINTMSK_T;

//HPRT
typedef union {
    REG32 v;
    struct
    {
        REG32 prtconnsts : 1;     // [0], read only
        REG32 prtconndet : 1;     // [1], write clear
        REG32 prtena : 1;         // [2], write clear
        REG32 prtenchng : 1;      // [3], write clear
        REG32 prtovrcurract : 1;  // [4], read only
        REG32 prtovrcurrchng : 1; // [5], write clear
        REG32 prtres : 1;         // [6]
        REG32 prtsusp : 1;        // [7]
        REG32 prtrst : 1;         // [8]
        REG32 __9_9 : 1;
        REG32 prtlnsts : 2;  // [11:10], read only
        REG32 prtpwr : 1;    // [12]
        REG32 prttstctl : 4; // [16:13]
        REG32 prtspd : 2;    // [18:17], read only
        REG32 __31_19 : 13;
    } b;
} REG_USBC_HPRT_T;

//HCCHAR0
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR0_T;

//HCSPLT0
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT0_T;

//HCINT0
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT0_T;

//HCINTMSK0
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK0_T;

//HCTSIZ0
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ0_T;

//HCCHAR1
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR1_T;

//HCSPLT1
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT1_T;

//HCINT1
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT1_T;

//HCINTMSK1
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK1_T;

//HCTSIZ1
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ1_T;

//HCCHAR2
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR2_T;

//HCSPLT2
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT2_T;

//HCINT2
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT2_T;

//HCINTMSK2
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK2_T;

//HCTSIZ2
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ2_T;

//HCCHAR3
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR3_T;

//HCSPLT3
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT3_T;

//HCINT3
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT3_T;

//HCINTMSK3
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK3_T;

//HCTSIZ3
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ3_T;

//HCCHAR4
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR4_T;

//HCSPLT4
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT4_T;

//HCINT4
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT4_T;

//HCINTMSK4
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK4_T;

//HCTSIZ4
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ4_T;

//HCCHAR5
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR5_T;

//HCSPLT5
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT5_T;

//HCINT5
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT5_T;

//HCINTMSK5
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK5_T;

//HCTSIZ5
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ5_T;

//HCCHAR6
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR6_T;

//HCSPLT6
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT6_T;

//HCINT6
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT6_T;

//HCINTMSK6
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK6_T;

//HCTSIZ6
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ6_T;

//HCCHAR7
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR7_T;

//HCSPLT7
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT7_T;

//HCINT7
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT7_T;

//HCINTMSK7
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK7_T;

//HCTSIZ7
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ7_T;

//HCCHAR8
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR8_T;

//HCSPLT8
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT8_T;

//HCINT8
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT8_T;

//HCINTMSK8
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK8_T;

//HCTSIZ8
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ8_T;

//HCCHAR9
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR9_T;

//HCSPLT9
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT9_T;

//HCINT9
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT9_T;

//HCINTMSK9
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK9_T;

//HCTSIZ9
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ9_T;

//HCCHAR10
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR10_T;

//HCSPLT10
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT10_T;

//HCINT10
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT10_T;

//HCINTMSK10
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK10_T;

//HCTSIZ10
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ10_T;

//HCCHAR11
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR11_T;

//HCSPLT11
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT11_T;

//HCINT11
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT11_T;

//HCINTMSK11
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK11_T;

//HCTSIZ11
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ11_T;

//HCCHAR12
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR12_T;

//HCSPLT12
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT12_T;

//HCINT12
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT12_T;

//HCINTMSK12
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK12_T;

//HCTSIZ12
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ12_T;

//HCCHAR13
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR13_T;

//HCSPLT13
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT13_T;

//HCINT13
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT13_T;

//HCINTMSK13
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK13_T;

//HCTSIZ13
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ13_T;

//HCCHAR14
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR14_T;

//HCSPLT14
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT14_T;

//HCINT14
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT14_T;

//HCINTMSK14
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK14_T;

//HCTSIZ14
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ14_T;

//HCCHAR15
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11;  // [10:0]
        REG32 epnum : 4; // [14:11]
        REG32 epdir : 1; // [15]
        REG32 __16_16 : 1;
        REG32 lspddev : 1; // [17]
        REG32 eptype : 2;  // [19:18]
        REG32 ec : 2;      // [21:20]
        REG32 devaddr : 7; // [28:22]
        REG32 oddfrm : 1;  // [29]
        REG32 chdis : 1;   // [30]
        REG32 chena : 1;   // [31]
    } b;
} REG_USBC_HCCHAR15_T;

//HCSPLT15
typedef union {
    REG32 v;
    struct
    {
        REG32 prtaddr : 7;  // [6:0]
        REG32 hubaddr : 7;  // [13:7]
        REG32 xactpos : 2;  // [15:14]
        REG32 compsplt : 1; // [16]
        REG32 __30_17 : 14;
        REG32 spltena : 1; // [31]
    } b;
} REG_USBC_HCSPLT15_T;

//HCINT15
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;         // [0], write clear
        REG32 chhltd : 1;            // [1], write clear
        REG32 ahberr : 1;            // [2], write clear
        REG32 stall : 1;             // [3], write clear
        REG32 nak : 1;               // [4], write clear
        REG32 ack : 1;               // [5], write clear
        REG32 nyet : 1;              // [6], write clear
        REG32 xacterr : 1;           // [7], write clear
        REG32 bblerr : 1;            // [8], write clear
        REG32 frmovrun : 1;          // [9], write clear
        REG32 datatglerr : 1;        // [10], write clear
        REG32 bnaintr : 1;           // [11], write clear
        REG32 xcs_xact_err : 1;      // [12], write clear
        REG32 desc_lst_rollintr : 1; // [13], write clear
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINT15_T;

//HCINTMSK15
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1; // [0]
        REG32 chhltdmsk : 1;    // [1]
        REG32 ahberrmsk : 1;    // [2]
        REG32 __10_3 : 8;
        REG32 bnaintrmsk : 1; // [11]
        REG32 __12_12 : 1;
        REG32 desc_lst_rollintrmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_HCINTMSK15_T;

//HCTSIZ15
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 pid : 2;       // [30:29]
        REG32 dopng : 1;     // [31]
    } b;
} REG_USBC_HCTSIZ15_T;

//DCFG
typedef union {
    REG32 v;
    struct
    {
        REG32 devspd : 2;        // [1:0]
        REG32 nzstsouthshk : 1;  // [2]
        REG32 ena32khzsusp : 1;  // [3]
        REG32 devaddr : 7;       // [10:4]
        REG32 perfrint : 2;      // [12:11]
        REG32 endevoutnak : 1;   // [13]
        REG32 xcvrdly : 1;       // [14]
        REG32 erraticintmsk : 1; // [15]
        REG32 __22_16 : 7;
        REG32 descdma : 1;     // [23]
        REG32 perschintvl : 2; // [25:24]
        REG32 resvalid : 6;    // [31:26]
    } b;
} REG_USBC_DCFG_T;

//DCTL
typedef union {
    REG32 v;
    struct
    {
        REG32 rmtwkupsig : 1;   // [0]
        REG32 sftdiscon : 1;    // [1]
        REG32 gnpinnaksts : 1;  // [2], read only
        REG32 goutnaksts : 1;   // [3], read only
        REG32 tstctl : 3;       // [6:4]
        REG32 sgnpinnak : 1;    // [7]
        REG32 cgnpinnak : 1;    // [8]
        REG32 sgoutnak : 1;     // [9]
        REG32 cgoutnak : 1;     // [10]
        REG32 pwronprgdone : 1; // [11]
        REG32 __12_12 : 1;
        REG32 gmc : 2;         // [14:13]
        REG32 ignrfrmnum : 1;  // [15]
        REG32 nakonbble : 1;   // [16]
        REG32 encontonbna : 1; // [17]
        REG32 __31_18 : 14;
    } b;
} REG_USBC_DCTL_T;

//DSTS
typedef union {
    REG32 v;
    struct
    {
        REG32 suspsts : 1;   // [0], read only
        REG32 enumspd : 2;   // [2:1], read only
        REG32 errticerr : 1; // [3], read only
        REG32 __7_4 : 4;
        REG32 soffn : 14;   // [21:8]
        REG32 devlnsts : 2; // [23:22], read only
        REG32 __31_24 : 8;
    } b;
} REG_USBC_DSTS_T;

//DIEPMSK
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1;   // [0]
        REG32 epdisbldmsk : 1;    // [1]
        REG32 ahberrmsk : 1;      // [2]
        REG32 timeoutmsk : 1;     // [3]
        REG32 intkntxfempmsk : 1; // [4]
        REG32 intknepmismsk : 1;  // [5]
        REG32 inepnakeffmsk : 1;  // [6]
        REG32 __7_7 : 1;
        REG32 txfifoundrnmsk : 1; // [8]
        REG32 bnainintrmsk : 1;   // [9]
        REG32 __12_10 : 3;
        REG32 nakmsk : 1; // [13]
        REG32 __31_14 : 18;
    } b;
} REG_USBC_DIEPMSK_T;

//DOEPMSK
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercomplmsk : 1;   // [0]
        REG32 epdisbldmsk : 1;    // [1]
        REG32 ahberrmsk : 1;      // [2]
        REG32 setupmsk : 1;       // [3]
        REG32 outtknepdismsk : 1; // [4]
        REG32 stsphsercvdmsk : 1; // [5]
        REG32 back2backsetup : 1; // [6]
        REG32 __7_7 : 1;
        REG32 outpkterrmsk : 1;  // [8]
        REG32 bnaoutintrmsk : 1; // [9]
        REG32 __11_10 : 2;
        REG32 bbleerrmsk : 1; // [12]
        REG32 nakmsk : 1;     // [13]
        REG32 nyetmsk : 1;    // [14]
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DOEPMSK_T;

//DAINT
typedef union {
    REG32 v;
    struct
    {
        REG32 inepint0 : 1;  // [0], read only
        REG32 inepint1 : 1;  // [1], read only
        REG32 inepint2 : 1;  // [2], read only
        REG32 inepint3 : 1;  // [3], read only
        REG32 inepint4 : 1;  // [4], read only
        REG32 inepint5 : 1;  // [5], read only
        REG32 inepint6 : 1;  // [6], read only
        REG32 inepint7 : 1;  // [7], read only
        REG32 inepint8 : 1;  // [8], read only
        REG32 inepint9 : 1;  // [9], read only
        REG32 inepint10 : 1; // [10], read only
        REG32 inepint11 : 1; // [11], read only
        REG32 inepint12 : 1; // [12], read only
        REG32 __15_13 : 3;
        REG32 outepint0 : 1;  // [16], read only
        REG32 outepint1 : 1;  // [17], read only
        REG32 outepint2 : 1;  // [18], read only
        REG32 outepint3 : 1;  // [19], read only
        REG32 outepint4 : 1;  // [20], read only
        REG32 outepint5 : 1;  // [21], read only
        REG32 outepint6 : 1;  // [22], read only
        REG32 outepint7 : 1;  // [23], read only
        REG32 outepint8 : 1;  // [24], read only
        REG32 outepint9 : 1;  // [25], read only
        REG32 outepint10 : 1; // [26], read only
        REG32 outepint11 : 1; // [27], read only
        REG32 outepint12 : 1; // [28], read only
        REG32 __31_29 : 3;
    } b;
} REG_USBC_DAINT_T;

//DAINTMSK
typedef union {
    REG32 v;
    struct
    {
        REG32 inepmsk0 : 1;  // [0]
        REG32 inepmsk1 : 1;  // [1]
        REG32 inepmsk2 : 1;  // [2]
        REG32 inepmsk3 : 1;  // [3]
        REG32 inepmsk4 : 1;  // [4]
        REG32 inepmsk5 : 1;  // [5]
        REG32 inepmsk6 : 1;  // [6]
        REG32 inepmsk7 : 1;  // [7]
        REG32 inepmsk8 : 1;  // [8]
        REG32 inepmsk9 : 1;  // [9]
        REG32 inepmsk10 : 1; // [10]
        REG32 inepmsk11 : 1; // [11]
        REG32 inepmsk12 : 1; // [12]
        REG32 __15_13 : 3;
        REG32 outepmsk0 : 1;  // [16]
        REG32 outepmsk1 : 1;  // [17]
        REG32 outepmsk2 : 1;  // [18]
        REG32 outepmsk3 : 1;  // [19]
        REG32 outepmsk4 : 1;  // [20]
        REG32 outepmsk5 : 1;  // [21]
        REG32 outepmsk6 : 1;  // [22]
        REG32 outepmsk7 : 1;  // [23]
        REG32 outepmsk8 : 1;  // [24]
        REG32 outepmsk9 : 1;  // [25]
        REG32 outepmsk10 : 1; // [26]
        REG32 outepmsk11 : 1; // [27]
        REG32 outepmsk12 : 1; // [28]
        REG32 __31_29 : 3;
    } b;
} REG_USBC_DAINTMSK_T;

//DVBUSDIS
typedef union {
    REG32 v;
    struct
    {
        REG32 dvbusdis : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DVBUSDIS_T;

//DVBUSPULSE
typedef union {
    REG32 v;
    struct
    {
        REG32 dvbuspulse : 12; // [11:0]
        REG32 __31_12 : 20;
    } b;
} REG_USBC_DVBUSPULSE_T;

//DTHRCTL
typedef union {
    REG32 v;
    struct
    {
        REG32 nonisothren : 1; // [0]
        REG32 isothren : 1;    // [1]
        REG32 txthrlen : 9;    // [10:2]
        REG32 ahbthrratio : 2; // [12:11]
        REG32 __15_13 : 3;
        REG32 rxthren : 1;  // [16]
        REG32 rxthrlen : 9; // [25:17]
        REG32 __26_26 : 1;
        REG32 arbprken : 1; // [27]
        REG32 __31_28 : 4;
    } b;
} REG_USBC_DTHRCTL_T;

//DIEPEMPMSK
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfempmsk : 16; // [15:0]
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DIEPEMPMSK_T;

//DIEPCTL0
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 2; // [1:0]
        REG32 __14_2 : 13;
        REG32 usbactep : 1; // [15], read only
        REG32 __16_16 : 1;
        REG32 naksts : 1; // [17], read only
        REG32 eptype : 2; // [19:18], read only
        REG32 __20_20 : 1;
        REG32 stall : 1;  // [21]
        REG32 txfnum : 4; // [25:22]
        REG32 cnak : 1;   // [26]
        REG32 snak : 1;   // [27]
        REG32 __29_28 : 2;
        REG32 epdis : 1; // [30]
        REG32 epena : 1; // [31]
    } b;
} REG_USBC_DIEPCTL0_T;

//DIEPINT0
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT0_T;

//DIEPTSIZ0
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 7; // [6:0]
        REG32 __18_7 : 12;
        REG32 pktcnt : 2; // [20:19]
        REG32 __31_21 : 11;
    } b;
} REG_USBC_DIEPTSIZ0_T;

//DTXFSTS0
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS0_T;

//DIEPCTL1
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL1_T;

//DIEPINT1
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT1_T;

//DIEPTSIZ1
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ1_T;

//DTXFSTS1
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS1_T;

//DIEPCTL2
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL2_T;

//DIEPINT2
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT2_T;

//DIEPTSIZ2
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ2_T;

//DTXFSTS2
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS2_T;

//DIEPCTL3
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL3_T;

//DIEPINT3
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT3_T;

//DIEPTSIZ3
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ3_T;

//DTXFSTS3
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS3_T;

//DIEPCTL4
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL4_T;

//DIEPINT4
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT4_T;

//DIEPTSIZ4
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ4_T;

//DTXFSTS4
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS4_T;

//DIEPCTL5
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL5_T;

//DIEPINT5
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT5_T;

//DIEPTSIZ5
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ5_T;

//DTXFSTS5
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS5_T;

//DIEPCTL6
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL6_T;

//DIEPINT6
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT6_T;

//DIEPTSIZ6
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ6_T;

//DTXFSTS6
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS6_T;

//DIEPCTL7
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL7_T;

//DIEPINT7
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT7_T;

//DIEPTSIZ7
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ7_T;

//DTXFSTS7
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS7_T;

//DIEPCTL8
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL8_T;

//DIEPINT8
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT8_T;

//DIEPTSIZ8
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ8_T;

//DTXFSTS8
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS8_T;

//DIEPCTL9
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL9_T;

//DIEPINT9
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT9_T;

//DIEPTSIZ9
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ9_T;

//DTXFSTS9
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS9_T;

//DIEPCTL10
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL10_T;

//DIEPINT10
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT10_T;

//DIEPTSIZ10
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ10_T;

//DTXFSTS10
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS10_T;

//DIEPCTL11
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL11_T;

//DIEPINT11
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT11_T;

//DIEPTSIZ11
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ11_T;

//DTXFSTS11
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS11_T;

//DIEPCTL12
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 __20_20 : 1;
        REG32 stall : 1;    // [21]
        REG32 txfnum : 4;   // [25:22]
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DIEPCTL12_T;

//DIEPINT12
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;   // [0], write clear
        REG32 epdisbld : 1;    // [1], write clear
        REG32 ahberr : 1;      // [2], write clear
        REG32 timeout : 1;     // [3], write clear
        REG32 intkntxfemp : 1; // [4], write clear
        REG32 intknepmis : 1;  // [5], write clear
        REG32 inepnakeff : 1;  // [6], write clear
        REG32 txfemp : 1;      // [7], read only
        REG32 txfifoundrn : 1; // [8], write clear
        REG32 bnaintr : 1;     // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;  // [11], write clear
        REG32 bbleerr : 1;    // [12], write clear
        REG32 nakintrpt : 1;  // [13], write clear
        REG32 nyetintrpt : 1; // [14], write clear
        REG32 __31_15 : 17;
    } b;
} REG_USBC_DIEPINT12_T;

//DIEPTSIZ12
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 mc : 2;        // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DIEPTSIZ12_T;

//DTXFSTS12
typedef union {
    REG32 v;
    struct
    {
        REG32 ineptxfspcavail : 16; // [15:0], read only
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DTXFSTS12_T;

//DOEPCTL0
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 2; // [1:0], read only
        REG32 __14_2 : 13;
        REG32 usbactep : 1; // [15], read only
        REG32 __16_16 : 1;
        REG32 naksts : 1; // [17], read only
        REG32 eptype : 2; // [19:18], read only
        REG32 snp : 1;    // [20]
        REG32 stall : 1;  // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1; // [26]
        REG32 snak : 1; // [27]
        REG32 __29_28 : 2;
        REG32 epdis : 1; // [30], read only
        REG32 epena : 1; // [31]
    } b;
} REG_USBC_DOEPCTL0_T;

//DOEPINT0
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT0_T;

//DOEPTSIZ0
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 7; // [6:0]
        REG32 __18_7 : 12;
        REG32 pktcnt : 1; // [19]
        REG32 __28_20 : 9;
        REG32 supcnt : 2; // [30:29]
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ0_T;

//DOEPCTL1
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL1_T;

//DOEPINT1
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT1_T;

//DOEPTSIZ1
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ1_T;

//DOEPCTL2
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL2_T;

//DOEPINT2
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT2_T;

//DOEPTSIZ2
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ2_T;

//DOEPCTL3
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL3_T;

//DOEPINT3
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT3_T;

//DOEPTSIZ3
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ3_T;

//DOEPCTL4
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL4_T;

//DOEPINT4
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT4_T;

//DOEPTSIZ4
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ4_T;

//DOEPCTL5
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL5_T;

//DOEPINT5
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT5_T;

//DOEPTSIZ5
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ5_T;

//DOEPCTL6
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL6_T;

//DOEPINT6
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT6_T;

//DOEPTSIZ6
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ6_T;

//DOEPCTL7
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL7_T;

//DOEPINT7
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT7_T;

//DOEPTSIZ7
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ7_T;

//DOEPCTL8
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL8_T;

//DOEPINT8
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT8_T;

//DOEPTSIZ8
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ8_T;

//DOEPCTL9
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL9_T;

//DOEPINT9
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT9_T;

//DOEPTSIZ9
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ9_T;

//DOEPCTL10
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL10_T;

//DOEPINT10
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT10_T;

//DOEPTSIZ10
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ10_T;

//DOEPCTL11
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL11_T;

//DOEPINT11
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT11_T;

//DOEPTSIZ11
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ11_T;

//DOEPCTL12
typedef union {
    REG32 v;
    struct
    {
        REG32 mps : 11; // [10:0]
        REG32 __14_11 : 4;
        REG32 usbactep : 1; // [15]
        REG32 dpid : 1;     // [16], read only
        REG32 naksts : 1;   // [17], read only
        REG32 eptype : 2;   // [19:18]
        REG32 snp : 1;      // [20]
        REG32 stall : 1;    // [21]
        REG32 __25_22 : 4;
        REG32 cnak : 1;     // [26]
        REG32 snak : 1;     // [27]
        REG32 setd0pid : 1; // [28]
        REG32 setd1pid : 1; // [29]
        REG32 epdis : 1;    // [30]
        REG32 epena : 1;    // [31]
    } b;
} REG_USBC_DOEPCTL12_T;

//DOEPINT12
typedef union {
    REG32 v;
    struct
    {
        REG32 xfercompl : 1;      // [0], write clear
        REG32 epdisbld : 1;       // [1], write clear
        REG32 ahberr : 1;         // [2], write clear
        REG32 setup : 1;          // [3], write clear
        REG32 outtknepdis : 1;    // [4], write clear
        REG32 stsphsercvd : 1;    // [5], write clear
        REG32 back2backsetup : 1; // [6], write clear
        REG32 __7_7 : 1;
        REG32 outpkterr : 1; // [8], write clear
        REG32 bnaintr : 1;   // [9], write clear
        REG32 __10_10 : 1;
        REG32 pktdrpsts : 1;   // [11], write clear
        REG32 bbleerr : 1;     // [12], write clear
        REG32 nakintrpt : 1;   // [13], write clear
        REG32 nyetintrpt : 1;  // [14], write clear
        REG32 stuppktrcvd : 1; // [15], write clear
        REG32 __31_16 : 16;
    } b;
} REG_USBC_DOEPINT12_T;

//DOEPTSIZ12
typedef union {
    REG32 v;
    struct
    {
        REG32 xfersize : 19; // [18:0]
        REG32 pktcnt : 10;   // [28:19]
        REG32 rxdpid : 2;    // [30:29], read only
        REG32 __31_31 : 1;
    } b;
} REG_USBC_DOEPTSIZ12_T;

//PCGCCTL
typedef union {
    REG32 v;
    struct
    {
        REG32 stoppclk : 1; // [0]
        REG32 __2_1 : 2;
        REG32 rstpdwnmodule : 1; // [3]
        REG32 __5_4 : 2;
        REG32 physleep : 1;    // [6], read only
        REG32 l1suspended : 1; // [7], read only
        REG32 __31_8 : 24;
    } b;
} REG_USBC_PCGCCTL_T;

#endif
