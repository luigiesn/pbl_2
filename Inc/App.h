#ifndef APP_H
#define APP_H

#include "BootConfig.h"
#include "ProcessManager.h"

/**
 * @brief System main routine
 *
 * This routine initiates all basics
 * resources of the systems.
 *
 * App() execution is responsible for
 * call the boot routines and run the
 * process manager
 */
void App(void);

#endif
