#ifndef VIEW_H
#define VIEW_H

#include "LCD.h"

#include "Model.h"

/**
 * Screens available to render on LCD screen
 */
typedef enum{
    viwBLANK, viwSPLASH, viwMAIN, viwCONFIG_HOME
}View;

/**
 * @brief Initializes the view.
 *
 * @warning This routine must be called before
 * any other.
 */
void View_Init(void);

/**
 * @brief Render a view
 *
 * @param v View to be rendered.
 */
void View_Render(View v);

#endif
