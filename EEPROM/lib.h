#include <lpc214x.h>

void system_init(void);
unsigned int * adc_read(void);
unsigned int adc_read_single(void);
void adc_start (void);
void adc_init(void);
void delay(int num);
void delay (int num);
void UART_init();
unsigned char read ();
void send (unsigned char c);
void send_text (unsigned char msg[]);
