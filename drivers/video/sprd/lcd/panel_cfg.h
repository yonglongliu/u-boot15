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

extern struct panel_driver dummy_mipi_driver;
extern struct panel_driver ili9881c_xxx_driver;
extern struct panel_driver ili9881c_3lane_driver;
extern struct panel_driver nt35532_truly_driver;
extern struct panel_driver nt35695_truly_driver;
extern struct panel_driver nt35596_boe_driver;
extern struct panel_driver nt35597_boe_driver;
extern struct panel_driver nt35597_fpga_driver;
extern struct panel_driver jd9161_xxx_driver;

static struct panel_cfg supported_panel[] = {
#ifdef CONFIG_LCD_ILI9881C_XXX_MIPI_HD
	{
		.lcd_id = 0x9881,
		.drv = &ili9881c_xxx_driver,
	},
#endif
#ifdef CONFIG_LCD_ILI9881C_3LANE_MIPI_HD
	{
		.lcd_id = 0x9881,
		.drv = &ili9881c_3lane_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35532_TRULY_MIPI_FHD
	{
		.lcd_id = 0x32,
		.drv = &nt35532_truly_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35596_BOE_MIPI_FHD
	{
		.lcd_id = 0x96,
		.drv = &nt35596_boe_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35597_BOE_MIPI_HD
	{
		.lcd_id = 0x97,
		.drv = &nt35597_boe_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35597_FPGA_MIPI_2K
	{
		.lcd_id = 0x97,
		.drv = &nt35597_fpga_driver,
	},
#endif
#ifdef CONFIG_LCD_NT35695_TRULY_MIPI_FHD
	{
		.lcd_id = 0x35695,
		.drv = &nt35695_truly_driver,
	},
#endif
#ifdef CONFIG_LCD_JD9161_XXX_MIPI_WVGA
	{
		.lcd_id = 0x91612,
		.drv = &jd9161_xxx_driver,
	},
#endif
/* warning: the dummy lcd must be the last item in this array */
	{
		.lcd_id = 0xFFFF,
		.drv = &dummy_mipi_driver,
	},
};
