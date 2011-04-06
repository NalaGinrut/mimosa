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
#include <error.h>
#include <lock.h>

void lock_require(void *lock ,u32_t offset ,lock_type type)
{
  switch(type)
    {
    case LOCK_SPIN:
      lock_spin_require(lock ,offset);break;
    default:
      panic("invalid lock type!\n");
    }
}


  
  
