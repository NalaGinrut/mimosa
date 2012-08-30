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
#endif

#define __X86_W    "w"
#define __X86_L    "l"
#ifdef 	__X86_64BIT__
#define __X86_Q    "q"
#endif

static inline void __atomic_set_bit(void *p ,__u32_t offset);
static inline void __atomic_clear_bit(void *p ,__u32_t offset);
static inline void* __atomic_cmpxchg(void *p ,__u32_t old ,__u32_t new); 
#define __atomic_set_u8(p ,v)	__atomic_xchg_u8(p ,v)
#define __atomic_set_u16(p ,v)	__atomic_xchg_u16(p ,v)
#define __atomic_set_u32(p ,v)	__atomic_xchg_u32(p ,v)
#ifdef 	__X86_64BIT__
#define __atomic_set_u64(p ,v)	__atomic_xchg_u64(p ,v)
#endif // End of __X86_64BIT;

static inline u8_t __xchg_u8(u8_t* p ,u8_t v)
{
  u8_t ret = v;

  __xchg_op_u8(p ,ret ,X86_XCHG_OP ,NON_LOCK);

  return ret;
}

static inline u8_t __atomic_xchg_u8(u8_t* p ,u8_t v)
{
  u8_t ret = v;

  __xchg_op_u8(p ,ret ,X86_XCHG_OP ,LOCK_PREFIX);

  return ret;
}

static inline __u16_t __xchg_u16(__u16_t* p ,__u16_t v)
{
  __u16_t ret = v;

  __xchg_op(p ,ret ,X86_XCHG_OP ,__X86_W ,NON_LOCK);

  return ret;
}

static inline __u16_t __atomic_xchg_u16(__u16_t* p ,__u16_t v)
{
  __u16_t ret = v;

  __xchg_op(p ,ret ,X86_XCHG_OP ,__X86_W ,LOCK_PREFIX);

  return ret;
}

static inline __u32_t __xchg_u32(__u32_t* p ,__u32_t v)
{
  __u32_t ret = v;

  __xchg_op(p ,ret ,X86_XCHG_OP ,__X86_L ,NON_LOCK);

  return ret;
}

static inline __u32_t __atomic_xchg_u32(__u32_t* p ,__u32_t v)
{
  __u32_t ret = v;
  
  __xchg_op(p ,ret ,X86_XCHG_OP ,__X86_L ,LOCK_PREFIX);

  return ret;
}

#ifdef 	__X86_64BIT__
static inline __u64_t __xchg_u64(__u64_t* p ,__u64_t v)
{
  __u64_t ret = v;

  __xchg_op(p ,ret ,X86_XCHG_OP ,__X86_Q ,NON_LOCK);

  return ret;
}

static inline __u64_t __atomic_xchg_u64(__u64_t* p ,__u64_t v)
{
  __u64_t ret = v;
  
  __xchg_op(p ,ret ,X86_XCHG_OP ,__X86_Q ,LOCK_PREFIX);

  return ret;
}
#endif // End of __X86_64BIT__;

/* In 64-bit mode, r/m8 can not be encoded to access the following
 * byte registers if a REX prefix is used: AH, BH, CH, DH.
 * So we have to use "+q" for 8bit xchg. */
#define __xchg_op_u8(ptr, arg, op, size ,lock)			\
  do{								\
  __asm__ __volatile__ (lock #op "b %b0 ,%1\n"			\
			: "+q" (arg) ,"+m" (*(ptr))		\
			: : "memory" ,"cc");			\
  while(0);

#define __xchg_op(ptr, arg, op, size ,lock)			\
  do{								\
  __asm__ __volatile__ (lock #op #size " %" #size "0 ,%1\n"	\
			: "+r" (arg) ,"+m" (*(ptr))		\
			: : "memory" ,"cc");			\
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

#undef __X86_W
#undef __X86_L

#ifdef 	__X86_64BIT__
#undef __X86_Q
#endif 

#endif // End of __MIMOSA_BSP_ATOMIC_H;
