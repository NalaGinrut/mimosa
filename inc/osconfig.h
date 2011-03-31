#ifndef __OS_CONFIG_H
#define __OS_CONFIG_H
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

// Enable kernel debugger
#define __KERN_DEBUG__

// Enable ARCH 64bit address:
//#define MIMOSA_ADDRESS_64


#define __MULTI_BOOT__


/* FIXME:
 * it's a stupid handle, I'll fix it after conf-tools' ready.
 */
#define KERN_BASE	0xC0000000
#define FULL_ADDR	0xFFFFFFFF
#define PG_SHIFT	12
#define KERN_STACK_SIZE	4096

#endif // End of __OS_CONFIG_H;
