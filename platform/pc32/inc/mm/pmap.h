#ifndef 	__MIMOSA_BSP_PC32_PMAP_H
#define	__MIMOSA_BSP_PC32_PMAP_H
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
#include <types.h>
#include <error.h>
#include <ds/qlist.h>
#include <bsp/cpu/paging.h>

extern char* recondo;
extern char* tmp_stack ,tmp_stack_top;

extern struct Page *pages;
extern size_t npage;

//extern physaddr_t boot_cr3;
//extern pde_t *boot_pgdir;

//extern struct Segdesc gdt[];
//extern struct Pseudodesc gdt_pd;

/* define Page List */
SLIST_HEAD(Page_list ,Page);

typedef SLIST_ENTRY(Page) page_list_entry_t;

typedef struct Page
{
	page_list_entry_t pp_link;	/* free list link */
	u16_t pp_ref;
}page_t;


/* This function takes a kernel virtual address -- an address that points above
 * KERNBASE, where the machine's maximum 256MB of physical memory is mapped --
 * and returns the corresponding physical address.  It panics if you pass it a
 * non-kernel virtual address.
 */
static inline physaddr_t PADDR(physaddr_t kva)
{	
	physaddr_t __m_kva = (physaddr_t)kva;	

	if (__m_kva < KERN_BASE)			
		panic("PADDR called with invalid kva %08lx", __m_kva);
	
	return __m_kva - KERN_BASE;					
}

/* This function takes a physical address and returns the corresponding kernel
 * virtual address.  It panics if you pass an invalid physical address. */
static inline void* KADDR(physaddr_t pa)
{
	physaddr_t __m_pa = (pa);	
	u32_t __m_ppn = PPN(__m_pa);	

	if (__m_ppn >= npage)		
		panic("KADDR called with invalid pa %08lx", __m_pa);

	return (void*) (__m_pa + KERN_BASE);					
}

static inline ppn_t
page2ppn(struct Page *pp)
{
	return pp - pages;
}

static inline physaddr_t
page2pa(struct Page *pp)
{
	return page2ppn(pp) << PGSHIFT;
}

static inline struct Page*
pa2page(physaddr_t pa)
{
	if (PPN(pa) >= npage)
		panic("pa2page called with invalid pa");
	return &pages[PPN(pa)];
}

static inline void*
page2kva(struct Page *pp)
{
	return KADDR(page2pa(pp));
}


#endif // End of __BSP_PC32_PMAP_H;
