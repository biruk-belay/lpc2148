#include <lpc214x.h>

#define ASSERT (IO0CLR |=0x800)
#define DEASSERT_card (IO0SET |=0x800)

void write_single_char (short int block, unsigned char data);
unsigned char read_single_char(short int block) ;
void read_block (unsigned char * buffer, int size, short int block);
void read_card();
void write_card () ;
void write_block (unsigned char* buffer, short int block);