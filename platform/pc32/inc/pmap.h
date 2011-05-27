#ifndef	__MIMOSA_BSP_PC32_PMAP_H
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
#include <bsp/bsp_mm.h>

extern char recondo[];
extern char tmp_stack[] ,tmp_stack_top[];

extern struct Page *GET_GLOBAL_VAR(pages);
extern size_t GET_GLOBAL_VAR(npage);

extern seg_des_t GET_GLOBAL_VAR(gdt[]);
extern struct gdt_prelude GET_GLOBAL_VAR(gdt_pl);

//extern physaddr_t boot_cr3;
//extern pde_t *boot_pgdir;

//extern struct Segdesc gdt[];
//extern struct Pseudodesc gdt_pd;


/* define Page List */
typedef struct Page
{
  SLIST_HEAD(,Page_entry) pg_list;
  u16_t pg_ref;
}page_list_t;
 
// FIXME: I need this pmap struct to unify all page map information;
/*
  typedef struct Page_map_struct
  {
  pte_t			*pm_pdir;       // KVA of page directory 
  TAILQ_ENTRY(pmap)       pm_pmnode;      // list of pmaps 
  size_t 			npage;		// numbers of pages 	
  //TAILQ_HEAD(,pv_entry)   pm_pvlist;      // list of mappings in pmap 
  int	               pm_count;       // reference count 
  //cpumask_t               pm_active;      // active on cpus 
  //cpumask_t               pm_cached;      // cached on cpus 
  int                     pm_filler02;    // (filler sync w/vkernel) 
  //struct pmap_statistics  pm_stats;       // pmap statistics 
  //struct  vm_page         *pm_ptphint;    // pmap ptp hint 
  //int                     pm_generation;  // detect pvlist deletions 
  }pmap_t ,*pmap_tp;
*/

/* This function takes a kernel virtual address -- an address that points above
 * KERN_BASE, where the machine's maximum of physical memory is mapped --
 * and returns the corresponding physical address.  It panics if you pass it a
 * non-kernel virtual address.
 */
static inline physaddr_t PADDR(physaddr_t kva)
{	
  physaddr_t __m_kva = (physaddr_t)kva;	
  
  if (__m_kva < KERN_BASE)			
    panic("PADDR called with invalid kva %08lx", __m_kva);
	
  return (__m_kva - KERN_BASE);					
}

/* This function takes a physical address and returns the corresponding kernel
 * virtual address.  It panics if you pass an invalid physical address.
 */
static inline void* KADDR(physaddr_t pa)
{
  physaddr_t _pa = (pa);
  u32_t _ppn = PPN(_pa);
  size_t npage = GET_GLOBAL_VAR(npage);
  
  if (_ppn >= npage)
    panic("KADDR called with invalid pa %08lx", _pa);
  
  return (void*) (_pa + KERN_BASE);	
}

static inline ppn_t page2ppn(struct Page *pp)
{
  return (pp - pages); // neat!
}

static inline physaddr_t page2pa(struct Page *pp)
{
  return page2ppn(pp) << PG_SHIFT;
}

static inline struct Page* pa2page(physaddr_t pa)
{
  size_t npage = GET_GLOBAL_VAR(npage);

  if (PPN(pa) >= npage)
    panic("pa2page called with invalid pa");
  return &pages[PPN(pa)];
}

static inline void* page2kva(struct Page *pp)
{
  return KADDR(page2pa(pp));
}

void pmap_detect_memory(void);
static void* pmap_tmp_alloc(u32_t n ,u32_t align);

#endif // End of __BSP_PC32_PMAP_H;
