/* swr.c is part of ChibiAmpFirmware.
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

#include "swr.h"

// Variables ==================================================================
static ADCConfig adcConfig;

/*!
 * \brief Analog conversion on channel 0 (PA0).
 * 
 * - Continuous
 * - 8-bit resolution
 * - Sample rate = STM32_ADCCLK / (sample_cycles + 8 cycles)
 *               = 1.5 MHz / 488
 *               = 3.074 KHz
 */
static ADCConversionGroup adcConversionGroup =
{
   // Enables the circular buffer mode for the group.
   .circular = 1,
   // Number of the analog channels belonging to the conversion group.
   .num_channels = ADC_GROUP1_NUM_CHANNELS,
   // Callback function associated to the group or NULL.
   .end_cb = adcBufferFilled,
   // Error callback or NULL.
   .error_cb = 0,
   /*
    * ADC CR1 register initialization data.
    * All the required bits must be defined into this field except
    * ADC_CR1_SCAN that is enforced inside the driver.
    */
   .cr1 = ADC_CR1_RES_1, // 8-bit conversion
   /*
    * ADC CR2 register initialization data.
    * All the required bits must be defined into this field except
    * ADC_CR2_DMA, ADC_CR2_CONT and ADC_CR2_ADON that are
    * enforced inside the driver.
    */
   // NOTE: Philip - Unsure why, but SWSTART has to be set in order for CONT
   //       to be set by the driver.
   .cr2 = ADC_CR2_SWSTART,
   /*
    * ADC SMPR1 register initialization data.
    * In this field must be specified the sample times for channels
    * 10...18.
    */
   //.smpr1 = ,
   /*
    * ADC SMPR2 register initialization data.
    * In this field must be specified the sample times for channels
    * 0...9.
    */
   .smpr2 = ADC_SMPR2_SMP_AN0(ADC_SAMPLE_480), // 480 cycles
   /*
    * ADC SQR1 register initialization data.
    * Conversion group sequence 13...16 + sequence length.
    */
   .sqr1 = ADC_SQR1_NUM_CH(ADC_GROUP1_NUM_CHANNELS),
   /*
    * ADC SQR2 register initialization data.
    * Conversion group sequence 7...12.
    */
   //.sqr2 = ;
   /*
    * ADC SQR3 register initialization data.
    * Conversion group sequence 1...6.
    */
   .sqr3 = ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0),
};

adcsample_t adcBuffer[ADC_GROUP1_NUM_CHANNELS * ADC_GROUP1_BUF_DEPTH];
static uint8_t adcMean = 0;
uint32_t recvdSamples = 0;
//-----------------------------------------------------------------------------

void swr_init(void)
{
   // Start filling that ADC buffer!
   adcStart(&ADCD1, &adcConfig);
   adcStartConversion(
      &ADCD1,
      &adcConversionGroup,
      adcBuffer,
      ADC_GROUP1_BUF_DEPTH
   );
}

void adcBufferFilled(ADCDriver* adcp, adcsample_t* buffer, size_t n)
{
   (void)adcp;
   (void)buffer;
   (void)n;

   size_t i;
   uint16_t sum;

   recvdSamples += n;
   
// 0 for half-buffer mode, 1 for whole buffer mode
#define PROC_MODE 0

#if PROC_MODE == 0
   for( i = 0, sum = 0; i < n; ++i )
      sum += (uint8_t)(buffer[i] & 0xFF);
   adcMean = ((uint16_t)adcMean + sum/n)>>1;
#elif PROC_MODE == 1
   // NOTE: only process when we've just filled the buffer, because the ADC
   // driver fires two callbacks: on half full AND full.
   if(buffer+n != adcBuffer+ADC_GROUP1_BUF_DEPTH || n == 0)
      return;
   for( i = 0, sum = 0; i < ADC_GROUP1_BUF_DEPTH; ++i )
      sum += (uint8_t)(adcBuffer[i] & 0xFF);
   adcMean = sum / ADC_GROUP1_BUF_DEPTH;
#endif

#undef PROC_MODE
}
