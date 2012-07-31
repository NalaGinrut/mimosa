#ifndef __MIMOSA_PAGE_H__
#define __MIMOSA_PAGE_H__
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

#include <bsp/bsp_mm.h>

#ifdef __MM_HAS_PAGING__

#include <bsp/pmap.h>

struct Page* __alloc_page();
void __free_page(struct Page* pg);
void __page_remove(void* va);

#endif // End of __MM_HAS_PAGING__;

#endif // Enf of __MIMOSA_PAGE_H__;
