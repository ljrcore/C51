/*P1.0��P1.1�ֱ��������ؿ���S1,S2����ʼΪȫ�أ�2S��S1����0.1S��S2����
/*S1����2.0S S2����2.4S����˷���,fosc=10Mz
/*���عأ�2S�󣨹ؿ���1S�󣨿�����1.9S�󣨿��أ�5S�󣨹عأ�
/*��ÿ��10ms�ж�һ��,��Ӧ�Ĵ���Ϊ:0,200,300,490,990 ��P1���0,1,3,2  */
#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar i;
uint time;
code struct
{int position;
 char pattern;
 }next[]=
    {{0,0x00},{200,0x00},{300,0x03},{490,0x02},{990,0xff}};
time0()interrupt 1 using 1
{TH0=-8333/256;TL0=-8333%256;
 time++;
 if (time==next[i].position)
    {if(next[i].pattern==0xff)i=time=0;
     P1=next[i++].pattern;
     }
 }
main()
{P1=time=0;i=1;TMOD=0x01;
 TH0=8333/256;TL0=-8333%256;
 TR0=1;ET0=1;EA=1;
 for (;;){}
 }
    
       


