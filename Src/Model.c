#include "Model.h"

#define STRING(b,l,m)  (b[l] + (VIEW_COLUMS+1)*m)

#define WELCOME_MSG_OFFSET 1

mdlTempLimits temp1Limits;
mdlTempLimits temp2Limits;
mdlTemp temp1;
mdlTemp temp2;
mdlDate date;
mdlTime time;
mdlDayPeriod dp;
mdlLanguage language;
unsigned char cot;
bool subScreenSelected;

unsigned char splash[] = {"X ELETRONICA"};

unsigned char msgPT[msgEND][VIEW_COLUMS+1] = {
   "Portugues",
   "Bom dia",
   "Boa tarde",
   "Boa noite",
   "Limite",
   "Inferior",
   "Superior",
   "Temperatura"
};

unsigned char cotPT[cotEND][VIEW_COLUMS+1] = {
   "Temperatura 1",
   "Temperatura 2",
   "Hora",
   "Dia"
};

unsigned char msgEN[msgEND][VIEW_COLUMS+1] = {
   "English",
   "Good morning",
   "Good afternoon",
   "Good evening",
   "Limit",
   "Lower",
   "Upper",
   "Temperature"
};

unsigned char cotEN[cotEND][VIEW_COLUMS+1] = {
   "Temperature 1",
   "Temperature 2",
   "Time",
   "Date"
};

unsigned char *msgTranslation[lanEND] = {
    (unsigned char*)msgPT,
    (unsigned char*)msgEN
};

unsigned char *cotTranslation[lanEND] = {
    (unsigned char*)cotPT,
    (unsigned char*)cotEN
};

void* data[mddEnd];
unsigned char ModelDataSize[mddEnd];

void Model_Init(void){
    data[mddDate] = (void*) &date;
    data[mddTemp1] = (void*) &temp1;
    data[mddTemp2] = (void*) &temp2;
    data[mddTempLimits1] = (void*) &temp1Limits;
    data[mddTempLimits2] = (void*) &temp2Limits;
    data[mddTime] = (void*) &time;
    data[mddLanguage] = (void*) &language;
    data[mddDayPeriod] = (void*) &dp;
    data[mddConfigOptTxt] = (void*) &cot;

    subScreenSelected = false;
}

bool Model_SetValue(ModelData md, void *value){
    switch(md){
        case mddDate:
        {
            mdlDate *aux = (mdlDate*)value;

            if(aux->year <= 99 && aux->month <= 12 && aux->day <= 31){
                *((mdlDate*)data[mddDate]) = *aux;
                return true;
            }
            break;
        }
        case mddDayPeriod:
        {
            mdlDayPeriod *aux = (mdlDayPeriod*)value;

            if(*aux <= (mdlDayPeriod)2){
                *((mdlDayPeriod*)data[mddDayPeriod]) = *aux;
                return true;
            }
            break;
        }
        case mddTemp1:
        {
            mdlTemp *aux = (mdlTemp*)value;

            if(aux->temp <= 999){
                *((mdlTemp*)data[mddTemp1]) = *aux;
                return true;
            }
            break;
        }
        case mddTemp2:
        {
            mdlTemp *aux = (mdlTemp*)value;

            if(aux->temp <= 999){
                *((mdlTemp*)data[mddTemp2]) = *aux;
                return true;
            }
            break;
        }
        case mddTempLimits1:
        {
            mdlTempLimits *aux = (mdlTempLimits*)value;

            if(aux->tempMax <= 999 && aux->tempMin <= 999){
                *((mdlTempLimits*)data[mddTempLimits1]) = *aux;
                return true;
            }
            break;
        }
        case mddTempLimits2:
        {
            mdlTempLimits *aux = (mdlTempLimits*)value;

            if(aux->tempMax <= 999 && aux->tempMin <= 999){
                *((mdlTempLimits*)data[mddTempLimits2]) = *aux;
                return true;
            }
            break;
        }
        case mddTime:
        {
            mdlTime *aux = (mdlTime*)value;

            if(aux->hour <= 23 && aux->min <= 59){
                *((mdlTime*)data[mddTime]) = *aux;
                return true;
            }
            break;
        }
    }

    return false;
}

void Model_GetValue(ModelData md, void* value){
    switch (md) {
        case mddConfigOptTxt:
        {
            *((unsigned char*)value) = *((unsigned char*)data[mddConfigOptTxt]);
            break;
        }
        case mddDate:
        {
            *((mdlDate*)value) = *((mdlDate*)data[mddDate]);
            break;
        }
        case mddDayPeriod:
        {
            *((mdlDayPeriod*)value) = *((mdlDayPeriod*)data[mddDayPeriod]);
            break;
        }
        case mddLanguage:
        {
            *((mdlLanguage*)value) = *((mdlLanguage*)data[mddLanguage]);
            break;
        }
        case mddTemp1:
        {
            *((mdlTemp*)value) = *((mdlTemp*)data[mddTemp1]);
            break;
        }
        case mddTemp2:
        {
            *((mdlTemp*)value) = *((mdlTemp*)data[mddTemp2]);
            break;
        }
        case mddTempLimits1:
        {
            *((mdlTempLimits*)value) = *((mdlTempLimits*)data[mddTempLimits1]);
            break;
        }
        case mddTempLimits2:
        {
            *((mdlTempLimits*)value) = *((mdlTempLimits*)data[mddTempLimits2]);
            break;
        }
        case mddTime:
        {
            *((mdlTime*)value) = *((mdlTime*)data[mddTime]);
            break;
        }
    }
}

char *Model_GetMessage(ModelMsg mm, mdlLanguage lang){
    return STRING(msgTranslation, lang, (unsigned char)mm);
}

char *Model_GetConfigOptText(ModelConfigOptTxt cot, mdlLanguage lang){
    return STRING(cotTranslation, lang, (unsigned char)cot);
}

char *Model_GetSplash(void){
    return splash;
}

void Model_MenuNext(void){
    if(*((unsigned char*)data[mddConfigOptTxt]) < cotEND - 1)
        *((unsigned char*)data[mddConfigOptTxt]) += 1;
}

void Model_MenuPrev(void){
    if(*((unsigned char*)data[mddConfigOptTxt]) > 0)
        *((unsigned char*)data[mddConfigOptTxt]) -= 1;
}

unsigned char Model_GetMenuState(void){
     return *((unsigned char*)data[mddConfigOptTxt]);
}

void Model_SelectSubMenu(bool s){
    subScreenSelected = s;
}
bool Model_SubMenuIsSelected(void){
    return subScreenSelected;
}
