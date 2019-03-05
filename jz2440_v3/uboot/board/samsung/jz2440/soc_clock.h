/*是否在lowlevel_init.S完成初始化*/
#define INIT_USE_LOWLEVEL_ASM 0	/*1=lowlevel_init初始化，0=board_early_init初始化*/

/*分频系数*/
#define CLKDIVN						0x4c000014	/*分频系数*/

/*#define DIVN_UPLL	0x1	*/
/*0: UCLK = UPLL clock(48MHZ) 1: UCLK = UPLL clock(96MHZ) / 2 */
#define DIVN_UPLL	(U_M_SDIV & 0x1) /* UCLK select register(UCLK must be 48MHz for USB)，该选项与UPLL的设置联动*/
#define HDIVN		0x2		/*02 : HCLK = FCLK / 4  */
#define PDIVN		0x1		/* 1 : PCLK = HCLK / 2  */
#define CLKDIVN_VALUE ((DIVN_UPLL<<3)|(HDIVN<<1)|PDIVN)
/**************************************/

/*MPLL configuration*/
#define MPLLCON 	0x4c000004
/* Fout = 400MHz */
#define M_MDIV		0x5c
#define M_PDIV		0x1
#define M_SDIV		0x1
#define MPLLCON_VALUE		((M_MDIV << 12) + (M_PDIV << 4) + M_SDIV)

/*UPLL configuration*/
#define UPLLCON		0x4c000008

#define U_M_MDIV	0x38
#define U_M_PDIV	0x2
#define U_M_SDIV	0x1		/*0x1=96MHZ  0x2=48MHZ,*/
#define UPLLCON_VALUE		((U_M_MDIV << 12) + (U_M_PDIV << 4) + U_M_SDIV)

