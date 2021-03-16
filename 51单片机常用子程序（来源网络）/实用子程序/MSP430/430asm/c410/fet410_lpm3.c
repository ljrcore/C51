//******************************************************************************
//  MSP-FET430P410 Demo - Demonstrate LPM3, BT Interrupt   
//
//  Description: System runs normally in LPM3 with basic timer clocked by 
//  32kHz ACLK. At a 2 second interval the basic timer ISR will wake the 
//  system and flash the LED on P5.1 inside of the Mainloop. If using
//  FET, must release JTAG on go.
//  //*External watch crystal on XIN XOUT is required for ACLK*//	  
//
//
//           MSP430F413
//         ---------------
//     /|\|            XIN|-  
//      | |               | 32kHz
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
  FLL_CTL0 |= XCAP14PF;                 // Configure load caps
  IE2 |= BTIE;                          // Enable BT interrupt
  BTCTL = BTDIV+BTIP2+BTIP1+BTIP0;      // 2s Interrupt       
  P1DIR = 0xFF;                         // All P1.x outputs
  P1OUT = 0;                            // All P1.x reset
  P2DIR = 0xFF;                         // All P2.x outputs
  P2OUT = 0;                            // All P2.x reset
  P3DIR = 0xFF;                         // All P3.x outputs
  P3OUT = 0;                            // All P3.x reset
  P4DIR = 0xFF;                         // All P4.x outputs
  P4OUT = 0;                            // All P4.x reset
  P5DIR = 0xFF;                         // All P5.x outputs
  P5OUT = 0;                            // All P5.x reset
  P6DIR = 0xFF;                         // All P6.x outputs
  P6OUT = 0;                            // All P6.x reset
  _EINT();                              // Enable interrupts
  
  while(1)
  {
    int i;
    _BIS_SR(LPM3_bits);                 // Enter LPM3
    P5OUT |= 0x02;                      // Set P5.1 LED on
    for (i = 5000; i>0; i--);           // Delay
    P5OUT &= ~0x02;                     // Clear P5.1 LED off
  }
}

// Basic Timer interrupt service routine
interrupt[BASICTIMER_VECTOR] void basic_timer(void)
{
    _BIC_SR_IRQ(LPM3_bits);             // Cleat LPM3 bits from 0(SR)
}
