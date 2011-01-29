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


#include <multi_boot.h>
#include <now/cpu/segment.h>
#include <now/drivers/bda.h>
	

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

	
	

	



	