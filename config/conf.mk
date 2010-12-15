# This file is config for "Make", you may change it as you will.

# "V = " for verbose, "V = @" for non-verbose
V := @ 

# Debug config
ifdef DEBUG
STABS := -gstabs
else
STABS := 
endif