////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件

//---------------------------------------
//1602液晶相关I/O设置
sbit E=P2^3;               //1602液晶的E脚接在P2.3口上
sbit RW=P2^4;              //1602液晶的RW脚接在P2.4口上
sbit RS=P2^5;              //1602液晶的RS脚接在P2.5口上
//---------------------------------------
sbit Key_Data =P3^5;
sbit Key_CLK =P3^3; 
//---------------------------------------

unsigned char IntNum = 0; //中断次数计数
unsigned char KeyV; //键值
unsigned char DisNum = 0; //显示用指针
unsigned char Key_UP=0, Shift = 0;//Key_UP是键松开标识，Shift是Shift键按下标识
unsigned char keybuf;
unsigned char disbuf[32];
unsigned char weizhi;
bit BF; //标识是否有字符被收到
bit disbit;
		 

unsigned char code UnShifted[58][2] = {
0x1C, 'a',
0x32, 'b',
0x21, 'c',
0x23, 'd',
0x24, 'e',
0x2B, 'f',
0x34, 'g',
0x33, 'h',
0x43, 'i',
0x3B, 'j',
0x42, 'k',
0x4B, 'l',
0x3A, 'm',
0x31, 'n',
0x44, 'o',
0x4D, 'p',
0x15, 'q',
0x2D, 'r',
0x1B, 's',
0x2C, 't',
0x3C, 'u',
0x2A, 'v',
0x1D, 'w',
0x22, 'x',
0x35, 'y',
0x1A, 'z',
0x45, '0',
0x16, '1',
0x1E, '2',
0x26, '3',
0x25, '4',
0x2E, '5',
0x36, '6',
0x3D, '7',
0x3E, '8',
0x46, '9',
0x70, '0',
0x69, '1',
0x72, '2',
0x7A, '3',
0x6B, '4',
0x73, '5',
0x74, '6',
0x6C, '7',
0x75, '8',
0x7D, '9',

0x4E, '-',
0x55, '=',
0x5D, ' ',
0x29, ' ',
0x54, '[',
0x5B, ']',
0x4C, ';',
0x52, ' ',
0x41, ',',
0x49, '.',
0x4A, '/',
0x71, '.',
};
unsigned char code Shifted[59][2] = {
0x1C,'A',
0x32,'B',
0x21,'C',
0x23,'D',
0x24,'E',
0x2B,'F',
0x34,'G',
0x33,'H',
0x43,'I',
0x3B,'J',
0x42,'K',
0x4B,'L',
0x3A,'M',
0x31,'N',
0x44,'O',
0x4D,'P',
0x15,'Q',
0x2D,'R',
0x1B,'S',
0x2C,'T',
0x3C,'U',
0x2A,'V',
0x1D,'W',
0x22,'X',
0x35,'Y',
0x1A,'Z',

0x45,')',
0x16,'!',
0x1E,'@',
0x26,'#',
0x25,'$',
0x2E,'%',
0x36,'^',
0x3D,'&',
0x3E,'*',
0x46,'(',	 
  
0x4e,'_',
0x4E,'_',
0x55,'+',
0x5D,'|',
0x29,' ',
0x29,' ',
0x29,' ',
0x4C,':',
0x29,' ',
0x41,'<',
0x49,'>',
0x4A,'?',
0x71,'.',

0x70,'0',
0x69,'1',
0x72,'2',
0x7A,'3',
0x6B,'4',
0x73,'5',
0x74,'6',
0x6C,'7',
0x75,'8',
0x7D,'9',
};

//---------------------------------------
//名称：键处理函数	
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
unsigned char  Decode(unsigned char ScanCode)
//注意:如SHIFT+G为12H 34H F0H 34H F0H 12H?
//也就是说shift的通码+G的通码+shift的断码+G的断码
{
	unsigned char TempCyc; 
	unsigned char KeyChar=0;
	if (!Key_UP) //当键盘松开时
	{
		switch (ScanCode)
  		{
  			case 0xF0 : // 当收到0xF0，Key_UP置1表示断码开始
         		Key_UP = 1;
      		break;

  			case 0x12 : // 左 SHIFT
      			Shift = 1;
         	break;

  			case 0x59 : // 右 SHIFT
         		Shift = 1;
            break;
			case 0x66:  //backspace
				if(weizhi>0)
				{
				 	weizhi--;
					disbuf[weizhi]=0x20;
					disbit=1;
				}
			break;
  			default: 
      			if (DisNum > 15) DisNum = 0; 
         		if(!Shift) //如果SHIFT没按下
         		{
       				for (TempCyc = 0;(UnShifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //查表显示
          			if (UnShifted[TempCyc][0] == ScanCode) 
					{
                    	KeyChar=UnShifted[TempCyc][1]; 	
						disbit=1;
						disbuf[weizhi]=KeyChar;
						if(++weizhi>31) 
						{
							for(weizhi=0;weizhi<32;weizhi++) disbuf[weizhi]=0x20;
							weizhi=0;
						}
					}				
          			DisNum++;
         		} 
      			else //按下SHIFT
          		{
         			for(TempCyc = 0; (Shifted[TempCyc][0]!=ScanCode)&&(TempCyc<59); TempCyc++); //查表显示
       				if (Shifted[TempCyc][0] == ScanCode) 
					{
                    	KeyChar=Shifted[TempCyc][1];
						disbit=1;
						disbuf[weizhi]=KeyChar;
						if(++weizhi>31) 
						{
							for(weizhi=0;weizhi<32;weizhi++) disbuf[weizhi]=0x20;
							weizhi=0;
						}
					}
        			DisNum++;
       			}
      		break;
     	}
	}
	else
	{ 
		Key_UP = 0;
		switch (ScanCode) //当键松开时不处理判码，如G 34H F0H 34H 那么第二个34H不会被处理
  		{
  			case 0x12 : // 左 SHIFT
      			Shift = 0;
         	break;
  			case 0x59 : // 右 SHIFT
      			Shift = 0;
         	break;
  		}
	}
	return KeyChar;
} 	
//---------------------------------------
//名称：键盘扫描函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//--------------------------------------- 
void scakey()
{		
	if (BF)
	{				
		Decode(keybuf);
		BF=0;
		EX1=0;	
		EA=1;		
	}
	else
    	EX1 = 1; //开中断      		
} 

//---------------------------------------
//名称：外部INT1中断服务程序
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void INIT1(void) interrupt 2 
{

    //***此处用户自行添加外部INT1中断处理程序***
	if ((IntNum > 0) && (IntNum < 9))
	{ 
		KeyV = KeyV >> 1; //因键盘数据是低>>高，结合上一句所以右移一位
		if (Key_Data) KeyV = KeyV | 0x80; //当键盘数据线为1时为1到最高位
	}
	IntNum++;
	while (!Key_CLK); //等待PS/2CLK拉高
	if (IntNum > 10)
	{
		IntNum = 0; //当中断11次后表示一帧数据收完，清变量准备下一次接收
		BF = 1; //标识有字符输入完了 
		keybuf=KeyV;
		KeyV=0;		 	
	}
    //******************************************
}

//---------------------------------------
//名称：1602液晶用延时函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void Delay1602(unsigned int t)
{ 
     unsigned int k;      //定义一个16位寄存器用来做延时用 
     for(k=0;k<t;k++);    //延时 
} 

//---------------------------------------
//名称：1602液晶忙检测函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void LCD1602_busy(void)
{ 
     P0_7=1;              //将P0.7置1，为读状态做准备 
     RS=0;                //RS=0、RW=1、E=1时，忙信号输出到DB7，由P0.7读入
     RW=1;                //RS=0、RW=1、E=1时，忙信号输出到DB7，由P0.7读入
     E=1;                 //RS=0、RW=1、E=1时，忙信号输出到DB7，由P0.7读入
     while(P0_7==1);      //由P0.7读入1，表示1602液晶忙，需要等待
     E=0;                 //读完以后，恢复E的电平
} 

//---------------------------------------
//名称：1600写命令函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void LCD1602_Write_com(unsigned char combuf)
{ 
     RS=0;                //选择指令寄存器
     RW=0;                //选择写状态
     P0=combuf;           //将命令字通过P0口送至DB
     E=1;                 //E高电平将命令字写入1602液晶
     E=0;                 //写完以后，恢复E的电平
} 

//---------------------------------------
//名称：1602写命令函数(带忙检测)
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void LCD1602_Write_com_busy(unsigned char combuf)
{ 
     LCD1602_busy();            //调用忙检测函数
     LCD1602_Write_com(combuf); //调用忙检测函数
} 

//---------------------------------------
//名称：1602写数据函数(带忙检测)
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void LCD1602_Write_data_busy(unsigned char databuf)
{ 
     LCD1602_busy();      //调用忙检测函数
     RS=1;                //选择数据寄存器
     RW=0;                //选择写状态
     P0=databuf;          //将命令字通过P0口送至DB
     E=1;                 //E高电平将命令字写入1602液晶
     E=0;                 //写完以后，恢复E的电平
} 

//---------------------------------------
//名称：1602液晶显示地址写函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void LCD1602_Write_address(unsigned char x,unsigned char y)
{ 
     x&=0x0f;             //列地址限制在0-15间
     y&=0x01;             //行地址限制在0-1间
     if(y==0)             //如果是第一行
         LCD1602_Write_com_busy(x|0x80);        //将列地址写入
     else                 //如果是第二行
         LCD1602_Write_com_busy((x+0x40)|0x80); //将列地址写入
} 

//---------------------------------------
//名称：1602液晶初始化函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void LCD1602_init(void)
{ 
     Delay1602(1500);               //调用延时函数
     LCD1602_Write_com(0x38);       //8位数据总线，两行显示模式，5*7点阵显示
     Delay1602(500);                //调用延时函数
     LCD1602_Write_com(0x38);       //8位数据总线，两行显示模式，5*7点阵显示
     Delay1602(500);                //调用延时函数
     LCD1602_Write_com(0x38);       //8位数据总线，两行显示模式，5*7点阵显示
     LCD1602_Write_com_busy(0x38);  //8位数据总线，两行显示模式，5*7点阵显示
     LCD1602_Write_com_busy(0x08);  //显示功能关，无光标
     LCD1602_Write_com_busy(0x01);  //清屏
     LCD1602_Write_com_busy(0x06);  //写入新的数据后，光标右移，显示屏不移动
     LCD1602_Write_com_busy(0x0C);  //显示功能开，无光标
} 

//---------------------------------------
//名称：1602液晶指定地址显示函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void LCD1602_Disp(unsigned char x,unsigned char y,unsigned char buf)
{ 
     LCD1602_Write_address(x,y);    //先将地址信息写入
     LCD1602_Write_data_busy(buf);  //再写入要显示的数据
} 

//---------------------------------------
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{
	unsigned char k,l;
    LCD1602_init();        //调用1602液晶初始化函数
		
    //***外部中断INT1初始化***
    IT1=1;                 //下降沿触发方式
    EX1=1;                 //外部INT1中断允许
    //**********************

    //***开全局中断设置****
    //外部中断INT1设置了中断允许,此处要开全局中断
    EA=1;                  //开全局中断
    //*********************

	for(weizhi=0;weizhi<32;weizhi++) disbuf[weizhi]=0x20;
	weizhi=0;
	while(1)
	{	 
		scakey();
		if(disbit)
		{
		 	disbit=0;
			LCD1602_init();
			for(k=0;k<2;k++)
			{
				for(l=0;l<16;l++)
				{
					LCD1602_Disp(l,k,disbuf[k*14+l]);   //					
				}
			}
		}					
	}
}

