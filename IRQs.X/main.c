/*
 * File:   main.c
 * Author: Halim
 *
 * 
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000


void main(void) {
    // set pin 0 in port B as an input
    TRISB0 = 1;
    // set the IRQ Edge
    INTEDG = 1;
    // Enable RB0 IRQ
    INTE = 1;
    GIE = 1;
    
    // set RC1 and RC2 to be Output pins
    TRISC1=0;
    TRISC2=0;
    
    // set RC1 and RC2 to be initial off
    RC1=0;
    RC2=0;
    
    while(1)
    {
        RC2 = ~RC2;
        __delay_us(10000);
       
    }
    
    
    
    return;
}
// Interrupt Handler
void __interrupt() ISR(void)
{
    if(INTF)
    {
        RC1=~RC1;
        INTF = 0;
    }
}