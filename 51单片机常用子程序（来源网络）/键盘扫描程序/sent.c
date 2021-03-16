#include <reg51.h>
uchar idata trdata[]={"MCS-----51串口测试程序"};
void sent(void)
{uchar i;
 uint j;
 TMOD=0X20;                /*定时器1八位自动重装*/
 TL1=0Xdd;TH1=0Xdd;        /*8MHz，1200波特,-0.79% */
 SCON=0Xd8;PCON=0X10;      /*11位异步,定时器控制*/
 TR1=1;
 while(1)
    {i=0;
     while(trdata[i]!=0x00)
        {SBUF=trdata[i];
	   	 while(TI==0);
	     TI=0;i++;
	     }
     for(j=0;j<65535;j++); /*发送之间的岩石*/
    }
}
