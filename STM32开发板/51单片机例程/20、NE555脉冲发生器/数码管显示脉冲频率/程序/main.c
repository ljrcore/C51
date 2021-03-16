/*******************************************************************************
*                 
*                 		       普中科技
--------------------------------------------------------------------------------
* 实 验 名		 : NE555脉冲计数显示试验
* 实验说明       : 数码管显示接收到的脉冲频率。
* 连接方式       : 见连接图
* 注    意		 : 
*******************************************************************************/

#include<reg51.h>

//--定义使用的IO--//
#define GPIO_DIG P0

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

//--定义全局变量--//
unsigned char code DIG_CODE[17]={
0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0、1、2、3、4、5、6、7、8、9、A、b、C、d、E、F的显示码
unsigned char DisplayData[8];
//用来存放要显示的8位数的值

//--声明全局函数--//
void DigDisplay(); //动态显示函数
void TIMER_Configuration();	//初始化定时器

//--定义全局变量--//
unsigned long   Freq;        //用来存放要显示的频率值
unsigned long	TimeCount;   //用于计算1S钟的
/*******************************************
*函数名		：main
*功  能 	：主函数
*输	 入 	：无
*输  出		：无
*******************************************/

void main()
{

	TIMER_Configuration();
	
	while(1)
	{
		if(TR0 == 0)         //当计数器停下的时候，表明计数完毕
		{
			Freq = Freq + TL1;         //读取TL的值
			Freq = Freq + (TH1 * 256); //读取TH的值

			//--求频率的个十百千万十万位--//
			DisplayData[0] = DIG_CODE[Freq%1000000/100000];	
			DisplayData[1] = DIG_CODE[Freq%100000/10000];	
			DisplayData[2] = DIG_CODE[Freq%10000/1000];	
			DisplayData[3] = DIG_CODE[Freq%1000/100];	
			DisplayData[4] = DIG_CODE[Freq%100/10];	
			DisplayData[5] = DIG_CODE[Freq%10];
			
			//--显示完，重新计算下一次频率。--//	
			Freq = 0;//将计算的频率清零
			TH1 = 0; //将计数器的值清零
			TL1 = 0;
			TR0 = 1; //开启定时器
			TR1 = 1; //开启计数器	
		}

		//--显示求得的数值--//
		DigDisplay();
	}
}

/*******************************************
*函数名		：TIMER_Configuration
*功  能 	：配置定时/计数器T0和T1
*输	 入 	：无
*输  出		：无
*******************************************/

void TIMER_Configuration()
{
	//--定时器T1做计数器，工作方式1（16位定时器），只由TRx打开计数器--//
	//--定时器T0做定时器，工作方式1（16位定时器），只由TRx打开定时器--//	
	TMOD=0x51;

	//--设置定时器晶振为12MHZ时定时50ms--//
	TH0=0x3C;
	TL0=0xB0;

	//--打开中断-//
	ET0=1;
	ET1=1;
	EA=1;

	//--打开定时器*/
	TR0=1;
	TR1=1;
}
/*******************************************
*函数名		：Timer0
*功  能 	：定时器0的中断函数
*输	 入 	：无
*输  出		：无
*******************************************/

void Timer0()	interrupt 1
{
	TimeCount++;
	if(TimeCount==20)//计时到1S
	{
		TR0=0;
		TR1=0;
		TimeCount=0;		
	}

	//--12MHZ设置定时50ms的初值--//
	TH0=0x3C;
	TL0=0xB0;	
}
/*******************************************
*函数名		：Timer1
*功  能 	：定时器1的中断函数
*输	 入 	：无
*输  出		：无
*******************************************/

void Timer1()	interrupt 3
{	
	//--进入一次中断，表明计数到了65536--//
	Freq=Freq+65536;		
}

/*******************************************************************************
* 函 数 名         : DigDisplay
* 函数功能		   : 使用数码管显示
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void DigDisplay()
{
	unsigned char i;
	unsigned int j;
	for(i=0;i<8;i++)
	{
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位	
		}
		GPIO_DIG=DisplayData[i];//发送段码
		j=50;						 //扫描间隔时间设定
		while(j--);	
		GPIO_DIG=0x00;//消隐
	}
}

