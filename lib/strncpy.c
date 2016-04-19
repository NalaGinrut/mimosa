#ifdef USE_LIB_STRNCPY
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

#endif // End of USE_LIB_STRNCPY;
