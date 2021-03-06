/* main.c is part of ChibiAmpFirmware.
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

#include <inttypes.h>
#include "ch.h"
#include "hal.h"

#include "gui.h"
#include "printf.h"
#include "rfdet.h"
#include "serlcd.h"
#include "switches.h"
#include "swr.h"

#define VALUE_TO_STRING(x) #x
#define VALUE(x) VALUE_TO_STRING(x)
#define VAR_NAME_VALUE(var) #var "=" VALUE(var)
// Make sure I'm not crazy
/*
#pragma message(VAR_NAME_VALUE(STM32_SYSCLK))
#pragma message(VAR_NAME_VALUE(STM32_HCLK))
#pragma message(VAR_NAME_VALUE(STM32_PCLK1))
#pragma message(VAR_NAME_VALUE(STM32_PCLK2))
#pragma message(VAR_NAME_VALUE(STM32_ADCCLK))
*/

// SD1 driver config
// The SerLCD defaults to 9600 baud, 1 stop bit, no parity.
static SerialConfig sd1cfg =
{
   .speed = 9600,
   .cr1   = 0,
   .cr2   = USART_CR2_STOP1_BITS | USART_CR2_LINEN,
   .cr3   = 0
};

void serial_init(void)
{
   /*
    * Activates the serial driver using the sd1cfg configuration.
    * PA9(TX) is routed to USART1.
    */
   sdStart(&SD1, &sd1cfg);
   // SD1 is up, so enable printf stuff.
   init_printf((BaseSequentialStream*)&SD1);
   // Setup serial lcd module
   serLcdInit(printf);
}

int main(void)
{
   //EXTConfig extConfig;

   /*
    * System initializations.
    * - HAL initialization, this also initializes the configured device drivers
    *   and performs the board-specific initializations.
    * - Kernel initialization, the main() function becomes a thread and the
    *   RTOS is active.
    */
   halInit();
   chSysInit();

   /*
    * ChibiAmpFirmware module options
    */
   rfdet_options.enabled = 1;

   /*
    * ChibiAmpFirmware module initializations
    */
   serial_init();
   switches_init();
   //swr_init()
   //rfdet_init(&extConfig);
   init_gui();

   // Start EXT driver
   //extStart(&EXTD1, &extConfig);

   //==========================================================================
   while(1)
   {
      //serLcdClear();
      //printf("Hello");
      chThdSleepMilliseconds(1000);
   }
   //==========================================================================

   return 0;
}
