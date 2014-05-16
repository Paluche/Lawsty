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
 * Initialisation of Digital to Analog Converter and function to set the
 * values of the output.
 */
#include "stm32f10x.h"
#include "hal.h"
#include "global.h"

// Initialise Digital to Analog Convert peripheral according to our needs for
// the control of the K12N.
void init_dac(void)
{
    uint32_t dac_cr_val = DAC->CR;

    // No independent trigger
    // No wave generation
    // Default value for triangle amplitude.
    // Disable output buffer
    dac_cr_val &= !(DAC_CR_TEN1  | DAC_CR_TEN2  |
                    DAC_CR_WAVE1 | DAC_CR_WAVE2 |
                    DAC_CR_MAMP1 | DAC_CR_MAMP2 |
                    DAC_CR_BOFF1 | DAC_CR_BOFF2);

    // Enable DAC channel 1 and 2
    dac_cr_val |= DAC_CR_EN1 | DAC_CR_EN2;
    DAC->CR = dac_cr_val;
}

// Set the values of the output.
// Channel 1 = X axis
// Channel 2 = Y axis
void set_dac(uint16_t val_ch1, uint16_t val_ch2)
{
    DAC->DHR12LD = val_ch1 << 16 | val_ch2;
}
