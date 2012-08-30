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

#include <osconfig.h>
#include <bsp/bsp_types.h>

#define LOCK_PREFIX	" lock; "
#define NO_LOCK		""

// we need 'pause' instruction for hyper-threading CPU
#ifdef X86_HYPER_THREADING
#define X86_PAUSE "pause; \n\t"
#endif

#define __X86_CASE_B    1
#define __X86_CASE_W    2
#define __X86_CASE_L    4
#ifdef CONFIG_64BIT
#define __X86_CASE_Q    8
#else
#define __X86_CASE_Q    -1              /* sizeof will never return -1 */
#endif

static inline void __atomic_set_bit(void *p ,__u32_t offset);
static inline void __atomic_clear_bit(void *p ,__u32_t offset);
static inline void* __atomic_cmpxchg(void *p ,__u32_t old ,__u32_t new); 
#define __atomic_set_u32(p ,v)	__xchg_op

#define __port_read(port ,data)		\
  do{					\
  __asm__ __volatile__("in%z0 %w1 ,%0"	\
		       :"=a" (data)	\
		       :"d" (port)	\
		       );		\
  }while(0);

static inline u8_t __xchg_u8(u8_t* p ,u8_t v)
{
  u8_t ret = v;

  __xchg_op(p ,ret ,X86_XCHG_OP ,NON_LOCK);

  return ret;
}

static inline u8_t __atomic_xchg_u8(u8_t* p ,u8_t v)
{
  u8_t ret = v;

  __xchg_op(p ,ret ,X86_XCHG_OP ,LOCK_PREFIX);

  return ret;
}

// FIXME: modify it to data-oriented mechanism
#define __xchg_op(ptr, arg, op, lock)				\
  do{								\
  int size = sizeof(*(ptr));					\
    switch (size) {						\
    case __X86_CASE_B:						\
      __asm__ __volatile__ (lock #op "b %b0, %1\n"		\
			    : "+q" (arg) ,"+m" (*(ptr))		\
			    : : "memory" ,"cc");		\
      break;							\
    case __X86_CASE_W:						\
      __asm__ __volatile__ (lock #op "w %w0, %1\n"		\
			    : "+r" (arg) ,"+m" (*(ptr))	\
			    : : "memory" ,"cc");		\
      break;							\
    case __X86_CASE_L:						\
      __asm__ __volatile__ (lock #op "l %0, %1\n"		\
			    : "+r" (arg) ,"+m" (*(ptr))	\
			    : : "memory" ,"cc");		\
      break;							\
    case __X86_CASE_Q:						\
      __asm__ __volatile__ (lock #op "q %q0, %1\n"		\
			    : "+r" (arg) ,"+m" (*(ptr))	\
			    : : "memory" ,"cc");		\
      break;							\
    default:							\
      panic("error size: %u\n" ,size);				\
    }								\
  }while(0);

static inline void __atomic_set_bit(void *ptr ,u32_t offset)
{
  __asm__ __volatile__("1: " LOCK_PREFIX "bts%z0 %0 ,%1\n\t"
  		       "jnc 2f\n\t"
#ifdef X86_PAUSE
		       X86_PAUSE
#endif
		       "jmp 1b\n\t"
		       "2: ret"
		       :"=r" (ptr)
		       :"0" (ptr) ,"Ir" (offset)
		       :"cc"
		       );
}

static inline void __atomic_clear_bit(void *ptr ,u32_t offset)
{
  __asm__ __volatile__(LOCK_PREFIX "btr%z0 %0 ,%1"
		       :"=r" (ptr)
		       :"0" (ptr) ,"Ir" (offset)
		       :"cc"
		       );
}

static inline void* __atomic_cmpxchg(void *ptr ,__u32_t old ,__u32_t new)
{
  volatile u32_t *__ptr = (volatile u32_t *)(ptr);   
  u32_t __ret;                                    
  __asm__ __volatile__( LOCK_PREFIX "cmpxchgl %2,%1"           
		: "=a" (__ret) ,"+m" (*__ptr)                
		: "r" (new) ,"0" (old)
		: "memory" );
  
  return __ret;                                         
}


#ifdef X86_PAUSE
#undef X86_PAUSE
#endif

#endif // End of __MIMOSA_BSP_ATOMIC_H;
