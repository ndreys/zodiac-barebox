/*
 * [origin: Linux kernel include/asm-arm/arch-at91/at91sam9_smc.h]
 *
 * Copyright (C) 2007 Andrew Victor
 * Copyright (C) 2007 Atmel Corporation.
 *
 * Static Memory Controllers (SMC) - System peripherals registers.
 * Based on AT91SAM9261 datasheet revision D.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef AT91SAM9_SMC_H
#define AT91SAM9_SMC_H

#define at91_smc_read(id, field) \
	__raw_readl(AT91_BASE_SMC + ((id) * 0x10) + field)

#define at91_smc_write(id, field, value) \
	__raw_writel(value, AT91_BASE_SMC + ((id) * 0x10) + field)

#ifndef __ASSEMBLY__
struct sam9_smc_config {
	/* Setup register */
	u8 ncs_read_setup;
	u8 nrd_setup;
	u8 ncs_write_setup;
	u8 nwe_setup;

	/* Pulse register */
	u8 ncs_read_pulse;
	u8 nrd_pulse;
	u8 ncs_write_pulse;
	u8 nwe_pulse;

	/* Cycle register */
	u16 read_cycle;
	u16 write_cycle;

	/* Mode register */
	u32 mode;
	u8 tdf_cycles:4;

	/* Timings register */
	u8 tclr;
	u8 tadl;
	u8 tar;
	u8 ocms;
	u8 trr;
	u8 twb;
	u8 rbnsel;
	u8 nfsel;
};

extern void sam9_smc_configure(int id, int cs, struct sam9_smc_config *config);
extern void sam9_smc_read(int id, int cs, struct sam9_smc_config *config);
extern void sam9_smc_read_mode(int id, int cs, struct sam9_smc_config *config);
extern void sam9_smc_write_mode(int id, int cs, struct sam9_smc_config *config);

extern void sama5_smc_configure(int id, int cs, struct sam9_smc_config *config);
#endif

#define AT91_SMC_SETUP		0x00				/* Setup Register for CS n */
#define		AT91_SMC_NWESETUP	(0x3f << 0)			/* NWE Setup Length */
#define			AT91_SMC_NWESETUP_(x)	((x) << 0)
#define		AT91_SMC_NCS_WRSETUP	(0x3f << 8)			/* NCS Setup Length in Write Access */
#define			AT91_SMC_NCS_WRSETUP_(x)	((x) << 8)
#define		AT91_SMC_NRDSETUP	(0x3f << 16)			/* NRD Setup Length */
#define			AT91_SMC_NRDSETUP_(x)	((x) << 16)
#define		AT91_SMC_NCS_RDSETUP	(0x3f << 24)			/* NCS Setup Length in Read Access */
#define			AT91_SMC_NCS_RDSETUP_(x)	((x) << 24)

#define AT91_SMC_PULSE		0x04				/* Pulse Register for CS n */
#define		AT91_SMC_NWEPULSE	(0x7f <<  0)			/* NWE Pulse Length */
#define			AT91_SMC_NWEPULSE_(x)	((x) << 0)
#define		AT91_SMC_NCS_WRPULSE	(0x7f <<  8)			/* NCS Pulse Length in Write Access */
#define			AT91_SMC_NCS_WRPULSE_(x)((x) << 8)
#define		AT91_SMC_NRDPULSE	(0x7f << 16)			/* NRD Pulse Length */
#define			AT91_SMC_NRDPULSE_(x)	((x) << 16)
#define		AT91_SMC_NCS_RDPULSE	(0x7f << 24)			/* NCS Pulse Length in Read Access */
#define			AT91_SMC_NCS_RDPULSE_(x)((x) << 24)

#define AT91_SMC_CYCLE		0x08				/* Cycle Register for CS n */
#define		AT91_SMC_NWECYCLE	(0x1ff << 0 )			/* Total Write Cycle Length */
#define			AT91_SMC_NWECYCLE_(x)	((x) << 0)
#define		AT91_SMC_NRDCYCLE	(0x1ff << 16)			/* Total Read Cycle Length */
#define			AT91_SMC_NRDCYCLE_(x)	((x) << 16)

#define AT91_SAMA5_SMC_TIMINGS	0x0c				/* Timings register for CS n */
#define		AT91_SMC_TCLR		(0x0f  <<  0)			/* CLE to REN Low Delay */
#define			AT91_SMC_TCLR_(x)	((x) << 0)
#define		AT91_SMC_TADL		(0x0f  <<  4)			/* ALE to Data Start */
#define			AT91_SMC_TADL_(x)	((x) << 4)
#define		AT91_SMC_TAR		(0x0f  <<  8)			/* ALE to REN Low Delay */
#define			AT91_SMC_TAR_(x)	((x) << 8)
#define		AT91_SMC_OCMS		(0x1   << 12)			/* Off Chip Memory Scrambling Enable */
#define			AT91_SMC_OCMS_(x)	((x) << 12)
#define		AT91_SMC_TRR		(0x0f  << 16)			/* Ready to REN Low Delay */
#define			AT91_SMC_TRR_(x)        ((x) << 16)
#define		AT91_SMC_TWB		(0x0f  << 24)			/* WEN High to REN to Busy */
#define			AT91_SMC_TWB_(x)	((x) << 24)
#define		AT91_SMC_RBNSEL		(0x07  << 28)			/* Ready/Busy Line Selection */
#define			AT91_SMC_RBNSEL_(x)	((x) << 28)
#define		AT91_SMC_NFSEL		(0x01  << 31)			/* Nand Flash Selection */
#define			AT91_SMC_NFSEL_(x)	((x) << 31)

#define AT91_SAM9_SMC_MODE 0xc
#define AT91_SAMA5_SMC_MODE 0x10
#define		AT91_SMC_READMODE	(1 <<  0)			/* Read Mode */
#define		AT91_SMC_WRITEMODE	(1 <<  1)			/* Write Mode */
#define		AT91_SMC_EXNWMODE	(3 <<  4)			/* NWAIT Mode */
#define			AT91_SMC_EXNWMODE_DISABLE	(0 << 4)
#define			AT91_SMC_EXNWMODE_FROZEN	(2 << 4)
#define			AT91_SMC_EXNWMODE_READY		(3 << 4)
#define		AT91_SMC_BAT		(1 <<  8)			/* Byte Access Type */
#define			AT91_SMC_BAT_SELECT		(0 << 8)
#define			AT91_SMC_BAT_WRITE		(1 << 8)
#define		AT91_SMC_DBW		(3 << 12)			/* Data Bus Width */
#define			AT91_SMC_DBW_8			(0 << 12)
#define			AT91_SMC_DBW_16			(1 << 12)
#define			AT91_SMC_DBW_32			(2 << 12)
#define		AT91_SMC_TDF		(0xf << 16)			/* Data Float Time. */
#define			AT91_SMC_TDF_(x)		((x) << 16)
#define		AT91_SMC_TDFMODE	(1 << 20)			/* TDF Optimization - Enabled */
#define		AT91_SMC_PMEN		(1 << 24)			/* Page Mode Enabled */
#define		AT91_SMC_PS		(3 << 28)			/* Page Size */
#define			AT91_SMC_PS_4			(0 << 28)
#define			AT91_SMC_PS_8			(1 << 28)
#define			AT91_SMC_PS_16			(2 << 28)
#define			AT91_SMC_PS_32			(3 << 28)

#endif
