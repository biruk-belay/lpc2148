#include <lpc214x.h>
#include "lcd.h"


int main () {

	//init_4bit();
	lcd_init(); // start the lcd controller with the proper setting
	//lcd_data(0x41);
	//lcd_write("hello");
	while (1) {
		//lcd_cmd(0x1);
		//delay(1);
	  //lcd_goto(6,2);
		//lcd_data(0x41);
	}

}