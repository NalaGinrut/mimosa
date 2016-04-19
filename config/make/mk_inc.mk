# YOU MUST USE "-include", NOT "include"

-include $(BSPDIR)/Makefile.mk
-include $(KERNEL)/Makefile.mk
-include $(LIB)/Makefile.mk
-include $(DRIVERS)/Makefile.mk

ifdef KDEBUG
-include $(DEBUG)/Makefile.mk
endif
