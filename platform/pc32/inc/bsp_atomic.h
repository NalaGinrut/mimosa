#ifndef	__MIMOSA_BSP_ATOMIC_H
#define __MIMOSA_BSP_ATOMIC_H
/*	
 *  Copyright (C) 2010-2012  
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
#include <bsp/bsp_types.h>

#define LOCK_PREFIX	" lock; "
#define NO_LOCK		""

// we need 'pause' instruction for hyper-threading CPU
#ifdef X86_HYPER_THREADING
#define X86_PAUSE "pause; \n\t"
#else
#define	X86_PAUSE ""
#endif // End of X86_HYPER_THREADING;

#define __X86_W    "w"
#define __X86_L    "l"
#ifdef 	__X86_64BIT__
#define __X86_Q    "q"
#endif

#include "cpu/xchg.h"
#include "cpu/btx.h"

#define __atomic_set_bit(p ,o)		__set_bit_op(p ,o ,LOCK_PREFIX)
#define __atomic_clear_bit(p ,o)	__clear_bit_op(p ,o ,LOCK_PREFIX)
#define __atomic_set_u8(p ,v)		__atomic_xchg_u8(p ,v)
#define __atomic_set_u16(p ,v)		__atomic_xchg_u16(p ,v)
#define __atomic_set_u32(p ,v)		__atomic_xchg_u32(p ,v)
#ifdef 	__X86_64BIT__
#define __atomic_set_u64(p ,v)		__atomic_xchg_u64(p ,v)
#endif // End of __X86_64BIT;

#undef X86_PAUSE
#undef __X86_W
#undef __X86_L

#ifdef 	__X86_64BIT__
#undef __X86_Q
#endif 

#endif // End of __MIMOSA_BSP_ATOMIC_H;
