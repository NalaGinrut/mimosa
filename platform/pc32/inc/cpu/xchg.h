#ifndef	__MIMOSA_X86_CPU_XCHG_H__
#define __MIMOSA_X86_CPU_XCHG_H__
/*	
 *  Copyright (C) 2012  
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

#include "../bsp_types.h"

/* In 64-bit mode, r/m8 can not be encoded to access the following
 * byte registers if a REX prefix is used: AH, BH, CH, DH.
 * So we have to use "+q" for 8bit xchg. */
#define __xchg_op_u8(ptr, arg, op ,lock)			\
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

static inline void* __atomic_cmpxchg(void *p ,__u32_t old ,__u32_t new); 
static inline __u8_t __xchg_u8(__u8_t* p ,__u8_t v);
static inline __u8_t __atomic_xchg_u8(__u8_t* p ,__u8_t v);
static inline __u16_t __xchg_u16(__u16_t* p ,__u16_t v);
static inline __u16_t __atomic_xchg_u16(__u16_t* p ,__u16_t v);
static inline __u32_t __xchg_u32(__u32_t* p ,__u32_t v);
static inline __u32_t __atomic_xchg_u32(__u32_t* p ,__u32_t v);
static inline __u64_t __xchg_u64(__u64_t* p ,__u64_t v);
static inline __u64_t __atomic_xchg_u64(__u64_t* p ,__u64_t v);

static inline __u8_t __xchg_u8(u8_t* p ,u8_t v)
{
  __u8_t ret = v;

  __xchg_op_u8(p ,ret ,X86_XCHG_OP ,NON_LOCK);

  return ret;
}

static inline __u8_t __atomic_xchg_u8(u8_t* p ,u8_t v)
{
  __u8_t ret = v;

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

#endif // End of __MIMOSA_X86_CPU_XCHG_H__;
