//**************************************************************************
//* 
//*   ADC12 Test Program for MSP430F149                           7/24/2001
//* 
//*   This demo program shows the use of sequence measurement triggered
//*   by one single signal. Mutliple Sample&Hold feature is used here.
//*   No interrupts are used but flag is monitored to determine end of 
//*   sequence of channels
//*   One single conversion sequence is initiated. The sequence is 
//*   triggered by software using the ADC12SC bit. After the sequence
//*   is finished the results are transmitted via RS232 (USART module of
//*   MSP430 is used). After that the next conversion sequence is initiated.
//*
//*   All 16 ADC12MEMx Registers are used by this program:
//*   ADC12MEM0 contains the input A0 conversion result,
//*   ADC12MEM1 contains the input A1 conversion result, and so on.
//*
//*   The conversion results are transmitted via the USART module (using
//*   TXD Pin P3.6).
//*   USART Settings:   4800 baud, 8 data bits, even parity, 1 stop bit
//* 
//**************************************************************************

#include "MSP430x14x.h"     // Standard Definition Control Register
#define ADCMEM ((int*) 0x0140)  // ADC12MEMx definition
//--------------------------------------------------------------------------
void Init(void);          // Initialization of System/Control Registers
void SendResult(void);    // conversion result is sent via RS232
int Digit0(int Register); // LSB nibble (digit 0) of Register is sent back
int Digit1(int Register); // middle nibble (digit 1) of Register is sent back
int Digit2(int Register); // MSB nibble (digit 2) of Register is sent back
int Hex2ASCII(int hex);   // conversion of hexadecimal number into ASCII
//--------------------------------------------------------------------------

void main(void)
{   unsigned int i; 
 
    Init();              // Initialization

    while (1)
    { 
       ADC12CTL0 |= 0x01; // start sampling (trigger signal for one sequence)

       while ((ADC12IFG&0x8000)==0); // wait until interrupt flag 15 is set
                                     // = whole sequence is finished

       SendResult();             // send conversion results via RS232
                                 // accessing ADC12MEMx registers clears
                                 // the interrupt flags
       for (i=0;i<=40000;i++);   // wait loop (delay between sequences)
    }
}


void Init(void)
{    WDTCTL = WDTPW + WDTHOLD;        // Stop watchdog timer

/* USART Settings:
      UART function, Idle line multiprocessor Protocol,
      4800 baud, 8 data bits, even parity, 1 stop bit   */
     UCTL1 &=~ SWRST;          // reset SWRST bit
     UCTL1 = 0xD0;  
     UBR01 = 0x06;  
     UBR11 = 0x00;  
     UMCTL1 = 0x6F; 
     UTCTL1 = 0x10; 
     URCTL1 = 0x00;    
     ME2 |= 0x20;              // enable USART transmit

     P3SEL = 0x40;             // Pin P3.6 used by USART module
     P3DIR = 0x40;             // Pin P3.6 is output

/* ADC12 Settings: */     
     ADC12CTL0 &=~ 0x02;   // Disable conversion before changing
                           // the ADC12 settings!!!
                        /* selection of reference and input */
     ADC12MCTL0  = 0x00;    // Ref = AVss, AVcc; Input = A0
     ADC12MCTL1  = 0x01;    // Ref = AVss, AVcc; Input = A1
     ADC12MCTL2  = 0x02;    // Ref = AVss, AVcc; Input = A2
     ADC12MCTL3  = 0x03;    // Ref = AVss, AVcc; Input = A3          
     ADC12MCTL4  = 0x04;    // Ref = AVss, AVcc; Input = A4
     ADC12MCTL5  = 0x05;    // Ref = AVss, AVcc; Input = A5
     ADC12MCTL6  = 0x06;    // Ref = AVss, AVcc; Input = A6
     ADC12MCTL7  = 0x07;    // Ref = AVss, AVcc; Input = A7
     ADC12MCTL8  = 0x08;    // Ref = AVss, AVcc; Input = A8
     ADC12MCTL9  = 0x09;    // Ref = AVss, AVcc; Input = A9
     ADC12MCTL10 = 0x0A;    // Ref = AVss, AVcc; Input = A10
     ADC12MCTL11 = 0x0B;    // Ref = AVss, AVcc; Input = A11
     ADC12MCTL12 = 0x0C;    // Ref = AVss, AVcc; Input = A12
     ADC12MCTL13 = 0x0D;    // Ref = AVss, AVcc; Input = A13
     ADC12MCTL14 = 0x0E;    // Ref = AVss, AVcc; Input = A14
     ADC12MCTL15 = 0x8F;    // Ref = AVss, AVcc; Input = A15
                            // ADC12MCTL15 is end of sequence 
                            // (EOS bit is set!)

     ADC12CTL1 = 0x0202;    // first conv. result is stored in ADC12MEM0
                            // ADC12SC bit triggers Sample&Hold
                            // sample pulse is generated by Sampling Timer
                            // Clock Source: ADC12 internal oscillator
                            // Clock divider: 1
                            // conversion mode: one single sequence

     ADC12CTL0 = 0x0090;    // Sample&Hold Time 0
                            // Sample&Hold Time 1 
                            // Multiple Sample&Hold 
                            // reference voltage is off
                            // ADC12 module is switched on 
                            // no interrupts 

     ADC12CTL0 |= 0x02;     // enable conversion
}


void SendResult(void)
{  char prompt1[81]="\r---------------------------------------\r\
mem0 mem1 mem2 mem3 mem4 mem5 mem6 mem7\r";
   char prompt2[42]="\r\rmem8 mem9 memA memB memC memD memE memF\r";
   int i;

   
   for (i=0;i<=80;i++)           // transmit "  MEM" via RS232
   {  TXBUF1=prompt1[i];
      while ((UTCTL1&0x01)==0);    
   }

   for (i=0;i<=7;i++)
   {  TXBUF1='0';                // transmit "0"
      while ((UTCTL1&0x01)==0);   
      TXBUF1=Digit2(ADCMEM[i]);  // transmit digit 2 of ADC12MEMx
      while ((UTCTL1&0x01)==0);   
      TXBUF1=Digit1(ADCMEM[i]);  // transmit digit 1 of ADC12MEMx
      while ((UTCTL1&0x01)==0);   
      TXBUF1=Digit0(ADCMEM[i]);  // transmit digit 0 of ADC12MEMx
      while ((UTCTL1&0x01)==0);    
      TXBUF1=' ';                // transmit " "
      while ((UTCTL1&0x01)==0);    
   }

   for (i=0;i<=41;i++)           // transmit "  MEM" via RS232
   {  TXBUF1=prompt2[i];
      while ((UTCTL1&0x01)==0);    
   }

   for (i=8;i<=15;i++)
   {  TXBUF1='0';                // transmit "0"
      while ((UTCTL1&0x01)==0);   
      TXBUF1=Digit2(ADCMEM[i]);  // transmit digit 2 of ADC12MEMx
      while ((UTCTL1&0x01)==0);   
      TXBUF1=Digit1(ADCMEM[i]);  // transmit digit 1 of ADC12MEMx
      while ((UTCTL1&0x01)==0);   
      TXBUF1=Digit0(ADCMEM[i]);  // transmit digit 0 of ADC12MEMx
      while ((UTCTL1&0x01)==0);    
      TXBUF1=' ';                // transmit " "
      while ((UTCTL1&0x01)==0);    
   }

   TXBUF1=13;                    // send carriage return
   while ((UTCTL1&0x01)==0);    
}

int Digit0(int Register)         // return LSB nibble (digit 0)
{  int result;

   result = Hex2ASCII(0x0F & Register);
   return result;
}

int Digit1(int Register)         // return nibble (digit 1)
{  int result;

   result = Register >> 4;
   result = Hex2ASCII(0x0F & result);
   return result;
}

int Digit2(int Register)         // return MSB nibble (digit 2)
{  int result;

   result = Register >> 8;
   result = Hex2ASCII(0x0F & result);
   return result;
}

int Hex2ASCII(int hex)        // hexadecimal to ASCII conversion
{  int result;

   if (hex<=9) 
   {  result=hex+'0'; }       // convert number
   else
   {  result=hex+('A'-10); }  // convert letter 
   
   return result;
}