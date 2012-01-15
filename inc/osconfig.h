#ifndef __OS_CONFIG_H
#define __OS_CONFIG_H
/*	
 *  Copyright (C) 2010-2012  
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

/* NOTE: DON'T TOUCH THIS FILE YOURSELF!
 *       This file should be auto-generated by conf-tools which hasn't been finished!
 */

// Enable kernel debugger
#define __KERN_DEBUG__

// Enable ARCH 64bit address:
//#define MIMOSA_ADDRESS_64


#define __MULTI_BOOT__

#define __BIT32_PAGING__
#define __BIT32_PAGING_NO_PSE__

/* FIXME:
 * it's a stupid handle, I'll fix it after conf-tools' ready.
 */
#define MIMOSA_BSP	"pc32"
#define KERN_BASE	0xC0000000
#define FULL_ADDR	0xFFFFFFFF
/* NOTE: 0x100000 is the loading offset ,it must be generated by 'genconf'.
 * You'd better not write it yourself.
 */
#define KERNEL_BEGIN	0xC0100000
#define KERNEL_STACK_SIZE 4096

#define PG_SHIFT	12
#define PG_SIZE		4096
#define PT_ENTRIES	1024
#define PT_SIZE		(PG_SIZE * PT_ENTRIES)
#define PD_SIZE		PT_SIZE		// actually, they are same
#define ADDR_BITS	32
#define KERN_STACK_SIZE	4096
#define MEM_HOLE_END	0x100000	// end of memory hole for well known historical reason.
#define IO_PHY_MEM	0xA0000		// IO mem start

/* how many bytes you need map in boot tmp map.
 * mimosa will map all available kernel space in debug mode.
 */
#ifdef __KERN_DEBUG__
#define KERN_TMP_MAP_SIZE (FULL_ADDR - KERN_BASE + 1)
#else
#define KERN_TMP_MAP_SIZE PT_SIZE
#endif // End of __KERN_DEBUG__;

#endif // End of __OS_CONFIG_H;
