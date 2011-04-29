#ifndef	__MIMOSA_IO_H
#define __MIMOSA_IO_H
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

#include <bsp/bsp_io.h>

// port/memory IO operation
#define readb(a) __readb(a)
#define readw(a) __readw(a)
#define readl(a) __readl(a)

#define readnb(s,d,n)	__readnb(s,d,n)
#define readnw(s,d,n)	__readnw(s,d,n)
#define readnl(s,d,n)	__readnl(s,d,n)

#define writeb(a,x) __writeb(a,x)
#define writew(a,x) __writew(a,x)
#define writel(a,x) __writel(a,x)

#define writenb(d,s,n) __writenb(d,s,n)
#define writenw(d,s,n) __writenw(d,s,n)
#define writenl(d,s,n) __writenl(d,s,n)

// Video output
#define VIDEO_BUFFER	VIDEO_BUFFER

#endif // End of __MIMOSA_IO_H;
