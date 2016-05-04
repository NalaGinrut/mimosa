# tool chain def
MAKE	:= make
CC	:= $(GCCPREFIX)gcc -pipe
GCC_LIB := $(shell $(CC) -print-libgcc-file-name $(MIMOSA_BSP_CFLAGS))
AS	:= $(GCCPREFIX)as
AR	:= $(GCCPREFIX)ar
LD	:= $(GCCPREFIX)ld
OBJCOPY	:= $(GCCPREFIX)objcopy
OBJDUMP	:= $(GCCPREFIX)objdump
NM	:= $(GCCPREFIX)nm
CPP	:= $(GCCPREFIX)cpp

# Native commands
NCC	:= $(GCCPREFIX)gcc $(CC_VER) -pipe
TAR	:= gtar
GUILE	:= guile
SHELL   := /bin/bash

LDPATH := -L$(OBJ) -L$(CONF) -L$(TOP) 
LDFLAGS := $(LDPATH) -T$(TOP)/kernel.ld -nostdlib -E $(MIMOSA_BSP_LDFLAGS)

CFLAGS := $(CFLAGS) -O$(O_LEV) -nostdinc -fno-stack-protector -Wno-int-to-pointer-cast -Werror -Wpointer-arith -Wextra \
	-I$(INC) -MD -Wall -Wno-format -Wno-unused -std=gnu99 $(STABS) $(MIMOSA_BSP_CFLAGS) \
	$(MIMOSA_LIB_CFLAGS) $(MIMOSA_KERN_CFLAGS) $(MIMOSA_GENERIC_CFLAGS) $(MIMOSA_BSP_SPECIFIC) \
	$(MIMOSA_DRIVER_CFLAGS) -W
