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


#include <io.h>
#include <types.h>
#include <drivers/console.h>
#include <drivers/kbd.h>
#include <libkern.h>

#ifdef __KERN_DEBUG__
#include <debug.h>
#endif

static u32_t port_6845;
static u16_t *crt_buf;
static u16_t crt_pos; 

void console_init()
{
  cga_init();
  kbd_init();

  //FIXME: do we need serial-port init here?

}

void console_putc(u16_t ch)
{

#ifdef __KERN_ONLINE_DEBUG__
  serial_putc(ch);
#endif

  cga_putc(ch);

}


static void cga_init()
{
  u16_t tmp;
  
  tmp = *CGA_DISP_BUF;

  // check out the display mode ,and select one of them. 
  *CGA_DISP_BUF = (u16_t)0xA55A;
  port_6845 = (*CGA_DISP_BUF == 0xA55A)? CGA_BASE : MONO_BASE;
  *CGA_DISP_BUF = tmp;

  // select MONO or CGA buffer
  crt_buf = (u16_t*)((port_6845 == MONO_BASE)? MONO_DISP_BUF : CGA_DISP_BUF);


  // get cursor location
  writeb(port_6845 ,CURSOR_H);
  crt_pos = readb(port_6845 + 1) << 8;

  writeb(port_6845 ,CURSOR_L);
  crt_pos |= readb(port_6845 + 1);

}


void cga_putc(u16_t ch)
{
  ch = (ch & 0xFF00)? ch : (ch | 0x0700);

  switch( ch & 0xFF )
    {
    case '\b':
      if( crt_pos > 0 )
	{
	  crt_pos--;
	  crt_buf[crt_pos] = ((ch & 0xFF00) | ' ');
	}
      break;
    case '\n':
      crt_pos += CRT_COLS;
      break;
    case '\r':
      crt_pos -= (crt_pos % CRT_COLS);
    case '\t':
      console_putc(' ');console_putc(' ');
      console_putc(' ');console_putc(' ');
      break;
    default:
      crt_buf[crt_pos++] = ch;
      break;
    }

  if (crt_pos >= CRT_SIZE)
    {
      int i;
    
      memcpy(crt_buf, crt_buf + CRT_COLS, 
	     (CRT_SIZE - CRT_COLS) * sizeof(u16_t));
      for (i = CRT_SIZE - CRT_COLS; i < CRT_SIZE; i++)
			crt_buf[i] = 0x0700 | ' ';
      crt_pos -= CRT_COLS;
    }

  writeb(port_6845 ,CURSOR_H);
  writeb(port_6845 + 1 ,crt_pos >> 8);

  writeb(port_6845 ,CURSOR_L);
  writeb(port_6845 + 1 ,crt_pos);

}

