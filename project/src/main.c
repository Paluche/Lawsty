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
#include "hal.h"
#include "exti.h"
#include "_dac.h"
#include "global.h"
#include "k12n.h"
#include "trace.h"

#include <string.h>

// Debug thread to know if the kernel stopped
static THD_WORKING_AREA(WA_led, (512));

__attribute__((noreturn)) msg_t led_thread(__attribute__((unused)) void *arg)
{
    for(;;) {
        PAL_SET_PAD(GPIOA, LED_DMX);
        chThdSleepMilliseconds(500);
        PAL_CLEAR_PAD(GPIOA, LED_DMX);
        chThdSleepMilliseconds(500);
    }
}

#define FORCE_DISPLAY 1
/*
 * SDIO configuration
 */
static const SDCConfig sdcfg = {
    0,
};

static uint8_t blkbuf[1024];

int main(void)
{
    // HAL initialization, this also initializes the configured device drivers
    // and performs the board-specific initializations.
    halInit();

    // Kernel initialization, the main() function becomes a thread and the
    // RTOS is active.
    chSysInit();

    // Initialization the exti lines
    // Not useful for now
    // exti_init();

    chThdCreateStatic(WA_led, sizeof WA_led, NORMALPRIO, led_thread, NULL);

    // Serial initialization
    serial_init();

    sdcStart(&SDCD1, &sdcfg);

    trace("/****** Waiting for card *****/\n\r");
    while(sdcConnect(&SDCD1)) ;

    PAL_CLEAR_PAD(GPIOA, LED_ERR);
    if (!sdcConnect(&SDCD1)) {
        trace("Card inserted\n\r");
        /* Single aligned read.*/
        int ret = sdcRead(&SDCD1, 0, blkbuf, 1);
        if (ret) {
            trace("Error single aligned read: %d\n\r", ret);
            goto exit;
        }
        /* Single unaligned read.*/
        ret = sdcRead(&SDCD1, 0, blkbuf + 1, 1);
        if (ret) {
            trace("Error single unaligned read: %d\n\r", ret);
            goto exit;
        }

        /* Multiple aligned read.*/
        ret = sdcRead(&SDCD1, 0, blkbuf, 4);
        if (ret) {
            trace("Error single unaligned read: %d\n", ret);
            goto exit;
        }

        /* Multiple unaligned read.*/
        ret = sdcRead(&SDCD1, 0, blkbuf + 1, 4);
        if (ret) {
            trace("Error single unaligned read: %d\n", ret);
            goto exit;
        }

        /* Repeated multiple aligned reads.*/
        for (int i = 0; i < 1000; i++) {
            ret = sdcRead(&SDCD1, 0, blkbuf, 4);
            if (ret) {
                trace("Error single unaligned read: %d\n", ret);
                goto exit;
            }
        }

        /* Repeated multiple unaligned reads.*/
        for (int i = 0; i < 1000; i++) {
            ret = sdcRead(&SDCD1, 0, blkbuf + 1, 4);
            if (ret) {
                trace("Error single unaligned read: %d\n", ret);
                goto exit;
            }
        }

        /* Repeated multiple aligned writes.*/
        for (int i = 0; i < 100; i++) {
            ret = sdcRead(&SDCD1, 0x10000, blkbuf, 4);
            if (ret) {
                trace("Error single unaligned read: %d\n", ret);
                goto exit;
            }

            ret = sdcWrite(&SDCD1, 0x10000, blkbuf, 4);
            if (ret) {
                trace("Error single unaligned read: %d\n", ret);
                goto exit;
            }

            ret = sdcWrite(&SDCD1, 0x10000, blkbuf, 4);
            if (ret) {
                trace("Error single unaligned read: %d\n", ret);
                goto exit;
            }
        }

        /* Repeated multiple unaligned writes.*/
        for (int i = 0; i < 100; i++) {
            ret = sdcRead(&SDCD1, 0x10000, blkbuf + 1, 4);
            if (ret) {
                trace("Error single unaligned read: %d\n", ret);
                goto exit;
            }
            ret = sdcWrite(&SDCD1, 0x10000, blkbuf + 1, 4);
            if (ret) {
                trace("Error single unaligned read: %d\n", ret);
                goto exit;
            }
            ret = sdcWrite(&SDCD1, 0x10000, blkbuf + 1, 4);
            if (ret) {
                trace("Error single unaligned read: %d\n", ret);
                goto exit;
            }
        }

        ret = sdcDisconnect(&SDCD1);
        if (ret) {
            trace("Error single unaligned read: %d\n", ret);
            goto exit;
        }
    }
exit:
    trace("/****** End of test ******/\r\n");
    for(;;)
        if (!sdcConnect(&SDCD1))
            PAL_CLEAR_PAD(GPIOA, LED_ERR);
        else
            PAL_SET_PAD(GPIOA, LED_ERR);

#if 0
    // Launch and initialization the laser with the timers
    init_laser();

    // Turn on the Laser
    //PAL_SET_PAD(GPIOA, LASER_ON);

    trace("Let's go\n\r");

    uint8_t buffer[124];
    for(;;) {
        size_t size = receive_cmd(buffer, 124);

        if (!memcmp((char *) buffer, "start", 5)) {
            start_laser();
            PAL_CLEAR_PAD(GPIOA, LED_ERR);
            serial_put(buffer, size);
            PAL_SET_PAD(GPIOA, LASER_ON);
        }

        if (!memcmp((char *) buffer, "stop", 4)) {
            stop_laser();
            PAL_SET_PAD(GPIOA, LED_ERR);
            PAL_CLEAR_PAD(GPIOA, LASER_ON);
        }
    }
#endif
}
