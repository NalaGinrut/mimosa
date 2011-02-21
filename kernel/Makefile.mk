# This is Makefile for kernel

OBJDIRS += kernel

K_LDPATH := -L$(TOP)/lib -L$(TOP)/config -L~/tmp/
K_LDFLAG := $(K_LDPATH) -T$(TOP)/kernel.ld -nostdlib -b binary

KERN_CFLAGS := $(CFLAGS) -D_MIMOSA_KERNEL $(STABS)
USER_CFLAGS := $(CFLAGS) -D_MIMOSA_USER $(STABS)

.PHONY: ktest

ktest: ldscript
	@echo "$(K_LDFLAG)"
	ld -t ~/tmp/entry.o $(K_LDFLAG)



