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

#ifndef MIMOSA_BITS_H
#define MIMOSA_BITS_H

#include "inc/types.h"


// FIXME: Maybe we need 8/16/64 bits' CHECK_FLAG?
// Note: CHK_FLAG is used during if/while judgement, DO NOT use "do{}while(0)";
#define CHK_FLAG(des ,f)	\
  ( (reg) & (f) )

#define SET_FLAG(des ,f)	\
  ( (reg) |= (f) );

#define CLR_FLAG(des ,f)	\
  ( (reg) &= (f) );


#ifdef MIMOSA_ADDRESS_64
#define FLAG_BASE	0xFFFFFFFFFFFFFFFFuL // make sure unsigned long!!!;
#else
#define FLAG_BASE	0xFFFFFFFFuL // make sure unsigned long!!!;
#endif // End of !MIMOSA_ADDRESS_64;

/* use FLAG_FIX for FLAG value set. E.g: FLAG_FIX(3 ,5 ,32) stands for 
   "this flag is 3bits length and start from 5th bit of 32bits integer";
*/
#define FLAG_FIX(len ,start ,bit)			\
  ( ((FLAG_BASE)>>((bit)-start))<<(len) )

#define F_FIX32(len ,start)	FLAG_FIX(len ,start ,32)
#define F_FIX64(len ,start)	FLAG_FIX(len ,start ,64)


#endif // End of MIMOSA_BITS_H;
