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

    unsigned int cur_val;
    unsigned int max = 0;
    
    while (1) {
        // divided by 1.4 is just a calibration to reduce the sensitivity to light 
        //     so that the LED behavior becomes not that boring
        cur_val = ADC_getval() / 1.4;  // get brightness in digital
        
        // the maximum value should not exceed 80, otherwise it exceeds the range
        //     and it would take very long time for max to drop down
        if (cur_val > 80) {cur_val = 80;}  // 8 LEDs (decimal), so 80
        
        // return the display value to be the next max value
        max = LEDarray_disp_PPM(cur_val, max);
        __delay_ms(1000);
    }
}