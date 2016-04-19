#ifndef	__MIMOSA_BSP_IO_H
#define __MIMOSA_BSP_IO_H
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

#include <drivers/console.h>
#include <bsp/cpu/mmio.h>
#include <error.h>

// memory IO operation
#define __readb(a)   mmio_readb(a)
#define __readw(a)   mmio_readw(a)
#define __readl(a)   \
  do { panic("__readl isn't supported by ATmega!"); } while(0);

#define __readnb(s,d,n)	mmio_rnb(s,d,n)
#define __readnw(s,d,n)	mmio_rnw(s,d,n)
#define __readnl(s,d,n)	\
  do { panic("__readnl isn't supported by ATmega!"); } while(0);

#define __writeb(a,x)	port_wb(a,x)
#define __writew(a,x)	port_ww(a,x)
#define __writel(a,x)	port_wl(a,x)

#define __writenb(d,s,n) port_wnb(d,s,n)
#define __writenw(d,s,n) port_wnw(d,s,n)
#define __writenl(d,s,n) port_wnl(d,s,n)

#define __get_frame_pointer() read_ebp()

// Video output
// TODO: display buffer
#define __VIDEO_BUFFER	CGA_DISP_BUF


#endif // End of __MIMOSA_BSP_IO_H;
