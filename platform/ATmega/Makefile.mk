#  Copyright (C) 2016
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

OBJDIRS += bsp

BSP_OBJ := $(OBJ)/bsp

bsp-cfile := $(wildcard $(BSPDIR)/*.c)
bsp-ofile := $(bsp-cfile:.c=.o)
bsp-ofile := $(subst $(BSPDIR)/,$(BSP_OBJ)/,$(bsp-ofile))

BSP_LDFLAGS := -r -nostdlib $(MIMOSA_BSP_LDFLAGS)
BSP_CFLAGS := $(CFLAGS) -D__MIMOSA_KERNEL__ $(STABS) 

-include $(BSPDIR)/boot/Makefile.mk

# entry.o is a special object file. And entry.S should be 
# the unique Assemble File. If you want to use assembler for
# some purpose, you should consider the inlne assemble in C.
$(OBJ)/entry.o: $(BSPDIR)/entry.S
	@echo + as $<
	@mkdir -p $(@D)
	$(V)$(CC) $(BSP_CFLAGS) -c -o $@ $<

$(BSP_OBJ)/%.o: $(BSPDIR)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) $(BSP_CFLAGS) -c -o $@ $<

$(OBJ)/bsp-obj: $(bsp-ofile)
	@echo + merge $@
	$(V)$(LD) $(BSP_LDFLAGS) -o $@ $^
