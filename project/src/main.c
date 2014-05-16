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

#include "ch.h"
#include "hal.h"
#include "board.h"

/*
 * Application entry point.
 */
int main(void) {

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /*
   * Normal main() thread activity, in this demo it does nothing except
   * sleeping in a loop and check the button state.
   */
  while (TRUE) {
    palSetPad(GPIOC, GPIOC_RGB_LED_B);
    palClearPad(GPIOA, GPIOA_LED_DMX);
    chThdSleepMilliseconds(1000);
    palSetPad(GPIOA, GPIOA_LED_DMX);
    palClearPad(GPIOA, GPIOA_LED_ERR);
    chThdSleepMilliseconds(1000);
    palSetPad(GPIOA, GPIOA_LED_ERR);
    palClearPad(GPIOC, GPIOC_RGB_LED_R);
    chThdSleepMilliseconds(1000);
    palSetPad(GPIOC, GPIOC_RGB_LED_R);
    palClearPad(GPIOC, GPIOC_RGB_LED_G);
    chThdSleepMilliseconds(1000);
    palSetPad(GPIOC, GPIOC_RGB_LED_G);
    palClearPad(GPIOC, GPIOC_RGB_LED_B);
    chThdSleepMilliseconds(1000);
  }
}
