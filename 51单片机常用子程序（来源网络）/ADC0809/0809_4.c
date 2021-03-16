#include <reg51.h>                //����51ϵ��CPU��I/0�˿ڡ����ܼĴ����ȵĶ���ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int
sbit START=P2^2;    //��ALE����
sbit OE   =P2^3;
void serial(void) interrupt 4             //51EMB-32��
{}

void Hdelay(uint count)/*MAX��ʱ0.590383��*/
{    while (count--);
}

void main (void)
{ 
    SCON  = 0x50;                /* SCON: mode 1, 8-bit UART, enable rcvr*/
    TMOD = 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload*/
    PCON=0x80;                    /*��Ƶ*/
    TH1   = 0xf3;                /* TH1:  reload value for 19.2k baud @ 12MHz*/
    TR1   = 1;                  /* TR1:  timer 1 run*/
    ES=1;                       /*����Ϊ�����ȼ�*/
    EA=1;
    TI=0;
while (1)
{   OE=0;
    START=0;
    START=1;
    START=0;
    Hdelay(0x255);
    OE=1;
    SBUF=P0; 
     while (TI==0);
     TI=0;
    Hdelay(0x2255);
    }
} 

