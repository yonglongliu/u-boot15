#
# (C) Copyright 2000-2003
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

extra-y	:= start.o

obj-y	+= cpu.o
obj-y	+= generic_timer.o
obj-y	+= cache_v8.o
obj-y	+= exceptions.o
obj-y	+= cache.o
obj-y	+= tlb.o
obj-y	+= transition.o

obj-$(CONFIG_FSL_LSCH3) += fsl-lsch3/
obj-$(CONFIG_TARGET_XILINX_ZYNQMP) += zynqmp/
obj-$(CONFIG_SC9860) += whale2/
obj-$(CONFIG_SOC_SHARKLJ1) += sharklj1/
obj-$(CONFIG_SOC_SHARKLE) += sharkle/
obj-$(CONFIG_SOC_SHARKL3) += sharkl3/
obj-$(CONFIG_SOC_WHALEK) += whalek/
