/* printf.h is part of ChibiAmpFirmware.
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

#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdarg.h>
#include <ch.h>
#include <chstreams.h>

/*!
 * \brief Initialize printf with a "stdout" stream
 *
 * Can safely cast things like SerialDriver objects to BaseSequentialStream
 */
void init_printf(BaseSequentialStream* ss);
void ch_printf(char* fmt, ...);

#define printf ch_printf
#define snprintf chsnprintf

#endif
