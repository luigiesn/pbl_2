#include "View.h"

typedef enum {
    tabLEFT, tabCENTER, tabRIGHT
}TabType;

static void View_Clear(void);
static unsigned char View_PrintTab(unsigned char* str, TabType t, unsigned char row);
static void View_WriteInteger(unsigned char i);
static void View_WriteDecimal(float f);

void View_Init(){
}

void View_Render(View v){
    View_Clear();

    switch (v){
        case viwBLANK:
        {
            LCD_WriteCommand(lcdCURSOR_OFF);
            break;
        }
        case viwSPLASH:
        {
            View_PrintTab(Model_GetSplash(), tabCENTER, 1);

            mdlLanguage tempLang;
            mdlDayPeriod tempDp;

            Model_GetValue(mddLanguage, (void*)&tempLang);
            Model_GetValue(mddDayPeriod, (void*)&tempDp);

            ModelMsg msg;
            msg = tempDp + 1;

            View_PrintTab(Model_GetMessage(msg, tempLang), tabCENTER, 2);

            break;
        }
        case viwMAIN:
        {
            mdlTime tempTime;
            mdlTemp tempTemp1, tempTemp2;

            Model_GetValue(mddTime, (void*)&tempTime);
            Model_GetValue(mddTemp1, (void*)&tempTemp1);
            Model_GetValue(mddTemp2, (void*)&tempTemp2);

            // parse from integer to character
            unsigned char time[6]=  {(unsigned char)(tempTime.hour/10) + '0', (unsigned char)(tempTime.hour%10) + '0', ':',(unsigned char)(tempTime.min/10) + '0',(unsigned char)(tempTime.min%10) + '0','\0'};

            LCD_WriteString("T1:");
            View_WriteDecimal((tempTemp1.temp)/10.0);

            View_PrintTab(time, tabRIGHT, 1);

            LCD_WriteCommand(lcdROW2);

            LCD_WriteString("T2:");
            View_WriteDecimal(tempTemp2.temp/10.0);

            break;
        }
        case viwCONFIG_HOME:
        {
            unsigned char opt, *optTxt, optDetail[VIEW_COLUMS+1];
            mdlLanguage tempLang;

            Model_GetValue(mddConfigOptTxt, (void*)&opt);
            Model_GetValue(mddLanguage, (void*)&tempLang);

            optTxt = Model_GetConfigOptText(opt, tempLang);

            unsigned char i;
            for(i = 0; i < VIEW_COLUMS ; i++)
                optDetail[i] = ' ';

            switch (opt){

                case cotCONF_DATE:
                {
                    mdlDate tempDate;
                    Model_GetValue(mddDate, (void*)&tempDate);

                    // parse from integer to character
                    optDetail[0] = tempDate.day/10 + '0';
                    optDetail[1] = tempDate.day%10 + '0';
                    optDetail[2] = '-';
                    optDetail[3] = tempDate.month/10 + '0';
                    optDetail[4] = tempDate.month%10 + '0';
                    optDetail[5] = '-';
                    optDetail[6] = tempDate.year/10 + '0';
                    optDetail[7] = tempDate.year%10 + '0';
                    optDetail[8] = '\0';
                    break;
                }
                case cotCONF_TIME:
                {
                    mdlTime tempTime;
                    Model_GetValue(mddTime, (void*)&tempTime);

                    // parse from integer to character
                    optDetail[0] = tempTime.hour/10 + '0';
                    optDetail[1] = tempTime.hour%10 + '0';
                    optDetail[2] = ':';
                    optDetail[3] = tempTime.min/10 + '0';
                    optDetail[4] = tempTime.min%10 + '0';
                    optDetail[5] = ':';
                    optDetail[6] = tempTime.sec/10 + '0';
                    optDetail[7] = tempTime.sec%10 + '0';

                    optDetail[8] = '\0';
                    break;
                }
                case cotCONF_TEMP1:
                {
                    mdlTempLimits tempTempLimits1;
                    Model_GetValue(mddTempLimits1, (void*)&tempTempLimits1);
                    unsigned int temp1;

                    // parse from integer to character
                    // min temp
                    temp1 = tempTempLimits1.tempMin;
                    optDetail[0] = ((temp1/100)%10 + '0');
                    optDetail[1] = ((temp1/10)%10 + '0');
                    optDetail[2] = ('.');
                    optDetail[3] = (temp1%10 + '0');

                    optDetail[4] = ' ';
                    optDetail[5] = ' ';
                    optDetail[6] = ' ';

                    // max temp
                    temp1 = tempTempLimits1.tempMax;
                    optDetail[7] = ((temp1/100)%10 + '0');
                    optDetail[8] = ((temp1/10)%10 + '0');
                    optDetail[9] = ('.');
                    optDetail[10] = (temp1%10 + '0');

                    optDetail[11] = '\0';

                    break;
                }
                case cotCONF_TEMP2:
                {
                    mdlTempLimits tempTempLimits2;
                    Model_GetValue(mddTempLimits2, (void*)&tempTempLimits2);
                    unsigned int temp2;

                    // parse from integer to character
                    // min temp
                    temp2 = tempTempLimits2.tempMin;
                    optDetail[0] = ((temp2/100)%10 + '0');
                    optDetail[1] = ((temp2/10)%10 + '0');
                    optDetail[2] = ('.');
                    optDetail[3] = (temp2%10 + '0');

                    optDetail[4] = ' ';
                    optDetail[5] = ' ';
                    optDetail[6] = ' ';

                    // max temp
                    temp2 = tempTempLimits2.tempMax;
                    optDetail[7] = ((temp2/100)%10 + '0');
                    optDetail[8] = ((temp2/10)%10 + '0');
                    optDetail[9] = ('.');
                    optDetail[10] = (temp2%10 + '0');

                    optDetail[11] = '\0';
                    break;
                }

            }

            View_PrintTab(optDetail, tabCENTER, 2);
            View_PrintTab(optTxt, tabCENTER, 1);

            unsigned char arrow[2] = {[0 ... 1] = '\0'};

            if(Model_SubMenuIsSelected()){
                arrow[0] = CHAR_LEFT_ARROW;
                View_PrintTab(arrow, tabLEFT, 2);

                arrow[0] = CHAR_RIGHT_ARROW;
                View_PrintTab(arrow, tabRIGHT, 2);
            }
            else{
                arrow[0] = CHAR_LEFT_ARROW;
                View_PrintTab(arrow, tabLEFT, 1);

                arrow[0] = CHAR_RIGHT_ARROW;
                View_PrintTab(arrow, tabRIGHT, 1);
            }
            break;
        }
    }
}

static void View_Clear(void){
    LCD_WriteCommand(lcdCLEAR);
}

static void View_WriteInteger(unsigned char i){
    LCD_WriteData(i + '0');
}

static void View_WriteDecimal(float f){
    unsigned char integer, decimal;

    integer = (unsigned char) f;
    decimal = (unsigned char)((f - (float)integer)*10);

    LCD_WriteData(integer/10 + '0');
    LCD_WriteData(integer%10 + '0');
    LCD_WriteData('.');

    if(f - decimal > 0)
        decimal++;

    LCD_WriteData(decimal + '0');
}

static unsigned char View_PrintTab(unsigned char* str, TabType t, unsigned char row){
    unsigned char c, offset;

    for(c = 0; str[c] != '\0'; c++); // count elements number in str

    if(c > VIEW_COLUMS)
        return 0;

    if(t == tabLEFT){
        offset = 0;
    }
    else if(t == tabCENTER){ // calculate text start position base on number of chars in str
        offset = (unsigned char)((VIEW_COLUMS - c)/2);
    }
    else if(t == tabRIGHT){
        offset = VIEW_COLUMS - c;
    }
    else
        return 0;

    // set starting cursor position
    LCD_WriteCommand((lcdCmd)(lcdSETTOXX | ((row - 0x01u) << 6) | offset));
    // write str
    LCD_WriteString((char*)str);

    return 1;
}
