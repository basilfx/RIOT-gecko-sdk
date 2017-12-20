MODULE = gecko_sdk_librail

RAIL_LIB_VERSION ?=1.1

RAIL_SDK_SRCDIR = $(PKGDIRBASE)/gecko_sdk/dist/radio/rail_lib_v$(RAIL_LIB_VERSION)

ifeq ($(EFM32_FAMILY),efr32mg1p)
	RAIL_LIB = $(RAIL_SDK_SRCDIR)/autogen/librail_release/librail_efr32xg1_gcc_release.a
endif
ifeq ($(EFM32_FAMILY),efr32mg12p)
	RAIL_LIB = $(RAIL_SDK_SRCDIR)/autogen/librail_release/librail_efr32xg12_gcc_release.a
endif
ifeq ($(EFM32_FAMILY),efr32mg13p)
	RAIL_LIB = $(RAIL_SDK_SRCDIR)/autogen/librail_release/librail_efr32xg13_gcc_release.a
endif

$(BINDIR)/$(MODULE).a: 
	        cp $(RAIL_LIB) $@

