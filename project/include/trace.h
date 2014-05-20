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
 * Macros for serial.
 */
#ifndef __SERIAL_H__
#define __SERIAL_H__

#include "hal.h"
#include "chprintf.h"

// USART1 configuration
static const SerialConfig sdconfig = {
    9600,
    0,
    0,
    0
};

#define serial_init()    sdStart(&SD1, &sdconfig);

// Characters
#define serial_getc()    sdGet(&SD1);
#define serial_putc(c)   sdPut(&SD1, c);

// Get/put s characters from/to the serial
#define serial_get(b, s) sdRead(&SD1, b, s)
#define serial_put(b, s) sdWrite(&SD1, b, s);

// Equivalent printf function
#define trace(...)       chprintf((BaseSequentialStream *) &SD1, __VA_ARGS__)

// Receive what I call a command, a string ended by '\n\' and '\r'
size_t receive_cmd(uint8_t *buffer, size_t size);

#endif
