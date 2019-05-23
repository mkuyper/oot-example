# Basic MAC Out-of-Tree Example

This example demonstrates how to setup an out-of-tree project that uses a
custom board for both Basic MAC and Basic Loader.

## Preparation

At the time of writing, there is a small bug that prevent out-of-tree builds for Basic Loader and one that prevents out-of-tree builds with custom boards for Basic MAC projects. 

## Bootloader

Creating a Basic Loader variant for a new board of an already supported MCU is
very simple. Simply create a Makefile in a new directory and set the `TOPDIR`
variable to the Basic Loader directory, specify the flavor and MCU:

https://github.com/mkuyper/oot-example/blob/f6f3f8b78bd36c661912c975c5d2f9a28e882133/bootloader/Makefile#L1-L9

```make
TOPDIR  := /work/current/basicmac/basicloader
FLAVOR  := stm32lx
MCU     := STM32L073Z

include $(TOPDIR)/build/boards/main.mk

# The bootloader (optionally) uses an LED to blink out diagnostics information
# after an exception occurs, and during installation of an update.
CDEFS   += BOOT_LED_GPIO="GPIO('A',7,0)"
```
