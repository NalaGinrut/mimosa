#ifndef __MIMOSA_ERROR_H
#define __MIMOSA_ERROR_H
/*	
 *  Copyright (C) 2010-2012  
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
#include <retval.h>
#include <libkern.h>

#ifdef __KERN_DEBUG__
#include <debug/display.h>
// TODO: debug
#endif

#define panic(...)  _panic(__func__ ,__FILE__ ,__LINE__ ,__VA_ARGS__)
#define warn(...) _warn(__func__ ,__FILE__ ,__LINE__ ,__VA_ARGS__)

#define ASSERT_OUTFMT "Assert:\"%s\" failed!\n"

#define __assert_print(p) \
  panic(ASSERT_OUTFMT ,#p)

#define assert(p) \
  do{ if(!(p)) __assert_print(p); }while(0);

#define catch_then_do(p) \
  if(p) { warn(ASSERT_OUTFMT ,#p);

#define catch_else() }else{

#define catch_context_end() }

void _warn(const char* ,const char* ,int ,const char* ,...);
void _panic(const char* ,const char* ,int ,const char* ,...) no_return;

/* FIXME: This 'halt' is too naive. I need something like:
 *	  1. a monitor to show info
 *        2. a debugger server
 */
#define halt() while(1)

static void print_errmsg(retval rv);

#endif // End of __MIMOSA_ERROR_H;



