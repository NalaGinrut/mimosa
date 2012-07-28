#  Copyright (C) 2012
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


# This is Makefile for inner Scheme system

OBJDIRS += scheme

KERN_OBJ := $(OBJ)/scheme

scheme-cfile := $(wildcard $(SCHEME)/*.c)
scheme-ofile := $(scheme-cfile:.c=.o)
scheme-ofile := $(subst $(SCHEME)/,$(KERN_OBJ)/,$(scheme-ofile))


SCHEME_LDFLAGS := -r -nostdlib

## we need 8bit enums ,but seems only for GCC.
SCHEME_CFLAGS := $(CFLAGS) -fshort-enums 

$(SCHEME_OBJ)/%.o: $(SCHEME)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) $(SCHEME_CFLAGS) -c -o $@ $<

# NOTE: all %-obj generated must be in the $(OBJ),
# 	not KERN_OBJ, LIB_OBJ, etc...
$(OBJ)/scheme-obj: $(scheme-ofile)
	@echo + merge $@
	$(V)$(LD) $(SCHEME_LDFLAGS) -o $@ $^

