/*	
 *  Copyright (C) 2010-2012  
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
#include <bsp/tlb.h>
#include <retval.h>

#ifdef __KERN_DEBUG__
#define kprintf cprintf
#define MARK_TWAIN kprintf("%s OK\n" ,__func__)
static void pmap_check_boot_pgdir();
static physaddr_t pmap_check_va2pa(pte_t *pgdir ,laddr_t va);
#else
#define kprintf
#define MARK_TWAIN
#endif 

static void pmap_jump_into_paging_mode(pde_t* pgdir);
static void pmap_page_init_pg(struct Page *pg);
static void* pmap_tmp_alloc(u32_t n ,u32_t align);
static inline pte_t* pmap_tmp_lookup_dir(pde_t *pgdir ,laddr_t la);
static pte_t* pmap_tmp_pgdir_get(pde_t *pgdir ,laddr_t la);
static void pmap_tmp_segment_map(pde_t *pgdir ,laddr_t la ,size_t size,
				 physaddr_t pa ,int attr);

// These variables are set by i386_detect_memory()
static physaddr_t pa_top;	// top of physical address
static u32_t base_mem;		// Amount of base memory (in bytes)
static u32_t ext_mem;		// Amount of extended memory (in bytes)

// These variables are set in i386_vm_init()
static pde_t* tmp_pgdir;	// Virtual address of boot time page directory
static void* tmp_freemem = 0;	// Pointer to next byte of free mem

// global variables
u32_t MK_GLOBAL_VAR(npage);		// Amount of physical memory (in pages)
struct Page* MK_GLOBAL_VAR(pages); // Virtual address of physical page array

// FIXME: I need atomic handler to this free list
static page_list_t pmap_page_free_list; // Free list of physical pages

#define PMAP_EXT_MEM_FIX(mem)	\
  (MEM_HOLE_END + (mem))

#define pmap_how_many_pages()	\
  (pa_top / PG_SIZE)

#define pmap_pde(m, v)  (&((m)->pm_pdir[(vm_offset_t)(v) >> PDRSHIFT]))
#define pdir_pde(m, v) (m[(vm_offset_t)(v) >> PDRSHIFT])

#define pmap_page_set_attr(pg ,attr)	\
  pmap_pte_set_attr(page2pa(pg) ,attr)

#define pmap_pxe_pred(pde ,attr)	((pde) & (attr))

#define pmap_pde_p(pde)         pmap_pxe_pred(pde ,PTE_PRESENT) // Page Dirctory is present
#define pmap_lookup_dir_from_pde(la ,pde)	(&((pde)[PDX(la)]))
#define pmap_get_pte_from_va(va ,pte)	((pte)[PTX(va)])
#define pmap_pde_set_attr(pde ,attr) (pde_t)((u32_t)(pde) | (attr))

#define pmap_pte_w(pte)         pmap_pxe_pred(pte ,PTE_WRITE) 	// Page Table is writable
#define pmap_pte_d(pte)         pmap_pxe_pred(pte ,PTE_DIRTY) 	// Page Table is dirty
#define pmap_pte_u(pte)         pmap_pxe_pred(pte ,PTE_USER) 	// Page Table is user
#define pmap_pte_p(pte)         pmap_pxe_pred(pte ,PTE_PRESENT)	// Page Table is present

#define pmap_get_pte_in_pa(addr)	((pte_t)PADDR((u32_t)addr))
#define pmap_get_pte_in_ka(addr)	((pte_t)KADDR((u32_t)addr))
#define pmap_pte_set_attr(pte ,attr) (pte_t)((u32_t)(pte) | (attr))

// use PD in case mess up with pmap_map_pa_to_la
#define pmap_map_PD_to_la(dir ,pd ,la ,attr)	\
  do{ dir[PDX(la)] = ((u32_t)pd | PTE_PRESENT | attr); }while(0);

#define pmap_map_pa_to_la(table ,pa ,la ,attr) \
  do{ table[PTX(la)] = ((u32_t)pa | PTE_PRESENT | attr); }while(0);

#define pmap_paging_mode_turn_on()	\
  do{					\
    u32_t cr0 = cr0_get();		\
    cr0 |= BSP_PG_MODE_ON;		\
    cr0 &= ~(BSP_PG_MODE_OFF);		\
    cr0_set(cr0);			\
  }while(0);

physaddr_t pmap_va2pa(pde_t *pgdir ,laddr_t va)
{
  return 0;
}

pde_t *pmap_get_tmp_pgdir()
{
 return tmp_pgdir;
}

void pmap_detect_memory()
{
  base_mem = nvram_get_base_mem_size();
  ext_mem = nvram_get_ext_mem_size();

  pa_top = ext_mem? PMAP_EXT_MEM_FIX(ext_mem) : base_mem;
  GET_GLOBAL_VAR(npage) = pmap_how_many_pages();

  cprintf("Physical memory: %uK available, " ,pa_top/1024);
  cprintf("base = %dK, extended = %dK\n" ,base_mem/1024 ,ext_mem/1024);
  MARK_TWAIN;
}

static void* pmap_tmp_alloc(u32_t size ,u32_t align)
{
  void *va;
  extern char recondo[];
  
  tmp_freemem = tmp_freemem? tmp_freemem : recondo;

  if( PADDR((physaddr_t)tmp_freemem) > (u32_t)pa_top )
    {
      panic("mmr: memory is not enough!!");
    }

  tmp_freemem = (void*)ROUND_UP((u32_t)tmp_freemem ,align);
  va = (void *)tmp_freemem;
  tmp_freemem += size;

  //MARK_TWAIN;
  return va;
}

// NOTE: search present page ,NULL for opposite
static inline pde_t* pmap_tmp_lookup_dir(pde_t *pgdir ,laddr_t la)
{
  return (pde_t*)pmap_lookup_dir_from_pde(la ,pgdir);
}

/* create a pgdir in tmp-stage
 * if the pgdir is present, just return it.
 * or create a new one then map it.
 */
static pde_t* pmap_tmp_pgdir_get(pde_t *pgdir ,laddr_t la)
{
  pde_t *pd = NULL;
  pde_t *ret = pmap_tmp_lookup_dir(pgdir ,la);
  // pd is pgdir-addr ,*pd is the pgdir
  
  // if found a present page dir than return it
  if(!pmap_pte_p(*ret))
    {

      // else alloc a new page dir and map it
      pd = (pde_t*)pmap_tmp_alloc(PT_ENTRIES ,PG_SIZE);
      memset(pd ,0 ,PT_ENTRIES);
      pd = (pde_t*)pmap_pte_set_attr(pd ,PTE_WRITE | PTE_PRESENT);
            
      // NOTE: page content is physaddr
      *ret = (pde_t)pmap_get_pte_in_pa(pd);
    }
  
  //MARK_TWAIN;
  return ret;
}

static void pmap_tmp_segment_map(pde_t *pgdir ,laddr_t la ,size_t size,
				 physaddr_t pa ,int attr)
{
  u32_t count;
  pde_t *pd = NULL;
  pte_t *pt = NULL;
  u32_t n = size/PG_SIZE;
  const u32_t kstktop = (u32_t)GET_BSP_VAR(KSTKTOP);
  const u32_t kstksize = KERNEL_STACK_SIZE;

  for(count = 0;
      count < n;
      count++ ,la += PG_SIZE ,pa += PG_SIZE)
    {
      pd = pmap_tmp_pgdir_get(pgdir ,la);
      // NOTE: don't check NULL here, because tmp_alloc already done that.

      pt = (pte_t*)pmap_get_pte_in_ka(PTA(*pd));
      pmap_map_pa_to_la(pt ,pa ,la ,attr);
    }

  //MARK_TWAIN;
}

void pmap_vm_init()
{
  pde_t *pgdir;
  u32_t size = 0;
  DECL_MUTABLE_GLOBAL_PTRVAR(struct Page** ,pages);

  // read-only vars
  const u32_t vpt = (u32_t)GET_BSP_VAR(VPT);
  const u32_t uvpt = (u32_t)GET_BSP_VAR(UVPT);
  const u32_t kstktop = (u32_t)GET_BSP_VAR(KSTKTOP);
  const u32_t kstksize = KERNEL_STACK_SIZE;
  const u32_t upages = (u32_t)GET_BSP_VAR(UPAGES);
  DECL_IMMUTABLE_GLOBAL_VAR(u32_t ,npage);
  //

  /* map VPT/UVPT to same physical address with different attribute
   */
  pgdir = pmap_tmp_alloc(PG_SIZE ,PG_SIZE);
  memset(pgdir ,0 ,PG_SIZE);
  tmp_pgdir = pgdir;
  kprintf("pmap_vm_init: #1 init pgdir:%p\n" ,pgdir);

  pmap_map_PD_to_la(pgdir ,PADDR((u32_t)pgdir) ,vpt ,PTE_WRITE);
  pmap_map_PD_to_la(pgdir ,PADDR((u32_t)pgdir) ,uvpt ,PTE_USER);
  kprintf("pmap_vm_init: #2 map VPT/UVPT\n");

  // map tmp_stack
  size = kstksize;
  pmap_tmp_segment_map(pgdir ,kstktop-kstksize ,size,
  		       PADDR((u32_t)tmp_stack) ,PTE_WRITE);
  kprintf("pmap_vm_init: #3 map KERNEL STACK\n");

  /* map kernel space, NOTE: we map kernel from 0 ,so we can easily convert
   * kernel address to physical address by simple minus. You'll enjoy it later.
   */
  size = KERN_TMP_MAP_SIZE;
  pmap_tmp_segment_map(pgdir ,KERN_BASE ,size ,0 ,PTE_WRITE);
  // clear 1 page to avoid some trouble when you init pages
  memset((void*)KERN_BASE ,0 ,PG_SIZE);
  kprintf("pmap_vm_init: #4 map KERNEL space\n");

  /* map meta-page space
   * FIXME: we'll clear all meta-page space, but it causes slowly boot.
   *	    I expect it to clear these space with LD trick. I'll fix it later.
   */
  size = npage * sizeof(struct Page);
  *pages = pmap_tmp_alloc(size ,PG_SIZE);
  memset(*pages ,0 ,size);
  pmap_tmp_segment_map(pgdir ,upages ,size,
		       PADDR((u32_t)(*pages)) ,PTE_USER);
  kprintf("pmap_vm_init: #5 map meta-PAGE space\n");

#ifdef __KERN_DEBUG__
  kprintf("Checking boot memory alloc...\n");
  pmap_check_boot_pgdir();
  kprintf("Boot memory init OK...\n");
#endif
  pmap_jump_into_paging_mode(pgdir);
  
  MARK_TWAIN;
}

static void pmap_jump_into_paging_mode(pde_t* pgdir)
{
  DECL_IMMUTABLE_GLOBAL_PTRVAR(struct gdt_pseudo_desc* ,gdt_pd);
  u32_t cr3 = PADDR((u32_t)pgdir);
  kprintf("pgdir:%p cr3:%p\n" ,pgdir ,cr3);

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
  pgdir[0] = pgdir[PDX(KERN_BASE)];

  /* jump into Paging Mode, however, we have 32bit-paging only.
   * If you need a PAE-paging, go for it! get up, you're a hacker!
   */ 
  cr3_set(cr3); // Install page table first
  pmap_paging_mode_turn_on();

  // Reload all segment registers.
  gdt_load(*gdt_pd);

  gdt_seg_reload(gs ,UD_SEL | RPL_RING3); 
  gdt_seg_reload(fs ,UD_SEL | RPL_RING3);
  gdt_seg_reload(es ,KD_SEL | RPL_RING0);
  gdt_seg_reload(ds ,KD_SEL | RPL_RING0);
  gdt_seg_reload(ss ,KD_SEL | RPL_RING0); // FIXME: I need a kernel stack selector

  gdt_cs_reload();

  gdt_local_desc_load(0);

  // Final mapping: KERN_BASE+x => KERN_BASE+x => x.

  // This mapping was only used after paging was turned on but
  // before the segment registers were reloaded.
  pmap_map_PD_to_la(pgdir ,0 ,0 ,0);

  // Flush the TLB for good measure, to kill the pgdir[0] mapping.
  __flush_tlb();

  MARK_TWAIN;
}  

#ifdef __KERN_DEBUG__
static void pmap_check_boot_pgdir()
{
  u32_t i, n;
  pde_t *pgdir = tmp_pgdir;

  // read-only vars
  const u32_t upages = (u32_t)GET_BSP_VAR(UPAGES);
  const u32_t kstksize = KERNEL_STACK_SIZE;
  const u32_t kstktop = (u32_t)GET_BSP_VAR(KSTKTOP);
  const u32_t vpt = (u32_t)GET_BSP_VAR(VPT);
  const u32_t uvpt = (u32_t)GET_BSP_VAR(UVPT);
  DECL_IMMUTABLE_GLOBAL_VAR(struct Page* ,pages);
  DECL_IMMUTABLE_GLOBAL_VAR(u32_t ,npage);

  //
  // check pages array
  n = ROUND_UP(npage*sizeof(struct Page) ,PG_SIZE);

  for(i = 0; i < n; i += PG_SIZE)
    {
      assert(pmap_check_va2pa(pgdir ,upages + i) == PADDR((u32_t)pages) + i);
    }
  kprintf("[1]page check ok!\n");
  // check phys mem
  for(i = 0; KERN_BASE + i != 0; i += PG_SIZE)
    {
      assert(pmap_check_va2pa(pgdir, KERN_BASE + i) == i);
    }
  kprintf("[2]kern check ok!\n");

  // check kernel stack
  for(i = 0; i < kstksize; i += PG_SIZE)
    {
      assert(pmap_check_va2pa(pgdir, kstktop - kstksize + i) == PADDR((u32_t)tmp_stack) + i);
    }
  kprintf("[3]kstack check ok!\n");

  // check for zero/non-zero in PDEs
  for(i = 0; i < PT_ENTRIES; i++) 
    {
      if(i == PDX(vpt)
	 || i == PDX(uvpt)
	 || i == PDX(kstktop-1)
	 || i == PDX(upages))
	{
	  assert(pgdir[i]);
	  continue;
	}
	   
      if(i >= PDX(KERN_BASE))
	{
	  assert(pgdir[i]);
	}
      else
	{
	  assert(pgdir[i] == 0);
	}

    }

  MARK_TWAIN;
}

static physaddr_t pmap_check_va2pa(pde_t *pgdir, laddr_t va)
{
  pte_t *pd = NULL;
  pte_t *pt = NULL;
  pte_t p = 0;

  pd = (pte_t*)pmap_tmp_lookup_dir(pgdir ,va);
  
  if(!pmap_pte_p(*pd))
    {
      panic("page table %p didn't map\n" ,*pd);
      return ~0;
    }
  
  pt = (pte_t*)KADDR(PTA(*pd));
  p = (pte_t)pt[PTX(va)];
  
  if(!pmap_pte_p(p))
    {
      panic("va:%p didn't map\n" ,va);
      return ~0;
    }

  //MARK_TWAIN;
  return PTA(p);
}
#endif // End of __KERN_DEBUG__


void pmap_page_init()
{
  DECL_MUTABLE_GLOBAL_PTRVAR(struct Page** ,pages);
  //struct Page* pages = GET_GLOBAL_VAR(pages);
  struct Page* pp = NULL;
  
  // read-only vars
  DECL_IMMUTABLE_GLOBAL_VAR(u32_t ,npage);
  //const u32_t npage = GET_GLOBAL_VAR(npage);
  //

  memset(*pages ,0 ,npage*sizeof(struct Page));
  LIST_INIT(&pmap_page_free_list);

  for(int i = npage-1; i >= 0; i--)
    {
      pp = *pages+i;

      if(0 == i)
	{
	  pp->pg_ref = 1; // mark page0 as used!
	  kprintf("page0: %p -- %u\n" ,&(*pages)[i] ,(*pages)[i].pg_ref);

	}else if( i >= (IO_PHY_MEM / PG_SIZE) 
		  && i < (MEM_HOLE_END / PG_SIZE) )
	{
	  pp->pg_ref = 1;

	}else if( i >= (IO_PHY_MEM / PG_SIZE)
		  && i < (KERN_BASE / PG_SIZE) )
	{
	  pp->pg_ref = 1;

	}else
	{
	  pp->pg_ref = 0;
	}
	  
    if(0 == i)
      {
	kprintf("page0: %p -- %u\n" ,&(*pages)[0] ,(*pages)[0].pg_ref);
      }
    
    LIST_INSERT_HEAD(&pmap_page_free_list ,pp ,pg_link);
  }

  //panic("ok");	
}

static void pmap_page_init_pg(struct Page *pg)
{
  memset(pg ,0 ,sizeof(struct Page));
}

retval pmap_page_alloc(struct Page **pg_store)
{
  if( LIST_EMPTY(&pmap_page_free_list) )
    {
      //warn("[0]%x\n",ENOMEM);
      //kprintf("pmap_page_alloc: empty page list!\n");
      return ENOMEM;
    }

  *pg_store = LIST_FIRST(&pmap_page_free_list);
  LIST_REMOVE(*pg_store ,pg_link);

  if( !(*pg_store) )
    {
      //warn("[1]%x\n",ENOMEM);
      //kprintf("pmap_page_alloc: invalid pg_store or no mem!\n");
      return ENOMEM;
    }

  //warn("[2]%x\n",ENOMEM);

  //kprintf("pmap_page_alloc: %p allocated!\n" ,*pg_store);
  return OK;
}
  
void pmap_page_free(struct Page *pg)
{
  kprintf("pmap_page_free: pg-%p pg->pg_ref=%u pg->pg_link=%p\n",
	  pg ,pg->pg_ref ,pg->pg_link);
  
  LIST_INSERT_HEAD(&pmap_page_free_list ,pg ,pg_link);
}

void pmap_page_dec_ref(struct Page *pg)
{
  if(pg->pg_ref != 0 &&
     --pg->pg_ref == 0)
    {
      kprintf("pmap_page_dec_ref: pg->pg_ref ==> %u\n",
	      pg->pg_ref);
      
      pmap_page_free(pg);
    }
}

// FIXME: it should be dir_lookup
pde_t* pmap_page_dir_lookup(pde_t* pgdir ,const void *va)
{
  // FIXME: I need arbitrary level page table lookup
  pde_t* pd = NULL;

  pd = pmap_lookup_dir_from_pde(va ,pgdir);
  kprintf("pmap_pgdir_lookup: #0 pgdir-%p va-%p pd-%p *pd-%p\n",
	  pgdir ,va ,pd ,*pd);

#ifdef __KERN_DEBUG__
  if( pmap_pde_p(*pd) )
    {
      kprintf("pmap_pgdir_lookup: #1 find a page_dir-*(%p):%p at %p\n",
	      pd ,*pd ,va);
    }
  else
    {
      kprintf("pmap_pgdir_lookup: #2 page_dir-%p at %p is used,\n"
	      "I can't find an available one!\n",
	      *pd ,va);
    }
#endif // End of __KERN_DEBUG__

  return pmap_pde_p(*pd)? pd : NULL;
}
    
pde_t* pmap_page_dir_create(pde_t *pgdir ,const void* va)
{
  // FIXME: I need arbitrary level page table lookup
  pde_t *pd = pmap_page_dir_lookup(pgdir ,va);
  struct Page *pg = NULL;

  if(NULL != pd)
    {
      kprintf("pmap_pgdir_create: #0 va-%p is used by %p!\n" ,va ,pd);
      return pd;
    }
      
  kprintf("pmap_pgdir_create: #0 request to create one page_table page!\n");
  
  if( ENOMEM == pmap_page_alloc(&pg) )
    {
      kprintf("pmap_pgdir_create: #1 no free mem!\n");
      return NULL;
    }

  *pd = pmap_page_set_attr(pg ,PTE_PRESENT);

  kprintf("pmap_pgdir_create: #2 created a new page_dir at *(%p)-%p\n",
	  *pd ,pd);

  return pd;
}
      
retval pmap_page_insert(pde_t *pgdir ,struct Page *pg ,void *va ,int attr)
{
  // FIXME: I need arbitrary level page table lookup
  pde_t *pd = pmap_page_dir_lookup(pgdir ,va);
  pte_t *pt = NULL;
  
  if(NULL == pd)
    {
      kprintf("pmap_page_insert: #0 didn't find page_dir. craete one!\n");
      pd = pmap_page_dir_create(pgdir ,va);

      if(NULL == pd)
	return ENOMEM;
    }

  kprintf("pmap_page_insert: #1 we got a page_dir-%p in va-%p\n",
	  *pd ,va);

  pt = (pte_t*)pmap_get_pte_in_ka(PTA(*pd));
  
  if( pmap_pte_p(pt[PTX(va)]) ) // table present
    {
      if( PTA(pt[PTX(va)]) == page2pa(pg) ) 
	{
	  // if the page is present and has the same map ,then return OK
	  kprintf("pmap_page_insert: #2 we find same map between va-%p "
		  "and pa-%p\n ,do nothing then return!\n" ,va ,pg);
	  return OK;
	}
      else
	{
	  /* if the page is present but has different map ,then delete it
	   * so we'll remap it later
	   * TLB will be updated during pmap_page_remove
	   */
	  kprintf("pmap_page_insert: #3 we find a used page at %p[PTX(%p)]-%p "
		  "removed it!\n" ,pt ,va ,pt[PTX(va)]);
	  pmap_page_remove(pgdir ,va);
	}
    }

  kprintf("pmap_page_insert: #4 insert pg-%p into page_table at %p[PTX(%p)]\n",
	  pg ,pt ,va);

  pt[PTX(va)] = pmap_page_set_attr((void*)page2pa(pg) ,attr);

  pg->pg_ref++;
  kprintf("pmap_page_insert: #5 increase %p->pg_ref to %u \n",
	  pg ,pg->pg_ref);
  
  return OK;
}

struct Page* pmap_page_lookup(pde_t* pgdir ,void* va ,pde_t** pde_store)
{
  pde_t* pd = NULL;
  pte_t* pt = NULL;
  
  kprintf("pmap_page_lookup: #0 get in!\n");

  if(NULL != pde_store)
    {
      kprintf("pmap_page_lookup: #1 get valid pte_store-%p\n" ,pde_store);
 
      pd = pmap_page_dir_lookup(pgdir ,va);

      if(NULL == pd)
	{
	  kprintf("pmap_page_lookup: #2 didn't find it's page_dir entry, "
		  "return NULL!\n");
	  return NULL;
	}

      kprintf("pmap_page_lookup: #3 find it's page_dir entry: pd-%p *pd-%p\n",
	      pd ,*pd);

      *pde_store = pd;

      // walk 2-level page table
      pd = (pte_t*)KADDR(PTA(*pd));
      pt = (pte_t*)pd[PTX(va)];
	  
      kprintf("pmap_page_lookup: #4 pt-%p *pde_store-%p ret-%p "
	      "%p[PTX(%p)]-%p\n" ,pt ,*pde_store ,pa2page(PTA(pt)));

      return pa2page(PTX(pt));

    }
  
  return NULL;
}

void pmap_page_remove(pde_t *pgdir, void *va)
{
  pde_t* pd = NULL;
  pte_t* pt = NULL;
  struct Page *pg = pmap_page_lookup(pgdir ,va ,&pd);

  kprintf("pmap_page_remove: #0 get in!\n");

  if(NULL == pg)
    {
      warn("pd-%p PTX(%p)-%p pg-%p\n",pd ,va ,PTX(va));
      kprintf("pmap_page_remove: #1 pd-%p pt[PTX(%p)]-%p pg-%p didn't mapped!\n",
	      pd ,va ,pd[PTX(va)] ,pg);
      return;
    }
  warn("here!");
  pt = (pte_t*)KADDR(PTA(*pd));
  kprintf("pmap_page_remove: #2 release va-%p\n" ,va);

  pmap_page_dec_ref(pg);
  kprintf("pmap_page_remove: #3 pt[PTX(va)]==%p[PTX(%p)]-%p\n"
	  "pg-%p pg->pg_link-%p pg->pg_ref-%u\n",
	  pt ,va ,pt[PTX(va)] ,pg ,pg->pg_link ,pg->pg_ref);

  pt[PTX(va)] = pmap_pte_set_attr(pt[PTX(va)] ,PTE_PRESENT);
  pmap_tlb_invalidate(pgdir ,va);
  kprintf("pmap_page_remove: #4 FINISHED!\n");
}

void pmap_tlb_invalidate(pde_t* pgdir ,void* va)
{
  /* FIXME: we have only 2-level page table now, so we just flush va directly.
   *	    But I need an arbitrary n-level page table. so fixme later please.
   */	
  //TLB_flush_mem(va);
  __flush_tlb(va);
}

#ifdef __KERN_DEBUG__
void pmap_page_check()
{
  struct Page *pp ,*pp0 ,*pp1 ,*pp2;
  page_list_t fl;
  pde_t *pd = NULL;

  kprintf("ok pg check #1\n");
  // should be able to allocate three pages
  pp0 = pp1 = pp2 = NULL;
  assert(pmap_page_alloc(&pp0) == 0);
  assert(pmap_page_alloc(&pp1) == 0);
  assert(pmap_page_alloc(&pp2) == 0);


  kprintf("ok pg check #2\n");

  assert(pp0);
  assert(pp1 && pp1 != pp0);
  assert(pp2 && pp2 != pp1 && pp2 != pp0);

  /* kprintf("ok pg check #3\n" */
  /* 	  "pp0-%p pp0->pg_ref-%u page0-%p\n" */
  /* 	  "pp1-%p pp1->pg_ref-%u page1-%p\n" */
  /* 	  "pp2-%p pp2->pg_ref-%u page2-%p\n", */
  /* 	  pp0 ,pp0->pg_ref ,page2pa(pp0) , */
  /* 	  pp1 ,pp1->pg_ref ,page2pa(pp1) , */
  /* 	  pp2 ,pp2->pg_ref ,page2pa(pp2)); */


  // temporarily steal the rest of the free pages
  fl = pmap_page_free_list;
  LIST_INIT(&pmap_page_free_list);

  kprintf("ok pg check #4\n");

  // should be no free memory
  assert(pmap_page_alloc(&pp) == ENOMEM);
  kprintf("ok pg check #4.1\n");

  // there is no page allocated at address 0
  assert(pmap_page_lookup(tmp_pgdir, (void *) 0x0, &pd) == NULL);

  kprintf("ok pg check #4.2\n");

  // there is no free memory, so we can't allocate a page table 
  assert(pmap_page_insert(tmp_pgdir, pp1, 0x0, 0) < 0);

  kprintf("ok pg check #5\n");

  // free pp0 and try again: pp0 should be used for page table
  pmap_page_free(pp0);
  kprintf("ok pg check #5.1\n");
  assert(pmap_page_insert(tmp_pgdir, pp1, 0x0, 0) == 0);
  kprintf("ok pg check #5.2\n");
  assert(PTA(tmp_pgdir[0]) == page2pa(pp0));
  kprintf("ok pg check #5.3\n");
  assert(pmap_check_va2pa(tmp_pgdir, 0x0) == page2pa(pp1));
  kprintf("ok pg check #5.4\n");
  assert(pp1->pg_ref == 1);
  kprintf("ok pg check #5.5 pp0-%p pp1-%p\n"
	  "pp0->pg_ref: %u ,pp1->pg_ref: %u\n",
	  pp0 ,pp1 ,pp0->pg_ref ,pp1->pg_ref);
  assert(pp0->pg_ref == 1);

  kprintf("ok pg check #6\n");

  // should be able to map pp2 at PG_SIZE because pp0 is already allocated for page table
  assert(pmap_page_insert(tmp_pgdir, pp2, (void*) PG_SIZE, 0) == 0);
  assert(pmap_check_va2pa(tmp_pgdir, PG_SIZE) == page2pa(pp2));
  assert(pp2->pg_ref == 1);

  kprintf("ok pg check #7\n");

  // should be no free memory
  assert(pmap_page_alloc(&pp) == ENOMEM);
  kprintf("ok pg check #7.1\n");
  // should be able to map pp2 at PG_SIZE because it's already there
  assert(pmap_page_insert(tmp_pgdir, pp2, (void*) PG_SIZE, 0) == 0);
  kprintf("ok pg check #7.2\n");
  assert(pmap_check_va2pa(tmp_pgdir, PG_SIZE) == page2pa(pp2));
  kprintf("ok pg check #7.3 va:%p <=> pa:%p c_v2p:%p \n",
	  PG_SIZE ,page2pa(pp2) ,pmap_check_va2pa(tmp_pgdir ,PG_SIZE));
  assert(pp2->pg_ref == 1);

  kprintf("ok pg check #8\n");

  // pp2 should NOT be on the free list
  // could happen in ref counts are handled sloppily in page_insert
  assert(pmap_page_alloc(&pp) == ENOMEM);
  kprintf("ok pg check #8.1\n");
  // should not be able to map at PT_SIZE because need free page for page table
  assert(pmap_page_insert(tmp_pgdir, pp0, (void*) PT_SIZE, 0) < 0);
  kprintf("ok pg check #8.2\n");
  // insert pp1 at PG_SIZE (replacing pp2)
  assert(pmap_page_insert(tmp_pgdir, pp1, (void*) PG_SIZE, 0) == 0);
  kprintf("ok pg check #8.3\n");
  // should have pp1 at both 0 and PG_SIZE, pp2 nowhere, ...
  assert(pmap_check_va2pa(tmp_pgdir, 0) == page2pa(pp1));
  kprintf("ok pg check #8.4\n");
  assert(pmap_check_va2pa(tmp_pgdir, PG_SIZE) == page2pa(pp1));
  kprintf("ok pg check #8.5\n");
  // ... and ref counts should reflect this
  assert(pp1->pg_ref == 2);
  kprintf("ok pg check #8.6\n"
	  "pp1-%p pp2-%p\n"
	  "pp1->pg_ref: %u ,pp2->pg_ref: %u\n",
	  pp1 ,pp2 ,pp1->pg_ref ,pp2->pg_ref);

  assert(pp2->pg_ref == 0);
  kprintf("ok pg check #8.7\n");
	
  // pp2 should be returned by pmap_page_alloc
  assert(pmap_page_alloc(&pp) == 0 && pp == pp2);

  kprintf("ok pg check #9\n");


  // unmapping pp1 at 0 should keep pp1 at PG_SIZE
  pmap_page_remove(tmp_pgdir, 0x0);
  assert(pmap_check_va2pa(tmp_pgdir, 0x0) == ~0);
  assert(pmap_check_va2pa(tmp_pgdir, PG_SIZE) == page2pa(pp1));
  assert(pp1->pg_ref == 1);
  assert(pp2->pg_ref == 0);

  kprintf("ok pg check #10\n");

  // unmapping pp1 at PG_SIZE should free it
  pmap_page_remove(tmp_pgdir, (void*) PG_SIZE);
  assert(pmap_check_va2pa(tmp_pgdir, 0x0) == ~0);
  assert(pmap_check_va2pa(tmp_pgdir, PG_SIZE) == ~0);
  assert(pp1->pg_ref == 0);
  assert(pp2->pg_ref == 0);

  kprintf("ok pg check #11\n");

  // so it should be returned by pmap_page_alloc
  assert(pmap_page_alloc(&pp) == 0 && pp == pp1);

  // should be no free memory
  assert(pmap_page_alloc(&pp) == ENOMEM);

  // forcibly take pp0 back
  assert(PTA(tmp_pgdir[0]) == page2pa(pp0));
  tmp_pgdir[0] = 0;
  assert(pp0->pg_ref == 1);
  pp0->pg_ref = 0;

  kprintf("ok pg check #12\n");

  // give free list back
  pmap_page_free_list = fl;

  // free the pages we took
  pmap_page_free(pp0);
  pmap_page_free(pp1);
  pmap_page_free(pp2);

  kprintf("pmap_page_check() succeeded!\n");
}
#endif // End of __KERN_DEBUG__

