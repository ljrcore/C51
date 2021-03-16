#include"reg51.h"
#include"XPT2046.h"

//--����ʹ�õ�IO--//
#define GPIO_DIG P0

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//--����ȫ�ֱ���--//
unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0��1��2��3��4��5��6��7��8��9��A��b��C��d��E��F����ʾ��
unsigned char DisplayData[8];		//�������Ҫ��ʾ��8λ����ֵ
void DigDisplay(void);
void main(void)
{
	uint temp,count;
	while(1)
	{
	  if(count==50)
	  {
	  	count=0; 
	//	temp = Read_AD_Data(0x94);		//   AIN0 ��λ��
	//	temp = Read_AD_Data(0xD4);		//   AIN1 ��������
		temp = Read_AD_Data(0xA4);		//   AIN2 ��������
	//	temp = Read_AD_Data(0xE4);		//   AIN3 �ⲿ����
	  }
	  count++;
	  
	  DisplayData[0]=DIG_CODE[0];
	  DisplayData[1]=DIG_CODE[0];
	  DisplayData[2]=DIG_CODE[0];
	  DisplayData[3]=DIG_CODE[0];

	  DisplayData[4]=DIG_CODE[temp%10000/1000];
	  DisplayData[5]=DIG_CODE[temp%1000/100];
	  DisplayData[6]=DIG_CODE[temp%100/10];
	  DisplayData[7]=DIG_CODE[temp%10/1];

	  DigDisplay();
	}
}
void DigDisplay(void)
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
		GPIO_DIG=DisplayData[i];//���Ͷ���
		j=50;						 //ɨ����ʱ���趨
		while(j--);	
		GPIO_DIG=0x00;//����
	}
}
	
