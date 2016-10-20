#ifndef EEPROM_H
#define EEPROM_H

/**
 * @brief Writes a byte to a memory position
 */
void Eeprom_Write(unsigned int addr, unsigned char data);

/**
 * @brief Reads a byte from a memory position
 */
unsigned char Eeprom_Read(unsigned int addr);

#endif
