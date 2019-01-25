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
#include "lcd/panel_cfg.h"
#include "sprd_dsi.h"
#include "sprd_dphy.h"

static uint32_t lcd_id_to_kernel;
static uint32_t lcd_width_to_kernel;
static uint32_t lcd_hight_to_kernel;
static struct panel_driver *panel_drv;

struct panel_info *panel_info_attach(void)
{
	return panel_drv->info;
}

void save_lcd_size_to_kernel(uint32_t width, uint32_t hight)
{
	lcd_width_to_kernel = width;
	lcd_hight_to_kernel = hight;
}

void save_lcd_id_to_kernel(uint32_t id)
{
	lcd_id_to_kernel = id;
}

uint32_t load_lcd_id_to_kernel(void)
{
	return lcd_id_to_kernel;
}

uint32_t load_lcd_width_to_kernel(void)
{
	return lcd_width_to_kernel;
}

uint32_t load_lcd_hight_to_kernel(void)
{
	return lcd_hight_to_kernel;
}

static int panel_if_init(void)
{
	int type = panel_drv->info->type;

	switch (type) {
	case SPRD_PANEL_TYPE_MIPI:
		sprd_dsi_probe();
		sprd_dphy_probe();
		return 0;

	case SPRD_PANEL_TYPE_RGB:
		return 0;

	default:
		pr_err("doesn't support current interface type %d\n", type);
		return -1;
	}
}

static int panel_if_uinit(void)
{
	int type = panel_drv->info->type;

	switch (type) {
	case SPRD_PANEL_TYPE_MIPI:
		sprd_dphy_suspend(&dphy_device);
		sprd_dsi_suspend(&dsi_device);
		return 0;

	case SPRD_PANEL_TYPE_RGB:
		return 0;

	default:
		pr_err("doesn't support current interface type %d\n", type);
		return -1;
	}
}

int sprd_panel_probe(void)
{
	struct panel_info *info;
	struct panel_ops *ops;
	int ret;
	int i;

	for (i = 0; i < ARRAY_SIZE(supported_panel); i++) {
		panel_drv = supported_panel[i].drv;
		info = panel_drv->info;
		ops = panel_drv->ops;

		panel_if_init();

		if (ops && ops->power)
			ops->power(true);
		if (ops && ops->read_id) {
			ret = ops->read_id();
			if (!ret) {
				pr_info("attach panel 0x%x success\n",
					supported_panel[i].lcd_id);
				break;
			}
		}
		if (ops && ops->power)
			ops->power(false);

		panel_if_uinit();

		pr_err("attach panel 0x%x failed, try next...\n",
			supported_panel[i].lcd_id);
	}

	if (ops && ops->init)
		ops->init();

	panel_info.vl_row = info->height;
	panel_info.vl_col = info->width;
	save_lcd_id_to_kernel(supported_panel[i].lcd_id);
	save_lcd_size_to_kernel(info->height, info->width);

	return 0;
}
