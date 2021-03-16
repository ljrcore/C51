//******************************************************************************
//  MSP-FET430P140 Demo - USART0 9600 Baud UART Echo Example With Interrupt
//
//  Description; Echo a received character, RX ISR used. Normal mode is LPM0, 
//  RX interrupt triggers TX Echo. 
//  ACLK = MCLK = UCLK0 = 3.58MHz, SMCLK = DCOCLK
//  Baud rate divider with 3.58Mhz XTAL @9600 = 3.58MHz/9600 = 372 (0174h)
//  //*An external 3.58Mhz XTAL on XIN XOUT is required for ACLK*//	  
//
//                MSP430F149   
//             -----------------
//         /|\|              XIN|-  
//          | |                 | 3.58MHz 
//          --|RST          XOUT|-
//            |                 |
//            |             P1.0|-->LED
//            |                 |
//            |             P3.4|------------> 
//            |                 | 9600 - 8N1
//            |             P3.5|<------------
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

  do 
  {
  IFG1 &= ~OFIFG;                       // Clear OSCFault flag
  for (i = 0xFF; i > 0; i--);           // Time for flag to set
  }
  while ((IFG1 & OFIFG) == OFIFG);      // OSCFault flag still set?                

  BCSCTL2 |= SELM1+SELM0;               // MCLK = LFXT1 (safe)
  UCTL0 = CHAR;                         // 8-bit character
  UTCTL0 = SSEL0;                       // UCLK = ACLK
  UBR00 = 0x74;                         // 3.58Mhz 9600 - 372
  UBR10 = 0x01;                         //
  UMCTL0 = 0x00;                        // no modulation
  ME1 |= UTXE0 + URXE0;                 // Enable USART0 TXD/RXD
  IE1 |= URXIE0;                        // Enable USART0 RX interrupt
  P3SEL |= 0x30;                        // P3.4,5 = USART0 TXD/RXD
  P3DIR |= 0x10;                        // P3.4 output direction
  _EINT();                              // Enable interrupts
  
  for (;;)                              //
  {
    _BIS_SR(CPUOFF);                    // Enter LPM0
    _NOP();                             // Required only for C-spy
  }
}

interrupt[UART0RX_VECTOR] void usart0_rx (void)
{
  while ((IFG1 & UTXIFG0) == 0);        // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                      // RXBUF0 to TXBUF0
}
