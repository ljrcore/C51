//******************************************************************************
//  MSP-FET430X110 Demo - Toggle P1.0 Using WDT and 32kHz ACLK 
//
//  Description; Toggle P1.0 using software timed by WDT ISR. Toggle rate is 
//  exatly 250ms based on 32kHz ACLK WDT clock source.  In this example the 
//  WDT is configured to divide 32768 watch-crystal(2^15) by 2^13 with an ISR 
//  triggered @ 4Hz.  
//  //*External watch crystal installed on XIN XOUT is required for ACLK*//	  
//
//                MSP430F1121
//             -----------------
//         /|\|              XIN|-  
//          | |                 | 32k
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include  <msp430x11x1.h>

void main(void)
{ 
  WDTCTL = WDT_ADLY_250;                // Set Watchdog Timer to exactly 250ms
  IE1 |= WDTIE;                         // Enable WDT interrupt
  P1DIR |= 0x01;                        // Set P1.0 to output direction
  _EINT();                              // Enable interrupts
  
  for (;;)                              // Infinate loop
  {
    _BIS_SR(LPM3_bits);                 // CPU and DCO not required
    _NOP();                             // Required only for C-spy
  }
}

// Watchdog Timer interrupt service routine
interrupt[WDT_VECTOR] void watchdog_timer(void)
{
  P1OUT ^= 0x01;                        // Toggle P1.0 using exclusive-OR
}

