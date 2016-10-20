#ifndef IO_H
#define IO_H

#include "Port_HAL.h"

/**
  * @brief Configures all I/Os
  *
  * @warning This must be called before any function
  * which uses or configure any input or output peripheral.
  */
void Io_Init(void);

#endif
