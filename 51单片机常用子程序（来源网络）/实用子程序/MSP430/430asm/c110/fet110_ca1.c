//*******************************************************************************
//  MSP-FET430X110 Demo - Output Comparator_A reference voltages 
//
//  Description; Output comparator_A reference levels on P2.3.  Program will 
//  cycle through the on-chip comparator_A reference voltages with output on 
//  P2.3. 
//
//		 MSP430F1121
//             -----------------
//         /|\|              XIN|-  
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//            |             P2.3|-->Vref
//            |                 |			 
//
//  M.Buccini
//  Texas Instruments, Inc
//  January 2002
//*******************************************************************************

#include  "msp430x11x1.h"

void delay(void);                       // Software delay

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  CACTL2 = P2CA0;                       // P2.3 = +comp

  while (1)                             // Loop
  {
    CACTL1 = 0x00;                      // No reference voltage
    delay();
    CACTL1 = CAREF0 + CAON;             // 0.25*Vcc on P2.3, Comp. on
    delay();
    CACTL1 = CAREF1 + CAON;             // 0.5*Vcc on P2.3, Comp. on
    delay();
    CACTL1 = CAREF1 + CAREF0+ CAON;     // 0.55V on P2.3, Comp. on
    delay();
  }
}

void delay(void)
{
  unsigned long i;
    for (i = 0x7FFFF; i > 0; i--);
}  