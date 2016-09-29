#ifndef BOOTCONFIG_H
#define	BOOTCONFIG_H

#include "defs.h"

typedef void (*BootRoutine)(void);

BootRoutine *Boot_getBootRoutines(void);

#endif	/* BOOTCONFIG_H */
