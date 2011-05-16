#ifndef __MIMOSA_TYPES_H
#define __MIMOSA_TYPES_H
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

#ifndef __ASSEMBLER__

#include <bsp/bsp_types.h>

#define no_return __no_return
#define true_inline __true_inline

#ifndef NULL
#define NULL ((void*) 0)
#endif

// Represents true-or-false values
typedef __bool bool;

// CPU word long
typedef __longword longword;

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
typedef __bptr bptr;
typedef __wptr wptr;
typedef __lptr lptr;

// ptr to constant
typedef __cb_p cb_p;
typedef __cw_p cw_p;
typedef __cl_p cl_p;

// constant ptr
typedef __b_cp b_cp;
typedef __w_cp w_cp;
typedef __l_cp l_cp;

typedef __gptr_t gptr_t;
typedef __cptr_t cptr_t;




typedef __stdptr_t stdptr_t;

typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;
typedef __physaddr_t physaddr_t;

// FIXME: how to deal with 64bit_ARCH for other things, such as "page"?

/* paging type shouldn't be visible to kernel, use them in BSP only; 
// Page numbers are 32 bits long(default). We haven't consider others yet.
typedef __ppn_t ppn_t;
typedef __pte_t pte_t;
typedef __pte_tp pte_tp;
typedef __pde_t pde_t;
typedef __pde_tp pde_tp;
typedef __laddr_t laddr_t;
typedef __laddr_tp laddr_tp;
*/

// size_t is used for memory object sizes.
typedef __size_t size_t;
// ssize_t is a signed version of ssize_t, used in case there might be an
// error return.
typedef __ssize_t ssize_t;

// off_t is used for file offsets and lengths.
typedef __off_t off_t;


#define MIN(_a ,_b) __MIN(_a ,_b)

#define MAX(_a ,_b) __MAX(_a ,_b)


/* These two useful MACRO must be familar to you (IF NOT, GO BACK TO BASIC HACKING!), 
 * and as I said, I won't implement any of my code out of the ANSI C standard.
 * So here is a ANSI C version.
 */
#define container_of(elem_addr ,struct_type ,member)	\
    ( (struct_type*)((stdptr_t)(elem_addr) - offsetof(struct_type ,member)) )

#define offsetof(type ,member)	\
  (off_t)(&((type*)0)->member)	

#endif // !__ASSEMBLER__

#endif // End of __MIMOSA_TYPES_H;
