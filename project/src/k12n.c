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
/*
 * Definition of a function controlling the different parameters to display
 * pictures with the laser through the k12n scanner.
 */
#include "hal.h"
#include "dac.h"
#include "global.h"

// We are going to use the ILDA image format.
// ILDA_Coodrdinate Header constant
#define ILDA_C_HEADER_SZ                  32
#define ILDA_C_HEADER_ID                  0
#define ILDA_C_HEADER_ID_SZ               4
#define ILDA_C_HEADER_ZEROS               4
#define ILDA_C_HEADER_ZEROS_SZ            3
#define ILDA_C_HEADER_FORMAT              7
#define ILDA_C_HEADER_FORMAT_SZ           1
#define ILDA_C_HEADER_COMPANY             16
#define ILDA_C_HEADER_COMPANY_SZ          8
#define ILDA_C_HEADER_TOTAL_PT            24
#define ILDA_C_HEADER_TOTAL_PT_SZ         2
#define ILDA_C_HEADER_FRAME_NB            27
#define ILDA_C_HEADER_FRAME_NB_SZ         2
#define ILDA_C_HEADER_TOTAL_FRAMES        28
#define ILDA_C_HEADER_TOTAL_FRAMES_SZ     2
#define ILDA_C_HEADER_SCANNER_HEAD        30
#define ILDA_C_HEADER_SCANNER_HEAD_SZ     1

// ILDA coordinate data
// NOTE: The position of the following depends on if the files represents 2D
// or 3D frames.
#define ILDA_C_DATA_SZ_2D                 6
#define ILDA_C_DATA_SZ_3D                 8
#define ILDA_C_X_COORDINATES              0
#define ILDA_C_X_COORDINATES_SZ           2
#define ILDA_C_Y_COORDINATES              2
#define ILDA_C_Y_COORDINATES_SZ           2
#define ILDA_C_Z_COORDINATES              4
#define ILDA_C_Z_COORDINATES_SZ           2
#define ILDA_C_STATUS_CODE_2D             4
#define ILDA_C_STATUS_CODE_3D             6
#define ILDA_C_STATUS_CODE_SZ             2
#define ILDA_STATUS_CODE_PT_COLOR_NB_MSK  0x000f
#define ILDA_STATUS_CODE_BLANK__MSK       0x4000
#define ILDA_STATUS_CODE_LAST_POINT_MSK   0x8000

// We are a single color laser, we don't care about the color table.


// We are going to use two timers to synchronised the display. One to
// synchronised the diplay of the point, the other to synchronised the switch
// between frames.

// NOTE: This is a test for the timer, the purpose is to draw a rectangle
// handled by timer 2, which shape is changed by timer 3.
#define HALF_WIDTH_MIN 0
#define HALF_WIDTH_MAX 0x7ffe

// Timer 3 variables (also used by timer 2)
static uint16_t rect_x_half_width = HALF_WIDTH_MIN;
static uint16_t rect_y_half_width = HALF_WIDTH_MIN;

#define CENTER  0x7fff
#define X_MIN   (CENTER - rect_x_half_width)
#define X_MAX   (CENTER + rect_x_half_width)
#define Y_MIN   (CENTER - rect_y_half_width)
#define Y_MAX   (CENTER + rect_y_half_width)

// Timer 2 variables
static uint16_t current_x   = CENTER - HALF_WIDTH_MIN;
static uint16_t current_y   = CENTER - HALF_WIDTH_MIN;
static int      current_axe = 0;
#define INCREMENT 600

static void tim2_cb(__attribute__((unused)) GPTDriver *gptp)
{

    switch (current_axe) {
        case 0: // Increasing X
            if (current_x + INCREMENT < X_MAX)
                current_x += INCREMENT;
            else {
                current_x = X_MAX;
                current_axe++;
            }
            break;

        case 1: // Increasing Y
            if (current_y + INCREMENT < Y_MAX)
                current_y += INCREMENT;
            else {
                PAL_CLEAR_PAD(GPIOC, RGB_LED_G);
                current_y = Y_MAX;
                current_axe++;
            }
            break;

        case 2: // Decreasing X
            if (current_x - INCREMENT > X_MIN)
                current_x -= INCREMENT;
            else {
                current_x = X_MIN;
                current_axe++;
            }
            break;

        case 3: // Decreasing Y
            if (current_y - INCREMENT > Y_MIN)
                current_y -= INCREMENT;
            else {
                current_y = Y_MIN;
                current_axe = 0;
            }
            break;
        default:
            // Go back to initial point
            current_x = X_MIN;
            current_y = Y_MIN;
            current_axe = 0;

    }
    set_dac(current_x, current_y);
}

#define INCREMENT2 600
static int move = 0;
static void tim3_cb(__attribute__((unused)) GPTDriver *gptp)
{
    switch (move) {
        case 0:
            // Increase X width
            if (rect_x_half_width + INCREMENT2 < HALF_WIDTH_MAX)
                rect_x_half_width += INCREMENT2;
            else {
                rect_x_half_width = HALF_WIDTH_MAX;
                move++;
            }
            break;

        case 1:
            // Increase Y width
            if (rect_y_half_width + INCREMENT2 < HALF_WIDTH_MAX)
                rect_y_half_width += INCREMENT2;
            else {
                rect_y_half_width = HALF_WIDTH_MAX;
                move++;
            }
            break;

        case 2:
            // Decrease X and Y width
            if ((rect_x_half_width - INCREMENT2 > HALF_WIDTH_MIN) &&
                (rect_y_half_width - INCREMENT2 > HALF_WIDTH_MIN)) {
                rect_x_half_width -= INCREMENT2;
                rect_y_half_width -= INCREMENT2;
            } else {
                rect_x_half_width = HALF_WIDTH_MIN;
                rect_y_half_width = HALF_WIDTH_MIN;
                move++;
            }
            break;

        case 3:
            // Increase X and Y width
            if ((rect_x_half_width + INCREMENT2 < HALF_WIDTH_MAX) &&
                (rect_y_half_width + INCREMENT2 < HALF_WIDTH_MAX)) {
                rect_x_half_width += INCREMENT2;
                rect_y_half_width += INCREMENT2;
            } else {
                rect_x_half_width = HALF_WIDTH_MAX;
                rect_y_half_width = HALF_WIDTH_MAX;
                move++;
            }
            break;

        case 4:
            // Decrease Y width
            if (rect_y_half_width - INCREMENT2 > HALF_WIDTH_MIN)
                rect_y_half_width -= INCREMENT2;
            else {
                rect_y_half_width = HALF_WIDTH_MIN;
                move++;
            }
            break;


        case 5:
            // Decrease X width
            if (rect_x_half_width - INCREMENT2 > HALF_WIDTH_MIN)
                rect_x_half_width -= INCREMENT2;
            else {
                rect_x_half_width = HALF_WIDTH_MIN;
                move = 0;
            }
            break;

        default:
            // Back to initial state
            rect_x_half_width = HALF_WIDTH_MIN;
            rect_y_half_width = HALF_WIDTH_MIN;
            move = 0;
            break;
    }
}

static const GPTConfig tim2_cfg = {
    40000,
    tim2_cb,
    0
};

static const GPTConfig tim3_cfg = {
    10000,
    tim3_cb,
    0
};

void init_laser(void)
{
    // DAC initialisation
    init_dac();

    // Activate amplifier
    PAL_SET_PAD(GPIOA, AMPLI_EN);

    // Timers initialisation
    gptStart(&GPTD2, &tim2_cfg);
    gptPolledDelay(&GPTD2, 10);

    gptStart(&GPTD3, &tim3_cfg);
    gptPolledDelay(&GPTD3, 10);

    PAL_CLEAR_PAD(GPIOA, LASER_ON);
}

void start_laser(void)
{
    // Start Timers
    gptStartContinuous(&GPTD2, 2);
    gptStartContinuous(&GPTD3, 400);
}

void stop_laser(void)
{
    // Start Timers
    gptStopTimer(&GPTD2);
    gptStopTimer(&GPTD3);
}
