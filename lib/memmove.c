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

void *memmove(void *dest ,void const *src ,size_t n)
{
  char *d = dest;
  char const *s = src;

  if (s < d)
    {
      /* Moving from low mem to hi mem; start at end.  */
      for (s += n, d += n; n; --n)
	*--d = *--s;
    }
  else if (s != d)
    {
      /* Moving from hi mem to low mem; start at beginning.  */
      while(--n)
        *d++ = *s++;
    }

  return d;
}
