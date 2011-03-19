
OBJDIRS += bsp

BSP_OBJ := $(OBJ)/bsp

bsp-cfile := $(wildcard $(BSP)/*.c)
bsp-ofile := $(bsp-cfile:.c=.o)
bsp-ofile := $(subst $(BSP)/,$(BSP_OBJ)/,$(bsp-ofile))

BSP_LDFLAGS := -r -nostdlib $(LDFLAGS)
BSP_CFLAGS := $(CFLAGS) -D__MIMOSA_KERNEL__ $(STABS)

-include $(BSP)/drivers/Makefile.mk

# entry.o is a special object file. And entry.S should be 
# the unique Assemble File. If you want to use assembler for
# some purpose, you should consider the inlne assemble in C.
$(OBJ)/entry.o: $(BSP)/entry.S
	@echo + as $<
	@mkdir -p $(@D)
	$(V)$(CC) -nostdinc $(BSP_CFLAGS) -c -o $@ $<

$(BSP_OBJ)/%.o: $(BSP)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) -nostdinc $(BSP_CFLAGS) -c -o $@ $<

$(OBJ)/bsp-obj: $(bsp-ofile)
	$echo + merge $@
	$(V)$(CC) $(BSP_CFLAGS) -o $@ $^

