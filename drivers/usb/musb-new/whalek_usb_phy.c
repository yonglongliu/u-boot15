/******************************************************************************
 ** File Name:      sprd_musb2_driver.c                                        *
 ** Author:         chunhou.wang                                              *
 ** DATE:           07/11/2016                                                *
 ** Copyright:      2010 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:                                                              *
 ******************************************************************************/
/**---------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **---------------------------------------------------------------------------*/



#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <sprd_regulator.h>
#include <usb/usb200_fdl.h>
#include <packet.h>
#include <dl_crc.h>

void usb_phy_init(void)
{
	/* enable usb module*/
	CHIP_REG_OR(REG_AP_AHB_AHB_EB, BIT_USB_EB);

	/*PHY width: 16 bit*/
	CHIP_REG_OR(REG_AP_AHB_OTG_PHY_CTRL,
				BIT_AP_AHB_UTMI_WIDTH_SEL);

	/*Soft reset phy*/
	CHIP_REG_OR(REG_AP_AHB_AHB_RST,BIT_OTG_UTMI_SOFT_RST);
	CHIP_REG_OR(REG_AON_APB_APB_RST2,  BIT_OTG_PHY_SOFT_RST);
	Musb_mdelay(5);
	CHIP_REG_AND(REG_AP_AHB_AHB_RST,~BIT_OTG_UTMI_SOFT_RST);
	CHIP_REG_AND(REG_AON_APB_APB_RST2,
				~BIT_OTG_PHY_SOFT_RST);
}

