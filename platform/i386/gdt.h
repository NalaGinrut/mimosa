/* Copyleft(c)2010 HackerFellowship. All lefts reserved.
  
 * NalaGinrut <NalaGinrut@gmail.com>
  
 * May Lord Bless!Happy Hacking!
  
 * This program is free software;you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundataion;either version 2 of the License,or (at 
 * your option) any later version.
  
 * You should have read the GNU General Public License before start "RTFSC".
  
 * If not,see <http://www.gnu.org/licenses/>
 */

#ifndef MIMOSA_GDT_H
#define MIMOSA_GDT_H

#include "mm/mmu.h"
#include "types.h"



#ifdef MIMOSA_ADDRESS_64
//TODO: code for 64bit address;

#else // code for 32bit address;
 
typedef struct SEG_DESC
{
	unsigned base : 32; // segment base address;
	unsigned limit : 20; // segment offset limit;
	unsigned type : 4; // segment type;
	unsigned system : 1; // 0 for system, 1 for application;
	unsigned dpl : 2; // descriptor privilege level;
	unsigned present : 1; // segment present;
	unsigned available : 1; // available for software use;
	unsigned reserved : 1; // bit for reserved;
	unsigned db : 1; // D/B flag, 0 for 16bit, 1 for 32bit, more detail in IA-BOOK V3A 3-15;
	unsigned g : 1; // granularity, 0 for 1B per offset-limit, 1 for 4K per offset-limit;
}seg_des_t ,seg_des_tp;

#include <inc/types.h>

// Segment Descriptors
struct Inner_Seg_Desc {
	unsigned sd_lim_15_0 : 16;  // Low bits of segment limit
	unsigned sd_base_15_0 : 16; // Low bits of segment base address
	unsigned sd_base_23_16 : 8; // Middle bits of segment base address
	unsigned sd_type : 4;       // Segment type (see STS_ constants)
	unsigned sd_s : 1;          // 0 = system, 1 = application
	unsigned sd_dpl : 2;        // Descriptor Privilege Level
	unsigned sd_p : 1;          // Present
	unsigned sd_lim_19_16 : 4;  // High bits of segment limit
	unsigned sd_avl : 1;        // Unused (available for software use)
	unsigned sd_rsv1 : 1;       // Reserved
	unsigned sd_db : 1;         // 0 = 16-bit segment, 1 = 32-bit segment
	unsigned sd_g : 1;          // Granularity: limit scaled by 4K when set
	unsigned sd_base_31_24 : 8; // High bits of segment base address
}inner_seg_desc_;

// Null segment
#define SEG_NULL	(struct Segdesc){ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
// Segment that is loadable but faults when used
#define SEG_FAULT	(struct Segdesc){ 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0 }



// functions:
static __inline__ 
inner_seg_desc_t SEG_DESC_FIX(set_des_t sd)
{    
	return SEG(sd.type ,
		   sd.base ,
		   sd.lim ,
		   sd.dpl ,
		   sd.system ,
		   sd.present ,
		   sd.available ,
		   sd.reserved ,
		   sd.db ,
		   sd.g);
}




#endif // End of ifdef MIMOSA_ADDRESS_64;






#endif // End of MIMOSA_GDT_H;
