/*fosc=12MHz,Ҫ��P1.0���T=200ms�ķ���,P1.7���T=2s�ķ���.*/
/*ʹ��������ʱ�ж�*/
#include<reg51.h>
sbit p1_0=P1^0;
sbit p1_7=P1^7;
unsigned char i=0;
timer0()interrupt 1 using 1
{p1_0=!p1_0;
TH0=-50000/256;
TL0=-50000%256;
i=i+1;
}
timer1()interrupt 3 using 2
{p1_7=!p1_7;
 i=0;
 }
main()
{p1_7=1;
 p1_0=1;
 TMOD=0X61;
 TH0=-50000/256;TL0=-50000%256;
 TH1=-5;TL1=-5;
 IP=0X08;EA=1;ET0=1;ET1=1;
 TR0=1;TR1=1;
 while(i<5);
 TCON=0x00;
 }
