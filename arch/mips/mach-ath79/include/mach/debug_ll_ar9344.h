/*
 * Copyright (C) 2017 Oleksij Rempel <o.rempel@pengutronix.de>
 * Copyright (C) 2012, 2013 Antony Pavlov <antonynpavlov@gmail.com>
 *
 * This file is part of barebox.
 * See file CREDITS for list of people who contributed to this project.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __AR9344_DEBUG_LL__
#define __AR9344_DEBUG_LL__

#include <asm/addrspace.h>
#include <mach/ar71xx_regs.h>

#define DEBUG_LL_UART_ADDR		KSEG1ADDR(AR934X_UART0_BASE)
#define DEBUG_LL_UART_SHIFT		AR934X_UART0_SHIFT

#define DEBUG_LL_UART_DIVISOR_40	(40000000 / (16 * CONFIG_BAUDRATE))
#define DEBUG_LL_UART_DIVISOR_25	(25000000 / (16 * CONFIG_BAUDRATE))

#define UART_THR			(0x0 << DEBUG_LL_UART_SHIFT)
#define UART_RBR			(0x0 << DEBUG_LL_UART_SHIFT)
#define UART_DLL			(0x0 << DEBUG_LL_UART_SHIFT)
#define UART_IER			(0x1 << DEBUG_LL_UART_SHIFT)
#define UART_DLM			(0x1 << DEBUG_LL_UART_SHIFT)
#define UART_FCR			(0x2 << DEBUG_LL_UART_SHIFT)
#define UART_LCR			(0x3 << DEBUG_LL_UART_SHIFT)
#define UART_LSR			(0x5 << DEBUG_LL_UART_SHIFT)

#define UART_LCR_W			0x07	/* Set UART to 8,N,2 & DLAB = 0 */
#define UART_LCR_DLAB			0x87	/* Set UART to 8,N,2 & DLAB = 1 */

#define UART_LSR_DR     		0x01    /* UART received data present */
#define UART_LSR_THRE			0x20	/* Xmit holding register empty */

#define UART_FCR_RST			0x07	/* FIFO_EN | RCVR_FIFO_RST | XMIT_FIFO_RST */

#ifndef __ASSEMBLY__

/*
 * C macros
 */

#include <asm/io.h>

static inline void PUTC_LL(char ch)
{
#ifdef CONFIG_DEBUG_LL
	while (!(__raw_readl((u8 *)DEBUG_LL_UART_ADDR + UART_LSR) & UART_LSR_THRE))
		;
	__raw_writel(ch, (u8 *)DEBUG_LL_UART_ADDR + UART_THR);
#endif /* CONFIG_DEBUG_LL */
}
#else /* __ASSEMBLY__ */
/*
 * Macros for use in assembly language code
 */

.macro	debug_ll_ar9344_init
#ifdef CONFIG_DEBUG_LL

	/* find out the ref clock */
	li	t5,	KSEG1ADDR(WASP_BOOTSTRAP_REG);
	li	t6,	WASP_REF_CLK_25
	lw	t7,	0(t5);
	and	t6,	t7,	t6
	beq	zero,	t6,	uart_setup_ref25_val
	nop
uart_setup_ref40_val:
	li	t5, DEBUG_LL_UART_DIVISOR_40
	b	1f
	nop

uart_setup_ref25_val:
	li	t5, DEBUG_LL_UART_DIVISOR_25
1:

	la	t0, DEBUG_LL_UART_ADDR

	li	t1, UART_LCR_DLAB		/* DLAB on */
	sw	t1, UART_LCR(t0)		/* Write it out */

	sw	t5, UART_DLL(t0)		/* write low order byte */
	li	t1, 0
	sw	t1, UART_DLM(t0)		/* write high order byte */

	li	t1, UART_LCR_W			/* DLAB off */
	sw	t1, UART_LCR(t0)		/* Write it out */

	li	t1, UART_FCR_RST		/* reset FIFOs */
	sw	t1, UART_FCR(t0)		/* Write it out */

	li	t1, 0				/* disable interrupts */
	sw	t1, UART_IER(t0)		/* Write it out */
#endif /* CONFIG_DEBUG_LL */
.endm

/*
 * output a character in a0
 */
.macro	debug_ll_outc_a0
#ifdef CONFIG_DEBUG_LL
	.set	push
	.set	reorder

	la	t0, DEBUG_LL_UART_ADDR

201:	lw	t1, UART_LSR(t0)	/* get line status */
	andi	t1, t1, UART_LSR_THRE	/* check for transmitter empty */
	beqz	t1, 201b			/* try again */

	sw	a0, UART_THR(t0)	/* write the character */

	.set	pop
#endif /* CONFIG_DEBUG_LL */
.endm

/*
 * output a character
 */
.macro	debug_ll_outc chr
#ifdef CONFIG_DEBUG_LL
	li	a0, \chr
	debug_ll_outc_a0
#endif /* CONFIG_DEBUG_LL */
.endm

/*
 * output CR + NL
 */
.macro	debug_ll_outnl
#ifdef CONFIG_DEBUG_LL
	debug_ll_outc '\r'
	debug_ll_outc '\n'
#endif /* CONFIG_DEBUG_LL */
.endm

/*
 * check character in input buffer
 * return value:
 *  v0 = 0   no character in input buffer
 *  v0 != 0  character in input buffer
 */
.macro	debug_ll_tstc
#ifdef CONFIG_DEBUG_LL
	.set	push
	.set	reorder

	la      t0, DEBUG_LL_UART_ADDR

	/* get line status and check for data present */
	lw	t1, UART_LSR(t0)
	andi	v0, t1, UART_LSR_DR

	.set	pop
#endif /* CONFIG_DEBUG_LL */
.endm

/*
 * get character to v0
 */
.macro	debug_ll_getc
#ifdef CONFIG_DEBUG_LL
	.set	push
	.set	reorder

204:
	debug_ll_tstc

	/* try again */
	beqz	v0, 204b

	/* read a character */
	lw	v0, UART_RBR(t0)

	.set	pop
#endif /* CONFIG_DEBUG_LL */
.endm
#endif /* __ASSEMBLY__ */

#endif /* __INCLUDE_MIPS_ASM_DEBUG_LL_NS16550_H__ */
