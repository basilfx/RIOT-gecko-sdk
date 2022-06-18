MODULE = gecko_sdk_librail

ifeq ($(EFM32_FAMILY),efr32mg1p)
  RAIL_LIB = $(CURDIR)/librail_efr32xg1_gcc_release.a
endif
ifeq ($(EFM32_FAMILY),efr32mg12p)
  RAIL_LIB = $(CURDIR)/librail_efr32xg12_gcc_release.a
endif
ifeq ($(EFM32_FAMILY),efr32mg13p)
  RAIL_LIB = $(CURDIR)/librail_efr32xg13_gcc_release.a
endif
ifeq ($(EFM32_FAMILY),efr32fg14p)
  RAIL_LIB = $(CURDIR)/librail_efr32xg14_gcc_release.a
endif

$(BINDIR)/$(MODULE).a: $(RAIL_LIB)
	cp $< $@
