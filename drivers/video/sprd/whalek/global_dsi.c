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

#include <asm/arch/sprd_reg.h>
#include <sprd_glb.h>
#include "sprd_dsi.h"

static int dsi_glb_parse_dt(struct dsi_context *ctx)
{
	ctx->base = SPRD_DSI_PHYS;
	return 0;
}

static void dsi_glb_enable(struct dsi_context *ctx)
{
	pr_info("dsi global enable\n");
}

static void dsi_glb_disable(struct dsi_context *ctx)
{
	pr_info("dsi global disable\n");
}

static void dsi_reset(struct dsi_context *ctx)
{
/*
// before ECO
	sci_glb_set(REG_AON_APB_APB_RST1, BIT_AON_DISP_SOFT_RST);
	udelay(10);
	sci_glb_clr(REG_AON_APB_APB_RST1, BIT_AON_DISP_SOFT_RST);
*/
// after ECO
}

static void dsi_power_domain(struct dsi_context *ctx, int enable)
{

}

static struct dsi_glb_ops dsi_glb_ops = {
	.parse_dt = dsi_glb_parse_dt,
	.reset = dsi_reset,
	.enable = dsi_glb_enable,
	.disable = dsi_glb_disable,
	.power = dsi_power_domain,
};

struct dsi_glb_ops *dsi_glb_ops_attach(void)
{
	return &dsi_glb_ops;
}

