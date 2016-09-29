#include "Led.h"

#include <LPC11xx.h>

#include "Port_HAL.h"

void Led_Boot(void){
    Port_HAL_PinDir(2, (unsigned char)ledA, OUTPUT);
	Port_HAL_PinDir(2, (unsigned char)ledB, OUTPUT);

    Port_HAL_SetOutput(2, (unsigned char)ledA, LOW);
	Port_HAL_SetOutput(2, (unsigned char)ledB, LOW);
}

void Led_Set(led l, bool state){
    Port_HAL_SetOutput(2, (unsigned char)l, state);
}
