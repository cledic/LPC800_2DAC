#include "spi.h"

/** Send a sample to the DAC.
 *
 * @param LPC_SPI structure
 * @param sample to send
 * @return none
 */
void TX_DAC(LPC_SPI_TypeDef *SPIx, uint16_t sample)
{

	sample = sample & 0x0FFF;
	sample = sample | 0x3000;		// b15=DAC_A, b14=Buffered, b13=OutputGain, b12=Shutdown

	while ( (SPIx->STAT & SPI_STAT_TXRDY) == 0 );
	SPIx->TXDATCTL = SPI_TXDATCTL_FSIZE(8-1) | (sample >> 8); 	// upper byte
	while ( (SPIx->STAT & SPI_STAT_RXRDY) == 0 );
	SPIx->RXDAT;

	while ( (SPIx->STAT & SPI_STAT_TXRDY) == 0 );
	SPIx->TXDATCTL = SPI_TXDATCTL_FSIZE(8-1) | SPI_TXDATCTL_EOT | (sample & 0xFF);	// lower byte
	while ( (SPIx->STAT & SPI_STAT_RXRDY) == 0 );
	SPIx->RXDAT;

}
