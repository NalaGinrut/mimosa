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


#include <elf.h>
#include <now/cpu/x86.h>
#include <now/bsp_bits.h>
#include <now/bsp_types.h>
#include "boot_main.h"


void cmain()
{
  
  Elf32_Phdr *prog_head ,*end_prog;
  
  //ptr to const
  const __u32_t *magic = (__u32_t*)elf_hdr;

  read_seg(elf_hdr ,SECTOR*BYTE ,0);
  
  if( *magic != ELF_MAGIC )
    {
#ifdef BOCHS_DEBUG
      goto bad_elf;
#else
      // TODO: show some error message;
      while(1);
#endif // End ifdef BOCHS_DEBUG;
    }

  prog_head = (Elf32_Phdr*)((__u32_t)elf_hdr + elf_hdr->e_phoff);
  end_prog = prog_head + prog_head->p_offset;//don't convert

  while( prog_head++ < end_prog )
    {
      read_seg(prog_head->p_vaddr & 0xFFFFFF,
	       prog_head->p_memsz,
	       prog_head->p_offset);
    }

  // NOTE: only 24bit addr for now is a trick; 
  ((entry_t)(elf_hdr->e_entry & 0xFFFFFF))();

#ifdef BOCHS_DEBUG
 bad_elf:
      port_wb(0x8A00 ,0x8A00);// enable bochs IO debug;
      port_wb(0x8A00 ,0x8E00);// 
#else

      // TODO: show some error message;

#endif // End ifdef BOCHS_DEBUG;

      while(1);


      // cmain should never return;
}

int read_seg(__u32_t va ,__u32_t count ,__u32_t byte_offset)
{
  __u32_t lba_offset = byte2lba(byte_offset);
  __u32_t addr = ROUND_DOWN(addr ,SECTOR);
  /* read n bytes once, you may change it;
   *  __u32_t n = 1;
   */
  
  for(;
      count-- > 0;
      sectors++ ,va += SECTOR)
    {
      read_sect((__u8_t*)addr ,1 ,lba_offset);
    }

  return 0;
}


int read_sect(void *dest ,__u32_t count ,__u32_t lba_offset)
{
  
  WAIT_DISK_READY;

  port_wb(HD0_HEAD ,HEAD(lba_offset) | LBA_PIO_28b);
  port_wb(HD0_SECT_CNT ,count);
  port_wb(HD0_SECT_N ,SECT(lba_offset));
  port_wb(HD0_CYL_L ,CY_L(lba_offset));
  port_wb(HD0_CYL_H ,CY_H(lba_offset));
  port_wb(HD0_CMD ,SECT_RR);

  WAIT_DISK_READY;

  port_rnb(HD0_DATA ,count);

  return 0;
}
