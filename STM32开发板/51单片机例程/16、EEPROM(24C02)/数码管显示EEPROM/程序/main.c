/*******************************************************************************
* ʵ����			  : EEPROMʵ��
* ʹ�õ�IO	    : 
* ʵ��Ч��      : ��K1������ʾ�����ݣ���K2��ȡ�ϴα�������ݣ���K3��ʾ���ݼ�һ��
*��K4��ʾ�������㡣
*	ע��					������P3.2�ڸ������߹��ã�����������ʵ��ʱΪ�˲��ú�����Ӱ��ʵ��Ч������ðѺ�������
*ȡ������
*
*********************************************************************************/
#include<reg51.h>
#include"i2c.h"

//--����ʹ�õ�IO��--//
//�����IO
#define GPIO_DIG	P0
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
//����IO
sbit K1=P3^0;
sbit K2=P3^1;
sbit K3=P3^2;
sbit K4=P3^3;

//--����ȫ�ֱ���--//
unsigned char code GPIO_DIG_CODE[10] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char Num=0;
unsigned int DisplayData[8] = {0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f};

//--����ȫ�ֺ���--//
void At24c02Write(unsigned char ,unsigned char );
unsigned char At24c02Read(unsigned char );
void Delay10ms(unsigned int c);   //��� 0us
void Timer0Configuration();

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void main()
{
	unsigned int num0 = 0,num1 = 0,n;

	Timer0Configuration();

	while(1)
	{
		if(K1 == 0)		 //����1����
		{
			Delay10ms(1);
			if(K1 == 0)
				At24c02Write(2,num0);
			while((n < 50)&&(K3==0))
			{
				n++;
				Delay10ms(1);	
			}			
			n=0;
			n=0;
		}
		
		if(K2 == 0)		 //����2����
		{
			Delay10ms(1);
			if(K2 == 0)
				num1 = At24c02Read(2);
			while((n < 50)&&(K2 == 0))
			{
				n++;
				Delay10ms(1);	
			}			
			n=0;
		}			
		if(K3 == 0)		 //����3����
		{
			Delay10ms(1);
			if(K3 == 0)
				num0++;
			while((n < 50)&&(K3 == 0))
			{
				n++;
				Delay10ms(1);	
			}			
			n=0;
			if(num0==256)
				num0=0;
		}
			
		if(K4 == 0)		 //����4����
		{
			Delay10ms(1);
			if(K4 == 0)
				num0 = 0;
			while((n < 50) && (K4 == 0))
			{
				n++;
				Delay10ms(1);	
			}			
			n=0;
		}
					
		DisplayData[0] = GPIO_DIG_CODE[num1/1000];//ǧλ
		DisplayData[1] = GPIO_DIG_CODE[num1%1000/100];//��λ
		DisplayData[2] = GPIO_DIG_CODE[num1%1000%100/10];//ʮλ
		DisplayData[3] = GPIO_DIG_CODE[num1%1000%100%10];//��λ
		DisplayData[4] = GPIO_DIG_CODE[num0/1000];//ǧλ
		DisplayData[5] = GPIO_DIG_CODE[num0%1000/100];//��λ
		DisplayData[6] = GPIO_DIG_CODE[num0%1000%100/10];//ʮλ
		DisplayData[7] = GPIO_DIG_CODE[num0%1000%100%10];	
	}
}									 
/*******************************************************************************
* �� �� ��         : Timer0Configuration()
* ��������		   : ���ü�ʱ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Timer0Configuration()
{
	TMOD=0X02;  //ѡ��Ϊ��ʱ��ģʽ��������ʽ2������TRX��������

	TH0=0X9C;	//����ʱ������ֵ����ʱ100us
	TL0=0X9C;	
	ET0=1;      //�򿪶�ʱ��0�ж�����
	EA=1;       //�����ж�
	TR0=1;      //�򿪶�ʱ��		
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

/*******************************************************************************
* �� �� ��         : void At24c02Write(unsigned char addr,unsigned char dat)
* ��������		   : ��24c02��һ����ַд��һ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void At24c02Write(unsigned char addr,unsigned char dat)
{
	I2C_Start();
	I2C_SendByte(0xa0, 1);//����д������ַ
	I2C_SendByte(addr, 1);//����Ҫд���ڴ��ַ
	I2C_SendByte(dat, 0);	//��������
	I2C_Stop();
}
/*******************************************************************************
* �� �� ��         : unsigned char At24c02Read(unsigned char addr)
* ��������		   : ��ȡ24c02��һ����ַ��һ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

unsigned char At24c02Read(unsigned char addr)
{
	unsigned char num;
	I2C_Start();
	I2C_SendByte(0xa0, 1); //����д������ַ
	I2C_SendByte(addr, 1); //����Ҫ��ȡ�ĵ�ַ
	I2C_Start();
	I2C_SendByte(0xa1, 1); //���Ͷ�������ַ
	num=I2C_ReadByte(); //��ȡ����
	I2C_Stop();
	return num;	
}
/*******************************************************************************
* �� �� ��         : GPIO_DIGDisplayDatalay() interrupt 1
* ��������		   : �ж��������ʾ
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void GPIO_DIGDisplayDatalay() interrupt 1
{
//��ʱ���ڹ�����ʽ�����Զ���װ�������Բ����ڸ�ֵ��
//	TH0=0X9c;//����ʱ������ֵ����ʱ1ms
//	TL0=0X00;		
	GPIO_DIG=0; //����
	switch(Num)	 //λѡ��ѡ�����������ܣ�
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
	GPIO_DIG = DisplayData[Num]; //��ѡ��ѡ����ʾ�����֡�
	Num++;
	if(Num>7)
	{
		Num=0;
	}
	
}