#ifdef USE_LIB_PRINTF
/*	
 *  Copyright (C) 2010-2012,2016
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

#include <types.h>
#include <error.h>
#include <retval.h>
#include <libkern.h>
#include <stdarg.h>

#ifdef __KERN_DEBUG__
#define kprintf cprintf
#else
#define kprintf
#endif // End of __KERN_DEBUG__

char *retval_string[20] =
  {
    "invalid size",
  };

#define retval_msg(r)	\
  retval_string[((r)&0xfff)]


static void print_errmsg(retval rv)
{
  kprintf("Errno %d - %s" ,rv ,retval_msg(rv));
}

void _panic(const char* func ,const char *file ,int line ,const char *fmt ,...)
{
  va_list ap;

  va_start(ap ,fmt);
  cprintf("kernel panic at %s:%d - %s\n" ,file ,line ,func);
  vcprintf(fmt ,ap);
  cprintf("\n");
  va_end(ap);

  halt();
}

void _warn(const char* func ,const char *file ,int line ,const char *fmt ,...)
{	
  va_list ap;

  va_start(ap ,fmt);
  cprintf("kernel warning at %s:%d called by %s\n" ,file ,line ,func);
  vcprintf(fmt ,ap);
  cprintf("\n");
  va_end(ap);
}



// static_assert(x) will generate a compile-time error if 'x' is false.
//#define static_assert(x)	switch (x) cas

#endif // End of USE_LIB_PRINTF;
