#include "Io.h"

void Io_Init(void){
    Port_HAL_PinDir(0, 7, OUTPUT);
    Port_HAL_PinDir(2, 9, OUTPUT);
    Port_HAL_PinDir(0, 6, INPUT);
    Port_HAL_PinDir(2, 2, INPUT);

    LPC_IOCON->PIO2_2 &= ~(2 << 3);
    LPC_IOCON->PIO0_6 &= ~(2 << 3);

    LPC_IOCON->PIO2_2 |= 1 << 3;
    LPC_IOCON->PIO0_6 |= 1 << 3;
}
