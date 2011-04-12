/* Copyleft(c) 2010 2011
 * HackerFellowship. All lefts reserved.
 
 * NalaGinrut <NalaGinrut@gmail.com>
 
 * May Lord Bless!Happy Hacking!
 
 * This program is free software;you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundataion;either version 2 of the License,or (at 
 * your option) any later version.
 
 * You should have read the GNU General Public License before start "RTFSC".
 
 * If not,see <http://www.gnu.org/licenses/>
 */


#include <math.h>
#include <types.h>

inline u32_t gcd(u32_t a ,u32_t b)
{
  u32_t c=0;
  u32_t _a = MAX(a,b);
  u32_t _b = MIN(a,b);

  do{
    c=_a%_b;
    _a=_b;
    _b=c;
  }while(c);
  
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
