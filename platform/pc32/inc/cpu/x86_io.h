#ifndef __MIMOSA_PC32_X86_IO_H
#define __MIMOSA_PC32_X86_IO_H
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




#define KB_CON_DPORT	0x0060 // KB controller data port(r/w)
#define KB_CON_STAT	0x0064 // KB controller status(r);
#define KB_CON_INBUF	0X0064 // KB controller input buffer(w);

#define KB_BUSY		0x02
#define KB_WRITE	0xd1 // set KB_CON_DPORT write control;
#define A20_EN		0xdf



#endif // End of MIMOSA_X86_IO_H;
