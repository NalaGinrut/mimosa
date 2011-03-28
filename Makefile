# This bachlor-Makefile follows the famous paper :
# <<Recursive Make Considered Harmful>>
# You may check it out here: http://aegis.sourceforge.net/auug97.pdf
# I must say, "recursive make" is pretty easier. But I trust the paper 
# author(Emm...actually I'm not sure), so...hope it works like the boast...
# God bless~ 
# NalaGinrut@gmail.com


# Never change these lines!!!
TOP := $(shell pwd)
CONF := $(TOP)/config
# Again! The Mimosa build framework is based on these lines. So let them alone!

all: kernel.ld mimosa 
	@echo "Mimosa kernel generated!\n"

include $(CONF)/conf.mk
-include $(BSP)/Makefile.mk
-include $(KERNEL)/Makefile.mk
-include $(LIB)/Makefile.mk
# DO NOT TOUCH!

KERN_LDS := $(addsuffix -lds,kernel)

mimosa-framework := 	$(OBJ)/entry.o	\
			$(OBJ)/bsp-obj	\
			$(OBJ)/kern-obj		
			#$(OBJ)/lib-obj

mimosa: $(mimosa-framework)
	@echo + generate kernel image... from $^
	$(V)$(LD) $(LDFLAGS) -o $@ $^

kernel.ld:
	$(V)$(MAKE) $(KERN_LDS)

.PHONY: pretty %-lds clean  

%-lds:
	$(V)$(CPP) $*/$*.cpp.ld -I$(INC) -o$*.ld
	$(V)sed -i "/^#.*/d" $*.ld

pretty:
	@echo "Deleting backup file..."
	$(V)find . -name '*~' -exec rm {} \;
	@echo "It's pretty now!"

clean:
	@echo "Cleaning all objs & generated files..."
	$(V)rm -frd *.ld
	$(V)test -e $(OBJ) && rm -frd $(OBJ) || echo "No objs generated!"
	$(V)test -e mimosa && rm -f mimosa || echo "No kernel generated!"
	$(V)$(MAKE) pretty 


