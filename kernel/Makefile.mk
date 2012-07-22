#  Copyright (C) 2010-2011  
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


# This is Makefile for kernel


OBJDIRS += kernel

KERN_OBJ := $(OBJ)/kernel

kernel-cfile := $(wildcard $(KERNEL)/*.c)
kernel-ofile := $(kernel-cfile:.c=.o)
kernel-ofile := $(subst $(KERNEL)/,$(KERN_OBJ)/,$(kernel-ofile))


KERN_LDFLAGS := -r $(LDFLAGS)

KERN_CFLAGS := $(CFLAGS) -D__MIMOSA_KERNEL__ 
USER_CFLAGS := $(CFLAGS) -D__MIMOSA_USER__ 

-include $(KERNEL)/mm/Makefile.mk
-include $(KERNEL)/tm/Makefile.mk

$(KERN_OBJ)/%.o: $(KERNEL)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) $(KERN_CFLAGS) -c -o $@ $<

# NOTE: all %-obj generated must be in the $(OBJ),
# 	not KERN_OBJ, LIB_OBJ, etc...
$(OBJ)/kern-obj: $(kernel-ofile)
	@echo + merge $@
	$(V)$(LD) $(KERN_LDFLAGS) -o $@ $^


