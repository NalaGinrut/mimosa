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


#include <math.h>
#include <types.h>

inline u32_t gcd(u32_t a ,u32_t b)
{
  u32_t _c = 0;
  u32_t _a = MAX(a,b);
  u32_t _b = MIN(a,b);

  if( !_a || !_b )
    return 0;

  do{
    _c = _a%_b;
    _a = _b;
    _b = _c;
  }while(_c);
  
  return _a;
  
}


// We don't need a negtive gcd. It's my assumption.
inline u32_t sgcd(s32_t a ,s32_t b)
{
  u32_t _a = abs(a);
  u32_t _b = abs(b);
  
  return  gcd(_a ,_b);
}

inline u32_t abs(s32_t a)
{
  return a>=0? a : -a;
}
