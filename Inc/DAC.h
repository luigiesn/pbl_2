#ifndef DAC_H
#define DAC_H

#include <LPC11xx.h>

#include "HAL_i2c.h"

/**
 * DAC reference voltage value
 */
#define DAC_VREF 3.3

/**
 * @brief Set DAC output voltage
 *
 * @param[in] v The output voltage which must be set on DAC
 */
void DAC_SetVoltage(unsigned int v); // millivolts

#endif
