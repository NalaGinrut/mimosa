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

#include <debug/trace.h>
#include <types.h>
#include <retval.h>
#include <cpu.h>

// FIXME: we implement this backtrace for IA32-convention,
// but we need a generic trace frameworks. 
retval pcall_backtrace(frame_info_t fi ,u32_t dep_count)
{
  /*
  u32_t *frame=(u32_t*)get_frame_head();
  u8_t frame_head=0,return_ip=1,args=2;

  while(dep_count-- > 0)
    {
      kprintf("frame_head:%x\n"
	      "return_ip:%x\n"
	      "args:%x\n",
	      frame ,frame[return_ip] ,frame[args]);
      frame=(u32_t*)frame[frame_head];
    }
  */
  return OK;
}
