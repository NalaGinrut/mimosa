#ifndef	__MIMOSA_PC32_STDARG_H
#define __MIMOSA_PC32_STDARG_H
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
