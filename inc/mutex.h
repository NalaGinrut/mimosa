#ifndef	__MIMOSA_MUTEX_H
#define __MIMOSA_MUTEX_H
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

#include <types.h>
#include <lock.h>


// all mutex is spin type;
typedef u32_t mutex_t;

void mutex_wait(mutex_t *mutex);
void mutex_signal(mutex_t *mutex);

void mutex_set_wait(mutex_t *mutex ,u8_t offset);
void mutex_set_signal(mutex_t *mutex ,u8_t offset);

#endif // End of __MIMOSA_MUTEX_H;
