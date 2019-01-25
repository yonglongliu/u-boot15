/**
 * dwc3_uboot.c - DesignWare USB3 DRD Module glue file
 *
 * Copyright (C) 2015 Spreadtrum  - http://www.spreadtrum.com
 *
 * Authors: Miao.Zhu <miao.zhu@spreadtrum.com>,
 *
 * SPDX-License-Identifier:     GPL-2.0
 */
#include <common.h>
#include <malloc.h>
#include <dwc3-uboot.h>
#include <asm/dma-mapping.h>
#include <linux/ioport.h>

#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>

#include "core.h"
#include "gadget.h"
#include "io.h"

#include "linux-compat.h"

#ifdef CONFIG_USB_DWC3_SPRD
#include "sprd_usb3_hw.c"
#else
#ifdef CONFIG_USB_DWC3_SPRD_INTEL
#include "sprd_intel_usb3_hw.c"
#else
static void dwc3_device dwc3_dev = {
	.base = 0x0,
	.maximum_speed = USB_SPEED_UNKNOWN,
};
static void usb_clk_enable(u32 is_on) {}
static void usb_phy_enable(u32 is_on) {}
#endif
#endif

int usb_driver_init(unsigned int max_speed)
{
	usb_clk_enable(1);
	usb_phy_enable(1);

	if (max_speed <= USB_SPEED_HIGH &&
		max_speed >= USB_SPEED_FULL)
		dwc3_dev.maximum_speed = max_speed;

	return dwc3_uboot_init(&dwc3_dev);

}

void usb_driver_exit(void)
{
	usb_clk_enable(0);
	usb_phy_enable(0);
}

int usb_gadget_handle_interrupts(void)
{
	dwc3_uboot_handle_interrupt(&dwc3_dev);
}

