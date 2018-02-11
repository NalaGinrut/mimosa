# YOU MUST USE "-include", NOT "include"

-include $(BSPDIR)/Makefile.mk
ifneq ($(APPDIR),)
-include $(APPDIR)/Makefile.mk
endif
-include $(KERNEL)/Makefile.mk
-include $(LIB)/Makefile.mk
-include $(DRIVERS)/Makefile.mk

ifdef KDEBUG
-include $(DEBUG)/Makefile.mk
endif
