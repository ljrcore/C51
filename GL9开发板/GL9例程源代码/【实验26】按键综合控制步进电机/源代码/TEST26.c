#include <AT89X52.h>       //调用51单片机的头文件

sbit P1key=P2^0;           //按键P1接在P2.0口上
sbit P2key=P2^1;           //按键P2接在P2.1口上
sbit P3key=P2^2;           //按键P3接在P2.2口上
sbit P4key=P2^3;           //按键P4接在P2.3口上
sbit P5key=P2^4;           //按键P5接在P2.4口上
sbit P6key=P2^5;           //按键P6接在P2.5口上
sbit P7key=P2^6;           //按键P7接在P2.6口上
sbit P8key=P2^7;           //按键P8接在P2.7口上
//---------------------------------------
//定义一个数据表格
unsigned char code TAB[8]=
{                          //定义表格一定要使用code，这样会做到程序存储区中
    0x77,                  //表格第1步数据0b 01110111
    0x33,                  //表格第2步数据0b 00110011
    0xBF,                  //表格第3步数据0b 10111011
    0x9F,                  //表格第4步数据0b 10011001
    0xDF,                  //表格第5步数据0b 11011101
    0xCF,                  //表格第6步数据0b 11001100
    0xEF,                  //表格第7步数据0b 11101110
    0x6F,                  //表格第8步数据0b 01100110
};

//---------------------------------------
//8独立按键相关I/O设置

//---------------------------------------

//---------------------------------------
//按键部分用寄存器设置
unsigned char KEYbuf;      //设置8位的寄存器用来暂存按键键值数据
unsigned char KEYcon;
bit KEYbit;
//---------------------------------------
bit STEPbit;
bit ZFbit;
unsigned char STEPspeed;
//---------------------------------------
//名称: 主函数

//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{

    unsigned int a=0;      //定义一个int型变量，做延时用
    unsigned char b=0;    //定义一个char型变量，显示内容用

    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {
		//***8独立按键扫描部分***
    //按P1-P8键，KEYbuf赋值1-8
        if(P1key==0) KEYbuf=1;     //如果P1键按下，KEYbuf赋值写1
        else if(P2key==0) KEYbuf=2; //如果P2键按下，KEYbuf赋值写2
        else if(P3key==0) KEYbuf=3; //如果P3键按下，KEYbuf赋值写3
        else if(P4key==0) KEYbuf=4; //如果P4键按下，KEYbuf赋值写4
        else if(P5key==0) KEYbuf=5; //如果P5键按下，KEYbuf赋值写5
        else if(P6key==0) KEYbuf=6; //如果P6键按下，KEYbuf赋值写6
        else if(P7key==0) KEYbuf=7; //如果P7键按下，KEYbuf赋值写7
        else if(P8key==0) KEYbuf=8; //如果P8键按下，KEYbuf赋值写8
		  else 
		  {
			KEYbuf=0;
		  	if(KEYbit==0)
			{
				if(++KEYcon>100)
				{
					KEYcon=0;
		  			KEYbit=1;              //无按键按下，KEYbit赋值为1
				}
			}
		}
    //*********************    
    	
		if(KEYbuf==1)               //P1键控制步进电机启停
		{			
			if(KEYbit==1)
			{
				KEYbit=0;
				STEPbit=!STEPbit;     //步进电机启动标志位	
 			}			
		}
		if(KEYbuf==2)               //P2键控制步进电机转向
		{		
			if(KEYbit==1)
			{				
				ZFbit=!ZFbit;     	 //步进电机转向标志位	 
				P1=0xFF;    			//关闭步进电机	
			}			
		}
		if(KEYbuf==3)               //P3键控制步进电机转速
		{			
			if(KEYbit==1)
			{				
				if(++STEPspeed>3) STEPspeed=0;     //速度加1，并限制在0-3间	 			
			}		
		}		

		if(STEPspeed==0) 
		{
			for(a=0;a<1700;a++); 		//速度1延时
		}
		else if(STEPspeed==1) 
		{
			for(a=0;a<1300;a++); 		//速度2延时
		}
		else if(STEPspeed==2) 
		{
			for(a=0;a<900;a++); 			//速度3延时		
		}
		else  
		{
			for(a=0;a<500;a++); 			//速度4延时
		}
		if(STEPbit==1)
		{
			if(ZFbit==1)
			{
				if(++b>7) b=0;     	    //b做+1操作，并限制在0-7以内        
			}
			else
			{
				if(b==0) b=7;     	 //并限制在0-7以内     
				else b--;     	    //b做-1操作			   	
			}
        	P1=TAB[b]; 				//将TAB[b]的值送入P1口输出
		}
		else
		{
			P1=0xFF;    			//关闭步进电机	
		}
   }
}



