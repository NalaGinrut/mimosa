#ifndef MIMOSA_CPUID_H
#define MIMOSA_CPUID_H
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


#include "bsp_types.h"

// CPUINFO only for 486+ cpu!!!;


// CPUINFO instruction;
#define CI_486	0x01
#define CI_PRO	0x02
#define CI_P3	0x03
#define CI_P4	0x02

static __bool __inline__ cpuid_check(__u64_t flags);


static __bool __inline__ cpuid_check(__u64_t flags)
{
  
  
}





#endif // End of MIMOSA_CPUID_H;
