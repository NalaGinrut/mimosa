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
#include <global.h>
#include <bsp/seg.h>
#include "inc/cpu/segment.h"
#include "inc/cpu/gdt.h"

/* all descriptors of segment;
 * SEG: type ,base ,lim 
 *	dpl ,syetem ,present ,available
 *	reserved ,op-size ,granularity
 */
#define KCODE_DEC SEG(USEG_X | USEG_R ,0x0 ,FULL_ADDR,			\
		      DPL_RING0 ,SEG_UNIV ,SEG_PRESENT ,SEG_AVAIL,	\
		      SEG_RES ,SEG_32BIT ,SEG_G4K)

#define KDATA_DEC SEG(USEG_W ,0x0 ,FULL_ADDR,				\
		      DPL_RING0 ,SEG_UNIV ,SEG_PRESENT ,SEG_AVAIL,	\
		      SEG_RES ,SEG_32BIT ,SEG_G4K)

#define UCODE_DEC SEG(USEG_X | USEG_R ,0x0 ,FULL_ADDR,			\
		      DPL_RING3 ,SEG_UNIV ,SEG_PRESENT ,SEG_AVAIL,	\
		      SEG_RES ,SEG_32BIT ,SEG_G4K)

#define UDATA_DEC SEG(USEG_W ,0x0 ,FULL_ADDR,				\
		      DPL_RING3 ,SEG_UNIV ,SEG_PRESENT ,SEG_AVAIL,	\
		      SEG_RES ,SEG_32BIT ,SEG_G4K)

// KSTACK and USTACK will come later




// Global descriptor table.
//
// The kernel and user segments are identical (except for the DPL).
// To load the SS register, the CPL must equal the DPL.  Thus,
// we must duplicate the segments for the user and the kernel.
//
// FIXME: inner_seg_desc_t is obsolete ,change it to seg_des_t
inner_seg_desc_t MK_GLOBAL_VAR(gdt[]) =
  {
    // unused (always faults -- for trapping NULL far pointers)
    [NULL_SEG] = SEG_NULL,
    
    // code segment
    [KCODE_SEG] = KCODE_DEC,

    // kernel data segment
    [KDATA_SEG] = KDATA_DEC,

    // user code segment
    [UCODE_SEG] = UCODE_DEC,

    // user data segment
    [UDATA_SEG] = UDATA_DEC,

    // tss, initialized in idt_init()
    [TSS_SEG] = SEG_NULL
  };

struct gdt_pseudo_desc MK_GLOBAL_VAR(gdt_pd) = 
  {
    sizeof(GET_GLOBAL_VAR(gdt)) - 1 ,(u32_t)GET_GLOBAL_VAR(gdt)
  };


	      
