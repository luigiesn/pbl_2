#ifndef DIFFAMP_H
#define DIFFAMP_H

#include "HAL_ADC.h"

#define AMP_A_CH 0
#define AMP_B_CH 6

#define DIFFAMP_MAX_VALUE 330
#define DIFFAMP_ADC_DISCRETIZATION_STEPS 1023

/**
 * @brief Get a sample from a differential amplifier channel
 *
 * @param[in] ch Channel which will be sampled
 * @return A sample from the selected channel
 *
 * The return value depends on defined constants values.
 * Sample value is obtained from the proportion given by
 * the instant value read by the ADC divided by the
 * DIFFAMP_ADC_DISCRETIZATION_STEPS constant and then multiplied by
 * DIFFAMP_MAX_VALUE
 *
 */
unsigned int DiffAmp_GetSample(unsigned char ch);

#endif
