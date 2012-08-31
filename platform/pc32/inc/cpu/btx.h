#ifndef	__MIMOSA_X86_CPU_BTX_H__
#define __MIMOSA_X86_CPU_BTX_H__
/*	
 *  Copyright (C) 2012  
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

#include "../bsp_types.h"

//			 X86_PAUSE				\

#define __set_bit_op(p ,o ,lock)				\
  do{								\
    __asm__ __volatile__("1: " lock "bts%z0 %0 ,%1\n\t"		\
			 "jnc 2f\n\t"				\
			 "jmp 1b\n\t"				\
			 "2: ret"				\
			 :"=r" (ptr)				\
			 :"0" (ptr) ,"Ir" (offset)		\
			 :"cc"					\
			 );					\
  }while(0);

#define __clear_bit_op(p ,o ,lock)				\
  do{								\
    __asm__ __volatile__(lock "btr%z0 %0 ,%1"			\
			 :"=r" (ptr)				\
			 :"0" (ptr) ,"Ir" (offset)		\
			 :"cc"					\
			 );					\
  }while(0);

#endif // End of __MIMOSA_X86_CPU_BTX_H__;
