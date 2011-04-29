#ifndef	__MIMOSA_BSP_ATOMIC_H
#define __MIMOSA_BSP_ATOMIC_H
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

#include <types.h>

typedef u32_t atomic_t; 

static inline void __atomic_set_bit(void *lock ,u32_t offset);
static inline void __atomic_clear_bit(void *lock ,u32_t offset);

static inline void __atomic_set_bit(void *lock ,u32_t offset)
{
  __asm__ __volatile__("1: lock bts%z0 %0 ,%1\n\t"
		       "jnc 1b"
		       :"=r" (lock)
		       :"0" (lock) ,"Ir" (offset)
		       :"cc"
		       );
}

static inline void __atomic_clear_bit(void *lock ,u32_t offset)
{
  __asm__ __volatile__("lock btr%z0 %0 ,%1"
		       :"=r" (lock)
		       :"0" (lock) ,"Ir" (offset)
		       :"cc"
		       );
}

#endif // End of __MIMOSA_BSP_ATOMIC_H;
