/*fosc=12MHz,要求P1.0输出T=2ms的方波.*/
/*使用中断方式*/
#include<reg51.h>
sbit p2_0=P2^0;

timer0() interrupt 1 using 1
{p2_0=!p2_0;
TH0=0xff;TL0=0xce;
}
main()
{TMOD=0X01;
P1=0x00;
P2=0x00;
P0=0x00;
P3=0x00;
p2_0=0;
EA=1;ET0=1;TR0=1;
do{}while(1);
}
