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

#include <types.h>
#include <ds/qlist.h>
#include <libkern.h>
#include <osconfig.h>
#include <global.h>
#include <error.h>
#include <bsp/pmap.h>
#include <bsp/bsp_mm.h>
#include <console.h>

#ifdef __KERN_DEBUG__
#define kprintf cprintf
#else
#define kprintf
#endif 

// These variables are set by i386_detect_memory()
static physaddr_t pa_top;	// top of physical address
static u32_t base_mem;		// Amount of base memory (in bytes)
static u32_t ext_mem;		// Amount of extended memory (in bytes)

// These variables are set in i386_vm_init()
static pde_t* tmp_pgdir;	// Virtual address of boot time page directory
static physaddr_t tmp_cr3;	// Physical address of boot time page directory
static void* tmp_freemem = 0;	// Pointer to next byte of free mem

// global variables
u32_t MK_GLOBAL_VAR(npage);		// Amount of physical memory (in pages)
struct Page* MK_GLOBAL_VAR(pages); // Virtual address of physical page array
static page_list_t MK_GLOBAL_VAR(page_free_list); // Free list of physical pages

#define PMAP_EXT_MEM_FIX(mem)	\
  (MEM_HOLE_END + (mem))

#define pmap_how_many_pages()	\
  (pa_top / PG_SIZE)

#define pmap_pde(m, v)  (&((m)->pm_pdir[(vm_offset_t)(v) >> PDRSHIFT]))
#define pdir_pde(m, v) (m[(vm_offset_t)(v) >> PDRSHIFT])

#define pmap_pxe_pred(pde ,attr)	(((pde) & (attr)) != 0)

#define pmap_pde_p(pde)         pmap_pxe_pred(pde ,PTE_PRESENT) // Page Dirctory is present
#define pmap_lookup_table_from_pde(la ,pde)	(&(pde)[PDX(la)])
#define pmap_pde_set_attr(pde ,attr) ((u32_t)(pde) | (attr))

#define pmap_pte_w(pte)         pmap_pxe_pred(pte ,PTE_WRITE) 	// Page Table is writable
#define pmap_pte_d(pte)         pmap_pxe_pred(pte ,PTE_DIRTY) 	// Page Table is dirty
#define pmap_pte_u(pte)         pmap_pxe_pred(pte ,PTE_USER) 	// Page Table is user
#define pmap_pte_p(pte)         pmap_pxe_pred(pte ,PTE_PRESENT)	// Page Table is present

#define pmap_get_pte_in_pa(addr)	((pte_t)PADDR((u32_t)addr))
#define pmap_get_pte_in_ka(addr)	((pte_t)KADDR((u32_t)addr))
#define pmap_pte_set_attr(pte ,attr) 	((u32_t)(pte) | (attr))

#define pmap_map_pa_to_la(table ,pa ,la ,attr)	\
  do{ table[PTX(la)] = ((u32_t)pa | attr); }while(0);

#define pmap_paging_mode_turn_on(cr0 ,cr3)	\
  do{						\
  cr3_set(cr3);					\
  (cr0) = cr0_get();				\
  (cr0) |= BSP_PG_MODE_ON;			\
  (cr0) &= ~(BSP_PG_MODE_OFF);			\
  cr0_set(cr0);					\
  }while(0);

void pmap_detect_memory(void)
{
  base_mem = nvram_get_mem_info(NVRAM_BASELO);
  ext_mem = nvram_get_mem_info(NVRAM_EXTLO);

  pa_top = ext_mem? PMAP_EXT_MEM_FIX(ext_mem) : base_mem;
  GET_GLOBAL_VAR(npage) = pmap_how_many_pages();

  cprintf("Physical memory: %dK available, ", (int)(pa_top/1024));
  cprintf("base = %dK, extended = %dK\n", (int)(base_mem/1024), (int)(ext_mem/1024));
}


static void* pmap_tmp_alloc(u32_t size ,u32_t align)
{
  void *va;
  
  tmp_freemem = tmp_freemem? tmp_freemem : recondo;
  
  if( PADDR((physaddr_t)tmp_freemem) > (u32_t)pa_top )
    {
      panic("mmr: memory is not enough!!\n");
    }

  tmp_freemem = (void*)ROUND_UP((u32_t)tmp_freemem ,align);
  va = (void *)tmp_freemem;
  tmp_freemem += size;

  return va;
}


static pte_t* pmap_tmp_pgdir_lookup(pde_t *pgdir ,laddr_t la)
{
  pte_t *ret = (pte_t*)pmap_lookup_table_from_pde(la ,pgdir);

  return pmap_pte_p(*ret)? NULL : ret;
}

static pte_t* pmap_tmp_pgdir_create(pde_t *pgdir ,laddr_t la)
{
  void *tmp_ptr = NULL;
  pte_t *ret = pmap_tmp_pgdir_lookup(pgdir ,la);

  if( ret != NULL )
    {
      tmp_ptr = pmap_tmp_alloc(PT_ENTRIES ,PG_SIZE);
      memset(tmp_ptr ,0 ,PD_SIZE);

      tmp_ptr = (void*)pmap_pte_set_attr(tmp_ptr ,PTE_WRITE | PTE_PRESENT);
      
      // NOTE: return pa rather than kva
      *ret = pmap_get_pte_in_pa(tmp_ptr);
    }

  return ret;
}

static void pmap_tmp_segment_map(pde_t *pgdir ,laddr_t la ,size_t size,
				 physaddr_t pa ,int attr)
{
  u32_t count;
  pte_t *pg_table = NULL;
  pte_t *tmp_pt = NULL;
  int flag = 0;
  
  for(count = 0;
      count < (size/PG_SIZE);
      count++ ,la += PG_SIZE ,pa += PG_SIZE)
    {
      pg_table = pmap_tmp_pgdir_create(pgdir ,la);
      // NOTE: don't check NULL here, because tmp_alloc already done that.

      tmp_pt = (pte_t*)pmap_get_pte_in_ka(PTA(*pg_table));
      pmap_map_pa_to_la(tmp_pt ,pa ,la ,attr);
    }
}

void pmap_vm_init(void)
{
  pde_t* pgdir;
  u32_t size = 0;
  struct Page* pages = GET_GLOBAL_VAR(pages);
  
  // read-only vars
  const u32_t vpt = GET_BSP_VAR(VPT);
  const u32_t uvpt = GET_BSP_VAR(UVPT);
  const u32_t kstktop = GET_BSP_VAR(KSTKTOP);
  const u32_t kstksize = KERNEL_STACK_SIZE;
  const u32_t upages = GET_BSP_VAR(UPAGES);
  const u32_t npage = GET_GLOBAL_VAR(npage);
  //

  /* map VPT/UVPT to same physical address with different attribute
   */
  pgdir = pmap_tmp_alloc(PT_ENTRIES ,PG_SIZE);
  memset(pgdir ,0 ,PG_SIZE);
  tmp_pgdir = pgdir;
  tmp_cr3 = PADDR((u32_t)pgdir);
  kprintf("pmap_vm_init: #1 init pgdir:%p\n",pgdir);

  pmap_map_pa_to_la(pgdir ,PADDR((u32_t)pgdir) ,vpt ,PTE_WRITE | PTE_PRESENT);
  pmap_map_pa_to_la(pgdir ,PADDR((u32_t)pgdir) ,uvpt ,PTE_USER | PTE_PRESENT);
  kprintf("pmap_vm_init: #2 map VPT/UVPT\n");

  // map tmp_stack
  pmap_tmp_segment_map(pgdir ,kstktop-kstksize ,kstksize,
		       PADDR((u32_t)tmp_stack) ,PTE_WRITE);
  kprintf("pmap_vm_init: #3 map KERNEL STACK\n");

  /* map kernel space, NOTE: we map kernel from 0 ,so we can easily convert
   * kernel address to physical address by simple minus. You'll enjoy it later.
   */
  pmap_tmp_segment_map(pgdir ,KERN_BASE ,KERN_TMP_MAP_SIZE,
		       0 ,PTE_WRITE);
  // clear 1 page to avoid some trouble when you init pages
  memset((void*)KERN_BASE ,0 ,PG_SIZE);
  kprintf("pmap_vm_init: #4 map KERNEL space\n");

  /* map meta-page space
   * FIXME: we'll clear all meta-page space, but it causes slowly boot.
   *	    I expect it to clear these space with LD trick. I'll fix it later.
   */
  size = npage * sizeof(struct Page);
  pages = pmap_tmp_alloc(size ,PG_SIZE);
  memset(pages ,0 ,size);
  pmap_tmp_segment_map(pgdir ,upages ,size,
		       PADDR((u32_t)pages) ,PTE_PRESENT | PTE_USER);
  kprintf("pmap_vm_init: #5 map meta-PAGE space\n");

  check_boot_pgdir();

  pmap_jump_into_paging_mode(pgdir ,(u32_t)tmp_cr3);
  
}

static void pmap_jump_into_paging_mode(pde_t* pgdir ,u32_t cr3)
{
  const struct gdt_pseudo_desc gdt_pd = GET_GLOBAL_VAR(gdt_pd);  
  u32_t cr0;
  //////////////////////////////////////////////////////////////////////
  // On x86, segmentation maps a VA to a LA (linear addr) and
  // paging maps the LA to a PA.  I.e. VA => LA => PA.  If paging is
  // turned off the LA is used as the PA.  Note: there is no way to
  // turn off segmentation.  The closest thing is to set the base
  // address to 0, so the VA => LA mapping is the identity.

  // Current mapping: VA KERN_BASE+x => PA x.
  //     (segmentation base=-KERN_BASE and paging is off)

  // From here on down we must maintain this VA KERN_BASE + x => PA x
  // mapping, even though we are turning on paging and reconfiguring
  // segmentation.

  // Map VA 0:4MB same as VA KERN_BASE, i.e. to PA 0:4MB.
  // (Limits our kernel to <4MB)
  pmap_map_pa_to_la(pgdir ,KERN_BASE ,0 ,0);
  
  /* jump into Paging Mode, however, we have 32bit-paging.
   * If you need a PAE-paging, get to it! get up, you're a hacker!
   */ 
  pmap_paging_mode_turn_on(cr0 ,cr3);

  // Reload all segment registers.
  gdt_load((void*)&gdt_pd);

  gdt_seg_reload(gs ,UD_SEL | RPL_RING3); 
  gdt_seg_reload(fs ,UD_SEL | RPL_RING3);
  gdt_seg_reload(es ,KD_SEL | RPL_RING0);
  gdt_seg_reload(ds ,KD_SEL | RPL_RING0);
  gdt_seg_reload(ss ,KD_SEL | RPL_RING0);

  gdt_cs_reload();
  
  gdt_local_desc_load(0);

  // Final mapping: KERN_BASE+x => KERN_BASE+x => x.

  // This mapping was only used after paging was turned on but
  // before the segment registers were reloaded.
  pmap_map_pa_to_la(pgdir ,0 ,0 ,0);

  // Flush the TLB for good measure, to kill the pgdir[0] mapping.
  cr3_set(cr3);
}  

#ifdef __KERN_DEBUG__
static void check_boot_pgdir(void)
{
	u32_t i, n;
	pde_t *pgdir = tmp_pgdir;

	// read-only vars
	const u32_t upages = GET_BSP_VAR(UPAGES);
	const u32_t npage = GET_GLOBAL_VAR(npage);
	const u32_t kstksize = KERNEL_STACK_SIZE;
	const u32_t kstktop = GET_BSP_VAR(KSTKTOP);
	const u32_t vpt = GET_BSP_VAR(VPT);
	const u32_t uvpt = GET_BSP_VAR(UVPT);
	const struct Page* pages = GET_GLOBAL_VAR(pages);
	//

	// check pages array
	n = ROUND_UP(npage*sizeof(struct Page), PG_SIZE);
	for (i = 0; i < n; i += PG_SIZE)
	  {	
	    //cprintf("i:%d\n",i/PGSIZE);
	    assert(check_va2pa(pgdir, upages + i) == PADDR((u32_t)pages) + i);
	  }

	// check phys mem
	for (i = 0; KERN_BASE + i != 0; i += PG_SIZE)
	  {
	    //cprintf("i:%d\n",i/PGSIZE);

	    assert( check_va2pa(pgdir, KERN_BASE + i) == i);

	//cprintf("%p->%p\n",KERNBASE+i,		    //== i);
	  }
	// check kernel stack
	for (i = 0; i < kstksize; i += PG_SIZE)
	  {
	    //cprintf("i:%d\n",i/PGSIZE);
	    assert(check_va2pa(pgdir, kstktop - kstksize + i) == PADDR((u32_t)tmp_stack) + i);
	  }

	// check for zero/non-zero in PDEs
	for (i = 0; i < PT_ENTRIES; i++) 
	  {
	    if(i == PDX(vpt)
	       || i == PDX(uvpt)
	       || i == PDX(kstktop-1)
	       || i == PDX(upages))
	      {
		assert(pgdir[i]);
	      }
	   
	    if (i >= PDX(KERN_BASE))
	      {
		assert(pgdir[i]);
	      }
	    else
	      {
		assert(pgdir[i] == 0);
	      }

	  }

	cprintf("check_boot_pgdir() succeeded!\n");
}

static physaddr_t check_va2pa(pde_t *pgdir, laddr_t va)
{
	pte_t *p;

	pgdir = &pgdir[PDX(va)];
	
	if(!pmap_pte_p(*pgdir))
	  return ~0;
	
	p = (pte_t*)KADDR(PTA(*pgdir));
	
	if(!pmap_pte_p(p[PTX(va)]))
	  return ~0;
	
	return PTA(p[PTX(va)]);

  return 0;
}
#endif // End of __KERN_DEBUG__

