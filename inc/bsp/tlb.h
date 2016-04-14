#ifndef	__MIMOSA_PC32_TLB_H
#define __MIMOSA_PC32_TLB_H
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

#include <types.h>
#include "cpu/crx.h"
#include "cpu/paging.h"

static inline void __flush_tlb() __true_inline;
static inline void __flush_tlb_global() __true_inline;
static inline void __flush_tlb_page(void *addr) __true_inline;

static inline void __flush_tlb() 
{
  cr3_set(cr3_get());
}

static inline void __flush_tlb_global()
{
  global_pages_disable();
  __flush_tlb();
  global_pages_enable();
}

static inline void __flush_tlb_page(void *addr)
{
  TLB_flush_mem(addr);
}



#endif // End of __MIMOSA_PC32_TLB_H;
