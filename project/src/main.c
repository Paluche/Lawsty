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

// Helpers
#define PAL_SET_PAD(G,P)   palSetPad(G, G##_##P)
#define PAL_CLEAR_PAD(G,P) palClearPad(G, G##_##P)
int main(void)
{
    // HAL initialization, this also initializes the configured device drivers
    // and performs the board-specific initializations.
    halInit();

    // Kernel initialization, the main() function becomes a thread and the
    // RTOS is active.
    chSysInit();

    // Initialise the exti lines
    exti_init();

    int toggle_led_dmx   = 0;
    int toggle_rgb_led_r = 0;
    int toggle_rgb_led_g = 0;
    int toggle_rgb_led_b = 0;

    int  rslt_msk;
    for(;;) {
        rslt_msk = wait_button(ALL_SW_MSK);

        if (rslt_msk & PC0_SW_MSK) {
            if (toggle_led_dmx) {
                toggle_led_dmx = 0;
                PAL_SET_PAD(GPIOA, LED_DMX);
            } else {
                toggle_led_dmx = 1;
                PAL_CLEAR_PAD(GPIOA, LED_DMX);
            }
        }

        if (rslt_msk & PC1_SW_MSK) {
            if (toggle_rgb_led_r) {
                toggle_rgb_led_r = 0;
                PAL_SET_PAD(GPIOC, RGB_LED_R);
            } else {
                toggle_rgb_led_r = 1;
                PAL_CLEAR_PAD(GPIOC, RGB_LED_R);
            }
        }

        if (rslt_msk & PC2_SW_MSK) {
            if (toggle_rgb_led_g) {
                toggle_rgb_led_g = 0;
                PAL_SET_PAD(GPIOC, RGB_LED_G);
            } else {
                toggle_rgb_led_g = 1;
                PAL_CLEAR_PAD(GPIOC, RGB_LED_G);
            }
        }

        if (rslt_msk & PC3_SW_MSK) {
            if (toggle_rgb_led_b) {
                toggle_rgb_led_b = 0;
                PAL_SET_PAD(GPIOC, RGB_LED_B);
            } else {
                toggle_rgb_led_b = 1;
                PAL_CLEAR_PAD(GPIOC, RGB_LED_B);
            }
        }
    }
}
