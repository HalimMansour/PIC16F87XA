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

//--------------------------------
// Function Declarations
void initializePeripherals(void);
void __interrupt() uartReceiveISR(void);

// Globals
volatile uint8_t uartRxBuffer = 0;

//--------------------------------
// Main Routine
void main(void)
{
    initializePeripherals();

    while (1)
    {
        // Stay Idle, Everything is handled in the ISR!
    }
}

//--------------------------------
// Function Definitions
void initializePeripherals(void)
{
    // Initialize UART
    BRGH = 1; // Set For High-Speed Baud Rate
    SPBRG = 25; // Set The Baud Rate To Be 9600 bps
    SYNC = 0; // Asynchronous mode
    SPEN = 1; // Enable UART
    TRISC6 = 1; // Set RX pin as input
    TRISC7 = 1; // Set TX pin as input
    CREN = 1; // Enable Continuous Reception
    RCIE = 1; // Enable UART Receive Interrupt
    PEIE = 1; // Enable Peripheral Interrupts
    GIE = 1; // Enable Global Interrupts

    // Initialize output port
    TRISB = 0x00; // Output Port (4-Pins)
    PORTB = 0x00; // Initially OFF
}

void __interrupt() uartReceiveISR(void)
{
    if (RCIF) // Check if UART receive interrupt occurred
    {
        uartRxBuffer = RCREG; // Read the received data buffer
        PORTB = uartRxBuffer; // Display the received data on LEDs
        RCIF = 0; // Clear the interrupt flag
    }
}
