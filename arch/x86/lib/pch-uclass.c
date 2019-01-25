/*
 * Copyright (c) 2015 Google, Inc
 * Written by Simon Glass <sjg@chromium.org>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <dm.h>
#include <dm/root.h>

static int pch_uclass_post_bind(struct udevice *bus)
{
	/*
	 * Scan the device tree for devices
	 *
	 * Before relocation, only bind devices marked for pre-relocation
	 * use.
	 */
	return dm_scan_fdt_node(bus, gd->fdt_blob, dev_of_offset(bus),
				gd->flags & GD_FLG_RELOC ? false : true);
}

UCLASS_DRIVER(pch) = {
	.id		= UCLASS_PCH,
	.name		= "pch",
	.post_bind	= pch_uclass_post_bind,
};
