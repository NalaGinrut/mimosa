#ifndef __MIMOSA_GENERIC_LD_H
#define __MIMOSA_GENERIC_LD_H
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

#include <osconfig.h>
#include <global.h>

/* Align . to 8, it's maximum function alignment */
#define ALIGN_FUNC()	. = ALIGN(ALIGN_SIZE)

#define DATA_SECTION		\
	*(.data)		

#define TEXT_SECTION				\
	ALIGN_FUNC();				\
	*(.text)				\
	*(.stub .text.* .gnu.linkonce.t.*)

#define BSS_SECTION			\
	PROVIDE(__bss_start = .);	\
	*(.bss)		      		\
	PROVIDE(__bss_end = .);

#define STAB_SECTION			\
	PROVIDE(__STAB_BEGIN__ = .);	\
	*(.stab);	       	 	\
	PROVIDE(__STAB_END__ = .);	\
	
#define STABSTR_SECTION			\
	PROVIDE(__STABSTR_BEGIN__ = .);	\
	*(.stabstr);		    	\
	PROVIDE(__STABSTR_END__ = .);	

#define MK_RODATA(align)		\
	. = ALIGN((align));		\
	.rodata : {			\
		*(.rodata)		\
		*(.rodata.*)		\
		*(.gnu.linkonce.r.*)	\
	}  
	
#define RO_DATA	MK_RODATA(PG_SIZE)


#endif 
