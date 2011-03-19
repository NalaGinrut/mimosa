
TM := $(KERNEL)/tm

$(KERN_OBJ)/%.o: $(TM)/%.c 
	@echo +cc $<
	@mkdir -p $(@D)
	$(V)$(CC) -nostdinc $(KERN_CFLAGS) -c -o $@ $<