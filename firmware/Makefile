TOPDIR := /work/current/basicmac

TARGET := myowndevice
#TARGET := b_l072z_lrwan1
#TARGET := nucleo_l053r8-sx1276mbed
#TARGET := nucleo_l053r8-sx1261mbed
#TARGET := nucleo_l053r8-sx1262mbed

VARIANTS := eu868 us915 hybrid simul

REGIONS.simul := eu868
TARGET.simul := unicorn

FAM_MAKEFILES += target.mk

CFLAGS += -Os
CFLAGS += -g
CFLAGS += -Wall -Wno-main

SVCS += app

DEFS += -DDEBUG_RX
DEFS += -DDEBUG_TX

LMICCFG += eeprom_keys
LMICCFG += DEBUG
LMICCFG += extapi

include $(TOPDIR)/projects/projects.gmk

ifeq (simul,$(VARIANT))
test: build-$(VARIANT)/$(PROJECT).hex
	PYTHONPATH=$${PYTHONPATH}:$(TOPDIR)/tools/pylora:$(TOPDIR)/unicorn/simul \
		   $(TOPDIR)/unicorn/simul/lwtest.py \
		   -r EU868 \
		   -v -d -t \
		   $(TESTOPTS) \
		   $(BL)/build/boards/$(BL_BRD)/bootloader.hex \
		   $<
endif


.PHONY: test
