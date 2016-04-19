#ifndef	__MIMOSA_BSP_ATMEGA_MMIO_H
#define __MIMOSA_BSP_ATMEGA_MMIO_H
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
#include <bsp/bsp_bits.h>

static __inline__ __u8_t mmio_readb(__u32_t addr) __true_inline;
static __inline__ __u16_t mmio_readw(__u32_t addr) __true_inline;

static __inline__ void mmio_rnb(__u16_t addr,
                                __gptr_t addr,
                                __u16_t cnt) __true_inline;

static __inline__ void mmio_rnw(__u16_t addr,
                                __gptr_t addr,
                                __u16_t cnt) __true_inline;

// ======================================================================
static __inline__ __u8_t mmio_readb(__u8_t addr)
{ return (*(volatile u8_t *)(addr)); }

static __inline__ __u16_t mmio_readw(__u16_t addr)
{ return  (*(volatile u16_t *)(addr)); }

static __inline__ void mmio_rnb(__u32_t addr, __gptr_t addr, __u32_t cnt)
{}

/*
static __inline__ void mmio_rnb(__u32_t addr, __gptr_t addr, __u32_t cnt)
{
  while (cnt-- > 0)
    {
      
  __mmio_nread(insb);
}
*/

#endif // End of __MIMOSA_BSP_ATMEGA_MMIO_H
