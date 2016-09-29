#ifndef EEPROM_H
#define EEPROM_H

void Eeprom_Init(void);

void Eeprom_Write(unsigned int addr, unsigned char data);

unsigned char Eeprom_Read(unsigned int addr);

#endif
