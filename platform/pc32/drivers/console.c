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

#include <now/cpu/port.h>
#include <now/bsp_types.h>
#include <now/drivers/console.h>
#include <now/drivers/kbd.h>
#include <libkern.h>

#ifdef __KERN_DEBUG__
#include <debug.h>
#endif

static __u32_t port_6845;
static __u16_t *crt_buf;
static __u16_t crt_pos; 

void console_init()
{
  cga_init();
  kbd_init();

  //FIXME: do we need serial-port init here?

}

void console_putc(__u16_t ch)
{

#ifdef __KERN_ONLINE_DEBUG__
  serial_putc(ch);
#endif

  cga_putc(ch);

}


static void cga_init()
{
  __u16_t tmp;
  
  tmp = *CGA_DISP_BUF;

  // check out the display mode ,and select one of them. 
  *CGA_DISP_BUF = (__u16_t)0xA55A;
  port_6845 = (*CGA_DISP_BUF == 0xA55A)? CGA_BASE : MONO_BASE;
  *CGA_DISP_BUF = tmp;

  // select MONO or CGA buffer
  crt_buf = (__u16_t*)((port_6845 == MONO_BASE)? MONO_DISP_BUF : CGA_DISP_BUF);


  // get cursor location
  port_wb(port_6845 ,CURSOR_H);
  crt_pos = port_rb(port_6845 + 1) << 8;

  port_wb(port_6845 ,CURSOR_L);
  crt_pos |= port_rb(port_6845 + 1);

}


void cga_putc(__u16_t ch)
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
	     (CRT_SIZE - CRT_COLS) * sizeof(__u16_t));
      for (i = CRT_SIZE - CRT_COLS; i < CRT_SIZE; i++)
			crt_buf[i] = 0x0700 | ' ';
      crt_pos -= CRT_COLS;
    }

  port_wb(port_6845 ,CURSOR_H);
  port_wb(port_6845 + 1 ,crt_pos >> 8);

  port_wb(port_6845 ,CURSOR_L);
  port_wb(port_6845 + 1 ,crt_pos);

}

