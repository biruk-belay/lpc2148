#include <lpc214x.h>
#include "lib.h" 
#include "printf.h"
/*#include "uart.h" 
#include "adc.h"
#include "system.h"
*/

int main (void) {
	unsigned int num;
	unsigned int * data_out;
	//unsigned char msg []  = "hello";
	system_init();
	UART_init();
	adc_init(); 
	PINSEL1 = 0X1000000;
	PINSEL1 |= ((1<<19) | (0<<18));
	//	adc_start();

	while (1)
	{
	  //data_out = adc_read();
		num= adc_read_single();
		
		printf("the number is %i ", num);
		//printf("the number is %i volts  from ADC %i ", data_out[0], data_out[1]);
	
		//delay (1);
		send(0xD);
		send (0xA);
	}

return 0;
}