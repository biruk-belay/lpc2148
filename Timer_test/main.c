#include<lpc21xx.h>


void delay10ms(unsigned char);
void __irq timer0(void);
void timersetup(void);
void toggle();

int main()
{
        PINSEL0 = 0x00000000;
        PINSEL1 = 0x00000000;
        IODIR0 = 0x01;
        IOSET0=0x01;
        timersetup();



        while(1)
        {
           VICSoftInt = 0x00000010;
          //IOPIN0^=0x01;
           delay10ms(80);
					//toggle();
				}

}

void delay10ms(unsigned char val)
{
unsigned int j;
unsigned char i;
for(;val>=1;val--)
{
for(j=0;j<1623;j++)
for(i=10;i>=1;i--);
}
}

void timersetup(void)
{
				VICIntEnClr = 0xFFFFFFFF; 
        VICIntSelect=0x00000000;
        VICVectCntl0=0x24;
        VICVectAddr0=(unsigned)timer0;
        //VICDefVectAddr = (unsigned) timer0;
				VICIntEnable=(1<<4);
				
        /*
        VPBDIV=0x01;
        T0PR=0x00;
        T0MR0=0x00000FFF;
        T0MCR= 0x03;
        T0TCR = 0x01;
         */

        }

__irq void timer0(void)
{
				 VICSoftIntClr=(1<<4);
       IOPIN0^=0x01;
        VICVectAddr=0xFFFFF;
//      T0IR=0x01;
}

void toggle () {
IOPIN0^=0x01;
delay10ms(80);
}