MODULE = gecko_sdk

DIRS += emlib/src emlib-extra/src

ifneq (,$(filter gecko_sdk_librail,$(USEMODULE)))
  DIRS += radio/rail_lib/autogen/librail_release
endif

ifneq (,$(filter gecko_sdk_librail_pa,$(USEMODULE)))
  DIRS += radio/rail_lib/plugin/pa-conversions
endif

include $(RIOTBASE)/Makefile.base
