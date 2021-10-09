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

#ifndef _CP_MAILBOX_H_
#define _CP_MAILBOX_H_

#ifdef CT_ASM
#error "You are trying to use in an assembly code the normal H description of 'cp_mailbox'."
#endif

// =============================================================================
//  MACROS
// =============================================================================

// =============================================================================
//  TYPES
// =============================================================================

// ============================================================================
// CP_MAILBOX_T
// -----------------------------------------------------------------------------
///
// =============================================================================
#if defined(REG_ADDRESS_FOR_GGE)
#define REG_MAILBOX_BASE 0x05104000
#else
#define REG_MAILBOX_BASE 0x50104000
#endif

typedef volatile struct
{
    REG32 intgr0;                //0x00000000
    REG32 intstr0;               //0x00000004
    REG32 intcr0;                //0x00000008
    REG32 intmr0;                //0x0000000C
    REG32 intsr0;                //0x00000010
    REG32 intmsr0;               //0x00000014
    REG32 Reserved_00000018[2];  //0x00000018
    REG32 intgr1;                //0x00000020
    REG32 intstr1;               //0x00000024
    REG32 intcr1;                //0x00000028
    REG32 intmr1;                //0x0000002C
    REG32 intsr1;                //0x00000030
    REG32 intmsr1;               //0x00000034
    REG32 Reserved_00000038[2];  //0x00000038
    REG32 intgr2;                //0x00000040
    REG32 intstr2;               //0x00000044
    REG32 intcr2;                //0x00000048
    REG32 intmr2;                //0x0000004C
    REG32 intsr2;                //0x00000050
    REG32 intmsr2;               //0x00000054
    REG32 Reserved_00000058[2];  //0x00000058
    REG32 intgr3;                //0x00000060
    REG32 intstr3;               //0x00000064
    REG32 intcr3;                //0x00000068
    REG32 intmr3;                //0x0000006C
    REG32 intsr3;                //0x00000070
    REG32 intmsr3;               //0x00000074
    REG32 Reserved_00000078[2];  //0x00000078
    REG32 intgr4;                //0x00000080
    REG32 intstr4;               //0x00000084
    REG32 intcr4;                //0x00000088
    REG32 intmr4;                //0x0000008C
    REG32 intsr4;                //0x00000090
    REG32 intmsr4;               //0x00000094
    REG32 Reserved_00000098[2];  //0x00000098
    REG32 intgr5;                //0x000000A0
    REG32 intstr5;               //0x000000A4
    REG32 intcr5;                //0x000000A8
    REG32 intmr5;                //0x000000AC
    REG32 intsr5;                //0x000000B0
    REG32 intmsr5;               //0x000000B4
    REG32 Reserved_000000B8[18]; //0x000000B8
    REG32 sysmail0;              //0x00000100
    REG32 sysmail1;              //0x00000104
    REG32 sysmail2;              //0x00000108
    REG32 sysmail3;              //0x0000010C
    REG32 sysmail4;              //0x00000110
    REG32 sysmail5;              //0x00000114
    REG32 sysmail6;              //0x00000118
    REG32 sysmail7;              //0x0000011C
    REG32 sysmail8;              //0x00000120
    REG32 sysmail9;              //0x00000124
    REG32 sysmail10;             //0x00000128
    REG32 sysmail11;             //0x0000012C
    REG32 sysmail12;             //0x00000130
    REG32 sysmail13;             //0x00000134
    REG32 sysmail14;             //0x00000138
    REG32 sysmail15;             //0x0000013C
    REG32 sysmail16;             //0x00000140
    REG32 sysmail17;             //0x00000144
    REG32 sysmail18;             //0x00000148
    REG32 sysmail19;             //0x0000014C
    REG32 sysmail20;             //0x00000150
    REG32 sysmail21;             //0x00000154
    REG32 sysmail22;             //0x00000158
    REG32 sysmail23;             //0x0000015C
    REG32 sysmail24;             //0x00000160
    REG32 sysmail25;             //0x00000164
    REG32 sysmail26;             //0x00000168
    REG32 sysmail27;             //0x0000016C
    REG32 sysmail28;             //0x00000170
    REG32 sysmail29;             //0x00000174
    REG32 sysmail30;             //0x00000178
    REG32 sysmail31;             //0x0000017C
    REG32 Reserved_00000180[32]; //0x00000180
    REG32 sysmail32;             //0x00000200
    REG32 sysmail33;             //0x00000204
    REG32 sysmail34;             //0x00000208
    REG32 sysmail35;             //0x0000020C
    REG32 sysmail36;             //0x00000210
    REG32 sysmail37;             //0x00000214
    REG32 sysmail38;             //0x00000218
    REG32 sysmail39;             //0x0000021C
    REG32 sysmail40;             //0x00000220
    REG32 sysmail41;             //0x00000224
    REG32 sysmail42;             //0x00000228
    REG32 sysmail43;             //0x0000022C
    REG32 sysmail44;             //0x00000230
    REG32 sysmail45;             //0x00000234
    REG32 sysmail46;             //0x00000238
    REG32 sysmail47;             //0x0000023C
    REG32 sysmail48;             //0x00000240
    REG32 sysmail49;             //0x00000244
    REG32 sysmail50;             //0x00000248
    REG32 sysmail51;             //0x0000024C
    REG32 sysmail52;             //0x00000250
    REG32 sysmail53;             //0x00000254
    REG32 sysmail54;             //0x00000258
    REG32 sysmail55;             //0x0000025C
    REG32 sysmail56;             //0x00000260
    REG32 sysmail57;             //0x00000264
    REG32 sysmail58;             //0x00000268
    REG32 sysmail59;             //0x0000026C
    REG32 sysmail60;             //0x00000270
    REG32 sysmail61;             //0x00000274
    REG32 sysmail62;             //0x00000278
    REG32 sysmail63;             //0x0000027C
    REG32 Reserved_00000280[32]; //0x00000280
    REG32 sysmail64;             //0x00000300
    REG32 sysmail65;             //0x00000304
    REG32 sysmail66;             //0x00000308
    REG32 sysmail67;             //0x0000030C
    REG32 sysmail68;             //0x00000310
    REG32 sysmail69;             //0x00000314
    REG32 sysmail70;             //0x00000318
    REG32 sysmail71;             //0x0000031C
    REG32 sysmail72;             //0x00000320
    REG32 sysmail73;             //0x00000324
    REG32 sysmail74;             //0x00000328
    REG32 sysmail75;             //0x0000032C
    REG32 sysmail76;             //0x00000330
    REG32 sysmail77;             //0x00000334
    REG32 sysmail78;             //0x00000338
    REG32 sysmail79;             //0x0000033C
    REG32 sysmail80;             //0x00000340
    REG32 sysmail81;             //0x00000344
    REG32 sysmail82;             //0x00000348
    REG32 sysmail83;             //0x0000034C
    REG32 sysmail84;             //0x00000350
    REG32 sysmail85;             //0x00000354
    REG32 sysmail86;             //0x00000358
    REG32 sysmail87;             //0x0000035C
    REG32 sysmail88;             //0x00000360
    REG32 sysmail89;             //0x00000364
    REG32 sysmail90;             //0x00000368
    REG32 sysmail91;             //0x0000036C
    REG32 sysmail92;             //0x00000370
    REG32 sysmail93;             //0x00000374
    REG32 sysmail94;             //0x00000378
    REG32 sysmail95;             //0x0000037C
    REG32 Reserved_00000380[32]; //0x00000380
    REG32 sysmail96;             //0x00000400
    REG32 sysmail97;             //0x00000404
    REG32 sysmail98;             //0x00000408
    REG32 sysmail99;             //0x0000040C
    REG32 sysmail100;            //0x00000410
    REG32 sysmail101;            //0x00000414
    REG32 sysmail102;            //0x00000418
    REG32 sysmail103;            //0x0000041C
    REG32 sysmail104;            //0x00000420
    REG32 sysmail105;            //0x00000424
    REG32 sysmail106;            //0x00000428
    REG32 sysmail107;            //0x0000042C
    REG32 sysmail108;            //0x00000430
    REG32 sysmail109;            //0x00000434
    REG32 sysmail110;            //0x00000438
    REG32 sysmail111;            //0x0000043C
    REG32 sysmail112;            //0x00000440
    REG32 sysmail113;            //0x00000444
    REG32 sysmail114;            //0x00000448
    REG32 sysmail115;            //0x0000044C
    REG32 sysmail116;            //0x00000450
    REG32 sysmail117;            //0x00000454
    REG32 sysmail118;            //0x00000458
    REG32 sysmail119;            //0x0000045C
    REG32 sysmail120;            //0x00000460
    REG32 sysmail121;            //0x00000464
    REG32 sysmail122;            //0x00000468
    REG32 sysmail123;            //0x0000046C
    REG32 sysmail124;            //0x00000470
    REG32 sysmail125;            //0x00000474
    REG32 sysmail126;            //0x00000478
    REG32 sysmail127;            //0x0000047C
    REG32 Reserved_00000480[32]; //0x00000480
    REG32 sysmail128;            //0x00000500
    REG32 sysmail129;            //0x00000504
    REG32 sysmail130;            //0x00000508
    REG32 sysmail131;            //0x0000050C
    REG32 sysmail132;            //0x00000510
    REG32 sysmail133;            //0x00000514
    REG32 sysmail134;            //0x00000518
    REG32 sysmail135;            //0x0000051C
    REG32 sysmail136;            //0x00000520
    REG32 sysmail137;            //0x00000524
    REG32 sysmail138;            //0x00000528
    REG32 sysmail139;            //0x0000052C
    REG32 sysmail140;            //0x00000530
    REG32 sysmail141;            //0x00000534
    REG32 sysmail142;            //0x00000538
    REG32 sysmail143;            //0x0000053C
    REG32 sysmail144;            //0x00000540
    REG32 sysmail145;            //0x00000544
    REG32 sysmail146;            //0x00000548
    REG32 sysmail147;            //0x0000054C
    REG32 sysmail148;            //0x00000550
    REG32 sysmail149;            //0x00000554
    REG32 sysmail150;            //0x00000558
    REG32 sysmail151;            //0x0000055C
    REG32 sysmail152;            //0x00000560
    REG32 sysmail153;            //0x00000564
    REG32 sysmail154;            //0x00000568
    REG32 sysmail155;            //0x0000056C
    REG32 sysmail156;            //0x00000570
    REG32 sysmail157;            //0x00000574
    REG32 sysmail158;            //0x00000578
    REG32 sysmail159;            //0x0000057C
    REG32 Reserved_00000580[32]; //0x00000580
    REG32 sysmail160;            //0x00000600
    REG32 sysmail161;            //0x00000604
    REG32 sysmail162;            //0x00000608
    REG32 sysmail163;            //0x0000060C
    REG32 sysmail164;            //0x00000610
    REG32 sysmail165;            //0x00000614
    REG32 sysmail166;            //0x00000618
    REG32 sysmail167;            //0x0000061C
    REG32 sysmail168;            //0x00000620
    REG32 sysmail169;            //0x00000624
    REG32 sysmail170;            //0x00000628
    REG32 sysmail171;            //0x0000062C
    REG32 sysmail172;            //0x00000630
    REG32 sysmail173;            //0x00000634
    REG32 sysmail174;            //0x00000638
    REG32 sysmail175;            //0x0000063C
    REG32 sysmail176;            //0x00000640
    REG32 sysmail177;            //0x00000644
    REG32 sysmail178;            //0x00000648
    REG32 sysmail179;            //0x0000064C
    REG32 sysmail180;            //0x00000650
    REG32 sysmail181;            //0x00000654
    REG32 sysmail182;            //0x00000658
    REG32 sysmail183;            //0x0000065C
    REG32 sysmail184;            //0x00000660
    REG32 sysmail185;            //0x00000664
    REG32 sysmail186;            //0x00000668
    REG32 sysmail187;            //0x0000066C
    REG32 sysmail188;            //0x00000670
    REG32 sysmail189;            //0x00000674
    REG32 sysmail190;            //0x00000678
    REG32 sysmail191;            //0x0000067C
} HWP_CP_MAILBOX_T;

#define hwp_mailbox ((HWP_CP_MAILBOX_T *)REG_ACCESS_ADDRESS(REG_MAILBOX_BASE))

#endif
