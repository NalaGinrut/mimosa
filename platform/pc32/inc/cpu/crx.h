#ifndef __MIMOSA_CRN_H
#define __MIMOSA_CRN_H
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

#include "bsp_bits.h"
#include "bsp_types.h"

/* NOTE: These control register definitions is only for 32-bits;
 * And all Reserved bits must be 0, or may cause Gerneral Protection Fault;
 */

// CR0 definition;
#define CR0_PM	_B(0)	// Protection Mode;
#define CR0_MP	_B(1)	// Monitor Coprocessor;
#define CR0_EM	_B(2)	// Emulation;
#define CR0_TS	_B(3)	// Task Switched;
#define CR0_ET	_B(4)	// Extension Type;
#define CR0_NE	_B(5)	// Numeric Error;
#define CR0_WP	_B(16)	// Write Protect;
#define CR0_AM	_B(18)	// Alignment Mask;
#define CR0_NW	_B(29)	// Not Write-Through;
#define CR0_CD	_B(30)	// Cache Disable;
#define CR0_PG	_B(31)	// Paging;

// CR1 definition;
/* CR1 is Reserved, we don't have any definition;
 */

// CR2 definition;
/* CR2 is used for Page-Fault Linear Address;
 */

// CR3 definition;
#define CR3_PWT		_B(3) 	// Page-Level Write-Through;
#define CR3_PCD		_B(4)	// Page-Level Cache Disable;
/* Page-Directory Base under 32-bits mode is 20-bits from 12th-bit;
   While we want to write a PDB, use CR3_PDB_W to fix this addr, if the addr
   is longer than 20-bits, this MACRO will round down;
 */ 
#define CR3_PDB_W(addr)	(((addr)<<12) & FLAG_FIX(20 ,12))
#define CR3_PDB_R	FLAG_FIX(20 ,12)


// CR4 definition;
#define CR4_VME		_B(0)	// Virtual-8086 Mode Extensions;
#define CR4_PVI		_B(1)	// Protected-Mode Virtual Interrupts;
#define CR4_TSD		_B(2)	// Time Stamp Disable;
#define CR4_DE		_B(3)	// Debugging Extensions;
#define CR4_PSE		_B(4)	// Page Size Extensions;
#define CR4_PAE		_B(5)	// Physical Address Extension;
#define CR4_MCE		_B(6)	// Machine-Check Enable;
#define CR4_PGE		_B(7)	// Page Global Enable;
#define CR4_PCE		_B(8)	// Performance-Monitoring Counter Enable;
#define CR4_OSFXSR	_B(9)	// OS Support for FXSAVE & FXRSTOR;
#define CR4_OSXMMEXCPT	_B(10)	// OS Support for Unmasked SIMD Floating-point Exceptions;
#define CR4_VMXE	_B(13)	// VMX-Enable Bit;
#define CR4_SMXE	_B(14)	// SMX-Enable Bit;
#define CR4_PCIDE	_B(17)	// PCI D-Enable Bit;
#define CR4_OSXSAVE	_B(18)	// XSAVE and Processor Extended States-Enable Bit;

// CR8 definition;
#define CR8_TPL_W(mode)	((mode) & FLAG_FIX(4 ,0))
#define CR8_TPL_R	FLAG_FIX(4 ,0)



// DON'T USE THIS PROCs DIRECTLY!!!
#define __crx_set(crx ,flag)				\
  do{							\
    asm volatile("movl %%eax ,%%"#crx			\
		 :					\
		 :"a" (flag)				\
		 );					\
  }while(0);

#define __crx_get(crx)					\
  do{							\
    asm volatile("movl %%"#crx" ,%%eax"			\
		 :"=a" (ret)				\
		 );					\
  }while(0);
//-----------------------------------

//------CRX set curried function~
#define cr0_set(flags) __crx_set(cr0 ,flags)
#define cr1_set(flags) __crx_set(cr1 ,flags)
#define cr2_set(flags) __crx_set(cr2 ,flags)
#define cr3_set(flags) __crx_set(cr3 ,flags)
#define cr4_set(flags) __crx_set(cr4 ,flags)
//---------------------------------


//-----CRX get curried decl&defn
// IT'S JUST FOR DECL&DEFN! NEVER USE THEM IN YOUR CODE!!
#define decl_crx_get(crx)					\
  static inline __u32_t crx##_get() true_inline;

#define defn_crx_get(crx)					\
  static inline __u32_t  crx##_get()				\
  {								\
    __u32_t ret = 0;						\
    __crx_get(crx);						\
    return ret;
  }

decl_crx_get(cr0);
defn_crx_get(cr0);

decl_crx_get(cr1);
defn_crx_get(cr1);

decl_crx_get(cr2);
defn_crx_get(cr2);

decl_crx_get(cr3);
defn_crx_get(cr3);

decl_crx_get(cr4);
defn_crx_get(cr4);
//------------------------


#define decl_crx_chk(crx)					\
  static inline __u32_t crx##_chk(__u32_t flags) true_inline;

#define defn_crx_chk(crx)					\
  static inline __u32_t  crx##_chk(__u32_t flags)		\
  {								\
    __u32_t ret = 0;						\
    __crx_get(crx);						\
    return ( ret & flags );
  }

decl_crx_chk(cr0);
defn_crx_chk(cr0);

decl_crx_chk(cr1);
defn_crx_chk(cr1);

decl_crx_chk(cr2);
defn_crx_chk(cr2);

decl_crx_chk(cr3);
defn_crx_chk(cr3);

decl_crx_chk(cr4);
defn_crx_chk(cr4);
//-------------------

#endif // End of __MIMOSA_CRN_H;










