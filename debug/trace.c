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

#include "debug/trace.h"
#include "types.h"
#include "error.h"
#include "cpu.h"

// FIXME: we implement this backtrace for IA32-convention,
// but we need a generic trace frameworks. 
err_t pcall_backtrace(frame_info fi ,u32_t dep_count)
{
  u32_t *frame=get_frame_head();
  u8_t frame_head=0,return_ip=1,args=2;

  while(dep_count-- > 0)
    {
      cprintf("frame_head:%x\n"
	      "return_ip:%x\n"
	      "args:%x\n"
	      frame,frame[return_ip],frame[args]);
      frame=frame[frame_head];
    }

  return OK;
}
