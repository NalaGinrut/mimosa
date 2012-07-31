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

#include <osconfig.h>
#include <types.h>
#include <global.h>
#include <bsp/bsp_mm.h>

#ifdef __MM_HAS_PAGING__

#include <bsp/pmap.h>

// define a mutable var of VPT in case we need to do something with it.
static void* mimosa_vpt = (void*) GET_BSP_VAR(VPT);

struct Page* __alloc_page()
{
  struct Page* ret = ____get_free_page();

  if(!ret)
    {
      /* TODO: If no free page, then do:
       *	1. give the warn;
       *	2. try swap then alloc
       *	3. try free some pages then alloc
       *	4. panic
       */
      panic("no free page!\n");
    }
  
  return ret;
}

void __free_page(struct Page* pg)
{
  if(!pg)
    panic("Try to free an NULL page!");

  return ____free_this_page(pg);
}

void __page_remove(void* va)
{

  // TODO: the wrapper of pmap_page_remove
}

#endif // End of __MM_HAS_PAGING__;
