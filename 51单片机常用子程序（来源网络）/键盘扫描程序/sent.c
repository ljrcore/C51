#include <reg51.h>
uchar idata trdata[]={"MCS-----51���ڲ��Գ���"};
void sent(void)
{uchar i;
 uint j;
 TMOD=0X20;                /*��ʱ��1��λ�Զ���װ*/
 TL1=0Xdd;TH1=0Xdd;        /*8MHz��1200����,-0.79% */
 SCON=0Xd8;PCON=0X10;      /*11λ�첽,��ʱ������*/
 TR1=1;
 while(1)
    {i=0;
     while(trdata[i]!=0x00)
        {SBUF=trdata[i];
	   	 while(TI==0);
	     TI=0;i++;
	     }
     for(j=0;j<65535;j++); /*����֮�����ʯ*/
    }
}
