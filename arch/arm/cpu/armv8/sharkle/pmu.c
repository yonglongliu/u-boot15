/******************************************************************************
 ** File Name:      pmu.c                                             *
 ** Author:         Zhongfa.Wang                                              *
 ** DATE:           26/12/2016                                                *
 ** Copyright:      2014 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the basic information on chip.          *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 26/12/2016     Zhongfa.Wang		Create.                                   *
 ******************************************************************************/

/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/
#include <asm/io.h>
#include "adi_hal_internal.h"
//#include "asm/arch/wdg_drvapi.h"
#include "asm/arch-sharkle/sprd_reg.h"
#include "asm/arch-sharkle/common.h"
/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif

#ifndef CONFIG_FPGA
void pmu_commom_config(void)
{
	uint32_t reg_val;

	CHIP_REG_SET(REG_PMU_APB_PD_CA53_TOP_CFG,
		//BIT_PMU_APB_PD_CA53_TOP_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_TOP_PD_SEL |
		//BIT_PMU_APB_PD_CA53_TOP_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_CA53_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_TOP_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_CA53_TOP_ISO_ON_DLY(0xFF) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_C0_CFG,
		//BIT_PMU_APB_PD_CA53_C0_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_C0_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_C0_PD_SEL |
		//BIT_PMU_APB_PD_CA53_C0_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_CA53_C0_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_C0_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA53_C0_PWR_ON_SEQ_DLY(0x05) |
		BIT_PMU_APB_PD_CA53_C0_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_C1_CFG,
		//BIT_PMU_APB_PD_CA53_C1_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_C1_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_C1_PD_SEL |
		BIT_PMU_APB_PD_CA53_C1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_C1_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_C1_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA53_C1_PWR_ON_SEQ_DLY(0x04) |
		BIT_PMU_APB_PD_CA53_C1_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_C2_CFG,
		//BIT_PMU_APB_PD_CA53_C2_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_C2_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_C2_PD_SEL |
		BIT_PMU_APB_PD_CA53_C2_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_C2_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_C2_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA53_C2_PWR_ON_SEQ_DLY(0x03) |
		BIT_PMU_APB_PD_CA53_C2_ISO_ON_DLY(0x03) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_C3_CFG,
		//BIT_PMU_APB_PD_CA53_C3_WFI_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_C3_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_CA53_C3_PD_SEL |
		BIT_PMU_APB_PD_CA53_C3_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_CA53_C3_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_CA53_C3_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_CA53_C3_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_CA53_C3_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_CA53_TOP_CFG2,
		BIT_PMU_APB_PD_CA53_TOP_DCDC_PWR_ON_DLY(0x7D) |
		BIT_PMU_APB_PD_CA53_TOP_DCDC_PWR_OFF_DLY(0xFA) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_AP_SYS_CFG,
		//BIT_PMU_APB_PD_AP_SYS_FORCE_SHUTDOWN |
		BIT_PMU_APB_PD_AP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_AP_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_AP_SYS_ISO_ON_DLY(0x06) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_MM_TOP_CFG,
		BIT_PMU_APB_PD_MM_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_MM_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_MM_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_MM_TOP_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_MM_TOP_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GPU_TOP_CFG,
		//BIT_PMU_APB_PD_GPU_TOP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_GPU_TOP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_GPU_TOP_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LTE_P1_CFG,
		BIT_PMU_APB_PD_WTLCP_LTE_P1_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LTE_P1_AUTO_SHUTDOWN_EN  |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_WTLCP_LTE_P1_ISO_ON_DLY(0x04) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_LDSP_CFG,
		//BIT_PMU_APB_PD_WTLCP_LDSP_PD_SEL |
		BIT_PMU_APB_PD_WTLCP_LDSP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_LDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_LDSP_PWR_ON_SEQ_DLY(0x04) |
		BIT_PMU_APB_PD_WTLCP_LDSP_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_TGDSP_CFG,
		//BIT_PMU_APB_PD_WTLCP_TGDSP_PD_SEL |
		BIT_PMU_APB_PD_WTLCP_TGDSP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_TGDSP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_PWR_ON_SEQ_DLY(0x05) |
		BIT_PMU_APB_PD_WTLCP_TGDSP_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_HU3GE_A_CFG,
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_HU3GE_A_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_PWR_ON_SEQ_DLY(0x03) |
		BIT_PMU_APB_PD_WTLCP_HU3GE_A_ISO_ON_DLY(0x03) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WTLCP_SYS_CFG,
		BIT_PMU_APB_PD_WTLCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WTLCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_WTLCP_SYS_ISO_ON_DLY(0x05) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_PUBCP_SYS_CFG,
		//BIT_PMU_APB_PD_PUBCP_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_PUBCP_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_PUBCP_SYS_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_PUB_SYS_CFG,
		//BIT_PMU_APB_PD_PUB_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_PUB_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_PUB_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_PUB_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_PUB_SYS_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTL_WAIT_CNT,
		BIT_PMU_APB_XTL1_WAIT_CNT(0x46) |
		BIT_PMU_APB_XTL0_WAIT_CNT(0x46) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_XTLBUF_WAIT_CNT,
		BIT_PMU_APB_XTLBUF1_WAIT_CNT(0x01) |
		BIT_PMU_APB_XTLBUF0_WAIT_CNT(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT1,
		BIT_PMU_APB_LTEPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_TWPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_DPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_MPLL_WAIT_CNT(0x08) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PLL_WAIT_CNT2,
		BIT_PMU_APB_ISPPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_RPLL_WAIT_CNT(0x08) |
		BIT_PMU_APB_GPLL_WAIT_CNT(0x08) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PUB_SYS_SLEEP_BYPASS_CFG,
		//BIT_PMU_APB_PUB_SYS_SELF_REFRESH_FLAG_BYPASS |
		//BIT_PMU_APB_PUB_SYS_PWR_PD_ACK_BYPASS |
		//BIT_PMU_APB_PUB_SYS_DEEP_SLEEP_LOCK_ACK_BYPASS |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WCN_SYS_CFG,
		//BIT_PMU_APB_PD_WCN_SYS_DBG_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WCN_SYS_PD_SEL | /*Not Used */
		//BIT_PMU_APB_PD_WCN_SYS_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WCN_SYS_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WCN_SYS_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WCN_SYS_PWR_ON_SEQ_DLY(0x01) |
		BIT_PMU_APB_PD_WCN_SYS_ISO_ON_DLY(0x03) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_WIFI_WRAP_CFG,
		//BIT_PMU_APB_PD_WIFI_WRAP_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_WIFI_WRAP_PD_SEL |
		//BIT_PMU_APB_PD_WIFI_WRAP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_WIFI_WRAP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_WIFI_WRAP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_WIFI_WRAP_PWR_ON_SEQ_DLY(0x03) |
		BIT_PMU_APB_PD_WIFI_WRAP_ISO_ON_DLY(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PD_GNSS_WRAP_CFG,
		//BIT_PMU_APB_PD_GNSS_WRAP_DBG_SHUTDOWN_EN |
		//BIT_PMU_APB_PD_GNSS_WRAP_PD_SEL |
		//BIT_PMU_APB_PD_GNSS_WRAP_FORCE_SHUTDOWN |
		//BIT_PMU_APB_PD_GNSS_WRAP_AUTO_SHUTDOWN_EN |
		BIT_PMU_APB_PD_GNSS_WRAP_PWR_ON_DLY(0x01) |
		BIT_PMU_APB_PD_GNSS_WRAP_PWR_ON_SEQ_DLY(0x02) |
		BIT_PMU_APB_PD_GNSS_WRAP_ISO_ON_DLY(0x02) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG0,
		BIT_PMU_APB_PUBCP_PWR_WAIT_CNT(0x08) |
		BIT_PMU_APB_WTLCP_PWR_WAIT_CNT(0x08) |
		BIT_PMU_APB_AP_PWR_WAIT_CNT(0x08) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_CNT_WAIT_CFG1,
		BIT_PMU_APB_SP_SYS_PWR_WAIT_CNT(0x08) |
		BIT_PMU_APB_WCN_SYS_PWR_WAIT_CNT(0x08) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_DDR_SLP_WAIT_CNT,
		BIT_PMU_APB_PUB_SYS_DEEP_SLEEP_WAIT_CNT(0x0) |
		BIT_PMU_APB_PUB_SYS_SLEEP_WAIT_CNT(0x0) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PMU_CLK_DIV_CFG,
		BIT_PMU_APB_PWR_ST_CLK_DIV_CFG(0x0F) |
		BIT_PMU_APB_SLP_CTRL_CLK_DIV_CFG(0x7F) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_CGM_PMU_SEL,
		BIT_PMU_APB_CGM_PMU_SEL_REG(0x01) |
		0
	);
	CHIP_REG_SET(REG_PMU_APB_PWR_DGB_PARAMETER,
		BIT_PMU_APB_ISO_OFF_DLY(0x01) |
		BIT_PMU_APB_CGM_ON_DLY(0x01) |
		BIT_PMU_APB_RST_ASSERT_DLY(0x01) |
		0
	);
	reg_val = CHIP_REG_GET(REG_PMU_APB_ANALOG_PHY_PD_CFG) & 0x0F;
	CHIP_REG_SET(REG_PMU_APB_ANALOG_PHY_PD_CFG,
		reg_val |
		BIT_PMU_APB_PHY_PWR_DLY(0x01) |
		0
	);
}

/*sharkLE deepsleep: 0.7V; normal: 0.9V*/
static void dcdc_core_ds_config(uint32_t core_cal_para, uint32_t core_ctrl_para)
{
	ANA_REG_SET(ANA_REG_GLB_DCDC_CORE_SLP_CTRL1,
			BITS_DCDC_CORE_CAL_DS_SW(core_cal_para)|
			BITS_DCDC_CORE_CTRL_DS_SW(core_ctrl_para)
	);
}

void CSP_Init(uint32_t gen_para)
{
	pmu_commom_config();
	dcdc_core_ds_config(0x0,0x3);
}
#endif

/**---------------------------------------------------------------------------*
 **                         Compiler Flag                                     *
 **---------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif


