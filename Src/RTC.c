#include "RTC.h"

static unsigned char params[rtcEND];

static ProcessReturn RTC_UpdateLocals(void);

static bool changed = true;

void RTC_Init(void){
    // init RTC parameters
    RTC_SetParam(rtcSECOND, 50);
    RTC_SetParam(rtcMINUTE, 59);
    RTC_SetParam(rtcHOUR, 3);
    RTC_SetParam(rtcDAY, 0);
    RTC_SetParam(rtcDATE, 1);
    RTC_SetParam(rtcMONTH, 1);
    RTC_SetParam(rtcYEAR, 0);

    static Process update;
    update.pR = RTC_UpdateLocals;

    ProcMan_AddProcess(&update);
}

void RTC_SetParam(rtcParam p, unsigned char v){
    params[p] = v;
    changed = true;
}

unsigned char RTC_ReadParam(rtcParam p){
    return params[p];
}

static ProcessReturn RTC_UpdateLocals(void){
    static unsigned int cnt = 0;

    cnt++;
    if(cnt < 10000)
        return prcREPEAT;

    cnt = 0;

    rtcParam tempParam;
    unsigned char temp;

    // update remote parameters
    for(tempParam = 0; tempParam < rtcEND; tempParam++){
        unsigned char temp[2];

        // convert binary to bcd code
        temp[0] = (unsigned char)tempParam;
        temp[1] = (params[tempParam]%10) | ((params[tempParam]/10) << 4);

        HAL_i2c_Send(idvRTC, temp, 2);
    }

    // update local parameters
    if(changed){
        changed = false;
        for(tempParam = 0; tempParam < rtcEND; tempParam++){
            HAL_i2c_Send(idvRTC, (unsigned char*)&tempParam, 1);
            temp = HAL_i2c_Receive(idvRTC);
            temp = (temp & 0x0f) + ((temp & 0x70) >> 4)*10;
            params[tempParam] = temp;
        }
    }

    return prcREPEAT;
}
