/* printf.c is part of ChibiAmpFirmware.
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

#include "printf.h"
#include <chprintf.h>

static BaseSequentialStream* stdout_ss;

void init_printf(BaseSequentialStream* ss)
{
   stdout_ss=ss;
}

void ch_printf(char* fmt, ...)
{
   va_list va;
   va_start(va, fmt);
   chvprintf(stdout_ss, fmt, va);
   va_end(va);
}
