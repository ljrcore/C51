//******************************************************************************
//  MSP-FET430P140 Demo - Toggle P1.0 using Timer_A and DCO/SMCLK 
//
//  Description; Toggle P1.0 using using software and TA_0 ISR. Toggle rate is 
//  set at 50000 DCO/SMCLK cycles. Default DCO frequency used for TACLK. 
//  Durring the TA_0 ISR P0.1 is toggled and 50000 clock cycles are added to 
//  CCR0.  TA_0 ISR is triggered exactly 50000 cycles. CPU is normally off and
//  used only durring TA_ISR.  
//   
//
//           MSP430F149
//         ---------------
//     /|\|            XIN|-  
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//
//  M. Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include <msp430x14x.h>

void main(void)
{ 
  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  TACTL = TASSEL1 + TACLR;              // SMCLK, clear TAR
  CCTL0 = CCIE;                         // CCR0 interrupt enabled
  CCR0 = 50000;
  P1DIR |= 0x01;                        // P1.0 output
  TACTL |= MC1;                         // Start Timer_A in continuous mode
  _EINT();                              // Enable interrupts
 
  for (;;)                              // Infinate loop
  {
    _BIS_SR(CPUOFF);                    // CPU off
    _NOP();                             // Required only for C-spy
  }
}

// Timer A0 interrupt service routine
interrupt[TIMERA0_VECTOR] void Timer_A (void)
{
  P1OUT ^= 0x01;                        // Toggle P1.0
  CCR0 += 50000;                        // Add Offset to CCR0
}

