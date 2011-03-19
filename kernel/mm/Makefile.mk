
MM := $(KERNEL)/mm

mm-cfile := $(wildcard $(MM)/*.c)
mm-ofile := $(mm-cfile:.c=.o)
mm-ofile := $(subst $(MM),$(KERN_OBJ),$(mm-ofile))

kernel-ofile += mm-ofile

$(KERN_OBJ)/%.o: $(MM)/%.c 
	@echo +cc $<
	@mkdir -p $(@D)
	$(V)$(CC) -nostdinc $(KERN_CFLAGS) -c -o $@ $<

