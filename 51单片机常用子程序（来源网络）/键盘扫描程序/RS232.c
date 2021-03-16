#include<reg51.h>
void RS232(void)
{uchar a;
 TMOD=0X20;
 TL1=0Xdd;TH1=0Xdd;
 SCON=0X50;PCON=0X10;//8MHz,1200波特,-0.79%,方式1
 TR1=1;
 while(1)
      {while(RI==0);//接收数据
       RI=0;
	   a=SBUF;
	   SBUF=a;      //发送数据
       while(TI==0);
       TI=0;
       }
 }
	   