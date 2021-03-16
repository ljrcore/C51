/*******************************************************************************
* ʵ �� ��		 : ��̬����ܰ����ƶ���ʾ����
* ʵ��˵��       : 
* ���ӷ�ʽ       : �����߽�P0�ں�74H573�Աߵ�J12��������
*                * ��138��������A��B��C�˷ֱ��P2.2��P2.3��P2.4
*                * �����߽�P1�ں;�������Աߵ�JP4��������
* ע    ��		 : 
*******************************************************************************/
#include<reg51.h>

//--����ʹ�õ�IO��--//
#define GPIO_DIG P0
#define GPIO_KEY P1

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//--����ȫ�ֱ���--//
unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0��1��2��3��4��5��6��7��8��9��A��b��C��d��E��F����ʾ��
unsigned char KeyValue;
//������Ŷ�ȡ���ļ�ֵ
unsigned char KeyState;	//��¼������״̬��0û�У�1��
unsigned char DisplayData[8];
//�������Ҫ��ʾ��8λ����ֵ

//--����ȫ�ֱ���--//
void Delay10ms(unsigned int c);   //��� 0us
void KeyDown();		 //��ⰴ������
void DigDisplay(); //��̬��ʾ����
/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void main(void)
{
	KeyState=0;
	while(1)
	{
		KeyDown();
	 	if(KeyState==1)
		{
			DisplayData[7]=DisplayData[6];
			DisplayData[6]=DisplayData[5];
			DisplayData[5]=DisplayData[4];
			DisplayData[4]=DisplayData[3];
			DisplayData[3]=DisplayData[2];
			DisplayData[2]=DisplayData[1];
			DisplayData[1]=DisplayData[0];
			DisplayData[0]=DIG_CODE[KeyValue];
			
			KeyState=0;
		}
		DigDisplay();
	}				
}

/*******************************************************************************
* �� �� ��         : DigDisplay
* ��������		   : ʹ���������ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void DigDisplay()
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
		j=10;						 //ɨ����ʱ���趨
		while(j--);	
		GPIO_DIG=0x00;//����
	}
}

/*******************************************************************************
* �� �� ��         : KeyDown
* ��������		   : ����а������²���ȡ��ֵ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void KeyDown(void)
{
	unsigned int a=0;

	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)
  	{
		Delay10ms(1);
		a++;	
		a=0;
		if(GPIO_KEY!=0x0f)
		{
			KeyState=1;//�а�������
			//������
			GPIO_KEY=0X0F;
// 			Delay10ms(1);
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=4;break;
				case(0X0d): KeyValue=8;break;
				case(0X0e):	KeyValue=12;break;
//				default:	KeyValue=17;	//������ظ�17��˼�ǰ������ȫ�����
			}
			//������
			GPIO_KEY=0XF0;
//			Delay10ms(1);
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue+3;break;
				case(0Xb0):	KeyValue=KeyValue+2;break;
				case(0Xd0): KeyValue=KeyValue+1;break;
				case(0Xe0):	KeyValue=KeyValue;break;
//				default:	KeyValue=17;
			}
			while((a<50)&&(GPIO_KEY!=0xf0))	 //�������ּ��
			{
				Delay10ms(1);
				a++;
			}
			a=0;
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