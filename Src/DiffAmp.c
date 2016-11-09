#include "DiffAmp.h"

unsigned int DiffAmp_GetSample(unsigned char ch){
    HAL_ADC_SetChannel(ch);

    // normalize to the reading scale
    return (unsigned int)((float)HAL_ADC_GetSample()*DIFFAMP_MAX_VALUE/DIFFAMP_ADC_DISCRETIZATION_STEPS);
}
