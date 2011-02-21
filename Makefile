# This bachlor-Makefile follows the famous paper :
# <<Recursive Make Considered Harmful>>
# You may check it out here: http://aegis.sourceforge.net/auug97.pdf
# I must say, "recursive make" is pretty easier. But I trust the paper 
# author(Emm...actually I'm not sure), so...hope it works like the boast...
# God bless~ 
# NalaGinrut@gmail.com


# Never change these three lines!!!
TOP := $(shell pwd)
CONF := $(TOP)/config
# Again! The Makefile framework is based on these three lines. So let them alone!

include $(CONF)/conf.mk
-include $(KERNEL)/Makefile.mk
-include $(PLATFORM)/Makefile.mk

CFLAGS := $(CFLAGS) $(DEFS) -O$(O_LEV) -fno-builtin -I$(INC) -MD -Wall -Wno-format -Wno-unused -Werror $(STABS)

kernel-ld := $(addsuffix -lds,kernel)

all: 
	$(V)test -e "kernel.ld" || { echo "no!"; false; }

.PHONY: pretty mtest %-lds clean ldscript

ldscript:
	$(V)make $(kernel-ld)

%-lds:
	$(V)$(CPP) $*/$*.cpp.ld -I$(INC) -o$*.ld
	$(V)sed -i "/^#/d" $*.ld

mtest:
	@echo "TOP: $(TOP)"
	@echo "LIB: $(LIB)"
	@echo "CONF: $(CONF)"
	@echo "MAKEFILE_LIST: $(MAKEFILE_LIST)"


pretty:
	@echo "Deleting backup file..."
	$(V)find . -name '*~' -exec rm {} \;
	@echo "It's pretty now!"

clean:
	@echo "Cleaning all objs & generated files..."
	$(V)rm -frd *.ld
	$(V)test -e "$(OBJ)" && rm -frd $(OBJ) || echo "No objs generated!"
	$(V)make pretty 


