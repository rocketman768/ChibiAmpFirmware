/* rfdet.h is part of ChibiAmpFirmware.
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

#ifndef RFDET_H
#define RFDET_H

#include "ch.h"
#include "hal.h"

typedef struct {
   int enabled;
   int debounceOnTime_ms;
   int debounceOffTime_ms;
} RFDetOptions;

typedef struct {
   int rfIsPresent;
   systime_t rfOnTime;
   systime_t rfOffTime;
} RFDetState;

//! \brief All the options for the rf detector module.
extern RFDetOptions rfdet_options;
extern RFDetState rfdet_state;

//! \brief Initialization of the rf detector module.
void rfdet_init(EXTConfig* extConfig);

#endif /*RFDET_H*/
