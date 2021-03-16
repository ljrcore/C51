//******************************************************************************
//  MSP-FET430P410 Demo - Toggle P5.1 Using BT ISR and DCO/SMCLK 
//
//  Description; This program will toggle P5.1 by xor'ing P5.1 inside of
//  a basic timer ISR. Default DCO used to clock basic timer. 
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
  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  IE2 |= BTIE;                          // Enable BT interrupt
  BTCTL = BTSSEL+BTIP2+BTIP1+BTIP0;       
  P5DIR |= 0x02;                        // Set P5.1 to output direction
  _EINT();                              // Enable interrupts
  
  for (;;)                              // Infinate loop
  {
    _BIS_SR(CPUOFF);                    // Enter LPM0
    _NOP();                             // Required only for C-spy
  }
}

// Basic Timer interrupt service routine
interrupt[BASICTIMER_VECTOR] void basic_timer(void)
{
  P5OUT ^= 0x02;                        // Toggle P5.1 using exclusive-OR
}

