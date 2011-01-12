#ifndef	__MIMOSA_BOOT_MAIN_H
#define __MIMOSA_BOOT_MAIN_H
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
#include <now/bsp_bits.h>

#define BYTE	8
#define SECTOR	512

#define HD0_DATA	0x01F0	// data register;
#define HD0_SECT_CNT	0x01F2	// sector count;
#define HD0_SECT_N	0x01F3	// sector number;
#define HD0_CYL_L	0x01F4	// cylinder low;
#define HD0_CYL_H	0x01F5	// cylinder high;
#define HD0_HEAD	0x01F6	// drive head
#define HD0_STATS	0x01F7	// status;
#define HD0_CMD		0x01F7 	// cmd;

#define HD0_READY	_B(6)	// device ready;
#define HD0_CMD_E	_B(7)	// Executing a cmd;
#define HD0_OK		(HD0_READY & ~HD0_CMD_E)
#define SECT_RR		0x20 	// read sector with retry;

#define LBA_PIO_28b	0xE0
#define LBA_PIO_48b	0x40

#define SECT(addr)	((__u8_t)(addr))
#define CY_L(addr)	((__u8_t)((addr)>>8))
#define CY_H(addr)	((__u8_t)((addr)>>16))
#define HEAD(addr)	((__u8_t)((addr)>>24))

#define WAIT_DISK_READY					\
  while( (port_rb(HD0_STATS) & (HD0_READY | HD0_CMD_E))	\
	 != HD0_OK );



#define elf_hdr ((Elf32_Ehdr *) 0x1000)

#define byte2lba(_b)	((_b)/SECTOR + 1)
#define down2sect(addr)	((addr) & (__u32_t)(-SECTOR))

int read_seg(__u32_t ,__u32_t ,__u32_t);
int read_sect(void ,__u32_t ,__u32_t);




#endif // End of __MIMOSA_BOOT_MAIN_H;
