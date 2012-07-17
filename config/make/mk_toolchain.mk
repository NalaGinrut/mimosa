# tool chain def
MAKE	:= gmake
CC	:= $(GCCPREFIX)gcc -pipe
GCC_LIB := $(shell $(CC) -print-libgcc-file-name $(MIMOSA_BSP_FLAGS))
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

CFLAGS := $(CFLAGS) -O$(O_LEV) -nostdinc -fno-builtin -fno-stack-protector \
	-I$(INC) -MD -Wall -Wno-format -Wno-unused -std=c99 $(STABS) $(MIMOSA_BSP_FLAGS)