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


#include <bsp/cpu/port.h>
#include <bsp/drivers/kbd.h>
#include <bsp/bsp_types.h>

// NOTE: Scancode for set 1

static const __u8_t normal_map[256] =
  {
    NA,   0x1B, '1',  '2',  '3',  '4',  '5',  '6',	// 0x00
    '7',  '8',  '9',  '0',  '-',  '=',  '\b', '\t',
    'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',	// 0x10
    'o',  'p',  '[',  ']',  '\n', NA,   'a',  's',
    'd',  'f',  'g',  'h',  'j',  'k',  'l',  ';',	// 0x20
    '\'', '`',  NA,   '\\', 'z',  'x',  'c',  'v',
    'b',  'n',  'm',  ',',  '.',  '/',  NA,   '*',	// 0x30
    NA,   ' ',  NA,   NA,   NA,   NA,   NA,   NA,
    NA,   NA,   NA,   NA,   NA,   NA,   NA,   '7',	// 0x40
    '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
    '2',  '3',  '0',  '.',  NA,   NA,   NA,   NA,	// 0x50
    [0x97] KEY_HOME,		[0x9C] '\n' /*KP_Enter*/,
    [0xB5] '/' /*KP_Div*/,	[0xC8] KEY_UP,
    [0xC9] KEY_PGUP,		[0xCB] KEY_LF,
    [0xCD] KEY_RT,		[0xCF] KEY_END,
    [0xD0] KEY_DN,		[0xD1] KEY_PGDN,
    [0xD2] KEY_INS,		[0xD3] KEY_DEL,
    [0x1D] KEY_CTRL,		[0x2A] KEY_SHIFT,
    [0x36] KEY_SHIFT,		[0x38] KEY_ALT,
    [0x9D] KEY_CTRL,		[0xB8] KEY_ALT,
    [0x3A] KEY_CAPSLOCK,	[0x45] KEY_NUMLOCK,
    [0x46] KEY_SCROLLLOCK
  };

static const __u8_t shift_map[256] = 
  {
    NA,   033,  '!',  '@',  '#',  '$',  '%',  '^',	// 0x00
    '&',  '*',  '(',  ')',  '_',  '+',  '\b', '\t',
    'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',	// 0x10
    'O',  'P',  '{',  '}',  '\n', NA,   'A',  'S',
    'D',  'F',  'G',  'H',  'J',  'K',  'L',  ':',	// 0x20
    '"',  '~',  NA,   '|',  'Z',  'X',  'C',  'V',
    'B',  'N',  'M',  '<',  '>',  '?',  NA,   '*',	// 0x30
    NA,   ' ',  NA,   NA,   NA,   NA,   NA,   NA,
    NA,   NA,   NA,   NA,   NA,   NA,   NA,   '7',	// 0x40
    '8',  '9',  '-',  '4',  '5',  '6',  '+',  '1',
    '2',  '3',  '0',  '.',  NA,   NA,   NA,   NA,	// 0x50
    [0x97] KEY_HOME,		[0x9C] '\n' /*KP_Enter*/,
    [0xB5] '/' /*KP_Div*/,	[0xC8] KEY_UP,
    [0xC9] KEY_PGUP,		[0xCB] KEY_LF,
    [0xCD] KEY_RT,		[0xCF] KEY_END,
    [0xD0] KEY_DN,		[0xD1] KEY_PGDN,
    [0xD2] KEY_INS,		[0xD3] KEY_DEL
    [0x1D] KEY_CTRL,		[0x2A] KEY_SHIFT,
    [0x36] KEY_SHIFT,		[0x38] KEY_ALT,
    [0x9D] KEY_CTRL,		[0xB8] KEY_ALT,
    [0x3A] KEY_CAPSLOCK,	[0x45] KEY_NUMLOCK,
    [0x46] KEY_SCROLLLOCK
  };

#define _C(x) ((x) - '@')

static const __u8_t ctrl_map[256] =
  {
    NA,      NA,      NA,      NA,      NA,      NA,      NA,      NA, 
    NA,      NA,      NA,      NA,      NA,      NA,      NA,      NA, 
    _C('Q'), _C('W'), _C('E'), _C('R'), _C('T'), _C('Y'), _C('U'), _C('I'),
    _C('O'), _C('P'), NA,      NA,      '\r',    NA,      _C('A'), _C('S'),
    _C('D'), _C('F'), _C('G'), _C('H'), _C('J'), _C('K'), _C('L'), NA, 
    NA,      NA,      NA,      _C('\\'),_C('Z'), _C('X'), _C('C'), _C('V'),
    _C('B'), _C('N'), _C('M'), NA,      NA,      _C('/'), NA,      NA,
    [0x97] KEY_HOME,
    [0xB5] _C('/'),		[0xC8] KEY_UP,
    [0xC9] KEY_PGUP,		[0xCB] KEY_LF,
    [0xCD] KEY_RT,		[0xCF] KEY_END,
    [0xD0] KEY_DN,		[0xD1] KEY_PGDN,
    [0xD2] KEY_INS,		[0xD3] KEY_DEL
  };

static const __u8_t *char_code[4] =
  {
    normal_map,
    shift_map,
    ctrl_map,
    ctrl_map
  };


/* This proc is implemented for 'scan-codes set 1'. So you may need
 * to google that if you can't understand it.
 */
static int kbd_get_data()
{
  int ch;
  __u8_t data;
  static __u32_t logic_ruler;

  if( (port_rb(KBSTATP) & KBS_DIB) == 0)
    return -1;

  switch( data = port_rb(KBDATAP) )
    {
    case KBD_E0:
      logic_ruler |= E0ESC;
      return 0;
    case KBD_ERR:
      // FIXME: do some panic
      return -1;
    case KBD_ECHO:
      // TODO: handle this echo
      break;
    case KBD_ACK:
      // TODO: handle this ack
      break;
    case KBD_ACK_FAIL:
      // TODO: handle this fail
      break;
    default:   // ordinary scancode
      if(data & 0x80)  // break code
	{
	  /* Special code follows a E0ESC is impossible, so if such a 
	   * code & 0x80 is true, it must be an ordinary code. And we 
	   * must clean its break bit first because this key is released.
	   */
	  data = (logic_ruler & E0ESC ? data : (data & ~0x80));
	  
	  /* And clear E0ESC. So the key press this time became invalid.
	   * The keyboard driver expect next key press event now.
	   */
	  logic_ruler &= ~(control_code[data] | E0ESC);

	  return 0;
	}
      else if(logic_ruler & E0ESC)
	{
	  data |= 0x80;  // avoid repeat, or it will show till get the break code
	  logic_ruler &= ~E0ESC;
	}
    }

  logic_ruler |= control_code[data];
  logic_ruler ^= toggle_code[data];
	  
