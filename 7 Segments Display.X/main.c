/*
 * File:   main.c
 * Author: Halim
 *
 * Created on March 18, 2023, 8:57 AM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ  4000000


void main(void) {
    
    unsigned char counter = 0; // To access seg array
    
    // Define a table of values to display 0-9 on the 7-segment display
    unsigned char seg_digits[] = {
        0b11111100, // 0xFX (0)
        0b01100000, // 0x60 (1)
        0b11011010, // 0xDA (2)
        0b11110010, // 0xF2 (3)
        0b01100110, // 0x66 (4)
        0b10110110, // 0xB6 (5)
        0b10111110, // 0xBE (6)
        0b11100000, // 0xE0 (7)
        0b11111110, // 0xFE (8)
        0b11110110  // 0xF6 (9)
    };
   
    // Set the TRIS values for the 7-segment display pins as outputs
    TRISB = 0x00;     //    TRISB0 = 0; TRISB1 = 0; TRISB2 = 0;  etc
    
    // Initial state for PORTB (low)
    PORTB = 0x00;
    
    // main routine
    while (1) {
          
        PORTB = seg_digits[counter];
        
        // Delay for a short period of time
        __delay_ms(1000);
        
        // Go to next the element of array
        counter++;
        
        // Back to 0
        if(counter == 10)
            counter = 0;
    
       
    }
    return;
}
