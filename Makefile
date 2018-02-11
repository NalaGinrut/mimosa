#  Copyright (C) 2010-2012, 2016
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

# default BSP is PC32
BSP := pc32
APP :=

all: kernel.ld
	#$(V)scripts/genconf.scm $(BSP)
	$(V)make mimosa
	@echo "Mimosa kernel generated!"

include $(CONF)/conf.mk
# DO NOT TOUCH!

mimosa-framework :=	$(OBJ)/entry.o \
			$(OBJ)/bsp-obj \
			$(OBJ)/kern-obj \
			$(OBJ)/lib-obj \
			$(OBJ)/drivers-obj
ifeq ($(KDEBUG),1)
mimosa-framework += $(OBJ)/debug-obj
endif

ifneq ($(APP),)
mimosa-framework += $(OBJ)/app-obj
endif

### TARGET ###
kernel.ld:
	@echo "Preparing $(BSP) BSP..."
	$(V)rm -f inc/bsp platform/bsp config/conf.ld
	$(V)ln -s $(BSP) platform/bsp
	$(V)ln -s ../platform/bsp/inc inc/bsp
	$(V)ln -s ../platform/bsp/conf.ld config/conf.ld
	$(V)if [ -n "$(APP)" ]; then rm -f $(APPDIR); ln -s $(APP) $(APPDIR); fi;
	$(V)$(CPP) kernel/kernel.cpp.ld -I$(INC) -okernel.ld
	$(V)sed -i "/^#.*/d" kernel.ld

mimosa: $(mimosa-framework)
	@echo + generate kernel image... from $^
	$(V)$(LD) $(LDFLAGS) -o $@ $^ $(GCC_LIB) 

$(OBJ)/mimosa.img: kernel.ld mimosa $(OBJ)/boot
	@echo + mk $@
	$(V)dd if=/dev/zero of=$(OBJ)/$(@F).bak count=10000
	$(V)dd if=$(OBJ)/boot.out of=$(OBJ)/$(@F).bak conv=notrunc 
	$(V)dd if=mimosa of=$(OBJ)/$(@F).bak seek=1 conv=notrunc 
	$(V)mv $(OBJ)/$(@F).bak $(OBJ)/$(@F)

.PHONY: echo pretty clean bochs grub qemu clean-isr

echo:
	@echo $(BSP)
	@echo $(MIMOSA_LIB_CFLAGS)
	@echo $(MIMOSA_BSP_LDFLAGS)

bochs: $(OBJ)/mimosa.img
	$(V)bochs

qemu: $(OBJ)/mimosa.img
	$(V)qemu-system-i386 --enable-kvm -hda $^ -m 32

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
	$(V)rm -fr *.ld *.log .sw{o,p}
	$(V)test -e $(OBJ) && rm -fr $(OBJ) || echo "No objs generated!"
	$(V)test -e mimosa && rm -f mimosa || echo "No kernel generated!"
	$(V)$(MAKE) pretty 
	$(V)$(MAKE) clean-isr
	$(V)rm -f inc/bsp platform/bsp config/conf.ld app/run
	$(V)rm -f *.hex *.eep
