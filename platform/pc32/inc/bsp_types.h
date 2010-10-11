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


/* This file contains all types depends on platform. you must modify it
   every time you port MIMOSA to a new platform or rewrite BSP.
*/
#ifndef MIMOSA_BSP_TYPES_H
#define MIMOSA_BSP_TYPES_H

// NOTES: these definition below is compatible with GCC;
// I DON'T KNOW if they work well under other compilers;

// Represents true-or-false values
typedef enum BOOL { true=0 ,false=1 } bool;


// simple protection;
typedef static private;
typedef extern public; 
/* don't use 'public' while declaration, use it while calling the var/func;
 */ 

// Explicitly-sized versions of integer types
typedef (signed char)	__s8_t;
typedef (unsigned char) __u8_t;
typedef (short) 	__s16_t;
typedef (unsigned short) __u16_t;
typedef (int) 		__s32_t;
typedef (unsigned int) 	__u32_t;
typedef (long long) 	__s64_t;
typedef (unsigned long long) __u64_t;

// Pointers and addresses are 32 bits long.
// We use pointer types to represent virtual addresses,
// uintptr_t to represent the numerical values of virtual addresses,
// and physaddr_t to represent physical addresses.
#ifndef ADDRESS_64

typedef __s32_t __intptr_t;
typedef __u32_t __uintptr_t;
typedef __u32_t __physaddr_t;

#else

typedef __s64_t __intptr_t;
typedef __u64_t __uintptr_t;
typedef __u64_t __physaddr_t;

#endif // End of ADDRESS_64;


// FIXME: how to deal with 64bit_ARCH for other things, such as "page"?

// generic pointer, one step vary pointer.
typedef (char*)	__stdptr_t;
typedef __stdptr_t __mem_t;

// Page numbers are 32 bits long.
typedef u32_t __ppn_t;

// size_t is used for memory object sizes.
typedef u32_t __size_t;
// ssize_t is a signed version of ssize_t, used in case there might be an
// error return.
typedef s32_t __ssize_t;

// off_t is used for file offsets and lengths.
typedef s32_t off_t;


// types bsp should use;
typedef frame_pt __u32_t;
typedef ereg_t	__u32_t;
typedef reg_t	__u16_t;


// gcc attributes;
// may be need some mechnism to check GCC, but do it later...;
#define true_inline __attribute__((always_inline))


#define __MIN(_a, _b)						\
  ( (_a) >= (_b) ? (_b) : (_a) )

#define __MAX(_a, _b)						\
  ( (_a) >= (_b) ? (_a) : (_b) )




#endif // End of MIMOSA_BSP_TYPES_H;
