#include <absacc.h>
#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
#define ADC0809  XBYTE[0x2010]
void power(void);
void wait(uint n);
void main(void)
{power();}
void power(void)
{  uchar x;
   for(;;)
        {ADC0809=0x01;
         wait(1000);
         x=ADC0809;
         P2=x;
         }
}

void wait(uint n)
{   uint i,j;
    for(i=0;i<n;i++)
    for(j=0;j<100;j++);
}

