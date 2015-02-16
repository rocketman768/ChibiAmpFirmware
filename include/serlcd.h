/* serlcd.h is part of ChibiAmpFirmware.
 *
 * ChibiAmpFirmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ChibiAmpFirmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ChibiAmpFirmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _SERLCD_H
#define _SERLCD_H

/*!
 * This module is for the SerLCD v2.5 backpack from Sparkfun
 */

#include <inttypes.h>

extern void (*serLcdPrint)(char*,...);

//! \brief Initialize the serLcd module with the given print function.
void serLcdInit(void (*printFunc)(char*,...));
//! \brief set \c brightness in [0,29]
void serLcdBrightness(uint8_t brightness);
//! \brief Clear the display
void serLcdClear(void);
//! \brief Move cursor to given \c line and character \c pos
void serLcdPos(uint8_t line, uint8_t pos);

#endif /* _SERLCD_H*/
