#ifndef __MIMOSA_PC32_PLATFORM_CPP_LD
#define __MIMOSA_PC32_PLATFORM_CPP_LD
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

/* Every bsp-specific symbol must use this macro to define it.
 * So we could avoid these symbols knock up against the generic symbols.
 */
#ifdef BSP_SYM
#undef BSP_SYM
#define BSP_SYM(sym)	MK_BSP_SYM("pc32",sym)
#endif 


/* pc32 platform need some ISA reserved address, I'll define it later.
 */

	



#endif // End of __MIMOSA_PC32_PLATFORM_CPP_LD
