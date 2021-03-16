/*******************************************************************************
*                 
*                 		       ���пƼ�
--------------------------------------------------------------------------------
* ʵ �� ��		 : 24C02EEPROM�洢����
* ʵ��˵��       : ʹ��LCD1602��ʾд������ݺͶ���������
* ���ӷ�ʽ       : ������ͼ
* ע    ��		 : 
*******************************************************************************/
#include<reg51.h>
#include"i2c.h"
#include"lcd.h"

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
unsigned char wordCode0[6] = "write:";
unsigned char wordCode1[6] = " read:"; 

//--����ȫ�ֺ���--//
void At24c02Write(unsigned char ,unsigned char );
unsigned char At24c02Read(unsigned char );
void Delay10ms(unsigned int c);   //��� 0us


/*******************************************************************************
* ������         : main
* ��������		 : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{
	unsigned int num0 = 0,num1 = 0,n;

	LcdInit();

	LcdWriteCom(0x80);
	for(n=0; n<6; n++)
	{
		LcdWriteData(wordCode0[n]);
	}
	LcdWriteCom(0x80 + 0x40);
	for(n=0; n<6; n++)
	{
		LcdWriteData(wordCode1[n]);
	}
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

		LcdWriteCom(0x87);		
		LcdWriteData('0' + (num0/1000));//ǧλ		
		LcdWriteData('0' + (num0%1000/100));//��λ					
		LcdWriteData('0' + (num0%1000%100/10));//ʮλ
		LcdWriteData('0' + (num0%1000%100%10));//��λ

		LcdWriteCom(0x87 + 0x40);
		LcdWriteData('0' + (num1/1000));//ǧλ		
		LcdWriteData('0' + (num1%1000/100));//��λ					
		LcdWriteData('0' + (num1%1000%100/10));//ʮλ
		LcdWriteData('0' + (num1%1000%100%10));//��λ
			
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
