#include <lpc214x.h>
#include "Timer.h"
 
 __irq void timer_isr(void) 
{
long int val ;
	//T0IR = 1;
	//IODIR0 = 0xF0;
	T0IR =1;
	IOSET0 = 0xF0;
	delay_ms(1);
	IOCLR0 = 0xF0;
	//T0IR= val;
	VICVectAddr = 0x00000;
}

void Timer_init() {
	
	//VICIntEnClr = 0x10;
	T0CTCR= 0;       // enable timer
	T0PR = 11999;
	T0MR0 = 1000;    // match every second
	T0EMR = 0x30;
	T0MCR = 0X3;	//Interrupt and reset on match
	T0TCR =1;
	/*
	VICVectAddr1 = (unsigned) timer_isr;
	VICVectCntl1 = 0x24;
						//start timer
	VICIntEnable = 0x10;
*/
	//T0TCR = 0X2;	
}

//#pragma section = ".irqisr"

void counter_init () {
 T1TCR =1;
	T1PR =0;
	T1CTCR = 0X2; 
	T1CCR= 0X2;
	}

	
void delay_ms(unsigned int del) {
  	
	del *= 10000;
	while (del -- >0);
	//T0TCR = 0X2;
//T0MCR = 0X2;	
//	while (T0TC < T0MR0);}
}


void interrupt_init() {
VICIntEnClr = 0x10;	
VICVectAddr0 = (unsigned) timer_isr;
VICVectCntl0 = 0x20|4;
VICIntEnable = 0x10;
	
}