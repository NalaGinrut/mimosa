#ifndef	__MIMOSA_PC32_CONSOLE_H
#define __MIMOSA_PC32_CONSOLE_H
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

extern char principio[];

#define MONO_BASE	0x3B4
#define MONO_BUF	0xB0000
#define CGA_BASE	0x3D4
#define CGA_BUF		0xB8000

#define CGA_DISP_BUF	((volatile __u16_t*)(principio + CGA_BUF))
#define MONO_DISP_BUF	((volatile __u16_t*)(principio + MONO_BUF))

#define CRT_ROWS	25
#define CRT_COLS	80
#define	CRT_SIZE	(CRT_ROWS * CRT_COLS)

#define CURSOR_H	0x0E // cursor location high register
#define CURSOR_L	0x0F // cursor location low register

void console_init();
void console_putc(__u16_t ch);

static void cga_init();
void cga_putc(__u16_t ch);

#endif // End of __MIMOSA_PC32_CONSOLE_H;
