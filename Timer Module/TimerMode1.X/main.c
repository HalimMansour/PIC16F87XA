/*
 * File:   main.c
 * Author: Halim
 *
 * 
 */


#include <xc.h>
#include "config.h"


unsigned char counter = 0;

void main() {
    
    // Configure RB0 as output for LED
    TRISB0 = 0;
    // Set initial of RB0 to be OFF (LED Off)
    RB0 = 0;
    // Enable Timer 1 interrupt
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    //Start Counting  
    TMR1= 15536;
    
    // Select Timer mode (timer)
    TMR1CS = 0;
    
    // Prescaler (0,0) = 1
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    
    // Turn on Timer Module
    TMR1ON=1;
    
    while(1)
    {
        
    }
    
    
    return;
}

// Interrupt Handler
void __interrupt() ISR(void)
{
    if(TMR1IF)
    {
        TMR1= 15536;
        counter++;
        if(counter==20)
        {
            RB0= ~RB0;
            counter=0;
        }
        TMR1IF = 0;
    }
    
}
