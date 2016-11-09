#ifndef MODEL_H
#define MODEL_H

#include "defs.h"

#define DEFAULT_LANGUAGE lanPT
#define VIEW_COLUMS 16
#define VIEW_ROWS   2

/**
 * Messages list
 */
typedef enum {
    msgLANG, msgGOOD_MORNING, msgGOOD_AFTERNOON, msgGOOD_EVENING, msgLIMITS, msgINF_LIMIT, msgSUP_LIMIT, msgTEMP,
    msgEND
}ModelMsg;

/**
 * Options of configuration menu
 */
typedef enum {
    cotCONF_TEMP1, cotCONF_TEMP2, cotCONF_TIME, cotCONF_DATE,
    cotEND
}ModelConfigOptTxt;

/**
 * Data types list defined in the Model
 */
typedef enum{
    mddTempLimits1, /**< Channel 1 temperature detection thresholds */
    mddTempLimits2, /**< Channel 2 temperature detection thresholds */
    mddTemp1, /**< Instant temperature of channel 1 */
    mddTemp2, /**< Instant temperature of channel 2 */
    mddTime, /**< Current time stored in RTC */
    mddDayPeriod, /**< Period of the day */
    mddDate, /**< Current date stored in RTC */
    mddLanguage, /**< System language */
    mddConfigOptTxt, /**< Menu configuration option selected */
    mddEnd
}ModelData;

/** Day period variable */
typedef enum{
    mdpMORING, mdpAFTERNOON, mdpNIGHT
}mdlDayPeriod;

/** Language variable */
typedef enum {
    lanPT, lanEN, lanEND
}mdlLanguage;

/** Time limits variable */
typedef struct{
    unsigned int tempMin;
    unsigned int tempMax;
}mdlTempLimits;

/** Temperature variable */
typedef struct{
    unsigned int temp;
}mdlTemp;

/** Time variable */
typedef struct{
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
}mdlTime;

/** Date variable */
typedef struct{
    unsigned char day;
    unsigned char month;
    unsigned char year;
}mdlDate;

/**
 * @brief Initializes this
 */
void Model_Init(void);

/**
 * @brief Set a variable value
 *
 * @param md Variable data type referred.
 * @param value Value passed by reference
 */
bool Model_SetValue(ModelData md, void* value);

/**
 * @brief Get a variable value
 *
 * @param md Variable data type referred.
 * @param value Value passed by reference
 */
void Model_GetValue(ModelData md, void* value);

/**
 * @brief Get a message in a given language
 *
 * @param mm Message type.
 * @param lang Message language.
 *
 * @return Number of characters in the message.
 */
char *Model_GetMessage(ModelMsg mm, mdlLanguage lang);

/**
 * @brief Get a the label text of option selected menu option.
 *
 * @param cot Menu option.
 * @param lang Menu label text language.
 *
 * @return Number of characters in the label text.
 */
char *Model_GetConfigOptText(ModelConfigOptTxt cot, mdlLanguage lang);

/**
 * @brief Get the splash text.
 *
 * @return Number of characters in the splash text.
 */
char *Model_GetSplash(void);

/**
 * @brief Change to next menu option.
 */
void Model_MenuNext(void);

/**
 * @brief Change to previous menu option.
 */
void Model_MenuPrev(void);

/**
 * @brief Get the current menu option.
 *
 * @return Current menu state
 */
unsigned char Model_GetMenuState(void);

/**
 * @brief Enters in sub menu from current option
 *
 * @param s Selection action. Enter or exit from a sub-menu.
 */
void Model_SelectSubMenu(bool s);

/**
 * @brief Checks is a menu is selected.
 *
 * @return Selection state
 */
bool Model_SubMenuIsSelected(void);


#endif
