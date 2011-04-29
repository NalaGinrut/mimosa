#ifndef	__MIMOSA_DEBUG_H
#define __MIMOSA_DEBUG_H
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

/* online debug take advantage of serial port to debug kernel from another
 * machine. Not implemented yet.
 * TODO: Can we implement it with gdb-server or similar?
 */
//#define __KERN_ONLINE_DEBUG__

#include <debug/display.h>
#include <debug/trace.h>

#endif // End of __MIMOSA_DEBUG_H;
