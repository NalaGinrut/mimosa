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

LDPATH := -L$(TOP)/lib -L$(TOP)/config -L$(OBJ)/
LDFLAGS := $(LDPATH) -T$(TOP)/kernel.ld -nostdlib -b binary

CFLAGS := $(CFLAGS) $(O_LEV) -fno-builtin -I$(INC) -MD -Wall -Wno-format -Wno-unused -Werror $(STABS)