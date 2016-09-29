#include "DAC.h"

#include "HAL_i2c.h"

void DAC_Init(void){


}

void DAC_SetVoltage(unsigned int v){

    unsigned int convValue = (unsigned int)(((float)v*4096)/(DAC_VREF*1000));

    if(convValue > 4095) convValue = 4095;

    unsigned char tempData[3];

    tempData[0] = (unsigned char)(0b01000000);
    tempData[1] = (unsigned char)((convValue >> 4) & 0xff);
    tempData[2] = (unsigned char)((convValue << 4) & 0xff);

    HAL_i2c_Send((unsigned char)idvDAC, tempData, 3);
}



