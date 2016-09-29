#ifndef LCD_H
#define LCD_H

#include "Port_HAL.h"
#include "defs.h"

#define CHAR_LEFT_ARROW 0x7F
#define CHAR_RIGHT_ARROW 0x7E

typedef enum{
    lcdCLEAR = 0x01,
    lcdCURSOR_HOME = 0x02,
    lcdCURSOR_OFF = 0x0c,
    lcdCURSOR_ON = 0x0f,
    lcdSETTOXX = 0x80,
    lcdROW2 = 0xC0
}lcdCmd;

void LCD_Boot(void);

void LCD_WriteCommand(lcdCmd cmd);

void LCD_WriteData(unsigned char data);

void LCD_WriteString(char *str);

void LCD_BackLight(bool b);

#endif
