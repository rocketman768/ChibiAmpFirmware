#include "printf.h"
#include "serlcd.h"
#include "rfdet.h"
#include "switches.h"

static WORKING_AREA(waGuiThread, 128);
static msg_t guiThread(void *arg)
{
   (void)arg;

   int count = 0;

   chRegSetThreadName("gui");
   while (1)
   {
      // First line
      serLcdClear();
      printf("pth %d rf %d %d", switches_state.radioPath, rfdet_state.rfIsPresent, count);
      count = (count)? 0 : 1;

      // Second line
      serLcdPos(1,0);
      printf("bnd %d pwr %d", switches_state.band, switches_state.ampPower);

      chThdSleepMilliseconds(1000);
   }

   return 0;
}

void init_gui(void)
{
   chThdCreateStatic(waGuiThread, sizeof(waGuiThread), NORMALPRIO, guiThread, NULL);
}
