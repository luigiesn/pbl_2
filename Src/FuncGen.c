#include "FuncGen.h"

unsigned int samples[32] = { 2048,2447,2831,3185,
							3495,3750,3939,4056,
							4095,4056,3939,3750,
							3495,3185,2831,2447,
							2048,1648,1264,910,
							600,345,156,39,
							0,39,156,345,
							600,910,1264,1648 };


int i = 0;

void FuncGen_Init(void){
    LPC_SYSCON->SYSAHBCLKCTRL |= 1 << 8;

    LPC_TMR16B1->PR = 12000;
    LPC_TMR16B1->MCR = 3; // interrupt on mr0i

    LPC_TMR16B1->MR0 = 999; // 1s

    //NVIC_EnableIRQ(TIMER_16_1_IRQn);

}

void FuncGen_Start(funcType f){
    LPC_TMR16B1->TC = 0; // clean the counter

    LPC_TMR16B1->IR = 0xff;

    LPC_TMR16B1->TCR |= 1; // enable

}

void FuncGen_Process(void){

    //DAC_SetVoltage((int)(sinf((float)i/50)*1650)+1650);
    i++;

}

void TIM0_IRQHandler(void){

    if ( LPC_TMR16B1->IR & 0x1 ){
        LPC_TMR16B1->IR = 1;

        i++;
        if(i==2)
            i=0;
    }

    return;
}
