#include<at89x51.h>//6MHz����
#include<intrins.h>
#define beep P3_5
#define disp_data 	 P2_2
#define disp_clk 	 P2_3
#define play	 	 P2_7
#define record	 	 P2_6
#define online	 	 P2_0
#define localwarning 	 P3_4
#define jumper           P1_7
//************************1ms��ʱ���0.01ms(��1%)**********************//
void delayx1ms(Word num)  //ʵ��Ϊ1.17ms
{Word i,j;
 P3_6=!P3_6;
 for(i=0;i<num;i++)
 for(j=0;j<69;j++);
}
//*************************1ms��ʱ���0.01ms(��1%)*********************//
void delayx1ms1(Word count)//ʵ��Ϊ1.18ms
{Word j;
 while(count--!=0)
	for(j=0;j<46;j++);
}
void Pulse(void)
{for(;;)
	{P0_0=0;
	 delayx1ms(1);
	 P0_0=1;
	 delayx1ms(1);
	}
}
void Pulse1(void)
{for(;;)
	{P0_0=0;
	 delayx1ms1(1);
	 P0_0=1;
	 delayx1ms1(1);
	}
}
void main(void)
{
 P0=P1=P2=P3=0xff;
 play=0;			//������Ϊ0
 online=localwarning=0;		//��ռ�ߣ������ر���
 if (jumper)Pulse();
 else  	   Pulse1();
 }

