#ifndef	__MIMOSA_LIB_KERNEL_H
#define __MIMOSA_LIB_KERNEL_H
/*	
 *  Copyright (C) 2010-2011  
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
#include <stdio.h>
#include <stdarg.h>
#include <osconfig.h>

#define MAX_STRING_LEN 256

char *strndup(const char *str ,size_t n);
size_t strnlen(const char *str ,size_t n);
char *strncat(char *dest ,const char *src ,size_t n);
char *strncpy(char *dest ,const char *src ,size_t n);
int strncmp(const char *p ,const char *q ,size_t n);
char *strchr(void const *str ,int c_in);
long strtol(const char *s ,char **endptr ,int base);

void *memcpy (void *dest ,void const *src ,size_t n);
void *memset(void *str, int c ,size_t n);
void *memchr(void const *str ,int c_in ,size_t n);
void *memmove(void *dest ,void const *src ,size_t n);

u32_t fbc(u32_t v);

int cprintf(const char *format ,...);
int vcprintf(const char *fmt ,va_list ap);
char *read_line(const char *prompt);

static inline char getchar()	{ return __GET_CHAR__(); }
static inline void putchar(char ch)	{ return __PUT_CHAR__(ch); }

#endif // End of __MIMOSA_LIB_KERNEL_H;
