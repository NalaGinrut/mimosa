


INCLUDE conf.ld


SECTIONS
{

 . = KERNEL_BEGIN;

 PROVIDE(principio = KERNEL_BEGIN);

 .text : {
       . = ALIGN(8); *(.text) *(.stub .text.* .gnu.linkonce.t.*)
 }











 PROVIDE(etext = .);


 . = ALIGN((PGSIZE)); .rodata : { *(.rodata) *(.rodata.*) *(.gnu.linkonce.r.*) }


 .stab : {
       PROVIDE(__STAB_BEGIN__ = .); *(.stab); PROVIDE(__STAB_END__ = .);
       BYTE(0)


 }

 .stabstr : {
   PROVIDE(__STABSTR_BEGIN__ = .); *(.stabstr); PROVIDE(__STABSTR_END__ = .);
   BYTE(0)

 }


 . = ALIGN(PGSIZE);


 .data : {
       *(.data)
 }

 PROVIDE(edata = .);

 .bss : {
      PROVIDE(__bss_start = .); *(.bss) PROVIDE(__bss_end = .);
 }


 PROVIDE(recondo = .);




 .init : {
        *(.init)
 }
 PROVIDE(__mimosa_init_end = .);

}
