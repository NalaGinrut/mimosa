#ifndef	__MIMOSA_PC32_STDIO_H
#define __MIMOSA_PC32_STDIO_H
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
#include <drivers/console.h>

#define __BSP_PUT_CHAR__(ch) console_putc(ch)
//#define __BSP_GET_CHAR__() console_getc()

#endif // End of __MIMOSA_PC32_STDIO_H;
