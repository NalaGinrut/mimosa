#ifndef __BSP_ATMEGA_DELAY_H
#define __BSP_ATMEGA_DELAY_H
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

#include <bsp/bsp_types.h>

#define F_CPU 16000000ul // only for ATmega32u4

extern void __builtin_avr_delay_cycles(unsigned long);
extern double __builtin_ceil(double);
extern double __builtin_fabs(double);

#define ceil __builtin_ceil
#define fabs __builtin_fabs

void _delay_ms(double __ms)
{
  double __tmp = 0; 
  __u32_t __ticks_dc = 0;

  //round up by default
  __ticks_dc = (__u32_t)(ceil(fabs(__tmp)));

  __builtin_avr_delay_cycles(__ticks_dc);
}

#endif // End of __BSP_ATMEGA_PMAP_H;
