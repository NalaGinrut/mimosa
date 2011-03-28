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

#include <libkern.h>
#include <types.h>

#define __STRNCMP_GET_DIFF(s1 ,s2)	\
  ((int)((u8_t) *s1 - (u8_t) *s2))

int strncmp(const char *s1, const char *s2, size_t n)
{
  size_t len1 = 0;
  size_t len2 = 0;
  size_t max = 0;
  size_t len = 0;

  max = (n > MAX_STRING_LEN) ? MAX_STRING_LEN : n;
  len1 = strnlen(s1 ,max);
  len2 = strnlen(s2 ,max);
  len = (len1 > len2) ? len1 : len2; // get larger length; 

  while(len-- > 0 &&
	*s1++ == *s2++)
    ;;;

  // both zero if larger length equal to zero;
  if(len == 0)
    return 0;

  return __STRNCMP_GET_DIFF(s1 ,s2) > 0 ? 1 : -1;
      
}
