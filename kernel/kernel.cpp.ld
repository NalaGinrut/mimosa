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


/* This ld script used for kernel linking. 
 * Modify it may effect the whole kernel framework, so DON'T MODIFY IT!!!
 */

#include <generic/generic.ld.h>


/* "conf.ld" is $(TOP)/config/conf.ld */
INCLUDE conf.ld


SECTIONS
{

	/* principio is default kernel start address */
	PROVIDE(principio = DEFINED(principio) ? principio : KERNEL_BEGIN);
	. = principio;

	.text : {
	      TEXT_SECTION	
	}

/* This platform.cpp.ld is used to specific bsp memory layout.
 * We insert it next to .text in case some platform need mapping/reserved
 * low memory address. BSP developers must define this file or just 
 * leave it empty.
 */
#include <now/platform.cpp.ld>

	/* C99 permit program to reference "etext" without any error, 
	 * even if "etext" had never been defined. 
	 * We define it here for later use.
 	 */
	PROVIDE(etext = .);

	/* Include debugging information in kernel memory */
	.stab : {
	      STAB_SECTION
	      BYTE(0) /* Force the linker to allocate space
		       * for this section */

	}

	.stabstr : {
		 STABSTR_SECTION
		 BYTE(0) /* Force the linker to allocate space
		       	  * for this section */
	}

	/* Adjust the address for the data segment to the next page */
	. = ALIGN(PGSIZE);

	/* The data segment */
	.data : {
	      DATA_SECTION
	} :data

	PROVIDE(edata = .);

	.bss : {
		*(.bss)
	}

	/* available memory address entry */
	PROVIDE(recondo = .);
	
	/* init contain run-once code, this section will be merged to
	 * available memory. limit-addr is "init_end" after startup.
	 */
	.init : {
	      	*(.init)
	}
	PROVIDE(KERN_SYM(init_end) = .);

}
