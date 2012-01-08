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

#include <osconfig.h>
#include <libkern.h>
#include <stdarg.h>
#include <stdio.h>
#include <types.h>
#include <retval.h>

#define MAXERROR 6

static const char* const error_string[MAXERROR + 1] =
  {
    NULL,
    "Unspecified Error",
    "Bad Environment",
    "Invalid Parameter",
    "Out of Memory",
    "Out of Environments",
    "Segmentation Fault",
  };

typedef struct Sprint_Buf
{
  char *buf;
  int end;
  int cnt;
  int color;
}spbuf_t ,*spbuf_tp;

typedef struct Reswitch_Context
{
  int width;
  int precision;
  int lflag;
  int altflag;
  char padc;
}resw_cont_t ,*resw_cont_tp;
  
typedef void (*putch_func_t)(char ,spbuf_t*);

static int vcprintf(const char *fmt ,va_list ap);
static void printfmt(putch_func_t putch ,spbuf_t *spb ,const char *fmt ,...);
static void color_putch(char ch ,spbuf_t *spb);
static void sprint_putch(char ch ,spbuf_t *spb);
static int vsnprintf(char *buf ,int n ,const char *fmt ,va_list ap);
static void print_num(putch_func_t putch ,spbuf_t *spb ,u64_t num,
		      u32_t base ,int width ,int padc);
static u64_t get_uint(va_list *ap ,int lflag);
static s64_t get_int(va_list *ap ,int lflag);
static inline void reswitch(resw_cont_t *rc ,putch_func_t putch,
			    spbuf_t *spb ,const char *fmt ,va_list ap);
static void vprintfmt(putch_func_t putch ,spbuf_t *spb ,const char *fmt ,va_list ap);

int cprintf(const char *fmt ,...)
{
  va_list ap;
  int cnt;

  va_start(ap ,fmt);
  cnt = vcprintf(fmt ,ap);
  va_end(ap);

  return cnt;
}

static int vcprintf(const char *fmt ,va_list ap)
{
  // TODO: provide line buffer
  spbuf_t spb = { .buf = NULL,
		  .end = 0,
		  .cnt = 0,
		  .color = 0 };

  vprintfmt(color_putch ,&spb ,fmt ,ap);

  return spb.cnt;
}

static void printfmt(putch_func_t putch ,spbuf_t *spb ,const char *fmt ,...)
{
  va_list ap;

  va_start(ap, fmt);
  vprintfmt(putch ,spb ,fmt ,ap);
  va_end(ap);
}

static void color_putch(char ch ,spbuf_t *spb)
{
  // colored char
  u16_t cch = ch | spb->color<<8;

  __PUT_CHAR__(cch);

  spb->cnt++;
}

static void sprint_putch(char ch ,spbuf_t *spb)
{
  int cnt = spb->cnt;
  
  if(cnt < spb->end)
    {
      spb->buf[cnt] = ch;
      spb->cnt++;
    }
}

static int vsnprintf(char *buf ,int n ,const char *fmt ,va_list ap)
{
  /* NOTE: string length contains '\0', so be sure n > 1
   */
  spbuf_t spb = { .buf = buf,
		  .end = n-1,
		  .cnt = 0,
		  .color = 0 };

  if(NULL == buf || n <= 1)
    return EINVAL;

  // print the string to the buffer
  vprintfmt(sprint_putch ,&spb ,fmt ,ap);

  // null terminate the buffer
  spb.buf[spb.cnt] = '\0';

  return spb.cnt;
}

static void print_num(putch_func_t putch ,spbuf_t *spb ,u64_t num,
		      u32_t base ,int width ,int padc)
{
  /* FIXME: only can handle maximum 64bit number,
   *	    but this should according to max length integer which depends on platform.
   */
  char buf[21] = {0};
  int cnt = 0;
  
  while(num > 0)
    {
      if(num >= base)
	{
	  width--;
	}
      else
	{
	  // print any needed pad characters before first digit
	  while(width-- > 0)
	    putch(padc ,spb);
	}
      
      // then print this (the least significant) digit
      buf[cnt]="0123456789abcdef"[num % base];
      cnt++;
      num /= base;
    }

  for(int i=cnt-1 ;i>=0 ;i--)
    putch(buf[i] ,spb);
}

static u64_t get_uint(va_list *ap ,int lflag)
{
  if(lflag >= 2)
    return va_arg(*ap ,u64_t);
  else if(lflag)
    return (u64_t)va_arg(*ap ,u32_t);
  else
    return (u64_t)va_arg(*ap ,u16_t);
}

static s64_t get_int(va_list *ap ,int lflag)
{
  if(lflag >= 2)
    return va_arg(*ap ,s64_t);
  else if(lflag)
    return (s64_t)va_arg(*ap ,s32_t);
  else
    return (s64_t)va_arg(*ap ,s16_t);
}

static inline void reswitch(resw_cont_t *rc ,putch_func_t putch,
			    spbuf_t *spb ,const char *fmt ,va_list ap)
{
  register const char *p;
  register char ch;
  register int err;
  u64_t num;
  int base;
  int lflag = rc->lflag;
  int width = rc->width;
  int precision = rc->precision;
  int altflag = rc->altflag;
  char padc = rc->padc;

#define	process_precision() 	\
  if(width < 0)			\
  {				\
    width = precision;		\
    precision = -1;		\
  }				
  
#define process_number() print_num(putch ,spb ,num ,base ,width ,padc)
  
  while(1)
    {
      switch(ch = *(unsigned char *)fmt++)
	{
	case '\0':
	  return;

	  // flag to pad on the right
	case '-':
	  padc = '-';
	  break;
			
	  // flag to pad with 0's instead of spaces
	case '0':
	  padc = '0';
	  break;

	  // width field
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	  for(precision = 0 ;(0 <= ch && ch <= 9) ;fmt++)
	    {
	      precision = precision * 10 + ch - '0';
	      ch = *fmt;
	    }	
	  process_precision();
	  break;	

	case '*':
	  precision = va_arg(ap ,int);
	  process_precision();
	  break;

	case '.':
	  if(width < 0)
	    width = 0;
	  break;

	case '#':
	  altflag = 1;
	  break;


	  // long flag (doubled for long long)
	case 'l':
	  lflag++;
	  break;

	  // character
	case 'c':
	  putch(va_arg(ap ,int) ,spb);
	  return;

	  // error message
	case 'e':
	  err = va_arg(ap ,int);
	  if(err < 0)
	    err = -err;
	  if(err > MAXERROR || NULL == (p = error_string[err]))
	    printfmt(putch ,spb ,"error %d" ,err);
	  else
	    printfmt(putch ,spb ,"%s" ,p);
	  return;

	  // string
	case 's':
	  if(NULL == (p = va_arg(ap ,char *)))
	    p = "(null)";
	  if(width > 0 && padc != '-')
	    for(width -= strnlen(p ,precision) ;width > 0 ;width--)
	      putch(padc ,spb);
	  for( ;(ch = *p++) != '\0' && (precision < 0 || --precision >= 0) ;width--)
	    if(altflag && (ch < ' ' || ch > '~'))
	      putch('?' ,spb);
	    else
	      putch(ch ,spb);
	  for( ;width > 0 ;width--)
	    putch(' ' ,spb);
	  return;

	  // (signed) decimal
	case 'd':
	  num = get_int(&ap ,lflag);
	  if((s64_t)num < 0)
	    {
	      putch('-' ,spb);
	      num = (-(s64_t)num);
	    }
	  base = 10;
	  process_number();
	  return;

	  // unsigned decimal
	case 'u':
	  num = get_uint(&ap ,lflag);
	  base = 10;
	  process_number();
	  return;

	  // (unsigned) octal
	case 'o':
	  num = get_uint(&ap ,lflag);
	  base = 8;
	  process_number();
	  return;

	  // pointer
	case 'p':
	  putch('0' ,spb);
	  putch('x' ,spb);
	  num = (uintptr_t)va_arg(ap ,void *);
	  base = 16;
	  process_number();
	  return;

	  // (unsigned) hexadecimal
	case 'x':
	  num = get_uint(&ap ,lflag);
	  base = 16;
	  process_number();
	  return;

	  // escaped '%' character
	case '%':
	  putch(ch ,spb);
	  return;
	  
	  // unrecognized escape sequence - just print it literally
	default:
	  putch('%' ,spb);
	  for(fmt-- ;fmt[-1] != '%' ;fmt--)
	    /* do nothing */;
	  return;
	}
    }

#undef process_precision
#undef process_number
}

static void vprintfmt(putch_func_t putch ,spbuf_t *spb ,const char *fmt ,va_list ap)
{
  register char ch;
  resw_cont_t rc;
  
  while(1)
    {
      while('%' != (ch = *(char *)fmt++))
	{
	  if('\0' == ch)
	    return;

	  putch(ch ,spb);
	}	

      // Process a %-escape sequence
      rc.padc = ' ';
      rc.width = -1;
      rc.precision = -1;
      rc.lflag = 0;
      rc.altflag = 0;

      reswitch(&rc ,putch ,spb ,fmt ,ap);
    }
}

#undef MAXERROR
