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
#include <osconfig.h>

/* Every bsp-specific symbol must use this macro to define it.
 * So we could avoid these symbols knock up against the generic symbols.
 */
#ifdef BSP_SYM
#undef BSP_SYM
#define BSP_SYM(sym)	MK_BSP_SYM(MIMOSA_BSP,sym)
#endif 


/* pc32 platform need some ISA reserved address, I'll define it later.
 */

/* memory layout of BSP ,you should change them with "make genconf"
 * DO NOT MODIFY THEM MANUALLY!!!
 */
 MK_BSP_SYM(VPT) = KERN_BASE - PT_SIZE;
 MK_BSP_SYM(KSTKTOP) = GET_BSP_SYM(VPT);
 MK_BSP_SYM(ULIM) = GET_BSP_SYM(KSTKTOP) - PT_SIZE;
 MK_BSP_SYM(UVPT) = GET_BSP_SYM(ULIM) - PT_SIZE;
 MK_BSP_SYM(UPAGES) = GET_BSP_SYM(UVPT) - PT_SIZE;
 MK_BSP_SYM(UENVS) = GET_BSP_SYM(UPAGES) - PT_SIZE;
 MK_BSP_SYM(UTOP) = GET_BSP_SYM(UENVS);
 MK_BSP_SYM(UXSTKTOP) = GET_BSP_SYM(UTOP);
 MK_BSP_SYM(USTKTOP) = GET_BSP_SYM(UTOP) - 2 * PG_SIZE;
 MK_BSP_SYM(UTEXT) = 2 * PT_SIZE;
 MK_BSP_SYM(UTEMP) = PT_SIZE;
 MK_BSP_SYM(PFTEMP) = GET_BSP_SYM(UTEMP) + PT_SIZE - PG_SIZE;
 MK_BSP_SYM(USTABDATA) = PT_SIZE / 2;


#endif // End of __MIMOSA_PC32_PLATFORM_CPP_LD
