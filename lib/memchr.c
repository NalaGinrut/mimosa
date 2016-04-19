#ifdef USE_LIB_MEMCHR
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

#include <libkern.h>
#include <types.h>

void *memchr(void const *str ,int c_in ,size_t n)
{

  const unsigned char *char_ptr;
  const longword *longword_ptr;
  longword repeated_one;
  longword repeated_c;
  register char c;

  c = (unsigned char) c_in;

  for (char_ptr = (const unsigned char *) str;
       n > 0 && (size_t) char_ptr % sizeof (longword) != 0;
       --n, ++char_ptr)
    if (*char_ptr == c)
      return (void *) char_ptr;

  longword_ptr = (const longword *) char_ptr;

  repeated_one = 0x01010101;
  repeated_c = c | (c << 8);
  repeated_c |= repeated_c << 16;
  if (0xffffffffU < (longword) -1)
    {
      repeated_one |= repeated_one << 31 << 1;
      repeated_c |= repeated_c << 31 << 1;
      if (8 < sizeof (longword))
        {
          size_t i;

          for (i = 64; i < sizeof (longword) * 8; i *= 2)
            {
              repeated_one |= repeated_one << i;
              repeated_c |= repeated_c << i;
            }
        }
    }

  while (n >= sizeof (longword))
    {
      longword longword1 = *longword_ptr ^ repeated_c;
      longword key = (longword1 - repeated_one) & (repeated_one << 7);

      if ( key )
        break;

      longword_ptr++;
      n -= sizeof (longword);
    }

  char_ptr = (const unsigned char *) longword_ptr;

  for (; n > 0; --n, ++char_ptr)
    {
      if (*char_ptr == c)
        return (void *) char_ptr;
    }

  return NULL;
}

#endif // End of USE_LIB_MEMCHR;
