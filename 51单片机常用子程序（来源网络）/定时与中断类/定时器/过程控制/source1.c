/*P1.0和P1.1分别由两开关控制S1,S2。开始为全关，2S后S1开，0.1S后S2开，
/*S1保持2.0S S2保持2.4S，如此反复,fosc=10Mz
/*（关关）2S后（关开）1S后（开开）1.9S后（开关）5S后（关关）
/*设每次10ms中断一次,对应的次数为:0,200,300,490,990 而P1输出0,1,3,2  */
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
    
       


