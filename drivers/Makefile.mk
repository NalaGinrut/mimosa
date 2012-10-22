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


DRIVERS := drivers
DRV_OBJ:= $(OBJ)/drivers

#BSP-MODULES := $(DRIVERS)/%.c

drv-cfile := $(wildcard $(DRIVERS)/*.c)
drv-ofile := $(drv-cfile:.c=.o)
drv-ofile := $(subst $(DRIVERS)/,$(DRV_OBJ)/,$(drv-ofile))

DRV_LDFLAGS := -r -nostdlib $(MIMOSA_BSP_LDFLAGS)
DRV_CFLAGS := $(CFLAGS) -D__MIMOSA_KERNEL__ 

$(DRV_OBJ)/%.o : $(DRIVERS)/%.c
	@echo + cc $<
	@mkdir -p $(@D)
	$(V)$(CC) -nostdinc $(DRV_CFLAGS) -c -o $@ $<

$(OBJ)/drivers-obj: $(drv-ofile)
	@echo + merge $@
	$(V)$(LD) $(DRV_LDFLAGS) -o $@ $^
