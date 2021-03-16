/*******************************************************************************
*                 
*                 		       ���пƼ�
--------------------------------------------------------------------------------
* ʵ �� ��		 : ���������ʾ����
* ʵ��˵��       : LCD1602��ʾ��ȡ���ļ�ֵ
* ���ӷ�ʽ       : ������ͼ
* ע    ��		 : 
*******************************************************************************/
#include<reg51.h>	
#include"lcd.h"

//--����ʹ�õ�IO��--//	
#define GPIO_KEY P1

//--����ȫ�ֱ���--//
unsigned char PuZh[17]="The key value is:";
unsigned char KeyValue;
//������Ŷ�ȡ���ļ�ֵ

//--����ȫ�ֺ���--//
void KeyScan(void);
void Delay10ms(unsigned int c);   //��� 0us

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
void main(void)
{
	unsigned char i;
	LcdInit();
	for(i=0; i<17; i++)
	{		
		if(i == 14)
		{
			LcdWriteCom(0x80 + 0x40);
		}
		LcdWriteData(PuZh[i]);			
	}
	while(1)
	{
		KeyScan();
		LcdWriteCom(0x80 + 0x44);
		if(KeyValue < 10)
		{
		  	LcdWriteData('0' + KeyValue);
		}
		else
		{
			LcdWriteData('7' + KeyValue); //A��ASCII���ǰ10λ��7��������7������	
		}	
	}				
}

/*******************************************************************************
* �� �� ��         : KeyScan
* ��������		   : ����а������²���ȡ��ֵ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void KeyScan(void)
{
	char a = 0;
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//��ȡ�����Ƿ���
	{
		Delay10ms(1);//��ʱ10ms��������
		if(GPIO_KEY!=0x0f)//�ٴμ������Ƿ���
		{
			
			//������
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=4;break;
				case(0X0d): KeyValue=8;break;
				case(0X0e):	KeyValue=12;break;
			}
			//������
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue+3;break;
				case(0Xb0):	KeyValue=KeyValue+2;break;
				case(0Xd0): KeyValue=KeyValue+1;break;
				case(0Xe0):	KeyValue=KeyValue;break;
			}
			while((a<50) && (GPIO_KEY!=0xf0))	 //��ⰴ�����ּ��
			{
				Delay10ms(1);
				a++;
			}
		}
	}
}

/*******************************************************************************
* �� �� ��         : Delay10ms
* ��������		   : ��ʱ��������ʱ10ms
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Delay10ms(unsigned int c)   //��� 0us
{
    unsigned char a, b;

	//--c�Ѿ��ڴ��ݹ�����ʱ���Ѿ���ֵ�ˣ�������for����һ��Ͳ��ø�ֵ��--//
    for (;c>0;c--)
	{
		for (b=38;b>0;b--)
		{
			for (a=130;a>0;a--);
		}          
	}       
}
