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


/* A simple ld script for kernel linking. 
 * Modify it may effect the whole kernel framework, so DON'T MODIFY IT!!!
 */


/* "conf.ld" is $(TOP)/config/conf.ld */
INCLUDE conf.ld

SECTIONS
{
	/* principio is default kernel start address */
	PROVIDE(principio = DEFINED(principio) ? principio : k_begin);
	. = principio;

	.text : {
		*(.text .stub .text.* .gnu.linkonce.t.*)
	}

	/* C99 permit program to reference "etext" without any error, 
	 * even if "etext" had never been defined. 
	 * We define it here for later use.
 	 */
	PROVIDE(etext = .);

	.rodata : {
		*(.rodata .rodata.* .gnu.linkonce.r.*)
	}

	/* Include debugging information in kernel memory */
	.stab : {
		PROVIDE(__STAB_BEGIN__ = .);
		*(.stab);
		PROVIDE(__STAB_END__ = .);
		BYTE(0)		/* Force the linker to allocate space
				   for this section */
	}

	.stabstr : {
		PROVIDE(__STABSTR_BEGIN__ = .);
		*(.stabstr);
		PROVIDE(__STABSTR_END__ = .);
		BYTE(0)		/* Force the linker to allocate space
				   for this section */
	}

	/* Adjust the address for the data segment to the next page */
	. = ALIGN(0x1000);

	/* The data segment */
	.data : {
		*(.data)
	}

	PROVIDE(edata = .);

	.bss : {
		*(.bss)
	}

	/* available memory address entry */
	PROVIDE(recondo = .);
	
	/* init contain run-once code, this section will be merged to
	 * available memory. limit-addr is "recondo+init_lim" after startup.
	 */
	.init : {
	      	*(.init)
	}
	PROVIDE(init_end = .);
	
		
}
