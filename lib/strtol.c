/*	
 *  Copyright (C) 2012
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

// FIXME: well, this is a ugly implementation, I'll write a better one later.
long strtol(const char *s ,char **endptr ,int base)
{
  int neg = 0;
  long val = 0;

  // gobble initial whitespace
  while(*s == ' ' || *s == '\t')
    s++;

  // plus/minus sign
  if(*s == '+')
    s++;
  else if(*s == '-')
    s++, neg = 1;

  // hex or octal base prefix
  if((base == 0 || base == 16) && (s[0] == '0' && s[1] == 'x'))
    s += 2, base = 16;
  else if(base == 0 && s[0] == '0')
    s++, base = 8;
  else if(base == 0)
    base = 10;

  // digits
  while(1)
    {
      int dig;

      if(*s >= '0' && *s <= '9')
	dig = *s - '0';
      else if(*s >= 'a' && *s <= 'z')
	dig = *s - 'a' + 10;
      else if(*s >= 'A' && *s <= 'Z')
	dig = *s - 'A' + 10;
      else
	break;
      if (dig >= base)
	break;
      s++, val = (val * base) + dig;
      // we don't properly detect overflow!
    }

  if(endptr)
    *endptr = (char *) s;

  return (neg ? -val : val);
}

