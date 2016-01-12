#include <lpc214x.h>
#include "system_init.h"

#define BIT(x) (1<<x)

//void system_init(void);
void delay (int num);
void UART_init();
unsigned char read ();
void send (unsigned char c);
void send_text (unsigned char msg[]);


/*
=======================================================================================================
Function: delay ()
Description: simple function to create delay between tasks

========================================================================================================
*/

void delay (int num) {
	num = num*100000;
 while (num>0)
		num--;
}

/*
=======================================================================================================

Function: UART_init ()
Description: initialize Uart

========================================================================================================
*/

void UART_init() {
	PINSEL0 = 0X5; // select pin 1&2 as UART RX and TX
	U0LCR = 0x83;  // set DLAB, 8 bit, no parity and 1 stop bit
	U0DLL = 0x4E;  // Baud rate calculation 15Mhz Pclk
	U0DLM = 0;
		//U0TER=0;
	U0LCR =0X3;    // Clear DLAB 

}

/*
=======================================================================================================
Function: read ()
Description: reads a byte from the receive buffer

========================================================================================================
*/

unsigned char read () {
while (!(U0LSR & 0x01)); // wait while there is no data in U0RBR
		return (U0RBR);      // fetch while there is valid data in U0RBR   
}


/*
=======================================================================================================
Function: send ()
Description: writes a byte to transmit buffer

========================================================================================================
*/

void send (unsigned char c) {
while (!(U0LSR & 0X20)); // wait while Transmit register is busy
 U0THR= c;
}

/*
=======================================================================================================
Function: send_text ()
Description: writes a string to transmit buffer

========================================================================================================
*/

void send_text (unsigned char msg[])
{
 while (*msg) {
 send (*msg);
	 msg++;
 }

}

