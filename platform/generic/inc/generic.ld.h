#ifndef GENERIC_LD_H
#define GENERIC_LD_H
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



#ifndef KERN_SYM
#define KERN_SYM(sym)	__mimosa_##sym
#endif

#ifndef MK_BSP_SYM
#define MK_BSP_SYM(bsp,sym)	__mimosa_##bsp##_sym
#endif

/* Align . to 8, it's maximum function alignment */
#define ALIGN_FUNC()	. = ALIGN(8)

#define DATA_SECTION	\
	*(.data)	\

#define TEXT_SECTION				\
	ALIGN_FUNC();				\
	*(.text)				\
	*(.stub .text.* .gnu.linkonce.t.*)

#define BSS_SECTION			\
	PROVIDE(__bss_start = .);	\
	*(.bss)		      		\
	PROVIDE(__bss_end = .);

#define STAB_SECTION			\
	PROVIDE(__STAB_BEGIN__ = .);	\
	*(.stab);	       	 	\
	PROVIDE(__STAB_END__ = .);	\
	
#define STABSTR_SECTION			\
	PROVIDE(__STABSTR_BEGIN__ = .);	\
	*(.stabstr);		    	\
	PROVIDE(__STABSTR_END__ = .);	


#define MK_RODATA(align)		\
	. = ALIGN((align));		\
	.rodata : {			\
		*(.rodata)		\
		*(.rodata.*)		\
		*(.gnu.linkonce.r.*)	\
	}  
	
#define RO_DATA	MK_RODATA(PGSIZE)


#endif 
