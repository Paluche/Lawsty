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
 * Definition of global helpers.
 */
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

// PAL helpers
#define PAL_SET_PAD(G,P)   palSetPad(G, G##_##P)
#define PAL_CLEAR_PAD(G,P) palClearPad(G, G##_##P)
#define PAL_READ_PAD(G, P) palReadPad(G, G##_##P)

// Register helpers
#define READ(Base, Reg, Bit)    (Base->Reg & (Base##_##Reg##_##Bit))
#define SET(Base, Reg, Bit)     ((Base->Reg) |= ((Base##_##Reg##_##Bit)))
#define UNSET(Base, Reg, Bit)   ((Base->Reg) &= !(Base##_##Reg##_##Bit))

#endif
