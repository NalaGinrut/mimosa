#ifndef	__MIMOSA_LIB_STDARG_H
#define __MIMOSA_LIB_STDARG_H
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


#include <types.h>
#include <now/stdarg.h>

typedef __va_list va_list;

#define va_size(type) __va_size(type)

#define va_start(ap ,last) __va_start(ap ,last)

#define va_arg(ap ,type) __va_arg(ap ,type)

#define va_copy(dest ,src) __va_copy(dest ,src)

#define va_end(ap) __va_end(ap)


#endif // End of __MIMOSA_LIB_STDARG_H;
