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
 *
 *  Module for interfacing the Digital to Analog converter
 */
/*
 * Initialisation of Digital to Analog Converter and function to set the
 * values of the output.
 */
#ifndef __DAC_H__
#define __DAC_H__

// Initialise Digital to Analog Convert peripheral according to our needs for
// the control of the K12N.
void init_dac(void);

// Set the values of the output.
// Channel 1 = X axis
// Channel 2 = Y axis
// values are between 0 and 4095
void set_dac(uint16_t val_ch1, uint16_t val_ch2);

#endif
