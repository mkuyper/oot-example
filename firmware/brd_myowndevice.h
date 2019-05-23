// Copyright (C) 2016-2019 Semtech (International) AG. All rights reserved.
//
// This file is subject to the terms and conditions defined in file 'LICENSE',
// which is part of this source code package.

// to be included from board.h

// -------------------------------------------
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
