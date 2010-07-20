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

#ifndef MIMOSA_I386_H
#define MIMOSA_I386_H

#include "now/bsp_types.h"

// function declaratioin:
static __inline__ ereg_t read_ebp();


// function body:
static __inline__ ereg_t read_ebp()
{
  ereg_t value;
  __asm__ __volatile__ ("movw %%ebp ,%0"
			:
			:"=r" value
			:
			)
    return value;
}


//---------------------------------
// definition for EFLAGS:

// Control Flag:
#define EF_DF	((0x01)<<10)

// Status Flag:
#define EF_OF	((0x01)<<11)
#define EF_CF	(0x01)
#define EF_PF	((0x01)<<2)
#define EF_AF	((0x01)<<4)
#define EF_ZF	((0x01)<<6)
#define EF_SF	((0x01)<<7)

// System Flag:
#define EF_TF	((0x01)<<8)
#define EF_IF	((0x01)<<9)
#define EF_IOPL	((0x03)<<12)
#define EF_NT	((0x01)<<14)
#define EF_RF	((0x01)<<16)
#define EF_VM	((0x01)<<17)
#define EF_AC	((0x01)<<18)
#define EF_VIF	((0x01)<<19)
#define EF_VIP	((0x01)<<20)
#define EF_ID	((0x01)<<21)

// undefined bit for EFLAGS:
#define EF_N1	((0x01)<<1)
#define EF_N2	3
#define EF_N3	5
#define	EF_N4	15
#define EF_N6	17

// the init value of EFLAGS:
#define EF_INIT	0x00000002UL

// End of EFLAGS defination;
//---------------------------





#endif // End of MIMOSA_I386_H;
