/*
 * Memory Setup stuff - taken from blob memsetup.S
 *
 * Copyright (C) 1999 2000 2001 Erik Mouw (J.A.K.Mouw@its.tudelft.nl) and
 *                     Jan-Derk Bakker (J.D.Bakker@its.tudelft.nl)
 *
 * Modified for the Samsung SMDK2410 by
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include <config.h>
#include "soc_clock.h"

/* some parameters for the board */

/*
 *
 * Taken from linux/arch/arm/boot/compressed/head-s3c2410.S
 *
 * Copyright (C) 2002 Samsung Electronics SW.LEE  <hitchcar@sec.samsung.com>
 *
 */
/*引用c头文件会导致无法通过编译，所以将S3C24X0_WATCHDOG_BASE在这里重复定义一次
#include <asm/arch/s3c24x0_cpu.h>
*/

#define S3C24X0_WATCHDOG_BASE		0x53000000

#define BWSCON	0x48000000

/* BWSCON */
#define DW8			(0x0)
#define DW16			(0x1)
#define DW32			(0x2)
#define WAIT			(0x1<<2)
#define UBLB			(0x1<<3)

#define B1_BWSCON		(DW16)
#define B2_BWSCON		(DW16)
#define B3_BWSCON		(DW16)
#define B4_BWSCON		(DW16+WAIT+UBLB)	/*DM9000网卡*/
#define B5_BWSCON		(DW8 ) /*连接插座HEADER 20X2 ，jz2440 原理图上显示没有焊接 old : (DW16)*/
#define B6_BWSCON		(DW32)
#define B7_BWSCON		(DW32)

/* BANK0CON */
#define B0_Tacs			0x0	/*  0clk */
#define B0_Tcos			0x0	/*  0clk */
#define B0_Tacc			0x7	/* 14clk */
#define B0_Tcoh			0x0	/*  0clk */
#define B0_Tah			0x0	/*  0clk */
#define B0_Tacp			0x0
#define B0_PMC			0x0	/* normal */

/* BANK1CON */
#define B1_Tacs			0x0	/*  0clk */
#define B1_Tcos			0x0	/*  0clk */
#define B1_Tacc			0x7	/* 14clk */
#define B1_Tcoh			0x0	/*  0clk */
#define B1_Tah			0x0	/*  0clk */
#define B1_Tacp			0x0
#define B1_PMC			0x0

#define B2_Tacs			0x0
#define B2_Tcos			0x0
#define B2_Tacc			0x7
#define B2_Tcoh			0x0
#define B2_Tah			0x0
#define B2_Tacp			0x0
#define B2_PMC			0x0

/*smdk2410中对该band进行了定义，直接用Reset Value：0x700即可，就满足jz2440的设置要求*/
#define B3_Tacs			0x0	/*  0clk */
#define B3_Tcos			0x0	/*  4clk */
#define B3_Tacc			0x7	/* 14clk */
#define B3_Tcoh			0x0	/*  1clk */
#define B3_Tah			0x0	/*  0clk */
#define B3_Tacp			0x0     /*  6clk */
#define B3_PMC			0x0	/* normal */

/* for eth DM9000*/
#define B4_Tacs			0x0	/*  0clk */
#define B4_Tcos			0x3	/*  4clk */
#define B4_Tacc			0x7	/* 14clk */
#define B4_Tcoh			0x1	/*  1clk 对比之前韦东山二期视频讲解的DM9000时序设置，我们在这里将位7:6设置为01*/
#define B4_Tah			0x3	/*  4clk */
#define B4_Tacp			0x6 /*  6clk */
#define B4_PMC			0x0	/* normal */

#define B5_Tacs			0x0	/*  0clk */
#define B5_Tcos			0x0	/*  0clk */
#define B5_Tacc			0x7	/* 14clk */
#define B5_Tcoh			0x0	/*  0clk */
#define B5_Tah			0x0	/*  0clk */
#define B5_Tacp			0x0
#define B5_PMC			0x0	/* normal */

#define B6_MT			0x3	/* SDRAM */
#define B6_Trcd			0x1
#define B6_SCAN			0x1	/* 9bit */

#define B7_MT			0x3	/* SDRAM */
#define B7_Trcd			0x1	/* 3clk */
#define B7_SCAN			0x1	/* 9bit */

/* REFRESH parameter */
#define REFEN			0x1	/* Refresh enable */
#define TREFMD			0x0	/* CBR(CAS before RAS)/Auto refresh */
#define Trp			0x0	/* 2clk */
#define Tsrc		0x3 /* 7clk If Trp = 2clocks & Tsrc = 7clocks, Trc = 3+7=10clocks.*/
#define Tchr		0x0	/* s3c-2410&2440都没有该参数，所有设为0 old: 0x2 3clk */

#define REFCNT			1268
//#define cal_refcnt(a,b) 		(int)(2048+1-(a)*(b))  /*a=period, b=HCLK */
/*jz2440的参数: 未使用PLL时 period=7.8125us, HCLK=12Mhz  (2048+1-7.8125*12) = 1955*/
/*jz2440的参数: 使用PLL时 period=7.8125us, HCLK=100Mhz  (2048+1-7.8125*100) = 1268*/
/*smdk2410的参数: period=15.6us, HCLK=60Mhz, (2048+1-15.6*60)=1113 */

/* BANK SIZE parameter*/
#define BURST_EN	0x1
#define SCKE_EN		0x1
#define SCLK_EN		0x1		/*recommended*/
#define BK76MAP		0x1		/*64m*/


.globl lowlevel_init
lowlevel_init:

/*1、关看门狗 , 2440必须关，否则会3秒复位开发板一次，缺少喂狗动作*/
/*往WATCHDOG寄存器0x53000000写入0即可*/
	ldr		r0,=S3C24X0_WATCHDOG_BASE
	mov		r1,#0
	str		r1,[r0]

#if defined(INIT_USE_LOWLEVEL_ASM) && (INIT_USE_LOWLEVEL_ASM == 1)

/* 2. 设置分频系数 */
	ldr r0, =CLKDIVN
	/*
	mov r1,#5
	*/
	ldr r1, =CLKDIVN_VALUE
	str r1, [r0]

/*3、芯片手册中说s3c2440不支持“asynchronous bus mode”,但开发板上是s3c2440A，所以不受影响*/
	mrc 	p15, 0, r1, c1, c0, 0
	orr 	r1, r1, #0xc0000000
	mcr 	p15, 0, r1, c1, c0, 0

/*4、MPLLCON 设置*/
	ldr 	r0, =MPLLCON
	ldr 	r1, =MPLLCON_VALUE
	str 	r1, [r0]

#endif

/*5、配置内存控制器*/
	/* memory control configuration */
	/* make r0 relative the current location so that it */
	/* reads SMRDATA out of FLASH rather than memory ! */
	ldr     r0, =SMRDATA
	ldr	r1, =CONFIG_SYS_TEXT_BASE
	sub	r0, r0, r1
	ldr	r1, =BWSCON	/* Bus Width Status Controller */
	add     r2, r0, #13*4
0:
	ldr     r3, [r0], #4
	str     r3, [r1], #4
	cmp     r2, r0
	bne     0b

	/* everything is fine now */
	mov	pc, lr

	.ltorg
/* the literal pools origin */

SMRDATA:
    .word (0+(B1_BWSCON<<4)+(B2_BWSCON<<8)+(B3_BWSCON<<12)+(B4_BWSCON<<16)+(B5_BWSCON<<20)+(B6_BWSCON<<24)+(B7_BWSCON<<28))
    .word ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))
    .word ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))
    .word ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))
    .word ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))
    .word ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))
    .word ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))
    .word ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))
    .word ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))
    .word ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Tsrc<<18)+(Tchr<<16)+REFCNT)		/*REFRESH HCLK=12MHz:  0x008C07A3, HCLK=100MHz: 0x008C04F4*/
    .word ((BURST_EN<<7)+(SCKE_EN<<5)+(SCLK_EN<<4)+BK76MAP)						/*BANKSIZE real=64m, old:0x32 128m */
    .word 0x30		/*MRSRB6*/
    .word 0x30		/*MRSRB7*/
