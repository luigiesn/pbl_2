#ifndef HAL_I2C
#define HAL_I2C

#include <LPC11xx.h>

#include "System.h"

/**
 * Enumerates all devices on the bus.
 */
enum{ // i2c device bus address
    idvEEPROM = 0xae, idvDAC = 0xc6, idvRTC = 0xd0
}i2cDevice;

/**
 * @brief Initializes hardware internals.
 *
 * @warning Boot routine must be called before
 * any other.
 */
void HAL_i2c_Init(void);

/**
 * @brief Sends a buffer to a device
 *
 * Sends a size defined char buffer to a device
 * in I2C bus.
 *
 * @param addr Data destination device address.
 * @param buffer Data buffer to send from.
 * @param bufferSize Data buffer size
 */
void HAL_i2c_Send(unsigned char addr, unsigned char *buffer, unsigned int bufferSize);

/**
 * @brief Read a byte from I2C device
 *
 * Reads just one byte from a device in I2C bus
 *
 * @param addr Data source device address.
 * @return a byte from selected channel
 */
unsigned char HAL_i2c_Receive(unsigned char addr);

#endif
