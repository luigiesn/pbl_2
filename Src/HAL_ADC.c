#include "HAL_ADC.h"

static struct{
    unsigned char oldCh;
}Prv;

void HAL_ADC_Boot(void){
    // configurate clock
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);
    LPC_SYSCON->PDRUNCFG &= ~(1<<4);

    // disable adc
    LPC_ADC->CR = 0xb00;

    // prepare i/o
    LPC_IOCON->PIO1_11 = 0x01;
    LPC_IOCON->R_PIO0_11 = 0x02;
    LPC_IOCON->PIO1_10 = 0x01;

    // unreachable value to the last channel read from
    // to force channel changing when call HAL_ADC_SetChannel()
    Prv.oldCh = 0xff;
}

void HAL_ADC_SetChannel(unsigned char ch){
    if(Prv.oldCh == ch)
        return;
    // if channel is different from last channel settling

    LPC_ADC->CR &= ~(1 << Prv.oldCh); // reset the old
    DelayMs(1);
    LPC_ADC->CR |= (1 << ch); // set the new

    Prv.oldCh = ch;
}

unsigned int HAL_ADC_GetSample(void){

    LPC_ADC->CR |= (1<<24); // start conversion from selected channel

    while(!(LPC_ADC->GDR & (1<<31))); // wait for conversion end flag

    return (LPC_ADC->GDR >> 6) & 0x3ff; // return the value from conversion
}
