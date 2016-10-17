#include "BootConfig.h"

#include "LCD.h"
#include "Keyboard.h"
#include "HAL_ADC.h"
#include "Led.h"
#include "Alarm.h"
#include "HAL_i2c.h"
#include "Uart.h"
#include "SerialCommand.h"

static BootRoutine bR[] = {
    KBD_Boot,
    HAL_ADC_Boot,
    LCD_Boot,
    Led_Boot,
    Alarm_Boot,
    HAL_i2c_Init,
    Uart_Boot,
    SerialCmd_Boot,
    0
};

BootRoutine *Boot_getBootRoutines(void) {

    return bR;
}
