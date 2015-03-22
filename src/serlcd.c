/* serlcd.c is part of ChibiAmpFirmware.
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

#include "serlcd.h"
#include "ch.h"
#include "hal.h"

void (*serLcdPrint)(char*,...) = 0;
static int lcdDelay_ms = 2;

void serLcdInit(void (*printFunc)(char*,...))
{
   serLcdPrint = printFunc;
   // CTRL-R @ 9600 baud during splash screen resets the module to 9600 baud
   printFunc("%c", 'R' - 64);
   chThdSleepMilliseconds(lcdDelay_ms);
   //serLcdBrightness(25);
   //serLcdClear();
}

void serLcdBrightness(uint8_t brightness)
{
   serLcdPrint("%c%c", 0x7C, 0x80 | brightness);
   chThdSleepMilliseconds(lcdDelay_ms);
}

void serLcdClear(void)
{
   serLcdPrint("%c%c", 0xFE, 0x01);
   chThdSleepMilliseconds(lcdDelay_ms);
}

void serLcdPos(uint8_t line, uint8_t pos)
{
   uint8_t posVal = 0;
   switch( line )
   {
      default:
      case 0:
         posVal = 0;
         break;
      case 1:
         posVal = 64;
         break;
      case 2:
         posVal = 16;
         break;
      case 3:
         posVal = 80;
         break;
   }
   
   posVal += pos;
   
   serLcdPrint("%c%c", 0xFE, 0x80 | posVal);
   chThdSleepMilliseconds(lcdDelay_ms);
}
