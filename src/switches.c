#include "ch.h"
#include "hal.h"
#include "switches.h"

void switches_init(void)
{
   // In HW 1.0, need to leave on amp power.
   setAmpPower(1);
   // Antenna connected to radio
   setRadioPath(RADIO_PATH_ANTENNA);
   // 20M
   bandSelect(RADIO_BAND_20M_17M);
}

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
   /*
    * In ChibiAmp 1.0, there is a bug where we cannot turn the amp power off.
    * Reenable this on the next hardware revision
    *
   else
      palClearPad(GPIOB, GPIOB_AMP_PWR);
    */
}
