#ifndef __MIMOSA_BSP_BITS_H
#define __MIMOSA_BSP_BITS_H
/*
 *  Copyright (C) 2016
 *      "Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
 
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

// This file used for handling bits operation;

#include "bsp_types.h"


#define __BIT	(1UL)
// shift the value "x" to "b" bits;
#define _S(x,b)		((x)<<(b))
#define _B(b)		(__BIT<<(b))

// FIXME: Maybe we need 8/16/64 bits' CHECK_FLAG?
// Note: CHK_FLAG is used during if/while judgement, DO NOT use "do{}while(0)";
#define CHK_FLAG(des ,f)	\
  ( (des) & (f) )

#define SET_FLAG(des ,f)	\
  ( (des) |= (f) );

#define CLR_FLAG(des ,f)	\
  ( (des) &= (f) );

#define FLAG_BASE	0xFFFFFFFFuL // make sure unsigned long!!!;

/* use __FLAG_FIX for FLAG value set. E.g: __FLAG_FIX(3 ,5 ,32) stands for "this flag is 3bits length and start from 5th bit of 32bits integer".
   DON'T call this macro directly, you SHOULD call FLAG_FIX!!!
   Why we SHOULDN'T use "static inline"? We need this fixed_value populate during C Preprocessing. But "static inline" will populate it during runtime.
*/
#define __FLAG_FIX(len ,start ,bit)	\
	( ((FLAG_BASE)>>((bit)-start))<<(len) )


/* Our unified interface is FLAG_FIX;
 */
#define __FIX32(len ,start)	__FLAG_FIX(len ,start ,32)
#define FLAG_FIX(len ,start)	__FIX32(len ,start)

// Round up/down;
// Never use GCC extension! Prefer slow!

/* don't worry about mod/div speed ,I know roundup=rounddown(x+n-1,n),
 * but this form is simpler in C, for '/' op in C has rounddown feature,
 * and mod/div is the same instruction under X86;
 */

/* #define ROUND_UP(x ,n)			\ */
/*   ((n)&0x1 ? __RU_G(x ,n) : __RU_2(x ,n)) */

/* #define ROUND_DOWN(x ,n)		\ */
/*   ((n)&0x1 ? __RD_G(x ,n) : __RD_2(x ,n)) */

#define __RU_G(x ,n)	  	\
  ( ((x)+(n)-1) / (n) )

#define __RD_G(x ,n)	\
  ( (x) - (x)%(n) )

#define __RD_2(x ,n)	\
  ( ((x) & (-n)) )

#define __RU_2(x ,n)	  	\
  ( __RD_2(x ,n) + (n) )

// Rounding operations (efficient when n is a power of 2)
// Round down to the nearest multiple of n
#define ROUND_DOWN(a, n) \
  ((a) - (a) % (n))				

// Round up to the nearest multiple of n
#define ROUND_UP(a, n)	\
  (ROUND_DOWN((a) + (n) - 1, (n)))	


#endif // End of __MIMOSA_BITS_H;
