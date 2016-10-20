#ifndef RTC_H
#define RTC_H

#include "HAL_i2c.h"

#include "ProcessManager.h"

/**
 * The RTC address on I2C bus
 */
#define RTC_ADDR 0xD0

/**
 * RTC parameter type
 */
typedef enum{
    rtcSECOND, rtcMINUTE, rtcHOUR, rtcDAY, rtcDATE, rtcMONTH, rtcYEAR, rtcEND
}rtcParam;

/**
 * @brief Initializes the external RTC.
 *
 * @warning This routine must be called before
 * any other.
 */
void RTC_Init(void);

/**
 * @brief Set a RTC internal parameter
 *
 * @param p RTC parameter
 * @param v The value to be changed to it.
 */
void RTC_SetParam(rtcParam p, unsigned char v);

/**
 * @brief Read a RTC internal parameter
 *
 * @param p RTC parameter
 * @return v The value read from RTC internal parameter.
 */
unsigned char RTC_ReadParam(rtcParam p);

#endif
