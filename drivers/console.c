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

#include <osconfig.h>
#include <io.h>
#include <types.h>
#include <global.h>
#include <drivers/console.h>
#include <drivers/kbd.h>
#include <libkern.h>

#ifdef __KERN_DEBUG__
#include <debug.h>
#endif

static ccb_t MK_GLOBAL_VAR(con_ctr);

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

static inline void cga_update_cursor()
{
  ccb_t *ccb = &GET_GLOBAL_VAR(con_ctr);
  u32_t crt_port = ccb->crt_port;
  u16_t crt_pos = ccb->crt_pos;
  
  writeb(crt_port ,CURSOR_H);
  writeb(crt_port + 1 ,crt_pos >> 8);

  writeb(crt_port ,CURSOR_L);
  writeb(crt_port + 1 ,crt_pos);
}

static inline void cga_get_cursor_pos()
{
  ccb_t *ccb = &GET_GLOBAL_VAR(con_ctr);
  u32_t crt_port = ccb->crt_port;
  
  writeb(crt_port ,CURSOR_H);
  ccb->crt_pos = readb(crt_port + 1) << 8;

  writeb(crt_port ,CURSOR_L);
  ccb->crt_pos |= readb(crt_port + 1);
}

static void cga_init()
{
  u16_t tmp;
  ccb_t *ccb = &GET_GLOBAL_VAR(con_ctr);
  u32_t crt_port = ccb->crt_port;
  u16_t *crt_buf = ccb->crt_buf;

  tmp = *CGA_DISP_BUF;

  // check out the display mode ,and select one of them. 
  *CGA_DISP_BUF = (u16_t)0xA55A;
  crt_port = (*CGA_DISP_BUF == 0xA55A)? CGA_BASE : MONO_BASE;
  *CGA_DISP_BUF = tmp;

  // select MONO or CGA buffer
  crt_buf = (u16_t*)(crt_port == MONO_BASE ? MONO_DISP_BUF : CGA_DISP_BUF);

  ccb->crt_buf = crt_buf;
  ccb->crt_port = crt_port;
  // get cursor position
  cga_get_cursor_pos();
}	

void cga_putc(u16_t ch)
{
  ccb_t *ccb = &GET_GLOBAL_VAR(con_ctr);
  u32_t crt_port = ccb->crt_port;
  u16_t *crt_buf = ccb->crt_buf;
  u16_t crt_pos = ccb->crt_pos;
  
  ch = (ch & 0xFF00)? ch : (ch | BG_BLK_FG_GRAY);

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
      memcpy(crt_buf ,crt_buf + CRT_COLS ,(CRT_SIZE - CRT_COLS) * sizeof(u16_t));

      for (int i = CRT_SIZE - CRT_COLS ;i < CRT_SIZE ;i++)
	crt_buf[i] = 0x0700 | ' ';

      crt_pos -= CRT_COLS;
    }

  ccb->crt_pos = crt_pos;
  ccb->crt_buf = crt_buf;
  
  cga_update_cursor();
}

