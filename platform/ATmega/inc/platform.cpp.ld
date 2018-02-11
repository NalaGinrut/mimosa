#ifndef __MIMOSA_ATMEGA_PLATFORM_CPP_LD
#define __MIMOSA_ATMEGA_PLATFORM_CPP_LD
/*	
 *  Copyright (C) 2016
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


/* This ld script used for kernel linking. 
 * Modify it may effect the whole kernel framework, so DON'T MODIFY IT!!!
 */

#include <generic/generic.ld.h>
#include <global.h>

#undef KERN_BASE
#define KERN_BASE 0x0000
#undef KERNEL_BEGIN
#define KERNEL_BEGIN 0x0000
#undef ALIGN_SIZE
#define ALIGN_SIZE 4
#undef PG_SIZE
#define PG_SIZE 32

#define BSP_SPECFIC_SECTION                                     \
        PROVIDE(bsp_begin = .);                            \
        *(eeprom fuse lock signature user_signatures);          \
        PROVIDE(bsp_end = .);
        

#endif // End of __MIMOSA_ATMEGA_PLATFORM_CPP_LD
