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
#include "sprd_dispc.h"

enum {
	CLK_DPU_SEL_153_6M = 0,
	CLK_DPU_SEL_192M,
	CLK_DPU_SEL_256M,
	CLK_DPU_SEL_384M,
};

enum {
	CLK_DPI_SEL_128M = 0,
	CLK_DPI_SEL_153_6M,
	CLK_DPI_SEL_192M,
};

#ifndef CONFIG_DPI_CLK_SRC
#define CONFIG_DPI_CLK_SRC 128000000
#endif

static int dispc_clk_init(struct dispc_context *ctx)
{

	return 0;
}

static int dispc_clk_update(struct dispc_context *ctx, int clk_id, int val)
{

	return 0;
}

static int dispc_glb_parse_dt(struct dispc_context *ctx)
{
	ctx->base = SPRD_DPU_PHYS;

	return 0;
}

static void dispc_glb_enable(struct dispc_context *ctx)
{

}

static void dispc_glb_disable(struct dispc_context *ctx)
{

}

static void dispc_reset(struct dispc_context *ctx)
{

}

static void dispc_power_domain(struct dispc_context *ctx, int enable)
{

}

static struct dispc_clk_ops dispc_clk_ops = {
	.init = dispc_clk_init,
	.update = dispc_clk_update,
};

static struct dispc_glb_ops dispc_glb_ops = {
	.parse_dt = dispc_glb_parse_dt,
	.reset = dispc_reset,
	.enable = dispc_glb_enable,
	.disable = dispc_glb_disable,
	.power = dispc_power_domain,
};

struct dispc_clk_ops *dispc_clk_ops_attach(void)
{
	return &dispc_clk_ops;
}

struct dispc_glb_ops *dispc_glb_ops_attach(void)
{
	return &dispc_glb_ops;
}
