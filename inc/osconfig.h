#ifndef __OS_CONFIG_H
#define __OS_CONFIG_H
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
#define PG_SHIFT		12
#define PG_SIZE		4096
#define ADDR_BITS	32
#define KERN_STACK_SIZE	4096

#endif // End of __OS_CONFIG_H;
