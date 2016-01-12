/*
	This is a low level implementation of the driver for 25AA040 eeprom from Michrochip
	it consists of functions to read and write memory blocks. The 512 bit memory is orgnaized into 
	8 16 byte pages. 
	
	Project by Biruk Belay.... SPI library provided by Daniel D. Dec 2015, University of Trento
	
*/



#include <lpc214x.h>
#include "lib.h"
#include "printf.h"
#include "spi.h"
#include "eeprom.h"


int main () {
	
	unsigned char opt;  // variable to store option 
	//system_init();   	// optional system initialization
	UART_init();				// initialize UART
	SPI_init();					// Initiliaze SPI
	
	ASSERT;							// Select Card									
	
	
	while(1) {
		
		int i =0;
		printf(" WELCOME TO THE EEPROM CONSOLE \n");
		printf("press R to read W to write \n");
		
		opt= read(); 				// Read from UART input
		send (opt);					// Display option on Terminal
		
		switch (opt) {
		
			case 'R' | 'r':

			read_card();
			printf ("\n");
	
			break;
			
			case 'W' | 'w':
	
			write_card();
			break;
		
			default :
			printf("Please enter the correct option \n");
			break;
		}}
		
return 0;
}
