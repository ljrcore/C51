//******************************************************************************
//  MSP-FET430P120 Demo - Simple Single Sample ADC10 Channel A0 
//
//  Description; A simple single sample is made on A0 with refernce to Avcc.  
//  Software sets ADC10SC to start sample and conversion - ADC10SC 
//  automatically cleared at EOC. ADC10 internal oscillator times sample and 
//  conversion. ADC10BUSY flag is polled for EOC. Conversion code in ADC10MEM. 
//  //* MSP430F12x2 or MSP430F11x2 Device Required*//
//
//                MSP430F12x2
//             -----------------
//         /|\|              XIN|-  
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//        >---|A0               |
//
//  M.Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include  <msp430x12x2.h>

void main(void)
{ 
  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  ADC10CTL1 = ADC10SHT_2;               // Enable 16x sample timer 
  ADC10CTL0 = ADC10ON + ENC;            // ADC10ON, conversion enabled
  ADC10AE |= 0x01;                      // P2.0 ADC option select 
  
  for (;;)                              // Infinate loop
  {
    ADC12CTL0 |= ADC12SC;               // Sampling open
    ADC12CTL0 &= ~ADC12SC;              // Sampling closed, start conversion
    while ((ADC10CTL1 & ADC10BUSY) == 0);   // ADC10BUSY?
  }
}
