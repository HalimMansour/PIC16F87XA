/*
 * File:   main.c
 * Author: Halim
 *
 * 
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000

float distance(void)
{
    // The Distance variable
    float d = 0;
    // reset timer 1 
    TMR1=0;
    // trigger pulse
    RC2=1;
    __delay_us(10);
    RC2=0;
    
    while(!RB3);
    
    // Turn ON TIMER 
    
    TMR1ON = 1;
    
    while(RB3);
    
    // Turn OFF TIMER 
    TMR1ON = 0;
    
    d= TMR1/58.82;
    
    return d;

}

void main(void) {
    
    
    // Create Distance Variable
    unsigned char dis = 0;
    // Set port B as an output for LED
    TRISB = 0x00;
    // Set port B to be low for initial 
    PORTB = 0x00;
    // Set output pin (echo)
    TRISC2= 0;
    // Set input pin (trigger)
    TRISC3= 1;
    // Prescaler (0,0) = 1
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    
    // Chose timer mode 
    TMR1CS=0;
    
    
    while(1)
    {
        dis=distance()/5;
        switch(dis)
        {
            case 1:
                PORTB = 0x01;
                break;
            case 2:
                PORTB = 0x03;
                break;
            case 3:
                PORTB = 0x07;
                break;
            case 4:
                PORTB = 0x0F;
                break;
            default:
                PORTB = 0x00;
                __delay_ms(100);
               
        
        }
       
    }
    
    return;
}
