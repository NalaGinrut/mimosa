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


#include <lock.h>
#include <types.h>
#include <mutex.h>
#include <lock.h>


void mutex_wait(mutex_t *mutex)
{
  mutex_t *m = mutex;

  // all mutex is spin type;
  lock_require(m ,0 ,LOCK_SPIN);
}

void mutex_signal(mutex_t *mutex)
{
  mutex_t *m = mutex;

  lock_release(m ,0);
}

/* NOTE: "mutex set" is a set of mutex. You can handle it with
 * 	 "offset" of a mutex_t;
 */ 
void mutex_set_wait(mutex_t *mutex_set ,u8_t offset)
{
  mutex_t *ms = mutex_set;

  lock_require(ms ,offset ,LOCK_SPIN);
}

void mutex_set_signal(mutex_t *mutex_set ,u8_t offset)
{
  mutex_t *ms = mutex_set;

  lock_release(ms ,offset);
}
