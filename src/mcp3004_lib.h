#ifndef _MCP3004LIB_H_
#define _MCP3004LIB_H_

#include "LPC8xx.h"

uint16_t RX_ADC(LPC_SPI_TypeDef *SPIx, uint8_t chn);
uint16_t RX_ADC_ch0(LPC_SPI_TypeDef *SPIx);
uint16_t RX_ADC_ch1(LPC_SPI_TypeDef *SPIx);
uint16_t RX_ADC_ch2(LPC_SPI_TypeDef *SPIx);
uint16_t RX_ADC_ch3(LPC_SPI_TypeDef *SPIx);

#endif
