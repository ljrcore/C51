//******************************************************************************
//  MSP-FET430X110 Demo - Implement Auto RSEL SW FLL  
//
//  Description; Set DCO clock to (Delta)*(4096) using software FLL. DCO clock 
//  is output on P1.4 as SMCLK.  DCO clock, which is the selected SMCLK source 
//  for timer_A is integrated over ACLK/8 (4096) until SMCLK is is equal 
//  to Delta.  CCR2 captures ACLK/8.  To use Set_DCO Timer_A must be 
//  operating in continous mode.  Watch crystal for ACLK is required for 
//  this example.  Delta must be kept in a range that allows possible
//  DCO speeds.  Minimum Delta must be 64 or greater to ensure Set_DCO loop 
//  can complete within capture interval. Maximum delta can be calculated be 
//  f(DCOx7) / 4096.  f(DCOx7) can be found in device specific datasheet.  
//
//           MSP430F1121
//         ---------------
//     /|\|            XIN|-  
//      | |               | 32kHz
//      --|RST        XOUT|-
//        |               |
//        |           P1.4|--> SMLCK = target DCO
//   
//       
//  M. Buccini
//  Texas Instruments, Inc
//  January 2002
//******************************************************************************

#include <msp430x11x1.h>

//#define DELTA 900                       // target DCO = DELTA*(4096) = 3686400
#define DELTA 250                       // target DCO = DELTA*(4096) = 31024000  
//#define DELTA 64                        // target DCO = DELTA*(4096) = 3262144

void Set_DCO (void);

void main(void)
{ 
  unsigned int i;

  WDTCTL = WDTPW + WDTHOLD;             // Stop WDT
  BCSCTL1 |= DIVA1 + DIVA0;             // ACLK = LFXT1CLK/8
  P1DIR |= 0x10;                        // P1.4 output
  P1SEL |= 0x10;                        // P1.4 SMCLK output
  for (i = 0xFFFF; i > 0; i--);         // Delay for XTAL to settle
  Set_DCO();                            // Set DCO

  while (1);
}

void Set_DCO (void)                     // Subroutine to set DCO to selected frequency
{
  unsigned int Compare, Oldcapture = 0;

  CCTL2 = CCIS0 + CM0 + CAP;            // Define CCR2, CAP, ACLK
  TACTL = TASSEL1 + TACLR + MC1;        // SMCLK, continous mode
  while (1)
  {
    while ((CCTL2 & CCIFG) != CCIFG);   // Wait until capture occured!
    CCTL2 &= ~CCIFG;                    // Capture occured, clear flag
    Compare = CCR2;                     // Get current captured SMCLK
    Compare = Compare - Oldcapture;     // SMCLK difference
    Oldcapture = CCR2;                  // Save current captured SMCLK
    if (DELTA == Compare)
    {
      break;                            // if equal, leave "while(1)"
    }
    else if (DELTA < Compare)           // DCO is too fast, slow it down
    {
      DCOCTL--;
      if (DCOCTL == 0xFF)               // Did DCO role under?
      {
        BCSCTL1--;                      // Select next lower RSEL
      }
    }
    else
    {                      
      DCOCTL++;
      if (DCOCTL == 0x00)               // Did DCO role over?
      {
        BCSCTL1++;                      // Select next higher RSEL
      }
    }
  }  
CCTL2 = 0;                              // Stop CCR2 function
TACTL = 0;                              // Stop Timer_A
}

