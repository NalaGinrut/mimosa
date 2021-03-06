#ifndef	__MIMOSA_LOCK_H
#define __MIMOSA_LOCK_H
/*	
 *  Copyright (C) 2010-2011,2016
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

#include <types.h>
#include <atomic.h>

typedef enum Lock_Type
  {
    LOCK_SPIN ,
  }lock_type;

#define lock_spin_require(l ,o)	atomic_set_bit(l ,o)
#define lock_release(l ,o)	atomic_clear_bit(l ,o)

void lock_require(void *lock ,off_t offset ,lock_type type);

#endif // End of __MIMOSA_LOCK_H;
