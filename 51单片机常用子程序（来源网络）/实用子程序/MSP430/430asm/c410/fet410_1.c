//*******************************************************************************
//  MSP-FET430P410 Demo - Toggle P5.1 with Software 
//
//  Description; Toggle P5.1 by xor'ing P5.1 inside of a software loop.
//
//                MSP430F413
//             -----------------
//         /|\|              XIN|-  
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P5.1|-->LED
//
//  M. Buccini
//  Texas Instruments, Inc
//  December 2001
//******************************************************************************

#include  <msp430x41x.h>

void main(void)
{ 
  WDTCTL = WDTPW + WDTHOLD;             // Stop watchdog timer
  P5DIR |= 0x02;                        // Set P5.1 to output direction

  for (;;)                              // Infinate loop
  {
    unsigned int i;

    P5OUT ^= 0x02;                      // Toggle P5.1 using exclusive-OR

    i = 50000;                          // Delay
    do (i--);
    while (i != 0);
  }
}
