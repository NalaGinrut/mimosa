/*	
 *  Copyright (C) 2010-2011  
 *	"Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


/* This ld script used for kernel linking. 
 * Modify it may effect the whole kernel framework, so DON'T MODIFY IT!!!
 */

#include <generic/generic.ld.h>
#include <osconfig.h>

/* "conf.ld" is $(TOP)/config/conf.ld */
INCLUDE conf.ld

/* This platform.cpp.ld is used to specific bsp memory layout.
 * We insert it next to .text in case some platform need mapping/reserved
 * low memory address. BSP developers must define this file or just 
 * leave it empty.
 */
#include <bsp/platform.cpp.ld>

SECTIONS
{

	. = KERNEL_BEGIN;
	/* principio is default kernel start address */
	PROVIDE(principio = KERNEL_BEGIN);
	
	.text : {
	      TEXT_SECTION	
	}

	/* C99 permit program to reference "etext" without any error, 
	 * even if "etext" had never been defined. 
	 * We define it here for later use.
 	 */
	PROVIDE(etext = .);

	/* HERE IS RODATA */
	RO_DATA

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
	. = ALIGN(PG_SIZE);

	/* The data segment */
	.data : {
	      DATA_SECTION
	}

	PROVIDE(edata = .);

	.bss : {
	     BSS_SECTION
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
