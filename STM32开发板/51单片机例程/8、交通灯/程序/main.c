//
/*******************************************************************************
* ʵ����			   : ��̬��ʾ�����ʵ��
* ʹ�õ�IO	     : 
* ʵ��Ч��       : �������ʾ76543210��
*	ע��					 ����λѡ��P1�ڵ�ʱ��ע����ܻ���һλ��������ô����J21
*******************************************************************************/
#include<reg51.h>

//--����ʹ�õ�IO��--//
#define GPIO_DIG   P0
#define GPIO_PLACE P1

#define GPIO_TRAFFIC P2

sbit RED10   = P2^0;   //�����е����
sbit GREEN10 = P2^1;   //�����е��̵�
sbit RED11   = P2^2;
sbit YELLOW11= P2^3;
sbit GREEN11 = P2^4;

sbit RED00   = P3^0;	//�����е����
sbit GREEN00 = P3^1;	//�����е��̵�
sbit RED01   = P2^5;
sbit YELLOW01= P2^6;
sbit GREEN01 = P2^7;

//--����ȫ�ֱ���--//
unsigned char code DIG_PLACE[8] = {
0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};//λѡ����   ���ķ�������
unsigned char code DIG_CODE[17] = {
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0��1��2��3��4��5��6��7��8��9��A��b��C��d��E��F����ʾ��
unsigned char DisplayData[8];
//�������Ҫ��ʾ��8λ����ֵ
unsigned char Time, Second;		  //������Ŷ�ʱʱ��

//--����ȫ�ֺ���--//
void DigDisplay(); //��̬��ʾ����
void Timer0Cofig(void);

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void main(void)
{
	Second = 1;

	Timer0Cofig();

	while(1)
	{
		if(Second == 70)
		{
			Second = 1;
		}

		//--����·ͨ�У�30��--//
		if(Second < 31)
		{
			DisplayData[0] = 0x00;
			DisplayData[1] = 0x00;
			DisplayData[2] = DIG_CODE[(30 - Second) % 100 / 10];
			DisplayData[3] = DIG_CODE[(30 - Second) %10];
			DisplayData[4] = 0x00;
			DisplayData[5] = 0x00;
			DisplayData[6] = DisplayData[2];
			DisplayData[7] = DisplayData[3];
			DigDisplay();

			//--����·ͨ��--//

			GPIO_TRAFFIC = 0xFF;  //�����еĵ�Ϩ��
			RED00 = 1;
			GREEN00 = 1;

			GREEN11 = 0;    //����·�̵���			
			GREEN10	= 0;    //����·���е��̵���

			RED01 = 0;      //ǰ��·�����
			RED00 = 0;      //ǰ��·���е������
		}

		//--�ƵƵȴ��л�״̬��5��--//
		else if(Second < 36) 
		{
			DisplayData[0] = 0x00;
			DisplayData[1] = 0x00;
			DisplayData[2] = DIG_CODE[(35 - Second) % 100 / 10];
			DisplayData[3] = DIG_CODE[(35 - Second) %10];
			DisplayData[4] = 0x00;
			DisplayData[5] = 0x00;
			DisplayData[6] = DisplayData[2];
			DisplayData[7] = DisplayData[3];
			DigDisplay();

			//--�Ƶƽ׶�--//

			GPIO_TRAFFIC = 0xFF;  //�����еĵ�Ϩ��
			RED00 = 1;
			GREEN00 = 1;

			YELLOW11 = 0;    //����·�Ƶ���			
			RED10	= 0;     //����·���е������

			YELLOW01 = 0;    //ǰ��·�����
			RED00 = 0;       //ǰ��·���е������
		}

		//--ǰ��·ͨ��--//
		else if(Second < 66) 
		{
			DisplayData[0] = 0x00;
			DisplayData[1] = 0x00;
			DisplayData[2] = DIG_CODE[(65 - Second) % 100 / 10];
			DisplayData[3] = DIG_CODE[(65 - Second) %10];
			DisplayData[4] = 0x00;
			DisplayData[5] = 0x00;
			DisplayData[6] = DisplayData[2];
			DisplayData[7] = DisplayData[3];
			DigDisplay();

			//--�Ƶƽ׶�--//

			GPIO_TRAFFIC = 0xFF;  //�����еĵ�Ϩ��
			RED00 = 1;
			GREEN00 = 1;

			RED11 = 0;       //����·�����			
			RED10 = 0;       //����·���е������

			GREEN01 = 0;     //ǰ��·�̵���
			GREEN00 = 0;     //ǰ��·���е��̵���
		}

		//--�ƵƵȴ��л�״̬��5��--//
		else 
		{
			DisplayData[0] = 0x00;
			DisplayData[1] = 0x00;
			DisplayData[2] = DIG_CODE[(70 - Second) % 100 / 10];
			DisplayData[3] = DIG_CODE[(70 - Second) %10];
			DisplayData[4] = 0x00;
			DisplayData[5] = 0x00;
			DisplayData[6] = DisplayData[2];
			DisplayData[7] = DisplayData[3];
			DigDisplay();

			//--�Ƶƽ׶�--//

			GPIO_TRAFFIC = 0xFF;  //�����еĵ�Ϩ��
			RED00 = 1;
			GREEN00 = 1;

			YELLOW11 = 0;    //����·�Ƶ���			
			RED10	= 0;     //����·���е������

			YELLOW01 = 0;    //ǰ��·�����
			RED00 = 0;       //ǰ��·���е������
		}
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


	for(i=0; i<8; i++)
	{
		GPIO_PLACE = DIG_PLACE[i];	   //����λѡ
		GPIO_DIG = DisplayData[i];     //���Ͷ���
		j = 10;						   //ɨ����ʱ���趨
		while(j--);	
		GPIO_DIG = 0x00;               //����
	}
}

/*******************************************************************************
* �� �� ��         : Timer0Cofig
* ��������		   : ���ö�ʱ��
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/

void Timer0Cofig(void)
{
	TMOD = 0x01;     //��ʱ��0ѡ������ʽ1
    TH0  = 0x3C;	 //���ó�ʼֵ,��ʱ50MS
    TL0  = 0xB0; 
    EA   = 1;	     //�����ж�
    ET0  = 1;		 //�򿪶�ʱ��0�ж�
    TR0  = 1;		 //������ʱ��0	
}

/*******************************************************************************
* �� �� ��         : Timer0
* ��������		   : ��ʱ��0�жϺ���
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/		   

void Timer0() interrupt 1
{
	TH0 = 0x3C;	 //���ó�ʼֵ
	TL0 = 0xB0;
	Time++;
	if(Time == 20)
	{
		Second ++;
		Time = 0;
	}
}
