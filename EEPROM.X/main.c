/*
 * File:   main.c
 * Author: Halim
 *
 * 
 */


#include <xc.h>
#include <stdint.h>

// Configuration header file
#include "config.h"

// Define the crystal frequency
#define _XTAL_FREQ 4000000

// Pin Definitions
#define READ RB0
#define WRITE_3 RB1
#define WRITE_5 RB2
#define WRITE_7 RB3

// Function Declarations
void eeprom_write(uint8_t address, uint8_t data);
uint8_t eeprom_read(uint8_t address);

void main(void)
{
    // IO Pins Configuration
    TRISB = 0x0F;  // Push Buttons 
    TRISD = 0x00;   // Output LEDs
    PORTD = 0x00;    // Initially OFF

    uint8_t address = 0;

    while (1)
    {
        if (WRITE_3) // Write 0x03
        {
            eeprom_write(address++, 3);
            __delay_ms(500);
        }

        if (WRITE_5) // Write 0x05
        {
            eeprom_write(address++, 5);
            __delay_ms(500);
        }

        if (WRITE_7) // Write 0x07
        {
            eeprom_write(address++, 7);
            __delay_ms(500);
        }

        if (address == 3)
        {
            address = 0;
        }

        if (READ == 1)
        {
            // Read The EEPROM Data Out To PORTD LEDs
            for (uint8_t i = 0; i < 3; i++)
            {
                PORTD  = eeprom_read(i);
                __delay_ms(2000);
            }
        }
    }
}

// Function Definitions
void eeprom_write(uint8_t address, uint8_t data)
{
    while (EECON1bits.WR); // Waits Until Last Attempt To Write Is Finished

    EEADR = address;    // Writes The Address To Which We'll Write Our Data
    EEDATA = data;      // Write The Data To Be Saved
    EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
    EECON1bits.WREN = 1;  // Enable The Operation !
    INTCONbits.GIE = 0;   // Disable All Interrupts Until Writing Data Is Done
    EECON2 = 0x55;        // Part Of Writing Mechanism..
    EECON2 = 0xAA;        // Part Of Writing Mechanism..
    EECON1bits.WR = 1;    // Part Of Writing Mechanism..
    INTCONbits.GIE = 1;   // Re-Enable Interrupts
    EECON1bits.WREN = 0;  // Disable The Operation
    EECON1bits.WR = 0;    // Ready For Next Writing Operation
}

uint8_t eeprom_read(uint8_t address)
{
    uint8_t data;

    EEADR = address;      // Write The Address From Which We Want To Get Data
    EECON1bits.EEPGD = 0; // Cleared To Point To EEPROM Not The Program Memory
    EECON1bits.RD = 1;    // Start The Read Operation
    data = EEDATA;        // Read The Data

    return data;
}