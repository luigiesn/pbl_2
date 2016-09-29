#ifndef UART_H
#define UART_H

#include <LPC11xx.h>

#include "ProcessManager.h"

void Uart_Boot(void);

unsigned int Uart_Read(unsigned char* data, unsigned int size);

unsigned char Uart_ReadByte(void);

void Uart_Write(unsigned char* data, unsigned int size);

#endif
