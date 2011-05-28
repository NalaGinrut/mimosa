#ifndef __MIMOSA_PC32_SEGMENT_H
#define __MIMOSA_PC32_SEGMENT_H
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


#include "gdt.h"

// generate segmentation selection;
#define MAKE_SEL(idx)	(((idx)<<3) & 0xFFF8)

// global selector index;
#define NULL_SEG	0
#define	KCODE_SEG	1
#define KDATA_SEG	2
#define UCODE_SEG	3
#define UDATA_SEG	4
#define TSS_SEG		5
#define KSTCK_SEG	6
#define USTCK_SEG	7

#define NULL_SEL MAKE_SEL(NULL)
#define KC_SEL MAKE_SEL(KCODE_SEG)
#define KD_SEL MAKE_SEL(KDATA_SEG)
#define KS_SEL MAKE_SEL(KSTCK_SEG)
#define UC_SEL MAKE_SEL(UCODE_SEG)
#define UD_SEL MAKE_SEL(UDATA_SEG)
#define UK_SEL MAKE_SEL(USTCK_SEG)


#ifndef __ASSEMBLER__
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

#endif // !__ASSEMBLER__

// universal segment type
#define USEG_X		0x8	    // Executable segment
#define USEG_E		0x4	    // Expand down (non-executable segments)
#define USEG_C		0x4	    // Conforming code segment (executable only)
#define USEG_W		0x2	    // Writeable (non-executable segments)
#define USEG_R		0x2	    // Readable (executable segments)
#define USEG_A		0x1	    // Accessed

// Special segment type
#define SSEG_T16A	0x1	    // Available 16-bit TSS
#define SSEG_LDT	0x2	    // Local Descriptor Table
#define SSEG_T16B	0x3	    // Busy 16-bit TSS
#define SSEG_CG16	0x4	    // 16-bit Call Gate
#define SSEG_TG		0x5	    // Task Gate / Coum Transmitions
#define SSEG_IG16	0x6	    // 16-bit Interrupt Gate
#define SSEG_TG16	0x7	    // 16-bit Trap Gate
#define SSEG_T32A	0x9	    // Available 32-bit TSS
#define SSEG_T32B	0xB	    // Busy 32-bit TSS
#define SSEG_CG32	0xC	    // 32-bit Call Gate
#define SSEG_IG32	0xE	    // 32-bit Interrupt Gate
#define SSEG_TG32	0xF	    // 32-bit Trap Gate


#define SEG_RING3	0x3
#define SEG_RING0	0x0	    // DO NOT SUPPORT RING2 AND RING1!!!

#define SEG_SYSTEM	0x0
#define SEG_UNIV	0x1	    // code or data

#define SEG_AVAIL	0x0	    // available

#define SEG_RES		0x0	    // reserved

#define SEG_PRESENT	0x1	    // present
#define SEG_NOTPRES	0x0	    // not present

#define SEG_16BIT	0x0		
#define SEG_32BIT	0x1

#define SEG_G4K		0x1	    // granularity is 4K
#define SEG_GULIM	0x0	    // granularity is unlimited (constrained by seg_limit)
	

#endif // End of __MIMOSA_PC32_SEGMENT_H;
