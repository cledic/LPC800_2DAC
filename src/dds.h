#ifndef __DDS_H
#define __DDS_H

#define cLUT_SIZE   256                         // Size of the Lookup Table (LUT)

#define c0_DEGREE            0
#define c90_DEGREE           (cLUT_SIZE/4)
#define c180_DEGREE          (cLUT_SIZE/2)

#define cDDS_INITFREQ        500        // Default freq. if not specified.
#define cDDS_LOWFREQ         100        // Lower freq. configurable.

#define cDDS_SAMPLINGRATE   22100      // Sampling Freq

//extern unsigned int accum;
//extern unsigned int freq;
//extern unsigned short sine_table[];
//extern unsigned int dds_counter;
//
void ddsInit( unsigned int ddsfreq);
unsigned int dds_setFreq( unsigned int freq);
unsigned short dds_sample( void);
//Int32U init_ddstimer ( Int32U TimerInterval ) ;


#endif
