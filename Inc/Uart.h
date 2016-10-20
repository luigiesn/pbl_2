#ifndef UART_H
#define UART_H

#include <LPC11xx.h>

#include "ProcessManager.h"

/**
 * @brief Initializes hardware internals.
 *
 * @warning Boot routine must be called before
 * any other.
 */
void Uart_Boot(void);

/**
 * @brief Read data from uart input buffer
 *
 * @param data Data buffer
 * @param size Size of the data buffer
 *
 * @return Number of bytes read
 */
unsigned int Uart_Read(unsigned char* data, unsigned int size);

/**
 * @brief Read one byte from input buffer
 *
 * @return Byte read
 */
unsigned char Uart_ReadByte(void);

/**
 * @brief Write data on uart
 *
 * @param data Data buffer
 * @param size Size of the data buffer
 *
 * @return Number of bytes written
 */
void Uart_Write(unsigned char* data, unsigned int size);

#endif
