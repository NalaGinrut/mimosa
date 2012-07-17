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

#define LOCK_PREFIX " lock; "

typedef u32_t atomic_t; 

static inline void __atomic_set_bit(void *l ,u32_t offset);
static inline void __atomic_clear_bit(void *l ,u32_t offset);

static inline void __atomic_set_bit(void *l ,u32_t offset)
{
  __asm__ __volatile__("1: " LOCK_PREFIX "bts%z0 %0 ,%1\n\t"
  		       "jnc 1b"
		       :"=r" (l)
		       :"0" (l) ,"Ir" (offset)
		       :"cc"
		       );
}

static inline void __atomic_clear_bit(void *l ,u32_t offset)
{
  __asm__ __volatile__(LOCK_PREFIX "btr%z0 %0 ,%1"
		       :"=r" (l)
		       :"0" (l) ,"Ir" (offset)
		       :"cc"
		       );
}

#endif // End of __MIMOSA_BSP_ATOMIC_H;
