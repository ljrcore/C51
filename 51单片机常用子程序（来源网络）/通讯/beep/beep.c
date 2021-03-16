#include<AT89X051.H>
#define uchar unsigned char
#define uint unsigned int
void delay1ms(uint count)
{uint i;
 uchar j;
 for(i=0;i<count;i++)
 for(j=0;j<120;j++)
;
}
void beep()
{uchar i;
 for(i=0;i<0xff;i++)
	{
	 P3_5=0;
	 delay1ms(1);
	 P3_5=1;
	 delay1ms(1);
	}
}
void main(void)
{uchar a;
 TMOD=0X20;				//方式2自动重装
 TL1=0Xf3;TH1=0Xf3;     /*2400bps,12MHz*/
 SCON=0X5c;PCON=0X00;
 TR1=1;
 while(1)
      {while(RI==0);
       RI=0;
	   a=SBUF;
	   SBUF=a;
       while(TI==0);
       TI=0;
	   beep;
       }
 }
	   