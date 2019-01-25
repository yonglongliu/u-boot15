/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 *Version SP9850S-2_SCH_V1.0.0_Pinmap_V1.0
 */

#include <asm/io.h>
#include <asm/arch/pinmap.h>
#include <power/sprd_pmic/sprd_2731_pinmap.h>

#define BIT_PIN_SLP_ALL  (BIT_PIN_SLP_AP|BIT_PIN_SLP_PUBCP|BIT_PIN_SLP_TGLDSP|BIT_PIN_SLP_AGDSP)

#define BIT_PIN_SLP_ALL_CP  (BIT_PIN_SLP_PUBCP|BIT_PIN_SLP_TGLDSP|BIT_PIN_SLP_AGDSP)

static pinmap_t pinmap[]={
{REG_PIN_CTRL0,0x00000034},
{REG_PIN_CTRL1,0x0},
{REG_PIN_CTRL2,0x00410000}, // uart0->bt'uart;  uart1->ap'uart0; uart2->cp1'uart0; uart3->gps; uart4->agdsp uart0
{REG_PIN_CTRL3,0x00438000},
{REG_PIN_CTRL4,0x00000010}, // I2C0 of CM4
{REG_PIN_CTRL5,0x03f00000},
{REG_PIN_CTRL6,0x0},
{REG_PIN_CTRL7,0x0},

{REG_PIN_RFCTL20,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL20_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//GPS_GPIO0
{REG_PIN_RFCTL21,                BIT_PIN_SLP_ALL|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL21_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//EAR_MIC_DET    By 2.2K pull up to 2P8
{REG_PIN_RFCTL30,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL30_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//OCTA_ID        Distinct OCTA module
{REG_PIN_RFCTL31,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL31_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_NUL},//FG_ERR         Detecting for ESD Damage  low active
{REG_PIN_RFCTL32,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL32_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//TF_DET         By 1M pull up to 1P85
{REG_PIN_RFCTL33,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL33_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//NFC_EN
{REG_PIN_RFCTL34,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL34_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//SUB_DET        By 200K pull up to 1P85
{REG_PIN_RFCTL35,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL35_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//CAMERA_FLASH_EN0
{REG_PIN_RFCTL36,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL36_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//GRIP_SDA_1P8   By 2.2K pull up to 1P85       ??????
{REG_PIN_RFCTL37,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL37_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//GRIP_SCL_1P8   By 2.2K pull up to 1P85       ??????
{REG_PIN_RFCTL22,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL22_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_GPIO164,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO164_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_GPIO165,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO165_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL25,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL25_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//GPIO166        Pull down for LPDDR3,Pull up for LPDDR4
{REG_PIN_RFCTL26,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL26_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL27,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL27_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL28,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL28_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL29,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL29_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_SCL2,                   BIT_PIN_SLP_NONE|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SCL2_MISC,              BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//SENSOR_SCL_1P8     CM4 Pin       A+G Sensor
{REG_PIN_SDA2,                   BIT_PIN_SLP_NONE|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SDA2_MISC,              BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//SENSOR_SDA_1P8     CM4 Pin 
{REG_PIN_MTCK_ARM,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_MTCK_ARM_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//JTAG_MTCK
{REG_PIN_MTMS_ARM,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_MTMS_ARM_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//JTAG_MTMS
{REG_PIN_XTL_EN0,                BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_XTL_EN0_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//XTL_BUF_EN0      For MP3
{REG_PIN_PTEST,                  BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_PTEST_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//GND
{REG_PIN_AUD_DAD1,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_AUD_DAD1_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//AUD_DAD1
{REG_PIN_AUD_ADD0,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_AUD_ADD0_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//AUD_ADD0
{REG_PIN_AUD_ADSYNC,             BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_AUD_ADSYNC_MISC,        BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//AUD_ADSYNC
{REG_PIN_AUD_SCLK,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_AUD_SCLK_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//AUD_SCLK
{REG_PIN_CHIP_SLEEP,             BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_CHIP_SLEEP_MISC,        BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//CHIP_SLEEP
{REG_PIN_CLK_32K,                BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_CLK_32K_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//CLK_32K
{REG_PIN_DCDC_ARM_EN,            BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_DCDC_ARM_EN_MISC,       BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//VDDARM0_EN
{REG_PIN_EXT_RST_B,              BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_EXT_RST_B_MISC,         BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//EXT_RST_B
{REG_PIN_ADI_D,                  BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_ADI_D_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//ADI_D
{REG_PIN_ADI_SCLK,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_ADI_SCLK_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//ADI_CLK
{REG_PIN_XTL_EN1,                BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_XTL_EN1_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//XTL_BUF_EN1, For CM4 Sensor Hub
{REG_PIN_ANA_INT,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_ANA_INT_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//ANA_INT
{REG_PIN_AUD_DAD0,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_AUD_DAD0_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//AUD_DAD0
{REG_PIN_AUD_DASYNC,             BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_AUD_DASYNC_MISC,        BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//AUD_DASYNC
{REG_PIN_LCM_RSTN,               BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_LCM_RSTN_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_NUL},//MLCD_RST
{REG_PIN_DSI_TE,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_DSI_TE_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_NUL},//OLED_TE        Vsync pin  low active
{REG_PIN_PWMA,                   BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_PWMA_MISC,              BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_EXTINT0,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_EXTINT0_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//TSP_INT        low active
{REG_PIN_EXTINT1,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_EXTINT1_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//Touch_INT
{REG_PIN_SDA1,                   BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SDA1_MISC,              BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TSP_SDA_1P8    4.7K pull up
{REG_PIN_SCL1,                   BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SCL1_MISC,              BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TSP_SCL_1P8 
{REG_PIN_SIMCLK2,                BIT_PIN_SLP_AP|BITS_PIN_AF(1)|BIT_PIN_SLP_Z},
{REG_PIN_SIMCLK2_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//NFC_SCL_1P8    For NFC
{REG_PIN_SIMDA2,                 BIT_PIN_SLP_AP|BITS_PIN_AF(1)|BIT_PIN_SLP_Z},
{REG_PIN_SIMDA2_MISC,            BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//NFC_SDA_1P8
{REG_PIN_SIMRST2,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_SIMRST2_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TSP_A3P3_EN     
{REG_PIN_SIMCLK1,                BIT_PIN_SLP_PUBCP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_SIMCLK1_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//SIM2_CLK
{REG_PIN_SIMDA1,                 BIT_PIN_SLP_PUBCP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_SIMDA1_MISC,            BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//SIM2_DA       4.7K pull up
{REG_PIN_SIMRST1,                BIT_PIN_SLP_PUBCP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_SIMRST1_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//SIM2_RST
{REG_PIN_SIMCLK0,                BIT_PIN_SLP_PUBCP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_SIMCLK0_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//SIM1_CLK
{REG_PIN_SIMDA0,                 BIT_PIN_SLP_PUBCP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_SIMDA0_MISC,            BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//SIM1_DA       4.7K pull up
{REG_PIN_SIMRST0,                BIT_PIN_SLP_PUBCP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_SIMRST0_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//SIM1_RST
{REG_PIN_SD2_CMD,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_SD2_CMD_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//VDD_NFC_EN
{REG_PIN_SD2_D0,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_SD2_D0_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//NFC_FIRM      Connect to Host GPIO for NFC Firmware downloading data pin
{REG_PIN_SD2_D1,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_SD2_D1_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_SD2_CLK,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_SD2_CLK_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//LCD_3P0_EN    
{REG_PIN_SD2_D2,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_SD2_D2_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_SD2_D3,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_SD2_D3_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//LCD_IO_1P8_EN  
{REG_PIN_SD0_D3,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD0_D3_MISC,            BIT_PIN_NULL|BITS_PIN_DS(6)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//TFLASH_D(3)    20K pull up  10mA Driver level
{REG_PIN_SD0_D2,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD0_D2_MISC,            BIT_PIN_NULL|BITS_PIN_DS(6)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//TFLASH_D(2)
{REG_PIN_SD0_CMD,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD0_CMD_MISC,           BIT_PIN_NULL|BITS_PIN_DS(6)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//TFLASH_CMD
{REG_PIN_SD0_D0,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD0_D0_MISC,            BIT_PIN_NULL|BITS_PIN_DS(6)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//TFLASH_D(0)
{REG_PIN_SD0_D1,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD0_D1_MISC,            BIT_PIN_NULL|BITS_PIN_DS(6)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//TFLASH_D(1)
{REG_PIN_SD0_CLK,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_SD0_CLK_MISC,           BIT_PIN_NULL|BITS_PIN_DS(6)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TFLASH_CLK     14mA Driver level
{REG_PIN_EMMC_CMD,               BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_CMD_MISC,          BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_CMD       1.8K pull up   27mA Driver level
{REG_PIN_EMMC_D6,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_D6_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_D6
{REG_PIN_EMMC_D7,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_D7_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_D7
{REG_PIN_EMMC_CLK,               BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_EMMC_CLK_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//EMMC_CLK
{REG_PIN_EMMC_D5,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_D5_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_D5
{REG_PIN_EMMC_D4,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_D4_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_D4
{REG_PIN_EMMC_DS,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_EMMC_DS_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//EMMC_RCLK
{REG_PIN_EMMC_D3,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_D3_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_D3
{REG_PIN_EMMC_RST,               BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_EMMC_RST_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//EMMC_RST
{REG_PIN_EMMC_D1,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_D1_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_D1
{REG_PIN_EMMC_D2,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_D2_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_D2
{REG_PIN_EMMC_D0,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_EMMC_D0_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//EMMC_D0
{REG_PIN_IIS0DI,                 BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_IIS0DI_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//BT_PCM_OUT      Marlin2
{REG_PIN_IIS0DO,                 BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_IIS0DO_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//BT_PCM_IN
{REG_PIN_IIS0CLK,                BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_IIS0CLK_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//BT_PCM_CLK
{REG_PIN_IIS0LRCK,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_IIS0LRCK_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//BT_PCM_SYNC
{REG_PIN_SD1_CLK,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_SD1_CLK_MISC,           BIT_PIN_NULL|BITS_PIN_DS(4)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//WLAN_CLK      12mA Driver level
{REG_PIN_SD1_CMD,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD1_CMD_MISC,           BIT_PIN_WPUS|BITS_PIN_DS(4)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//WLAN_CMD
{REG_PIN_SD1_D0,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD1_D0_MISC,            BIT_PIN_WPUS|BITS_PIN_DS(4)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//WLAN_D(0)
{REG_PIN_SD1_D1,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD1_D1_MISC,            BIT_PIN_WPUS|BITS_PIN_DS(4)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//WLAN_D(1)
{REG_PIN_SD1_D2,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD1_D2_MISC,            BIT_PIN_WPUS|BITS_PIN_DS(4)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//WLAN_D(2)
{REG_PIN_SD1_D3,                 BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SD1_D3_MISC,            BIT_PIN_WPUS|BITS_PIN_DS(4)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//WLAN_D(3)
{REG_PIN_CLK_AUX0,               BIT_PIN_SLP_ALL|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_CLK_AUX0_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//CON_32K_IN     
{REG_PIN_WIFI_COEXIST,           BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_WIFI_COEXIST_MISC,      BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//WF_COEXIST
{REG_PIN_BEIDOU_COEXIST,         BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_BEIDOU_COEXIST_MISC,    BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_U3TXD,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_U3TXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//GPS_U0RXD       GE2
{REG_PIN_U3RXD,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_U3RXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//GPS_U0TXD
{REG_PIN_U3CTS,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_U3CTS_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//GPS_U0RTS
{REG_PIN_U3RTS,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_U3RTS_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPU},//GPS_U0CTS
{REG_PIN_U0TXD,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_U0TXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//BT_U0RXD
{REG_PIN_U0RXD,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_U0RXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//BT_U0TXD
{REG_PIN_U0CTS,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_U0CTS_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//BT_U0RTS
{REG_PIN_U0RTS,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_U0RTS_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//BT_U0CTS
{REG_PIN_IIS1DI,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_IIS1DI_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//WF_AGC1        Marlin2 GPIO1   High-Active
{REG_PIN_IIS1DO,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},  
{REG_PIN_IIS1DO_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//WF_AGC2        Marlin2 GPIO2   High-Active
{REG_PIN_IIS1CLK,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_IIS1CLK_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_IIS1LRCK,               BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_IIS1LRCK_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//GPS_PDN       
{REG_PIN_SPI0_CSN,               BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_SPI0_CSN_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_SPI0_DO,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_SPI0_DO_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_SPI0_DI,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SPI0_DI_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_SPI0_CLK,               BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SPI0_CLK_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_U2TXD,                  BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_U2TXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_U2RXD,                  BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_U2RXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_U4TXD,                  BIT_PIN_SLP_NONE|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_U4TXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TP4011        CM4 Pin  AP GPIO55
{REG_PIN_U4RXD,                  BIT_PIN_SLP_NONE|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_U4RXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//TP4010        CM4 Pin  AP GPIO55
{REG_PIN_CMMCLK1,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_CMMCLK1_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//VTCAM_MCLK
{REG_PIN_CMRST1,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_CMRST1_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//VTCAM_RST
{REG_PIN_CMMCLK0,                BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_CMMCLK0_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//CAM_MCLK
{REG_PIN_CMRST0,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_CMRST0_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//CAM_RST
{REG_PIN_CMPD0,                  BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_CMPD0_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_CMPD1,                  BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_CMPD1_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_SCL0,                   BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SCL0_MISC,              BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//VTCAM_SCL_1P8        For Front Camera
{REG_PIN_SDA0,                   BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SDA0_MISC,              BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//VTCAM_SDA_1P8
{REG_PIN_SDA6,                   BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SDA6_MISC,              BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//MAIN_CAM_SDA_1P8     For Rear Camera
{REG_PIN_SCL6,                   BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_SCL6_MISC,              BIT_PIN_WPUS|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//MAIN_CAM_SCL_1P8     For Rear Camera
{REG_PIN_U1TXD,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_U1TXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//BB_U1TXD
{REG_PIN_U1RXD,                  BIT_PIN_SLP_AP|BITS_PIN_AF(0)|BIT_PIN_SLP_IE},
{REG_PIN_U1RXD_MISC,             BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//BB_U1RXD
{REG_PIN_KEYOUT0,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_KEYOUT0_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//WB_RST
{REG_PIN_KEYOUT1,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_OE},
{REG_PIN_KEYOUT1_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//WB_EN
{REG_PIN_KEYOUT2,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_KEYOUT2_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//WB_ANT          INT From CP to AP, High Active
{REG_PIN_KEYIN0,                 BIT_PIN_SLP_AP|BITS_PIN_AF(1)|BIT_PIN_SLP_IE},
{REG_PIN_KEYIN0_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//VOP_UP
{REG_PIN_KEYIN1,                 BIT_PIN_SLP_AP|BITS_PIN_AF(1)|BIT_PIN_SLP_IE},
{REG_PIN_KEYIN1_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//KEYIN1
{REG_PIN_KEYIN2,                 BIT_PIN_SLP_AP|BITS_PIN_AF(1)|BIT_PIN_SLP_IE},
{REG_PIN_KEYIN2_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//HOME_KEY        By 100K pull up to 1P8   
{REG_PIN_IIS3DI,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_IIS3DI_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//PROXY_SDA_1P8   ??????
{REG_PIN_IIS3DO,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_IIS3DO_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//PROXY_SCL_1P8   ??????
{REG_PIN_IIS3CLK,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_IIS3CLK_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_IIS3LRCK,               BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_IIS3LRCK_MISC,          BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL0,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL0_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//MAIN_ANT_SW_CTL0
{REG_PIN_RFCTL1,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL1_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//MAIN_ANT_SW_CTL1
{REG_PIN_RFCTL10,                BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL10_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//ANT_LB_SW_SEL_1
{REG_PIN_RFCTL11,                BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL11_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//ANT_LB_SW_SEL_2
{REG_PIN_RFCTL12,                BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL12_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//ANT_HB_SW_SEL_1
{REG_PIN_RFCTL13,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL13_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//HW_REV_MOD_2
{REG_PIN_RFCTL14,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL14_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//HW_REV_MOD_1
{REG_PIN_RFCTL15,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL15_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL16,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL16_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL17,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL17_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL18,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL18_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFCTL19,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFCTL19_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//LVDS_TEST
{REG_PIN_RFCTL2,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL2_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//SUB_ANT_SW_CTL1
{REG_PIN_EXTINT5,                BIT_PIN_SLP_NONE|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_EXTINT5_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//PROXY_INT      CM4 Pin  AP GPIO27
{REG_PIN_EXTINT6,                BIT_PIN_SLP_NONE|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_EXTINT6_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//ACC_INT        CM4 Pin  AP GPIO28
{REG_PIN_EXTINT7,                BIT_PIN_SLP_NONE|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_EXTINT7_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//COVER_INT      CM4 Pin  AP GPIO28  Hall IC interrupt low active
{REG_PIN_GPIO30,                 BIT_PIN_SLP_NONE|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_GPIO30_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//PCD_INT        CM4 Pin  Detecting for OCTA Pannel damage  low active
{REG_PIN_GPIO31,                 BIT_PIN_SLP_NONE|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO31_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//GRIP_INT       CM4 Pin
{REG_PIN_GPIO32,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO32_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//EL_ON1         CM4 Pin  Detecting for ESD damage   low active
{REG_PIN_GPIO33,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_GPIO33_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//NFC_IRQ         Connect to Host external IRQ or GPIO for NFC interrupt
{REG_PIN_GPIO34,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_GPIO34_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//MUIC_INT        SM5504
{REG_PIN_RFCTL3,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL3_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//HW_REV_MOD_0
{REG_PIN_RFCTL4,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL4_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TX_SW_CTRL_B7_40
{REG_PIN_RFCTL5,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL5_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//PA0_R0
{REG_PIN_RFCTL6,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL6_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//B7_B40_PA_EN
{REG_PIN_RFCTL7,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL7_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//CTL_B28
{REG_PIN_GPIO15,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO15_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_GPIO16,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO16_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_RFFE0_SCK0,             BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_RFFE0_SCK0_MISC,        BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//RFFE0_CLK
{REG_PIN_GPIO38,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO38_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//MUIC_SDA_1P8     ??????
{REG_PIN_RFFE0_SDA0,             BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_RFFE0_SDA0_MISC,        BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//RFFE0_DATA
{REG_PIN_GPIO39,                 BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO39_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//MUIC_SCL_1P8     ??????
{REG_PIN_RFFE1_SCK0,             BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFFE1_SCK0_MISC,        BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_GPIO181,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO181_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//TOUCH_SDA_1P8
{REG_PIN_RFFE1_SDA0,             BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_RFFE1_SDA0_MISC,        BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPD|BIT_PIN_SLP_WPD},//NC
{REG_PIN_GPIO182,                BIT_PIN_SLP_AP|BITS_PIN_AF(3)|BIT_PIN_SLP_Z},
{REG_PIN_GPIO182_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPD},//TOUCH_SCL_1P8
{REG_PIN_RF_LVDS0_ADC_ON,        BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RF_LVDS0_ADC_ON_MISC,   BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TP4000
{REG_PIN_RF_LVDS0_DAC_ON,        BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RF_LVDS0_DAC_ON_MISC,   BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TP4001
{REG_PIN_RFSCK0,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_RFSCK0_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//PCC_RFSCK
{REG_PIN_RFSDA0,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_RFSDA0_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//PCC_RFSDA
{REG_PIN_RFSEN0,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_RFSEN0_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//PCC_RFSEN
{REG_PIN_RF_LVDS1_ADC_ON,        BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RF_LVDS1_ADC_ON_MISC,   BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TP4002
{REG_PIN_RF_LVDS1_DAC_ON,        BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_OE},
{REG_PIN_RF_LVDS1_DAC_ON_MISC,   BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//TP4003
{REG_PIN_RFSCK1,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_RFSCK1_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//SCC_RFSCK
{REG_PIN_RFSDA1,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_RFSDA1_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//PCC_RFSDA
{REG_PIN_RFSEN1,                 BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(0)|BIT_PIN_SLP_Z},
{REG_PIN_RFSEN1_MISC,            BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_WPD},//PCC_RFSEN
{REG_PIN_RFCTL38,                BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(1)|BIT_PIN_SLP_OE},
{REG_PIN_RFCTL38_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_NUL|BIT_PIN_SLP_NUL},//WCN_LTECOEXIST_RX
{REG_PIN_RFCTL39,                BIT_PIN_SLP_ALL_CP|BITS_PIN_AF(1)|BIT_PIN_SLP_IE},
{REG_PIN_RFCTL39_MISC,           BIT_PIN_NULL|BITS_PIN_DS(1)|BIT_PIN_WPU|BIT_PIN_SLP_WPU},//WCN_LTECOEXIST_TX

};



/*here is the adie pinmap such as 2731*/
static pinmap_t adie_pinmap[]={
{REG_PIN_ANA_EXT_XTL_EN0,		BITS_ANA_PIN_DS(1)|BIT_ANA_PIN_NUL|BIT_ANA_PIN_SLP_IE},//XTL_BUF_EN0
{REG_PIN_ANA_EXT_XTL_EN1,		BITS_ANA_PIN_DS(1)|BIT_ANA_PIN_NUL|BIT_ANA_PIN_SLP_IE},//XTL_BUF_EN1   
{REG_PIN_ANA_EXT_XTL_EN2,		BITS_ANA_PIN_DS(1)|BIT_ANA_PIN_WPD|BIT_ANA_PIN_SLP_IE},//WB_CLK_REQ  Active High when BT need host to turn on reference clock
{REG_PIN_ANA_EXT_XTL_EN3,		BITS_ANA_PIN_DS(1)|BIT_ANA_PIN_WPD|BIT_ANA_PIN_SLP_IE},//NFC_CLK_REQ
};

int  pin_init(void)
{
	int i;
	for (i = 0; i < sizeof(pinmap)/sizeof(pinmap[0]); i++) {
		__raw_writel(pinmap[i].val, CTL_PIN_BASE + pinmap[i].reg);
	}

	for (i = 0; i < sizeof(adie_pinmap)/sizeof(adie_pinmap[0]); i++) {
		sci_adi_set(CTL_ANA_PIN_BASE + adie_pinmap[i].reg, adie_pinmap[i].val);
	}

	return 0;
}
