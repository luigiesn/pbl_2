#include "ProcessManager.h"

#include "BootConfig.h"

static struct {
    UINT8 head;
    UINT8 tail;
} local;

static Process *procs[APP_PROC_MAXNUM];

void ProcMan_Init(void) {
    local.head = 0;
    local.tail = 0;
}

void ProcMan_RunScheduler(void) {
    if (local.head != local.tail) {
        ProcessReturn tempProcRet;

        if (local.tail >= APP_PROC_MAXNUM)
            local.tail = 0;

        tempProcRet = procs[local.tail]->pR(); //execute

        if (tempProcRet == prcREPEAT) {
            ProcMan_AddProcess(procs[local.tail]); // add the last execution to queue
        }

        local.tail++;
    }
}

void ProcMan_AddProcess(Process *p) {
    if (local.head >= APP_PROC_MAXNUM)
        local.head = 0;

    procs[local.head++] = p;
}


