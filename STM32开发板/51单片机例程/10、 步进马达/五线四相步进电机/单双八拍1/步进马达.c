/*************************************************************************************
*  标题:  步进电机试验二															 *
* 																					 *
*    通过本例程了解步进马达使用及驱动程序编写										 *
*;   单双八拍工作方式：                                                           	 *
*;   A-AB-B-BC-C-CD-D-DA (即一个脉冲,转 3.75 度)      								 *
*    J14短路冒需断开                  	                                             *
*  请学员一定要消化掉本例程                       	                            	 *
                    	                           *								 *
**************************************************************************************/    
 

#include "reg52.h"
unsigned char code RUN[8]={0xf1,0xf3,0xf2,0xf6,0xf4,0xfc,0xf8,0xf9};  //步进电机相序表
void delay(unsigned int t);


//步进电机驱动
void  motor_ffw()
 { 
   unsigned char i;
  
      for (i=0; i<8; i++)       //一个周期转3.75*8=30度
        {
          P1 = RUN[i]&0x1f;     //取数据
          delay(100);             //调节转速
        }
     } 

/******延时函数****************/
void delay(unsigned int t)
{                           
   unsigned int k;
   while(t--)
   {
     for(k=0; k<60; k++)//用for的空循环延长程序的执行时间
     { }
   }
}


main() 
{ 
    while(1)
	{
	  motor_ffw(); //调用旋转处理函数

	 }
}

