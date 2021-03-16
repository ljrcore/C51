//*******************************************************************************
//  MSP-FET430P140 Demo - Toggle P1.0 with Software 
//
//  Description; Toggle P1.0 by xor'ing P0.1 inside of a software loop.
//
//                MSP430F149
//             -----------------
//         /|\|              XIN|-  
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{ 
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  P1DIR |= 0x01;                        // Set P1.0 to output direction

  for (;;)                              // Infinate loop
  {
    unsigned int i;

    P1OUT ^= 0x01;                      // Toggle P1.0 using exclusive-OR

    i = 50000;                          // Delay
    do (i--);
    while (i != 0);
  }
}
