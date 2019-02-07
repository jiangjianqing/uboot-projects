/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002, 2010
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <netdev.h>
#include <asm/io.h>
#include <asm/arch/s3c24x0_cpu.h>
#include <asm/mach-types.h>
#include "soc_clock.h"

DECLARE_GLOBAL_DATA_PTR;

static inline void pll_delay(unsigned long loops)
{
	__asm__ volatile ("1:\n"
	  "subs %0, %1, #1\n"
	  "bne 1b" : "=r" (loops) : "0" (loops));
}

/*
 * Miscellaneous platform dependent initialisations
 */

int board_early_init_f(void)
{
	struct s3c24x0_clock_power * const clk_power =
					s3c24x0_get_base_clock_power();
	struct s3c24x0_gpio * const gpio = s3c24x0_get_base_gpio();

#if !defined(INIT_USE_LOWLEVEL_ASM) || (INIT_USE_LOWLEVEL_ASM != 1)

	/*设置分频系数 1:4:8*/
	writel(0x5,&clk_power->clkdivn);

	/*开启“asynchronous bus mode” ，写法模拟cache_enable()*/
	uint32_t reg;
	reg = get_cr();
	set_cr(reg | 0xc0000000);

	/*>>>>设置MPLL倍频值。它应该要在设置分频系数和初始化内存控制器之间来设置
	 *>>>>这里的初始化部分都移到lowlevel_init.S中用汇编实现
	 */

	/* to reduce PLL lock time, adjust the LOCKTIME register */
	/*
	writel(0xFFFFFF, &clk_power->locktime);
	*/

	/* configure MPLL */
	writel((M_MDIV << 12) + (M_PDIV << 4) + M_SDIV,
	       &clk_power->mpllcon);
	/* some delay between MPLL and UPLL */
	/*
	pll_delay(4000);
	*/

	/* configure UPLL */
	/*
	writel((U_M_MDIV << 12) + (U_M_PDIV << 4) + U_M_SDIV,
	       &clk_power->upllcon);
	*/

	/* some delay between MPLL and UPLL */
	/*
	pll_delay(8000);
	*/
#endif
	/* set up the I/O ports */

	/*
	writel(0x007FFFFF, &gpio->gpacon);
	writel(0x00044555, &gpio->gpbcon);
	writel(0x000007FF, &gpio->gpbup);
	writel(0xAAAAAAAA, &gpio->gpccon);
	writel(0x0000FFFF, &gpio->gpcup);
	writel(0xAAAAAAAA, &gpio->gpdcon);
	writel(0x0000FFFF, &gpio->gpdup);
	writel(0xAAAAAAAA, &gpio->gpecon);
	writel(0x0000FFFF, &gpio->gpeup);
	writel(0x000055AA, &gpio->gpfcon);
	writel(0x000000FF, &gpio->gpfup);
	writel(0xFF95FFBA, &gpio->gpgcon);
	writel(0x0000FFFF, &gpio->gpgup);
	*/
	int gphcon_val = 0xa0;
	/*
	gphcon_val = 2<<6 | 2<<4;
	*/
	writel(gphcon_val, &gpio->gphcon);
	int gphup_val = 0xc;
	/*
	int gphup_val = ~(1<<2 | 1<<3);
	*/
	writel(gphup_val, &gpio->gphup);
	return 0;
}

int board_init(void)
{
	/* arch number of MINI2440 board ， */
	/*重要：对应kernel中的mach-mini-2440这样能够直接输出串口信息*/
	gd->bd->bi_arch_number = MACH_TYPE_MINI2440;

	/* adress of boot parameters */
	gd->bd->bi_boot_params = 0x30000100;

	icache_enable();
	dcache_enable();

	return 0;
}

int dram_init(void)
{
	/* dram_init must store complete ramsize in gd->ram_size */
	gd->ram_size = PHYS_SDRAM_1_SIZE;
	return 0;
}

#ifdef CONFIG_CMD_NET
int board_eth_init(bd_t *bis)
{
	int rc = 0;
#ifdef CONFIG_DRIVER_DM9000
	rc = dm9000_initialize(bis);
#endif
	return rc;
}
#endif

/*
 * Hardcoded flash setup:
 * Flash 0 is a non-CFI MX29LV160DBTI flash.
 * cfi_flash.c 和 jedec_flash.c 完成nor flash检测
 * drivers/mtd/jedec_flash.c 中加入该nor flash芯片的支持
 */
ulong board_flash_get_legacy(ulong base, int banknum, flash_info_t *info)
{
	info->portwidth = FLASH_CFI_16BIT;
	info->chipwidth = FLASH_CFI_BY16;
	info->interface = FLASH_CFI_X16;
	return 1;
}
