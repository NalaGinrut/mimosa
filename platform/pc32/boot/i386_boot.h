#ifndef __MIMOSA_I386_BOOT_H
#define __MIMOSA_I386_BOOT_H
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



// These gdt index is one-touch vars, after bootup they are useless;
// And if you gonnar change them, don't forget they are aligned to 8-Bytes;
#define PM_CS	0x8	/* code segment selector
			 * NOTE: can't be 0! for 0 is NULL descriptor!
			 */
#define PM_DS 	0x10	// data segment selector


// A20
#define KB_CON_STAT	0x64
#define KB_IS_BUSY	0x02
#define KB_WRITE	0xd1
#define KB_CON_INBUF	0x64
#define A20_EN		0xdf
#define KB_CON_DPORT	0x6
#define CR0_PM	0x01

#endif // End of __MIMOSA_I386_BOOT_H;
