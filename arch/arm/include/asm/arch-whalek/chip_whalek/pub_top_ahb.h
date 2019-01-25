/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-06-15 20:32:44
 *
 */


#ifndef PUB_TOP_AHB_H
#define PUB_TOP_AHB_H

#define CTL_BASE_PUB_TOP_AHB 0x30200000


#define REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL           ( CTL_BASE_PUB_TOP_AHB + 0x0000 )
#define REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL0        ( CTL_BASE_PUB_TOP_AHB + 0x0010 )
#define REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL1        ( CTL_BASE_PUB_TOP_AHB + 0x0014 )
#define REG_PUB_TOP_AHB_DMC_RST_CTL                ( CTL_BASE_PUB_TOP_AHB + 0x0080 )
#define REG_PUB_TOP_AHB_DMC_EMC_REF_SEL            ( CTL_BASE_PUB_TOP_AHB + 0x0084 )
#define REG_PUB_TOP_AHB_HSEL_IDLE_CNT              ( CTL_BASE_PUB_TOP_AHB + 0x0088 )
#define REG_PUB_TOP_AHB_DMC_CLK_INIT_SW_START      ( CTL_BASE_PUB_TOP_AHB + 0x0100 )
#define REG_PUB_TOP_AHB_DMC_CLK_STATE              ( CTL_BASE_PUB_TOP_AHB + 0x0104 )
#define REG_PUB_TOP_AHB_DMC_CLK_INIT_CFG           ( CTL_BASE_PUB_TOP_AHB + 0x0108 )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CFG        ( CTL_BASE_PUB_TOP_AHB + 0x0200 )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT0       ( CTL_BASE_PUB_TOP_AHB + 0x0204 )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT1       ( CTL_BASE_PUB_TOP_AHB + 0x0208 )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT2       ( CTL_BASE_PUB_TOP_AHB + 0x020C )
#define REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT3       ( CTL_BASE_PUB_TOP_AHB + 0x0210 )
#define REG_PUB_TOP_AHB_DMC_DDL_CTRL               ( CTL_BASE_PUB_TOP_AHB + 0x0300 )

/* REG_PUB_TOP_AHB_DMC_DDR_CLK_CTRL */

#define BIT_PUB_TOP_AHB_PUB_CLK_DFS_AUTO_GATE_EN            BIT(28)
#define BIT_PUB_TOP_AHB_DMC_SREF_AUTO_GATE_EN               BIT(26)
#define BIT_PUB_TOP_AHB_DDR_PHY_AUTO_GATE_EN                BIT(25)
#define BIT_PUB_TOP_AHB_DDR_UMCTL_AUTO_GATE_EN              BIT(24)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_FORCE_PHASE(x)       (((x) & 0x3) << 18)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_FORCE_PHASE_SEL      BIT(17)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_FORCE_BYP            BIT(16)
#define BIT_PUB_TOP_AHB_PUB_CLK_DFS_EB                      BIT(15)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_D2_CPU_EB               BIT(14)
#define BIT_PUB_TOP_AHB_PUB_CLK_MLB_D2_EB                   BIT(13)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_D2_EB                   BIT(12)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_X1_EB                   BIT(11)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_EB                   BIT(10)
#define BIT_PUB_TOP_AHB_PUB_CLK_DCC_EB                      BIT(9)
#define BIT_PUB_TOP_AHB_PUB_DDR_CLK_EB                      BIT(8)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_D2_CPU_CGM_SEL          BIT(6)
#define BIT_PUB_TOP_AHB_PUB_CLK_MLB_D2_CGM_SEL              BIT(5)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_D2_CGM_SEL              BIT(4)
#define BIT_PUB_TOP_AHB_PUB_CLK_DMC_X1_CGM_SEL              BIT(3)
#define BIT_PUB_TOP_AHB_PUB_CLK_PHY_X2_CGM_SEL              BIT(2)
#define BIT_PUB_TOP_AHB_PUB_CLK_DCC_CGM_SEL                 BIT(1)
#define BIT_PUB_TOP_AHB_PUB_DDR_CLK_CGM_SEL                 BIT(0)

/* REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL0 */

#define BIT_PUB_TOP_AHB_DDR_CHN7_AXI_LP_EN                  BIT(23)
#define BIT_PUB_TOP_AHB_DDR_CHN6_AXI_LP_EN                  BIT(22)
#define BIT_PUB_TOP_AHB_DDR_CHN5_AXI_LP_EN                  BIT(21)
#define BIT_PUB_TOP_AHB_DDR_CHN4_AXI_LP_EN                  BIT(20)
#define BIT_PUB_TOP_AHB_DDR_CHN3_AXI_LP_EN                  BIT(19)
#define BIT_PUB_TOP_AHB_DDR_CHN2_AXI_LP_EN                  BIT(18)
#define BIT_PUB_TOP_AHB_DDR_CHN1_AXI_LP_EN                  BIT(17)
#define BIT_PUB_TOP_AHB_DDR_CHN0_AXI_LP_EN                  BIT(16)
#define BIT_PUB_TOP_AHB_DDR_CHN7_CGM_SEL                    BIT(7)
#define BIT_PUB_TOP_AHB_DDR_CHN6_CGM_SEL                    BIT(6)
#define BIT_PUB_TOP_AHB_DDR_CHN5_CGM_SEL                    BIT(5)
#define BIT_PUB_TOP_AHB_DDR_CHN4_CGM_SEL                    BIT(4)
#define BIT_PUB_TOP_AHB_DDR_CHN3_CGM_SEL                    BIT(3)
#define BIT_PUB_TOP_AHB_DDR_CHN2_CGM_SEL                    BIT(2)
#define BIT_PUB_TOP_AHB_DDR_CHN1_CGM_SEL                    BIT(1)
#define BIT_PUB_TOP_AHB_DDR_CHN0_CGM_SEL                    BIT(0)

/* REG_PUB_TOP_AHB_DDR_CHN_SLEEP_CTRL1 */

#define BIT_PUB_TOP_AHB_DDR_CHN7_AXI_STOP_SEL               BIT(7)
#define BIT_PUB_TOP_AHB_DDR_CHN6_AXI_STOP_SEL               BIT(6)
#define BIT_PUB_TOP_AHB_DDR_CHN5_AXI_STOP_SEL               BIT(5)
#define BIT_PUB_TOP_AHB_DDR_CHN4_AXI_STOP_SEL               BIT(4)
#define BIT_PUB_TOP_AHB_DDR_CHN3_AXI_STOP_SEL               BIT(3)
#define BIT_PUB_TOP_AHB_DDR_CHN2_AXI_STOP_SEL               BIT(2)
#define BIT_PUB_TOP_AHB_DDR_CHN1_AXI_STOP_SEL               BIT(1)
#define BIT_PUB_TOP_AHB_DDR_CHN0_AXI_STOP_SEL               BIT(0)

/* REG_PUB_TOP_AHB_DMC_RST_CTL */

#define BIT_PUB_TOP_AHB_DCC_SOFT_RST                        BIT(1)
#define BIT_PUB_TOP_AHB_DDRPHY_SOFT_RST                     BIT(0)

/* REG_PUB_TOP_AHB_DMC_EMC_REF_SEL */

#define BIT_PUB_TOP_AHB_DMC_EMC_REF_SEL                     BIT(0)

/* REG_PUB_TOP_AHB_HSEL_IDLE_CNT */

#define BIT_PUB_TOP_AHB_HSEL_IDLE_CNT(x)                    (((x) & 0xFF))

/* REG_PUB_TOP_AHB_DMC_CLK_INIT_SW_START */

#define BIT_PUB_TOP_AHB_DMC_CLK_INIT_SW_START               BIT(0)

/* REG_PUB_TOP_AHB_DMC_CLK_STATE */

#define BIT_PUB_TOP_AHB_DMC_CLK_HW_CUR_STATE(x)             (((x) & 0xF) << 4)
#define BIT_PUB_TOP_AHB_DMC_CUR_CLK_MODE(x)                 (((x) & 0x3) << 2)
#define BIT_PUB_TOP_AHB_DMC_CLK_INIT_SW_DONE                BIT(0)

/* REG_PUB_TOP_AHB_DMC_CLK_INIT_CFG */

#define BIT_PUB_TOP_AHB_DESKEW_PLL_PD_DEFAULT_SW            BIT(5)
#define BIT_PUB_TOP_AHB_DESKEW_PLL_PD_DEFAULT_SEL           BIT(4)
#define BIT_PUB_TOP_AHB_DFS_CLK_AUTO_MODE                   BIT(0)

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CFG */

#define BIT_PUB_TOP_AHB_DSKDLL_DCC_FINE_WAIT_SRC_SW         BIT(10)
#define BIT_PUB_TOP_AHB_DSKDLL_DCC_COARSE_WAIT_SRC_SW       BIT(9)
#define BIT_PUB_TOP_AHB_DSKPLL_LOCK_WAIT_SRC_SW             BIT(8)
#define BIT_PUB_TOP_AHB_DDL_ADJS_V_WAIT_EN                  BIT(3)
#define BIT_PUB_TOP_AHB_DSKDLL_DCC_FINE_WAIT_EN             BIT(2)
#define BIT_PUB_TOP_AHB_DSKDLL_DCC_COARSE_WAIT_EN           BIT(1)
#define BIT_PUB_TOP_AHB_DSKPLL_LOCK_WAIT_EN                 BIT(0)

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT0 */

#define BIT_PUB_TOP_AHB_WAIT_CNT_DSKPLL_PWRON_TIME(x)       (((x) & 0xFFFF) << 16)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DSKPLL_LOCK_TIME(x)        (((x) & 0xFFFF))

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT1 */

#define BIT_PUB_TOP_AHB_WAIT_CNT_DSKDLL_DCC_FINE_TIME(x)    (((x) & 0xFFFF) << 16)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DSKDLL_DCC_COARSE_TIME(x)  (((x) & 0xFFFF))

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT2 */

#define BIT_PUB_TOP_AHB_WAIT_CNT_DFS_RESET_OFF_TIME(x)      (((x) & 0xFF) << 24)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DFS_RESET_ON_TIME(x)       (((x) & 0xFF) << 16)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DFS_CLK_OFF_TIME(x)        (((x) & 0xFF))

/* REG_PUB_TOP_AHB_DMC_DESKEW_WAIT_CNT3 */

#define BIT_PUB_TOP_AHB_WAIT_CNT_DDL_ADJS_V_HIGH_TIME(x)    (((x) & 0xFF) << 16)
#define BIT_PUB_TOP_AHB_WAIT_CNT_DDL_ADJS_V_LOW_TIME(x)     (((x) & 0xFF))

/* REG_PUB_TOP_AHB_DMC_DDL_CTRL */

#define BIT_PUB_TOP_AHB_PTEST_DDL_SCOUT                     BIT(26)
#define BIT_PUB_TOP_AHB_PTEST_DDL_SCIN                      BIT(25)
#define BIT_PUB_TOP_AHB_PTEST_DDL_SE                        BIT(24)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_ADJS(x)                  (((x) & 0x1FF) << 8)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_UPDATE                   BIT(7)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_BYPASS                   BIT(6)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_RESET                    BIT(5)
#define BIT_PUB_TOP_AHB_DMC_DDL_SW_ADJS_VALID               BIT(4)
#define BIT_PUB_TOP_AHB_DMC_DDL_CFG_SRC_PURE_SW             BIT(1)
#define BIT_PUB_TOP_AHB_DMC_DDL_CFG_SRC_SW                  BIT(0)


#endif /* PUB_TOP_AHB_H */

