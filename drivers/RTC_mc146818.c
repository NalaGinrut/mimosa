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


#include <drivers/RTC_mc146818.h>
#include <types.h>
#include <io.h>

u32_t mc146818_read_byte(u32_t index)
{
	writeb(RTC_PORT ,index);
	return readb(RTC_PORT+1);
}

void mc146818_write_byte(u32_t index ,int data)
{
	writeb(RTC_PORT ,index);
	writeb(RTC_PORT+1 ,data);
}

