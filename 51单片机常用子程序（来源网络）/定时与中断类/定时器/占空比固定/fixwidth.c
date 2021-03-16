//fosc=10MHz,要求输出T=2.5s占空比为20%的脉冲。//
//取10ms时基，中断方式。2.5s需求量250次中断，高电平为50次中断。//
//时间常数=10*1000*10/12=8333//
#include <reg51.h>
#define uchar unsigned char
uchar time,period=250,high=50;

timer0()interrupt 1 using 1
{TH0=-8333/256;TL0=-8333%256;
 if(++time==high)P1=0;       // 高电平时间到变低性 //
 else if(time==period)       // 周期时间到变高并复位，开始下一周期//
     {time=0;P1=1;}
}
main()
{TMOD=0X01;
TH0=-8333/256;
TL0=-8333%256;
EA=1;ET0=1;TR0=1;
do{}while(1);
}

