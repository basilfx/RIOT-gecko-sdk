MODULE = gecko_sdk

DIRS += emlib/src emlib-extra/src 

ifneq (,$(filter rail,$(USEMODULE)))
  DIRS += radio
endif

include $(RIOTBASE)/Makefile.base
