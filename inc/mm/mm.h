#ifndef	__MIMOSA__MM_H
#define __MIMOSA__MM_H
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
#include <bits.h>
#include <ds/rbtree.h>

#ifdef __MM_HAS_PAGING__
#include <mm/page.h>
#endif // End of __MM_HAS_PAGING__;

#define KMAP_CROSS_SEG	_B(0)

typedef struct kmap
{
  struct rb_node rb_node;
  void*	addr;  // head address
  u32_t size;
  u32_t flags;
} *kmap_t;

typedef struct kmap_table
{
  struct rb_root rb_root;
  kmap_t kmap;
  // spin_lock_t spin;
} *kmap_table_t;

void *kmalloc(size_t size);


#endif // End of __MIMOSA__MM_H;
