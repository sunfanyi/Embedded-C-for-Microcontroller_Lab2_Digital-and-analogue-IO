#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
	unsigned int count = 0b00000111;
    char *direction = 'left';
    LEDarray_init();
  
    while (1) {
        if (direction == 'left') {
            count <<= 1;
        }else if (direction == 'right') {
            count >>= 1;
        }
        
		if (count>0b1110000000) {
            // from 1-on to 2-on instead of 1-on jump to 3-on
            count = 0b11000000;
            // intermediate, to make the process smoother
            LEDarray_disp_bin(count);
            __delay_ms(50);
            
            count = 0b11100000; // reset a when it gets too big
            direction = 'right'; // reverse direction
        }
		if (count<1) {
            count = 0b00000011;
            LEDarray_disp_bin(count);
            __delay_ms(50);
            count = 0b00000111; // reset a when it gets too small
            direction = 'left'; // reverse direction
        }
		LEDarray_disp_bin(count); //output a on the LED array in binary
		__delay_ms(50); // Delay so human eye can see change
    }
}
