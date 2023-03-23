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

//--[ Pin Definitions ]--
#define REVERSE_DIRECTION_BUTTON RB0
#define SPEED_0_BUTTON RB1
#define SPEED_50_BUTTON RB2
#define SPEED_75_BUTTON RB3
#define SPEED_100_BUTTON RB4

//--[ Function Declarations ]--
void PWM1_Set_Duty(uint16_t);

void initialize_io_pins(void);
void initialize_pwm(void);

void main(void) {
    
    initialize_io_pins();
    initialize_pwm();
    
     while(1)
  {
    if(REVERSE_DIRECTION_BUTTON) // Reverse The Direction
    {
      RD0 = ~RD0;
      RD1 = ~RD1;
      __delay_ms(500); // Wait For The Button To Be Released
    }
    if(SPEED_0_BUTTON) // 0% DC
    {
      PWM1_Set_Duty(0);
      __delay_ms(100); // Wait For The Button To Be Released
    }
    if(SPEED_50_BUTTON) // 50% DC
    {
      PWM1_Set_Duty(250);
      __delay_ms(100); // Wait For The Button To Be Released
    }
    if(SPEED_75_BUTTON) // 75% DC
    {
      PWM1_Set_Duty(375);
      __delay_ms(100); // Wait For The Button To Be Released
    }
    if (SPEED_100_BUTTON) // 100% DC
    {
      PWM1_Set_Duty(500);
      __delay_ms(100); // Wait For The Button To Be Released
    }
    __delay_ms(10);  // Wait To Reduce The Simulation Overloading
  }
  return;
}

void initialize_io_pins(void)
{
  // Set RB0-RB4 as input pins
  TRISB = 0x1F;
  
  // Set RD0 and RD1 as output pins
  TRISD0 = 0;
  TRISD1 = 0;
  
  // Initially set motor direction to clockwise rotation
  RD0 = 0;
  RD1 = 1;
}

void initialize_pwm(void)
{
  // Configure CCP1 for PWM mode
  CCP1M3 = 1;
  CCP1M2 = 1;
  
  // Set CCP1 output pin (PWM)
  TRISC2 = 0;
  
  // Set PWM frequency (2kHz)
  PR2 = 124;
  
  // Set Timer2 prescaler to 1:4
  T2CKPS0 = 1;
  T2CKPS1 = 0;
  
  // Start CCP1 PWM
  TMR2ON = 1;
}

void PWM1_Set_Duty(uint16_t duty_cycle)
{
  // Check The Duty Cycle Value To Make Sure it's Within 10-Bit Range
  if(duty_cycle <1024)
  {
    CCP1Y = duty_cycle & 1;
    CCP1X = duty_cycle & 2;
    CCPR1L = duty_cycle >> 2;
  }
}