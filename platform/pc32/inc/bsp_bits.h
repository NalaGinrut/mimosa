#ifndef __MIMOSA_BSP_BITS_H
#define __MIMOSA_BSP_BITS_H
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


// This file used for handling bits operation;


#include "bsp_types.h"


#define __BIT	(0x01)
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
#define FLAG_FIX	__FIX32

// Round up/down;
// Never use GCC extension! Prefer slow!

/* don't worry about mod/div speed ,I know roundup=rounddown(x+n-1,n),
 * but this form is simpler in C, for '/' op in C has rounddown feature,
 * and mod/div is the same instruction under X86;
 */
#define ROUND_UP(x ,n)	  	\
  ( ((x)+(n)-1) / (n) )

#define ROUND_DOWN(x ,n)	\
  ( (x)-(x)%(n) )

#endif // End of __MIMOSA_BITS_H;
