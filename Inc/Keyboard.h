#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "ProcessManager.h"

#define KBD_AD_CH 7

typedef enum{
    kysNOT_PRESSING, kysPRESSING, kysLONG_PRESSING, kysNULL
}keyState;

typedef enum{
    key_K1, key_K2, key_K3, key_K4, key_K5
}key;

void KBD_Boot(void);

keyState KBD_GetEvent(key k);

#endif
