#ifdef USE_DRV_NVRAM
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

#include <osconfig.h>
#include <drivers/nvram.h>
#include <types.h>
#include <bits.h>

// will return in Kilobytes
u32_t nvram_get_base_mem_size()
{
  u32_t mem_lo = nvram_read_byte(NVRAM_BASELO);
  u32_t mem_hi = nvram_read_byte(NVRAM_BASEHI);
  u32_t ret = ((mem_lo | (mem_hi<<8)) * 1024);
  return ROUND_DOWN(ret ,PG_SIZE);
}

// will return in Kilobytes
u32_t nvram_get_ext_mem_size()
{
  u32_t mem_lo = nvram_read_byte(NVRAM_EXTLO);
  u32_t mem_hi = nvram_read_byte(NVRAM_EXTHI);
  u32_t ret = ((mem_lo | (mem_hi<<8)) * 1024);
  return ROUND_DOWN(ret ,PG_SIZE);
}

u32_t nvram_read_byte(u32_t index)
{
  return mc146818_read_byte(index);
}

void nvram_write_byte(u32_t index ,int data)
{
  // FIXME: This write OP must be exclusive!
  // LOCK
  mc146818_write_byte(index ,data);
  // UNLOCK
}

#endif // End of USE_DRV_NVRAM;
