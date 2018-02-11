.text

.global _start
.extern platform_init /* C function must be declared as .extern in AVR asm code */
        
_start:
        /* TODO: do something init, maybe stack clean? */
        /* NOTE: AVR asm in gcc seems not support AT&T style */
        mov     r1, 0    /* r1 must be 0 before calling C function */
	rcall   platform_init /* `call' is not supported by AVR2 model */
