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

// Pointers and addresses are 32 bits long.
// We use pointer types to represent virtual addresses,
// uintptr_t to represent the numerical values of virtual addresses,
// and physaddr_t to represent physical addresses.
#ifndef ADDRESS_64

typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;
typedef __physaddr_t physaddr_t;

#else

typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;
typedef __physaddr_t physaddr_t;

#endif // End of ADDRESS_64;

// FIXME: how to deal with 64bit_ARCH for other things, such as "page"?

// Page numbers are 32 bits long.
typedef u32_t ppn_t;

// size_t is used for memory object sizes.
typedef u32_t size_t;
// ssize_t is a signed version of ssize_t, used in case there might be an
// error return.
typedef s32_t ssize_t;

// off_t is used for file offsets and lengths.
typedef s32_t off_t;


// FIXME: Can we trash down the GCC_extension: "sizeof" ??
// Efficient min and max operations
#define MIN(_a, _b)						\
({								\
	typeof(_a) __a = (_a);					\
	typeof(_b) __b = (_b);					\
	__a <= __b ? __a : __b;					\
})
#define MAX(_a, _b)						\
({								\
	typeof(_a) __a = (_a);					\
	typeof(_b) __b = (_b);					\
	__a >= __b ? __a : __b;					\
})

// Rounding operations (efficient when n is a power of 2)
// Round down to the nearest multiple of n
#define ROUNDDOWN(a, n)						\
({								\
	u32_t __a = (u32_t) (a);				\
	(typeof(a)) (__a - __a % (n));				\
})
// Round up to the nearest multiple of n
#define ROUNDUP(a, n)						\
({								\
	u32_t __n = (u32_t) (n);				\
	(typeof(a)) (ROUNDDOWN((u32_t) (a) + __n - 1, __n));	\
})

// Return the offset of 'member' relative to the beginning of a struct type
#define offsetof(type, member)  ((size_t) (&((type*)0)->member))

#endif // End of MIMOSA_TYPES_H;
