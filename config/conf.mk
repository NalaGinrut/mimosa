# DON'T TOUCH ANYTHING BELOW!!!

MK_CONF := $(CONF)/make

include $(MK_CONF)/all_conf.mk

# Verbose handler
ifndef VERBOSE
V := @ # "V = " for verbose, "V = @" for non-verbose
else
V :=
endif

# Debug handler
ifdef DEBUG
STABS := -gstabs
else
STABS := 
endif

 
# Optimize handler
ifndef O_LEV
O_LEV := 0
endif


