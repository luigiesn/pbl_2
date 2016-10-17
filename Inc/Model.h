#ifndef MODEL_H
#define MODEL_H

#include "defs.h"

#define DEFAULT_LANGUAGE lanPT
#define VIEW_COLUMS 16
#define VIEW_ROWS   2

typedef enum {
    msgLANG, msgGOOD_MORNING, msgGOOD_AFTERNOON, msgGOOD_EVENING, msgLIMITS, msgINF_LIMIT, msgSUP_LIMIT, msgTEMP,
    msgEND
}ModelMsg;

typedef enum {
    cotCONF_TEMP1, cotCONF_TEMP2, cotCONF_TIME, cotCONF_DATE,
    cotEND
}ModelConfigOptTxt;

typedef enum{
    mddTempLimits1,
    mddTempLimits2,
    mddTemp1,
    mddTemp2,
    mddTime,
    mddDayPeriod,
    mddDate,
    mddLanguage,
    mddConfigOptTxt,
    mddEnd
}ModelData;

typedef enum{
    mdpMORING, mdpAFTERNOON, mdpNIGHT
}mdlDayPeriod;

typedef enum {
    lanPT, lanEN, lanEND
}mdlLanguage;

typedef struct{
    unsigned int tempMin;
    unsigned int tempMax;
}mdlTempLimits;

typedef struct{
    unsigned int temp;
}mdlTemp;

typedef struct{
    unsigned char hour;
    unsigned char min;
}mdlTime;

typedef struct{
    unsigned char day;
    unsigned char month;
    unsigned char year;
}mdlDate;

void Model_Init(void);

// Variables operations
bool Model_SetValue(ModelData md, void* value);

void Model_GetValue(ModelData md, void* value);

char *Model_GetMessage(ModelMsg mm, mdlLanguage lang);

char *Model_GetConfigOptText(ModelConfigOptTxt cot, mdlLanguage lang);

char *Model_GetSplash(void);

// Menu operations
void Model_MenuNext(void);

void Model_MenuPrev(void);

unsigned char Model_GetMenuState(void);

void Model_SelectSubMenu(bool s);

bool Model_SubMenuIsSelected(void);


#endif
