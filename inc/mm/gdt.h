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
	unsigned dpl : 3; // descriptor privilege level;
	unsigned present : 1; // segment present;
	unsigned available : 1; // available for software use;
	unsigned reserved : 1; // bit for reserved;
	unsigned db : 1; // D/B flag, 0 for 16bit, 1 for 32bit, more detail in IA-BOOK V3A 3-15;
	unsigned g : 1; // granularity, 0 for 1B per offset-limit, 1 for 4K per offset-limit;
}seg_des_t ,seg_des_tp;

#endif // End of ifdef MIMOSA_ADDRESS_64;

#endif // End of MIMOSA_GDT_H;
