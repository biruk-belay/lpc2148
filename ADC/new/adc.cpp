#include <lpc214x.h>

#define adc_DONE (1<<31)
#define adc_Burst_Mode_off (0<<16)
#define adc_clk_div 11
#define adc_Start ((1<<24)|(0<<25)|(0<<26))
#define adc_Power_up (1<<21)
#define BIT(x) (1<<x)

void adc_init(void){
AD0CR = 0X2 | (adc_clk_div <<8) | adc_Burst_Mode_off | adc_Power_up;
}

unsigned int adc_read(void) {

unsigned int data;
AD0CR |= adc_Start;
	while ((AD0GDR & (1U<<31))==0);
	
		data = (AD0GDR >>6) & 0x3FF;
	  return data;
	}
void adc_start (void) {


}

