#
# Makefile for Broadcom BCM947XX boards
#
# Copyright (C) 2008, Broadcom Corporation
# All Rights Reserved.
# 
# THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
# KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
# SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.
#
# $Id: Makefile,v 1.3 2008/05/02 22:49:54 Exp $
#

EXTRA_CFLAGS+=-I$(TOPDIR)/brcm/include 

BCM947XX_OBJS = hndmips.o hndchipc.o sflash.o
BCM947XX_OBJS += nvram.o gpio.o cfe_env.o

EXTRA_CFLAGS += -DLINUX_HYBRID_POSTPROCESSING_REMOVAL
ifeq ($(CONFIG_PCI),y)
BCM947XX_OBJS += hndpci.o pcibios.o
endif

BCM947XX_OBJS += setup.o prom.o time.o irq.o perfcntr.o nvram_linux.o

bcm947xx-objs += $(BCM947XX_OBJS)
obj-y += bcm947xx.o
