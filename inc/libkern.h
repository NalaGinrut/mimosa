#ifndef	__MIMOSA_LIB_KERNEL_H
#define __MIMOSA_LIB_KERNEL_H
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

#include <types.h>
#include <stdarg.h>
#include <osconfig.h>

#define MAX_STRING_LEN 256

#ifdef USE_LIB_STRNDUP
char *strndup(const char *str ,size_t n);
#endif

#ifdef USE_LIB_STRNLEN
size_t strnlen(const char *str ,size_t n);
#endif

#ifdef USE_LIB_STRNCAT
char *strncat(char *dest ,const char *src ,size_t n);
#endif

#ifdef USE_LIB_STRNCPY
char *strncpy(char *dest ,const char *src ,size_t n);
#endif

#ifdef USE_LIB_STRNCMP
int strncmp(const char *p ,const char *q ,size_t n);
#endif

#ifdef USE_LIB_STRCHR
char *strchr(void const *str ,int c_in);
#endif

#ifdef USE_LIB_STRTOL
long strtol(const char *s ,char **endptr ,int base);
#endif

#ifdef USE_LIB_MEMCPY
void *memcpy (void *dest ,void const *src ,size_t n);
#endif

#ifdef USE_LIB_MEMSET
void *memset(void *str, int c ,size_t n);
#endif

#ifdef USE_LIB_MEMCHR
void *memchr(void const *str ,int c_in ,size_t n);
#endif

#ifdef USE_LIB_MEMMOVE
void *memmove(void *dest ,void const *src ,size_t n);
#endif

#ifdef USE_LIB_BITWISE
u32_t lbc(u32_t v);
#endif

#ifdef USE_LIB_PRINTF
int cprintf(const char *format ,...);
int vcprintf(const char *fmt ,va_list ap);
#endif

#ifdef USE_LIB_READLINE
char *read_line(const char *prompt);
#endif

#endif // End of __MIMOSA_LIB_KERNEL_H;
