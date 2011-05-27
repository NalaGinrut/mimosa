#ifndef	__MIMOSA_GLOBAL_H
#define __MIMOSA_GLOBAL_H
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

#include <osconfig.h>

#define MK_GLOBAL_VAR(var)	(__mimosa_global_##var)
#define GET_GLOBAL_VAR(var)	EX_GLOBAL_VAR(var)


#define KERN_SYM(sym)	__mimosa_##sym

#define MK_BSP_SYM(bsp ,sym)	__mimosa_##bsp##_sym
#define GET_BSP_VAR(var)	MK_BSP_SYM(MIMOSA_BSP ,var)	

	
#endif // End of __MIMOSA_GLOBAL_H;