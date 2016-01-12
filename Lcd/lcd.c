#include "lpc214x.h"
#define BIT(x)  (1<<x)

/*
====================================================================================================================

Function: delay
Description: function to instantiate delay between tasks 

====================================================================================================================
*/

void delay (int num) {
	num = num*10000;
 while (num>0)
		num--;
}


/*
====================================================================================================================

Function: enable
Description: toggles the pin connected to the enable pin of the lcd since actual transfer of data takes place on the 
falling edge of the enable signal

====================================================================================================================
*/

void enable () {

	IO0SET = BIT(9);	
	delay(1);
	
	IO0CLR = BIT(9);
	delay (1);
	}

/*
====================================================================================================================

Function: lcd_cmd
Description: writes commands on the lcd controller register. The lcd controller has to be set to command mode 

====================================================================================================================
*/

	
void lcd_cmd (unsigned char cmd) {

	IO0CLR = BIT(8); // set command mode
	delay(1);
	
	IO0PIN &= 0XFFFFFF00; // mask all bits except the last byte i.e the first 8 pins of the MCU
	IO0PIN |= cmd ;				// Transfer command to lcd register
	delay(1);
	enable();							// toggle enable pin to tranmit the command
	

}

/*
====================================================================================================================

Function: lcd_data
Description: takes a character and writes it on the lcd 8 bit register. The lcd controller has to be set to data mode 

====================================================================================================================
*/


	void lcd_data (unsigned char data) {
	
		IO0SET = BIT(8); // set data mode 
		delay(1);
		
		IO0PIN &= 0XFFFFFF00; // mask all bits except the last 8 bits 
		IO0PIN |=  data ;     // load data on IOPIN hence the data register of the lcd
		delay (1);
		enable(); 						// toggle the enable pin to load data on lcd register
		
	}

	
/*
===============================================================================================================	
	Function: lcd_init()
	Description: initialize lcd in 8 bit mode, 5*7 dot format, increment mode and blink and underscore of cursor
	
==========================================================================================================	
*/
	
	void lcd_init(void)

{
	IO0DIR = 0XFFFFFFFF;
	lcd_cmd(0x01); // clear display
	lcd_cmd(0x38); // 8 bits, 2 line mode, 5*7 dot format
	lcd_cmd(0x08); // display off, underline off, blink off
	lcd_cmd(0x06); // increment cursor
	lcd_cmd(0x0F); // display on, underline on, blink on
	
}

/*
=========================================================================================================

Function: lcd_write
Description: writes a string to the lcd using lcd_data ()

==============================================================================================================
*/
void lcd_write (char * ptr) {
	
		while (*ptr !='\0')
		{
			lcd_data(*ptr);
			ptr++;
}}



/*
=========================================================================================================
Function: lcd_goto(int, int)
Description: takes x and y coordinate on the screen as parameter and navigates cursor to that point

=========================================================================================================
*/


void lcd_goto(int x, int y) {
	int addr;
	if ((x>16) || (y>2)) return;
	 
	if (y==1) addr =0x80;
	
	else addr =0xC0;

		lcd_cmd(addr+x);

}

/*
=========================================================================================================
Function: init_4bit()
Description: The lcd starts off in 8 bit mode and only the last 4 data pins are connected. the first command to be sent 
should drive the lcd into 4 bit mode after. After this data is transferred in 4 bit mode (the most significant nibble first)
=========================================================================================================
*/


void init_4bit() {

	IO0DIR = 0XFFFFFFFF; // set all pins as output 
	IO0CLR = BIT(8);		// Command mode
	delay(1);
	
	IO0PIN &= 0XFFFFFF00; // Mask all bits but the last byte on the MCU
	IO0PIN |= 0X20; 			// 4 bit mode command 
	
	delay(1);
	enable();							// enable the transfer of the command

}