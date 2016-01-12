#include <lpc214x.h>

/********************************************************************************
	
												Function Definition
			
**********************************************************************************/


/********************************************************************

									Function for delay

********************************************************************/

void delay (int num) {
	num = num*100000;
 while (num>0)
		num--;
}

/*
	Initialize UART
*/

void UART_init() {
	PINSEL0 &= 0XFFFFFFF0;
	PINSEL0 |= 0X5; // select pin 1&2 as UART RX and TX
	U0LCR = 0x83;  // set DLAB, 8 bit, no parity and 1 stop bit
	U0DLL = 0x4E;  // Baud rate calculation 12Mhz Pclk
	U0DLM = 0;
		//U0TER=0;
	U0LCR =0X3;    // Clear DLAB 

}

/*****************************************************************************

					Function to read byte from receive buffer

*************************************************************************************/

unsigned char read () {
while (!(U0LSR & 0x01)); // wait while there is no data in U0RBR
		return (U0RBR);      // fetch while there is valid data in U0RBR   
}


/*
Function to write byte to receive buffer
*/

void send (unsigned char c) {
while (!(U0LSR & 0X20)); // wait while Transmit register is busy
 U0THR= c;
}


/*******************************************************************

						Function to write string to receive buffer

******************************************************************************/

void send_text (unsigned char msg[])
{
 while (*msg) {
 send (*msg);
	 msg++;
 }

}
