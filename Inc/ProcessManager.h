#ifndef PROCESSMAN_H
#define	PROCESSMAN_H

#include "defs.h"

#define APP_PROC_MAXNUM 20

typedef enum{
    prcFAIL, prcSUCCESS, prcREPEAT
}ProcessReturn;

typedef ProcessReturn (*ProcessRoutine)(void);

typedef struct{
    ProcessRoutine pR;
}Process;

void ProcMan_Init(void);

void ProcMan_RunScheduler(void);

void ProcMan_AddProcess(Process *p);

#endif	/* PROCESSMAN_H */

