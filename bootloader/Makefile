TOPDIR	:= /work/current/basicmac/basicloader
FLAVOR	:= stm32lx
MCU	:= STM32L073Z

include $(TOPDIR)/build/boards/main.mk

# The bootloader (optionally) uses an LED to blink out diagnostics information
# after an exception occurs, and during installation of an update.
CDEFS	+= BOOT_LED_GPIO="GPIO('A',7,0)"
