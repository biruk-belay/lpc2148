#include <lpc214x.h>
#include "system_init.h"
#include "Uart_init.h"
#define NEW_LINE 0xA

int main () {
	unsigned char msg [] = "1234656"; // {'h','e','l','l','o', '\0'}; //"*****uarft tUTORIAL for the first time**** ";
  //VPBDIV = 0X1;
	system_init();     // initialize clock
	UART_init();      // initialize UART  
	send_text(msg);  // send string
  send ('h');     // send character

 while (1) {
	 			//char c = read();
				//send('c');
			//send(NEW_LINE);
		 send_text(msg);
send (' ');
send (' ');	 
			delay (10);
}}
