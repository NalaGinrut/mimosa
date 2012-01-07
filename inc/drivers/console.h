#ifndef	__MIMOSA_PC32_CONSOLE_H
#define __MIMOSA_PC32_CONSOLE_H
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

extern char principio[];

#define MONO_BASE	0x3B4
#define MONO_BUF	0xB0000
#define CGA_BASE	0x3D4
#define CGA_BUF		0xB8000

#define CGA_DISP_BUF	((volatile u16_t*)(KERN_BASE + CGA_BUF))
#define MONO_DISP_BUF	((volatile u16_t*)(KERN_BASE + MONO_BUF))

#define CRT_ROWS	25
#define CRT_COLS	80
#define	CRT_SIZE	(CRT_ROWS * CRT_COLS)

#define CURSOR_H	0x0E // cursor location high register
#define CURSOR_L	0x0F // cursor location low register

#define BG_BLK_FG_GRAY	0x0700

typedef struct Console_Ctrl_Block
{
  u32_t crt_port; // port 6845
  u16_t *crt_buf;
  u16_t crt_pos; 
}ccb_t ,*ccb_tp;

void console_init();
void console_putc(u16_t ch);

static inline void cga_get_cursor_pos();
static void cga_init();
void cga_putc(u16_t ch);

#endif // End of __MIMOSA_PC32_CONSOLE_H;
