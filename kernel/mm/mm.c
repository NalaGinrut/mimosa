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

#include <osconfig.h>
#include <types.h>
#include <mm/mm.h>

#ifdef __KERN_DEBUG__
#include <debug.h>
#endif

static struct kmap_table mimosa_kmap_table = { RB_ROOT ,NULL };

static inline void __kmap_init();
static inline kmap_t __kmap_alloc();

static inline void __kmap_init()
{
    
}

static inline kmap_t __kmap_alloc()
{
  struct struct kmap* m = NULL;
  
  
  /*   	TODO:
   *	1. alloc a huge block mem in the init step;
   *	2. init this block mem into a list;
   *	3. alloc one kmap from this list;
   */

  return m;
}

static inline kmap_t __mm_search_kmap(void* addr)
{
  struct rb_node* n = mimosa_kmap_table.rb_root;
  struct kmap *m;

  while (n)
    {
      page = rb_entry(n ,struct kmap ,rb_node);

      if(addr < m->addr)
	n = n->rb_left;
      else if (addr > page->offset)
	n = n->rb_right;
      else
	return page;
    }

  return NULL;
}

static inline kmap_t __mm_insert_kmap(void* addr ,u32_t size)
{
  struct kmap *m = __kmap_alloc();
}

// TODO: LOCK is needed.
static inline struct Page* __mm_insert_page_cache(struct inode * inode,
						  u32_t offset,
						  struct rb_node * node)
{
  struct Page *pg  = __rb_insert_page_cache(inode, offset, node);

  if(pg)
    rb_insert_color(node, &inode->i_rb_page_cache);

  return ret;
}
