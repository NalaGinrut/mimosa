#ifndef __MIMOSA_X86_H
#define __MIMOSA_X86_H
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


#include <now/bsp_types.h>
#include <now/bsp_bits.h>

// function declaratioin:
static __inline__ ereg_t read_ebp() true_inline;

// get data operate;
static __inline__ __u8_t port_rb(__u32_t port) true_inline;
static __inline__ __u16_t port_rw(__u32_t port) true_inline;
static __inline__ __u32_t port_rl(__u32_t port) true_inline;

static __inline__ void port_rnb(__u32_t port,
				__gptr_t addr,
				__u32_t cnt) true_inline;

static __inline__ void port_rnw(__u32_t port,
				__gptr_t addr,
				__u32_t cnt) true_inline;

static __inline__ void port_rnl(__u32_t port,
				__gptr_t addr,
				__u32_t cnt) true_inline;


// output data operate;
static __inline__ void port_wb(__u32_t port ,__u8_t data) true_inline;
static __inline__ void port_ww(__u32_t port ,__u16_t data) true_inline;
static __inline__ void port_wl(__u32_t port ,__u32_t data) true_inline;
static __inline__ void port_wnb(__u32_t port,
				__cptr_t addr,
				__u32_t cnt) true_inline;
static __inline__ void port_wnw(__u32_t port,
				__cptr_t addr,
				__u32_t cnt) true_inline;
static __inline__ void port_wnl(__u32_t port,
				__cptr_t addr,
				__u32_t cnt) true_inline;



// you'd better explicitly cast while calling "port_w" directly
#define __port_write(port ,data)			\
  do{ 							\
    __asm__ __volatile__("out%z0 %0 ,%w1"		\
			 :				\
			 :"a" (data) ,"d" (port)	\
			 );				\
  }while(0);

#define __port_nwrite(cmd)					\
  do{								\
    __asm__ __volatile__("cld\n\t"				\
			 "repne\n\t"				\
			 #cmd					\
			 :"=S" (addr) ,"=c" (cnt)		\
			 :"d" (port) ,"0" (addr) ,"1" (cnt)	\
			 :"cc"					\
			 );					\
  }while(0);


#define __port_read(port ,data)		\
  do{					\
  __asm__ __volatile__("in%z0 %w1 ,%0"	\
		       :"=a" (data)	\
		       :"d" (port)	\
		       );		\
  }while(0);

#define __port_nread(cmd)					\
  do{								\
    __asm__ __volatile__("cld\n\t"				\
			 "repne\n\t"				\
			 #cmd					\
			 :"=D" (addr) ,"=c" (cnt)		\
			 :"d" (port) ,"0" (addr) ,"1" (cnt)	\
			 :"memory" ,"cc"			\
			 );					\
  }while(0);

/* Actually we don't need these "cast". I wrote them in case
 * some Muggle who can't "cast" ask why thay are similar. :-)
 */
static __inline__ __u8_t port_rb(__u32_t port)
{
  __u8_t data;
  __port_read(port ,(__u8_t)data);
  
  return data;
}

static __inline__ __u16_t port_rw(__u32_t port)
{
  __u16_t data;
  __port_read(port ,(__u16_t)data);
  
  return data;
}

static __inline__ __u32_t port_rl(__u32_t port)
{
  __u32_t data;
  __port_read(port ,(__u32_t)data);
  
  return data;
}


static __inline__ void port_rnb(__u32_t port ,__gptr_t addr ,__u32_t cnt)
{
  __port_nread(insb);
}

static __inline__ void port_rnw(__u32_t port ,__gptr_t addr ,__u32_t cnt)
{
  __port_nread(insw);
}

static __inline__ void port_rnl(__u32_t port ,__gptr_t addr ,__u32_t cnt)
{
  __port_nread(insl);
}


static __inline__ ereg_t read_ebp()
{
  ereg_t value;
  __asm__ __volatile__ ("mov%z0 %%ebp ,%0"
			:"=r" (value)
			);
  return value;
}



static __inline__ void port_wb(__u32_t port ,__u8_t data)
{
  __port_write(port ,(__u8_t)data);
}

static __inline__ void port_ww(__u32_t port ,__u16_t data)
{
  __port_write(port ,(__u16_t)data);
}

static __inline__ void port_wl(__u32_t port ,__u32_t data)
{
  __port_write(port ,(__u32_t)data);
}

static __inline__ void port_wnb(__u32_t port,
				__cptr_t addr,
				__u32_t cnt)
{
  __port_nwrite(outsb);
}

static __inline__ void port_wnw(__u32_t port,
				__cptr addr,
				__u32_t cnt)
{
  __port_nwrite(outsw);
}

static __inline__ void port_wnl(__u32_t port,
				__cptr_t addr,
				__u32_t cnt)
{
  __port_nwrite(outsl);
}

 


//----------------------------------
// definition for 

//---------------------------------
// definition for EFLAGS:

// Control Flag:
#define EF_DF	_B(10)

// Status Flag:
#define EF_OF	_B(11)
#define EF_CF	_B(0)
#define EF_PF	_B(2)
#define EF_AF	_B(4)
#define EF_ZF	_B(6)
#define EF_SF	_B(7)

// System Flag:
#define EF_TF	_B(8)
#define EF_IF	_B(9)
#define EF_IOPL	_S(0x3,12)
#define EF_NT	_B(14)
#define EF_RF	_B(16)
#define EF_VM	_B(17)
#define EF_AC	_B(18)
#define EF_VIF	_B(19)
#define EF_VIP	_B(20)
#define EF_ID	_B(21)

// undefined bit for EFLAGS:
#define EF_N1	_B(1)
#define EF_N2	_B(3)
#define EF_N3	_B(5)
#define	EF_N4	_B(15)
#define EF_N6	_B(17)

// the init value of EFLAGS:
#define EF_INIT	0x00000002UL

// End of EFLAGS defination;
//---------------------------





#endif // End of __MIMOSA_X86_H;
