#include <lpc214x.h>
#define adc_DONE (1<<31)
#define adc_Burst_Mode_off (0<<16)
#define adc_Burst_Mode_on (1<<16)
#define adc_clk_div 11
#define adc_Start ((1<<24)|(0<<25)|(0<<26))
#define adc_Power_up (1<<21)
#define BIT(x) (1<<x)
#define adc_EDGE (1<<27)
#define adc_Start_pressed ((0<<24)| (1<<25) | (0<<26)) 

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
	PINSEL0 = 0X5; // select pin 1&2 as UART RX and TX
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
			
void adc_init(void){
AD0CR = 0X2 | (adc_clk_div <<8) | adc_Burst_Mode_off | adc_Power_up;

}

unsigned int * adc_read(void) {
	
unsigned int GD;
unsigned int data [2];
//AD0CR |= adc_Start;
	while ((AD0GDR & (1U<<31))==0);
		
		GD = AD0GDR;
		data [0] = (AD0GDR >>6) & 0x3FF;
		data[1] = (GD >>24) & 0x7;
  return data;
	
}
void adc_start (void) {

//AD0CR |= adc_Start;
}
  
	unsigned int	adc_read_single (void) {

			unsigned int data; 
      AD0CR |= adc_Start;
		//AD0CR |= adc_Start_pressed | adc_EDGE;
			
			while ((AD0GDR & (1U<<31))==0);
			data  = (AD0GDR >>6) & 0x3FF;
		DACR = (data << 6);	
		return data;
	
}

