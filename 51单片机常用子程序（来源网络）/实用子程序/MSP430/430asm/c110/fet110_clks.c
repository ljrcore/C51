//******************************************************************************
//  MSP-FET430x110 Demo - Output buffered SMCLK(DCO), ACLK and MCLK/12 
//     
//  Description; Buffer ACLK on P2.0, default SMCLK(DCO) on P1.4 and MCLK/12 on 
//  P1.1.  To measure SMCLK on P1.4 with the FET, JTAG must be released.
//  //*External watch crystal installed on XIN XOUT is required for ACLK*//	  
//
//               MSP430F1121
//             -----------------
//         /|\|              XIN|-  
//          | |                 | 32k
//          --|RST          XOUT|-
//            |                 |
//            |             P1.4|-->SMCLK ~ 800kHz
//            |             P1.1|-->MCLK/12 = DCO/12
//            |             P2.0|-->ACLK = 32kHz
//
//  M.Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include  <msp430x11x1.h>

void main(void)
{ 
  WDTCTL = WDTPW +WDTHOLD;  // Stop Watchdog Timer
  P1DIR |= 0x12;            // P1.1 and P1.4 outputs
  P1SEL |= 0x10;            // P1.4 SMCLK output
  P2DIR |= 0x01;            // P2.0 output
  P2SEL |= 0x01;            // P2.0 ACLK output
  
  while(1)
  {
	P1OUT ^= 0x02;      // Toggle P1.1
  }
}

