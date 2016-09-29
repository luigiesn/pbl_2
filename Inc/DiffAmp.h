#ifndef DIFFAMP_H
#define DIFFAMP_H

#include "HAL_ADC.h"

#define AMP_A_CH 0
#define AMP_B_CH 6

void DiffAmp_Init(void);

unsigned int DiffAmp_GetSample(unsigned char ch);

#endif
