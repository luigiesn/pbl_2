#ifndef DAC_H
#define DAC_H

#include <LPC11xx.h>

#define DAC_VREF 3.3

void DAC_Init(void);

void DAC_SetVoltage(unsigned int v); // millivolts

void DAC_Transmitir ( uint16_t v_uAmostra );

#endif
