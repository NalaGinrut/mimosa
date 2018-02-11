/*	
 *  Copyright (C) 2016
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
 
/* This is linker config for ATMega BSP
 */

/* TODO: I must write a convenient script(guile?) to custom these
 * env properly.
 */
OUTPUT_FORMAT("elf32-avr")
OUTPUT_ARCH(avr:5)
ENTRY(_start)
/*STARTUP(entry.o)
*/

/* NOTE: There's a bug in avr-ld that (rw!x) is treated as wrong
 *    	 syntax when it's included. A proper fix is (rw ! x).
 *       Check it here:
 *       https://sourceware.org/bugzilla/show_bug.cgi?id=17900
 */
MEMORY
{
  text   (rx)   : ORIGIN = 0, LENGTH = 128K
  data   (rw ! x) : ORIGIN = 0x800060, LENGTH = 0xffa0
  eeprom (rw ! x) : ORIGIN = 0x810000, LENGTH = 64K
  fuse      (rw ! x) : ORIGIN = 0x820000, LENGTH = 1K
  lock      (rw ! x) : ORIGIN = 0x830000, LENGTH = 1K
  signature (rw ! x) : ORIGIN = 0x840000, LENGTH = 1K
  user_signatures (rw ! x) : ORIGIN = 0x850000, LENGTH = 1K
}
