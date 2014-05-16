/*
 *  Lawsty - Laser with Style
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

/*
 * Event source
 */
static EVENTSOURCE_DECL(pc0_sw_evt);
static EVENTSOURCE_DECL(pc1_sw_evt);
static EVENTSOURCE_DECL(pc2_sw_evt);
static EVENTSOURCE_DECL(pc3_sw_evt);

/*
 * Event Listeners
 */
static EventListener pc0_sw_listener;
static EventListener pc1_sw_listener;
static EventListener pc2_sw_listener;
static EventListener pc3_sw_listener;

/*
 * Callback definition
 */
#define DEF_SW_PC_CB(N)                                                      \
    static void pc##N##_sw_cb(__attribute__ ((unused)) EXTDriver *extp,      \
                              __attribute__ ((unused)) expchannel_t channel) \
    {                                                                        \
        chSysLockFromIsr();                                                  \
        chEvtBroadcastFlagsI(&pc##N##_sw_evt, PC##N##_SW_MSK);               \
        chSysUnlockFromIsr();                                                \
    }

DEF_SW_PC_CB(0);
DEF_SW_PC_CB(1);
DEF_SW_PC_CB(2);
DEF_SW_PC_CB(3);

static const EXTConfig extcfg = {
    {
        // 0: GPIOC: PC0 switch
        {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC,
            pc0_sw_cb},

        // 1: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 2: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 3: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 4: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 5: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 6: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 7: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 8: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 9: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 10: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 11: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 12: Nothing
        {EXT_CH_MODE_DISABLED, NULL},

        // 13: GPIOC: PC1 switch
        {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC,
            pc1_sw_cb},

        // 14: GPIOC: PC2 switch
        {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC,
            pc2_sw_cb},

        // 15: GPIOC: PC3 switch
        {EXT_CH_MODE_FALLING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC,
            pc3_sw_cb},

        // 16: PVD output disabled
        {EXT_CH_MODE_DISABLED, NULL},

        // 17: RTC Alarm event disabled
        {EXT_CH_MODE_DISABLED, NULL},

        // 18: USB Device FS Wakeup events disabled
        {EXT_CH_MODE_DISABLED, NULL},
    }
};


// Initialise the EXT driver and register the buttons events to the current
// thread.
void exti_init(void)
{
    chEvtRegisterMask(&pc0_sw_evt, &pc0_sw_listener, PC0_SW_MSK);
    chEvtRegisterMask(&pc1_sw_evt, &pc1_sw_listener, PC1_SW_MSK);
    chEvtRegisterMask(&pc2_sw_evt, &pc2_sw_listener, PC2_SW_MSK);
    chEvtRegisterMask(&pc3_sw_evt, &pc3_sw_listener, PC3_SW_MSK);
    extStart(&EXTD1, &extcfg);
}

#define PAL_READ_PAD(G, P) palReadPad(G, G##_##P)

// Check the state of one or several buttons.
// Use the event mask to specified which button you want to check.
// Return the mask of the activated button(s).
int check_button(int bt_evt_msk)
{
    int rslt_msk = 0;

#define CHECK_PC(N)                              \
    if (bt_evt_msk & PC##N##_SW_MSK)             \
        if (!PAL_READ_PAD(GPIOC, PC##N))         \
            rslt_msk |= PC##N##_SW_MSK

    CHECK_PC(0);
    CHECK_PC(1);
    CHECK_PC(2);
    CHECK_PC(3);

    return rslt_msk;
}

// Wait for a push on one or several buttons specified by event mask.
// Return the mask of the activated button(s).
int wait_button(int bt_evt_msk)
{
    int rslt_msk = check_button(bt_evt_msk);

    while (! rslt_msk) {
        chEvtWaitOne(bt_evt_msk);
        rslt_msk = check_button(bt_evt_msk);
    }

    return rslt_msk;
}
