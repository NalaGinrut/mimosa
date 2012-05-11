#ifndef __MIMOSA_DEBUG_TRACE_H
#define __MIMOSA_DEBUG_TRACE_H
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


#include <retval.h>
#include <types.h>
#include <error.h>
#include <bsp/cpu/trap.h>

typedef struct Frame_Info
{
  //TODO: all info about frame, argc,args, others.....;
}frame_info_t;// should we need pass frame_info pointer to accelerate??

retval pcall_backtrace(frame_info_t fi ,u32_t back_count);  



#endif // End of __MIMOSA_DEBUG_TRACE_H;
