#include<AT89X51.H>
#define uchar unsigned char
#define uint unsigned int
bit T_done;
main()
{static uchar i,j;
 TMOD=0X20;                /*��ʱ��1��λ�Զ���װ*/
 TL1=0X40;TH1=0x40;        //11.0592MHz,57600����
 SCON=0X5c;PCON=0X80;      /*11λ�첽,��ʱ������*/
 IE=0x90;
 TR1=1;
 T_done=1;
while(1)
     {for(i=0;i<128;i++)
         {for(j=0;j<8;j++)
            {while(!T_done);
             SBUF=i;
             T_done=0;
 	        }
         }  
      }
 }

serial() interrupt 4 using 1
 {TI=0;
  T_done=1;
  }