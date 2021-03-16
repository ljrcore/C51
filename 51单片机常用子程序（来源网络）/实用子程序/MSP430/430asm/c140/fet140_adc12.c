//******************************************************************************
//  MSP-FET430P140 Demo - Simple Single That Samples ADC12 Channel A0 
//
//  Description; A simple single sample is made on A0 with refernce to Avcc.  
//  Software controls pulse on ADC12SC to sample analog input signal and start 
//  conversion. ADC12  internal oscillator times conversion. ADC12BUSY flag is 
//  polled for EOC. Conversion result saved in ADC12MEMO. 
//  // For acurate conversion, bias ADC12 references per device datasheet //  
//  
//                MSP430F149
//             -----------------
//         /|\|              XIN|-  
//          | |                 |
//          --|RST          XOUT|-
//            |                 |
//  0-AVcc >--|A0               |
//
//  M.Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include  <msp430x14x.h>

void main(void)
{ 
  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  ADC12CTL0 = ADC12ON + ENC;            // ADC12ON, conversion enabled
  P6SEL |= 0x01;                        // P6.0 ADC option select 
  
  for (;;)                              // Infinate loop
  {
    ADC12CTL0 |= ADC12SC;               // Sampling open
    ADC12CTL0 &= ~ADC12SC;              // Sampling closed, start conversion
    while ((ADC12CTL1 & ADC12BUSY) == 0);   // ADC12 busy?
  }
}
