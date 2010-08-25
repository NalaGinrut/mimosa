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

// CPUID only for 486+ cpu!!!;


// CPUID instruction;
// P4+ support will add later......;
// and we don't support extended info now;
#define CI_486	0x01
#define CI_PRO	0x02
#define CI_P3	0x03
#define CI_P4	0x02

//===== cpuid version info definition;

//-- processor type -> p_type:
#define PT_OEM	0x00	// Intel Original OEM Processor;
#define PT_OD	0x01 	// Intel Over Drive Processor;
#define PT_DUAL	0x02	// Intel Dual Processor;
#define PT_RES	0x03	// Intel Reserved;
//--

// other fields means we will add after this kernel finish;
// anyway, cpuid is useful but not an emergency;

typedef union CPUID_EAX
{
  struct inner
  {
  stepping_id	:4;
  model		:4;
  family_id	:4;
  p_type	:2;
  reserved_1	:2;
  ex_model_id	:4;
  ex_family_id	:8;
  reserved_2	:4;
  }is; // inner structure;
  
  __u32_t all;
}cpuid_vi_t; // cupid version info returned from EAX;
 
//===== End of cpuid verion info;

//===== cpuid additional info;

//--- FIXME: add more later;

typedef union CPUID_EBX
{
  struct inner
  {
  brand_index	:8;
  cache_size	:8;
  local_ACPI	:8;
  reserved	:8;
  }is; // FIXME: should I use __u8_t instead of bit-field here?
  //would it be more efficient?

  __u32_t all;
}cpuid_ai_t; // cpuid additional info return from EBX;

//===== End of cpuid additional info from ECX;

//===== cpuid feature info;

typedef union CPUID_ECX
{
  struct inner
  {
  sse3		:1;
  pclmulqdq	:1;
  dtes64	:1;
  monitor	:1;
  ds_cpl	:1;
  vmx		:1;
  smx		:1;
  est		:1;
  tm2		:1;
  ssse3		:1;
  cnxt_id	:1;
  reserved_1	:1;
  fma		:1;
  cmpxchg16B	:1;
  x_tpr		:1;
  pdcm		:1;
  reserved_2	:2;
  dca		:1;
  sse4_1	:1;
  sse4_2	:1;
  x2_apic	:1;
  movbe		:1;
  popcnt	:1;
  reserved_3	:1;
  aes		:1;
  xsave		:1;
  osxsave	:1;
  avx		:1;
  reserved_4	:2;
  always_zero	:1; // NOTE: always zero!!!;
  }is;

  __u32_t all;
}cpuid_fic_t; // cpuid feature info returned from ECX;

//===== End of cpuid feature info from ECX;

//===== cpuid cpuid feature info from EDX
typedef union CPUID_EDX
{
  struct inner
  {
    //TODO: write them later......;
  }is;

  __u32_t all;
}cpuid_fid_t; // cpuid feature info returned from EDX

//===== End of cpuid feature info from EDX;


static __bool __inline__ cpuid_check(__u64_t flags);


static __bool __inline__ cpuid_check(__u64_t flags)
{
  
  //TODO: check cpu info if it has "flags" feature;
  // use gcc_asm implement it;
}





#endif // End of MIMOSA_CPUID_H;
