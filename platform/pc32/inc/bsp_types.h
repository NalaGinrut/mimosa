#ifndef __MIMOSA_BSP_TYPES_H
#define __MIMOSA_BSP_TYPES_H
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

// NOTES: these definition below is compatible with GCC;
// I DON'T KNOW if they work well under other compilers;

#ifndef __ASSEMBLER__
// Represents true-or-false values
typedef enum BOOL { true=0 ,false=1 } __bool;

// Explicitly-sized versions of integer types
typedef signed char	__s8_t;
typedef unsigned char	__u8_t;
typedef short	 	__s16_t;
typedef unsigned short	__u16_t;
typedef int 		__s32_t;
typedef unsigned int 	__u32_t;
typedef long long 	__s64_t;
typedef unsigned long long __u64_t;

// CPU word long ,pc32 is 32bit
typedef __u32_t __longword;

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
typedef __u8_t *__bptr;
typedef __u16_t *__wptr;
typedef __u32_t *__lptr;

// ptr to constant
typedef const __u8_t *__cb_p;
typedef const __u16_t *__cw_p;
typedef const __u32_t *__cl_p;

// constant ptr
typedef __u8_t *const __b_cp;
typedef __u16_t *const __w_cp;
typedef __u32_t *const __l_cp;

typedef void* __gptr_t;
typedef const void *__cptr_t;
typedef char*	__stdptr_t;
typedef __stdptr_t __mem_t;

// Page numbers are 32 bits long.
typedef __u32_t __ppn_t;

// size_t is used for memory object sizes.
typedef __u32_t __size_t;
// ssize_t is a signed version of ssize_t, used in case there might be an
// error return.
typedef __s32_t __ssize_t;

// off_t is used for file offsets and lengths.
typedef __s32_t __off_t;


// types bsp should use;
typedef __u32_t frame_pt;
typedef __u32_t ereg_t;
typedef __u16_t reg_t;


// gcc attributes;
// may be need some mechnism to check GCC, but do it later...;
#define true_inline __attribute__((always_inline))


#define __MIN(_a, _b)						\
  ( (_a) >= (_b) ? (_b) : (_a) )

#define __MAX(_a, _b)						\
  ( (_a) >= (_b) ? (_a) : (_b) )

// kernel entry type
typedef void (*entry_t)(void);

#endif // !__ASSEMBLER__

#endif // End of __MIMOSA_BSP_TYPES_H;
