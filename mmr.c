# 1 "platform/bsp/entry.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "platform/bsp/entry.S"
# 25 "platform/bsp/entry.S"
###############
# Text Segment
###############

.text
# 48 "platform/bsp/entry.S"
.globl _start
_start:
 movw $POST_WORM_BOOT ,BDA_POST_RESET

 call set_gdt




set_gdt:
 lgdt ((init_gdt_desc) - KERN_BEGIN)
 movl $KD_SEL ,%eax # set data seg_desc


 movw %ax ,%ds # data segment
 movw %ax ,%es # extra segment
 movw %ax ,%ss # stack segment

 ljmp $KD_SEL ,$init_cee_env

set_cee_env:
 movl $0 ,%ebp # clear ebp to terminate the backtrace
 movl $tmp_stack_top ,%esp

 # jump into the Cee code~yeah~I hate ASM!
 call platform_init

 # TODO: I need a debugger to check the reason why it returned.
return_is_error:

 jmp return_is_error
# 92 "platform/bsp/entry.S"
.extern KERNEL_BEGIN
.set FULL_ADDR ,0xFFFFFFFF

.data



.p2align PGSHIFT

.globl tmp_stack
tmp_stack:
 .space KERNEL_STACK_SIZE
.globl tmp_stack_top
# 116 "platform/bsp/entry.S"
 .p2align 2
init_gdt:
 SEG_NULL
 SEG(USEG_X|USEG_R ,((0) - KERN_BEGIN) ,FULL_ADDR) # code segment
 SEG(USEG_W ,((0) - KERN_BEGIN) ,FULL_ADDR) # data segment
init_gdt_desc:
 .word 0x17
 .long ((init_gdt_desc) - KERN_BEGIN)
