/*
 * File:   main.c
 * Author: Halim
 *
 * Created on March 21, 2023, 3:27 AM
 */

#include <stdint.h>
#include <xc.h>
#include "config.h"


uint8_t X =  0; 
void main(void) {
    TMR1 = 0;
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    TMR1CS = 0;
    TMR1ON = 1;
    
    // Set The Output Pin For The LED
    TRISC4=0;
    RC4=0; 
    
    CCPR1 = 50000; // (0.5s) / (4 * 1 * 10 /(4MHz))   
    
    CCP1M0 = 1;
    CCP1M1 = 1;
    CCP1M2 = 0;
    CCP1M3 = 1;
    
    
    CCP1IE = 1;
    PEIE = 1;
    GIE = 1;
 
// Create The Main Loop Of The System
  while (1)
  {
      
  }
  return;
}
 
// Write The ISR Handler
void __interrupt() ISR(void)
{
  if ( CCP1IF )
  {
    X++;
    if (X==10)
    {
      // Toggle The LED
      RC4 = ~RC4;
      X = 0;
    }
    // Clear The Interrupt Flag Bit
    CCP1IF = 0;
  }
}