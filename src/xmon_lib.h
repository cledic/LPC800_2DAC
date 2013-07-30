/* mbed XMON library.
*
*    XMON Micro controller serial port debugger variable view realtime curve tracer
*    http://webx.dk/XMON/index.htm
*
*    XMON is a windows program that show and plot value received fomr the serial port.
*    This is the banner from the XMON documentation:
*    // XMON 2.1 ALPHA (autoscaling on/off/min/max) 15 feb 2008
*    // XMON is a free utility for monitoring and communication with MCU development
*    // Made by DZL (help ideas support testing TST)
*    // if this program help you and you are happy to use it, please donate a fee to thomas@webx.dk via paypal
*    // any donation will be put into improving XMON, any size of donation small or big will be most appliciated.
*    // suggestions and bugs to thomas@webx.dk
*    // we will setup a homepage with features and tips and tricks and so on soon, see webx.dk and dzl.dk
*
*/

#ifndef __LPC800_XMONLIB_H
#define __LPC800_XMONLIB_H

#define UART0 	1
#define UART_SPEED	115200

#ifdef UART0
#define xmon_putc		uart0SendChar
#define uartInit	uart0Init
#else
#define putc
#define uartInit
#endif

#define XMON_AUTO_SCALE_OFF 0
#define XMON_AUTO_SCALE_ON 1
#define XMON_RED 0          // Colors of the PLOT GRAPHS
#define XMON_GREEN 1
#define XMON_BLUE 2
#define XMON_YELLOW 3

/**
 */
void XMon_Init( void);


/** Clear and restart x axis for the specified trace
 *
 * @param trace trace value
 */
void XMon_plotZero( unsigned int trace);


/** Plot float data
 *
 * @param data float value to plot.
 * @param trace color graph
 */
void XMon_plotf( float data, unsigned int trace);

/** View float data
 *
 * @param data float value to view.
 * @param line line label
 */
void XMon_viewf( float data, unsigned int trace);

/** Plot signed 32 bits data
 *
 * @param data signed 32bit value to plot.
 * @param trace color graph
 */
void XMon_plotl( int data,unsigned int trace);

/** View signed 32 bits data
 *
 * @param data unsigned short value to view.
 * @param line line label
 */
void XMon_viewl( int data, unsigned int trace);

/** Plot unsigned 16 bits data
 *
 * @param data unsigned short value to plot.
 * @param trace color graph
 */
void XMon_plot( unsigned short data, unsigned int trace);

/** View unsigned 16 bits data
 *
 * @param data unsigned short value to view.
 * @param line line label
 */
void XMon_view( unsigned short data, unsigned int line);

/** Put the PLOT GRAPH in auto scale mode
 *
 * @param s 0 auto scale OFF, 1 auto scale ON
 */
void XMon_autoscale( char s);

#endif
