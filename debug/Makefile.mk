
OBJDIRS += debug

DEBUG_OBJ := $(OBJ)/debug

debug-cfile := $(wildcard $(DEBUG)/*.c)
debug-ofile := $(debug-cfile:.c=.o)
debug-ofile := $(subst $(DEBUG)/,$(DEBUG_OBJ)/,$(debug-ofile))


DEBUG_LDFLAGS := -r -nostdlib $(MIMOSA_BSP_LDFLAGS)
DEBUG_CFLAGS := $(CFLAGS) -D__MIMOSA_KERNEL__ -gstabs

$(DEBUG_OBJ)/%.o: $(DEBUG)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) $(DEBUG_CFLAGS) -c -o $@ $<

$(OBJ)/debug-obj: $(debug-ofile)
	@echo + merge $@
	$(V)$(LD) $(DEBUG_LDFLAGS) -o $@ $^