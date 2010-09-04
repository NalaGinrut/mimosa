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
#ifndef MIMOSA_TYPES_H
#define MIMOSA_TYPES_H

#include "now/bsp_types.h"

#ifndef NULL
#define NULL ((void*) 0)
#endif

// Represents true-or-false values
typedef __bool bool;

// Explicitly-sized versions of integer types
typedef __s8_t s8_t;
typedef __u8_t u8_t;
typedef __s16_t s16_t;
typedef __u16_t u16_t;
typedef __s32_t s32_t;
typedef __u32_t u32_t;
typedef __s64_t s64_t;
typedef __u64_t u64_t;

// generic pointer, one step vary pointer
typedef __stdptr_t stdptr_t;

typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;
typedef __physaddr_t physaddr_t;

// FIXME: how to deal with 64bit_ARCH for other things, such as "page"?

// Page numbers are 32 bits long(default). We haven't consider others yet.
typedef __ppn_t ppn_t;

// size_t is used for memory object sizes.
typedef __size_t size_t;
// ssize_t is a signed version of ssize_t, used in case there might be an
// error return.
typedef __ssize_t ssize_t;

// off_t is used for file offsets and lengths.
typedef __off_t off_t;


#define MIN __MIN

#define MAX __MAX


/* These two useful MACRO must be familar to you (IF NOT, GO BACK TO BASIC HACKING!), 
 * and as I said, I won't implement any of my code out of the ANSI C standard.
 * So here is a ANSI C version.
 */
#define container_of(elem_addr ,struct_type ,member)	\
    ( (struct_type*)((stdptr_t)(elem_addr) - offsetof(struct_type ,member)) )

#define offsetof(type ,member)	\
  (off_t)(&((type*)0)->member)	


#endif // End of MIMOSA_TYPES_H;
