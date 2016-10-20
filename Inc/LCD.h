#ifndef LCD_H
#define LCD_H

#include "Port_HAL.h"
#include "defs.h"

#include "System.h"
#include "Led.h"

#define CHAR_LEFT_ARROW 0x7F
#define CHAR_RIGHT_ARROW 0x7E

/**
 * LCD commands list
 */
typedef enum{
    /** Clears the display */
    lcdCLEAR = 0x01,
    /** Moves cursor to the first position. */
    lcdCURSOR_HOME = 0x02,
    /** Stops to blink the cursor */
    lcdCURSOR_OFF = 0x0c,
    /** Stops to blink the cursor */
    lcdCURSOR_ON = 0x0f,
    /** Set the cursor to a defined position. Command and <b>OR</b>
     *  operations must be used. \n
     *  e.g., lcdSETTOXX | 0x42 to move the
     *  cursor to  the second position of the second line.
     */
    lcdSETTOXX = 0x80,
    /** Moves cursor to the first position of the second line */
    lcdROW2 = 0xC0
}lcdCmd;

/**
 * @brief Initializes the LCD.
 *
 * @warning Boot routine must be called before
 * any other.
 */
void LCD_Boot(void);

/**
 * @brief Send a command to LCD.
 *
 * @param cmd LCD command.
 */
void LCD_WriteCommand(lcdCmd cmd);

/**
 * @brief Send data to LCD
 *
 * @param cmd A character
 */
void LCD_WriteData(unsigned char data);

/**
 * @brief Send a data vector to LCD
 *
 * @param str A character vector ended with 0.
 */
void LCD_WriteString(char *str);

/**
 * @brief Turns on/off the display backlight
 *
 * @param b Boolean backlight state. True to turn on or
 * False to turn off the LCD
 */
void LCD_BackLight(bool b);

#endif
