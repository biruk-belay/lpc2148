#include <lpc214x.h>
#include "spi.h"
#include "eeprom.h"
#include "lib.h"
#include "printf.h"

unsigned char buffer [16]; // a 16 character buffer to write and read from card

/*-------------------------------------------------------------------------------------------
Function Name: write_single_char

Parameters: Block number & character data

Return: None

Description: This function writes a character data on a respective block number (address on the eeprom)

---------------------------------------------------------------------------------------------*/

void write_single_char (short int block, unsigned char data) {

	unsigned char temp;
	ASSERT;
	delay(1);
	
	SPI_write(0x06); // Write the Wren to initialize the writing 
	
	DEASSERT_card;   // Deselect the card for the wren latch to settle
	delay(1);
	
	temp = (((block & 0x0100)>>5)|0x2); // Insert MSB of the block address inside the WRITE command
	
	ASSERT;															// Select card
	delay(1);
	
	SPI_write(temp);										// latch first part of the addres and the read command
	temp =0;
	temp = block & 0xFF;								
	SPI_write(temp);										// latch the last 8 bits of the address to be written 
	SPI_write(data);										// latch the character (data)
	
	DEASSERT_card;											// Deselect the card for actual writing on the memory array
	delay(1);
}

/*-------------------------------------------------------------------------------------------
Function Name: read_single_char

Parameters: Block number

Return: unsigned character

Description: This function reads a single character from the requested block number in the parameter(address on the eeprom)

---------------------------------------------------------------------------------------------*/


unsigned char read_single_char(short int block) {

	unsigned char temp, response; 
	unsigned int retry =0;
	
	ASSERT;															// Select card
	delay(1);
	
	temp = (((block & 0x0100)>>5)|0x3); // Insert MSB of the block address inside the READ command
	SPI_write(temp);										// Latch the first command
	temp = block & 0xFF;
	SPI_write(temp);										// Latch the 8 bits of the address
	

	// Wait while no feedback from the eeprom
	
	while(((response = SPI_read()) == 0xFF) && (retry++ < 0x0fffffff));
	
	return response; // response contains the character read
	
	DEASSERT_card; 		// Deselect card to protect the chip reading to the next memory location
	//delay(1);
}






/*-------------------------------------------------------------------------------------------
Function Name: read_block

Parameters: character Buffer, Block number & size of buffer 

Return: None

Description: This function is to read a page the size of Size variable. The address of the first
memory location is supplied as an argument and the eeprom automatically increments the address at the 
end of each character read

---------------------------------------------------------------------------------------------*/


void read_block (unsigned char * buffer, int size, short int block) {

unsigned char temp, response;

	unsigned int retry =0;
	int i;
	ASSERT;								// Select card
	delay(1);
	
	temp = (((block & 0x0100)>>5)|0x3); // Insert MSB of the address inside the READ command
	
	SPI_write(temp);										// Latch the Read command
	temp = block & 0xFF;								// Extract the last 8 bits of the address
	SPI_write(temp);										// Latch the last 8 bits of the address
	
	
	// Wait while no data is latched on the MISO
	
	while(((response = SPI_read()) == 0xFF) && (retry++ < 0x0fffffff));
	
	buffer[0] = response;								
	
	for (i =1; i<size; i++)
	buffer[i] = SPI_read();									// Read characters as the eeprom keeps latching from subsequent memory locations

DEASSERT_card;														// Deselect card
}







/*-------------------------------------------------------------------------------------------
Function Name: write_card

Parameters: None

Return: None

Description: This function writes a page of the eeprom memory (16 bytes) using the function write_block
It also prompts the user to enter a 16 byte string and the start memory block to write the data
--------------------------------------------------------------------------------------------------*/

void write_card () 

{
			int i =0;
			unsigned char opt, data;
			printf (" \n Enter the text \n");	
	
	// Enter the 16 byte text... If entry less than 16 bytes 0's are appended to buffer
	
	do {	
			buffer[i]= read();
	 if(buffer[i] == 0xD)
	 {	
		 if(i<16)
			 for (;i<16;i++)
			buffer[i]=0;
	 break;
	 }	printf("%c", buffer[i]);
				} while (++i<16);

			printf ("\n Enter the block number \n");  // Prompt for the first block number to store string
				
			opt =read();
			send (opt);
			
			write_block (buffer, (short int) (opt-48) * 16); // call to function write_block to actually write the data 
			DEASSERT_card;
			
}




/*-------------------------------------------------------------------------------------------
Function Name: read_card

Parameters: None

Return: None

Description: This function prompts user for a block number and starts starts reading using read_block function

---------------------------------------------------------------------------------------------*/


void read_card() {
	unsigned char opt;
	int i;
printf ("Enter the block number \n");
			opt= read();
			send(opt);
			
	read_block (buffer, 16,(short int)(opt-48)*16);
		
	
	printf(" \n%s", buffer);
	
	DEASSERT_card;
			
}





/*-------------------------------------------------------------------------------------------
Function Name: write_block

Parameters: Character buffer & start block 

Return: None

Description: This function writes a page (16 bytes) from the start of the block parameter. The eeprom allows only to write 16 consecutive 
bytes. 16 byte -> 1 block memory abstraction is used. The start address of the each block is a multiple of 16
if different the write will not be successful.
---------------------------------------------------------------------------------------------*/


void write_block (unsigned char* buffer, short int block) {

	unsigned char temp;
	int i;
	ASSERT;
	delay(1);
	
	SPI_write(0x06); // wren
	
	DEASSERT_card;
	
	delay(1);
	temp = (((block & 0x0100)>>5)|0x2); // insert msb address inside the write command
	ASSERT;
	
	delay(1);
	SPI_write(temp);
	
	temp =0;
	temp = block & 0xFF;
		
	SPI_write(temp);	
	for (i=0; i<16; i++)
		SPI_write(buffer[i]);
	
	DEASSERT_card;	
			printf(" \n Data successfully written \n");
		delay(1);
	
	/*
	printf (" \n Page is less than 16  bytes \n ");
	printf(" \n Data Not Written \n \n");
		*/
		return;
	}

