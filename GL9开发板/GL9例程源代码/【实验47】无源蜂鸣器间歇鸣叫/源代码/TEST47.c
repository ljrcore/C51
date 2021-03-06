////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件

unsigned int k;
unsigned int m;
bit S2bit;              //设置一个位变量，该位写1，蜂鸣器鸣叫，否则停止

//---------------------------------------
//名称：定时器0中断服务程序
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void Timer0(void) interrupt 1 
{                          //定时1000微秒
    TL0=0xCC;              //重新给TL0赋初值
    TH0=0xF8;              //重新给TH0赋初值

    //***此处用户自行添加定时器T0中断处理程序***
	if(S2bit==1)          //如果标志位为1，启动蜂鸣器
 		P1_2=~P1_2;       //1000us改变一次状态，周期为2000us，频率为500HZ
	else
		P1_2=1;            //如果标志位为0，关闭蜂鸣器
    //******************************************

}

//---------------------------------------
//名称: 蜂鸣器函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//--------------------------------------- 
void fengpro(void)
{
	if(S2bit==1)         //如果蜂鸣器鸣叫后，启动定时关闭蜂鸣器鸣叫
	{
		if(++m>2000)   //鸣叫时长为2000个循环周期
		{
			m=0;
			S2bit=0;	  //关闭蜂鸣器鸣叫				
		}		 	
	}		
}

//---------------------------------------
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{

    //***定时器Timer0初始化***
    TMOD&=0xF0;            //将TMOD的低4位定时器0控制部分清零
    TMOD|=0x01;            //设置定时器0为方式1
    TL0=0xCC;              //设置定时器0初值低8位
    TH0=0xF8;              //设置定时器0初值高8位
    TR0=1;                 //启动定时器0
    ET0=1;                 //Timer0中断允许
    //**********************

    //***开全局中断设置****
    //定时器Timer0设置了中断允许,此处要开全局中断
    EA=1;                  //开全局中断
    //*********************

    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {
		if(++k>60000)     //60000个循环后，启动一次蜂鸣器鸣叫
		{
			k=0;
			S2bit=1;      //启动鸣叫
		}
		fengpro();       //调用蜂鸣器处理函数
    }
}
