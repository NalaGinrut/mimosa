#ifndef	__MIMOSA_I386_H
#define __MIMOSA_I386_H
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


#include <now/bsp_bits.h>

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



#endif // End of __MIMOSA_I386_H;
