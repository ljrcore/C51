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
//名称: 按键扫描函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130924
//---------------------------------------
unsigned char ScanKey(void)
{
	 //***4×4矩阵按键扫描部分***
    //按K1-K16键，返回参数1-16
	 P1=0xFE;                  	//将第一行置零，以扫描K1-K4是否被按下
    if(P1_4==0) return 1;     	//如果K1键按下，返回1
    else if(P1_5==0) return 2; 	//如果K2键按下，返回2
    else if(P1_6==0) return 3; 	//如果K3键按下，返回3
    else if(P1_7==0) return 4; 	//如果K4键按下，返回4

    P1=0xFD;                  	//将第二行置零，以扫描K5-K8是否被按下
    if(P1_4==0) return 5;     	//如果K5键按下，返回5
    else if(P1_5==0) return 6; 	//如果K6键按下，返回6
    else if(P1_6==0) return 7; 	//如果K7键按下，返回7
    else if(P1_7==0) return 8; 	//如果K8键按下，返回8

    P1=0xFB;                  	//将第三行置零，以扫描K9-K12是否被按下
    if(P1_4==0) return 9;     	//如果K9键按下，返回9
    else if(P1_5==0) return 10;  //如果K10键按下，返回10
    else if(P1_6==0) return 11;  //如果K11键按下，返回11
    else if(P1_7==0) return 12;  //如果K12键按下，返回12

    P1=0xF7;                  	//将第四行置零，以扫描K13-K16是否被按下
    if(P1_4==0) return 13;     	//如果K13键按下，返回13
    else if(P1_5==0) return 14;  //如果K14键按下，返回14
    else if(P1_6==0) return 15;  //如果K15键按下，返回15
    else if(P1_7==0) return 16;  //如果K16键按下，返回16

	 return 0;                    //如果无按键按下，返回0
}

//---------------------------------------
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130924
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{    
	unsigned char k; 
	unsigned char d;
	unsigned char c;
	unsigned char k5con;
	unsigned int f=0;
	unsigned int keycon;
	bit keybit;

	f=0;
   while(1)               //死循环,单片机初始化后,将一直运行这个死循环
   {
		k=ScanKey();
 		if(k==0)          	//如果无键按下
		{
			k5con=0;
			if(keybit==0)
			{
				if(++keycon>50) //消除抖动参数，越大消抖效果越好，但是按键越不灵敏
				{
					keycon=0;
					keybit=1;
				}
			}
			else
				keycon=0;			
		}	   
		else if(k==1)      	//如果K1键按下,每次加1
		{
			if(keybit==1)  	//如果标志位有效，说明这个是有效按键
			{
				keybit=0;  		//清除标志位，以保证每次按键只处理一次
				if(f<9999) f++;
			}
	   }			
		else if(k==2)      	//如果K2键按下,每次减1
		{
			if(keybit==1)  	//如果标志位有效，说明这个是有效按键
			{
				keybit=0;  		//清除标志位，以保证每次按键只处理一次
				if(f>0) f--;
			}
	   }
		else if(k==5)      	//如果K5键按下,连续加
		{
			if(keybit==1)  	//如果标志位有效，说明这个是有效按键
			{				
				if(++k5con>250)
				{
					k5con=0;
					if(f<9999) f++;
				}
			}
	   }
		else if(k==6)      	//如果K6键按下,连续减
		{
			if(keybit==1)  	//如果标志位有效，说明这个是有效按键
			{				
				if(++k5con>250)
				{
					k5con=0;
					if(f>0) f--;
				}
			}
	   }
		for(c=0;c<250;c++);//做一个0-250的循环，不执行其他操作，只为延时
      
      P2=0;              //关一次显示，以免显示出鬼影
      if(++d>3) d=0;     //先将d加1，然后判断是否大于3，大于3归零
      if(d==0)           //如果d=0,显示千位
      {
          P0=0x03;       //U16A0=1,U16A1=1,U16A2=0选通数码管的千位进行显示
          P2=LED[f/1000];//将要显示的f的千位提取出来查表后送显示 
      }
      else if(d==1)      //如果d=1,显示百位
      {
          P0=0x02;       //U16A0=0,U16A1=1,U16A2=0选通数码管的百位进行显示
          P2=LED[(f%1000)/100];    //将要显示的f的百位提取出来查表后送显示
      }
      else if(d==2)      //如果d=2,显示十位
      {
          P0=0x01;       //U16A0=1,U16A1=0,U16A2=0选通数码管的十位进行显示
          P2=LED[(f%100)/10];      //将要显示的f的十位提取出来查表后送显示
      }
      else               //如果d=3,显示个位
      {
          P0=0x00;       //U16A0=0,U16A1=0,U16A2=0选通数码管的个位进行显示
          P2=LED[f%10];            //将要显示的f的个位提取出来查表后送显示
      }
   }
}

