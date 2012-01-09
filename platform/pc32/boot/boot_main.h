#ifndef	__MIMOSA_BOOT_MAIN_H
#define __MIMOSA_BOOT_MAIN_H
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

#include <bsp/bsp_types.h>
#include <bsp/bsp_bits.h>

#define BYTE	8
#define SECTOR	512

#define HDC_DATA	0x01F0	// data register;
#define HDC_SECT_CNT	0x01F2	// sector count;
#define HDC_SECT_N	0x01F3	// sector number;
#define HDC_CYL_L	0x01F4	// cylinder low;
#define HDC_CYL_H	0x01F5	// cylinder high;
#define HDC_HEAD	0x01F6	// drive head
#define HDC_STATS	0x01F7	// status;
#define HDC_CMD		0x01F7 	// cmd;

#define HDC_READY	_B(6)	// device ready;
#define HDC_CMD_E	_B(7)	// Executing a cmd;
#define HDC_OK		(HDC_READY & ~HDC_CMD_E)
#define SECT_RR		0x20 	// read sector with retry;

#define LBA_PIO_28b	0xE0
#define LBA_PIO_48b	0x40

#define SECT(lba)	((__u8_t)(lba))
#define CY_L(lba)	((__u8_t)((lba)>>8))
#define CY_H(lba)	((__u8_t)((lba)>>16))
#define HEAD(lba)	((__u8_t)((lba)>>24))

#define WAIT_FOR_DISK_READY					\
  while( (port_rb(HDC_STATS) & (HDC_READY | HDC_CMD_E))	\
	 != HDC_OK );



#define elf_hdr ((Elf32_Ehdr *) 0x1000)

#define byte2lba(_b)	((_b)/SECTOR + 1)
#define down2sect(addr)	((addr) & (__u32_t)(-SECTOR))

int read_seg(__u32_t ,__u32_t ,__u32_t);
int read_sect(void* ,__u32_t ,__u32_t);




#endif // End of __MIMOSA_BOOT_MAIN_H;
