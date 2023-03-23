/*
 * File:   main.c
 * Author: Halim
 *
 *
 */


#include <xc.h>
#include "config.h"


void main(void) {
    //Set all the bits in port B as a OUTPUT
    TRISB = 0x00;
    
    //Set Initial state for port B pins to be LOW
    PORTB = 0x00;
    
    // [Configure The Timer module to Counter mode]
        // 1- Clear TMR1 Register
    TMR1 = 0x00;
        // 2- Select Clock Source 1 - > External PIN - > Counter mode
    TMR1CS = 1;
        // 3- Turn On synchronization bin
    T1SYNC = 0;
        // 4- Oscillator is enabled
    T1OSCEN = 1;
        //  Timer1 Input Clock Prescale Select bits
    T1CKPS1 = 0;
    T1CKPS0 = 0;
        //  Timer1 On bit
    TMR1ON = 1;
    
    while(1)
    {
        
        PORTB = TMR1;
    
    }
    
    return;
}
