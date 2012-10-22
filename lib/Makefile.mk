# This is Makefile for kernel lib

OBJDIRS += lib

LIB_OBJ := $(OBJ)/lib

lib-cfile := $(wildcard $(LIB)/*.c)
lib-ofile := $(lib-cfile:.c=.o)
lib-ofile := $(subst $(LIB)/,$(LIB_OBJ)/,$(lib-ofile))


LIB_LDFLAGS := -r -nostdlib $(MIMOSA_BSP_LDFLAGS)
LIB_CFLAGS := $(CFLAGS) -D__MIMOSA_KERNEL__


$(LIB_OBJ)/%.o: $(LIB)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) $(LIB_CFLAGS) -c -o $@ $<

$(OBJ)/lib-obj: $(lib-ofile)
	@echo + merge $@
	$(V)$(LD) $(LIB_LDFLAGS) -o $@ $^