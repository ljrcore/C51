//******************************************************************************
//  MSP-FET430P140 Demo - LFXT1 / MCLK configured to operate with HF XTAL
//
//  Description; Proper selection of an external HF XTAL for MCLK is shown by
//  first polling the OSC fault until XTAL is stable - only then is MCLK
//  sourced by LFXT1.  MCLK is on P5.4 
//  ** HF XTAL NOT INSTALLED ON FET **//
//
//                MSP430F149
//             -----------------
//         /|\|              XIN|-  
//          | |                 | HF XTAL (455k - 8Mhz)
//          --|RST          XOUT|-
//            |                 |
//            |             P5.4|-->MCLK = XTAL
//
//       
//  M. Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include <msp430x14x.h>

void main(void)
{
  unsigned int i;
  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  BCSCTL1 |= XTS;                       // ACLK = LFXT1 = HF XTAL
  P5SEL |= 0x10;                        // P5.4 = MCLK
  P5DIR |= 0x10;                        // P5.4 output direction

  do 
  {
  IFG1 &= ~OFIFG;                       // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);           // Time for flag to set
  }
  while ((IFG1 & OFIFG) == OFIFG);      // OSCFault flag still set?                

  BCSCTL2 |= SELM1+SELM0;               // MCLK = LFXT1 (safe)
  
  for (;;);                             // Do nothing
}
