#ifdef PLATFORM_HAS_PAGE
/*	
 *  Copyright (C) 2012,2016
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
#include <bsp/pmap.h>
#include <bsp/bsp_mm.h>

void* __alloc_page(size_t cnt)
{
  // TODO: alloc 'cnt' pages and return the head addr
  return NULL;
}

void __free_page(size_t ppn)
{
  // TODO: free the page whose page number is 'ppn'
}

void __page_remove(void* va)
{
  // TODO: the wrapper of pmap_page_remove
}

#endif // End of PLATFORM_HAS_PAGE;
