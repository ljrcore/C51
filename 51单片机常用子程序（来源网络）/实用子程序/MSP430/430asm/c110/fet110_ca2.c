/*;******************************************************************************
;    MSP-FET430F1121 Demo - Using Comparator_A to detect theshold 
;
;    Description; Use comparator_A to detect a voltage threshold.
;    Using an external potentiometer, an unknown voltage is applied to P2.3.
;    Comparator_A compares the unknown voltage to an internal reference
;    voltage, in this example 0.25*VCC.  If the unknown voltage is higher
;    than 0.25*VCC, P1.0 is set, if not, P1.0 is reset.
;    
;           MSP430F1121
;        _________________
;    /|\ |            XIN|-  
;     |  |               | 
;     ---|RST        XOUT|-
;     |  |               |
;     R<-|P2.3       P1.0|-->LED
;     |  |               |           
;     ---|VSS
;
;    Thomas Neu
;    Texas Instruments, Inc
;    March 2000
;******************************************************************************;*/

#include  "msp430x11x1.h"

void main (void)
{
  WDTCTL = WDTPW + WDTHOLD;       // Stop WDT
  P1DIR |= BIT0;                  // P1.0 output
  CACTL1 = CARSEL + CAREF0 + CAON;   // 0.25 Vcc = -comp, on
  CACTL2 = P2CA0;                 // P2.3 = +comp

  while (1)                       // Test comparator_A output
  {
    if ((CAOUT & CACTL2) == CAOUT) P1OUT |= BIT0;   // if CAOUT set, set P1.0
    else P1OUT &= ~BIT0;          // else reset
  }
}

