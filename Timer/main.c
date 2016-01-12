#include <lpc214x.h>
#include "system_init.h"
#include "Timer.h"



int main () {
	//unsigned int temp =0;
system_init();
interrupt_init();
	Timer_init();
	
//	counter_init();
//UART_init();
	PINSEL0 = 0X80;//0000;
//IODIR0 = 0XFFFFFFFF;	
//IODIR0 |= 0X8;
IODIR0 = 0xF0;

	while (1) {
		
		//IOPIN0 = ~IOPIN0;
	/*
		IOSET0 = 0X10;
		
		delay_ms(1);
		IOCLR0 = 0x10;
		delay_ms(1);
		*/
		//toggle();
	}
}
