#  Copyright (C) 2010-2012  
#	"Mu Lei" known as "NalaGinrut" <NalaGinrut@gmail.com>
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.


# This bachlor-Makefile follows the famous paper :
# <<Recursive Make Considered Harmful>>
# You may check it out here: http://aegis.sourceforge.net/auug97.pdf
# I must say, "recursive make" is pretty easier. But I trust the paper 
# author(Emm...actually I'm not sure), so...hope it works like the boast...
# God bless~ 
# NalaGinrut@gmail.com

# Never change these lines!!!
TOP := $(shell pwd)
CONF := $(TOP)/config
# Again! The Mimosa build framework is based on these lines. So let them alone!

all: kernel.ld mimosa 
	@echo "Mimosa kernel generated!\n"

include $(CONF)/conf.mk
# DO NOT TOUCH!

GCC_LIB := $(shell $(CC) -print-libgcc-file-name)

KERN_LDS := $(addsuffix -lds,kernel)

mimosa-framework := 	$(OBJ)/entry.o \
			$(OBJ)/bsp-obj \
			$(OBJ)/kern-obj \
			$(OBJ)/lib-obj \
			$(OBJ)/drivers-obj
ifdef KDEBUG
mimosa-framework += $(OBJ)/debug-obj
endif

### TARGET ###
mimosa: $(mimosa-framework)
	@echo + generate kernel image... from $^
	$(V)$(LD) $(LDFLAGS) -o $@ $^ $(GCC_LIB)

kernel.ld:
	$(V)$(MAKE) $(KERN_LDS)

$(OBJ)/mimosa.img: kernel.ld mimosa $(OBJ)/boot
	@echo + mk $@
	$(V)dd if=/dev/zero of=$(OBJ)/$(@F).bak count=10000
	$(V)dd if=$(OBJ)/boot.out of=$(OBJ)/$(@F).bak conv=notrunc 
	$(V)dd if=mimosa of=$(OBJ)/$(@F).bak seek=1 conv=notrunc 
	$(V)mv $(OBJ)/$(@F).bak $(OBJ)/$(@F)

.PHONY: pretty %-lds clean bochs grub qemu clean-isr

bochs: $(OBJ)/mimosa.img
	$(V)bochs

qemu: $(OBJ)/mimosa.img
	$(V)qemu -hda $^ -m 32

%-lds:
	$(V)$(CPP) $*/$*.cpp.ld -I$(INC) -o$*.ld
	$(V)sed -i "/^#.*/d" $*.ld

pretty:
	@echo "Deleting backup file..."
	$(V)find . -name '*~' -exec rm {} \;
	@echo "It's pretty now!"

clean-isr:
	@echo "Cleaning auto-generated ISR file..."
	$(V)find . -name 'isr.S' -exec rm {} \;
	@echo "Clean OK!"

clean:
	@echo "Cleaning all objs & generated files..."
	$(V)rm -frd *.ld *.log .sw{o,p}
	$(V)test -e $(OBJ) && rm -frd $(OBJ) || echo "No objs generated!"
	$(V)test -e mimosa && rm -f mimosa || echo "No kernel generated!"
	$(V)$(MAKE) pretty 
	$(V)$(MAKE) clean-isr

