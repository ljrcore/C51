#include <reg51.h>                //加入51系列CPU的I/0端口、功能寄存器等的定义头文件
#define uchar unsigned char
#define uint unsigned int
sbit START=P2^2;    //与ALE共用
sbit OE   =P2^3;
void serial(void) interrupt 4             //51EMB-32用
{}

void Hdelay(uint count)/*MAX延时0.590383秒*/
{    while (count--);
}

void main (void)
{ 
    SCON  = 0x50;                /* SCON: mode 1, 8-bit UART, enable rcvr*/
    TMOD = 0x20;               /* TMOD: timer 1, mode 2, 8-bit reload*/
    PCON=0x80;                    /*倍频*/
    TH1   = 0xf3;                /* TH1:  reload value for 19.2k baud @ 12MHz*/
    TR1   = 1;                  /* TR1:  timer 1 run*/
    ES=1;                       /*串口为高优先级*/
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

