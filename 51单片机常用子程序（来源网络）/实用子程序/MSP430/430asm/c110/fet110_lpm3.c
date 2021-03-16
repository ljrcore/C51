//******************************************************************************
//  MSP-FET430X110 Demo - Demonstrate LPM3, WDT Interrupt   
//
//  Description; This program operates MSP430 normally in LPM3, pulsing P1.0 
//  at 4 second intervals. WDT ISR used to wake-up system. All I/O configured 
//  as low outputs to eliminate floating inputs. Current consumption does 
//  increase when LED is powered on P1.0. Demo for measuring LPM3 current. 
//  //*External watch crystal installed on XIN XOUT is required for ACLK*//	  
//
//
//           MSP430F1121
//         ---------------
//     /|\|            XIN|-  
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.0|-->LED
//    
//  M. Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include <msp430x11x1.h>

void main(void)
{ 
  BCSCTL1 |= DIVA1;                     // ACLK/4
  WDTCTL = WDT_ADLY_1000;               // WDT 1s/4 interval timer
  IE1 |= WDTIE;                         // Enable WDT interrupt
  P1DIR = 0xFF;                         // All P1.x outputs
  P1OUT = 0;                            // All P1.x reset
  P2DIR = 0xFF;                         // All P2.x outputs
  P2OUT = 0;                            // All P2.x reset
  _EINT();                              // Enable interrupts
  
  while(1)
  {
    int i;
    _BIS_SR(LPM3_bits);                 // Enter LPM3
    P1OUT |= 0x01;                      // Set P1.0 LED on
    for (i = 5000; i>0; i--);           // Delay
    P1OUT &= ~0x01;                     // Reset P1.0 LED off
  }
}

interrupt[WDT_VECTOR] void watchdog_timer (void)
{
    _BIC_SR_IRQ(LPM3_bits);             // Cleat LPM3 bits from 0(SR)
}
