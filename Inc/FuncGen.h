#ifndef FUNC_GEN_H
#define FUNC_GEN_H

#include <LPC11xx.h>

#include "DAC.h"

typedef enum{
    ftSine
}funcType;

void FuncGen_Init(void);

void FuncGen_Process(void);

void FuncGen_Start(funcType f);

void TIM0_IRQHandler(void);


#endif
