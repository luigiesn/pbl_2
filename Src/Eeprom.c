#include "Eeprom.h"

#include "HAL_i2c.h"

void Eeprom_Write(unsigned int addr, unsigned char data){
    unsigned char temp[3];

    // put data in EEPROM protocol format
    temp[0] = (addr >> 8) & 0xff;
    temp[1] = addr & 0xff;
    temp[2] = data;

    HAL_i2c_Send(idvEEPROM, temp, 3);

}

unsigned char Eeprom_Read(unsigned int addr){
    unsigned char temp[2];

    // prepare to read
    // put data in EEPROM format
    temp[0] = (addr >> 8) & 0xff;
    temp[1] = addr & 0xff;

    unsigned int sendCnt;

    LPC_I2C->CONSET = 0x20;

    while(LPC_I2C->STAT != 0x08); // while not started

    LPC_I2C->DAT = (unsigned int) idvEEPROM;

    LPC_I2C->CONCLR = 0x28; // clear int flag and start to send

    while(LPC_I2C->STAT != 0x18); // wait ack

    // send requesting data
    for(sendCnt = 0; sendCnt < 2; sendCnt++){
        LPC_I2C->DAT = (unsigned int)temp[sendCnt];
        LPC_I2C->CONCLR = 0x8;
        while(LPC_I2C->STAT != 0x28);
    }


   // LPC_I2C->CONSET = 0x10;
    LPC_I2C->CONCLR = 0x8;


    LPC_I2C->CONSET = 0x20;
	while(LPC_I2C->STAT != 0x10);

	LPC_I2C->DAT = (unsigned char)idvEEPROM;
	LPC_I2C->CONCLR = 0x28;
	while(LPC_I2C->STAT != 0x40);

    LPC_I2C->CONCLR = 0x2C;
    while((LPC_I2C->STAT != 0x50) && (LPC_I2C->STAT != 0x58));

    char data = LPC_I2C->DAT;

	LPC_I2C->CONSET = 0x10;
	LPC_I2C->CONCLR = 0x8;

	return data;

}
