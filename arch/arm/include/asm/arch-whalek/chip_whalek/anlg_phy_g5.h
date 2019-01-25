/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2017-12-14 16:29:52
 *
 */


#ifndef ANLG_PHY_G5_H
#define ANLG_PHY_G5_H

#define CTL_BASE_ANLG_PHY_G5 0x323D0000


#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_PWR_CTRL       ( CTL_BASE_ANLG_PHY_G5 + 0x0000 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_RST_CTRL       ( CTL_BASE_ANLG_PHY_G5 + 0x0004 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_EN_CTRL        ( CTL_BASE_ANLG_PHY_G5 + 0x0008 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL0            ( CTL_BASE_ANLG_PHY_G5 + 0x000C )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL1            ( CTL_BASE_ANLG_PHY_G5 + 0x0010 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL2            ( CTL_BASE_ANLG_PHY_G5 + 0x0014 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_CTRL        ( CTL_BASE_ANLG_PHY_G5 + 0x0018 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_PLL_CLKEN             ( CTL_BASE_ANLG_PHY_G5 + 0x001C )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_RESERVED         ( CTL_BASE_ANLG_PHY_G5 + 0x0020 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_PERFOR           ( CTL_BASE_ANLG_PHY_G5 + 0x0028 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANALOG_TEST           ( CTL_BASE_ANLG_PHY_G5 + 0x002C )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_CTRL1            ( CTL_BASE_ANLG_PHY_G5 + 0x0030 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_CTRL2            ( CTL_BASE_ANLG_PHY_G5 + 0x0034 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_RSVD           ( CTL_BASE_ANLG_PHY_G5 + 0x0038 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_RTC4M_CTRL            ( CTL_BASE_ANLG_PHY_G5 + 0x003C )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_CTRL         ( CTL_BASE_ANLG_PHY_G5 + 0x0040 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_0           ( CTL_BASE_ANLG_PHY_G5 + 0x0044 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_WRAP_GLUE_CTRL        ( CTL_BASE_ANLG_PHY_G5 + 0x0048 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_1           ( CTL_BASE_ANLG_PHY_G5 + 0x004C )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_2           ( CTL_BASE_ANLG_PHY_G5 + 0x0050 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_3           ( CTL_BASE_ANLG_PHY_G5 + 0x0054 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_4           ( CTL_BASE_ANLG_PHY_G5 + 0x0058 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_CAL             ( CTL_BASE_ANLG_PHY_G5 + 0x005C )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_CAL              ( CTL_BASE_ANLG_PHY_G5 + 0x0060 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_CAL              ( CTL_BASE_ANLG_PHY_G5 + 0x0064 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_CAL              ( CTL_BASE_ANLG_PHY_G5 + 0x0068 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_PLL_FREQ_CAL_CFG      ( CTL_BASE_ANLG_PHY_G5 + 0x006C )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_RESULT          ( CTL_BASE_ANLG_PHY_G5 + 0x0070 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_RESULT           ( CTL_BASE_ANLG_PHY_G5 + 0x0074 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_RESULT           ( CTL_BASE_ANLG_PHY_G5 + 0x0078 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_RESULT           ( CTL_BASE_ANLG_PHY_G5 + 0x007C )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_PLL_TEST_FLAG         ( CTL_BASE_ANLG_PHY_G5 + 0x0080 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_ISPPLL_CTRL0          ( CTL_BASE_ANLG_PHY_G5 + 0x0084 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_0         ( CTL_BASE_ANLG_PHY_G5 + 0x0088 )
#define REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_1         ( CTL_BASE_ANLG_PHY_G5 + 0x008C )
#define REG_ANLG_PHY_G5_ANALOG_THM1_THM1_CTL                ( CTL_BASE_ANLG_PHY_G5 + 0x0090 )
#define REG_ANLG_PHY_G5_ANALOG_THM1_THM1_RESERVED_CTL       ( CTL_BASE_ANLG_PHY_G5 + 0x0094 )
#define REG_ANLG_PHY_G5_ANALOG_THM1_WRAP_GLUE_CTRL          ( CTL_BASE_ANLG_PHY_G5 + 0x0098 )
#define REG_ANLG_PHY_G5_ANALOG_THM1_REG_SEL_CFG_0           ( CTL_BASE_ANLG_PHY_G5 + 0x009C )
#define REG_ANLG_PHY_G5_ANALOG_RPLL_SEL                     ( CTL_BASE_ANLG_PHY_G5 + 0x00A0 )
#define REG_ANLG_PHY_G5_ANALOG_AAPC_RAMP_GEN_SEL            ( CTL_BASE_ANLG_PHY_G5 + 0x00A4 )

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_PWR_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_PD                                BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_REC_26MHZ_0_BUF_PD                     BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_PD                              BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_PD                              BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_RST_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_RST                               BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RTC100M_RSTB                           BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_EN_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_DIV_EN                            BIT(24)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CLKOUT_EN                         BIT(23)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_POSTDIV                           BIT(22)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_CLK26MHZ_AUD_EN                        BIT(21)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RTC100M_EN                             BIT(20)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_SEL(x)                           (((x) & 0x3F) << 14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_SINDRV_ENA                             BIT(13)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_SINDRV_ENA_SQUARE                      BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_REC_26MHZ_SR_TRIM(x)                   (((x) & 0xF) << 8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_REC_26MHZ_0_CUR_SEL(x)                 (((x) & 0x3) << 6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_CLK26M_RESERVED(x)                     (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_SINE_DRV_SEL                           BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_BB_CON_BG                              BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_N(x)                              (((x) & 0x7FF) << 11)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_IBIAS(x)                          (((x) & 0x3) << 9)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_LPF(x)                            (((x) & 0x7) << 6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_SDM_EN                            BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_MOD_EN                            BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_DIV_S                             BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_REF_SEL(x)                        (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_26M_SEL                           BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_NINT(x)                           (((x) & 0x7F) << 23)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_KINT(x)                           (((x) & 0x7FFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CTRL2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_EN                           BIT(7)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_26M_DIV(x)                        (((x) & 0x3F) << 1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_LOCK_DONE                         BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_CTRL(x)                      (((x) & 0xFF) << 16)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_BIST_CNT(x)                       (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_PLL_CLKEN */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_SINEO_RPLL_CLKOUT_EN                   BIT(8)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_SSC_CTRL(x)                       (((x) & 0xFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_RESERVED */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_RESERVED(x)                       (((x) & 0x1FFFFF) << 3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_VSET(x)                           (((x) & 0x7))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_PERFOR */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_ICP(x)                            (((x) & 0x7) << 10)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CP_EN                             BIT(9)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_LDO_TRIM(x)                       (((x) & 0xF) << 5)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_VCO_TEST_EN                       BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_FBDIV_EN                          BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_CP_OFFSET(x)                      (((x) & 0x3) << 1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_FREQ_DOUBLE_EN                    BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANALOG_TEST */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_ANALOG_TESTMUX(x)                      (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_CTRL1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_G0(x)                             (((x) & 0x3) << 24)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_G1(x)                             (((x) & 0x3) << 22)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_G2(x)                             (((x) & 0x3) << 20)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_LOW_V_CON                       BIT(19)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_D(x)                            (((x) & 0x3FFF) << 5)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_BPRES                           BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_APCOUT_SEL(x)                        (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_S_AAPC_RESERVED(x)                     (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_CTRL2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_D(x)                            (((x) & 0x3FFF) << 6)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_LOW_V_CON                       BIT(5)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_BPRES                           BIT(4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_APCOUT_SEL(x)                        (((x) & 0x3) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_M_AAPC_RESERVED(x)                     (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_RSVD */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_ANA_BB_RESERVED(x)                     (((x) & 0xFFFF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TO_LVDS_SEL(x)                         (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_RTC4M_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RTC100M_RESERVED(x)                    (((x) & 0xFF) << 13)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RTC100M_LDO_EN                         BIT(12)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RTC100M_LDO_BYPASS                     BIT(11)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RTC100M_LDO_VOLTAGE_SEL(x)             (((x) & 0x3) << 9)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RTC100M_LDO_BIAS_SEL(x)                (((x) & 0x3) << 7)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RTC100M_RC_C(x)                        (((x) & 0x7F))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_EN                            BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_OD                            BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_TEST_CLK_DIV(x)                        (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_MAX_RANGE(x)                      (((x) & 0x3FFF) << 17)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_MIN_RANGE(x)                      (((x) & 0x3FFF) << 3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_RSTN                              BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_GEN_SEL(x)                        (((x) & 0x3))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_STEP_SEL(x)                       (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_PD_SEL                            BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_RPLL_RST_SEL                           BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_1 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_SQUA_D0(x)                        (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_SQUA_D1(x)                        (((x) & 0x3FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_2 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_SQUA_D2(x)                        (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_SQUA_D3(x)                        (((x) & 0x3FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_3 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_SQUA_D4(x)                        (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_SQUA_D5(x)                        (((x) & 0x3FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_TEST_4 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_SQUA_D6(x)                        (((x) & 0x3FFF) << 14)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AAPC_SQUA_D7(x)                        (((x) & 0x3FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_CAL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_MAX_RANGE(x)                     (((x) & 0x7FFF) << 15)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_MIN_RANGE(x)                     (((x) & 0x7FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_CAL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_MAX_RANGE(x)                      (((x) & 0x7FFF) << 15)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_MIN_RANGE(x)                      (((x) & 0x7FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_CAL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_MAX_RANGE(x)                      (((x) & 0x7FFF) << 15)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_MIN_RANGE(x)                      (((x) & 0x7FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_CAL */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_MAX_RANGE(x)                      (((x) & 0x7FFF) << 15)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_MIN_RANGE(x)                      (((x) & 0x7FFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_PLL_FREQ_CAL_CFG */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_DIV_NUM_26M(x)                         (((x) & 0x3FF) << 4)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_CAL_EN                            BIT(3)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_CAL_EN                            BIT(2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_CAL_EN                            BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_CAL_EN                           BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_RESULT */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_FREQ(x)                          (((x) & 0x7FFF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_READY                            BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PROBE_PASS                             BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_RESULT */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_FREQ(x)                           (((x) & 0x7FFF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_READY                             BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX0_PASS                              BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_RESULT */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_FREQ(x)                           (((x) & 0x7FFF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_READY                             BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX1_PASS                              BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_RESULT */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_FREQ(x)                           (((x) & 0x7FFF) << 2)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_READY                             BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_AUX2_PASS                              BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_PLL_TEST_FLAG */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_PLLS_FLAG(x)                           (((x) & 0xFFFFFFFF))

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_ISPPLL_CTRL0 */

#define BIT_ANLG_PHY_G5_ANALOG_BB_TOP_BB_BG_RBIAS_MODE                       BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_PD                        BIT(31)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_REC_26MHZ_0_BUF_PD             BIT(30)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_PD                      BIT(29)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_PD                      BIT(28)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_RST                       BIT(27)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RTC100M_RSTB                   BIT(26)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_DIV_EN                    BIT(25)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_CLKOUT_EN                 BIT(24)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_CLK26MHZ_AUD_EN                BIT(23)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RTC100M_EN                     BIT(22)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_SINDRV_ENA                     BIT(21)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_SINDRV_ENA_SQUARE              BIT(20)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_N                         BIT(19)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_IBIAS                     BIT(18)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_LPF                       BIT(17)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_SDM_EN                    BIT(16)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_MOD_EN                    BIT(15)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_DIV_S                     BIT(14)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_REF_SEL                   BIT(13)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_NINT                      BIT(12)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_KINT                      BIT(11)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_BIST_EN                   BIT(10)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_26M_DIV                   BIT(9)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_BIST_CTRL                 BIT(8)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RPLL_RESERVED                  BIT(7)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_AAPC_G0                        BIT(6)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_AAPC_G1                        BIT(5)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_AAPC_G2                        BIT(4)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_LOW_V_CON               BIT(3)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_D                       BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_BPRES                   BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_APCOUT_SEL                   BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_BB_TOP_REG_SEL_CFG_1 */

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_S_AAPC_RESERVED                BIT(6)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_D                       BIT(5)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_LOW_V_CON               BIT(4)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_BPRES                   BIT(3)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_APCOUT_SEL                   BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_M_AAPC_RESERVED                BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_BB_TOP_RTC100M_RC_C                   BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_THM1_THM1_CTL */

#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_RSTN                                 BIT(27)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_RUN                                  BIT(26)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_PD                                   BIT(25)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_VALID                                BIT(24)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_BG_RBIAS_MODE                        BIT(23)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_TEST_SEL(x)                          (((x) & 0x3) << 21)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_BP_MODE                              BIT(20)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_DATA(x)                              (((x) & 0x3FF) << 10)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_BP_DATA(x)                           (((x) & 0x3FF))

/* REG_ANLG_PHY_G5_ANALOG_THM1_THM1_RESERVED_CTL */

#define BIT_ANLG_PHY_G5_ANALOG_THM1_THM_RESERVED(x)                          (((x) & 0xFFFF))

/* REG_ANLG_PHY_G5_ANALOG_THM1_WRAP_GLUE_CTRL */

#define BIT_ANLG_PHY_G5_ANALOG_THM1_DGB_SEL_THM_RESERVED_BIT0_CONVERT_CYCLE  BIT(1)
#define BIT_ANLG_PHY_G5_ANALOG_THM1_DGB_SEL_THM_RESERVED_BIT3_SENSOR_SEL     BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_THM1_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_THM1_THM_RSTN                         BIT(2)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_THM1_THM_RUN                          BIT(1)
#define BIT_ANLG_PHY_G5_DBG_SEL_ANALOG_THM1_THM_PD                           BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_RPLL_SEL */

#define BIT_ANLG_PHY_G5_RPLL_PD_SEL_RFTI_OR_PMU                              BIT(1)
#define BIT_ANLG_PHY_G5_RPLL_RST_SEL_RFTI_OR_PMU                             BIT(0)

/* REG_ANLG_PHY_G5_ANALOG_AAPC_RAMP_GEN_SEL */

#define BIT_ANLG_PHY_G5_R2G_RAMP_GEN_SEL                                     BIT(0)


#endif /* ANLG_PHY_G5_H */


