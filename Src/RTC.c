#include "RTC.h"

#include "HAL_i2c.h"
#include "RTC.h"

void RTC_Init(void){
    RTC_SetParam(rtcSECOND, 0);
    RTC_SetParam(rtcMINUTE, 23);
    RTC_SetParam(rtcHOUR, 0);
    RTC_SetParam(rtcDAY, 0);
    RTC_SetParam(rtcDATE, 1);
    RTC_SetParam(rtcMONTH, 1);
    RTC_SetParam(rtcYEAR, 0);
}

void RTC_SetParam(rtcParam p, unsigned char v){
    unsigned char temp[2] = {(unsigned char)p , v};
    HAL_i2c_Send(idvRTC, temp, 2);

}

unsigned char RTC_ReadParam(rtcParam p){
    HAL_i2c_Send(idvRTC, (unsigned char*)&p, 1);
    return HAL_i2c_Receive(idvRTC);
}
