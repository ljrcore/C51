//******************************************************************************
//  MSP-FET430P140 Demo - Toggle P1.0 using Timer_B and DCO/SMCLK 
//
//  Description; Toggle P1.0 using using software and TB_0 ISR. Toggle rate is 
//  set at 50000 DCO/SMCLK cycles. Default DCO frequency used for TACLK. 
//  Durring the TB_0 ISR P1.0 is toggled and 50000 clock cycles are added to 
//  CCR0.  TB_0 ISR is triggered exactly 50000 cycles. CPU is normally off and
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
  TBCTL = TBSSEL1 + TBCLR;              // SMCLK, clear TAR
  TBCCTL0 = CCIE;                       // CCR0 interrupt enabled
  TBCCR0 = 50000;
  P1DIR |= 0x01;                        // P1.0 output
  TBCTL |= MC1;                         // Start Timer_A in continuous mode
  _EINT();                              // Enable interrupts
 
  for (;;)                              // Infinate loop
  {
    _BIS_SR(CPUOFF);                    // CPU off
    _NOP();                             // Required only for C-spy
  }
}

// Timer B0 interrupt service routine
interrupt[TIMERB0_VECTOR] void Timer_B (void)
{
  P1OUT ^= 0x01;                        // Toggle P1.0
  TBCCR0 += 50000;                      // Add Offset to CCR0
}

