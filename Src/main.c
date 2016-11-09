#include "App.h"

#include <LPC11xx.h>

int main(void){

    // configure clock busS
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6) | (1<<16);

    //__enable_irq();

    for(;;)	{

        // runs the application
        App();
	}
}

