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

/* NOTE:
 * These strop lib functions is useless if you don't want to parse strings.
 * Use them if and only if you need kshell for debugging and inner-scheme-repl.
 */
#ifdef __MIMOSA_LIB_STROP__
// ctype definition
static inline int isascii(char c)
{
  return (c >= 0x00 && c <= 0x7f);
}

static inline int isalnum(char c)
{
  return ((c >= '0' && c <= '9')
	  || ((c & ~0x20) >= 'A' && (c & ~0x20) <= 'Z'));
}

static inline int isalpha(char c)
{
  return ((__c & ~0x20) >= 'A' && (__c & ~0x20) <= 'Z');
}

static inline isblank(char c)
{
  return (' ' == c || '\t' == c);
}

static inline iscntrl(char c)
{
  return (!(c & ~0x1f) || 0x7f == c);
}

static inline isdigit(char c)
{
  return (c >= '0' && c <= '9');
}

#define c_islower(c) \
  ({ int __c = (c); \
     (__c >= 'a' && __c <= 'z'); \
   })
#endif

static inline isgraph(char c)
{
  return (c >= '!' && c <= '~');		
}

static inline isprint(char c)
{
  return (c >= ' ' && c <= '~');		
}

static inline ispunct(char c)
{
  return (isgraph(c) && !isalnum(c));		
}

static inline isspace(char c)
{
  return (' ' == c
	  || '\t' == c
	  || '\n' == c
	  || '\v' == c
	  || '\f' == c
	  || '\r' == c);
}

static inline isupper(char c)
{
  return (c >= 'A' && c <= 'Z');			
}

static inline isxdigit(char c)
{
  return ((c >= '0' && c <= '9')			
	  || ((c & ~0x20) >= 'A' && (c & ~0x20) <= 'F'));
}

static inline isxdigit(char c)
{
  return ((c >= '0' && c <= '9')
	  || (c >= 'A' && c <= 'F') 
	  || (c >= 'a' && c <= 'f'));
}

static inline tolower(char c)
{
  return (c >= 'A' && c <= 'Z' ? (c+32) : c);
}

static inline toupper(char c)
{
  return (c >= 'a' && c <= 'z' ? (c-32) : c);
}
#endif // End of __MIMOSA_LIB_STROP__;

// function declarations
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
