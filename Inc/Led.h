#ifndef LED_H
#define LED_H

#include "defs.h"

typedef enum{
    ledA, ledB = 0x0a
}led;

void Led_Boot(void);

void Led_Set(led l, bool state);

#endif
