#ifdef USE_LIB_READLINE
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

#include <osconfig.h>
#include <libkern.h>
#include <error.h>
#include <types.h>
#include <stdio.h>

#define READ_LINE_BUFLEN 1024
static char buf[READ_LINE_BUFLEN];

#ifdef __KERN_DEBUG__
static char *read_line_polling(const char *prompt);
#else
static char *read_line_interrupt(const char *prompt);
#endif 

char *read_line(const char *prompt)
{
  if(!prompt)
    return NULL;
  
  // TODO: define stdout port and puts(str ,port)

#ifdef __KERN_DEBUG__
  return read_line_polling(prompt);
#else
  return read_line_interrupt(prompt);
#endif
}

#ifdef __KERN_DEBUG__
static char *read_line_polling(const char *prompt)
{

  int i, c, echoing;

  if(prompt != NULL)
    cprintf("%s" ,prompt);

  i = 0;
  echoing = iscons(0);
  
  while(1)
    {
      c = __GET_CHAR__();
      if(c < 0)
	{
	  cprintf("read error: %e\n", c);
	  return NULL;
	}
      else if(c >= ' ' && i < READ_LINE_BUFLEN-1)
	{
	  if (echoing)
	    __PUT_CHAR__(c);
	  buf[i++] = c;
	}
      else if(c == '\b' && i > 0)
	{
	  if(echoing)
	    __PUT_CHAR__(c);
	  i--;
	}
      else if(c == '\n' || c == '\r')
	{
	  if(echoing)
	    __PUT_CHAR__(c);
	  buf[i] = 0;
	  return buf;
	}
    }

  return NULL;
}
#else
static char *read_line_interrupt(const char *prompt)
{
  panic("read_line_interrupt didn't finish");
  return NULL;
}
#endif // End of __KERN_DEBUG__;

#endif // End of USE_LIB_READLINE;
