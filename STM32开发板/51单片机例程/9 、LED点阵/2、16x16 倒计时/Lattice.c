/*******************************************************************************
*                 
*                 		       普中科技
--------------------------------------------------------------------------------
* 实 验 名		 : LED点阵数字倒计时
* 实验说明       : 
* 连接方式       : 见接线图
* 注    意		 : 
*******************************************************************************/

#include <REG51.H>

//--重定义函数变量--//
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

//--定义SPI要使用的 IO--//
sbit MOSIO = P3^4;
sbit R_CLK = P3^5;
sbit S_CLK = P3^6;

//---全局变量声明--//
ulong column;   //点阵列
ulong row;      //点阵行
ulong dt;

//--点阵显示数组--//
uchar code tab0[] = 
{0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x08,
 0x00, 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x80,
 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x08, 0x00,
 0x10, 0x00, 0x20, 0x00, 0x40, 0x00, 0x80, 0x00}; 

//--10字模--//
uchar code tab1[] = 
{0, 0, 0, 0, 0, 0, 8, 24, 14, 36, 8, 66, 8, 66, 8, 66, 
 8, 66, 8, 66, 8, 66, 8, 36, 62, 24, 0, 0, 0, 0, 0, 0};

//--09字模--//
uchar code tab2[] = 
{0, 0, 0, 0, 0, 0, 24, 24, 36, 36, 66, 66, 66, 66, 66,
 66, 66, 100, 66, 88, 66, 64, 66, 64, 36, 36, 24, 28, 0, 0, 0, 0} ;

//--08字模--//
uchar code tab3[] = 
{0, 0, 0, 0, 0, 0, 24, 60, 36, 66, 66, 66, 66, 66, 66, 36,
66, 24, 66, 36, 66, 66, 66, 66, 36, 66, 24, 60, 0, 0, 0, 0};

//--07字模--//
uchar code tab4[] = 
{0, 0, 0, 0, 0, 0, 24, 126, 36, 34, 66, 34, 66, 16, 66, 16,
 66, 8, 66, 8, 66, 8, 66, 8, 36, 8, 24, 8, 0, 0, 0, 0};

//--06字模--//
uchar code tab5[] = 
{0, 0, 0, 0, 0, 0, 24, 56, 36, 36, 66, 2, 66, 2, 66, 26, 66,
 38, 66, 66, 66, 66, 66, 66, 36, 36, 24, 24, 0, 0, 0, 0};

//--05字模--//
uchar code tab6[] = 
{0, 0, 0, 0, 0, 0, 24, 126, 36, 2, 66, 2, 66, 2, 66, 26, 66,
 38, 66, 64, 66, 64, 66, 66, 36, 34, 24, 28, 0, 0, 0, 0};

//--04字模--//
uchar code tab7[] = 
{0, 0, 0, 0, 0, 0, 24, 32, 36, 48, 66, 40, 66, 36, 66, 36, 66,
34, 66, 34, 66, 126, 66, 32, 36, 32, 24, 120, 0, 0, 0, 0};

//--03字模--//
uchar code tab8[] = 
{0, 0, 0, 0, 0, 0, 24, 60, 36, 66, 66, 66, 66, 32, 66, 24, 66,
 32, 66, 64, 66, 64, 66, 66, 36, 34, 24, 28, 0, 0, 0, 0};

//--02字模--//
uchar code tab9[] = 
{0, 0, 0, 0, 0, 0, 24, 60, 36, 66, 66, 66, 66, 66, 66, 32, 66,
 32, 66, 16, 66, 8, 66, 4, 36, 66, 24, 126, 0, 0, 0, 0};

//--01字模--//
uchar code tab10[] = 
{0, 0, 0, 0, 0, 0, 24, 8, 36, 14, 66, 8, 66, 8, 66, 8, 66, 8, 66,
8, 66, 8, 66, 8, 36, 8, 24, 62, 0, 0, 0, 0};

//--00字模--//
uchar code tab11[] = 
{0, 0, 0, 0, 0, 0, 24, 24, 36, 36, 66, 66, 66, 66, 66, 66, 66, 66,
66, 66, 66, 66, 66, 66, 36, 36, 24, 24, 0, 0, 0, 0};

//--GO--//
uchar code tab12[] = 
{0, 0, 0, 0, 0, 0, 60, 28, 34, 34, 34, 65, 1, 65, 1, 65, 1, 65, 113,
 65, 33, 65, 34, 65, 34, 34, 28, 28, 0, 0, 0, 0};


//--全局函数声明--//
void HC595SendData(  uchar BT3, uchar BT2,uchar BT1,uchar BT0);
																							
/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void main(void)
{
	int k, i, ms;
	
	i = 60;					//显示时间									 
												  
	while(1)
	{
		//--显示10--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)										
			{	 
			HC595SendData(~tab1[2*k +1],~tab1[2*k],tab0[2*k],tab0[2*k + 1]);
			} 		 
		}
	
		//--清屏--//
		HC595SendData(0xff,0xff,0,0);										  							    
		
		//--显示09--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)											    
			{	 
				HC595SendData(~tab2[2*k +1],~tab2[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
	
		//--清屏--//
		HC595SendData(0xff,0xff,0,0);								      	
		
		//--显示08--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)												
			{	 
				HC595SendData(~tab3[2*k +1],~tab3[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		
		//--清屏--//	
		HC595SendData(0xff,0xff,0,0); 	
		
		//--显示07--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)						
			{	 
				HC595SendData(~tab4[2*k +1],~tab4[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		
		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);								      	  	
																			 
		//--显示06--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)												
			{	 
				HC595SendData(~tab5[2*k +1],~tab5[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		
		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);								      	 	
	
	    //--显示05--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)												//欢
			{	 
				HC595SendData(~tab6[2*k +1],~tab6[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);					      	
	
	    //--显示04--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)							
			{	 
				HC595SendData(~tab7[2*k +1],~tab7[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);					    
		
		//--显示03--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)							
			{	 
				HC595SendData(~tab8[2*k +1],~tab8[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);								
		
		//--显示02--//	
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)						
			{	 
				HC595SendData(~tab9[2*k +1],~tab9[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}

		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);									
		
		//--显示01--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)								
			{	 
				HC595SendData(~tab10[2*k +1],~tab10[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		
		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);								    	

		//--显示00--//
		for(ms = i; ms > 0; ms--)
		{
			for(k = 0; k < 16; k++)							
			{	 
				HC595SendData(~tab11[2*k +1],~tab11[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}
		}
		//--清屏--//	
		HC595SendData(0xff,0xff,0,0);								      	  //清屏
	
	    //--一直显示G0--//
		while(1)
		{
			for(k = 0; k < 16; k++)												//中
			{	 
				HC595SendData(~tab12[2*k +1],~tab12[2*k],tab0[2*k],tab0[2*k + 1]); 		 
			}				
		}							      		
	}
}
/*******************************************************************************
* 函 数 名         : HC595SendData
* 函数功能		   : 通过595发送四个字节的数据
* 输    入         : BT3：第四个595输出数值
*                  * BT2: 第三个595输出数值
*                  * BT1：第二个595输出数值
*                  * BT0：第一个595输出数值
* 输    出         : 无
*******************************************************************************/

void HC595SendData(  uchar BT3, uchar BT2,uchar BT1,uchar BT0)
{  
	uchar i;
	
	//--发送第一个字节--//
	for(i=0;i<8;i++)
	{
		MOSIO = BT3 >> 7 ;	//从高位到低位
		BT3 <<= 1;

		S_CLK = 0;
		S_CLK = 1;		
	}

	//--发送第一个字节--//
	for(i=0;i<8;i++)
	{
		MOSIO = BT2 >>7;		//从高位到低位
		BT2 <<= 1;

		S_CLK = 0;
		S_CLK = 1;	
	}

	//--发送第一个字节--//
	for(i=0;i<8;i++)
	{
		MOSIO = BT1 >> 7;		//从高位到低位
		BT1 <<= 1;
		S_CLK = 0;
		S_CLK = 1;	
	}

	//--发送第一个字节--//
	for(i=0;i<8;i++)
	{
		MOSIO = BT0 >> 7;		//从高位到低位
		BT0 <<= 1;
		S_CLK = 0;
		S_CLK = 1;
	}
   
	//--输出--//
	R_CLK = 0; //set dataline low
	R_CLK = 1; //片选
	R_CLK = 0; //set dataline low
}






