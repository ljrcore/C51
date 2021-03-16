//******************************************************************************
//  MSP-FET430P410 Demo - Toggle P5.1 Using WDT ISR and DCO/SMCLK 
//
//  Description; Toggle P5.1 using software timed by the WDT ISR. Toggle rate 
//  is approximately 30ms based on default ~ 800khz DCO/SMCLK clock source 
//  used in this example for the WDT.  
//
//		  MSP430F413
//             -----------------
//         /|\|              XIN|-  
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  M.Buccini
//  Texas Instruments, Inc
//  December 2001
//******************************************************************************

#include  <msp430x41x.h>

void main(void)
{ 
  WDTCTL = WDT_MDLY_32;                 // Set Watchdog Timer interval to ~30ms
  IE1 |= WDTIE;                         // Enable WDT interrupt
  P5DIR |= 0x02;                        // Set P5.1 to output direction
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
  P5OUT ^= 0x02;                        // Toggle P5.1 using exclusive-OR
}

