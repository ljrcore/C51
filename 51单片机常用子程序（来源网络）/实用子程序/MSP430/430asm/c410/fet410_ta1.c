//******************************************************************************
//   MSP-FET430P410 Demo - Toggle P5.1 using Timer_A and DCO/SMCLK 
//
//   Description; Toggle P5.1 using using software and TA_0 ISR. Toggle rate is 
//   set at 50000 DCO/SMCLK cycles. Default DCO frequency used for TACLK. 
//   Durring the TA_0 ISR P5.1 is toggled and 50000 clock cycles are added to 
//   CCR0.  TA_0 ISR is triggered exactly 50000 cycles. CPU is normally off and
//   used only durring TA_ISR.  
//   
//
//           MSP430F413
//         ---------------
//     /|\|            XIN|-  
//      | |               |
//      --|RST        XOUT|-
//        |               |
//        |           P5.1|-->LED
//
//    M. Buccini
//    Texas Instruments, Inc
//    December 2001
//******************************************************************************

#include <msp430x41x.h>

void main(void)
{ 
  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  TACTL = TASSEL1 + TACLR;              // SMCLK, clear TAR
  CCTL0 = CCIE;                         // CCR0 interrupt enabled
  CCR0 = 50000;
  P5DIR |= 0x02;                        // P5.1 output
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
  P5OUT ^= 0x02;                        // Toggle P5.1
  CCR0 += 50000;                        // Add Offset to CCR0
}

