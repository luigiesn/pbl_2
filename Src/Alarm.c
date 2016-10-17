#include "Alarm.h"

typedef enum{
    alsIDLE, alsINIT
}AlarmState;

static struct {
    AlarmState state;
} local;

static ProcessReturn Alarm_Process(void);

void Alarm_Boot(void){

    local.state = alsINIT;

    static Process alarm;
    alarm.pR = Alarm_Process;
    ProcMan_AddProcess(&alarm);
}

static ProcessReturn Alarm_Process(void){
    switch (local.state){
        case alsIDLE:
        {

            break;
        }
        case alsINIT:
        {
            UI_Init();
            RTC_Init();
            DiffAmp_Init();

            local.state = alsIDLE;
            break;
        }
    }

    return prcREPEAT;
}
