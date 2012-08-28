#ifndef	__MIMOSA__KMALLOC_H
#define __MIMOSA__KMALLOC_H
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
#include <ds/rbtree.h>

#ifdef __MM_HAS_PAGING__
#include <mm/page.h>
#endif // End of __MM_HAS_PAGING__;

typedef struct kmalloc_info
{
  struct Page* current_page;
  size_t cur_page_rest_mem;
  spin_lock_t spin;
}kmalloc_info_t;

void* sbrk(size_t amount);
int brk(void *end_data_segment);

#endif // End of __MIMOSA__KMALLOC_H;
