//*******************************************************************************
//  MSP-FET430X110 Demo - PWM Generation using timer_A in upmode and ACLK
//
//  Description; Generate PWM output on P1.2 using Timer_A in upmode. Value 
//  in CCR0 defines the period and value in CCR1 defines the the duty cycle.
//  In this example using 32kHz ACLK as TACLK, the period is 15.6ms with a 
//  75% duty cycle. PWM is done with timer_A hardware. 
//  //*External watch crystal installed on XIN XOUT is required for ACLK*//	  
//
//           MSP430F1121
//         ---------------
//     /|\|            XIN|-  
//      | |               | 32kHz
//      --|RST        XOUT|-     
//        |               |
//        |           P1.2|--> CCR1 - PWM Signal
//
//  M. Buccini
//  Texas Instruments, Inc
//  January 2002
//*******************************************************************************

#include <msp430x11x1.h>

void main(void)
{ 
  WDTCTL = WDTPW +WDTHOLD;              // Stop WDT
  TACTL = TASSEL0 + TACLR;              // ACLK, Clear Tar
  CCR0 = 512-1;                         // PWM Period
  CCTL1 = OUTMOD2 + OUTMOD1 + OUTMOD0;  // CCR1 reset/set
  CCR1 = 384;                           // CCR1 PWM duty cycle
  P1DIR |= 0x04;                        // P1.2 output
  P1SEL |= 0x04;                        // P1.2 TA1 output
  TACTL |= MC0;                         // Start Timer_A in up mode
  
  for (;;)                              // Infinate loop
  {
    _BIS_SR(LPM3_bits);                 // CPU and DCO not required
    _NOP();                             // Required only for C-spy
  }
}

