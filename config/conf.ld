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
 * if you didn't set it, a default "256M" kernel will be set.
 */
/* kernel_mem = 0 */

/* 32bit cpu. Maybe I could write a more convenient GUI to set all these.
 */
k_mem_all = 0xFFFFFFFF;

/* You may set the "k_begin" directly */ 
/* k_begin = */












/* handle env ,DON'T MODIFY ANY THING BELOW! */
_k_size = DEFINED(kernel_mem) ? kernel_mem : 256;
k_size = _k_size * 0x100000;
k_begin = DEFINED(k_begin) ? k_begin : (k_mem_all - k_size);


