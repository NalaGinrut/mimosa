/* This is linker config
 * You may modify this file to change the linker's behaviour,
 * BUT LEAVE ALONE ANY OTHER ld script!!!
 */

/* TODO: I must write a convenient script(guile?) to custom these
 * env properly.
 */
OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)


/* set "kernel_mem" the kernel size you want, 
 * if you didn't set it, a default "1024M" kernel will be set.
 * unit: MB
 */
/* kernel_mem = 0 */

/* 32bit cpu. Maybe I could write a more convenient GUI to set all these.
 */
__LD_32b_ALL = 0xFFFFFFFF;

/* You may set the "k_begin" directly */ 
/* k_begin = */












/* handle env ,DON'T MODIFY ANY THING BELOW! */
___K_LD_SIZE = DEFINED(__K_LD_MEM) ? __K_LD_MEM : 1024; /* unit: MB */
__K_LD_SIZE = ___K_LD_SIZE * 0x100000;
___K_LD_BEGIN = __LD_32b_ALL - __K_LD_SIZE + 0x100000;
__K_LD_BEGIN = DEFINED(LD_KERN_BEGIN) ? LD_KERN_BEGIN : ___K_LD_BEGIN;
