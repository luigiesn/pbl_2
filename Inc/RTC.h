#ifndef RTC_H
#define RTC_H

#define RTC_ADDR 0xD0

typedef enum{
    rtcSECOND, rtcMINUTE, rtcHOUR, rtcDAY, rtcDATE, rtcMONTH, rtcYEAR
}rtcParam;

void RTC_Init(void);

void RTC_SetParam(rtcParam p, unsigned char v);

unsigned char RTC_ReadParam(rtcParam p);

#endif
