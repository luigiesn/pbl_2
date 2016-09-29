#include "DiffAmp.h"


void DiffAmp_Init(void){

}

unsigned int DiffAmp_GetSample(unsigned char ch){
    HAL_ADC_SetChannel(ch);

    return (unsigned int)((float)HAL_ADC_GetSample()*3300/1024);
}
