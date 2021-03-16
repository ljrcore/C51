#include<AT89X051.H>
#define uchar unsigned char
#define uint unsigned int
uchar code trdata[]={"1_2_3韩红玲你好，我是尹刚，合作愉快！"};
//==============================================================
main()
{uchar i;				//i为待发数组指针、m为
 uint j;
 TMOD=0X20;                /*定时器1八位自动重装*/
 TL1=0Xff;TH1=0xff;        //11.0592MHz,57600波特
 SCON=0X5c;PCON=0X80;      /*11位异步,定时器控制*/
 TR1=1;
 while(1)
 	{
		{  i=0;
		   while(trdata[i]!=0x00)
	           {SBUF=trdata[i];
		   	    while(TI==0);
		        TI=0;i++;
		        }
		   for(j=0;j<30000;j++);
	    }
	}
}
