#ifndef	__MIMOSA_LOCK_H
#define __MIMOSA_LOCK_H
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


#include <atomic.h>

typedef enum Lock_Type
  {
    LOCK_SPIN ,
  }lock_type;

#define lock_spin_require(l ,o)	atomic_set_bit(l ,o)
#define lock_release(l ,o)	atomic_clear_bit(l ,o)

void lock_require(void *lock ,u32_t offset ,lock_type type);

#endif // End of __MIMOSA_LOCK_H;
