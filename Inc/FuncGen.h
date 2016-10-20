#ifndef FUNC_GEN_H
#define FUNC_GEN_H

#include <LPC11xx.h>

#include "math.h"
#include "DAC.h"

/**
 * @typdef Function type generate by the DAC output
 */
typedef enum{
    ftSine
}funcType;

/**
 * @brief Intializes function generator
 *
 * Configures all necessary peripheral structures
 */
void FuncGen_Init(void);

/**
 *
 */
void FuncGen_Process(void);

void FuncGen_Start(funcType f);

void TIM0_IRQHandler(void);


#endif
