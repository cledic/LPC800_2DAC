#ifndef _MCP4921LIB_H_
#define _MCP4921LIB_H_

#include "LPC8xx.h"

void TX_DAC(LPC_SPI_TypeDef *SPIx, uint16_t sample);

#endif
