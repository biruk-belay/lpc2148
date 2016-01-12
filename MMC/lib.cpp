#include <lpc214x.h>




/*-------------------------------------------------------------------------------------------
Function Name: delay

Parameters: None

Return: None

Description: A simple delay function

---------------------------------------------------------------------------------------------*/

void delay (int num) {
	num = num*10000;
 while (num>0)
		num--;
}



/*-------------------------------------------------------------------------------------------
Function Name: UART_init

Parameters: None

Return: None

Description: This function sets the GPIO pins as UART and sets the baud rate

---------------------------------------------------------------------------------------------*/

void UART_init() {
	PINSEL0 |= 0X5; // select pin 1&2 as UART RX and TX
	U0LCR = 0x83;  // set DLAB, 8 bit, no parity and 1 stop bit
	U0DLL = 0x4E;  // Baud rate calculation 12Mhz Pclk
	U0DLM = 0;
		//U0TER=0;
	U0LCR =0X3;    // Clear DLAB 

}




/*-------------------------------------------------------------------------------------------
Function Name: read

Parameters: None

Return: None

Description: This function reads a character from the UART RX line 

---------------------------------------------------------------------------------------------*/

unsigned char read () {
while (!(U0LSR & 0x01)); // wait while there is no data in U0RBR
		return (U0RBR);      // fetch while there is valid data in U0RBR   
}






/*-------------------------------------------------------------------------------------------
Function Name: send

Parameters: unsigned character

Return: None

Description: This function writes a character to the UART TX line

---------------------------------------------------------------------------------------------*/

void send (unsigned char c) {
while (!(U0LSR & 0X20)); // wait while Transmit register is busy
 U0THR= c;
}





/*-------------------------------------------------------------------------------------------
Function Name: send_text

Parameters: Unsigned char []

Return: None

Description:  This function writes a string to the UART TX line

---------------------------------------------------------------------------------------------*/

void send_text (unsigned char msg[])
{
 while (*msg) {
 send (*msg);
	 msg++;
 }

}
/*-------------------------------------------------------------------------------------------
Function Name: system_init

Parameters: None

Return: None

Description: This function initializes PLL with the correct clock 

---------------------------------------------------------------------------------------------*/

void system_init(void) {
PLL0CFG = 0X23;	
PLL0FEED = 0XAA;
PLL0FEED = 0X55;
	
PLL0CON = 0X1;
PLL0FEED = 0XAA;
PLL0FEED = 0X55;

while (!(PLL0STAT & 0X400));
	
PLL0CON =0X3;
PLL0FEED = 0XAA;
PLL0FEED = 0X55;


}
