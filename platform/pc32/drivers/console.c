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

#include <now/bsp_types.h>
#include <now/drivers/console.h>
#include <now/drivers/bda.h>


static __u32_t port_6845;
static __u16_t *crt_buf;
static __u16_t crt_pos; 

void console_init()
{
  cga_init();
  kbd_init();

  //FIXME: do we need serial-port init here?

}


static void cga_init()
{
  
  //volatile __u16_t *test;
  __u16_t tmp;
  __u32_t pos;

  
  tmp = *CGA_DISP_BUF;

  // check out the display mode ,and select one of them. 
  *CGA_DISP_BUF = (__u16_t)0xA55A;
  port_6845 = (*test == 0xA55A)? CGA_BASE : MONO_BASE;
  *CGA_DISP_BUF = tmp;

  // select MONO or CGA buffer
  crt_buf = (port_6845 == MONO_BASE)? MONO_DISP_BUF : CGA_DISP_BUF;


  // get cursor location
  port_wb(port_6845 ,CURSOR_H);
  crt_pos = port_rb(port_6845 + 1) << 8;

  port_wb(port_6845 ,CURSOR_L);
  crt_pos |= port_rb(port_6845 + 1);

}
