//******************************************************************************
//   MSP-FET430P120 Demo - USART0 19200 Baud UART Echo Example With Interrupt
//
//   Description; Echo a received character using USART0, RX ISR used. Also,
//   if character 'a' is received, P1.0 is set, else cleared.
//   ACLK = MCLK = UCLK0 = 3.58MHz, SMCLK = DCOCLK
//   Baud rate divider with 3.58Mhz XTAL @19200 = 3.58MHz/19200 = 186 (00BAh)
//   //*USART0 interrupt flags are in different SFR's from other MSP430's// 
//   //*An external 3.58Mhz XTAL on XIN XOUT is required for ACLK*//
//
//              
//                MSP430F123   
//             -----------------
//         /|\|              XIN|-  
//          | |                 | 3.58MHz 
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//            |                 |
//            |             P3.4|------------> 
//            |                 | 19200 - 8N1
//            |             P3.5|<------------
//
//       
//    M. Buccini
//    Texas Instruments, Inc
//    November 2001
//******************************************************************************

#include <msp430x12x.h>

void main(void)
{
  unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  BCSCTL1 |= XTS;                       // ACLK = LFXT1 = HF XTAL

  do 
  {
  IFG1 &= ~OFIFG;                       // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);           // Time for flag to set
  }
  while ((IFG1 & OFIFG) == OFIFG);      // OSCFault flag still set?                

  BCSCTL2 |= SELM1+SELM0;               // MCLK = LFXT1 (safe)
  UCTL0 = CHAR;                         // 8-bit character
  UTCTL0 = SSEL0;                       // UCLK = ACLK
  UBR00 = 0xBA;                         // 3.58Mhz 19200 - 186
  UBR10 = 0x00;                         //
  UMCTL0 = 0x00;                        // no modulation
  ME2 |= UTXE0 + URXE0;                 // Enabled USART0 TXD/RXD
  IE2 |= URXIE0;                        // Enabled USART0 RX interrupt
  P1DIR |= BIT0;                        // P1.0 output
  P3SEL |= 0x30;                        // P3.4,5 = USART0 TXD/RXD
  P3DIR |= 0x10;                        // P3.4 output direction
  _EINT();                              // Enable interrupts
  
  while(1)
  {
    _BIS_SR(CPUOFF);                    // Enter LPM0
    _NOP();                             // Required only for C-spy
  }
}

interrupt[UART0RX_VECTOR] void usart0_rx (void)
{
  while ((IFG2 & UTXIFG0) != UTXIFG0);  // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                      // RXBUF0 to TXBUF0
  if (RXBUF0 == 'a') P1OUT |= BIT0;     // 'a' received, set P1.0
  else P1OUT &= ~BIT0;                  // else reset P1.0
}
