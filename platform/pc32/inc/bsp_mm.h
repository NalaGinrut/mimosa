#ifndef __MIMOSA_BSP_MM_H
#define __MIMOSA_BSP_MM_H
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
#include <drivers/nvram.h>
#include <global.h>
#include "cpu/paging.h"
#include "cpu/crx.h"
#include "cpu/gdt.h"
#include "cpu/segment.h"

/* handle paging mode */
#ifdef PG_SIZE
#define PTX_SHIFT PG_SHIFT
#define PDX_SHIFT 22
#endif // End of PG_SIZE;

typedef __laddr_t laddr_t;
typedef __pde_t pde_t;
typedef __pte_t pte_t;

// page number field of address
#define PPN(la)		(((laddr_t)(la)) >> PTX_SHIFT)
#define VPN(la)		PPN(la)		// used to index into vpt[]

// page directory index
#define PDX(la)		((((laddr_t)(la)) >> PDX_SHIFT) & 0x3FF)
#define VPD(la)		PDX(la)		// used to index into vpd[]

// page table index
#define PTX(la)		((((laddr_t)(la)) >> PTX_SHIFT) & 0x3FF)

// offset in page
#define PGOFF(la)	(((laddr_t)(la)) & 0xFFF)

// next pte addr in pte
#define PTA(pte)	((laddr_t)(pte) & ~0xFFF)

// construct linear address from indexes and offset
#define PGADDR(d, t, o)	((void*) ((d) << PDX_SHIFT | (t) << PTX_SHIFT | (o)))

// we declare these global bsp addr as u32_t,
// you should take them to addr by explicitly cast
extern u32_t GET_BSP_VAR(VPT);
extern u32_t GET_BSP_VAR(KSTKTOP);
extern u32_t GET_BSP_VAR(ULIM);
extern u32_t GET_BSP_VAR(UVPT);
extern u32_t GET_BSP_VAR(UPAGES);
extern u32_t GET_BSP_VAR(UENVS);
extern u32_t GET_BSP_VAR(UTOP);
extern u32_t GET_BSP_VAR(UXSTKTOP);
extern u32_t GET_BSP_VAR(USTKTOP);
extern u32_t GET_BSP_VAR(UTEXT);
extern u32_t GET_BSP_VAR(UTEMP);
extern u32_t GET_BSP_VAR(PFTEMP);
extern u32_t GET_BSP_VAR(USTABDATA);


#endif // End of __MIMOSA_BSP_MM_H;

