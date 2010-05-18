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

#ifndef MIMOSA_MULTI_BOOT_H
#define MIMOSA_MULTI_BOOT_H


#include "inc/types.h"

/* The magic number for the Multiboot header. */
#define MULTIBOOT_HEADER_MAGIC          0x1BADB002
     
/* The flags for the Multiboot header. */
#ifdef __ELF__
# define MULTIBOOT_HEADER_FLAGS         0x00000003
#else
# define MULTIBOOT_HEADER_FLAGS         0x00010003
#endif
     
/* The magic number passed by a Multiboot-compliant boot loader. */
#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002
     
/* The size of our stack (16KB). */
#define STACK_SIZE                      0x4000
      
/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
# define EXT_C(sym)                     _ ## sym
#else
# define EXT_C(sym)                     sym
#endif
     
#ifdef __ASSEMBLER__
/* Do not include here in boot.S. */
  
/* Types. */
   
#else // NO Assemble code;  
/* The Multiboot header. */
typedef struct multiboot_header
{
  u32_t magic;
  u32_t flags;
  u32_t checksum;
  u32_t header_addr;
  u32_t load_addr;
  u32_t load_end_addr;
  u32_t bss_end_addr;
  u32_t entry_addr;
} multiboot_header_t;
     
/* The symbol table for a.out. */
typedef struct aout_symbol_table
{
  u32_t tabsize;
  u32_t strsize;
  u32_t addr;
  u32_t reserved;
} aout_symbol_table_t;

/* The section header table for ELF. */
typedef struct elf_section_header_table
{
  u32_t num;
  u32_t size;
  u32_t addr;
  u32_t shndx;
} elf_section_header_table_t;

/* The Multiboot information. */
typedef struct multiboot_info
{
  u32_t flags;
  u32_t mem_lower;
  u32_t mem_upper;
  u32_t boot_device;
  u32_t cmdline;
  u32_t mods_count;
  u32_t mods_addr;
  union
  {
    aout_symbol_table_t aout_sym;
    elf_section_header_table_t elf_sec;
  } u;
  u32_t mmap_length;
  u32_t mmap_addr;
} multiboot_info_t;

/* The module structure. */
typedef struct module
{
  u32_t mod_start;
  u32_t mod_end;
  u32_t string;
  u32_t reserved;
} module_t;

/* The memory map. Be careful that the offset 0 is base_addr_low
   but no size. */
typedef struct memory_map
{
  u32_t size;
  u32_t base_addr_low;
  u32_t base_addr_high;
  u32_t length_low;
  u32_t length_high;
  u32_t type;
} memory_map_t;     

#endif // End of __ASSEMBLER__;

#endif // End of MIMOSA_MUTI_BOOT_H;
