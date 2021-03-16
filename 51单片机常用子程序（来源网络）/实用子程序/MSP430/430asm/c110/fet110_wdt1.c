//******************************************************************************
//  MSP-FET430X110 Demo - Toggle P1.0 Using WDT ISR and DCO/SMCLK 
//
//  Description; Toggle P1.0 using software timed by the WDT ISR. Toggle rate 
//  is approximately 30ms based on default ~ 800khz DCO/SMCLK clock source 
//  used in this example for the WDT.  
//
//		 MSP430F1121
//             -----------------
//         /|\|              XIN|-  
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  M.Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include  <msp430x11x1.h>

void main(void)
{ 
  WDTCTL = WDT_MDLY_32;                 // Set Watchdog Timer interval to ~30ms
  IE1 |= WDTIE;                         // Enable WDT interrupt
  P1DIR |= 0x01;                        // Set P1.0 to output direction
  _EINT();                              // Enable interrupts
  
  for (;;)                              // Infinate loop
  {
    _BIS_SR(CPUOFF);                    // Enter LPM0
    _NOP();                             // Required only for C-spy
  }
}

// Watchdog Timer interrupt service routine
interrupt[WDT_VECTOR] void watchdog_timer(void)
{
  P1OUT ^= 0x01;                        // Toggle P1.0 using exclusive-OR
}

