
OBJDIRS += bootloader

BOOT_OBJ := $(OBJ)/bootloader

BOOT_CFLAGS := $(CFLAGS) -D__MIMOSA_KERNEL__ $(STABS)

$(BOOT_OBJ)/boot.o: $(BOOT)/i386_boot.S $(BOOT)/boot_main.c 
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) -nostdlib $(BOOT_CFLAGS) -Os -r -o $@ $^

$(OBJ)/boot: $(BOOT_OBJ)/boot.o
	@echo + ld $@ from $^
	@mkdir -p $(@D)
	$(V)$(LD) -N -e start -Ttext 0x7C00 -o $@.1st $^
	$(V)$(OBJCOPY) -S -O binary $@.1st $@
	$(V)$(GUILE) -e main $(TOOLS)/sign.gl $(OBJ)/boot