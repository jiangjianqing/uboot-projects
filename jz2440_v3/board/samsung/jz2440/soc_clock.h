/*是否在lowlevel_init.S完成初始化*/
#define INIT_USE_LOWLEVEL_ASM 0	/*1=lowlevel_init初始化，0=board_early_init初始化*/

#define FCLK_SPEED 1
#define USB_CLOCK 1

/*分频系数*/
#define CLKDIVN						0x4c000014	/*分频系数*/

#define DIVN_UPLL	0x0		/*UCLK select register(UCLK must be 48MHz for USB)，该选项影响UPLL的设置*/
#define HDIVN		0x2		/*02 : HCLK = FCLK / 4  */
#define PDIVN		0x1		/* 1 : PCLK = HCLK / 2  */
#define CLKDIVN_VALUE ((DIVN_UPLL<<3)|(HDIVN<<1)|PDIVN)
/**************************************/



/* configure MPLL  (M_MDIV << 12) + (M_PDIV << 4) + M_SDIV,*/
#define S3C2440_MPLL_400MHZ ((0x5c<<12) | (0x01<<4) | (0x01))

/*MPLL configuration*/
#define MPLLCON 	0x4c000004

#if (FCLK_SPEED == 0)		/* Fout = 203MHz, Fin = 12MHz for Audio */
#define M_MDIV	0xC3
#define M_PDIV	0x4
#define M_SDIV	0x1
#elif (FCLK_SPEED == 1)		/* Fout = 400MHz */
#define M_MDIV		0x5c
#define M_PDIV		0x1
#define M_SDIV		0x1
#define MPLLCON_VALUE		((M_MDIV << 12) + (M_PDIV << 4) + M_SDIV)
#endif

/*UPLL configuration*/
#define UPLLCON		0x4c000008

#if (USB_CLOCK == 0)
#define U_M_MDIV	0xA1
#define U_M_PDIV	0x3
#define U_M_SDIV	0x1
#elif (USB_CLOCK == 1)		/* Fout = 48MHz */
#define U_M_MDIV	0x38	/*old: 0x48*/
#define U_M_PDIV	0x2		/*old: 0x3*/
#define U_M_SDIV	0x1		/*old: 0x3*/
#define UPLLCON_VALUE		((U_M_MDIV << 12) + (U_M_PDIV << 4) + U_M_SDIV)
#endif
