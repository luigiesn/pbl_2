#ifndef HAL_ADC_H
#define HAL_ADC_H

#include "defs.h"

void HAL_ADC_Boot(void);

void HAL_ADC_SetChannel(unsigned char ch);

unsigned int HAL_ADC_GetSample(void);

#endif
