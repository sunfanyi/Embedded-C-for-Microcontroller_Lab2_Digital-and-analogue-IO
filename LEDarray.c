#include <xc.h>
#include <math.h>
#include "LEDarray.h"

/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers for pins connected to LED array
    TRISGbits.TRISG0 = 0;
    TRISGbits.TRISG1 = 0;
    TRISAbits.TRISA2 = 0;
    TRISFbits.TRISF6 = 0;
    TRISAbits.TRISA4 = 0;
    TRISAbits.TRISA5 = 0;
    TRISFbits.TRISF0 = 0;
    TRISBbits.TRISB0 = 0;
    
	//set initial output LAT values (they may have random values when powered on)
    // (rand() % 3) - 1  // random value (0 or 1)
    LATGbits.LATG0 = 0;  
    LATGbits.LATG1 = 0;
    LATAbits.LATA2 = 0;
    LATFbits.LATF6 = 0;
    LATAbits.LATA4 = 0;
    LATAbits.LATA5 = 0;
    LATFbits.LATF0 = 0;
    LATBbits.LATB0 = 0;
}

/************************************
/ LEDarray_init
/ Function used to initialise input from the button
************************************/
void btnInput_init(void)
{
    //set up TRIS registers for input from the button
    TRISFbits.TRISF2 = 1;
    //turn off analogue input
    ANSELFbits.ANSELF2 = 0;
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
	//some code to turn on/off the pins connected to the LED array
	//if statements and bit masks can be used to determine if a particular pin should be on/off
    if (number & 0b00000001) {LATGbits.LATG0 = 1;} else {LATGbits.LATG0 = 0;}
    if (number & 0b00000010) {LATGbits.LATG1 = 1;} else {LATGbits.LATG1 = 0;}
    if (number & 0b00000100) {LATAbits.LATA2 = 1;} else {LATAbits.LATA2 = 0;}
    if (number & 0b00001000) {LATFbits.LATF6 = 1;} else {LATFbits.LATF6 = 0;}
    if (number & 0b00010000) {LATAbits.LATA4 = 1;} else {LATAbits.LATA4 = 0;}
    if (number & 0b00100000) {LATAbits.LATA5 = 1;} else {LATAbits.LATA5 = 0;}
    if (number & 0b01000000) {LATFbits.LATF0 = 1;} else {LATFbits.LATF0 = 0;}
    if (number & 0b10000000) {LATBbits.LATB0 = 1;} else {LATBbits.LATB0 = 0;}
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{
	unsigned int disp_val;
	disp_val = pow(2, number/10) - 1;
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array

	LEDarray_disp_bin(disp_val); 	//display value on LED array
}


/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
unsigned int LEDarray_disp_PPM(unsigned int cur_val, unsigned int max)
{
	unsigned int disp_val;
	
	// some code to format the variable cur_val and max, store in disp_val for display on the LED array
	// hint: one method is to manipulate the variables separately and then combine them using the bitwise OR operator
    if (cur_val > max) {disp_val = cur_val;} else {disp_val = --max;}
	LEDarray_disp_bin(disp_val);	//display value on LED array
    return disp_val;  // return the display value
}