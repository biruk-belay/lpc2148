#include <lpc214x.h>
#include "lib.h"
#include "printf.h"
#include "SD.h"
#include "spi.h"

char buffer [512];
void write_card(void);
void read_card(void);


 int main () {

		unsigned char ans;
		char option;
		UART_init();
		SPI_init();
	 
	 VPBDIV = 1;
//printf("inited spi");
	 
	 
	  if(SD_init())                                   //Try Card initialization in SPI mode
  {
   printf("Error initializing card\r\n");   //There was an error in initializing the card
  }

		else printf("card initialized \n");
	 
//		printf("please insert char");
	
	 
	 printf("please insert char \n");
	
	
	while (1) {

		
		printf(" press r for read and w for write \n");
		option = read();
		
		switch (option) {
			case 'r' | 'R':
						read_card();
								break;
			case 'w' | 'W' :
				write_card();
					break;
			
			default:
				printf ("wrong option do it again \n");
				break;
		}
	
				/*	 
		ans = read();
		if (read() == 0xD) {
	 switch (ans)
		
{		 case 'a':
			 printf(" \n wrote a ");
			break;
		case 'b':
			 printf(" \n wrote b");
				break;
		default :
			 printf(" \n what the hell did you write ");
	 }	 }
	
	//unsigned char array []= {'h','e','l'};
	//send('b');
	//send_text(array);
	//printf("  the number is %i ", 15);
//	delay (5);

	
	*/}
return 0;
}
 

/*



*/

void write_card(void)
{
  unsigned int LBA;   //logical block address on card
  unsigned char error;
  unsigned int i=0;

  //user prompt for data to write to SD card
printf ("Type something to write to card\r\n");
  printf(" Pressed 'Enter' when you're done:\r\n");

  do                              //accept user chars until enter is pressed
  {
     buffer[i] = read();
     printf("%c",buffer[i]);

     if(buffer[i] == 0xD)     //End of data (ascii of 'ENTER')
     {
        if(i < 512)           //if not the full buffer is used
        {
           for(; i<512; i++)  //fill the rest of the block with zeros (optional)
              buffer[i] = 0;

           break;              //break the do-while loop
        }
     }
  }
  while(i++ < 512);          //we accept max of 1 block (512 bytes)

printf ("  \r\n\r\n");   //new lines

  //user prompt for LBA (logical block address) to write to
 printf("please give block address(0-9): ");

  LBA = read();    //LBA is now in ASCII (we have to subtract 48 to make it decimal)
  send(LBA);
printf("  \r\n");   //new line

  error = SD_writeSingleBlock((LBA-48),buffer);  //write to card

  if(!error)
  {
     printf("data successfully written on card\r\n");
  }
  else
  {
   printf("There was error writing data on card\r\n");
  }
}



/*


*/


void read_card(void)
{
  unsigned int LBA;   //logical block address on card
  unsigned int i,j;
  unsigned char error;

  //user prompt for LBA (logical block address) to write to
 printf("please give block address(0-9): ");

  LBA =read();    //LBA is now in ASCII (we have to subtract 48 to make it decimal)
  send(LBA);
 printf("  \r\n\r\n");   //new lines

  error = SD_readSingleBlock((LBA-48), buffer);  //read the specified block (512 bytes)

  if(error)
  {
   printf ("There was error reading data\r\n");
     return;
  }

  j = 1;   //start printing on first line
  i = 0;

  //print the read data on terminal
  while((buffer[i] != 0) && (i < 512))
  {
     if(i > (60*j))         //60 characters per line
     {
        j++;                //incremment line count
       printf ("  \r\n");   //new line
     }

      send(buffer[i]);
     i++;
  }
 printf ("  \r\n");   //new line
}
