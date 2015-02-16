/* swr.h is part of ChibiAmpFirmware.
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

#ifndef _SWR_H
#define _SWR_H

#include <inttypes.h>
#include "ch.h"
#include "hal.h"

// Defines ====================================================================
#define ADC_GROUP1_NUM_CHANNELS 1
#define ADC_GROUP1_BUF_DEPTH    128
//-----------------------------------------------------------------------------

// Externs ====================================================================
extern uint32_t recvdSamples;
extern adcsample_t adcBuffer[];
//-----------------------------------------------------------------------------

//! \brief Initialize the SWR module
void swr_init(void);

/*!
 * \brief Called when the adc buffer is filled or half-filled
 * 
 * Sets \c adcMean and \c recvdSamples.
 */
void adcBufferFilled(ADCDriver* adcp, adcsample_t* buffer, size_t n);

#endif /*_SWR_H*/
