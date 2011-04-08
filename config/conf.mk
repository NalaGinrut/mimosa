# DON'T TOUCH ANYTHING BELOW!!!

MK_CONF := $(CONF)/make

# Verbose handler
ifndef VERBOSE
V := @ # "V = " for verbose, "V = @" for non-verbose
else
V :=
endif

# Debug handler
KDEBUG := 1

ifdef KDEBUG
STABS := -gstabs
else
STABS := 
endif


# Optimize handler
ifndef O_LEV
O_LEV := 0
endif

# this line must be the last line ,DO NOT CHANGE IT!
include $(MK_CONF)/all_conf.mk

