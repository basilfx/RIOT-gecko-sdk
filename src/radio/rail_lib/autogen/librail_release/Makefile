MODULE = gecko_sdk_librail

ifeq ($(EFM32_LIBRAIL_BLOB_NAME),)
	$(error EFM32_LIBRAIL_BLOB_NAME not specified!)
endif

RAIL_LIB = $(CURDIR)/librail_$(EFM32_LIBRAIL_BLOB_NAME)_gcc_release.a

$(BINDIR)/$(MODULE).a: $(RAIL_LIB)
	cp $< $@
