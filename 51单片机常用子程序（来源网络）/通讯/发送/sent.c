#include<AT89X051.H>
#define uchar unsigned char
#define uint unsigned int
uchar code trdata[]={"1_2_3��������ã��������գ�������죡"};
//==============================================================
main()
{uchar i;				//iΪ��������ָ�롢mΪ
 uint j;
 TMOD=0X20;                /*��ʱ��1��λ�Զ���װ*/
 TL1=0Xff;TH1=0xff;        //11.0592MHz,57600����
 SCON=0X5c;PCON=0X80;      /*11λ�첽,��ʱ������*/
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
