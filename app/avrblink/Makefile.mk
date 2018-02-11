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

OBJDIRS += app

APP_OBJ := $(OBJ)/app

app-cfile := $(wildcard $(APPDIR)/*.c)
app-ofile := $(app-cfile:.c=.o)
app-ofile := $(subst $(APPDIR)/,$(APP_OBJ)/,$(app-ofile))

APP_LDFLAGS := -r -nostdlib
APP_CFLAGS := $(CFLAGS) -D__MIMOSA_APP__ $(STABS) 

$(APP_OBJ)/%.o: $(APPDIR)/%.c
	@echo + cc $<
	@rm -f $(APPDIR)
	@ln -s $(APP) $(APPDIR)
	@mkdir -p $(@D)
	$(V)$(CC) $(APP_CFLAGS) -c -o $@ $<

$(OBJ)/app-obj: $(app-ofile)
	@echo + merge $@
	$(V)$(LD) $(APP_LDFLAGS) -o $@ $^
