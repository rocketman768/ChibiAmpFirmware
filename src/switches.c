#include "ch.h"
#include "hal.h"
#include "switches.h"

void bandSelect(int band)
{
   // Switch into band 0 (no current drain) if given bad params.
   if( band < 0 || band > 3 )
      band = 0;
   
   switch(band)
   {
      case 0:
         palClearPad(GPIOB, GPIOB_BAND1);
         palClearPad(GPIOB, GPIOB_BAND2);
         palClearPad(GPIOB, GPIOB_BAND3);
         break;
      case 1:
         palSetPad(GPIOB, GPIOB_BAND1);
         palClearPad(GPIOB, GPIOB_BAND2);
         palClearPad(GPIOB, GPIOB_BAND3);
         break;
      case 2:
         palClearPad(GPIOB, GPIOB_BAND1);
         palSetPad(GPIOB, GPIOB_BAND2);
         palClearPad(GPIOB, GPIOB_BAND3);
         break;
      case 3:
         palClearPad(GPIOB, GPIOB_BAND1);
         palClearPad(GPIOB, GPIOB_BAND2);
         palSetPad(GPIOB, GPIOB_BAND3);
         break;
      default:
         break;
   }
}

void setRadioPath(int path)
{
   switch(path)
   {
      case RADIO_PATH_AMPLIFIER:
         palSetPad(GPIOC, GPIOC_ANT_SW);
         break;   
      default:
      case RADIO_PATH_ANTENNA:
         palClearPad(GPIOC, GPIOC_ANT_SW);
         break;
   }
}

void setAmpPower(int pwr)
{
   if(pwr)
      palSetPad(GPIOB, GPIOB_AMP_PWR);
   else
      palClearPad(GPIOB, GPIOB_AMP_PWR);
}
