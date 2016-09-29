#include "App.h"

#include <LPC11xx.h>

int main(void){

    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6) | (1<<16);

    //__enable_irq();

    for(;;)	{

        App();
	}
}

