#ifndef	__MIMOSA_ATOMIC_H
#define __MIMOSA_ATOMIC_H
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


#include <bsp/bsp_atomic.h>

#define atomic_set_bit(p ,o)	__atomic_set_bit(p ,o)
#define atomic_clear_bit(p ,o)	__atomic_clear_bit(p ,o)
#define atomic_cmpxchg(p ,o ,n) __atomic_cmpxchg(p ,o ,n)
#define atomic_xchg(p ,v)	__atomic_xchg(p ,v)
#define atomic_set_u32(p ,u32)	__atomic_set_u32(p ,u32) 

#endif // End of __MIMOSA_ATOMIC_H;
