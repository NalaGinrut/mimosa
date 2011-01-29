#ifndef __MIMOSA_SEGMENT_H
#define __MIMOSA_SEGMENT_H
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


#include "gdt.h"

// generate segmentation selection;
#define MAKE_SEL(idx)	(((idx)<<3) & 0xFFF8)

// global selector index;
#define NULL_SEG	0
#define	KCODE_SEG	1
#define KDATA_SEG	2
#define KSTCK_SEG	3
#define UCODE_SEG	4
#define UDATA_SEG	5
#define USTCK_SEG	6
#define TSS_SEG		7

#define NULL_SEL MAKE_SEL(NULL)
#define KC_SEL MAKE_SEL(KCODE_SEG)
#define KD_SEL MAKE_SEL(KDATA_SEG)
#define KS_SEL MAKE_SEL(KSTCK_SEG)
#define UC_SEL MAKE_SEL(UCODE_SEG)
#define UD_SEL MAKE_SEL(UDATA_SEG)
#define UK_SEL MAKE_SEL(USTCK_SEG)


// init a system segment descriptor;
// NOTE: use these init function at the END of the real seg_initilization!
#define SYS_SEG_INIT(sd)	\
  do{	 			\
    (sd).system = 0;		\
    (sd).type = 0;		\
    (sd).available = 0;		\
    (sd).db = 0;		\
    (sd).reserved = 0;		\
  }while(0);

#define CODE_SEG_INIT(sd)	\
  do{				\
    (sd).system = 1;		\
    (sd).type |= 0x8;		\
    (sd).reserved = 0;		\
  }while(0);

#define DATA_SEG_INIT(sd)	\
  do{				\
    (sd).system = 1;		\
    (sd).type &= 0x7;		\
    (sd).reserved = 0;		\
  }while(0);



#endif // End of __MIMOSA_SEGMENT_H;
