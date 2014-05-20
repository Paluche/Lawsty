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
#include "trace.h"
#include <stdint.h>

// What I call a command, is a string ended by '\n\' or '\r'
size_t receive_cmd(uint8_t *buffer, size_t size)
{
    char rec;
    size_t rec_size = 0;
    do {
        rec = serial_getc();
        buffer[rec_size++] = rec;
    } while((rec != '\n') && (rec != '\r') && (rec_size < size));
    return rec_size;
}
