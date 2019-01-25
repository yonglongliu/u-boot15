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


#ifndef ANLG_PHY_G2_AP_H
#define ANLG_PHY_G2_AP_H

#define CTL_BASE_ANLG_PHY_G2_AP 0x32440000


#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXCLKLANE          ( CTL_BASE_ANLG_PHY_G2_AP + 0x0000 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_0           ( CTL_BASE_ANLG_PHY_G2_AP + 0x0004 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_1           ( CTL_BASE_ANLG_PHY_G2_AP + 0x0008 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_2           ( CTL_BASE_ANLG_PHY_G2_AP + 0x000C )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_3           ( CTL_BASE_ANLG_PHY_G2_AP + 0x0010 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATAESC          ( CTL_BASE_ANLG_PHY_G2_AP + 0x0014 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_STATE_RX           ( CTL_BASE_ANLG_PHY_G2_AP + 0x0018 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_ERR                ( CTL_BASE_ANLG_PHY_G2_AP + 0x001C )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_CTRL               ( CTL_BASE_ANLG_PHY_G2_AP + 0x0020 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_RSVD               ( CTL_BASE_ANLG_PHY_G2_AP + 0x0024 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TEST               ( CTL_BASE_ANLG_PHY_G2_AP + 0x0028 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_DATALANE_CTRL      ( CTL_BASE_ANLG_PHY_G2_AP + 0x002C )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_DUMY_CTRL             ( CTL_BASE_ANLG_PHY_G2_AP + 0x0030 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_MIPI_CTRL7                ( CTL_BASE_ANLG_PHY_G2_AP + 0x0034 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_0             ( CTL_BASE_ANLG_PHY_G2_AP + 0x0038 )
#define REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_1             ( CTL_BASE_ANLG_PHY_G2_AP + 0x003C )

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXCLKLANE */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTHSCLK             BIT(4)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSCLK                  BIT(3)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXITCLK              BIT(2)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATECLK               BIT(1)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ULPSACTIVENOTCLK           BIT(0)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_0 */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_0          BIT(10)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_0             BIT(9)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_0                BIT(8)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_0                BIT(7)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_0               BIT(6)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_0(x)          (((x) & 0xF) << 2)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_0               BIT(1)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREADYESC_0               BIT(0)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_1 */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_1          BIT(10)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_1             BIT(9)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_1                BIT(7)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_1               BIT(6)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_2 */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_2          BIT(10)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_2             BIT(9)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_2                BIT(7)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_2               BIT(6)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATA_3 */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_3          BIT(10)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_3             BIT(9)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_3                BIT(7)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_3               BIT(6)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TXDATAESC */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_0(x)             (((x) & 0xFF) << 24)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_STATE_RX */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_RXLPDTESC_0                BIT(23)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_RXTRIGGERESC_0(x)          (((x) & 0xF) << 19)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_RXVALIDESC_0               BIT(18)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_ERR */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ERRESC_0                   BIT(19)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ERRSYNCESC_0               BIT(18)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTROL_0               BIT(17)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP0_0         BIT(16)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ERRCONTENTIONLP1_0         BIT(15)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_CTRL */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_PS_PD_S                    BIT(21)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_PS_PD_L                    BIT(20)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_SHUTDOWNZ                  BIT(19)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_RSTZ                       BIT(18)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_0                   BIT(17)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_1                   BIT(16)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_2                   BIT(15)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_3                   BIT(14)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_ENABLECLK                  BIT(13)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_FORCEPLL                   BIT(12)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_PLLLOCK                    BIT(11)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_RSVD */


/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_TEST */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TESTDIN(x)                 (((x) & 0xFF) << 11)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TESTDOUT(x)                (((x) & 0xFF) << 3)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TESTEN                     BIT(2)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TESTCLK                    BIT(1)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TESTCLR                    BIT(0)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_4L_DATALANE_CTRL */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_0              BIT(22)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_DIRECTION_0                BIT(21)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATEDATA_0            BIT(17)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATEDATA_1            BIT(12)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATEDATA_2            BIT(6)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_STOPSTATEDATA_3            BIT(0)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_DUMY_CTRL */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_ANALOG_DSI_DUMY_IN(x)          (((x) & 0xFFFF) << 16)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_ANALOG_DSI_DUMY_OUT(x)         (((x) & 0xFFFF))

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_MIPI_CTRL7 */

#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXSKEWCALHS_0              BIT(3)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXSKEWCALHS_1              BIT(2)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXSKEWCALHS_2              BIT(1)
#define BIT_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_DSI_TXSKEWCALHS_3              BIT(0)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_0 */

#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTHSCLK     BIT(31)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSCLK          BIT(30)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXITCLK      BIT(29)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_0  BIT(28)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_0     BIT(27)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXLPDTESC_0        BIT(26)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_0        BIT(25)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_0       BIT(24)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXTRIGGERESC_0     BIT(23)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXVALIDESC_0       BIT(22)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_1  BIT(21)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_1     BIT(20)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_1        BIT(19)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_1       BIT(18)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_2  BIT(17)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_2     BIT(16)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_2        BIT(15)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_2       BIT(14)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTDATAHS_3  BIT(13)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXREQUESTESC_3     BIT(12)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSESC_3        BIT(11)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXULPSEXIT_3       BIT(10)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXDATAESC_0        BIT(9)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_PS_PD_S            BIT(8)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_PS_PD_L            BIT(7)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_SHUTDOWNZ          BIT(6)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_RSTZ               BIT(5)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_0           BIT(4)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_1           BIT(3)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_2           BIT(2)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLE_3           BIT(1)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_ENABLECLK          BIT(0)

/* REG_ANLG_PHY_G2_AP_ANALOG_MIPI_DSI_4LANE_REG_SEL_CFG_1 */

#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_FORCEPLL           BIT(9)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TESTDIN            BIT(8)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TESTEN             BIT(7)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TESTCLK            BIT(6)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TESTCLR            BIT(5)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TURNREQUEST_0      BIT(4)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXSKEWCALHS_0      BIT(3)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXSKEWCALHS_1      BIT(2)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXSKEWCALHS_2      BIT(1)
#define BIT_ANLG_PHY_G2_AP_DBG_SEL_ANALOG_MIPI_DSI_4LANE_DSI_TXSKEWCALHS_3      BIT(0)


#endif /* ANLG_PHY_G2_AP_H */


