/******************************************************************************
 ** File Name:      pmu.c                                                     *
 ** Author:         Cheng.lu                                                  *
 ** DATE:           09/27/2017                                                *
 ** Copyright:      2017 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic information on chip.          *
 ******************************************************************************/

#include <asm/io.h>
#include "adi_hal_internal.h"
#include "asm/arch/sprd_reg.h"
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
#ifndef CONFIG_FPGA

#define PMU_CLK_6P5M	1
#define PMU_CLK_32K	0

#if defined(CONFIG_BOARD_ID)
extern int sprd_get_32k(void);
#endif

void pmu_commom_config(void)
{
	uint32_t reg_val;
	unsigned int feature_32k_less = 1;

#if defined(CONFIG_BOARD_ID)
	feature_32k_less = sprd_get_32k();
#endif

#if PMU_CLK_6P5M /*XTL/4=6.5M*/
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_TOP_CFG,
		//BIT_PMU_APB_PD_CA7_TOP_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_TOP_PD_SEL |
		//BIT_PMU_APB_PD_CA7_TOP_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_CA7_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA7_TOP_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_CA7_TOP_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C0_CFG,
		//BIT_PMU_APB_PD_CA7_C0_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA7_C0_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_C0_PD_SEL |
		//BIT_PMU_APB_PD_CA7_C0_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_CA7_C0_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_C0_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA7_C0_PWR_ON_SEQ_DLY(0x00) |
		BIT_PMU_APB_PD_CA7_C0_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C1_CFG,
		//BIT_PMU_APB_PD_CA7_C1_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA7_C1_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_C1_PD_SEL |
		BIT_PMU_APB_PD_CA7_C1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA7_C1_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_C1_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA7_C1_PWR_ON_SEQ_DLY(0x04) |
		BIT_PMU_APB_PD_CA7_C1_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C2_CFG,
		//BIT_PMU_APB_PD_CA7_C2_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA7_C2_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_C2_PD_SEL |
		BIT_PMU_APB_PD_CA7_C2_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA7_C2_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_C2_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA7_C2_PWR_ON_SEQ_DLY(0x08) |
		BIT_PMU_APB_PD_CA7_C2_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA7_C3_CFG,
		//BIT_PMU_APB_PD_CA7_C3_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA7_C3_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_C3_PD_SEL |
		BIT_PMU_APB_PD_CA7_C3_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA7_C3_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA7_C3_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA7_C3_PWR_ON_SEQ_DLY(0x0c) |
		BIT_PMU_APB_PD_CA7_C3_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AP_SYS_CFG,
		//BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(0x00) |
		BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_MM_TOP_CFG,
		//BIT_PMU_APB_PD_MM_TOP_FORCE_SHUTDOWN |
		//BIT_PD_MM_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_MM_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_MM_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_MM_TOP_PWR_ON_SEQ_DLY(0x14) |
		BIT_PMU_APB_PD_MM_TOP_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_CFG,
		//BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_GPU_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_SEQ_DLY(0x18) |
		BIT_PMU_APB_PD_GPU_TOP_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TGDSP_CFG,
		//BIT_PMU_APB_PD_WTLCP_TGDSP_PD_SEL |
		//BIT_PMU_APB_PD_WTLCP_TGDSP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_TGDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_SEQ_DLY(0x00) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_A_CFG,
		//BIT_PMU_APB_PD_WTLCP_HU3GE_A_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_HU3GE_A_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CP_SYS_CFG,
		//BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CP_SYS_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CP_SYS_PWR_ON_SEQ_DLY(0x00) |
		BIT_PMU_APB_PD_CP_SYS_ISO_ON_DLY(0x02) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WCN_TOP_CFG,
		//BIT_PMU_APB_PD_WCN_TOP_FORCE_SHUTDOWN|
		//BIT_PMU_APB_PD_WCN_TOP_AUTO_SHUTDOWN_EN|
		BIT_PMU_APB_PD_WCN_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WCN_TOP_PWR_ON_SEQ_DLY(0x00) |
		BIT_PMU_APB_PD_WCN_TOP_ISO_ON_DLY(0x02) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WCN_WIFI_CFG,
		//BIT_PMU_APB_PD_WCN_WIFI_AUTO_SEL|
		//BIT_PMU_APB_PD_WCN_WIFI_FORCE_SHUTDOWN|
		//BIT_PMU_APB_PD_WCN_WIFI_AUTO_SHUTDOWN_EN
		BIT_PMU_APB_PD_WCN_WIFI_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WCN_WIFI_PWR_ON_SEQ_DLY(0x00) |
		BIT_PMU_APB_PD_WCN_WIFI_ISO_ON_DLY(0x02) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PD_WCN_GNSS_CFG,
		//BIT_PMU_APB_PD_WCN_GNSS_AUTO_SEL|
		//BIT_PMU_APB_PD_WCN_GNSS_FORCE_SHUTDOWN|
		//BIT_PMU_APB_PD_WCN_GNSS_AUTO_SHUTDOWN_EN
		BIT_PMU_APB_PD_WCN_GNSS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WCN_GNSS_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_WCN_GNSS_ISO_ON_DLY(0x02) |
		0
	);


	/*PUB_SYS for DDR*/
	reg_val = CHIP_REG_GET(REG_PMU_APB_PD_PUB_SYS_CFG) & 0xff000000;
	CHIP_REG_SET(REG_PMU_APB_PD_PUB_SYS_CFG,
		//BIT_PMU_APB_PD_PUB_SYS_PRE_EN |
		//BIT_PMU_APB_PD_PUB_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUB_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUB_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_PUB_SYS_PWR_ON_SEQ_DLY(0x0a) |
		BIT_PMU_APB_PD_PUB_SYS_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTL_WAIT_CNT,
		BIT_PMU_APB_XTL0_WAIT_CNT(0x05) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTLBUF_WAIT_CNT,
		BIT_PMU_APB_XTLBUF0_WAIT_CNT(0x4) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT0,
		BIT_PMU_APB_CPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_TWPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_DPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_MPLL_WAIT_CNT(0x08) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT1,
		BIT_PMU_APB_GPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_BBPLL2_WAIT_CNT(0x08) |
		BIT_PMU_APB_BBPLL1_WAIT_CNT(0x08) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG0,
		BIT_PMU_APB_CP_PWR_WAIT_CNT(0x14) |
		BIT_PMU_APB_WCN_PWR_WAIT_CNT(0x14) |
		BIT_PMU_APB_AP_PWR_WAIT_CNT(0x1e) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG1,
		BIT_PMU_APB_CM4_PWR_WAIT_CNT(0x05) |
		0
	);

	CHIP_REG_OR(REG_PMU_APB_PMU_CLK_CFG,
		BIT_PMU_APB_CGM_PMU_SEL_REG|
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_ST_DLY0,
		BIT_PMU_APB_CGM_OFF_DLY(0x00) |
		BIT_PMU_APB_CGM_ON_DLY(0x00) |
		BIT_PMU_APB_ISO_OFF_DLY(0x00) |
		BIT_PMU_APB_RST_ASSERT_DLY(0x00) |
		0
	);

	CHIP_REG_SET(REG_PMU_APB_PWR_ST_DLY1,
		BIT_PMU_APB_WAKEUP_LOCK_DLY(0x00) |
		BIT_PMU_APB_RESTORE_DLY(0x00) |
		BIT_PMU_APB_SHUTDOWN_DLY(0x00) |
		BIT_PMU_APB_BISR_RST_DLY(0x00) |
		0
	);

	CHIP_REG_OR(REG_PMU_APB_PMU_CLK_DIV_CFG0,
		BIT_PMU_APB_PWR_ST_CLK_DIV_CFG(0x13)|
		0
	);

	CHIP_REG_OR(REG_PMU_APB_PMU_CLK_DIV_CFG1,
		BIT_PMU_APB_SLP_CTRL_CLK_DIV_CFG(0xc7)|
		0
	);
#endif/*PMU_CLK_6P5M*/

#if PMU_CLK_32K
	if(feature_32k_less) {
		CHIP_REG_SET(REG_PMU_APB_PD_CA7_TOP_CFG,
			//BIT_PMU_APB_PD_CA7_TOP_DBG_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_TOP_PD_SEL |
			//BIT_PMU_APB_PD_CA7_TOP_FORCE_SHUTDOWN |
			BIT_PMU_APB_PD_CA7_TOP_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_TOP_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_CA7_TOP_PWR_ON_SEQ_DLY(0x01) |
			BIT_PMU_APB_PD_CA7_TOP_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_CA7_C0_CFG,
			//BIT_PMU_APB_PD_CA7_C0_WFI_SHUTDOWN_EN |
			//BIT_PMU_APB_PD_CA7_C0_DBG_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_C0_PD_SEL |
			//BIT_PMU_APB_PD_CA7_C0_FORCE_SHUTDOWN |
			BIT_PMU_APB_PD_CA7_C0_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_C0_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_CA7_C0_PWR_ON_SEQ_DLY(0x00) |
			BIT_PMU_APB_PD_CA7_C0_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_CA7_C1_CFG,
			//BIT_PMU_APB_PD_CA7_C1_WFI_SHUTDOWN_EN |
			//BIT_PMU_APB_PD_CA7_C1_DBG_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_C1_PD_SEL |
			BIT_PMU_APB_PD_CA7_C1_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_CA7_C1_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_C1_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_CA7_C1_PWR_ON_SEQ_DLY(0x04) |
			BIT_PMU_APB_PD_CA7_C1_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_CA7_C2_CFG,
			//BIT_PMU_APB_PD_CA7_C2_WFI_SHUTDOWN_EN |
			//BIT_PMU_APB_PD_CA7_C2_DBG_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_C2_PD_SEL |
			BIT_PMU_APB_PD_CA7_C2_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_CA7_C2_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_C2_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_CA7_C2_PWR_ON_SEQ_DLY(0x08) |
			BIT_PMU_APB_PD_CA7_C2_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_CA7_C3_CFG,
			//BIT_PMU_APB_PD_CA7_C3_WFI_SHUTDOWN_EN |
			//BIT_PMU_APB_PD_CA7_C3_DBG_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_C3_PD_SEL |
			BIT_PMU_APB_PD_CA7_C3_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_CA7_C3_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CA7_C3_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_CA7_C3_PWR_ON_SEQ_DLY(0x0c) |
			BIT_PMU_APB_PD_CA7_C3_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_AP_SYS_CFG,
			//BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN |
			BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(0x00) |
			BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_MM_TOP_CFG,
			//BIT_PMU_APB_PD_MM_TOP_FORCE_SHUTDOWN |
			//BIT_PD_MM_TOP_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_MM_TOP_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_MM_TOP_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_MM_TOP_PWR_ON_SEQ_DLY(0x14) |
			BIT_PMU_APB_PD_MM_TOP_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_CFG,
			//BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_GPU_TOP_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_GPU_TOP_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_GPU_TOP_PWR_ON_SEQ_DLY(0x18) |
			BIT_PMU_APB_PD_GPU_TOP_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TGDSP_CFG,
			//BIT_PMU_APB_PD_WTLCP_TGDSP_PD_SEL |
			//BIT_PMU_APB_PD_WTLCP_TGDSP_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_WTLCP_TGDSP_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_SEQ_DLY(0x00) |
			BIT_PMU_APB_PD_WTLCP_TGDSP_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_A_CFG,
			//BIT_PMU_APB_PD_WTLCP_HU3GE_A_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_WTLCP_HU3GE_A_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_SEQ_DLY(0x02) |
			BIT_PMU_APB_PD_WTLCP_HU3GE_A_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PD_CP_SYS_CFG,
			//BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN |
			//BIT_PMU_APB_PD_CP_SYS_DBG_SHUTDOWN_EN |
			//BIT_PMU_APB_PD_CP_SYS_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_WTLCP_SYS_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_CP_SYS_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_CP_SYS_PWR_ON_SEQ_DLY(0x00) |
			BIT_PMU_APB_PD_CP_SYS_ISO_ON_DLY(0x02) |
			0
		);

		CHIP_REG_SET(REG_PMU_APB_PD_WCN_TOP_CFG,
			//BIT_PMU_APB_PD_WCN_TOP_FORCE_SHUTDOWN|
			//BIT_PMU_APB_PD_WCN_TOP_AUTO_SHUTDOWN_EN|
			BIT_PMU_APB_PD_WCN_TOP_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_WCN_TOP_PWR_ON_SEQ_DLY(0x00) |
			BIT_PMU_APB_PD_WCN_TOP_ISO_ON_DLY(0x02) |
			0
		);

		CHIP_REG_SET(REG_PMU_APB_PD_WCN_WIFI_CFG,
			//BIT_PMU_APB_PD_WCN_WIFI_AUTO_SEL|
			//BIT_PMU_APB_PD_WCN_WIFI_FORCE_SHUTDOWN|
			//BIT_PMU_APB_PD_WCN_WIFI_AUTO_SHUTDOWN_EN
			BIT_PMU_APB_PD_WCN_WIFI_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_WCN_WIFI_PWR_ON_SEQ_DLY(0x00) |
			BIT_PMU_APB_PD_WCN_WIFI_ISO_ON_DLY(0x02) |
			0
		);

		CHIP_REG_SET(REG_PMU_APB_PD_WCN_GNSS_CFG,
			//BIT_PMU_APB_PD_WCN_GNSS_AUTO_SEL|
			//BIT_PMU_APB_PD_WCN_GNSS_FORCE_SHUTDOWN|
			//BIT_PMU_APB_PD_WCN_GNSS_AUTO_SHUTDOWN_EN
			BIT_PMU_APB_PD_WCN_GNSS_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_WCN_GNSS_PWR_ON_SEQ_DLY(0x02) |
			BIT_PMU_APB_PD_WCN_GNSS_ISO_ON_DLY(0x02) |
			0
		);


		/*PUB_SYS for DDR*/
		reg_val = CHIP_REG_GET(REG_PMU_APB_PD_PUB_SYS_CFG) & 0xff000000;
		CHIP_REG_SET(REG_PMU_APB_PD_PUB_SYS_CFG,
			//BIT_PMU_APB_PD_PUB_SYS_PRE_EN |
			//BIT_PMU_APB_PD_PUB_SYS_FORCE_SHUTDOWN |
			//BIT_PMU_APB_PD_PUB_SYS_AUTO_SHUTDOWN_EN |
			BIT_PMU_APB_PD_PUB_SYS_PWR_ON_DLY(0x01) |
			BIT_PMU_APB_PD_PUB_SYS_PWR_ON_SEQ_DLY(0x0a) |
			BIT_PMU_APB_PD_PUB_SYS_ISO_ON_DLY(0x02) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_XTL_WAIT_CNT,
			BIT_PMU_APB_XTL0_WAIT_CNT(0x05) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_XTLBUF_WAIT_CNT,
			BIT_PMU_APB_XTLBUF0_WAIT_CNT(0x4) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT0,
			BIT_PMU_APB_CPLL_WAIT_CNT(0x08) |
			BIT_PMU_APB_TWPLL_WAIT_CNT(0x08) |
			BIT_PMU_APB_DPLL_WAIT_CNT(0x08) |
			BIT_PMU_APB_MPLL_WAIT_CNT(0x08) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT1,
			BIT_PMU_APB_GPLL_WAIT_CNT(0x08) |
			BIT_PMU_APB_BBPLL2_WAIT_CNT(0x08) |
			BIT_PMU_APB_BBPLL1_WAIT_CNT(0x08) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG0,
			BIT_PMU_APB_CP_PWR_WAIT_CNT(0x28) |
			BIT_PMU_APB_WCN_PWR_WAIT_CNT(0x28) |
			BIT_PMU_APB_AP_PWR_WAIT_CNT(0x3c) |
			0
		);
		CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG1,
			BIT_PMU_APB_CM4_PWR_WAIT_CNT(0x05) |
			0
		);

		CHIP_REG_AND(REG_PMU_APB_PMU_CLK_CFG,
			~BIT_PMU_APB_CGM_PMU_SEL_REG|
			0
		);

		CHIP_REG_SET(REG_PMU_APB_PWR_ST_DLY0,
			BIT_PMU_APB_CGM_OFF_DLY(0x00) |
			BIT_PMU_APB_CGM_ON_DLY(0x00) |
			BIT_PMU_APB_ISO_OFF_DLY(0x00) |
			BIT_PMU_APB_RST_ASSERT_DLY(0x00) |
			0
		);

		CHIP_REG_SET(REG_PMU_APB_PWR_ST_DLY1,
			BIT_PMU_APB_WAKEUP_LOCK_DLY(0x00) |
			BIT_PMU_APB_RESTORE_DLY(0x00) |
			BIT_PMU_APB_SHUTDOWN_DLY(0x00) |
			BIT_PMU_APB_BISR_RST_DLY(0x00) |
			0
		);

		CHIP_REG_OR(REG_PMU_APB_PMU_CLK_DIV_CFG0,
			BIT_PMU_APB_PWR_ST_CLK_DIV_CFG(0x13)|
			0
		);

		CHIP_REG_OR(REG_PMU_APB_PMU_CLK_DIV_CFG1,
			BIT_PMU_APB_SLP_CTRL_CLK_DIV_CFG(0xc7)|
			0
		);
	}
#endif /*PMU_CLK_32K*/
}

static void disable_clkautogate(void)
{
	__raw_writel(__raw_readl(REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG)
		     & ~(BIT_AP_AHB_CA7_CORE_AUTO_GATE_EN),
		     REG_AP_AHB_AP_SYS_AUTO_SLEEP_CFG);
}

void CSP_Init(uint32_t gen_para)
{
	pmu_commom_config();

	/* Disable clock auto gating bits */
	disable_clkautogate();
}
#endif

#ifdef __cplusplus
}
#endif


