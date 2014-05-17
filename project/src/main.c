/*
 *  Lawsty - Laser with style
 *
 *  Copyright (C) 2014 Hubert Lefevre
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "ch.h"
#include "hal.h"
#include "exti.h"
#include "trace.h"
#include "dac.h"
#include "global.h"

/*
 * SDIO configuration.
 */
static const SDCConfig sdccfg = {
  0
};

// Debug thread to know if the kernel stopped
static WORKING_AREA(WA_led, (512));

__attribute__((noreturn)) msg_t led_thread(__attribute__((unused)) void *arg)
{
    for(;;) {
        PAL_SET_PAD(GPIOA, LED_DMX);
        chThdSleepMilliseconds(500);
        PAL_CLEAR_PAD(GPIOA, LED_DMX);
        chThdSleepMilliseconds(500);
    }
}

#define FORCE_DISPLAY 0

int main(void)
{
    // HAL initialization, this also initializes the configured device drivers
    // and performs the board-specific initializations.
    halInit();

    // Kernel initialization, the main() function becomes a thread and the
    // RTOS is active.
    chSysInit();

    // Initializes the exti lines
    exti_init();

    chThdCreateStatic(WA_led, sizeof WA_led, NORMALPRIO, led_thread, NULL);

    // Initializes DAC
    init_dac();

    // Activate amplifier
    PAL_SET_PAD(GPIOA, AMPLI_EN);

    PAL_CLEAR_PAD(GPIOA, LASER_ON);

    for(;;) {
        if (!PAL_READ_PAD(GPIOC, PC0) || FORCE_DISPLAY) {
            PAL_SET_PAD(GPIOA, LASER_ON);
            set_dac(0,0);
            chThdSleepMilliseconds(1);
            //PAL_SET_PAD(GPIOA, LASER_ON);
            chThdSleepMilliseconds(5);
            //PAL_CLEAR_PAD(GPIOA, LASER_ON);
            set_dac(0xffff, 0);
            chThdSleepMilliseconds(1);
            //PAL_SET_PAD(GPIOA, LASER_ON);
            chThdSleepMilliseconds(5);
            //PAL_CLEAR_PAD(GPIOA, LASER_ON);
            set_dac(0xffff,0xffff);
            chThdSleepMilliseconds(1);
            //PAL_SET_PAD(GPIOA, LASER_ON);
            chThdSleepMilliseconds(5);
            //PAL_CLEAR_PAD(GPIOA, LASER_ON);
            set_dac(0,0xffff);
            chThdSleepMilliseconds(1);
            //PAL_SET_PAD(GPIOA, LASER_ON);
            chThdSleepMilliseconds(5);
            //PAL_CLEAR_PAD(GPIOA, LASER_ON);
        } else {
            PAL_CLEAR_PAD(GPIOA, LASER_ON);
            set_dac(0x7fff, 0x7fff);
        }
    }
}
