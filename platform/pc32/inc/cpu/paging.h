#ifndef __MIMOSA_PC32_PAGING_H
#define __MIMOSA_PC32_PAGING_H
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

#ifndef __ASSEMBLER__

#include <bsp/bsp_types.h>
#include <bsp/bsp_bits.h>
#include "crx.h"

#ifdef __BIT32_PAGING__


#ifdef __BIT32_PAGING_NO_PSE__
typedef union Linear_Address
{
  struct
  {
  offset	:12;
  table		:10;
  dir		:10;
  };

  __u32_t value;
}laddr_t ,laddr_tp *;

//--- PDE definition;
#define PDE_PRESENT	_B(0)
#define PDE_READ	_B(1)
#define PDE_USER	_B(2)
#define PDE_WRITE_TH	_B(3)
#define PDE_CACHE_D	_B(4)
#define PDE_ACCESSED	_B(5)
#define PDE_PAGE4MB	_B(6)
#define PDE_GLOBAL	_B(7)
#define PDE_PT_ADDR	FLAG_FIX(20 ,12)
typedef union Page_Dir_Entry
{
  struct 
  {
  p	:1; // 1 for present;
  r	:1; // 1 for read/write ,0 for read-only; 
  u	:1; // 1 for user ,0 for supervisor;
  w	:1; // 1 for write-through ,0 for write back;
  cd	:1; // 1 for cache Disable ,0 cache will be cached;
  a	:1; // 1 for have been accessed(since last check) ,0 for no;
  undef	:1; // always 0;
  s	:1; // 1 for 4MB page size ,0 for 4KB page size;
  g	:1; // 1 for translation is global if CR4.PGE=1 ,otherwise Ignored;
  igno	:3; // Ignored;
  pt_ad	:20;// Page Table 4KB aligned address;
  };
  
  __u32_t value;
}pde_t ,pde_tp *; // Page Directory Entry;

//--- PTE definition;
#define PTE_PRESENT	_B(0)
#define PTE_READ	_B(1)
#define PTE_USER	_B(2)
#define PTE_WRITE_TH	_B(3)
#define PTE_CACHE_D	_B(4)
#define PTE_ACCESSED	_B(5)
#define PTE_DIRTY	_B(6)
#define PTE_PAT		_B(7)
#define PTE_GLOBAL     	_B(8)
#define PTE_ADDR	FLAG_FIX(20 ,12)
typedef union Page_Table_Entry
{
  struct 
  {
  p	:1; // 1 for present;
  r	:1; // 1 for read/write ,0 for read-only; 
  u	:1; // 1 for user ,0 for supervisor;
  w	:1; // 1 for write-through ,0 for write back;
  cd	:1; // 1 for Cache disable ,0 cache will be cached;
  a	:1; // 1 for have been accessed(since last check) ,0 for no;
  d	:1; /* 1 for dirty ,0 for not;
	     * If the Dirty flag ('D') is set, then the page has been 
	     * written to. This flag is not updated by the CPU, and once 
	     * set will not unset itself.
	     */
  pat	:1; // 1 for pat(if supported) , otherwise ignored;
  g	:1; /* 1 for translation is global if CR4.PGE=1 ,otherwise Ignored;
	     * The Global, or 'G' above, flag, if set, prevents the TLB  
	     * from updating the address in it's cache if CR3 is reset. 
	     * Note, that the page global enable bit in CR4 must be set 
	     * to enable this feature.
	     */
  igno	:3; // ignored;
  pa	:20 // Page Frame 4KB aligned address;
  };

  __u32_t value;
}pte_t ,pte_tp *;


#else //__BIT32_PAGING_PAE__

typedef union Linear_Address
{
  struct 
  {
  offset	:22;
  dir		:10;
  };

  __u32_t value;
}laddr_t ,laddr_tp *;

// FIXME: where is the end of #endif PAGING_PAE??


typedef union Page_Dir_Entry
{
  struct 
  {
	//TODO
  };

  __u32_t value;
}pde_t ,pde_tp *; // Page Directory Entry;
#endif // End of __BIT32_PAGING_NO_PAE;__

#endif // End of __BIT32_PAGING__;


//--- definition of Page Fault Error Code;
typedef __u32_t pfec_t; // Page Fault Error Code; 
#define PFEC_P	_B(0) /* 1 caused by page-level-proctection ,
		       * 0 for page-not-present;
		       */
#define PFEC_WR	_B(1) // 1 caused by page-can't-write ,0 for read;
#define PFEC_US	_B(2) // 1 caused by excute-while-CPL=3 ,0 for CPL<3;
#define PFEC_RS	_B(3) /* 1 caused by reserved-bits-not-clear;
		       * this bit is set only-under PFEC_P is set ,
		       * because page-bit check only under page-presented
		       * situation ,
		       * 0: error not caused by reserved bits;
		       */
#define PFEC_ID	_B(4) /* 1 caused by instruction-fetch;
		       * 0: error not caused by instruction-fetch;
		       * NOTE: USELESS UNDER 32BIT-PAGE MODE(CR4.PAE=0 or 
		       * IA32_EFER.NXE=0);
		       */

#define page_enable()  cr0_set(CR0_PG)


#ifdef __486_COMPAT
#define TLB_flush_mem(mem) 	
#else
static inline void TLB_flush_mem(__mem_t mem) true_inline;
static inline void TLB_flush_mem(__mem_t mem)
{
  __asm__ volatile("invlpg %0\n\t"
		   :
		   :"m" (*mem)
		   );
}
#endif //End of __486_COMPAT




#endif // !__ASSEMBLER__

#endif // End of __MIMOSA_PC32_PAGING_H;
