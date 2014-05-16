/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _BOARD_H_
#define _BOARD_H_

/*
 * Setup for the Olimex STM32-P103 proto board.
 */

/*
 * Board identifier.
 */
#define BOARD_PULSE_2010
#define BOARD_NAME              "PULSE"

/*
 * Board frequencies.
 */
#define STM32_LSECLK            0
#define STM32_HSECLK            8000000

/*
 * MCU type, supported types are defined in ./os/hal/platforms/hal_lld.h.
 */
#define STM32F10X_LD

/*
 * IO pins assignments.
 */
#define GPIOA_LED_DMX           0
#define GPIOA_LED_ERR           1
#define GPIOA_AMPLI_EN          2
#define GPIOA_MICRO             3
#define GPIOA_K12N_X            4
#define GPIOA_K12N_Y            5
#define GPIOA_LASER_ON          6
// GPIOA7 unused
#define GPIOA_ETH_INT           8
#define GPIOA_USART1_TX         9
#define GPIOA_USART1_RX         10
#define GPIOA_USBDM             11
#define GPIOA_USBDP             12
// GPIOA13 JTAG
// GPIOA14 JTAG
// GPIOA15 JTAG

// GPIOB0 Unused
// GPIOB1 Unused
#define GPIOB_BOOT1             2
// GPIOB3 JTAG
// GPIOB4 JATG NJTRST
// GPIOB5 Unused
// GPIOB6 Unused
// GPIOB7 Unused
// GPIOB8 Unused
// GPIOB9 Unused
#define GPIOB_DMX_TX            10
#define GPIOB_DMX_RX            11
#define GPIOB_ETH_CS            12
#define GPIOB_ETH_CLK           13
#define GPIOB_ETH_MISO          14
#define GPIOB_ETH_MOSI          15

#define GPIOC_PC0               0
#define GPIOC_RGB_LED_R         1
#define GPIOC_RGB_LED_G         2
#define GPIOC_RGB_LED_B         3
#define GPIOC_THERM1            4
#define GPIOC_THERM2            5
#define GPIOC_SDIO_WP           6
#define GPIOC_SDIO_CD           7
#define GPIOC_SDIO_DAT0         8
#define GPIOC_SDIO_DAT1         9
#define GPIOC_SDIO_DAT2         10
#define GPIOC_SDIO_DAT3         11
#define GPIOC_SDIO_CLK          12
#define GPIOC_PC1               13
#define GPIOC_PC2               14
#define GPIOC_PC3               15

#define GPIOD_SDIO_CMD          2
/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 *
 * The digits have the following meaning:
 *   0 - Analog input.
 *   1 - Push Pull output 10MHz.
 *   2 - Push Pull output 2MHz.
 *   3 - Push Pull output 50MHz.
 *   4 - Digital input.
 *   5 - Open Drain output 10MHz.
 *   6 - Open Drain output 2MHz.
 *   7 - Open Drain output 50MHz.
 *   8 - Digital input with PullUp or PullDown resistor depending on ODR.
 *   9 - Alternate Push Pull output 10MHz.
 *   A - Alternate Push Pull output 2MHz.
 *   B - Alternate Push Pull output 50MHz.
 *   C - Reserved.
 *   D - Alternate Open Drain output 10MHz.
 *   E - Alternate Open Drain output 2MHz.
 *   F - Alternate Open Drain output 50MHz.
 * Please refer to the STM32 Reference Manual for details.
 */

/*
 * Port A setup.
 * Everything input with pull-up (8) except:
 * PA0  LED_DMX           Output pushpull  3
 * PA1  LED_ERR           Output pushpull  3
 * PA2  AMPLI_EN          Output pushpull  3
 * PA3  MICRO             Analog input     0
 * PA4  K12N_X            Alternate Output B  DAC
 * PA5  K12N_Y            Alternate Output B  DAC
 * PA6  LASER_ON          Output pushpull  3
 *
 * PA8  ETH_INT           Alternate Output B
 * PA9  USART1_TX         Alternate Output B
 * PA10 USART1_RX         Digital Input    4
 * PA11 USBDM             Digital Input    4
 * PA12 USBDP             Digital Input    4
 */
#define VAL_GPIOACRL            0x83BB0333      /*  PA7...PA0 */
#define VAL_GPIOACRH            0x888444BB      /* PA15...PA8 */
#define VAL_GPIOAODR            0xFFFFFFFF

/*
 * Port B setup.
 * Everything input with pull-up except:
 * PB10 DMX_TX            Alternate Output B
 * PB11 DMX_RX            Digital input    4
 * PB12 ETH_CS            Alternate Output B
 * PB13 ETH_CLK           Alternate Output B
 * PB14 ETH_MISO          Digital input    4
 * PB15 ETH_MOSI          Alternate Output B
 */
#define VAL_GPIOBCRL            0x88888888      /*  PB7...PB0 */
#define VAL_GPIOBCRH            0xB4BB4B88      /* PB15...PB8 */
#define VAL_GPIOBODR            0xFFFFFFFF

/*
 * Port C setup.
 * Everything input with pull-up except:
 * PC0  PC0               Digital Input    4
 * PC1  RGB_LED_R         Output pushpull  3
 * PC2  RGB_LED_G         Output pushpull  3
 * PC3  RGB_LED_B         Output pushpull  3
 * PC4  THERM1            Analog Input     0
 * PC5  THERM2            Analog Input     0
 * PC6  SDIO_WP           Digital Input    4
 * PC7  SDIO_CD           Input Pull-up    8
 *
 * PC8  SDIO_DAT0         Alternate Output B
 * PC9  SDIO_DAT1         Alternate Output B
 * PC10 SDIO_DAT2         Alternate Output B
 * PC11 SDIO_DAT3         Alternate Output B
 * PC12 SDIO_CLK          Alternate Output B
 * PC13 PC1               Digital Input    4
 * PC14 PC2               Digital Input    4
 * PC15 PC3               Digital Input    4
 */
#define VAL_GPIOCCRL            0x44003334      /*  PC7...PC0 */
#define VAL_GPIOCCRH            0x444BBBBB      /* PC15...PC8 */
#define VAL_GPIOCODR            0xFFFFFFFF

/*
 * Port D setup.
 * Everything input with pull-up except:
 * PD0 XTAL               Normal input     4
 * PD1 XTAL               Normal input     4
 * PD2 SDIO_CMD           Alternate Output B
 */
#define VAL_GPIODCRL            0x88888B44      /*  PD7...PD0 */
#define VAL_GPIODCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIODODR            0xFFFFFFFF

/*
 * Port E setup.
 * Everything input with pull-up except:
 * NO GPIO B on STM32F103RE
 */
#define VAL_GPIOECRL            0x88888888      /*  PD7...PD0 */
#define VAL_GPIOECRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIOEODR            0xFFFFFFFF

/*
 * Port F setup.
 * Everything input with pull-up except:
 * NO GPIO B on STM32F103RE
 */
#define VAL_GPIOFCRL            0x88888888      /*  PD7...PD0 */
#define VAL_GPIOFCRH            0x88888888      /* PD15...PD8 */
#define VAL_GPIOFODR            0xFFFFFFFF


/*
 * USB bus activation macro, required by the USB driver.
 */
// NO USB Pullup control
#define usb_lld_connect_bus(usbp)

/*
 * USB bus de-activation macro, required by the USB driver.
 */
// NO USB Pullup control
#define usb_lld_disconnect_bus(usbp)

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
    void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* _BOARD_H_ */
