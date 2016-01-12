#include <lpc214x.h>
#include "system_init.h"

			
void system_init(void) {
PLL0CFG = 0X23;	
PLL0FEED = 0XAA;
PLL0FEED = 0X55;
	
PLL0CON = 0X1;
PLL0FEED = 0XAA;
PLL0FEED = 0X55;

while (!(PLL0STAT & 0X400));
	
PLL0CON =0X3;
PLL0FEED = 0XAA;
PLL0FEED = 0X55;

}
			
