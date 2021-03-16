/* io分配:                                    			*
;*   OUTPUT:                                                    *
;*      P1.0 ...... 模拟量输入					*
;*      P1.1 ...... DA输入比较基准电压				*
;*      P1.2~7..... R-2R DA电阻网络				*
;*      P3.7 ...... LED 模拟亮度输出				*
;* CPU CLOCK EQU 6M                                             */
//xiaoqi last edit in 2001.11
//#pragma src 
#include "AT89x051.h"
#include <stdlib.h>
#include<math.h>
#include<intrins.h>

//变量类型标识的宏定义，大家都喜欢这么做
#define	Uchar unsigned char
#define Uint unsigned int

#define Ledlight() (P3 &= 0x7f)
#define Leddark()  (P3 |= 0x80)

sbit	P36	= P3^6;		// 比较器内部判断脚
sbit	LED	= P3^7;		// 一个发光二级管观察亮度变化

// 内部标志位定义
bit	less;			// 比较是否大于 1.小于，0.大于

// 全局变量定义
Uchar	timer1,		        // 通用延时计数器
	timer2,		        // 按键蜂鸣器反应定时器
	adcdata,		// ad转换变量
	pwm1;			// PWM输出比例

// 函数列表
void DelayMs(unsigned int number);      // 毫秒延时
void timers0();			        // 在定时器中断中做数码管的扫描显示(ct0)
void Initall(void);		        // 系统初始化
void timers1(void);		        // TC1定时器中断用于扫描显示与键盘
Uchar adcread(void);			// adc转换程序

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

// 毫秒延时
void DelayMs(unsigned int number) 
{
	unsigned char temp;

	for(;number!=0;number--) 
		for(temp=112;temp!=0;temp--);
}

/*************************************
   在定时器中断中做LED的PWM输出
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
;* 6位 ADC转换
;****************/
Uchar adcread(void)
{
	Uchar i=0x3f,temp=0;
	P36 =1;
	P1 = 3; _nop_();_nop_();		// 从零开始
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
;* 系统初始化
;****************/
void Initall(void)
{
	TMOD = 0x11;		// 0001 0001 16进制计数器
	IP = 0x8;		// 0000 1000 t1优先
        IE = 0x8A;		// 1000 1010 t0,t1中断允许
	TCON = 5;		// 0000 0101 外部中断低电平触发
        TR0 = 1;		// 打开定时器中断，IE中已经打开，在明示一下
	TR1 = 0;
        ET0 = 1;
	ET1 = 0;
        P1 = 0xff;
}
 
/*************************************
   TC1定时器中断用于扫描显示与键盘(ct1)
*************************************/
void timers1(void) interrupt 3 using 2 
{
_nop_();		//实验中没有启用
}

