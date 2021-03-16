//******************************************************************************
//  MSP-FET430P120 Demo - USART0 115200 Baud UART Echo Example With Interrupt
//
//  Description; Echo a received character, RX ISR used. Normal mode is LPM0, 
//  RX interrupt triggers TX Echo. 
//  ACLK = MCLK = UCLK0 = 8MHz
//  Baud rate divider with 8Mhz XTAL = 8000000/115200 = 0069 (0045h)
//  //*USART0 interrupt flags are in different SFR's from other MSP430's// 
//  //*An external 8Mhz XTAL on XIN XOUT is required for ACLK*//
//
//              
//                MSP430F123   
//             -----------------
//         /|\|              XIN|-  
//          | |                 | 8MHz 
//          --|RST          XOUT|-
//            |                 |
//            |             P3.4|------------> 
//            |                 | 115200 - 8N1
//            |             P3.5|<------------
//
//       
//  M. Buccini
//  Texas Instruments, Inc
//  January 2002
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
  UBR00 = 0x45;                         // 8MHz 115200
  UBR10 = 0x00;                         // 8MHz 115200
  UMCTL0 = 0x00;                        // 8MHz 115200 modulation
  ME2 |= UTXE0 + URXE0;                 // Enabled USART0 TXD/RXD
  IE2 |= URXIE0;                        // Enabled USART0 RX interrupt
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
  while ((IFG2 & UTXIFG0) == 0);        // USART0 TX buffer ready?
  TXBUF0 = RXBUF0;                      // RXBUF0 to TXBUF0
}
