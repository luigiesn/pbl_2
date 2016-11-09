#include "Keyboard.h"

#define VREF 3.3

#define R1 2000
#define R2 330
#define R3 620
#define R4 1000
#define R5 3300

#define TH1 (0)
#define TH2 (1023*((float)R2/(R2+R1)))
#define TH3 (1023*((float)(R3+R2)/(R3+R2+R1)))
#define TH4 (1023*((float)(R4+R3+R2)/(R4+R3+R2+R1)))
#define TH5 (1023*((float)(R5+R4+R3+R2)/(R5+R4+R3+R2+R1)))

#define DEAD_ZONE 50
#define KEY_NUMBR 5

#define LONG_HOLD 5000
#define DEBOUNCE_TIME 250

#define UP 0
#define DOWN 1

static unsigned char keyNow[KEY_NUMBR]; // keys state

keyState state[KEY_NUMBR];

static bool changed = false;

static ProcessReturn KBD_Process(void);
static void KBD_Debounce(key k);

void KBD_Boot(void){

    static Process kbd;
    kbd.pR = KBD_Process;
    ProcMan_AddProcess(&kbd);
}

static ProcessReturn KBD_Process(void){
    HAL_ADC_SetChannel(KBD_AD_CH);

    unsigned int temp;
    temp = HAL_ADC_GetSample(); // get keyboard current value

    unsigned char key;
    for(key = 0; key < KEY_NUMBR; key++){
        keyNow[key] = UP; // reset all keys state
    }

    // verify which key is pressed

    if(temp < TH1 + DEAD_ZONE){
        keyNow[0] = DOWN;

    }
    else if(temp < TH2 + DEAD_ZONE && temp > TH2 - DEAD_ZONE){
        keyNow[1] = DOWN;

    }
    else if(temp < TH3 + DEAD_ZONE && temp > TH3 - DEAD_ZONE){
        keyNow[2] = DOWN;

    }
    else if(temp < TH4 + DEAD_ZONE && temp > TH4 - DEAD_ZONE){
        keyNow[3] = DOWN;

    }
    else if(temp < TH5 + DEAD_ZONE && temp > TH5 - DEAD_ZONE){
        keyNow[4] = DOWN;

    }

    unsigned char i;
    for(i = 0; i < KEY_NUMBR; i++){
        // debounce all keys from keyboard
        KBD_Debounce(i);
    }

    return prcREPEAT;
}

static void KBD_Debounce(key k){
    static unsigned char keyLast[KEY_NUMBR]; // store key last state
    static unsigned int keyBounceCnt[KEY_NUMBR] = {[0 ... KEY_NUMBR - 1] = 0}; // bouncing count

    // if key seems stabilized
    if(keyNow[k] == keyLast[k]){
        // wait for key stabilization until DEBOUNCE_TIME
        if(keyBounceCnt[k] <= DEBOUNCE_TIME)
            keyBounceCnt[k]++;
    }
    else{
        // if key is bouncing
        keyBounceCnt[k] = 0;
        keyLast[k] = keyNow[k];
    }

    // if the key stabilized
    if(keyBounceCnt[k] == DEBOUNCE_TIME){

        if(keyNow[k] == DOWN){
            state[k] = kysPRESSING;
            changed = true;
        }
        else
            state[k] = kysNOT_PRESSING;
    }
}

keyState KBD_GetEvent(key k){
    keyState temp = state[k];

    // reset to prevent misreading
    state[k] = kysNULL;

    return temp;
}

bool KBD_Changed(void){
    bool temp = changed;

    // reset to prevent misreading
    changed = false;

    return temp;
}


