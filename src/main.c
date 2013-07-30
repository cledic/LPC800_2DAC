/**************************************************************************/
/*!
    @file     main.c

    @section LICENSE

    Software License Agreement (BSD License)

    Copyright (c) 2013, K. Townsend (microBuilder.eu)
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. Neither the name of the copyright holders nor the
    names of its contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
    EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
    LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
    ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/**************************************************************************/
#include <stdio.h>
#include "LPC8xx.h"
#include "gpio.h"
#include "mrt.h"
#include "uart.h"
#include "spi.h"
#include "systick.h"

#include "power_mode.h"
#include "mcp3004_lib.h"
#include "xmon_lib.h"
#include "dds.h"
#include "mcp4921_lib.h"

/* */
//#define USE_XMON 1

/* */
#define MODE_RX		0
#define MODE_TX		1
void SwitchMatrix_Init( void);

/* */
#define OUTPUT		1
#define INPUT		0

#if defined(__CODE_RED)
  #include <cr_section_macros.h>
  #include <NXP/crp.h>
  __CRP const unsigned int CRP_WORD = CRP_NO_CRP ;
#endif

#define LED_LOCATION    (2)

uint8_t i;
uint16_t sample;
uint32_t idx;
uint32_t ttick;
uint32_t freqgen=440;

int main(void)
{

  /* Configure the core clock/PLL via CMSIS */
  SystemCoreClockUpdate();

  /* Initialise the GPIO block */
  gpioInit();

  /* Initialise the UART block for printf or XMON */
#ifdef USE_XMON
  XMon_Init();
#else
  uart0Init( 230400);
#endif

  /*Configure the Systick timer for 100Hz period */
  SysTick_Init();

  /* Configure the multi-rate timer for 22100Hz period */
  mrtInit( SystemCoreClock/22100);

//  printf("Init SPI0\r\n");

  /* Configure the SPI0 interface*/
  spiInit( LPC_SPI0, 1, 0);				// div=1 -> 6Mhz

//  printf("Init Matrix\r\n");

  SwitchMatrix_Init();

  ddsInit( freqgen);

#ifdef USE_XMON
  XMon_plotZero( 0);
  XMon_plotZero( 1);
  XMon_plotZero( 2);
  XMon_plotZero( 3);
#endif

  idx=0;
  ttick=getTimerTick();
  while(1)
  {

#ifdef USE_XMON
#if 0
	if ( idx > 100) {
		XMon_plotZero( 0);
		XMon_plotZero( 1);
		XMon_plotZero( 2);
		XMon_plotZero( 3);
		idx=0;
	}
	//XMon_plot( RX_ADC( LPC_SPI0, 0), 0);
	//XMon_plot( RX_ADC( LPC_SPI0, 1), 1);
	//XMon_plot( RX_ADC( LPC_SPI0, 2), 2);
	//XMon_plot( RX_ADC( LPC_SPI0, 3), 3);
#endif
	//
	sample = dds_sample();
	XMon_plot( sample, 0);
#else
	/* Sync the DAC with systick timer */
	//ttick=getTimerTick();
	//while( getTimerTickDiff( ttick) < 1);

	/* Sync the dac with MRT 0 module */
	while( !mrt0_flag);
	mrt0_flag=0;

	//sample = RX_ADC( LPC_SPI0, 0);
	sample = dds_sample();
	//printf("sample: 0x%X\r\n", sample);
	TX_DAC( LPC_SPI0, (sample>>4));
	//
	if ( getTimerTickDiff( ttick) > 300 ) {
		freqgen +=100;
		freqgen = dds_setFreq( freqgen);
		ttick=getTimerTick();
	}
#endif
	//
	idx++;
  }
}

void SwitchMatrix_Init()
{
    /* Enable SWM clock */
    LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);

    /* Pin Assign 8 bit Configuration */
    /* U0_TXD */
    LPC_SWM->PINASSIGN0 = 0xffffff04UL;
    /* SPI0_SCK */
    LPC_SWM->PINASSIGN3 = 0x01ffffffUL;
    /* SPI0_MOSI */
    /* SPI0_MISO */
    /* SPI0_SSEL */
    LPC_SWM->PINASSIGN4 = 0xff020003UL;

    /* Pin Assign 1 bit Configuration */
    /* RESET */
    LPC_SWM->PINENABLE0 = 0xffffffbfUL;
}



