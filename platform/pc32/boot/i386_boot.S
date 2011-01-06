/* Copyleft(c)2010 HackerFellowship. All lefts reserved.
  
 * NalaGinrut <NalaGinrut@gmail.com>
  
 * May Lord Bless!Happy Hacking!
  
 * This program is free software;you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundataion;either version 2 of the License,or (at 
 * your option) any later version.
  
 * You should have read the GNU General Public License before start "RTFSC".
  
 * If not,see <http://www.gnu.org/licenses/>
 */

#include "i386_boot.h"
#include "cpu/crx.h"

	

#################
# ENTRY POINT
#################

.globl	start
start:	.code16
	cli
	cld

	# clear important data segment regs (DS,ES,SS)
	xorw	%ax ,%ax
	movw	%ax ,%ds
	movw	%ax ,%es
	movw	%ax ,%ss

	# set up stack point. a smart design is downword from 0x7c00
	movw 	$start ,%sp

	jmp	A20_1	# goto set A20

##############
# Enable A20
##############

# Check whether KeyBoard Controller's buffer is busy,if "yes",we need a busy wait. return for "no".
# There's no need to backup AL, it's just a sub_proc under same environment or a continuation.
busy_check:
		inb	$KB_CON_STAT ,%al
		testb	$KB_IS_BUSY ,%al
		jnz	busy_check
		ret
A20_1:
		call	busy_check
		movb	$KB_WRITE ,%al		# set output port: command->Write
		outb	%al ,$KB_CON_INBUF	# set it!
A20_2:
		call	busy_check
		movb	$A20_EN ,%al		# set A20->enable
		outb	%al ,$KB_CON_DPORT	# set it!

# FIXME: Should we need fast_A20?? Is it really necessary? How fast could it be??

######################
# Switch Real to PMODE
######################

r2p:
		cli

		lgdt	gdt_descriptor
		movl	%cr0 ,%eax		# crx can't change directly
		orl	$CR0_PM ,%eax		# enable Protected Mode
		movl	%eax ,%cr0

		ljmp	$PM_CS ,$p_mode

####################
# Under PMODE
####################
# Set up p_mode segment registers
	
p_mode:		.code32
		movw	$PM_CS ,%ax
		movw	%ax ,%ds
		movw	%ax ,%es
		movw	%ax ,%ss
		movw	%ax ,%gs
		movw	%ax ,%fs

# now we could load code from C
		call	cmain

spin:		jmp	spin	# cmain never return. But it's a simplest handler for such error.
				# maybe we can designed a more friendly handler. e.g: print some msg...

		.p2align 2	# paddr align to 1<<2
gdt_descriptor:
		.word	0x17	# limit: 8*N-1
				# N is the numbers of segments(include NULL)
		.long	gdt_descriptor
		.word	0x00	# NOTE: just one word
		# it's a gdt magic! NULL for standard, but we could store
		# gdt header in it!
		# check "lgdt" in IA32-BOOK,"lgdt" needs an address structure
		# which like:
		# 1.sizeof(defacto_gdt)
		# 2.address of defacto_gdt

		# FIXME: I want to use SEG() macro ,it's more clear.
		# I will fix it later...
		SEG_INIT(STA_X | STA_R ,0x0 ,0xffffffff)
		SEG_INIT(STA_W ,0x0 ,0xffffffff)

	
