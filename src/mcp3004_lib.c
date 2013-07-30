#include "spi.h"


/** Receive a sample from the ADC specified. Single-ended mode
 *
 * @param LPC_SPI structure
 * @param channel number. from 0 for chn 0 to 3 for chn 3
 * @return the sample received as 16 bit unsigned
 */
uint16_t RX_ADC(LPC_SPI_TypeDef *SPIx, uint8_t chn)
{
  uint16_t sample;

  while ( (SPIx->STAT & SPI_STAT_TXRDY) == 0 );
  SPIx->TXDATCTL = SPI_TXDATCTL_FSIZE(8-1) | 0x01; 	// Start bit
  while ( (SPIx->STAT & SPI_STAT_RXRDY) == 0 );
  SPIx->RXDAT;

  while ( (SPIx->STAT & SPI_STAT_TXRDY) == 0 );
  SPIx->TXDATCTL = SPI_TXDATCTL_FSIZE(8-1) | 0x80 | ((chn&0x03)<<4);	// chn is the ADC channel
  while ( (SPIx->STAT & SPI_STAT_RXRDY) == 0 );
  sample = SPIx->RXDAT;				// receive the bit9,bit8
  sample = ((sample & 0x03)<<8);

  while ( (SPIx->STAT & SPI_STAT_TXRDY) == 0 );
  SPIx->TXDATCTL = SPI_TXDATCTL_FSIZE(8-1) | SPI_TXDATCTL_EOT | 0xAA;	// dummy byte
  while ( (SPIx->STAT & SPI_STAT_RXRDY) == 0 );
  sample = sample | SPIx->RXDAT;	// receive the bit7 to bit0

  return sample;
}

/** Receive a sample from the ADC chn 0. Single-ended mode
 *
 * @param LPC_SPI structure
 * @return the sample received as 16 bit unsigned
 */
uint16_t RX_ADC_ch0(LPC_SPI_TypeDef *SPIx)
{
  return RX_ADC( SPIx, 0);
}

/** Receive a sample from the ADC chn 1. Single-ended mode
 *
 * @param LPC_SPI structure
 * @return the sample received as 16 bit unsigned
 */
uint16_t RX_ADC_ch1(LPC_SPI_TypeDef *SPIx)
{
  return RX_ADC( SPIx, 1);
}

/** Receive a sample from the ADC chn 2. Single-ended mode
 *
 * @param LPC_SPI structure
 * @return the sample received as 16 bit unsigned
 */
uint16_t RX_ADC_ch2(LPC_SPI_TypeDef *SPIx)
{
  return RX_ADC( SPIx, 2);
}

/** Receive a sample from the ADC chn 3. Single-ended mode
 *
 * @param LPC_SPI structure
 * @return the sample received as 16 bit unsigned
 */
uint16_t RX_ADC_ch3(LPC_SPI_TypeDef *SPIx)
{
  return RX_ADC( SPIx, 3);
}
