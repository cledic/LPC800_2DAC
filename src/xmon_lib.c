/* mbed XMON library.

    XMON Micro controller serial port debugger variable view realtime curve tracer
    http://webx.dk/XMON/index.htm

    XMON is a windows program that show and plot value received fomr the serial port.
    This is the banner from the XMON documentation:
    // XMON 2.1 ALPHA (autoscaling on/off/min/max) 15 feb 2008
    // XMON is a free utility for monitoring and communication with MCU development
    // Made by DZL (help ideas support testing TST)
    // if this program help you and you are happy to use it, please donate a fee to thomas@webx.dk via paypal
    // any donation will be put into improving XMON, any size of donation small or big will be most appliciated.
    // suggestions and bugs to thomas@webx.dk
    // we will setup a homepage with features and tips and tricks and so on soon, see webx.dk and dzl.dk

*/
#include "xmon_lib.h"
#include "uart.h"

/**
 */
void XMon_Init( void)
{
	uartInit( UART_SPEED);
}


/** Clear and restart x axis for the specified trace
 *
 * @param trace trace value
 */
void XMon_plotZero( unsigned int trace)
{               // value is the plot trace you want to zero on XMON
	xmon_putc('*');
	xmon_putc('T');  // re Trigger 'T', clear all traces and restart X axis scaling 'C'
	xmon_putc( (unsigned char)trace);
}

/** Plot float data
 *
 * @param data float value to plot.
 * @param trace color graph
 */
void XMon_plotf( float data, unsigned int trace)
{
    xmon_putc('*');
    xmon_putc('d');
    xmon_putc(((char*)&data)[3]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[2]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[1]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[0]);
    xmon_putc('F'); // here is the data handler selector indicator to XMON
    xmon_putc( (unsigned char)trace);
}

/** View float data
 *
 * @param data float value to view.
 * @param line line label
 */
void XMon_viewf( float data, unsigned int trace)
{
    xmon_putc('*');
    xmon_putc('d');
    xmon_putc(((char*)&data)[3]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[2]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[1]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[0]);
    xmon_putc('f');// here is the data handler selector indicator to XMON
    xmon_putc( (unsigned char)trace);
}

/** Plot signed 32 bits data
 *
 * @param data signed 32bit value to plot.
 * @param trace color graph
 */
void XMon_plotl( int data,unsigned int trace)
{
    xmon_putc('*');
    xmon_putc('d');
    xmon_putc(((char*)&data)[3]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[2]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[1]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[0]);
    xmon_putc('I');                    // here is the data handler selector indicator to XMON
    xmon_putc( (unsigned char)trace);
}

/** View signed 32 bits data
 *
 * @param data unsigned short value to view.
 * @param line line label
 */
void XMon_viewl( int data, unsigned int trace)
{
    xmon_putc('*');
    xmon_putc('d');
    xmon_putc(((char*)&data)[3]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[2]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[1]);
    xmon_putc('D');
    xmon_putc(((char*)&data)[0]);
    xmon_putc('i');                        // here is the data handler selector indicator to XMON
    xmon_putc( (unsigned char)trace);
}


/** Plot unsigned 16 bits data
 *
 * @param data unsigned short value to plot.
 * @param trace color graph
 */
void XMon_plot( unsigned short data, unsigned int trace)
{
	xmon_putc('*');
	xmon_putc('d');
	xmon_putc( (unsigned char)(data>>8));
	xmon_putc('D');
	xmon_putc( (unsigned char)data);
	xmon_putc('P');                    // here is the data handler selector indicator to XMON
	xmon_putc( (unsigned char)trace);
}

/** View unsigned 16 bits data
 *
 * @param data unsigned short value to view.
 * @param line line label
 */
void XMon_view( unsigned short data, unsigned int line) // Unsigned Integers 16 bits values in the VIEW variable value area
{
  xmon_putc('*');
  xmon_putc('d');
  xmon_putc( (unsigned char)(data>>8));
  xmon_putc('D');
  xmon_putc( (unsigned char)data);
  xmon_putc('V');// here is the data handler selector indicator to XMON
  xmon_putc( (unsigned char)line);
}

/** Put the PLOT GRAPH in auto scale mode
 *
 * @param s 0 auto scale OFF, 1 auto scale ON
 */
void XMon_autoscale( char s) //
{
   xmon_putc('*');
   xmon_putc('A');
   xmon_putc(s);
}

