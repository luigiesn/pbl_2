#include "HAL_ADC.h"

static struct{
    unsigned char oldCh;
}Prv;

void HAL_ADC_Boot(void){
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<13);
    LPC_SYSCON->PDRUNCFG &= ~(1<<4);

    LPC_ADC->CR = 0x00;

    LPC_IOCON->PIO1_11 = 0x01;
    LPC_IOCON->R_PIO0_11 = 0x02;
    LPC_IOCON->PIO1_10 = 0x01;

    Prv.oldCh = 0xff;
}

void HAL_ADC_SetChannel(unsigned char ch){
    if(Prv.oldCh == ch)
        return;
    LPC_ADC->CR &= ~(1 << Prv.oldCh);
    DelayMs(1);
    LPC_ADC->CR |= (1 << ch);

    Prv.oldCh = ch;
}

unsigned int HAL_ADC_GetSample(void){

    LPC_ADC->CR |= (1<<24);

    while(!(LPC_ADC->GDR & (1<<31)));

    return (LPC_ADC->GDR >> 6) & 0x3ff;
}
