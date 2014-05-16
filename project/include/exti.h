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
#ifndef __EXTI_H__
#define __EXTI_H__

// Event masks
#define PC0_SW_MSK (1 << 0)
#define PC1_SW_MSK (1 << 1)
#define PC2_SW_MSK (1 << 2)
#define PC3_SW_MSK (1 << 3)
#define ALL_SW_MSK 0xf

// Initialise the EXT driver and register the buttons events to the current
// thread.
void exti_init(void);

// Check the state of one or several buttons.
// Use the event mask to specified which button you want to check.
// Return the mask of the activated button(s).
int check_button(int bt_evt_msk);

// Wait for a push on one or several buttons specified by event mask.
// Return the mask of the activated button(s).
int wait_button(int bt_evt_msk);

#endif
