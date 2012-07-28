#ifndef __MIMOSA_BITS_H
#define __MIMOSA_BITS_H
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


// This file used for handling bits operation;


#include <bsp/bsp_bits.h>

/* Most of things here are included in "bsp_bits.h",
 * others coming soon...
 */

#ifdef _E
#undef _E
#endif
#define _E(x)	(-(0xE000 + x))

#ifdef __BIT
#undef __BIT
#endif
#define __BIT	(1UL)

// shift the value "x" to "b" bits;
#ifdef _S
#undef _S
#endif
#define _S(x,b)		((x)<<(b))

#ifdef _B
#undef _B
#endif
#define _B(b)		(__BIT<<(b))

#endif // End of __MIMOSA_BITS_H;
