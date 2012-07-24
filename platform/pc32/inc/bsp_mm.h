#ifndef __MIMOSA_BSP_MM_H
#define __MIMOSA_BSP_MM_H
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
#include <drivers/nvram.h>
#include <global.h>
#include "cpu/paging.h"
#include "cpu/crx.h"
#include "cpu/gdt.h"
#include "cpu/segment.h"
#include "pmap.h"

// we declare these global bsp addr as u32_t,
// you should take them to addr by explicitly cast
extern char GET_BSP_VAR(VPT)[];
extern char GET_BSP_VAR(KSTKTOP)[];
extern char GET_BSP_VAR(ULIM)[];
extern char GET_BSP_VAR(UVPT)[];
extern char GET_BSP_VAR(UPAGES)[];
extern char GET_BSP_VAR(UENVS)[];
extern char GET_BSP_VAR(UTOP)[];
extern char GET_BSP_VAR(UXSTKTOP)[];
extern char GET_BSP_VAR(USTKTOP)[];
extern char GET_BSP_VAR(UTEXT)[];
extern char GET_BSP_VAR(UTEMP)[];
extern char GET_BSP_VAR(PFTEMP)[];
extern char GET_BSP_VAR(USTABDATA)[];

// paging mode defined here, you may change it as you wish and be careful ^_^
#define BSP_PG_MODE_ON CR0_PM|CR0_PG|CR0_AM|CR0_WP|CR0_NE|CR0_TS|CR0_EM|CR0_MP
#define BSP_PG_MODE_OFF CR0_TS|CR0_EM

#define __page_free pmap_page_free
#define __page_alloc pmap_page_alloc
#define __page_lookup pmap_page_lookup
#define __boot_pgdir pmap_get_tmp_pgdir()
				  
#endif // End of __MIMOSA_BSP_MM_H;

