#include <lpc214x.h>
#include "system_init.h"
#include "Uart_init.h"
#include "adc.h"

int main () {
	unsigned int num;
	//unsigned char msg []  = "hello";
	system_init();
	UART_init();
	adc_init(); 
	PINSEL1 = 0X1000000;
//	adc_start();

	while (1)
	{
	  num = adc_read();
		send_text ((unsigned char*) &num);
		//send('c');
	
		delay (5);
		send(0xD);
		//send (0xA);
	}


}