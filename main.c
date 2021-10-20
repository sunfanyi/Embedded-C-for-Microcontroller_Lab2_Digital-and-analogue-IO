#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"
#include "ADC.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
	unsigned int count = 0;
    LEDarray_init();
    btnInput_init();
    ADC_init();

    unsigned int cur_val = ADC_getval();  // get brightness in digital
    unsigned int max;
    unsigned int tempval;
    int i;
    LEDarray_disp_bin(cur_val);
    
    while (1) {
        cur_val = 0;  // reset the next peak value
        for (i=0;i<1000;i++) {  // get the highest value within 1 sec
            tempval = ADC_getval();
            if (tempval > cur_val) {cur_val = tempval;}
            __delay_ms(1);
        }
        max = LEDarray_disp_PPM(cur_val, max);  // return the display value
    }
}