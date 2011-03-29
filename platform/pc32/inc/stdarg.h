#ifndef	__PC32_STDARG_H
#define __PC32_STDARG_H
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

typedef	char* __va_list;

/*
 * Standard va types and macros
 */
#define	__va_size(type) \
	(((sizeof(type) + sizeof(s32_t) - 1) / sizeof(s32_t)) * sizeof(s32_t))


/* Provide a free-standing implementation */
#define __va_start(ap, last) \
	((ap) = (__va_list)&(last) + __va_size(last))
#define __va_arg(ap, type) \
	(*(type *)((ap) += __va_size(type), (ap) - __va_size(type)))
/* This assumes a typical stack machine */
#define __va_copy(dest, src) \
	((void)((dest) = (src)))
#define __va_end(ap) (ap = NULL)


#endif // End of __PC32_STDARG_H;
