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
