////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件

//---------------------------------------
//数码管字形表，供显示时查询
unsigned char code LED[10]=
{                          //定义表格一定要使用code，这样会做到程序存储区中
    0x3F,                  //"0"的字形表，0B00111111
    0x06,                  //"1"的字形表，0B00000110
    0x5B,                  //"2"的字形表，0B01011011
    0x4F,                  //"3"的字形表，0B01001111
    0x66,                  //"4"的字形表，0B01100110
    0x6D,                  //"5"的字形表，0B01101101
    0x7D,                  //"6"的字形表，0B01111101
    0x07,                  //"7"的字形表，0B00000111
    0x7F,                  //"8"的字形表，0B01111111
    0x6F,                  //"9"的字形表，0B01101111
};

//---------------------------------------
//4位数码管相关I/O设置
sbit U165A0=P1^0;           //U165(74HC138)的A0脚接在P1.0口上
sbit U165A1=P1^1;           //U165(74HC138)的A1脚接在P1.1口上
sbit U165A2=P1^2;           //U165(74HC138)的A2脚接在P1.2口上
//---------------------------------------

//---------------------------------------
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20131121
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{

    unsigned char c=0;     //定义一个char型变量，做延时用
    unsigned char d=0;     //定义一个char型变量，控制显示位置
    unsigned char e=0;     //定义一个char型变量，做延时用
    unsigned long  f=0;     //定义一个long型变量，显示内容用，显示内容0-99999

    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {
        for(c=0;c<250;c++);//做一个0-250的循环，不执行其他操作，只为延时
        if(++e>200)        //做一个延时，时间到将显示内容加1
        {
            e=0;           //清零，为下一次延时做准备
            if(++f>99999) f=0;//显示内容加1，因为只有4位显示，超过99999后归零
        }
        P2=0;              //关一次显示，以免显示出鬼影
		P0=LED[f/10000];   //显示万位
        if(++d>3) d=0;     //先将d加1，然后判断是否大于3，大于3归零
	 	if(d==0)           //如果d=0,显示千位
        {
            P1=0x03;       //U16A0=1,U16A1=1,U16A2=0选通数码管的千位进行显示
            P2=LED[(f%10000)/1000];          //将要显示的f的千位提取出来查表后送显示 
        }
        else if(d==1)      //如果d=1,显示百位
        {
            P1=0x02;       //U16A0=0,U16A1=1,U16A2=0选通数码管的百位进行显示
            P2=LED[(f%1000)/100];    //将要显示的f的百位提取出来查表后送显示
        }
        else if(d==2)      //如果d=2,显示十位
        {
            P1=0x01;       //U16A0=1,U16A1=0,U16A2=0选通数码管的十位进行显示
            P2=LED[(f%100)/10];      //将要显示的f的十位提取出来查表后送显示
        }
        else             //如果d=3,显示个位
        {
            P1=0x00;       //U16A0=0,U16A1=0,U16A2=0选通数码管的个位进行显示
            P2=LED[f%10];            //将要显示的f的个位提取出来查表后送显示
        }	
    }
}


