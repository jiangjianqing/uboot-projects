/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2011 Samsung Electronics
 *
 * Configuration settings for the SAMSUNG ORIGEN (EXYNOS4210) board.
 */

#ifndef __CONFIG_ORIGEN_H
#define __CONFIG_ORIGEN_H

#include <configs/exynos4-common.h>


/* APLL : 800MHz */
//#define CONFIG_CLK_ARM_800_APLL_800
/* APLL : 1GHz */
//#define CONFIG_CLK_ARM_1000_APLL_1000
/* APLL : 1.1GHz */
//#define CONFIG_CLK_ARM_1200_APLL_1100
/* APLL : 1.2GHz */
//#define CONFIG_CLK_ARM_1200_APLL_1200
/* APLL : 1.3GHz */
//#define CONFIG_CLK_ARM_1200_APLL_1300
/* APLL : 1.4GHz */
#define CONFIG_CLK_ARM_1200_APLL_1400
/* APLL : 1.5GHz */
//#define CONFIG_CLK_ARM_1500_APLL_1500

/* bus clock: 100Mhz, DMC clock 200Mhz */
//#define CONFIG_CLK_BUS_DMC_100_200
/* bus clock: 165Mhz, DMC clock 330Mhz */
//#define CONFIG_CLK_BUS_DMC_165_330
/* bus clock: 200Mhz, DMC clock 400Mhz */
#define CONFIG_CLK_BUS_DMC_200_400

/* High Level Configuration Options */
/*定义 CONFIG_EXYNOS4210 只是为了沿用4210的编译参数，
 * 1、asm/spl.h : if defined(CONFIG_EXYNOS4210) ..  #include <asm/arch/spl.h>
 * 2、Makefile ： obj-$(CONFIG_EXYNOS4210)+= dmc_init.....   */
#define CONFIG_EXYNOS4210		1	/*    which is  a EXYNOS4210 SoC */
#define CONFIG_ORIGEN			1	/* working with ORIGEN*/
#define CONFIG_TINY4412			1

#define CONFIG_SYS_DCACHE_OFF		1

/* TINY4412-1412 core board has 8 bank of DRAM */
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define PHYS_SDRAM_1			CONFIG_SYS_SDRAM_BASE
#define SDRAM_BANK_SIZE         (128 << 20) /* 128 MB */


/* memtest works on */
#define CONFIG_SYS_MEMTEST_START	CONFIG_SYS_SDRAM_BASE
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_SDRAM_BASE + 0x6000000)
#define CONFIG_SYS_LOAD_ADDR		(CONFIG_SYS_SDRAM_BASE + 0x3E00000)

#define CONFIG_MACH_TYPE		MACH_TYPE_ORIGEN

/* select serial console configuration */

/* Console configuration */
#define CONFIG_DEFAULT_CONSOLE		"console=ttySAC1,115200n8\0"

#define CONFIG_SYS_MEM_TOP_HIDE	(1 << 20)	/* ram console */

#define CONFIG_SYS_MONITOR_BASE	0x00000000

/* Power Down Modes */
#define S5P_CHECK_SLEEP			0x00000BAD
#define S5P_CHECK_DIDLE			0xBAD00000
#define S5P_CHECK_LPA			0xABAD0000


#define CONFIG_SPL_STACK			0x02060000	/*u-boot-spl.bin  bl2阶段使用的堆栈地址*/
/* Stack address */
/*#define CONFIG_SYS_INIT_SP_ADDR		0x02060000	*/ /*u-boot.bin阶段使用的堆栈地址*/
#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_LOAD_ADDR + 0x100000 - \
				GENERATED_GBL_DATA_SIZE)

/* Because bl1 will copy bl2(spl) to iram address 0x02023400 , alloc length = 14 KB  */
#define CONFIG_SPL_TEXT_BASE		0x02023400		/* old : 0x02021410 */
#define CONFIG_SPL_MAX_FOOTPRINT	(14 * 1024)

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x40007000\0" \
	"rdaddr=0x48000000\0" \
	"kerneladdr=0x40007000\0" \
	"ramdiskaddr=0x48000000\0" \
	"console=ttySAC2,115200n8\0" \
	"mmcdev=0\0" \
	"bootenv=uEnv.txt\0" \
	"loadbootenv=load mmc ${mmcdev} ${loadaddr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from mmc ...; " \
		"env import -t $loadaddr $filesize\0" \
        "loadbootscript=load mmc ${mmcdev} ${loadaddr} boot.scr\0" \
        "bootscript=echo Running bootscript from mmc${mmcdev} ...; " \
                "source ${loadaddr}\0"
#define CONFIG_BOOTCOMMAND \
	"if mmc rescan; then " \
		"echo SD/MMC found on device ${mmcdev};" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${bootenv};" \
			"run importbootenv;" \
		"fi;" \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...;" \
			"run uenvcmd;" \
		"fi;" \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"fi; " \
	"fi;" \
	"load mmc ${mmcdev} ${loadaddr} uImage; bootm ${loadaddr} "

#define CONFIG_CLK_1000_400_200

/* MIU (Memory Interleaving Unit) */
#define CONFIG_MIU_2BIT_21_7_INTERLEAVED

/*
 *    SD MMC layout(enable spl ):
 *    +------------+-----------------+----------------+--------------+-----------------+-----------------+
 *    |            |                 |                |              |                 |                 |
 *    |    512B    |      8K(bl1)    |     16k(bl2)   |   16k(ENV)   |  512k(u-boot)   | 92k(trust-zone) |
 *    |  Reserved  | E4412_N.bl1.bin | u-boot-spl.bin |              |   u-boot.bin    |  E4412_tzsw.bin |
 *    |            |    block 1~16   |   block 17~48  |  block 49~80 | block 81 ~ 1104 |  block 1105 ~ + |
 *    +------------+-----------------+----------------+--------------+-----------------+-----------------+
 *
 *    SD MMC layout(no     spl ,not support yet):
 *    +------------+-----------------+----------------+--------------+-----------------+-----------------+
 *    |            |                 |                               |                 |                 |
 *    |    512B    |      8K(bl1)    |             16k(ENV)          |  512k(u-boot)   | 92k(trust-zone) |
 *    |  Reserved  | E4412_N.bl1.bin |                               |   u-boot.bin    |  E4412_tzsw.bin |
 *    |            |    block 1~16   |           block 17~48         | block 49 ~ 1072 |  block 1073 ~ + |
 *    +------------+-----------------+----------------+--------------+-----------------+-----------------+
 *
 */
/*------SD MMC layout 计算用变量定义区 start，仅用于本头文件-------------------*/
#define RESERVE_BLOCK_SIZE			(512)		/* 分区表预留空间 			unit : byte */
#define BL1_SIZE					(8 << 10) 	/* 8  KB for BL1		unit : byte ,注：官方提供的E4412_N.bl1.bin 刚好8k*/
#define BL2_SIZE					(16 << 10)	/* 16 KB for BL2(spl)	unit : byte ,注：实际使用空间为14K,14336*/
#define CONFIG_ENV_SIZE				(16 << 10)	/* 16 KB for ENV		unit : byte */
#define UBOOT_SIZE					0x80000		/* 512 KB for U-Boot	unit : byte */

#define CONFIG_ENV_OFFSET			(RESERVE_BLOCK_SIZE + BL1_SIZE + BL2_SIZE)	/* unit : byte */

#define UBOOT_START_OFFSET    		((CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)/512)
#define UBOOT_SIZE_BLOC_COUNT    	(UBOOT_SIZE/512)
/*-------SD MMC layout 计算用变量定义区 end---------------------------------*/

#define CONFIG_SYS_MMC_ENV_DEV		0			/*env保存的所在的MMC卡*/

/* MMC SPL  ,以下定义的常量都用在 arch/arm/mach-exynos/spl_boot.c : copy_uboot_to_ram(...)*/
#define COPY_BL2_FNPTR_ADDR			0x02020030	/*并没有真正使用，仅在spl_boot.c的注释中出现*/

#ifdef CONFIG_SPL	/*Samsung Exynos系列 SOC只能使用SPL的方式启动，因为其对BL2限制为14K大小 (14336)*/
#define BL2_START_OFFSET			UBOOT_START_OFFSET
#define BL2_SIZE_BLOC_COUNT			UBOOT_SIZE_BLOC_COUNT
#else
#error	tiny4412 mast config use CONFIG_SPL!
#define BL2_START_OFFSET			((RESERVE_BLOCK_SIZE + BL1_SIZE)/512)	/* unit : block */
#define BL2_SIZE_BLOC_COUNT			(BL2_SIZE/512)							/* unit : block */
#endif


#endif	/* __CONFIG_H */
