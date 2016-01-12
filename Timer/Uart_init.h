#include <lpc214x.h>
#include "system_init.h"

void UART_init();
unsigned char read ();
void send (unsigned char c);
void send_text (unsigned char msg[]);