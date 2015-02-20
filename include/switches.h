#ifndef _SWITCHES_H
#define _SWITCHES_H

/*!
 * \brief Select the band filters through which to pass the output signal.
 * 
 * \param band in [0,3]. Band 0 requires no current and should be default
 */
void bandSelect(int band);

#define RADIO_PATH_ANTENNA   0
#define RADIO_PATH_AMPLIFIER 1

/*!
 * \brief Choose which path the radio is connected to.
 * 
 * \param path
 *   - \c RADIO_PATH_AMPLIFIER route radio through amplifier
 *   - \c RADIO_PATH_ANTENNA route radio directly to antenna
 */
void setRadioPath(int path);

/*!
 * \brief Turn amp power on/off
 * 
 * \param pwr 0 for off, 1 for on
 */
void setAmpPower(int pwr);

#endif /* _SWITCHES_H */
