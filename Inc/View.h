#ifndef VIEW_H
#define VIEW_H

#include "LCD.h"

#include "Model.h"

typedef enum{
    viwBLANK, viwSPLASH, viwMAIN, viwCONFIG_HOME
}View;

void View_Init(void);

void View_Render(View v);

#endif
