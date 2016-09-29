#include "LCD.h"
#include "System.h"
#include "Led.h"

void LCD_Strobe(void);
void LCD_WriteByte(unsigned char valor, unsigned char data);

void LCD_Boot(void){

    Port_HAL_PinDir(3, 1, OUTPUT);
    Port_HAL_SetOutput(3, 1, 0);

    DelayMs(15);

    LPC_IOCON->PIO3_5 = 0;
    LPC_IOCON->PIO1_8 = 0;
    LPC_IOCON->PIO0_2 = 0;
    LPC_IOCON->PIO2_7 = 0;
    LPC_IOCON->PIO2_8 = 0;
    LPC_IOCON->PIO2_1 = 0;
    LPC_IOCON->PIO0_3 = 0;
    LPC_IOCON->PIO3_4 = 0;
    LPC_IOCON->PIO2_4 = 0;
    LPC_IOCON->PIO2_5 = 0;

    Port_HAL_PinDir(3, 5, OUTPUT);
	Port_HAL_PinDir(1, 8, OUTPUT);
	Port_HAL_PinDir(0, 2, OUTPUT);
	Port_HAL_PinDir(2, 7, OUTPUT);
	Port_HAL_PinDir(2, 8, OUTPUT);
	Port_HAL_PinDir(2, 1, OUTPUT);
	Port_HAL_PinDir(0, 3, OUTPUT);
	Port_HAL_PinDir(3, 4, OUTPUT);
	Port_HAL_PinDir(2, 4, OUTPUT);
    Port_HAL_PinDir(2, 5, OUTPUT);

	DelayMs(16);

	LCD_WriteByte(0x30, 0);

	DelayMs(2);

    LCD_WriteByte(0x3C, 0);

    DelayMs(16);

    LCD_WriteByte(0x0f, 0);

    DelayMs(16);

    LCD_WriteByte(0x01, 0);

    DelayMs(16);

    LCD_WriteByte(0x06, 0);

    DelayMs(16);
}

void LCD_BackLight(bool b){
    Port_HAL_SetOutput(3, 1, b);
}

void LCD_WriteCommand(lcdCmd cmd){
    LCD_WriteByte((unsigned char)cmd, 0);

    if(cmd == lcdCLEAR || cmd == lcdCURSOR_HOME){
            DelayUs(1640);
    }
}

void LCD_WriteData(unsigned char data){
    LCD_WriteByte(data, 1);
}


void LCD_WriteString(char *str){
	while(*str){
        LCD_WriteByte(*str++, 1);
        }
}

void LCD_Strobe(void){
    Port_HAL_SetOutput(2, 5, HIGH);
	DelayUs(40);
	Port_HAL_SetOutput(2, 5, LOW);
	DelayUs(40);
}

void LCD_WriteByte(unsigned char valor, unsigned char data){

	Port_HAL_SetOutput(3, 5, data);

	Port_HAL_SetOutput(1, 8 ,(valor & 0x80) >> 7); //7
	Port_HAL_SetOutput(0, 2 ,(valor & 0x40) >> 6); //6
	Port_HAL_SetOutput(2, 7 ,(valor & 0x20) >> 5); //5
	Port_HAL_SetOutput(2, 8 ,(valor & 0x10) >> 4); //4
	Port_HAL_SetOutput(2, 1 ,(valor & 0x08) >> 3); //3
	Port_HAL_SetOutput(0, 3 ,(valor & 0x04) >> 2); //2
	Port_HAL_SetOutput(3, 4 ,(valor & 0x02) >> 1); //1
	Port_HAL_SetOutput(2, 4 ,(valor & 0x01)); //0

	DelayUs(40);

	LCD_Strobe();
}
