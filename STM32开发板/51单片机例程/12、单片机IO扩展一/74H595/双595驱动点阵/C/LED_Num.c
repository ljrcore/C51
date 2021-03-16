/*********************************************************************************************
*																                             *
*	                        双595驱动LED点阵实验 										     *
*                             		                                                         *
*	说明： 点阵的红绿接口分别接在595的输出端口JP2和P595									     *
*   现象：(流动显示1 2 3 4 5 6 7 8 9)													     *
*   实验目的：掌握LED点阵的动作原理和74HC595的级联控制							             *
*             要求学员掌握 LED点阵的工作原理和 各点阵脚的定义及接法，具体接线请参考接线说明  *
**********************************************************************************************/
	
#include<reg51.h>
#include <intrins.h>

#define  NOP() _nop_()  /* 定义空指令 */

//SPI IO
sbit MOSIO =P3^4;   	 //定义管脚
sbit R_CLK =P3^5;        //定义管脚
sbit S_CLK =P3^6;        //定义管脚

void HC595SendData(unsigned int SendVal);	  //595驱动函数声明
void delay(unsigned char ms); 
	
	void main(void)
	{
	  while(1)
	  {
		 P0 = 0xff;
		 HC595SendData(0x00ff);
		 delay(250); delay(250);delay(250);delay(250);
		 P0 = 0xff;
		 HC595SendData(0xff00);
		 delay(250);delay(250);delay(250);delay(250);
		 P0 =  0x00;
		 HC595SendData(0x0000);
		 delay(250); delay(250);delay(250);delay(250);
	  }

    }
/*********************************************************************************************************
** 函数名称: HC595SendData
** 功能描述: 向SPI总线发送数据
*********************************************************************************************************/
void HC595SendData(unsigned int SendVal)
{  
  unsigned char i;
		
  for(i=0;i<16;i++) 
   {
	if((SendVal<<i)&0x8000) MOSIO=1; //set dataline high  0X8000  最高位与SendVal左移的最高位 进行逻辑运算
	else MOSIO=0;				   // 如果为真 MOSIO = 1  
 
	S_CLK=0;
	NOP();
	NOP();
	S_CLK=1;	
   }
   
	
  R_CLK=0; //set dataline low
  NOP();
  NOP();
  R_CLK=1; //片选

}

void delay(unsigned char ms)
{
  unsigned char i,j;
  for(i = 0;i < ms;i++)
    for(j= 0;j<110;j++);
}
	
