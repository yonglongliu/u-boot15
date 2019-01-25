/*
 * Copyright (C) 2017 Spreadtrum Communications Inc.
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

#include "sprd_panel.h"

static int dummy_init(void)
{
	pr_info("dummy lcd init\n");
	return 0;
}

static int dummy_readid(void)
{
	pr_info("dummy lcd read id ok\n");
	return 0;
}

static int dummy_power(int on)
{
	if (on)
		pr_info("dummy lcd power on\n");
	else
		pr_info("dummy lcd power off\n");
	return 0;
}

static struct panel_ops dummy_ops = {
	.init = dummy_init,
	.read_id = dummy_readid,
	.power = dummy_power,
};

static struct panel_info dummy_info = {
	/* common parameters */
	.lcd_name = "lcd_dummy_mipi_hd",
	.type = SPRD_PANEL_TYPE_MIPI,
	.bpp = 24,
//	.fps = 3,
	.width = 720,
	.height = 1280,

	/* DPI specific parameters */
	.pixel_clk = 64000000,
	.rgb_timing = {
		6, 6, 8,
		6, 6, 8
	},

	/* MIPI DSI specific parameters */
	.phy_freq = 500000,/*Kbps*/
	.lane_num = 4,
	.work_mode = SPRD_MIPI_MODE_VIDEO,
	.burst_mode = PANEL_VIDEO_BURST_MODE,
	.nc_clk_en = false,
};

struct panel_driver dummy_mipi_driver = {
	.info = &dummy_info,
	.ops = &dummy_ops,
};
