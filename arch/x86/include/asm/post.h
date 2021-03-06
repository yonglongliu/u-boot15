/*
 * Copyright (c) 2014 Google, Inc
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _post_h
#define _post_h

/* port to use for post codes */
#define POST_PORT		0x80

/* post codes which represent various stages of init */
#define POST_START		0x1e
#define POST_CAR_START		0x1f
#define POST_CAR_SIPI		0x20
#define POST_CAR_MTRR		0x21
#define POST_CAR_UNCACHEABLE	0x22
#define POST_CAR_BASE_ADDRESS	0x23
#define POST_CAR_MASK		0x24
#define POST_CAR_FILL		0x25
#define POST_CAR_ROM_CACHE	0x26
#define POST_CAR_MRC_CACHE	0x27
#define POST_CAR_CPU_CACHE	0x28
#define POST_START_STACK	0x29
#define POST_START_DONE		0x2a
#define POST_CPU_INIT		0x2b
#define POST_EARLY_INIT		0x2c
#define POST_CPU_INFO		0x2d
#define POST_PRE_MRC		0x2e
#define POST_MRC		0x2f
#define POST_DRAM		0x2f
#define POST_LAPIC		0x30

#define POST_RAM_FAILURE	0xea
#define POST_BIST_FAILURE	0xeb
#define POST_CAR_FAILURE	0xec

/* Output a post code using al - value must be 0 to 0xff */
#ifdef __ASSEMBLY__
#ifdef CONFIG_X86_POST_CODE
#define post_code(value) \
	movb	$value, %al; \
	outb	%al, $POST_PORT
#else
#define post_code(value)
#endif
#else
#include <asm/io.h>
#ifdef CONFIG_X86_POST_CODE
static inline void post_code(int code)
{
	outb(code, POST_PORT);
}
#else
static inline void post_code(int code) {}
#endif
#endif

#endif
