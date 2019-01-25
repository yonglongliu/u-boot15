/******************************************************************************
 ** File Name:      pinmap.h                                                  *
 ** Author:         Richard.Yang                                              *
 ** DATE:           03/08/2004                                                *
 ** Copyright:      2004 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    This file defines the structure of pin map.               *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 03/08/2004     Richard.Yang     Create.                                   *
 ******************************************************************************/

#ifndef _PINMAP_H_
#define _PINMAP_H_

#include <linux/types.h>
#include "sprd_reg.h"
#include "adi.h"

typedef struct {
	uint32_t reg;
	uint32_t val;
} pinmap_t;
int pin_init(void);

#define CTL_PIN_BASE			(SPRD_PIN_PHYS)

/* registers definitions for controller REG_PIN */
#define REG_PIN_PWR_PAD_CTL_RESERVED             ( 0x0000 )
#define REG_PIN_UART_MATRIX_MTX_CFG              ( 0x0004 )
#define REG_PIN_UART_MATRIX_MTX_CFG1             ( 0x0008 )
#define REG_PIN_IIS_MATRIX_MTX_CFG               ( 0x000C )
#define REG_PIN_SIM_MATRIX_MTX_CFG               ( 0x0010 )
#define REG_PIN_SPI_MATRIX_MTX_CFG               ( 0x0014 )
#define REG_PIN_IIC_MATRIX_MTX_CFG               ( 0x0018 )
#define REG_PIN_CTRL0                            ( 0x001C )
#define REG_PIN_CTRL1                            ( 0x0020 )
#define REG_PIN_CTRL2                            ( 0x0024 )
#define REG_PIN_CTRL3                            ( 0x0028 )
#define REG_PIN_CTRL4                            ( 0x002C )
#define REG_PIN_CTRL5                            ( 0x0030 )
/* registers definitions for controller CTL_PIN */
#define REG_PIN_IIS1CLK                          ( 0x0034 )
#define REG_PIN_IIS1DI                           ( 0x0038 )
#define REG_PIN_IIS1DO                           ( 0x003C )
#define REG_PIN_IIS1LRCK                         ( 0x0040 )
#define REG_PIN_SCL2                             ( 0x0044 )
#define REG_PIN_SDA2                             ( 0x0048 )
#define REG_PIN_CLK_AUX0                         ( 0x004C )
#define REG_PIN_T_DIG                            ( 0x0050 )
#define REG_PIN_GNSS_LNA_EN                      ( 0x0054 )
#define REG_PIN_EXTINT0                          ( 0x0058 )
#define REG_PIN_EXTINT1                          ( 0x005C )
#define REG_PIN_SCL3                             ( 0x0060 )
#define REG_PIN_SDA3                             ( 0x0064 )
#define REG_PIN_SCL0                             ( 0x0068 )
#define REG_PIN_SDA0                             ( 0x006C )
#define REG_PIN_SCL1                             ( 0x0070 )
#define REG_PIN_SDA1                             ( 0x0074 )
#define REG_PIN_CMPD2                            ( 0x0078 )
#define REG_PIN_CMRST2                           ( 0x007C )
#define REG_PIN_CMMCLK0                          ( 0x0080 )
#define REG_PIN_CMRST0                           ( 0x0084 )
#define REG_PIN_CMPD0                            ( 0x0088 )
#define REG_PIN_CMMCLK1                          ( 0x008C )
#define REG_PIN_CMRST1                           ( 0x0090 )
#define REG_PIN_CMPD1                            ( 0x0094 )
#define REG_PIN_U0TXD                            ( 0x0098 )
#define REG_PIN_U0RXD                            ( 0x009C )
#define REG_PIN_U0CTS                            ( 0x00A0 )
#define REG_PIN_U0RTS                            ( 0x00A4 )
#define REG_PIN_U1TXDG0                          ( 0x00A8 )
#define REG_PIN_U1RXDG0                          ( 0x00AC )
#define REG_PIN_U2TXDG0                          ( 0x00B0 )
#define REG_PIN_U2RXDG0                          ( 0x00B4 )
#define REG_PIN_EXTINT9                          ( 0x00B8 )
#define REG_PIN_EXTINT10                         ( 0x00BC )
#define REG_PIN_SD1_CLK                          ( 0x00C0 )
#define REG_PIN_SD1_CMD                          ( 0x00C4 )
#define REG_PIN_SD1_D0                           ( 0x00C8 )
#define REG_PIN_SD1_D1                           ( 0x00CC )
#define REG_PIN_SD1_D2                           ( 0x00D0 )
#define REG_PIN_SD1_D3                           ( 0x00D4 )
#define REG_PIN_DMIC_CLKG0                       ( 0x00D8 )
#define REG_PIN_DMIC_DATG0                       ( 0x00DC )
#define REG_PIN_DMIC_CLKG1                       ( 0x00E0 )
#define REG_PIN_DMIC_DATG1                       ( 0x00E4 )
#define REG_PIN_IIS0DI                           ( 0x00E8 )
#define REG_PIN_IIS0DO                           ( 0x00EC )
#define REG_PIN_IIS0CLK                          ( 0x00F0 )
#define REG_PIN_IIS0LRCK                         ( 0x00F4 )
#define REG_PIN_U4TXD                            ( 0x00F8 )
#define REG_PIN_U4RXD                            ( 0x00FC )
#define REG_PIN_U4CTS                            ( 0x0100 )
#define REG_PIN_U4RTS                            ( 0x0104 )
#define REG_PIN_U5TXD                            ( 0x0108 )
#define REG_PIN_U5RXD                            ( 0x010C )
#define REG_PIN_SCL6                             ( 0x0110 )
#define REG_PIN_SDA6                             ( 0x0114 )
#define REG_PIN_EMMC_D3                          ( 0x0118 )
#define REG_PIN_EMMC_D7                          ( 0x011C )
#define REG_PIN_EMMC_D4                          ( 0x0120 )
#define REG_PIN_EMMC_D2                          ( 0x0124 )
#define REG_PIN_EMMC_DS                          ( 0x0128 )
#define REG_PIN_EMMC_CLK                         ( 0x012C )
#define REG_PIN_EMMC_D5                          ( 0x0130 )
#define REG_PIN_EMMC_D1                          ( 0x0134 )
#define REG_PIN_EMMC_CMD                         ( 0x0138 )
#define REG_PIN_EMMC_D0                          ( 0x013C )
#define REG_PIN_EMMC_RST                         ( 0x0140 )
#define REG_PIN_EMMC_D6                          ( 0x0144 )
#define REG_PIN_NF_DATA_1                        ( 0x0148 )
#define REG_PIN_NF_CEN0                          ( 0x014C )
#define REG_PIN_NF_DATA_2                        ( 0x0150 )
#define REG_PIN_NF_DATA_0                        ( 0x0154 )
#define REG_PIN_NF_WEN                           ( 0x0158 )
#define REG_PIN_LCM_FMARK                        ( 0x015C )
#define REG_PIN_XTL_BUF_EN2                      ( 0x0160 )
#define REG_PIN_XTL_BUF_EN1                      ( 0x0164 )
#define REG_PIN_AUD_SCLK                         ( 0x0168 )
#define REG_PIN_LCM_RSTN                         ( 0x016C )
#define REG_PIN_AUD_ADD0                         ( 0x0170 )
#define REG_PIN_CHIP_SLEEP                       ( 0x0174 )
#define REG_PIN_PTEST                            ( 0x0178 )
#define REG_PIN_EXT_RST_B                        ( 0x017C )
#define REG_PIN_AUD_ADSYNC                       ( 0x0180 )
#define REG_PIN_AUD_DASYNC                       ( 0x0184 )
#define REG_PIN_DCDCARM_EN                       ( 0x0188 )
#define REG_PIN_AUD_DAD0                         ( 0x018C )
#define REG_PIN_AUD_DAD1                         ( 0x0190 )
#define REG_PIN_CLK_32K                          ( 0x0194 )
#define REG_PIN_ADI_D                            ( 0x0198 )
#define REG_PIN_ADI_SCLK                         ( 0x019C )
#define REG_PIN_ANA_INT                          ( 0x01A0 )
#define REG_PIN_ADI_SYNC                         ( 0x01A4 )
#define REG_PIN_SD0_CMD                          ( 0x01A8 )
#define REG_PIN_SD0_D1                           ( 0x01AC )
#define REG_PIN_SD0_D0                           ( 0x01B0 )
#define REG_PIN_SD0_CLK                          ( 0x01B4 )
#define REG_PIN_SD0_D2                           ( 0x01B8 )
#define REG_PIN_SD0_D3                           ( 0x01BC )
#define REG_PIN_SD2_CLK                          ( 0x01C0 )
#define REG_PIN_SD2_D1                           ( 0x01C4 )
#define REG_PIN_SD2_D0                           ( 0x01C8 )
#define REG_PIN_SD2_CMD                          ( 0x01CC )
#define REG_PIN_SD2_D3                           ( 0x01D0 )
#define REG_PIN_SD2_D2                           ( 0x01D4 )
#define REG_PIN_SIMCLK0                          ( 0x01D8 )
#define REG_PIN_SIMDAT0                          ( 0x01DC )
#define REG_PIN_SIMRST0                          ( 0x01E0 )
#define REG_PIN_SIMCLK1                          ( 0x01E4 )
#define REG_PIN_SIMDAT1                          ( 0x01E8 )
#define REG_PIN_SIMRST1                          ( 0x01EC )
#define REG_PIN_SIMCLK2                          ( 0x01F0 )
#define REG_PIN_SIMDAT2                          ( 0x01F4 )
#define REG_PIN_SIMRST2                          ( 0x01F8 )
#define REG_PIN_KEYOUT0                          ( 0x01FC )
#define REG_PIN_KEYOUT1                          ( 0x0200 )
#define REG_PIN_KEYOUT2                          ( 0x0204 )
#define REG_PIN_KEYIN0                           ( 0x0208 )
#define REG_PIN_KEYIN1                           ( 0x020C )
#define REG_PIN_KEYIN2                           ( 0x0210 )
#define REG_PIN_RFFE0_SCK                        ( 0x0214 )
#define REG_PIN_RFFE0_SDA                        ( 0x0218 )
#define REG_PIN_RFCTL0                           ( 0x021C )
#define REG_PIN_RFCTL1                           ( 0x0220 )
#define REG_PIN_RFCTL2                           ( 0x0224 )
#define REG_PIN_RFCTL3                           ( 0x0228 )
#define REG_PIN_RFCTL4                           ( 0x022C )
#define REG_PIN_RFCTL5                           ( 0x0230 )
#define REG_PIN_RFCTL6                           ( 0x0234 )
#define REG_PIN_RFCTL7                           ( 0x0238 )
#define REG_PIN_RFCTL8                           ( 0x023C )
#define REG_PIN_RFCTL9                           ( 0x0240 )
#define REG_PIN_RFCTL10                          ( 0x0244 )
#define REG_PIN_RFCTL11                          ( 0x0248 )
#define REG_PIN_GPIO31                           ( 0x024C )
#define REG_PIN_GPIO32                           ( 0x0250 )
#define REG_PIN_RFFE1_SCK                        ( 0x0254 )
#define REG_PIN_RFFE1_SDA                        ( 0x0258 )
#define REG_PIN_GPIO33                           ( 0x025C )
#define REG_PIN_RFCTL16                          ( 0x0260 )
#define REG_PIN_RFCTL17                          ( 0x0264 )
#define REG_PIN_GPIO9                            ( 0x0268 )
#define REG_PIN_RFCTL19                          ( 0x026C )
#define REG_PIN_RFCTL20                          ( 0x0270 )
#define REG_PIN_RFSDA1                           ( 0x0274 )
#define REG_PIN_RFSCK1                           ( 0x0278 )
#define REG_PIN_RFSEN1                           ( 0x027C )
#define REG_PIN_RFSDA0                           ( 0x0280 )
#define REG_PIN_RFSCK0                           ( 0x0284 )
#define REG_PIN_RFSEN0                           ( 0x0288 )
#define REG_PIN_LVDSRF0_ADCON                    ( 0x028C )
#define REG_PIN_LVDSRF0_DACON                    ( 0x0290 )
#define REG_PIN_SPI2_CSN                         ( 0x0294 )
#define REG_PIN_SPI2_DO                          ( 0x0298 )
#define REG_PIN_SPI2_DI                          ( 0x029C )
#define REG_PIN_SPI2_CLK                         ( 0x02A0 )
#define REG_PIN_SPI0_CSN                         ( 0x02A4 )
#define REG_PIN_SPI0_DO                          ( 0x02A8 )
#define REG_PIN_SPI0_DI                          ( 0x02AC )
#define REG_PIN_SPI0_CLK                         ( 0x02B0 )
#define REG_PIN_TDO_LTE                          ( 0x02B4 )
#define REG_PIN_TDI_LTE                          ( 0x02B8 )
#define REG_PIN_TCK_LTE                          ( 0x02BC )
#define REG_PIN_TMS_LTE                          ( 0x02C0 )
#define REG_PIN_RTCK_LTE                         ( 0x02C4 )
#define REG_PIN_TCK_ARM                          ( 0x02C8 )
#define REG_PIN_TMS_ARM                          ( 0x02CC )
/* registers definitions for controller CTL_PIN MISC_OFFSET */
#define REG_PIN_PWR_PAD_CTL_G1                   ( 0x0000 )
#define REG_MISC_PIN_IIS1CLK                     ( 0x0434 )
#define REG_MISC_PIN_IIS1DI                      ( 0x0438 )
#define REG_MISC_PIN_IIS1DO                      ( 0x043C )
#define REG_MISC_PIN_IIS1LRCK                    ( 0x0440 )
#define REG_MISC_PIN_SCL2                        ( 0x0444 )
#define REG_MISC_PIN_SDA2                        ( 0x0448 )
#define REG_MISC_PIN_CLK_AUX0                    ( 0x044C )
#define REG_MISC_PIN_T_DIG                       ( 0x0450 )
#define REG_MISC_PIN_GNSS_LNA_EN                 ( 0x0454 )
#define REG_MISC_PIN_EXTINT0                     ( 0x0458 )
#define REG_MISC_PIN_EXTINT1                     ( 0x045C )
#define REG_MISC_PIN_SCL3                        ( 0x0460 )
#define REG_MISC_PIN_SDA3                        ( 0x0464 )
#define REG_MISC_PIN_SCL0                        ( 0x0468 )
#define REG_MISC_PIN_SDA0                        ( 0x046C )
#define REG_MISC_PIN_SCL1                        ( 0x0470 )
#define REG_MISC_PIN_SDA1                        ( 0x0474 )
#define REG_MISC_PIN_CMPD2                       ( 0x0478 )
#define REG_MISC_PIN_CMRST2                      ( 0x047C )
#define REG_MISC_PIN_CMMCLK0                     ( 0x0480 )
#define REG_MISC_PIN_CMRST0                      ( 0x0484 )
#define REG_MISC_PIN_CMPD0                       ( 0x0488 )
#define REG_MISC_PIN_CMMCLK1                     ( 0x048C )
#define REG_MISC_PIN_CMRST1                      ( 0x0490 )
#define REG_MISC_PIN_CMPD1                       ( 0x0494 )
#define REG_PIN_PWR_PAD_CTL_G2                   ( 0x0000 )
#define REG_MISC_PIN_U0TXD                       ( 0x0498 )
#define REG_MISC_PIN_U0RXD                       ( 0x049C )
#define REG_MISC_PIN_U0CTS                       ( 0x04A0 )
#define REG_MISC_PIN_U0RTS                       ( 0x04A4 )
#define REG_MISC_PIN_U1TXDG0                     ( 0x04A8 )
#define REG_MISC_PIN_U1RXDG0                     ( 0x04AC )
#define REG_MISC_PIN_U2TXDG0                     ( 0x04B0 )
#define REG_MISC_PIN_U2RXDG0                     ( 0x04B4 )
#define REG_MISC_PIN_EXTINT9                     ( 0x04B8 )
#define REG_MISC_PIN_EXTINT10                    ( 0x04BC )
#define REG_MISC_PIN_SD1_CLK                     ( 0x04C0 )
#define REG_MISC_PIN_SD1_CMD                     ( 0x04C4 )
#define REG_MISC_PIN_SD1_D0                      ( 0x04C8 )
#define REG_MISC_PIN_SD1_D1                      ( 0x04CC )
#define REG_MISC_PIN_SD1_D2                      ( 0x04D0 )
#define REG_MISC_PIN_SD1_D3                      ( 0x04D4 )
#define REG_MISC_PIN_DMIC_CLKG0                  ( 0x04D8 )
#define REG_MISC_PIN_DMIC_DATG0                  ( 0x04DC )
#define REG_MISC_PIN_DMIC_CLKG1                  ( 0x04E0 )
#define REG_MISC_PIN_DMIC_DATG1                  ( 0x04E4 )
#define REG_MISC_PIN_IIS0DI                      ( 0x04E8 )
#define REG_MISC_PIN_IIS0DO                      ( 0x04EC )
#define REG_MISC_PIN_IIS0CLK                     ( 0x04F0 )
#define REG_MISC_PIN_IIS0LRCK                    ( 0x04F4 )
#define REG_MISC_PIN_U4TXD                       ( 0x04F8 )
#define REG_MISC_PIN_U4RXD                       ( 0x04FC )
#define REG_MISC_PIN_U4CTS                       ( 0x0500 )
#define REG_MISC_PIN_U4RTS                       ( 0x0504 )
#define REG_MISC_PIN_U5TXD                       ( 0x0508 )
#define REG_MISC_PIN_U5RXD                       ( 0x050C )
#define REG_MISC_PIN_SCL6                        ( 0x0510 )
#define REG_MISC_PIN_SDA6                        ( 0x0514 )
#define REG_PIN_PWR_PAD_CTL_G3                   ( 0x0000 )
#define REG_MISC_PIN_EMMC_D3                     ( 0x0518 )
#define REG_MISC_PIN_EMMC_D7                     ( 0x051C )
#define REG_MISC_PIN_EMMC_D4                     ( 0x0520 )
#define REG_MISC_PIN_EMMC_D2                     ( 0x0524 )
#define REG_MISC_PIN_EMMC_DS                     ( 0x0528 )
#define REG_MISC_PIN_EMMC_CLK                    ( 0x052C )
#define REG_MISC_PIN_EMMC_D5                     ( 0x0530 )
#define REG_MISC_PIN_EMMC_D1                     ( 0x0534 )
#define REG_MISC_PIN_EMMC_CMD                    ( 0x0538 )
#define REG_MISC_PIN_EMMC_D0                     ( 0x053C )
#define REG_MISC_PIN_EMMC_RST                    ( 0x0540 )
#define REG_MISC_PIN_EMMC_D6                     ( 0x0544 )
#define REG_MISC_PIN_NF_DATA_1                   ( 0x0548 )
#define REG_MISC_PIN_NF_CEN0                     ( 0x054C )
#define REG_MISC_PIN_NF_DATA_2                   ( 0x0550 )
#define REG_MISC_PIN_NF_DATA_0                   ( 0x0554 )
#define REG_MISC_PIN_NF_WEN                      ( 0x0558 )
#define REG_PIN_PWR_PAD_CTL_G4                   ( 0x0000 )
#define REG_MISC_PIN_LCM_FMARK                   ( 0x055C )
#define REG_MISC_PIN_XTL_BUF_EN2                 ( 0x0560 )
#define REG_MISC_PIN_XTL_BUF_EN1                 ( 0x0564 )
#define REG_MISC_PIN_AUD_SCLK                    ( 0x0568 )
#define REG_MISC_PIN_LCM_RSTN                    ( 0x056C )
#define REG_MISC_PIN_AUD_ADD0                    ( 0x0570 )
#define REG_MISC_PIN_CHIP_SLEEP                  ( 0x0574 )
#define REG_MISC_PIN_PTEST                       ( 0x0578 )
#define REG_MISC_PIN_EXT_RST_B                   ( 0x057C )
#define REG_MISC_PIN_AUD_ADSYNC                  ( 0x0580 )
#define REG_MISC_PIN_AUD_DASYNC                  ( 0x0584 )
#define REG_MISC_PIN_DCDCARM_EN                  ( 0x0588 )
#define REG_MISC_PIN_AUD_DAD0                    ( 0x058C )
#define REG_MISC_PIN_AUD_DAD1                    ( 0x0590 )
#define REG_MISC_PIN_CLK_32K                     ( 0x0594 )
#define REG_MISC_PIN_ADI_D                       ( 0x0598 )
#define REG_MISC_PIN_ADI_SCLK                    ( 0x059C )
#define REG_MISC_PIN_ANA_INT                     ( 0x05A0 )
#define REG_MISC_PIN_ADI_SYNC                    ( 0x05A4 )
#define REG_MISC_PIN_SD0_CMD                     ( 0x05A8 )
#define REG_MISC_PIN_SD0_D1                      ( 0x05AC )
#define REG_MISC_PIN_SD0_D0                      ( 0x05B0 )
#define REG_MISC_PIN_SD0_CLK                     ( 0x05B4 )
#define REG_MISC_PIN_SD0_D2                      ( 0x05B8 )
#define REG_MISC_PIN_SD0_D3                      ( 0x05BC )
#define REG_MISC_PIN_SD2_CLK                     ( 0x05C0 )
#define REG_MISC_PIN_SD2_D1                      ( 0x05C4 )
#define REG_MISC_PIN_SD2_D0                      ( 0x05C8 )
#define REG_MISC_PIN_SD2_CMD                     ( 0x05CC )
#define REG_MISC_PIN_SD2_D3                      ( 0x05D0 )
#define REG_MISC_PIN_SD2_D2                      ( 0x05D4 )
#define REG_PIN_PWR_PAD_CTL_G5                   ( 0x0000 )
#define REG_MISC_PIN_SIMCLK0                     ( 0xC5D8 )
#define REG_MISC_PIN_SIMDAT0                     ( 0xC5DC )
#define REG_MISC_PIN_SIMRST0                     ( 0xC5E0 )
#define REG_MISC_PIN_SIMCLK1                     ( 0xC5E4 )
#define REG_MISC_PIN_SIMDAT1                     ( 0xC5E8 )
#define REG_MISC_PIN_SIMRST1                     ( 0xC5EC )
#define REG_MISC_PIN_SIMCLK2                     ( 0xC5F0 )
#define REG_MISC_PIN_SIMDAT2                     ( 0xC5F4 )
#define REG_MISC_PIN_SIMRST2                     ( 0xC5F8 )
#define REG_MISC_PIN_KEYOUT0                     ( 0xC5FC )
#define REG_MISC_PIN_KEYOUT1                     ( 0xC600 )
#define REG_MISC_PIN_KEYOUT2                     ( 0xC604 )
#define REG_MISC_PIN_KEYIN0                      ( 0xC608 )
#define REG_MISC_PIN_KEYIN1                      ( 0xC60C )
#define REG_MISC_PIN_KEYIN2                      ( 0xC610 )
#define REG_MISC_PIN_RFFE0_SCK                   ( 0xC614 )
#define REG_MISC_PIN_RFFE0_SDA                   ( 0xC618 )
#define REG_MISC_PIN_RFCTL0                      ( 0xC61C )
#define REG_MISC_PIN_RFCTL1                      ( 0xC620 )
#define REG_MISC_PIN_RFCTL2                      ( 0xC624 )
#define REG_MISC_PIN_RFCTL3                      ( 0xC628 )
#define REG_MISC_PIN_RFCTL4                      ( 0xC62C )
#define REG_MISC_PIN_RFCTL5                      ( 0xC630 )
#define REG_MISC_PIN_RFCTL6                      ( 0xC634 )
#define REG_MISC_PIN_RFCTL7                      ( 0xC638 )
#define REG_MISC_PIN_RFCTL8                      ( 0xC63C )
#define REG_MISC_PIN_RFCTL9                      ( 0xC640 )
#define REG_MISC_PIN_RFCTL10                     ( 0xC644 )
#define REG_MISC_PIN_RFCTL11                     ( 0xC648 )
#define REG_MISC_PIN_GPIO31                      ( 0xC64C )
#define REG_MISC_PIN_GPIO32                      ( 0xC650 )
#define REG_MISC_PIN_RFFE1_SCK                   ( 0xC654 )
#define REG_MISC_PIN_RFFE1_SDA                   ( 0xC658 )
#define REG_MISC_PIN_GPIO33                      ( 0xC65C )
#define REG_MISC_PIN_RFCTL16                     ( 0xC660 )
#define REG_MISC_PIN_RFCTL17                     ( 0xC664 )
#define REG_MISC_PIN_GPIO9                       ( 0xC668 )
#define REG_MISC_PIN_RFCTL19                     ( 0xC66C )
#define REG_MISC_PIN_RFCTL20                     ( 0xC670 )
#define REG_MISC_PIN_RFSDA1                      ( 0xC674 )
#define REG_MISC_PIN_RFSCK1                      ( 0xC678 )
#define REG_MISC_PIN_RFSEN1                      ( 0xC67C )
#define REG_MISC_PIN_RFSDA0                      ( 0xC680 )
#define REG_MISC_PIN_RFSCK0                      ( 0xC684 )
#define REG_MISC_PIN_RFSEN0                      ( 0xC688 )
#define REG_MISC_PIN_LVDSRF0_ADCON               ( 0xC68C )
#define REG_MISC_PIN_LVDSRF0_DACON               ( 0xC690 )
#define REG_MISC_PIN_SPI2_CSN                    ( 0xC694 )
#define REG_MISC_PIN_SPI2_DO                     ( 0xC698 )
#define REG_MISC_PIN_SPI2_DI                     ( 0xC69C )
#define REG_MISC_PIN_SPI2_CLK                    ( 0xC6A0 )
#define REG_MISC_PIN_SPI0_CSN                    ( 0xC6A4 )
#define REG_MISC_PIN_SPI0_DO                     ( 0xC6A8 )
#define REG_MISC_PIN_SPI0_DI                     ( 0xC6AC )
#define REG_MISC_PIN_SPI0_CLK                    ( 0xC6B0 )
#define REG_MISC_PIN_TDO_LTE                     ( 0xC6B4 )
#define REG_MISC_PIN_TDI_LTE                     ( 0xC6B8 )
#define REG_MISC_PIN_TCK_LTE                     ( 0xC6BC )
#define REG_MISC_PIN_TMS_LTE                     ( 0xC6C0 )
#define REG_MISC_PIN_RTCK_LTE                    ( 0xC6C4 )
#define REG_MISC_PIN_TCK_ARM                     ( 0xC6C8 )
#define REG_MISC_PIN_TMS_ARM                     ( 0xC6CC )

/* bits definitions for register REG_PIN_XXX */
#define BITS_PIN_DS(_x_)                 ( ((_x_) << 19) & (BIT_19|BIT_20|BIT_21 ))
#define BIT_PIN_SLP_CM4                  ( BIT_17 )
#define BIT_PIN_SLP_WCN                  ( BIT_16 )
#define BIT_PIN_SLP_WTLCP                ( BIT_15 )
#define BIT_PIN_SLP_PUBCP                ( BIT_14 )
#define BIT_PIN_SLP_AP                   ( BIT_13 )
#define BIT_PIN_SLP_NONE		(  (~(0x1f << 13)) & (BIT_13|BIT_14|BIT_15|BIT_16|BIT_17))
#define BITS_PIN_SLP(_x_)                ( ((_x_) << 13) & (BIT_13|BIT_14|BIT_15|BIT_16|BIT_17) )
#define BIT_PIN_WPUS                     ( BIT_12 )
#define BIT_PIN_SE                       ( BIT_11 )
#define BIT_PIN_WPU                      ( BIT_7 )
#define BIT_PIN_WPD                      ( BIT_6 )
#define BITS_PIN_AF(_x_)                 ( ((_x_) << 4) & (BIT_4|BIT_5) )
#define BIT_PIN_SLP_WPU                  ( BIT_3 )
#define BIT_PIN_SLP_WPD                  ( BIT_2 )
#define BIT_PIN_SLP_IE                   ( BIT_1 )
#define BIT_PIN_SLP_OE                   ( BIT_0 )
/* vars definitions for controller  CTL_PIN */
#define BIT_PIN_NUL                      ( 0 )
#define BIT_PIN_SLP_NUL                  ( 0 )
#define BIT_PIN_SLP_Z                    ( 0 )
#define BIT_PIN_NULL                     ( 0 )
#endif //_PINMAP_H_
