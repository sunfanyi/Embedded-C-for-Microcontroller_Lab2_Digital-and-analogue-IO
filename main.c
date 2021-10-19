#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "LEDarray.h"

#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void) 
{
	unsigned int count = 0;
    LEDarray_init();
    btnInput_init();
  
    while (1) {
        
        if (PORTFbits.RF2 == 0) {
            count++;
            // stop incrementing when the button is held down
            while (!PORTFbits.RF2);
        }
        
		LEDarray_disp_bin(count); //output a on the LED array in binary
		__delay_ms(50);
    }
}
