#include <lpc214x.h>

void delay (int num);
void UART_init();
unsigned char read ();
void send (unsigned char c);
void send_text (unsigned char msg[]);
