#include "UI_Control.h"

#define UP_BUTTON key_K5
#define UP_EVENT kysPRESSING

#define DOWN_BUTTON key_K1
#define DOWN_EVENT kysPRESSING

#define SELECT_BUTTON key_K3
#define SELECT_EVENT kysPRESSING

#define LEFT_BUTTON key_K2
#define LEFT_EVENT kysPRESSING

#define RIGHT_BUTTON key_K4
#define RIGHT_EVENT kysPRESSING

#define BACKLIGHT_COUNTDOWN 40000

typedef enum{
    uisINIT, uisRUNNING
}UiState;

typedef enum{
    scrSPLASH, scrMAIN, scrCONFIG_HOME, scrCONFIG_TEMP1, scrCONFIG_TEMP2, scrCONFIG_TIME, scrCONFIG_DATE
}Screen;

typedef enum{
    sscTEMP1, sscTEMP2, sscTIME, sscDATE, sscNONE
}SubScreen;

static struct{
    UiState state;

    Screen scr;
    SubScreen ssc;

    void(*view)(void);

    unsigned int calls;
} local;

static ProcessReturn UI_Process(void);
static ProcessReturn UI_ScreenProcess(void);
static ProcessReturn UI_BacklightProcess(void);
static ProcessReturn UI_VarsCheckProcess(void);

ProcessReturn UI_Config_Home(void);
ProcessReturn UI_Config_Time(void);
ProcessReturn UI_Config_Temp1(void);
ProcessReturn UI_Config_Temp2(void);
ProcessReturn UI_Config_Date(void);
ProcessReturn UI_Splash(void);
ProcessReturn UI_Main(void);

void UI_Init(void){
    local.state = uisINIT;

    static Process ui, scr, backlight, varCheck;
    ui.pR = UI_Process;
    scr.pR = UI_ScreenProcess;
    backlight.pR = UI_BacklightProcess;
    varCheck.pR = UI_VarsCheckProcess;

    ProcMan_AddProcess(&ui);
    ProcMan_AddProcess(&scr);
    ProcMan_AddProcess(&backlight);
    ProcMan_AddProcess(&varCheck);
}

static ProcessReturn UI_Process(void){
    static Process viewRender;

    switch (local.state){
        case uisINIT:
        {
            Model_Init();
            View_Init();

            View_Render(viwBLANK);

            mdlLanguage tempLan = DEFAULT_LANGUAGE;
            mdlDayPeriod tempDp = mdpAFTERNOON;
            mdlTemp tempT1 = {0};
            mdlTemp tempT2 = {0};
 //           mdlTime tempTime = {12,13};
            mdlDate tempData = {1,4,7};
            mdlTempLimits temp1Limits = {220 , 510};
            mdlTempLimits temp2Limits = {210 , 500};

            Model_SetValue(mddLanguage, (void*)&tempLan);
            Model_SetValue(mddDayPeriod, (void*)&tempDp);
            Model_SetValue(mddTemp1, (void*)&tempT1);
            Model_SetValue(mddTemp2, (void*)&tempT2);
//            Model_SetValue(mddTime, (void*)&tempTime);
            Model_SetValue(mddDate, (void*)&tempData);
            Model_SetValue(mddTempLimits1, (void*)&temp1Limits);
            Model_SetValue(mddTempLimits2, (void*)&temp2Limits);

            local.calls = 0;

            local.scr = scrSPLASH;
            local.ssc = sscNONE;

            local.state = uisRUNNING;
            break;
        }

        case uisRUNNING:
        {
            local.calls++;

            if(local.calls == 2000){
                viewRender.pR = local.view;
                ProcMan_AddProcess(&viewRender);
                local.calls = 0;

            }

            break;
        }

    }

    return prcREPEAT;
}

static ProcessReturn UI_BacklightProcess(void){
    static unsigned int bl;
    if(KBD_Changed() || local.scr == scrSPLASH){
        LCD_BackLight(true);
        bl = BACKLIGHT_COUNTDOWN;
    }
    if(bl){
        bl--;
        if(bl == 0){
            LCD_BackLight(false);
        }
    }

    return prcREPEAT;
}

static ProcessReturn UI_VarsCheckProcess(void){
    static unsigned int cnt = 0;

    cnt++;
    if(cnt != 2500)
        return prcREPEAT;

    cnt = 0;

    mdlTemp tempT;

    tempT.temp = DiffAmp_GetSample(AMP_A_CH);
    Model_SetValue(mddTemp1, (void*)&tempT);

    tempT.temp = DiffAmp_GetSample(AMP_B_CH);
    Model_SetValue(mddTemp2, (void*)&tempT);

    mdlTime time;
    time.hour = RTC_ReadParam(rtcHOUR);
    time.min = RTC_ReadParam(rtcMINUTE);

    Model_SetValue(mddTime, (void*)&time);

    return prcREPEAT;
}

static ProcessReturn UI_ScreenProcess(void){

    switch (local.scr){
        case scrSPLASH:
        {
            static unsigned int wait = 0;
            Model_SelectSubMenu(false);

            local.view = UI_Splash;

            wait++;
            if(wait == 500)
                local.scr = scrMAIN;

            break;
        }
        case scrMAIN:
        {
            local.view = UI_Main;

            if(KBD_GetEvent(SELECT_BUTTON) == SELECT_EVENT){
                local.scr = scrCONFIG_HOME;
            }
            break;
        }
        case scrCONFIG_HOME:
        {

            local.view = UI_Config_Home;

            if(!Model_SubMenuIsSelected()){

                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT)
                    Model_MenuPrev();

                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT)
                    Model_MenuNext();

                else if(KBD_GetEvent(SELECT_BUTTON) == SELECT_EVENT)
                    local.scr = scrMAIN;

                else if(KBD_GetEvent(DOWN_BUTTON) == DOWN_EVENT){
                    Model_SelectSubMenu(true);

                    unsigned char cot;
                    cot = Model_GetMenuState();

                    if(cot == cotCONF_DATE)
                        local.ssc = sscDATE;
                    else if(cot == cotCONF_TEMP1)
                        local.ssc = sscTEMP1;
                    else if(cot == cotCONF_TEMP2)
                        local.ssc = sscTEMP2;
                    else if(cot == cotCONF_TIME)
                        local.ssc = sscTIME;
                }
            }
            else{
                if(KBD_GetEvent(UP_BUTTON) == UP_EVENT){
                    Model_SelectSubMenu(false);
                }
            }
            break;
        }

    }

    switch (local.ssc){
        case sscNONE:
        {
            break;
        }
        case sscTIME:
        {
            static unsigned char fieldSel = 0;

            mdlTime time;
            //Model_GetValue(mddTime, (void*)&time);

            time.hour = RTC_ReadParam(rtcHOUR);
            time.min = RTC_ReadParam(rtcMINUTE);

            if(fieldSel == 0){

                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT){
                    time.hour--;
                }
                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT){
                    time.hour++;
                }

            }
            else if(fieldSel == 1){

                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT){
                    time.min--;
                }
                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT){
                    time.min++;

                }

            }

            if(KBD_GetEvent(DOWN_BUTTON) == DOWN_EVENT){
                fieldSel++;
                if(fieldSel == 2)
                    fieldSel = 0;
            }

            RTC_SetParam(rtcHOUR, time.hour);
            RTC_SetParam(rtcMINUTE, time.min);

            break;
        }
        case sscTEMP1:
        {
            static unsigned char fieldSel = 0;

            mdlTempLimits t1Limits;
            Model_GetValue(mddTempLimits1, (void*)&t1Limits);

            if(fieldSel == 0){
                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT){
                    t1Limits.tempMin--;
                }
                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT){
                    t1Limits.tempMin++;
                }
                else if(KBD_GetEvent(DOWN_BUTTON) == DOWN_EVENT){
                    fieldSel = 1;
                }
            }
            else if(fieldSel == 1){
                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT){
                    t1Limits.tempMax--;
                }
                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT){
                    t1Limits.tempMax++;
                }
                else if(KBD_GetEvent(DOWN_BUTTON) == DOWN_EVENT){
                    fieldSel = 0;
                }
            }

            Model_SetValue(mddTempLimits1, (void*)&t1Limits);

            break;
        }
        case sscTEMP2:
        {
            static unsigned char fieldSel = 0;

            mdlTempLimits t2Limits;
            Model_GetValue(mddTempLimits2, (void*)&t2Limits);

            if(fieldSel == 0){
                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT){
                    t2Limits.tempMin--;
                }
                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT){
                    t2Limits.tempMin++;
                }
                else if(KBD_GetEvent(DOWN_BUTTON) == DOWN_EVENT){
                    fieldSel = 1;
                }
            }
            else if(fieldSel == 1){
                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT){
                    t2Limits.tempMax--;
                }
                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT){
                    t2Limits.tempMax++;
                }
                else if(KBD_GetEvent(DOWN_BUTTON) == DOWN_EVENT){
                    fieldSel = 0;
                }
            }

            Model_SetValue(mddTempLimits2, (void*)&t2Limits);

            break;
        }
        case sscDATE:
        {
            static unsigned char fieldSel = 0;

            mdlDate date;
            Model_GetValue(mddDate, (void*)&date);


            if(fieldSel == 0){
                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT)
                    date.day--;

                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT)
                    date.day++;
            }
            else if(fieldSel == 1){
                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT)
                    date.month--;

                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT)
                    date.month++;
            }
            else if(fieldSel == 2){
                if(KBD_GetEvent(LEFT_BUTTON) == LEFT_EVENT)
                    date.year--;

                else if(KBD_GetEvent(RIGHT_BUTTON) == RIGHT_EVENT)
                    date.year++;
            }

            if(KBD_GetEvent(DOWN_BUTTON) == DOWN_EVENT){
                fieldSel++;
                if(fieldSel == 3)
                    fieldSel = 0;
            }

            Model_SetValue(mddDate, (void*)&date);

            break;
        }

    }

    return prcREPEAT;
}

ProcessReturn UI_Config_Home(void){

    View_Render(viwCONFIG_HOME);

    return prcSUCCESS;
}

ProcessReturn UI_Splash(void){

    View_Render(viwSPLASH);

    return prcSUCCESS;
}

ProcessReturn UI_Main(void){

    View_Render(viwMAIN);

    return prcSUCCESS;
}
