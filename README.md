# Basic MAC Out-of-Tree Example

This example demonstrates how to setup an out-of-tree project that uses a
custom board for both [Basic MAC](https://github.com/lorabasics/basicmac) and
Basic Loader.

The actual firmware is simply a copy of the *ex-join* example that is part of
Basic MAC.

## Preparation

At the time of writing, there is a small bug that prevent out-of-tree builds
for Basic Loader and one that prevents out-of-tree builds with custom boards
for Basic MAC projects. 

Apply the supplied patches,
[basicloader.patch](https://github.com/mkuyper/oot-example/blob/master/basicloader.patch)
and
[basicmac.patch](https://github.com/mkuyper/oot-example/blob/master/basicmac.patch)
to the respective repositories until such time that these bugs are fixed
upstream.

## Bootloader

Creating a Basic Loader variant for a new board of an already supported MCU is
very simple. Simply create a Makefile in a new directory and set the `TOPDIR`
variable to the Basic Loader directory, specify the flavor and MCU:

[bootloader/Makefile](https://github.com/mkuyper/oot-example/blob/master/bootloader/Makefile)
```make
TOPDIR  := /work/current/basicmac/basicloader
FLAVOR  := stm32lx
MCU     := STM32L073Z

include $(TOPDIR)/build/boards/main.mk

# The bootloader (optionally) uses an LED to blink out diagnostics information
# after an exception occurs, and during installation of an update.
CDEFS   += BOOT_LED_GPIO="GPIO('A',7,0)"
```

Then, you can simply type `make` in that directory to build the
bootloader.hex file.

## Firmware

To build a Basic MAC firmware project out-of-tree, you need to set the `TOPDIR`
variable to the Basic MAC directory in the Makefile and include the
`$(TOPDIR)/projects/project.gmk` file:

[firmware/Makefile](https://github.com/mkuyper/oot-example/blob/master/firmware/Makefile)
```make
TOPDIR := /work/current/basicmac

...

include $(TOPDIR)/projects/projects.gmk
```

Further, to build for a custom board, which we'll call **myowndevice** in this
example, you'll need to create a *family makefile* that will set up the build
environment for this target:

[firmware/target.mk](https://github.com/mkuyper/oot-example/blob/master/firmware/target.mk)
```make
ifeq (myowndevice,$(TARGET))
    MCU         := stm32l0
    LD_SCRIPTS  += $(BL)/src/arm/stm32lx/ld/STM32L0xxZ.ld
    DEFS        += -DSTM32L0 -DSTM32L073xx
    DEFS        += -DCFG_myowndevice_board
    DEFS        += -DBRD_IMPL_INC='"$(CURDIR)/brd_myowndevice.h"'
endif
```

As you can see, this setup calls for a custom *board implementation header
file*, `brd_myowndevice.h`, which will be included in the build. This file
contains macro definitions for radio type, peripherals, and GPIOs used:

[firmware/brd_myowndevice.h](https://github.com/mkuyper/oot-example/blob/master/firmware/brd_myowndevice.h)
```c
#if defined(CFG_myowndevice_board)

// Use the SX1276
#define BRD_sx1276_radio

// GPIOs connected to the SX1276
#define GPIO_RST	BRD_GPIO(PORT_B, 10)       // PB10
#define GPIO_DIO0	BRD_GPIO(PORT_B, 11)       // PB11
#define GPIO_DIO1	BRD_GPIO(PORT_C, 13)       // PC13
#define GPIO_DIO2	BRD_GPIO(PORT_B, 9)        // PB9
#define GPIO_DIO3	BRD_GPIO(PORT_B, 4)        // PB4, not used by stack
#define GPIO_DIO4	BRD_GPIO(PORT_B, 3)        // PB3, not used by stack
#define GPIO_DIO5	BRD_GPIO(PORT_A, 15)       // PA15, not used by stack

// SPI bus connection to the SX1276
#define BRD_RADIO_SPI	2                          // SPI2
#define GPIO_NSS	BRD_GPIO(PORT_B, 12)       // PB12
#define GPIO_SCK	BRD_GPIO_AF(PORT_B, 13, 0) // PB13, alternate function 0
#define GPIO_MISO	BRD_GPIO_AF(PORT_B, 14, 0) // PB14, alternate function 0
#define GPIO_MOSI	BRD_GPIO_AF(PORT_B, 15, 0) // PB15, alternate function 0

// UART for debug output
#define BRD_DBG_UART	1                          // UART1
#define GPIO_DBG_TX	BRD_GPIO_AF(PORT_A, 9, 4)  // PA9, alternate function 4

#endif
```

Finally, the Makefile must set our custom target and add the custom family
makefile to the list of family makefiles:

[firmware/Makefile](https://github.com/mkuyper/oot-example/blob/master/firmware/Makefile)
```make
TARGET := myowndevice

...

FAM_MAKEFILES += target.mk
```

And now, you are ready to type `make`!
