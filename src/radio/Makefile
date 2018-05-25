MODULE = gecko_sdk_librail

RAIL_SDK_SRCDIR = $(PKGDIRBASE)/gecko_sdk/dist/radio/rail_lib

ifeq ($(EFM32_FAMILY),efr32mg1p)
  RAIL_LIB = $(RAIL_SDK_SRCDIR)/autogen/librail_release/librail_efr32xg1_gcc_release.a
endif
ifeq ($(EFM32_FAMILY),efr32mg12p)
  RAIL_LIB = $(RAIL_SDK_SRCDIR)/autogen/librail_release/librail_efr32xg12_gcc_release.a
endif
ifeq ($(EFM32_FAMILY),efr32mg13p)
  RAIL_LIB = $(RAIL_SDK_SRCDIR)/autogen/librail_release/librail_efr32xg13_gcc_release.a
endif
ifeq ($(EFM32_FAMILY),efr32fg14p)
  RAIL_LIB = $(RAIL_SDK_SRCDIR)/autogen/librail_release/librail_efr32xg14_gcc_release.a
endif

$(BINDIR)/$(MODULE).a:
	cp $(RAIL_LIB) $@
