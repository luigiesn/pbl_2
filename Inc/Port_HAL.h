#ifndef HAL_PORT_H
#define HAL_PORT_H

#include <LPC11xx.h>

#define Port_HAL_PinDir(port, pin, dir)  (LPC_GPIO##port->DIR = dir ?  LPC_GPIO##port->DIR | (1 << pin) : LPC_GPIO##port->DIR & ~(1 << pin))
#define Port_HAL_SetOutput(port, pin, lvl)  (LPC_GPIO##port->DATA = lvl ?  LPC_GPIO##port->DATA | (1 << pin) : LPC_GPIO##port->DATA & ~(1 << pin))
#define Port_HAL_PinCheck(port, pin)    (LPC_GPIO##port->DATA & (1<<pin))

enum{
    INPUT, OUTPUT
};

enum{
    LOW, HIGH
};

#endif
