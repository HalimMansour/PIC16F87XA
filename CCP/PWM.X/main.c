/*
 * File:   main.c
 * Author: Halim
 *
 * 
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000

void PWM1_Set_Duty(uint16_t);

void main(void)
{
    // Configure the CCP Module for PWM Mode
    CCP1M3 = 1;
    CCP1M2 = 1;
    TRISC2 = 0; // The CCP1 Output Pin (PWM)

    // Set the PWM Frequency
    PR2 = 124;

    // Set the PS for Timer2 (1:4 Ratio)
    T2CKPS0 = 1;
    T2CKPS1 = 0;

    // Start CCP1 PWM!
    TMR2ON = 1;

    uint16_t DC = 0;

    // Write the system's main routine
    while (1)
    {
        DC = 0; // Start with 0% DutyCycle

        // Gradually increase LED brightness
        while (DC < 500)
        {
            PWM1_Set_Duty(DC);
            DC++;
            __delay_ms(2);
        }
        __delay_ms(100);

        // Gradually decrease LED brightness
        while (DC > 0)
        {
            PWM1_Set_Duty(DC);
            DC--;
            __delay_ms(2);
        }
        __delay_ms(100);
    }

    return;
}

void PWM1_Set_Duty(uint16_t DC)
{
    // Check the DC value to make sure it's within 10-bit range
    if (DC < 1024)
    {
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}
