#ifndef PROCESSMAN_H
#define	PROCESSMAN_H

#include "defs.h"

#include "BootConfig.h"

/**
 * Size of the process pool
 */
#define APP_PROC_MAXNUM 20

/**
 * Return values of a process
 */
typedef enum{
    prcFAIL, /**< The processes fails */
    prcSUCCESS, /**< The process ends successfully */
    prcREPEAT /**< The process must be reinserted in the pool */
}ProcessReturn;

/** Process routine function pointer type */
typedef ProcessReturn (*ProcessRoutine)(void);

/** Process structure */
typedef struct{
    ProcessRoutine pR;
}Process;

/**
 * @brief Initializes the process manager
 */
void ProcMan_Init(void);

/**
 * @brief Runs the process scheduler.
 *
 * @warning It must be placed in a loop.
 */
void ProcMan_RunScheduler(void);

/**
 * @brief Add a process to pool.
 *
 * @param p A process
 */
void ProcMan_AddProcess(Process *p);


#endif	/* PROCESSMAN_H */

