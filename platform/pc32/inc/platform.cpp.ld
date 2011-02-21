#ifndef PLATFORM_CPP_LD
#define PLATFORM_CPP_LD
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

/* Every bsp-specific symbol must use this macro to define it.
 * So we could avoid these symbols knock up against the generic symbols.
 */
#ifdef BSP_SYM
#undef BSP_SYM
#define BSP_SYM(sym)	MK_BSP_SYM("pc32",sym)
#endif 


/* pc32 platform need some ISA reserved address, I'll define it later.
 */

	



#endif