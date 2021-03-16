/* io����:                                    			*
;*   OUTPUT:                                                    *
;*      P1.0 ...... ģ��������					*
;*      P1.1 ...... DA����Ƚϻ�׼��ѹ				*
;*      P1.2~7..... R-2R DA��������				*
;*      P3.7 ...... LED ģ���������				*
;* CPU CLOCK EQU 6M                                             */
//xiaoqi last edit in 2001.11
//#pragma src 
#include "AT89x051.h"
#include <stdlib.h>
#include<math.h>
#include<intrins.h>

//�������ͱ�ʶ�ĺ궨�壬��Ҷ�ϲ����ô��
#define	Uchar unsigned char
#define Uint unsigned int

#define Ledlight() (P3 &= 0x7f)
#define Leddark()  (P3 |= 0x80)

sbit	P36	= P3^6;		// �Ƚ����ڲ��жϽ�
sbit	LED	= P3^7;		// һ����������ܹ۲����ȱ仯

// �ڲ���־λ����
bit	less;			// �Ƚ��Ƿ���� 1.С�ڣ�0.����

// ȫ�ֱ�������
Uchar	timer1,		        // ͨ����ʱ������
	timer2,		        // ������������Ӧ��ʱ��
	adcdata,		// adת������
	pwm1;			// PWM�������

// �����б�
void DelayMs(unsigned int number);      // ������ʱ
void timers0();			        // �ڶ�ʱ���ж���������ܵ�ɨ����ʾ(ct0)
void Initall(void);		        // ϵͳ��ʼ��
void timers1(void);		        // TC1��ʱ���ж�����ɨ����ʾ�����
Uchar adcread(void);			// adcת������

void main(void)  using 0
{
	DelayMs(120);
	Initall();
	pwm1 = adcread();
	LED=1;
	while(1) 
	{
		pwm1 = adcread();
		timer2=10;
		while (timer2);
	}
}

// ������ʱ
void DelayMs(unsigned int number) 
{
	unsigned char temp;

	for(;number!=0;number--) 
		for(temp=112;temp!=0;temp--);
}

/*************************************
   �ڶ�ʱ���ж�����LED��PWM���
*************************************/
void timers0() interrupt 1 using 1 
{
	TH0 = 0xff;
	TL0 = 0xd0;
	timer1--;
	if (timer1==pwm1)LED=0;
	if (timer1==0){
		LED=1;
		timer1=0x40;
		timer2--;
		};
}

/****************
;* 6λ ADCת��
;****************/
Uchar adcread(void)
{
	Uchar i=0x3f,temp=0;
	P36 =1;
	P1 = 3; _nop_();_nop_();		// ���㿪ʼ
	while ((i--)&& (P36))
		{
		temp += 4;
		P1 = temp|3;
		_nop_(); 
		}
	temp >>= 2;
	return temp;
}

/****************
;* ϵͳ��ʼ��
;****************/
void Initall(void)
{
	TMOD = 0x11;		// 0001 0001 16���Ƽ�����
	IP = 0x8;		// 0000 1000 t1����
        IE = 0x8A;		// 1000 1010 t0,t1�ж�����
	TCON = 5;		// 0000 0101 �ⲿ�жϵ͵�ƽ����
        TR0 = 1;		// �򿪶�ʱ���жϣ�IE���Ѿ��򿪣�����ʾһ��
	TR1 = 0;
        ET0 = 1;
	ET1 = 0;
        P1 = 0xff;
}
 
/*************************************
   TC1��ʱ���ж�����ɨ����ʾ�����(ct1)
*************************************/
void timers1(void) interrupt 3 using 2 
{
_nop_();		//ʵ����û������
}

