#ifdef USE_LIB_BITWISE
/*	
 *  Copyright (C) 2012,2016
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

#include <libkern.h>
#include <types.h>

/* Last Bit Counter
 * Inspired from http://www-graphics.stanford.edu/~seander/bithacks.html#IntegerLog
 * A bisect last bit search ,e.g:
 *	000110100 ==> 2
 *      876543210
 *
 * FIXME: the register reserved word for less-32bit CPU?
 */
u32_t lbc(u32_t v)
{
  register u32_t r; // result of log2(v) will go here
  register u32_t shift;

  r =     (v > 0xFFFF) << 4; v >>= r;
  shift = (v > 0xFF  ) << 3; v >>= shift; r |= shift;
  shift = (v > 0xF   ) << 2; v >>= shift; r |= shift;
  shift = (v > 0x3   ) << 1; v >>= shift; r |= shift;
  r |= (v >> 1);

  return r;
}

#endif // End of USE_LIB_BITWISE;
