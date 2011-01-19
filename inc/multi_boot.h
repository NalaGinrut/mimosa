#ifndef __MIMOSA_MULTI_BOOT_H
#define __MIMOSA_MULTI_BOOT_H
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



#include "types.h"

/* How many bytes from the start of the file we search for the header. */
#define MULTIBOOT_SEARCH		8192

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

/* The bits in the required part of flags field we don't support.  */
#define MULTIBOOT_UNSUPPORTED		0x0000fffc

/* Alignment of multiboot modules.  */
#define MULTIBOOT_MOD_ALIGN		0x00001000

/* Alignment of the multiboot info structure.  */
#define MULTIBOOT_INFO_ALIGN		0x00000004

/*
 * Flags set in the 'flags' member of the multiboot header.
 */

/* Align all boot modules on i386 page (4KB) boundaries.  */
#define MULTIBOOT_PAGE_ALIGN		0x00000001

/* Must pass memory information to OS.  */
#define MULTIBOOT_MEMORY_INFO		0x00000002

/* Must pass video information to OS.  */
#define MULTIBOOT_VIDEO_MODE		0x00000004

/* This flag indicates the use of the address fields in the header.  */
#define MULTIBOOT_AOUT_KLUDGE		0x00010000

/*
 *  Flags to be set in the 'flags' member of the multiboot info structure.
 */

/* is there basic lower/upper memory information? */
#define MULTIBOOT_INFO_MEMORY		0x00000001
/* is there a boot device set? */
#define MULTIBOOT_INFO_BOOTDEV		0x00000002
/* is the command-line defined? */
#define MULTIBOOT_INFO_CMDLINE		0x00000004
/* are there modules to do something with? */
#define MULTIBOOT_INFO_MODS		0x00000008

/* These next two are mutually exclusive */

/* is there a symbol table loaded? */
#define MULTIBOOT_INFO_AOUT_SYMS	0x00000010
/* is there an ELF section header table? */
#define MULTIBOOT_INFO_ELF_SHDR		0x00000020

/* is there a full memory map? */
#define MULTIBOOT_INFO_MEM_MAP		0x00000040

/* Is there drive info?  */
#define MULTIBOOT_INFO_DRIVE_INFO	0x00000080

/* Is there a config table?  */
#define MULTIBOOT_INFO_CONFIG_TABLE	0x00000100

/* Is there a boot loader name?  */
#define MULTIBOOT_INFO_BOOT_LOADER_NAME	0x00000200

/* Is there a APM table?  */
#define MULTIBOOT_INFO_APM_TABLE	0x00000400

/* Is there video information?  */
#define MULTIBOOT_INFO_VIDEO_INFO	0x00000800

     
/* The size of our stack (16KB). */
#define STACK_SIZE                      0x4000
      


//FIXME: move these EXT_C macro to a proper header file;
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

struct grub_multiboot_header
{
  /* Must be MULTIBOOT_MAGIC - see above.  */
  u32_t magic;

  /* Feature flags.  */
  u32_t flags;

  /* The above fields plus this one must equal 0 mod 2^32. */
  u32_t checksum;

  /* These are only valid if MULTIBOOT_AOUT_KLUDGE is set.  */
  u32_t header_addr;
  u32_t load_addr;
  u32_t load_end_addr;
  u32_t bss_end_addr;
  u32_t entry_addr;

  /* These are only valid if MULTIBOOT_VIDEO_MODE is set.  */
  u32_t mode_type;
  u32_t width;
  u32_t height;
  u32_t depth;
};

struct grub_multiboot_info
{
  /* Multiboot info version number */
  u32_t flags;

  /* Available memory from BIOS */
  u32_t mem_lower;
  u32_t mem_upper;

  /* "root" partition */
  u32_t boot_device;

  /* Kernel command line */
  u32_t cmdline;

  /* Boot-Module list */
  u32_t mods_count;
  u32_t mods_addr;

  u32_t syms[4];

  /* Memory Mapping buffer */
  u32_t mmap_length;
  u32_t mmap_addr;

  /* Drive Info buffer */
  u32_t drives_length;
  u32_t drives_addr;

  /* ROM configuration table */
  u32_t config_table;

  /* Boot Loader Name */
  u32_t boot_loader_name;

  /* APM table */
  u32_t apm_table;

  /* Video */
  u32_t vbe_control_info;
  u32_t vbe_mode_info;
  u16_t vbe_mode;
  u16_t vbe_interface_seg;
  u16_t vbe_interface_off;
  u16_t vbe_interface_len;
};

struct grub_multiboot_mmap_entry
{
  u32_t size;
  u64_t addr;
  u64_t len;
#define GRUB_MULTIBOOT_MEMORY_AVAILABLE		1
#define GRUB_MULTIBOOT_MEMORY_RESERVED		2
  u32_t type;
} __attribute__((packed));

struct grub_mod_list
{
  /* the memory used goes from bytes 'mod_start' to 'mod_end-1' inclusive */
  u32_t mod_start;
  u32_t mod_end;

  /* Module command line */
  u32_t cmdline;

  /* padding to take it to 16 bytes (must be zero) */
  u32_t pad;
};

#endif // End of !__ASSEMBLER__;

#endif // End of __MIMOSA_MUTI_BOOT_H;
