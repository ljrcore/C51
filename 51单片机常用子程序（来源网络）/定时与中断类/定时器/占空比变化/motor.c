#include<reg51.h>
#define uchar unsigned char
#define uint unsigned int
uchar time,status,percent,period;
bit one_round;
uint oldcount,target=500;

void pulse(void)interrupt 1 using 1
{TH0=-833/256;TL0=-833%256;ET0=1;
 if (++time==percent)P1=0;
 else if(time==100)
 {time=0;P1=1;}
 }

void tachmeter (void)interrupt 2 using 2
{union{uint word;
       struct{uchar hi;uchar lo;}byte;
       }newcount;
 newcount.byte.hi=TH1;
 newcount.byte.lo=TL1;
 period=newcount.word-oldcount;
 oldcount=newcount.word;
 one_round=1;
 }

void main(void)
{IP=0X04;TMOD=0X11;TCON=0X54;TH1=TL1=0;IE=0X86;
 for(;;)
  {if(one_round)
    {if(period<target)
       {if(percent<100)++percent;}
     else if(percent>0)--percent;
     one_round=0;
     }
   }
 }
      
