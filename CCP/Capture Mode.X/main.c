/*
 * File:   main.c
 * Author: Halim
 *
 * Created on March 21, 2023, 1:32 AM
 */


#include <xc.h>
#include "config.h"


void main(void) {
    // Set port B and D to be Capture and Timer Output
    TRISB = 0x00;
    PORTB = 0x00;
    TRISD = 0x00;
    PORTD = 0x00;
    
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
    
    // Config CPP -> Capture mode
    CCP1M0 = 1;
    CCP1M1 = 0;
    CCP1M2 = 1;
    CCP1M3 = 0;
    
    // Enable CCP1 Interrupt
    CCP1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    
    while(1)
    {
        PORTD = TMR1;
        
    }
    return;
}
// interrupt handler
void __interrupt() ISR(void)
{
    if(CCP1IF)
    {
        PORTB = CCPR1;
        CCP1IF=0;
    }
    
}