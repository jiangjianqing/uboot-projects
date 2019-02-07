/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 * Gary Jennejohn <garyj@denx.de>
 * David Mueller <d.mueller@elsoft.ch>
 *
 * Configuation settings for the SAMSUNG SMDK2410 board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

#define CONFIG_S3C24X0				/* This is a SAMSUNG S3C24x0-type SoC */
#define CONFIG_S3C2440				/* specifically a SAMSUNG S3C2440 SoC */
#define CONFIG_JZ2440			/* on a SAMSUNG SMDK2440 Board */

/*
include/configs/jz2440.h:23:1: error: C++ style comments are not allowed in ISO C90
 //#define CONFIG_SMDK2410   on a SAMSUNG SMDK2410 Board 
*/
#define CONFIG_SYS_TEXT_BASE	0x0

#define CONFIG_SYS_ARM_CACHE_WRITETHROUGH

/* input clock of PLL (the SMDK2410 has 12MHz input clock) */
#define CONFIG_SYS_CLK_FREQ	12000000

#define CONFIG_CMDLINE_TAG	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/*
 * Hardware drivers
 */

/* Ethernet */
/*自动生成MAC地址,需要提供rand_r函数用于自动生成mac*/
/*
#define CONFIG_NET_RANDOM_ETHADDR
#define CONFIG_LIB_RAND
*/
#define CONFIG_DRIVER_DM9000
#define CONFIG_DM9000_BASE      0x20000000
#define DM9000_IO           	CONFIG_DM9000_BASE
#define DM9000_DATA         	(CONFIG_DM9000_BASE + 4)

#define CONFIG_NETMASK		255.255.255.0
#define CONFIG_IPADDR		192.168.0.123
#define CONFIG_SERVERIP		192.168.0.104
#define CONFIG_GATEWAYIP	192.168.0.1

/*
 * select serial console configuration
 */

#define CONFIG_SERIAL1			/* we use SERIAL 1 on SMDK2410 */

/************************************************************
 * USB support (currently only works with D-cache off)
 ************************************************************/
/*
#define CONFIG_USB_OHCI
#define CONFIG_USB_OHCI_S3C24XX
#define CONFIG_DOS_PARTITION
*/

/************************************************************
 * RTC
 ************************************************************/
/*
#define CONFIG_RTC_S3C24X0
*/

/*
 * BOOTP options
 */
#define CONFIG_BOOTP_BOOTFILESIZE
#define CONFIG_BOOTP_BOOTPATH
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME

/*
 * Command line configuration.
 */
/*
#define CONFIG_CMD_BSP
#define CONFIG_CMD_DATE
#define CONFIG_CMD_NAND
*/

/*
*solve:cmd/reginfo.c:9:10: fatal error: asm/ppc.h: No such file or directory
*#define CONFIG_CMD_REGINFO
*/
/*
#define CONFIG_CMDLINE_EDITING
*/
/* autoboot */
/*
#define CONFIG_BOOT_RETRY_TIME	-1
#define CONFIG_RESET_TO_RETRY
*/

#if defined(CONFIG_CMD_KGDB)
#define CONFIG_KGDB_BAUDRATE	115200	/* speed to run kgdb serial port */
#endif

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_LONGHELP		/* undef to save memory */
#define CONFIG_SYS_CBSIZE	256
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE	(CONFIG_SYS_CBSIZE + \
				sizeof(CONFIG_SYS_PROMPT)+16)
#define CONFIG_SYS_MAXARGS	16
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE

#define CONFIG_SYS_MEMTEST_START	0x30000000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x33F00000	/* 63 MB in DRAM */

#define CONFIG_SYS_LOAD_ADDR		0x30800000

/* support additional compression methods */
/*去掉该部分减少了90k大小
#define CONFIG_BZIP2
#define CONFIG_LZO
#define CONFIG_LZMA
*/

/*-----------------------------------------------------------------------
 * Physical Memory Map
 */
#define CONFIG_NR_DRAM_BANKS	1          /* we have 1 bank of DRAM */
#define PHYS_SDRAM_1		0x30000000 /* SDRAM Bank #1 */
#define PHYS_SDRAM_1_SIZE	0x04000000 /* 64 MB */

#define PHYS_FLASH_1		0x00000000 /* Flash Bank #0 */

#define CONFIG_SYS_FLASH_BASE	PHYS_FLASH_1

/*-----------------------------------------------------------------------
 * FLASH and environment organization
 */

#define CONFIG_SYS_FLASH_CFI
#define CONFIG_FLASH_CFI_DRIVER
#define CONFIG_FLASH_CFI_LEGACY
#define CONFIG_SYS_FLASH_LEGACY_1Mx16 /*nor flash型号，在drivers/mtd/jedec_flash.c中用于匹配芯片*/
#define CONFIG_FLASH_SHOW_PROGRESS	45

#define CONFIG_SYS_MAX_FLASH_BANKS	1
#define CONFIG_SYS_FLASH_BANKS_LIST     { CONFIG_SYS_FLASH_BASE }
#define CONFIG_SYS_MAX_FLASH_SECT	(128)	/*old:19，但是jz2440 norflash的扇区有 1+ 2 + 1 + 31 = 35个，改成128*/

/*Environment*/
/*uboot默认将env数据保存在flash中*/
#define CONFIG_ENV_IS_IN_NAND

#if !(defined(CONFIG_ENV_IS_IN_FLASH) || defined(CONFIG_ENV_IS_IN_NAND))
#define CONFIG_ENV_IS_IN_FLASH
#endif

#ifdef CONFIG_ENV_IS_IN_FLASH
#define CONFIG_ENV_ADDR			(CONFIG_SYS_FLASH_BASE + 0x070000)

#define CONFIG_ENV_SIZE			0x10000
#endif

#ifdef CONFIG_ENV_IS_IN_NAND	/*一定要保持跟mtdparts表中的地址一致*/
#define CONFIG_ENV_SIZE         0x20000       /*环境变量空间大小 ,128k,保持与mtdparts移植*/
#define CONFIG_ENV_OFFSET               0x80000          /*保持与mtdparts一致，位于CONFIG_ENV_OFFSET~(CONFIG_ENV_OFFSET+CONFIG_ENV_SIZE)*/
/*#define CONFIG_ENV_RANGE                CONFIG_ENV_SIZE  环境变量的擦除范围,要>=SIZE ,不定义,env/nand.c中也会自动定义*/
#endif
/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE

/*
 * Size of malloc() pool
 * BZIP2 / LZO / LZMA need a lot of RAM
 */
#define CONFIG_SYS_MALLOC_LEN	(4 * 1024 * 1024)

#define CONFIG_SYS_MONITOR_LEN	(448 * 1024)
#define CONFIG_SYS_MONITOR_BASE	CONFIG_SYS_FLASH_BASE

/*
 * NAND configuration
 */
#ifdef CONFIG_CMD_NAND
#define CONFIG_NAND_S3C2440
#define CONFIG_SYS_S3C2440_NAND_HWECC
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SYS_NAND_BASE		0x4E000000
#endif

/*
 * File system
 */
/*
#define CONFIG_CMD_UBIFS
#define CONFIG_RBTREE
*/

/* additions for new relocation code, must be added to all boards */
#define CONFIG_SYS_SDRAM_BASE	PHYS_SDRAM_1
#define CONFIG_SYS_INIT_SP_ADDR	(CONFIG_SYS_SDRAM_BASE + 0x1000 - \
				GENERATED_GBL_DATA_SIZE)

#define CONFIG_BOARD_EARLY_INIT_F


/*----------以下为env param设置区域------------*/
#define CONFIG_BOOTCOMMAND \
	"mtdparts default;"	/*用mtd命令操作分区时，就不需要先运行 mtdparts default*/

#define SERVER_NFS_ROOT_PATH __stringify(CONFIG_SERVERIP) ":/home/cz_jjq/workspace/nfs_root/jz2440/"

#define TEMP_DOWNLOAD_ADDR 0x32000000

#define UPDATE_UBOOT_CMD \
	"update-uboot=tftp " __stringify(TEMP_DOWNLOAD_ADDR)  " " __stringify(CONFIG_SERVERIP) ":u-boot.bin;" /*tftp下载uboot.bin到内存*/ \
	"protect off all;" 				/*擦除nor flash写保护*/ \
	"erase 0 0x7ffff;"  				/*擦除512k内容*/\
	"cp.b " __stringify(TEMP_DOWNLOAD_ADDR) " 0x0 $(filesize);" 		/*复制到nor的0起始地址*/\
	"reset;" 		/*重启uboot   也可以用 go 0x0; 从0地址开始执行*/\
	"\0"/*必须以\0结尾*/

#define UPDATE_KERNEL_CMD	\
	"update-kernel=nfs " __stringify(TEMP_DOWNLOAD_ADDR) " " SERVER_NFS_ROOT_PATH "uImage;"	/*读取kernel到内存，准备写入kernel分区*/ \
	"nand erase.part kernel;" \
	"nand write " __stringify(TEMP_DOWNLOAD_ADDR) " kernel;" \
	"\0"/*必须以\0结尾*/

#define UPDATE_ROOTFS_CMD	\
	"update-rootfs=nfs " __stringify(TEMP_DOWNLOAD_ADDR) " " SERVER_NFS_ROOT_PATH "rootfs.jffs2;"	/*读取kernel到内存，准备写入kernel分区*/ \
	"nand erase.part root;" \
	"nand write.jffs2 " __stringify(TEMP_DOWNLOAD_ADDR) " root $(filesize);" \
	"\0"/*必须以\0结尾*/

/*include/env_default.h中通过CONFIG_EXTRA_ENV_SETTINGS来设置更多的自定义环境变量*/
#define CONFIG_EXTRA_ENV_SETTINGS \
	"ethaddr=00:06:3B:FF:FF:FF\0"  	/*手动指定MAC地址，命名方式由net/eth_common.c:19决定*/ \
	"machid=7cf\0"		/*设置为正确id后，linux kernel才能正常启动，mini2440(7cf)能够支持dm9000,默认的smdk2410(16a)则不行*/			\
	UPDATE_UBOOT_CMD	\
	UPDATE_KERNEL_CMD	\
	UPDATE_ROOTFS_CMD
/*执行run update-uboot  刷新uboot,可以避免使用openjtag下载*/

#define BOOT_FROM_NFS_ROOTFS

#define CONFIG_USE_BOOTARGS
	/*
	 * 2019.02.02 这行设置没有成功，依然必须在服务器上打开nfs2协议的支持
"nfsroot=" SERVER_NFS_ROOT_PATH "rootfs,proto=tcp,nfsvers=3 "  设定kernel默认使用的nfs协议版本，默认为2，但在ubuntu17之后已经默认不支持2版本协议

用NFS环境作为rootfs：开发环境下强烈推荐使用
*/
#define BOOT_FROM_NFS_ROOT	 \
		"root=/dev/nfs " \
		"nfsroot=" SERVER_NFS_ROOT_PATH "rootfs "

/*2019.02.02 14:58 ，从root part启动依然没有成功，可同样的rootfs从nfs可以*/
/*用nand mtdparts中的root分区作为rootfs，正常运行环境下使用*/
#define BOOT_FROM_NAND_ROOT	 \
		"root=/dev/mtdblock4 " /*一共5个分区，root分区在最后，容量也是最大*/\
		"rootfstype=jffs2 " \
		"mtdids=" CONFIG_MTDIDS_DEFAULT " " /*这里写的id在kernel中也必须存在，否则无法识别分区表，mini2440默认的nand0.id = nand */ \
		CONFIG_MTDPARTS_DEFAULT " " /*重要：将uboot的nand分区表数据传递给kernel，确保两者统一*/

/*这里用来选择从哪里启动*/
#define BOOT_FROM_WHERE	BOOT_FROM_NFS_ROOT

#define CONFIG_BOOTARGS \
	"noinitrd " \
	"user_debug=31 " \
	BOOT_FROM_WHERE \
	"ip=" __stringify(CONFIG_IPADDR) ":" __stringify(CONFIG_SERVERIP) ":" __stringify(CONFIG_GATEWAYIP) ":" __stringify(CONFIG_NETMASK) "::eth0:off " \
	"init=/linuxrc " \
	"console=ttySAC0," __stringify(CONFIG_BAUDRATE) " "

#endif /* __CONFIG_H */
