ifeq (myowndevice,$(TARGET))
    MCU         := stm32l0
    LD_SCRIPTS  += $(BL)/src/arm/stm32lx/ld/STM32L0xxZ.ld
    DEFS        += -DSTM32L0 -DSTM32L073xx
    DEFS        += -DCFG_myowndevice_board
    DEFS        += -DBRD_IMPL_INC='"$(CURDIR)/brd_myowndevice.h"'
    FLAGS       += -I.
endif
