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

char *strncpy(char *dest, const char *src, size_t n) 
{
  size_t i = 0;
  char *ret;

  ret = dest;

  while(i++ < n)
    {
      *dest++ = *src;

      if (*src != '\0')
	src++;
    }
  
  return ret;
}
