# This is Makefile for kernel

OBJDIRS += kernel

K_LDPATH := -L$(TOP)/lib -L$(TOP)/config
K_LDFLAG := $(K_LDPATH) -T $(KERNEL)/kernel.ld -nostdlib -b binary

.PHONY: ktest

ktest:
	#@echo "$(K_LDFLAG)"
	ld -t ~/tmp/tt.o $(K_LDFLAG)

KERN_CFLAGS := $(CFLAGS) -D_MIMOSA_KERNEL $(STABS)
USER_CFLAGS := $(CFLAGS) -D_MIMOSA_USER $(STABS)


