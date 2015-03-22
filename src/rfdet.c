/* rfdet.c is part of ChibiAmpFirmware.
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

#include "rfdet.h"
#include "switches.h"

RFDetOptions rfdet_options = {
   .enabled = 0,
   .debounceOnTime_ms = 5,
   .debounceOffTime_ms = 50,
};

struct RFDetState {
   int rfIsPresent;
   systime_t rfOnTime;
   systime_t rfOffTime;
} rfdet_state;

static void rfdet_updateAmpSwitches(void* p)
{
   (void)p;

   // This means the last transition was from "no rf" to "rf".
   int rfDetected = (rfdet_state.rfOnTime > rfdet_state.rfOffTime);

   if (rfdet_state.rfIsPresent) {
      if (!rfDetected) {
         rfdet_state.rfIsPresent = 0;
         setRadioPath(RADIO_PATH_ANTENNA);
         setAmpPower(0);
      }
      
   } else {
      if (rfDetected) {
         rfdet_state.rfIsPresent = 1;
         setRadioPath(RADIO_PATH_AMPLIFIER);
         setAmpPower(1);
      }
   }
}

/*!
 * \brief ISR for rf detector pin
 */
static void isr_rfdet(EXTDriver *extp, expchannel_t channel)
{
   (void)extp;
   (void)channel;
   static VirtualTimer vtDebounce;

   if (!rfdet_options.enabled)
      return;

   // Get RF pin state and record the time
   int rfDetected = ~palReadPad(GPIOC, GPIOC_RFDET);
   if (rfDetected)
      rfdet_state.rfOnTime = chTimeNow();
   else
      rfdet_state.rfOffTime = chTimeNow();

   // Lock since the VT stuff is I-class API
   chSysLockFromIsr(); //======================================================

   // Get out if we already armed the timer
   if (chVTIsArmedI(&vtDebounce))
      goto EPILOGUE;

   if (rfDetected ) {
      chVTSetI(
         &vtDebounce,
         MS2ST(rfdet_options.debounceOnTime_ms),
         rfdet_updateAmpSwitches,
         NULL
      );
   } else {
      chVTSetI(
         &vtDebounce,
         MS2ST(rfdet_options.debounceOffTime_ms),
         rfdet_updateAmpSwitches,
         NULL
      );
   }

EPILOGUE:
   chSysUnlockFromIsr(); //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}

void rfdet_init(EXTConfig* extConfig)
{
   // Set up PC2 as an external interrupt line with isr_rfdet() as ISR.
   extConfig->channels[GPIOC_RFDET].mode = EXT_MODE_GPIOC | EXT_CH_MODE_BOTH_EDGES | EXT_CH_MODE_AUTOSTART;
   extConfig->channels[GPIOC_RFDET].cb   = isr_rfdet;
   
   // Enable interrupt channel 2.
   //extChannelEnable(&EXTD1, GPIOC_RFDET);
}
