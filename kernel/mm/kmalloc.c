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

#include <mm/kmalloc.h>

#ifdef __KERN_DEBUG__
#include <debug.h>
#endif

static kmalloc_info_t
kmalloc_info = { NULL ,PG_SIZE ,SPIN_INIT };

static inline struct Page* get_current_page();
static inline struct Page* set_current_page(struct Page*);
static inline size_t get_current_page_rest_size();
static inline void current_page_alloc(size_t size);
static inline void current_page_realloc();

static inline struct Page* get_current_page()
{
  return kmalloc_info.current_page;
}

static inline struct Page* set_current_page(struct Page* pg)
{
  // TODO: must be exclusive!!!
  // lock
  kmalloc_info.current_page = pg;
  // unlock
  
  return kmalloc_info.current_page;
}

static inline size_t get_current_page_rest_size()
{
  return kmalloc_info.cur_page_rest_mem;
}

// >=0: alloc successly, <0 the other size need to alloc.  
static inline int current_page_alloc(size_t size)
{
  if(size > PG_SIZE)
    pinic("Alloc size too large! This must be a bug!");

  if(!get_current_page())
    current_page_realloc();
  
  kmalloc_info.cur_page_rest_mem -= size;

  return kmalloc_info.cur_page_rest_mem;
}

static inline void current_page_realloc()
{
  struct Page* pg = NULL;

  while((pg = __page_alloc()) == NULL)
    {
      // TODO: should sleep till there's available page
      //sleep();
    }

  return set_current_page(pg);
}

void* sbrk(size_t amount)
{
  size_t c = get_current_page_rest_size();
  size_t n = current_page_alloc(amount);
  struct Page* pg = get_current_page();
  void *m = pg->pg_link;
    
  do
    {
      c = get_current_page_rest_size();
      mm_map_to_current_heap(pg->pg_link ,c);

      amount -= n;
      n = current_page_realloc(amount);
    }while(n < 0);
      
  return m;
}

int brk(void* end_data_segment)
{}

void *kmalloc(size_t size)
{

  // TODO: implement it!
  return NULL;
}

