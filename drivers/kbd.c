#ifdef USE_DRV_KBD
/*	
 *  Copyright (C) 2010-2012,2016
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
#include <drivers/kbd.h>
#include <drivers/console.h>
#include <types.h>

// NOTE: Scancode for set 1

static u8_t shiftcode[256] = 
  {
    [0x1D] CTL,
    [0x2A] SHIFT,
    [0x36] SHIFT,
    [0x38] ALT,
    [0x9D] CTL,
    [0xB8] ALT
  };

static u8_t togglecode[256] = 
  {
    [0x3A] CAPSLOCK,
    [0x45] NUMLOCK,
    [0x46] SCROLLLOCK
  };

static u8_t normalmap[256] =
  {
    NO,   0x1B, '1',  '2',  '3',  '4',  '5',  '6',	// 0x00
    '7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',
    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',	// 0x10
    'o',  'p',  '[',  ']',  '\n', NO,   'a',  's',
    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',	// 0x20
    '\'', '`',  NO,   '\\', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  NO,   '*',	// 0x30
    NO,   ' ',  NO,   NO,   NO,   NO,   NO,   NO,
    NO,   NO,   NO,   NO,   NO,   NO,   NO,   '7',	// 0x40
    '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
    '2',  '3',  '0',  '.',  NO,   NO,   NO,   NO,	// 0x50
    [0x97] KEY_HOME,	[0x9C] '\n' /*KP_Enter*/,
    [0xB5] '/' /*KP_Div*/,	[0xC8] KEY_UP,
    [0xC9] KEY_PGUP,	[0xCB] KEY_LF,
    [0xCD] KEY_RT,		[0xCF] KEY_END,
    [0xD0] KEY_DN,		[0xD1] KEY_PGDN,
    [0xD2] KEY_INS,		[0xD3] KEY_DEL
  };

static u8_t shiftmap[256] = 
  {
    NO,   033,  '!',  '@',  '#',  '$',  '%',  '^',	// 0x00
    '&',  '*',  '(',  ')',  '_',  '+',  '\b', '\t',
    'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',	// 0x10
    'O',  'P',  '{',  '}',  '\n', NO,   'A',  'S',
    'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',	// 0x20
    '"',  '~',  NO,   '|',  'Z',  'X',  'C',  'V',
    'B',  'N',  'M',  '<',  '>',  '?',  NO,   '*',	// 0x30
    NO,   ' ',  NO,   NO,   NO,   NO,   NO,   NO,
    NO,   NO,   NO,   NO,   NO,   NO,   NO,   '7',	// 0x40
    '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
    '2',  '3',  '0',  '.',  NO,   NO,   NO,   NO,	// 0x50
    [0x97] KEY_HOME,	[0x9C] '\n' /*KP_Enter*/,
    [0xB5] '/' /*KP_Div*/,	[0xC8] KEY_UP,
    [0xC9] KEY_PGUP,	[0xCB] KEY_LF,
    [0xCD] KEY_RT,		[0xCF] KEY_END,
    [0xD0] KEY_DN,		[0xD1] KEY_PGDN,
    [0xD2] KEY_INS,		[0xD3] KEY_DEL
  };

#define C(x) (x - '@')

static u8_t ctlmap[256] = 
  {
    NO,      NO,      NO,      NO,      NO,      NO,      NO,      NO, 
    NO,      NO,      NO,      NO,      NO,      NO,      NO,      NO, 
    C('Q'),  C('W'),  C('E'),  C('R'),  C('T'),  C('Y'),  C('U'),  C('I'),
    C('O'),  C('P'),  NO,      NO,      '\r',    NO,      C('A'),  C('S'),
    C('D'),  C('F'),  C('G'),  C('H'),  C('J'),  C('K'),  C('L'),  NO, 
    NO,      NO,      NO,      C('\\'), C('Z'),  C('X'),  C('C'),  C('V'),
    C('B'),  C('N'),  C('M'),  NO,      NO,      C('/'),  NO,      NO,
    [0x97] KEY_HOME,
    [0xB5] C('/'),		[0xC8] KEY_UP,
    [0xC9] KEY_PGUP,		[0xCB] KEY_LF,
    [0xCD] KEY_RT,		[0xCF] KEY_END,
    [0xD0] KEY_DN,		[0xD1] KEY_PGDN,
    [0xD2] KEY_INS,		[0xD3] KEY_DEL
  };

static u8_t *charcode[4] =
  {
    normalmap,
    shiftmap,
    ctlmap,
    ctlmap
  };

/*
 * Get data from the keyboard.  If we finish a character, return it.  Else 0.
 * Return -1 if no data.
 */
static int kbd_proc_data(void)
{
  int c;
  u8_t data;
  static u32_t shift;

  if ((readb(KBSTATP) & KBS_DIB) == 0)
    return -1;

  data = readb(KBDATAP);

  if (data == 0xE0) {
    // E0 escape character
    shift |= E0ESC;
    return 0;
  } else if (data & 0x80) {
    // Key released
    data = (shift & E0ESC ? data : data & 0x7F);
    shift &= ~(shiftcode[data] | E0ESC);
    return 0;
  } else if (shift & E0ESC) {
    // Last character was an E0 escape; or with 0x80
    data |= 0x80;
    shift &= ~E0ESC;
  }

  shift |= shiftcode[data];
  shift ^= togglecode[data];

  c = charcode[shift & (CTL | SHIFT)][data];
  if(shift & CAPSLOCK) {
    if('a' <= c && c <= 'z')
      c += 'A' - 'a';
    else if('A' <= c && c <= 'Z')
      c += 'a' - 'A';
  }

  // Process special keys
  // Ctrl-Alt-Del: reboot
  if(!(~shift & (CTL | ALT)) && KEY_DEL == c)
    {
      //cprintf("Rebooting!\n");
      writeb(0x92, 0x3); // courtesy of Chris Frost
    }

  return c;
}

/***** General device-independent console code *****/
// Here we manage the console input buffer,
// where we stash characters received from the keyboard or serial port
// whenever the corresponding interrupt occurs.

#define CONSBUFSIZE 512

static struct
{
  u8_t buf[CONSBUFSIZE];
  u32_t rpos;
  u32_t wpos;
} cons;

// called by device interrupt routines to feed input characters
// into the circular console input buffer.
static void cons_intr(int (*proc)(void))
{
  int c;

  while(-1 != (c = (*proc)()))
    {
      if(0 == c)
	continue;

      cons.buf[cons.wpos++] = c;

      if(CONSBUFSIZE == cons.wpos)
	cons.wpos = 0;
    }
}

// return the next input character from the console, or 0 if none waiting
static int cons_getc(void)
{
  int c;

  // poll for any pending input characters,
  // so that this function works even when interrupts are disabled
  // (e.g., when called from the kernel monitor).
  //serial_intr();
  kbd_intr();

  // grab the next character from the input buffer.
  if(cons.rpos != cons.wpos)
    {
      c = cons.buf[cons.rpos++];
      if(CONSBUFSIZE == cons.rpos)
	cons.rpos = 0;
      return c;
    }

  return 0;
}

int kbd_getc(void)
{
  int c;

  while ((c = cons_getc()) == 0)
    /* do nothing */;
  return c;
}

int iscons(int fdnum)
{
  // used by readline
  return 1;
}

void kbd_intr(void)
{
  cons_intr(kbd_proc_data);
}

void kbd_init(void)
{
}

#endif // End of USE_DRV_KBD;
