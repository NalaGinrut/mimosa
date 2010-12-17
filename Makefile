# This bachlor-Makefile follows the famous paper :
# "Recursive Make Considered Harmful"
# You may check it out here: http://aegis.sourceforge.net/auug97.pdf
# I must say, "recursive make" is pretty easier. But I trust the paper 
# author(Emm...actually I'm not sure), so...hope it works like the boast...
# God bless~ 
# NalaGinrut@gmail.com


# Never change these two var!!!
TOP := $(shell pwd)
CONF := $(TOP)/config
# Again! The Makefile framework is based on these two var. So let them alone!

include $(CONF)/conf.mk

CFLAGS := $(CFLAGS) $(DEFS) -O$(O_LEV) -fno-builtin -I$(INC) -MD -Wall -Wno-format -Wno-unused -Werror $(STABS)


.PHONY: pretty mtest

mtest:
	@echo "TOP: $(TOP)"
	@echo "LIB: $(LIB)"
	@echo "CONF: $(CONF)"
	@echo "MAKEFILE_LIST: $(MAKEFILE_LIST)"


pretty:
	@echo "Deleting backup file..."
	$(V)find . -name '*~' -exec rm {} \;
	@echo "It's pretty now!"
