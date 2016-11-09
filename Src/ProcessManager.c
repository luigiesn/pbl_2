#include "ProcessManager.h"

static struct {
    UINT8 head;
    UINT8 tail;
} local;

static Process *procs[APP_PROC_MAXNUM];

void ProcMan_Init(void) {
    // intializes ringbuffer
    local.head = 0;
    local.tail = 0;
}

void ProcMan_RunScheduler(void) {
    if (local.head != local.tail) {
        ProcessReturn tempProcRet;

        if (local.tail >= APP_PROC_MAXNUM) // check if buffer tail reached to the end
            local.tail = 0; // move tail pointer to beginning

        tempProcRet = procs[local.tail]->pR(); //execute

        if (tempProcRet == prcREPEAT) {
            ProcMan_AddProcess(procs[local.tail]); // add the last execution to queue
        }

        local.tail++; // increment tail pointer
    }
}

void ProcMan_AddProcess(Process *p) {
    if (local.head >= APP_PROC_MAXNUM) // check if buffer head reached to the end
        local.head = 0; // move head pointer to beginning

    procs[local.head++] = p; // increment head pointer
}


