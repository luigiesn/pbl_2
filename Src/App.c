#include "App.h"

void App(void){

    // get declared boot routines
    BootRoutine *tempBootRoutine = Boot_getBootRoutines();

    UINT8 p;

    ProcMan_Init(); // initializes the process manager

    for (p = 0; tempBootRoutine[p]; p++) { // boot system
        tempBootRoutine[p]();
    }

    for (;;) {
        ProcMan_RunScheduler(); // run process scheduler
    }
}


