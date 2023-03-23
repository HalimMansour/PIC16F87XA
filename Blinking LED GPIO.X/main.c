/*
 * File:   main.c
 * Author: Halim
 *
 * Created on March 18, 2023, 3:00 AM
 */

#include "config.h"
#include <xc.h>
#define _XTAL_FREQ  4000000


void main() {
    // Set the RB0 pin as output and RB1 pin as input
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 1;
    
    // Initialize the LED to be off
    PORTBbits.RB0 = 0;
    
    while (1) {
        // Check if the button is pressed
        if ( PORTBbits.RB1 == 1) {
            // Turn the LED on
             PORTBbits.RB0 = 1;
            
            // Wait for a short period of time
            __delay_ms(500);
            
            // Turn the LED off
             PORTBbits.RB0 = 0;
            
            // Wait for another short period of time
            __delay_ms(500);
        }
    }
}
