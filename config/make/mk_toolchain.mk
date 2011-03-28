# tool chain def
MAKE	:= gmake
CC	:= $(GCCPREFIX)gcc -pipe
GCC_LIB := $(shell $(CC) -print-libgcc-file-name)
AS	:= $(GCCPREFIX)as
AR	:= $(GCCPREFIX)ar
LD	:= $(GCCPREFIX)ld
OBJCOPY	:= $(GCCPREFIX)objcopy
OBJDUMP	:= $(GCCPREFIX)objdump
NM	:= $(GCCPREFIX)nm
CPP	:= $(GCCPREFIX)cpp

# Native commands
NCC	:= gcc $(CC_VER) -pipe
TAR	:= gtar
GUILE	:= guile

LDPATH := -L$(OBJ) -L$(CONF) -L$(TOP)
LDFLAGS := $(LDPATH) -T$(TOP)/kernel.ld -nostdlib 

CFLAGS := $(CFLAGS) $(O_LEV) -nostdinc -fno-builtin -I$(INC) -MD -Wall -Wno-format -Wno-unused -Werror -std=c99 $(STABS)