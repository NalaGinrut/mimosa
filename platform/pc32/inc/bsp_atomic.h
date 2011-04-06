#ifndef	__PC32_BSP_ATOMIC_H
#define __PC32_BSP_ATOMIC_H
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


#include <types.h>

static inline void __atomic_set_bit(void *lock ,u32_t offset);
static inline void __atomic_clear_bit(void *lock ,u32_t offset);

static inline void __atomic_set_bit(void *lock ,u32_t offset)
{
  __asm__ __volatile__("1: lock bts%z0 %0 ,%1\n\t"
		       "jnc 1b"
		       :"=r" (lock)
		       :"Ir" (offset)
		       :"cc"
		       );
}

static inline void __atomic_clear_bit(void *lock ,u32_t offset)
{
  __asm__ __volatile__("lock btr%z0 %0 ,%1"
		       :"=r" (lock)
		       :"m" (lock) ,"Ir" (offset)
		       :"cc"
		       );
}

#endif // End of __PC32_BSP_ATOMIC_H;
