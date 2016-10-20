#ifndef LED_H
#define LED_H

#include <LPC11xx.h>

#include "Port_HAL.h"

#include "defs.h"

typedef enum{
    ledA, ledB = 0x0a
}led;

/**
 * @brief Initializes the LEDs.
 *
 * @warning Boot routine must be called before
 * any other.
 */
void Led_Boot(void);

/**
 * @brief Set a LED state.
 *
 * @param l LED to set.
 * @param state State to change the LED
 *
 */
void Led_Set(led l, bool state);

#endif
