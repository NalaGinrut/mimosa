#ifndef	__MIMOSA_LIB_STDARG_H
#define __MIMOSA_LIB_STDARG_H
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


#include <types.h>
#include <bsp/stdarg.h>

typedef __va_list va_list;

#define va_size(type) __va_size(type)

#define va_start(ap ,last) __va_start(ap ,last)

#define va_arg(ap ,type) __va_arg(ap ,type)

#define va_copy(dest ,src) __va_copy(dest ,src)

#define va_end(ap) __va_end(ap)


#endif // End of __MIMOSA_LIB_STDARG_H;
