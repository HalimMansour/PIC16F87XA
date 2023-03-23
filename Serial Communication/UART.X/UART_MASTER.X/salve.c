/*
 * File:   salve.c
 * Author: Halim`
 *
 * 
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"

#define _XTAL_FREQ 4000000

//--------------------------------
// Functions Declarations
void UART_RX_Init(void);
uint8_t UART_Read(void);

//--------------------------------
// Main Routine
void main(void)
{
  //--[ Peripherals & IO Configurations ]--
  UART_RX_Init(); // Initialize The UART in Slave Mode @ 9600bps
  TRISB = 0x00; // Output Port (4-Pins)
  PORTB = 0x00; // Initially OFF
  
  while(1)
  {
    // Stay Idle, Everything is handled in the ISR !
  }
}

//--------------------------------
// Functions Definitions
 
void UART_RX_Init()
{
  BRGH = 1; // Set For High-Speed Baud Rate
  SPBRG = 25; // Set The Baud Rate To Be 9600 bps
  // Enable The Ascynchronous Serial Port
  SYNC = 0;
  SPEN = 1;
  // Set The RX-TX Pins to be in UART mode (not io)
  TRISC6 = 1; // As stated in the datasheet
  TRISC7 = 1; // As stated in the datasheet
  //--[ Enable UART Receiving Interrupts ]--
  RCIE = 1; // UART Receving Interrupt Enable Bit
  PEIE = 1; // Peripherals Interrupt Enable Bit
  GIE = 1; // Global Interrupt Enable Bit
  
  CREN = 1; // Enable Data Continuous Reception
}

void interrupt ISR (void)
{
  if (RCIF == 1)
  {
    uint8_t receivedByte = UART_Read(); // Read The Received Data Buffer
    PORTB = receivedByte; // Display The Received Data On LEDs
    RCIF = 0; // Clear The Flag
  }
}

uint8_t UART_Read(void)
{
    while (!RCIF); // Wait until data is received
    return RCREG; // Return the received byte
}
