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

#include <types.h>
#include <io.h>
#include <debug/display.h>

void msg_print(const char *str)
{
  write_string(0x0C ,str);
}

void write_string(int colour, const char *string)
{
  u16_t wc;
  while(*string != '\0')
    {
      wc = (*string|colour<<8);
      cga_putc(wc);
      string++;
    }
}
