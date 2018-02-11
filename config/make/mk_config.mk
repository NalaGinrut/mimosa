# This file is config for "Make", you may change it as you will.

# Verbose config
# VERBOSE := 1

# Debug config
KDEBUG := 1

# Optimize config
# O_LEV := 

ifeq ($(BSP),pc32)
GCCPREFIX :=
# pc32 BSP config
MIMOSA_BSP_CFLAGS := -m32
MIMOSA_BSP_LDFLAGS := -m elf_i386

# Lib config
MIMOSA_LIB_CFLAGS := -DUSE_LIB_BITWISE -DUSE_LIB_MATH -DUSE_LIB_MEMCHR     \
		-DUSE_LIB_MEMCPY -DUSE_LIB_MEMMOVE -DUSE_LIB_MEMSET        \
		-DUSE_LIB_PRINTF -DUSE_LIB_READLINE -DUSE_LIB_STRCHR       \
		-DUSE_LIB_STRNCAT -DUSE_LIB_STRNCMP -DUSE_LIB_STRNCPY      \
		-DUSE_LIB_STRNDUP -DUSE_LIB_STRNLEN -DUSE_LIB_STRTOL

MIMOSA_KERN_CFLAGS := -DUSE_KERN_SHELL -DUSE_KERN_DEBUG

MIMOSA_GENERIC_CFLAGS := -DUSE_GENERIC_STREAM

MIMOSA_BSP_SPECIFIC :=  -DUSE_PC32_TRACE -DUSE_PC32_STAB -DUSE_PC32_DEBUG \
			-DPLATFORM_HAS_PAGE -DUSE_KERN_MALLOC \
			-DPLATFORM_HAS_TLB

MIMOSA_DRIVER_CFLAGS := -DUSE_DRV_RTC_MC14618 -DUSE_DRV_NVRAM \
			-DUSE_DRV_KBD -DUSE_DRV_CONSOLE
endif

## Atmega BSP config
ifeq ($(BSP),ATmega)
O_LEV := s
GCCPREFIX := avr-
KDEBUG :=
STABS :=
MIMOSA_BSP_CFLAGS := -fno-jump-tables -fpack-struct -fshort-enums -funsigned-bitfields
MIMOSA_BSP_LDFLAGS :=

MIMOSA_LIB_CFLAGS :=
MIMOSA_KERN_CFLAGS :=
MIMOSA_GENERIC_CFLAGS :=
MIMOSA_BSP_SPECIFIC :=
MIMOSA_DRIVER_CFLAGS :=

MCU := atmega32u4
TARGET := mimosa
AVRDUDE := avrdude
AVRDUDE_PROGRAMMER = avr109
AVRDUDE_PORT := /dev/ttyACM0
AVRDUDE_WRITE_FLASH := -U flash:w:$(TARGET).hex
AVRDUDE_BASIC := -p $(MCU) -P $(AVRDUDE_PORT) -c $(AVRDUDE_PROGRAMMER)
AVRDUDE_FLAGS := $(AVRDUDE_BASIC) $(AVRDUDE_NO_VERIFY) $(AVRDUDE_VERBOSE) $(AVRDUDE_ERASE_COUNTER)
AVR_CFLAGS := -mmcu=$(MCU) -I. $(CFLAGS)
AVR_ASFLAGS := -mmcu=$(MCU) -I. -x assembler-with-cpp $(ASFLAGS)
AVR_FORMAT := ihex

.PHONY: program

$(TARGET).hex: all
	$(OBJCOPY) -O $(AVR_FORMAT) -R .eeprom mimosa $@

$(TARGET).eep: all
	$(OBJCOPY) -j .eeprom --set-section-flags=.eeprom="alloc,load" --change-section-lma .eeprom=0 -O $(AVR_FORMAT) mimosa $@

program: $(TARGET).hex $(TARGET).eep
	$(V)$(AVRDUDE) $(AVRDUDE_FLAGS) $(AVRDUDE_WRITE_FLASH) $(AVRDUDE_WRITE_EEPROM) -b 57600 -v
endif
