#include "HAL_i2c.h"

void HAL_i2c_Init(void){
    LPC_SYSCON->SYSAHBCLKCTRL |= 0x20;
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16);	// habilitar o clock para o bloco IOCON (UM10398, 3.5.14)
    LPC_SYSCON->PRESETCTRL |= 0x02;

    LPC_IOCON->PIO0_4 |= 0x1;
    LPC_IOCON->PIO0_5 |= 0x1;

    LPC_I2C->SCLH = 120;
    LPC_I2C->SCLL = 120;

    LPC_I2C->CONSET |= 0x40; // enable i2c
}

void HAL_i2c_Send(unsigned char addr, unsigned char *buffer, unsigned int bufferSize){

    unsigned int sendCnt;

    LPC_I2C->CONSET = 0x20;

    while(LPC_I2C->STAT != 0x8); // while not started

    LPC_I2C->DAT = (unsigned int) addr;

    LPC_I2C->CONCLR = 0x28; // clear int flag and start to send

    while(LPC_I2C->STAT != 0x18);

    for(sendCnt = 0; sendCnt < bufferSize; sendCnt++){
        LPC_I2C->DAT = (unsigned int)buffer[sendCnt];
        LPC_I2C->CONCLR = 0x8;
        while(LPC_I2C->STAT != 0x28);
    }


    LPC_I2C->CONSET = 0x10;
    LPC_I2C->CONCLR = 0x8;
}

unsigned char HAL_i2c_Receive(unsigned char addr){

	LPC_I2C->CONSET = 0x20;
	while(LPC_I2C->STAT != 0x8);

	LPC_I2C->DAT = (unsigned char)addr + 1;
	LPC_I2C->CONCLR = 0x28;
	while(LPC_I2C->STAT != 0x40);

    LPC_I2C->CONCLR = 0x2C;
    while((LPC_I2C->STAT != 0x50) && (LPC_I2C->STAT != 0x58));

    char data = LPC_I2C->DAT;

	LPC_I2C->CONSET = 0x10;
	LPC_I2C->CONCLR = 0x8;

	return data;
}
