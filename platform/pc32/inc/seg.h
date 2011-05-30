#ifndef	__MIMOSA_PC32_SEG_H
#define __MIMOSA_PC32_SEG_H
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
#include <global.h>
#include <osconfig.h>
#include <bsp/bsp_mm.h>

extern inner_seg_desc_t GET_GLOBAL_VAR(gdt[]);
extern struct gdt_pseudo_desc GET_GLOBAL_VAR(gdt_pd);



#endif // End of __MIMOSA_PC32_SEG_H;
