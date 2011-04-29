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
