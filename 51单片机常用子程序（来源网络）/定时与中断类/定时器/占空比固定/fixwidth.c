//fosc=10MHz,Ҫ�����T=2.5sռ�ձ�Ϊ20%�����塣//
//ȡ10msʱ�����жϷ�ʽ��2.5s������250���жϣ��ߵ�ƽΪ50���жϡ�//
//ʱ�䳣��=10*1000*10/12=8333//
#include <reg51.h>
#define uchar unsigned char
uchar time,period=250,high=50;

timer0()interrupt 1 using 1
{TH0=-8333/256;TL0=-8333%256;
 if(++time==high)P1=0;       // �ߵ�ƽʱ�䵽����� //
 else if(time==period)       // ����ʱ�䵽��߲���λ����ʼ��һ����//
     {time=0;P1=1;}
}
main()
{TMOD=0X01;
TH0=-8333/256;
TL0=-8333%256;
EA=1;ET0=1;TR0=1;
do{}while(1);
}

