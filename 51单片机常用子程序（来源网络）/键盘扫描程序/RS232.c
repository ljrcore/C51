#include<reg51.h>
void RS232(void)
{uchar a;
 TMOD=0X20;
 TL1=0Xdd;TH1=0Xdd;
 SCON=0X50;PCON=0X10;//8MHz,1200����,-0.79%,��ʽ1
 TR1=1;
 while(1)
      {while(RI==0);//��������
       RI=0;
	   a=SBUF;
	   SBUF=a;      //��������
       while(TI==0);
       TI=0;
       }
 }
	   