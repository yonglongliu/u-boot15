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
#include "sprd_dsi.h"
#include "dsi/mipi_dsi_api.h"
#include "sprd_dphy.h"
#include <i2c.h>

static uint8_t init_data[] = {
	0x23, 0x00, 0x00, 0x02, 0xFF, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xFB, 0x01,

	0x23, 0x00, 0x00, 0x02, 0x00, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x01, 0x44,
	0x23, 0x00, 0x00, 0x02, 0x02, 0x59,
	0x23, 0x00, 0x00, 0x02, 0x04, 0x0C,
	0x23, 0x00, 0x00, 0x02, 0x05, 0x2B,
	0x23, 0x00, 0x00, 0x02, 0x06, 0x64,
	0x23, 0x00, 0x00, 0x02, 0x07, 0xC6,
	//GVDDP 4.3V
	0x23, 0x00, 0x00, 0x02, 0x0D, 0x89,
	0x23, 0x00, 0x00, 0x02, 0x0E, 0x89,
 
	0x23, 0x00, 0x00, 0x02, 0x0F, 0xE0,
	0x23, 0x00, 0x00, 0x02, 0x10, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x11, 0x5A,
	0x23, 0x00, 0x00, 0x02, 0x12, 0x5A,
	//vcom
	0x23, 0x00, 0x00, 0x02, 0x13, 0x7E,
	0x23, 0x00, 0x00, 0x02, 0x14, 0x7E,
	0x23, 0x00, 0x00, 0x02, 0x15, 0x60,

	0x23, 0x00, 0x00, 0x02, 0x16, 0x13,
	0x23, 0x00, 0x00, 0x02, 0x17, 0x13,
	0x23, 0x00, 0x00, 0x02, 0x1C, 0xA3,
	0x23, 0x00, 0x00, 0x02, 0x6E, 0x80,
	0x23, 0x00, 0x00, 0x02, 0x60, 0x77,
	0x23, 0x00, 0x00, 0x02, 0x68, 0x13,

	//gamma
	//R(+) MCR cmd
	0x23, 0x00, 0x00, 0x02, 0x75, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x76, 0x77,
	0x23, 0x00, 0x00, 0x02, 0x77, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x78, 0x78,
	0x23, 0x00, 0x00, 0x02, 0x79, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x7A, 0xB0,
	0x23, 0x00, 0x00, 0x02, 0x7B, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x7C, 0xCC,
	0x23, 0x00, 0x00, 0x02, 0x7D, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x7E, 0xE3,
	0x23, 0x00, 0x00, 0x02, 0x7F, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x80, 0xF6,
	0x23, 0x00, 0x00, 0x02, 0x81, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x82, 0x06,
	0x23, 0x00, 0x00, 0x02, 0x83, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x84, 0x15,
	0x23, 0x00, 0x00, 0x02, 0x85, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x86, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x87, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x88, 0x4E,
	0x23, 0x00, 0x00, 0x02, 0x89, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x8A, 0x71,
	0x23, 0x00, 0x00, 0x02, 0x8B, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x8C, 0xA7,
	0x23, 0x00, 0x00, 0x02, 0x8D, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x8E, 0xD2,
	0x23, 0x00, 0x00, 0x02, 0x8F, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x90, 0x14,
	0x23, 0x00, 0x00, 0x02, 0x91, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x92, 0x49,
	0x23, 0x00, 0x00, 0x02, 0x93, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x94, 0x4B,
	0x23, 0x00, 0x00, 0x02, 0x95, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x96, 0x7D,
	0x23, 0x00, 0x00, 0x02, 0x97, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x98, 0xB6,
	0x23, 0x00, 0x00, 0x02, 0x99, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x9A, 0xD9,
	0x23, 0x00, 0x00, 0x02, 0x9B, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x9C, 0x0D,
	0x23, 0x00, 0x00, 0x02, 0x9D, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x9E, 0x2A,
	0x23, 0x00, 0x00, 0x02, 0x9F, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xA0, 0x51,
	0x23, 0x00, 0x00, 0x02, 0xA2, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xA3, 0x5D,
	0x23, 0x00, 0x00, 0x02, 0xA4, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xA5, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0xA6, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xA7, 0x78,
	0x23, 0x00, 0x00, 0x02, 0xA9, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xAA, 0x89,
	0x23, 0x00, 0x00, 0x02, 0xAB, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xAC, 0x9E,
	0x23, 0x00, 0x00, 0x02, 0xAD, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xAE, 0xB7,
	0x23, 0x00, 0x00, 0x02, 0xAF, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xB0, 0xCE,
	0x23, 0x00, 0x00, 0x02, 0xB1, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xB2, 0xD1,
	//R(-) MCR cmd
	0x23, 0x00, 0x00, 0x02, 0xB3, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB4, 0x18,
	0x23, 0x00, 0x00, 0x02, 0xB5, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB6, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0xB7, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB8, 0xB0,
	0x23, 0x00, 0x00, 0x02, 0xB9, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xBA, 0xCC,
	0x23, 0x00, 0x00, 0x02, 0xBB, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xBC, 0xE3,
	0x23, 0x00, 0x00, 0x02, 0xBD, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xBE, 0xF6,
	0x23, 0x00, 0x00, 0x02, 0xBF, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC0, 0x06,
	0x23, 0x00, 0x00, 0x02, 0xC1, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC2, 0x15,
	0x23, 0x00, 0x00, 0x02, 0xC3, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC4, 0x22,
	0x23, 0x00, 0x00, 0x02, 0xC5, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC6, 0x4E,
	0x23, 0x00, 0x00, 0x02, 0xC7, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC8, 0x71,
	0x23, 0x00, 0x00, 0x02, 0xC9, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xCA, 0xA7,
	0x23, 0x00, 0x00, 0x02, 0xCB, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xCC, 0xD2,
	0x23, 0x00, 0x00, 0x02, 0xCD, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xCE, 0x14,
	0x23, 0x00, 0x00, 0x02, 0xCF, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xD0, 0x49,
	0x23, 0x00, 0x00, 0x02, 0xD1, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xD2, 0x4B,
	0x23, 0x00, 0x00, 0x02, 0xD3, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xD4, 0x7D,
	0x23, 0x00, 0x00, 0x02, 0xD5, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xD6, 0xB6,
	0x23, 0x00, 0x00, 0x02, 0xD7, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xD8, 0xD9,
	0x23, 0x00, 0x00, 0x02, 0xD9, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xDA, 0x0D,
	0x23, 0x00, 0x00, 0x02, 0xDB, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xDC, 0x2A,
	0x23, 0x00, 0x00, 0x02, 0xDD, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xDE, 0x51,
	0x23, 0x00, 0x00, 0x02, 0xDF, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE0, 0x5D,
	0x23, 0x00, 0x00, 0x02, 0xE1, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE2, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0xE3, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE4, 0x78,
	0x23, 0x00, 0x00, 0x02, 0xE5, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE6, 0x89,
	0x23, 0x00, 0x00, 0x02, 0xE7, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE8, 0x9E,
	0x23, 0x00, 0x00, 0x02, 0xE9, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xEA, 0xB7,
	0x23, 0x00, 0x00, 0x02, 0xEB, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xEC, 0xCE,
	0x23, 0x00, 0x00, 0x02, 0xED, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xEE, 0xD1,
	//G(+) MCR cmd
	0x23, 0x00, 0x00, 0x02, 0xEF, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xF0, 0x77,
	0x23, 0x00, 0x00, 0x02, 0xF1, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xF2, 0x78,
	0x23, 0x00, 0x00, 0x02, 0xF3, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xF4, 0xB0,
	0x23, 0x00, 0x00, 0x02, 0xF5, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xF6, 0xCC,
	0x23, 0x00, 0x00, 0x02, 0xF7, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xF8, 0xE3,
	0x23, 0x00, 0x00, 0x02, 0xF9, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xFA, 0xF6,
	//page selection cmd start
	0x23, 0x00, 0x00, 0x02, 0xFF, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xFB, 0x01,
	//page selection cmd end
	0x23, 0x00, 0x00, 0x02, 0x00, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x01, 0x06,
	0x23, 0x00, 0x00, 0x02, 0x02, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x03, 0x15,
	0x23, 0x00, 0x00, 0x02, 0x04, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x05, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x06, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x07, 0x4E,
	0x23, 0x00, 0x00, 0x02, 0x08, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x09, 0x71,
	0x23, 0x00, 0x00, 0x02, 0x0A, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x0B, 0xA7,
	0x23, 0x00, 0x00, 0x02, 0x0C, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x0D, 0xD2,
	0x23, 0x00, 0x00, 0x02, 0x0E, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x0F, 0x14,
	0x23, 0x00, 0x00, 0x02, 0x10, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x11, 0x49,
	0x23, 0x00, 0x00, 0x02, 0x12, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x13, 0x4B,
	0x23, 0x00, 0x00, 0x02, 0x14, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x15, 0x7D,
	0x23, 0x00, 0x00, 0x02, 0x16, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x17, 0xB6,
	0x23, 0x00, 0x00, 0x02, 0x18, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x19, 0xD9,
	0x23, 0x00, 0x00, 0x02, 0x1A, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x1B, 0x0D,
	0x23, 0x00, 0x00, 0x02, 0x1C, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x1D, 0x2A,
	0x23, 0x00, 0x00, 0x02, 0x1E, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x1F, 0x51,
	0x23, 0x00, 0x00, 0x02, 0x20, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x21, 0x5D,
	0x23, 0x00, 0x00, 0x02, 0x22, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x23, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0x24, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x25, 0x78,
	0x23, 0x00, 0x00, 0x02, 0x26, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x27, 0x89,
	0x23, 0x00, 0x00, 0x02, 0x28, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x29, 0x9E,
	0x23, 0x00, 0x00, 0x02, 0x2A, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x2B, 0xB7,
	0x23, 0x00, 0x00, 0x02, 0x2D, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x2F, 0xCE,
	0x23, 0x00, 0x00, 0x02, 0x30, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x31, 0xD1,
	//G(-) MCR cmd
	0x23, 0x00, 0x00, 0x02, 0x32, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x33, 0x18,
	0x23, 0x00, 0x00, 0x02, 0x34, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x35, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0x36, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x37, 0xB0,
	0x23, 0x00, 0x00, 0x02, 0x38, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x39, 0xCC,
	0x23, 0x00, 0x00, 0x02, 0x3A, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x3B, 0xE3,
	0x23, 0x00, 0x00, 0x02, 0x3D, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x3F, 0xF6,
	0x23, 0x00, 0x00, 0x02, 0x40, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x41, 0x06,
	0x23, 0x00, 0x00, 0x02, 0x42, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x43, 0x15,
	0x23, 0x00, 0x00, 0x02, 0x44, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x45, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x46, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x47, 0x4E,
	0x23, 0x00, 0x00, 0x02, 0x48, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x49, 0x71,
	0x23, 0x00, 0x00, 0x02, 0x4A, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x4B, 0xA7,
	0x23, 0x00, 0x00, 0x02, 0x4C, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x4D, 0xD2,
	0x23, 0x00, 0x00, 0x02, 0x4E, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x4F, 0x14,
	0x23, 0x00, 0x00, 0x02, 0x50, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x51, 0x49,
	0x23, 0x00, 0x00, 0x02, 0x52, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x53, 0x4B,
	0x23, 0x00, 0x00, 0x02, 0x54, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x55, 0x7D,
	0x23, 0x00, 0x00, 0x02, 0x56, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x58, 0xB6,
	0x23, 0x00, 0x00, 0x02, 0x59, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x5A, 0xD9,
	0x23, 0x00, 0x00, 0x02, 0x5B, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x5C, 0x0D,
	0x23, 0x00, 0x00, 0x02, 0x5D, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x5E, 0x2A,
	0x23, 0x00, 0x00, 0x02, 0x5F, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x60, 0x51,
	0x23, 0x00, 0x00, 0x02, 0x61, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x62, 0x5D,
	0x23, 0x00, 0x00, 0x02, 0x63, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x64, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0x65, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x66, 0x78,
	0x23, 0x00, 0x00, 0x02, 0x67, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x68, 0x89,
	0x23, 0x00, 0x00, 0x02, 0x69, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x6A, 0x9E,
	0x23, 0x00, 0x00, 0x02, 0x6B, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x6C, 0xB7,
	0x23, 0x00, 0x00, 0x02, 0x6D, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x6E, 0xCE,
	0x23, 0x00, 0x00, 0x02, 0x6F, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x70, 0xD1,
	//B(+) MCR cmd
	0x23, 0x00, 0x00, 0x02, 0x71, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x72, 0x77,
	0x23, 0x00, 0x00, 0x02, 0x73, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x74, 0x78,
	0x23, 0x00, 0x00, 0x02, 0x75, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x76, 0xB0,
	0x23, 0x00, 0x00, 0x02, 0x77, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x78, 0xCC,
	0x23, 0x00, 0x00, 0x02, 0x79, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x7A, 0xE3,
	0x23, 0x00, 0x00, 0x02, 0x7B, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x7C, 0xF6,
	0x23, 0x00, 0x00, 0x02, 0x7D, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x7E, 0x06,
	0x23, 0x00, 0x00, 0x02, 0x7F, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x80, 0x15,
	0x23, 0x00, 0x00, 0x02, 0x81, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x82, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x83, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x84, 0x4E,
	0x23, 0x00, 0x00, 0x02, 0x85, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x86, 0x71,
	0x23, 0x00, 0x00, 0x02, 0x87, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x88, 0xA7,
	0x23, 0x00, 0x00, 0x02, 0x89, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x8A, 0xD2,
	0x23, 0x00, 0x00, 0x02, 0x8B, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x8C, 0x14,
	0x23, 0x00, 0x00, 0x02, 0x8D, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x8E, 0x49,
	0x23, 0x00, 0x00, 0x02, 0x8F, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x90, 0x4B,
	0x23, 0x00, 0x00, 0x02, 0x91, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x92, 0x7D,
	0x23, 0x00, 0x00, 0x02, 0x93, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x94, 0xB6,
	0x23, 0x00, 0x00, 0x02, 0x95, 0x02,
	0x23, 0x00, 0x00, 0x02, 0x96, 0xD9,
	0x23, 0x00, 0x00, 0x02, 0x97, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x98, 0x0D,
	0x23, 0x00, 0x00, 0x02, 0x99, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x9A, 0x2A,
	0x23, 0x00, 0x00, 0x02, 0x9B, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x9C, 0x51,
	0x23, 0x00, 0x00, 0x02, 0x9D, 0x03,
	0x23, 0x00, 0x00, 0x02, 0x9E, 0x5D,
	0x23, 0x00, 0x00, 0x02, 0x9F, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xA0, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0xA2, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xA3, 0x78,
	0x23, 0x00, 0x00, 0x02, 0xA4, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xA5, 0x89,
	0x23, 0x00, 0x00, 0x02, 0xA6, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xA7, 0x9E,
	0x23, 0x00, 0x00, 0x02, 0xA9, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xAA, 0xB7,
	0x23, 0x00, 0x00, 0x02, 0xAB, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xAC, 0xCE,
	0x23, 0x00, 0x00, 0x02, 0xAD, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xAE, 0xD1,
	//B(-) MCR cmd
	0x23, 0x00, 0x00, 0x02, 0xAF, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB0, 0x18,
	0x23, 0x00, 0x00, 0x02, 0xB1, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB2, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0xB3, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB4, 0xB0,
	0x23, 0x00, 0x00, 0x02, 0xB5, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB6, 0xCC,
	0x23, 0x00, 0x00, 0x02, 0xB7, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xB8, 0xE3,
	0x23, 0x00, 0x00, 0x02, 0xB9, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xBA, 0xF6,
	0x23, 0x00, 0x00, 0x02, 0xBB, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xBC, 0x06,
	0x23, 0x00, 0x00, 0x02, 0xBD, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xBE, 0x15,
	0x23, 0x00, 0x00, 0x02, 0xBF, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC0, 0x22,
	0x23, 0x00, 0x00, 0x02, 0xC1, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC2, 0x4E,
	0x23, 0x00, 0x00, 0x02, 0xC3, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC4, 0x71,
	0x23, 0x00, 0x00, 0x02, 0xC5, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC6, 0xA7,
	0x23, 0x00, 0x00, 0x02, 0xC7, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xC8, 0xD2,
	0x23, 0x00, 0x00, 0x02, 0xC9, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xCA, 0x14,
	0x23, 0x00, 0x00, 0x02, 0xCB, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xCC, 0x49,
	0x23, 0x00, 0x00, 0x02, 0xCD, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xCE, 0x4B,
	0x23, 0x00, 0x00, 0x02, 0xCF, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xD0, 0x7D,
	0x23, 0x00, 0x00, 0x02, 0xD1, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xD2, 0xB6,
	0x23, 0x00, 0x00, 0x02, 0xD3, 0x02,
	0x23, 0x00, 0x00, 0x02, 0xD4, 0xD9,
	0x23, 0x00, 0x00, 0x02, 0xD5, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xD6, 0x0D,
	0x23, 0x00, 0x00, 0x02, 0xD7, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xD8, 0x2A,
	0x23, 0x00, 0x00, 0x02, 0xD9, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xDA, 0x51,
	0x23, 0x00, 0x00, 0x02, 0xDB, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xDC, 0x5D,
	0x23, 0x00, 0x00, 0x02, 0xDD, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xDE, 0x6A,
	0x23, 0x00, 0x00, 0x02, 0xDF, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE0, 0x78,
	0x23, 0x00, 0x00, 0x02, 0xE1, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE2, 0x89,
	0x23, 0x00, 0x00, 0x02, 0xE3, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE4, 0x9E,
	0x23, 0x00, 0x00, 0x02, 0xE5, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE6, 0xB7,
	0x23, 0x00, 0x00, 0x02, 0xE7, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xE8, 0xCE,
	0x23, 0x00, 0x00, 0x02, 0xE9, 0x03,
	0x23, 0x00, 0x00, 0x02, 0xEA, 0xD1,

	0x23, 0x00, 0x00, 0x02, 0xFF, 0x05,
	0x23, 0x00, 0x00, 0x02, 0xFB, 0x01,

	0x23, 0x00, 0x00, 0x02, 0x00, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x01, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x02, 0x07,
	0x23, 0x00, 0x00, 0x02, 0x03, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x04, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x05, 0x25,
	0x23, 0x00, 0x00, 0x02, 0x06, 0x1D,
	0x23, 0x00, 0x00, 0x02, 0x07, 0x23,
	0x23, 0x00, 0x00, 0x02, 0x08, 0x1B,
	0x23, 0x00, 0x00, 0x02, 0x09, 0x21,
	0x23, 0x00, 0x00, 0x02, 0x0A, 0x19,
	0x23, 0x00, 0x00, 0x02, 0x0B, 0x1F,
	0x23, 0x00, 0x00, 0x02, 0x0C, 0x17,
	0x23, 0x00, 0x00, 0x02, 0x0D, 0x05,
	0x23, 0x00, 0x00, 0x02, 0x0E, 0x04,
	0x23, 0x00, 0x00, 0x02, 0x0F, 0x0F,
	0x23, 0x00, 0x00, 0x02, 0x10, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x11, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x12, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x13, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x14, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x15, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x16, 0x06,
	0x23, 0x00, 0x00, 0x02, 0x17, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x18, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x19, 0x24,
	0x23, 0x00, 0x00, 0x02, 0x1A, 0x1C,
	0x23, 0x00, 0x00, 0x02, 0x1B, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x1C, 0x1A,
	0x23, 0x00, 0x00, 0x02, 0x1D, 0x20,
	0x23, 0x00, 0x00, 0x02, 0x1E, 0x18,
	0x23, 0x00, 0x00, 0x02, 0x1F, 0x1E,
	0x23, 0x00, 0x00, 0x02, 0x20, 0x16,
	0x23, 0x00, 0x00, 0x02, 0x21, 0x05,
	0x23, 0x00, 0x00, 0x02, 0x22, 0x04,
	0x23, 0x00, 0x00, 0x02, 0x23, 0x0E,
	0x23, 0x00, 0x00, 0x02, 0x24, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x25, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x26, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x27, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x28, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x29, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x2A, 0x0E,
	0x23, 0x00, 0x00, 0x02, 0x2B, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x2D, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x2F, 0x16,
	0x23, 0x00, 0x00, 0x02, 0x30, 0x1E,
	0x23, 0x00, 0x00, 0x02, 0x31, 0x18,
	0x23, 0x00, 0x00, 0x02, 0x32, 0x20,
	0x23, 0x00, 0x00, 0x02, 0x33, 0x1A,
	0x23, 0x00, 0x00, 0x02, 0x34, 0x22,
	0x23, 0x00, 0x00, 0x02, 0x35, 0x1C,
	0x23, 0x00, 0x00, 0x02, 0x36, 0x24,
	0x23, 0x00, 0x00, 0x02, 0x37, 0x05,
	0x23, 0x00, 0x00, 0x02, 0x38, 0x04,
	0x23, 0x00, 0x00, 0x02, 0x39, 0x06,
	0x23, 0x00, 0x00, 0x02, 0x3A, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x3B, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x3D, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x3F, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x40, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x41, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x42, 0x0F,
	0x23, 0x00, 0x00, 0x02, 0x43, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x44, 0x40,
	0x23, 0x00, 0x00, 0x02, 0x45, 0x17,
	0x23, 0x00, 0x00, 0x02, 0x46, 0x1F,
	0x23, 0x00, 0x00, 0x02, 0x47, 0x19,
	0x23, 0x00, 0x00, 0x02, 0x48, 0x21,
	0x23, 0x00, 0x00, 0x02, 0x49, 0x1B,
	0x23, 0x00, 0x00, 0x02, 0x4A, 0x23,
	0x23, 0x00, 0x00, 0x02, 0x4B, 0x1D,
	0x23, 0x00, 0x00, 0x02, 0x4C, 0x25,
	0x23, 0x00, 0x00, 0x02, 0x4D, 0x05,
	0x23, 0x00, 0x00, 0x02, 0x4E, 0x04,
	0x23, 0x00, 0x00, 0x02, 0x4F, 0x07,
	0x23, 0x00, 0x00, 0x02, 0x50, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x51, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x52, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x53, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x5B, 0x0A,
	0x23, 0x00, 0x00, 0x02, 0x5C, 0x0A,
	0x23, 0x00, 0x00, 0x02, 0x63, 0x0A,
	0x23, 0x00, 0x00, 0x02, 0x64, 0x15,
	0x23, 0x00, 0x00, 0x02, 0x68, 0x24,
	0x23, 0x00, 0x00, 0x02, 0x69, 0x24,
	0x23, 0x00, 0x00, 0x02, 0x90, 0x7B,
	0x23, 0x00, 0x00, 0x02, 0x91, 0x10,  //VFP
	0x23, 0x00, 0x00, 0x02, 0x92, 0x15,  //VBP
	0x23, 0x00, 0x00, 0x02, 0x7E, 0x10,
	0x23, 0x00, 0x00, 0x02, 0x7F, 0x10,
	0x23, 0x00, 0x00, 0x02, 0x80, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x98, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x99, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x54, 0x2E,
	0x23, 0x00, 0x00, 0x02, 0x59, 0x38,
	0x23, 0x00, 0x00, 0x02, 0x5D, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x5E, 0x27,
	0x23, 0x00, 0x00, 0x02, 0x62, 0x39,
	0x23, 0x00, 0x00, 0x02, 0x66, 0x88,
	0x23, 0x00, 0x00, 0x02, 0x67, 0x11,
	0x23, 0x00, 0x00, 0x02, 0x6A, 0x0E,
	0x23, 0x00, 0x00, 0x02, 0x6B, 0x20,
	0x23, 0x00, 0x00, 0x02, 0x6C, 0x08,
	0x23, 0x00, 0x00, 0x02, 0x6D, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x7D, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xB7, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xB8, 0x0A,
	0x23, 0x00, 0x00, 0x02, 0xBA, 0x13,
	0x23, 0x00, 0x00, 0x02, 0xBC, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xBD, 0x55,
	0x23, 0x00, 0x00, 0x02, 0xBE, 0x38,
	0x23, 0x00, 0x00, 0x02, 0xBF, 0x44,
	0x23, 0x00, 0x00, 0x02, 0xCF, 0x88,
	0x23, 0x00, 0x00, 0x02, 0xC8, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xC9, 0x55,
	0x23, 0x00, 0x00, 0x02, 0xCA, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xCB, 0x55,
	0x23, 0x00, 0x00, 0x02, 0xCC, 0xA2,
	0x23, 0x00, 0x00, 0x02, 0xCE, 0x88,
	0x23, 0x00, 0x00, 0x02, 0xCF, 0x88,
	0x23, 0x00, 0x00, 0x02, 0xD0, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xD1, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xD3, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xD5, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xD6, 0x22,
	0x23, 0x00, 0x00, 0x02, 0xD7, 0x31,
	0x23, 0x00, 0x00, 0x02, 0xD8, 0x7E,

	0x23, 0x00, 0x00, 0x02, 0xFF, 0x00,   //CMD1
	0x23, 0x00, 0x00, 0x02, 0xFB, 0x01,
	0x23, 0x00, 0x00, 0x02, 0xD3, 0x24,   //VBP
	0x23, 0x00, 0x00, 0x02, 0xD4, 0x20,   //VFP
	0x23, 0x00, 0x00, 0x02, 0xD5, 0x5A,   //HBP
	0x23, 0x00, 0x00, 0x02, 0xD6, 0x50,   //HFP
	0x23, 0x00, 0x00, 0x02, 0xD7, 0x00,
	0x23, 0x00, 0x00, 0x02, 0x35, 0x00,

	0x23, 0x00, 0x00, 0x02, 0xFF, 0x00,
	0x23, 0x00, 0x00, 0x02, 0xFB, 0x01,
	0x23, 0x00, 0x00, 0x02, 0x51, 0xFF,
	0x23, 0x00, 0x00, 0x02, 0x53, 0x2C,
	0x23, 0x00, 0x00, 0x02, 0x36, 0x00,
	0x13, 0x78, 0x00, 0x01, 0x11,
	0x13, 0x32, 0x00, 0x01, 0x29,
	CMD_END
};

static int mipi_dsi_send_cmds(struct sprd_dsi *dsi, void *data)
{
	uint16_t len;
	struct dsi_cmd_desc *cmds = data;

	if ((cmds == NULL) || (dsi == NULL))
		return -1;

	for (; cmds->data_type != CMD_END;) {
		len = (cmds->wc_h << 8) | cmds->wc_l;
		mipi_dsi_gen_write(dsi, cmds->payload, len);
		if (cmds->wait)
			msleep(cmds->wait);
		cmds = (struct dsi_cmd_desc *)(cmds->payload + len);
	}
	return 0;
}

static int nt35532_init(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	struct sprd_dphy *dphy = &dphy_device;

	mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_send_cmds(dsi, init_data);
	mipi_dsi_set_work_mode(dsi, SPRD_MIPI_MODE_VIDEO);
	mipi_dsi_state_reset(dsi);
	mipi_dphy_hs_clk_en(dphy, true);

	return 0;
}

static int nt35532_readid(void)
{
	struct sprd_dsi *dsi = &dsi_device;
	uint8_t read_buf[4] = {0};
	uint8_t pwr_val;

	mipi_dsi_lp_cmd_enable(dsi, true);
	mipi_dsi_set_max_return_size(dsi, 3);
	mipi_dsi_dcs_read(dsi, 0xF4, read_buf, 1);

	if (read_buf[0] == 0x32) {
		pr_info("nt35532 read id success!\n");

		i2c_set_bus_num(3);
		pwr_val = i2c_reg_read(0x3E, 0x00);
		if (0x0A != pwr_val) {
			i2c_reg_write(0x3E, 0x00, 0x0A);
			i2c_reg_write(0x3E, 0x01, 0x0A);
			i2c_reg_write(0x3E, 0x03, 0x03);
			i2c_reg_write(0x3E, 0xFF, 0x80);
			mdelay(50);
		}
		return 0;
	}

	pr_err("nt35532 read id failed!\n");
	return -1;
}

static int nt35532_power(int on)
{
	if (on) {
		sprd_gpio_request(NULL, CONFIG_LCM_GPIO_AVDDEN);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_AVDDEN, 1);
		mdelay(10);

		sprd_gpio_request(NULL, CONFIG_LCM_GPIO_AVEEEN);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_AVEEEN, 1);
		mdelay(20);

		sprd_gpio_request(NULL, CONFIG_LCM_GPIO_RSTN);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 1);
		mdelay(5);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
		mdelay(5);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 1);
		mdelay(5);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
		mdelay(5);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 1);
		mdelay(20);
	} else {
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_AVEEEN, 0);
		mdelay(20);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_AVDDEN, 0);
		mdelay(10);
		sprd_gpio_direction_output(NULL, CONFIG_LCM_GPIO_RSTN, 0);
		mdelay(5);
	}

	return 0;
}

static struct panel_ops nt35532_ops = {
	.init = nt35532_init,
	.read_id = nt35532_readid,
	.power = nt35532_power,
};

static struct panel_info nt35532_info = {
	/* common parameters */
	.lcd_name = "lcd_nt35532_truly_mipi_fhd",
	.type = SPRD_PANEL_TYPE_MIPI,
	.bpp = 24,
//	.fps = 60,
	.width = 1080,
	.height = 1920,

	/* DPI specific parameters */
	.pixel_clk = 153600000, /*Hz*/
	.rgb_timing = {
		.hfp = 176,
		.hbp = 16,
		.hsync = 10,
		.vfp = 32,
		.vbp = 32,
		.vsync = 4,
	},

	/* MIPI DSI specific parameters */
#ifdef CONFIG_SPRD_SOC_SP9853I
	.phy_freq = 9798*100,
#else
	.phy_freq = 9646*100,
#endif
	.lane_num = 4,
	.work_mode = SPRD_MIPI_MODE_VIDEO,
	.burst_mode = PANEL_VIDEO_BURST_MODE,
	.nc_clk_en = false,
};

struct panel_driver nt35532_truly_driver = {
	.info = &nt35532_info,
	.ops = &nt35532_ops,
};
