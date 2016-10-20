#ifndef HAL_ADC_H
#define HAL_ADC_H

#include <LPC11xx.h>

#include "defs.h"

#include "System.h"

/**
 * @brief Initializes hardware internals.
 *
 * @warning Boot routine must be called before
 * getting any sample.
 */
void HAL_ADC_Boot(void);

/**
 * @brief Select a ADC channel.
 *
 * Prepares a channel to be read in next sampling.
 *
 * @param ch Channel to be switched to.
 */
void HAL_ADC_SetChannel(unsigned char ch);

/**
 * @brief Get a sample
 *
 * The sample is obtained from the last selected
 * conversion channel.
 *
 * @return A ADC channel sample.
 *
 * @warning If no channel is selected before sampling starts, 0 is
 * the default channel converter reads from.
 */
unsigned int HAL_ADC_GetSample(void);

#endif
