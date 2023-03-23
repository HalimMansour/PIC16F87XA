/*
 * File:   main.c
 * Author: Halim
 *
 *
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ  4000000


void main(void) {


    // Set the TRIS values for the motor pins as outputs
    TRISB = 0x00;
    // Set the PORTS to be OFF
    PORTB = 0x00;

    // Create a bit shifter
    unsigned char s;

    while(1)
    {
        s=0;

        //  Rotation to the left
        for(int j = 0 ;j<48 ; j++)
        {
            PORTB = (1<<s);
            s++;
            __delay_ms(100);

            if(s=4)
                s=0;

        }

        // wait a 1/2 second
        __delay_ms(500);


        // Rotation to the right
        for(int j = 0 , s = 0 ;j<48 ; j++)
        {
            PORTB = (8>>s);
            s++;
            __delay_ms(100);

            if(s=4)
                s=0;

        }



    }

    return;
}
