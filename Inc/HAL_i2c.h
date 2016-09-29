#ifndef HAL_I2C
#define HAL_I2C

#include <LPC11xx.h>

enum{ // i2c device bus address
    idvEEPROM = 0xae, idvDAC = 0xc6, idvRTC = 0xd0
}i2cDevice;

void HAL_i2c_Init(void);

void HAL_i2c_Send(unsigned char addr, unsigned char *buffer, unsigned int bufferSize);

unsigned char HAL_i2c_Receive(unsigned char addr);

#endif
