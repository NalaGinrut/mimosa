# This is Makefile for kernel


OBJDIRS += kernel

KERN_OBJ := $(OBJ)/kernel

kernel-cfile := $(wildcard $(KERNEL)/*.c)
kernel-ofile := $(kernel-cfile:.c=.o)
kernel-ofile := $(subst $(KERNEL)/,$(KERN_OBJ)/,$(kernel-ofile))


KERN_LDFLAGS := -r -nostdlib 

KERN_CFLAGS := $(CFLAGS) -D__MIMOSA_KERNEL__ 
USER_CFLAGS := $(CFLAGS) -D__MIMOSA_USER__ 

-include $(KERNEL)/mm/Makefile.mk
-include $(KERNEL)/tm/Makefile.mk

$(KERN_OBJ)/%.o: $(KERNEL)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<

# NOTE: all %-obj generated must be in the $(OBJ),
# 	not KERN_OBJ, LIB_OBJ, etc...
$(OBJ)/kern-obj: $(kernel-ofile)
	@echo + merge $@
	$(V)$(LD) $(KERN_LDFLAGS) -o $@ $^


