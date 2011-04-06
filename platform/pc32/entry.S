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

#include <osconfig.h>
#include <multi_boot.h>
#include <now/cpu/segment.h>
#include <now/drivers/bda.h>


#define RELOC(addr)	((addr) - KERN_BASE)

###############
# Text Segment
###############
	
.text

#ifdef __MULTI_BOOT__

// Must be aligned to 64bit according to multi_boot protocol	
.align 4
multiboot_header:
	/* magic */
	.long MULTIBOOT_HEADER_MAGIC
	/* flags */
	.long MULTIBOOT_HEADER_FLAGS
	/* checksum */
	.long (-(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS))

multiboot_header_end:

#endif // End of __MULTI_BOOT__


.globl	_start
_start:
	movw	$POST_WORM_BOOT ,BDA_POST_RESET

	call	set_gdt

set_gdt:
	lgdt	RELOC(init_gdt_desc)
	movw	$KD_SEL ,%ax	# set data seg_desc

	/* don't forget that segment-regs have only 16bit */
	movw	%ax ,%ds	# data segment
	movw	%ax ,%es	# extra segment
	movw	%ax ,%ss	# stack segment
	
	ljmp	$KC_SEL ,$set_cee_env

set_cee_env:
	movl	$0 ,%ebp	# clear ebp to terminate the backtrace
	movl	$tmp_stack_top ,%esp
	
	# jump into the Cee code~yeah~I hate ASM!
	call	platform_init

	# TODO: I need a debugger to check the reason why it returned.
return_is_error:
#ifndef __KERN_DEBUG__	
	jmp	return_is_error
#else
	/* TODO: we need to save environment when shit happens. And I
	 * think there're two alternative approaches:
	 * 1. save them immediately while return.
	 * 2. backtrace them in the kern_debug.
	 */
	call	kern_debug
#endif
	
	
.data

/* establish the temporary stack
 */
.p2align PG_SHIFT /* It should be decided by BSP config, but..
		   * Anyway, it's just a temporary stack...
		   */
	.globl tmp_stack
tmp_stack:
	.space	KERN_STACK_SIZE
	.globl tmp_stack_top
tmp_stack_top:	
	
/* You may notice that this code below is as alike as segment handle
 * code in the bootloader. In fact they are the same, the only difference
 * between is that the base address should be a little change. That is,
 * at this time we need a "base" which satisfy "KERN_BASE+base=0",then we
 * get "base=-KERN_BASE", it's easy ah?
 * But why we need to do that? Because we want to run Cee function, not
 * assembler anyway. So we need to establish a simple Cee runtime
 * environment: a data seg ,code seg to hold the program, and a stack for  * calling procedure.
 * When we entering the Cee world, they will be re-established formally.
 */
	.p2align 2	/* force 4byte aligment */

/* Well~still the gdt trick~I just like it
 */
init_gdt_desc:
	.word 0x17
	.long RELOC(init_gdt_desc)
	.word 0x00
	SEG_INIT(USEG_X|USEG_R ,RELOC(0) ,FULL_ADDR)	# code segment
	SEG_INIT(USEG_W ,RELOC(0) ,FULL_ADDR)	# data segment

