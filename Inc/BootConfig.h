#ifndef BOOTCONFIG_H
#define	BOOTCONFIG_H

#include "defs.h"

/**
 * @typedef Type to define a BootRoutine function
 */
typedef void (*BootRoutine)(void);

/**
 * @brief Get all boot routines in application
 *
 * All routines must be include in BootConfig.c
 * BootRoutine type vector.
 *
 * @return A vector of BootRoutines
 *
 * The vector is ended with 0.
 *
 * @warning All boot routines must be called until
 * the last element, a zero.
 */
BootRoutine *Boot_getBootRoutines(void);

#endif	/* BOOTCONFIG_H */
