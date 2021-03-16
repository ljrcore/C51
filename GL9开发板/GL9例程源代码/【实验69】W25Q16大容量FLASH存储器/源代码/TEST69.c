////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件
#include <intrins.h>       //包含位移和_nop_();

//---------------------------------------
//1602液晶相关I/O设置
sbit E=P2^3;               //1602液晶的E脚接在P2.3口上
sbit RW=P2^4;              //1602液晶的RW脚接在P2.4口上
sbit RS=P2^5;              //1602液晶的RS脚接在P2.5口上
//---------------------------------------

//---------------------------------------
//W25Q16相关I/O设置
sbit CS          = P3^6;	//选通  
sbit DIO         = P3^5;   //单片机输出
sbit DO          = P3^7;	//FLASH输出
sbit SCLK        = P3^4;	//时钟
//---------------------------------------

//---------------------------------------
//1602液晶寄存器设置
unsigned char DISbuf;     //设置8位的unsigend char型寄存器用来暂存1602要显示的内容
//---------------------------------------


//***************************************************************
#define W25X_ReadStatus       0x05		//读状态寄存器
#define W25X_WriteStatus      0x01		//写状态寄存器
#define W25X_ReadDATA8        0x03		//普读_数据
#define W25X_FastRead         0x0B		//快读_数据
#define W25X_DualOutput       0x3B		//快读_双输出
#define W25X_Write            0x02		//写_数据_0~255个字节
#define W25X_S_Erase          0x20		//扇区擦除4KB
#define W25X_B_Erase          0xD8		//块区擦除64KB
#define W25X_C_Erase          0xC7		//整片格式化
#define W25X_PowerDown        0xB9		//待机
#define W25X_PowerON_ID       0xAB		//开机或是读ID
#define W25X_JEDEC_ID         0x9F		//十六位的JEDEC_ID
#define W25X_WriteEnable      0x06		//写充许
#define W25X_WriteDisable     0x04		//写禁止


unsigned char xdata Send_DATA[2];	 //要发送的数据
unsigned char xdata Recv_DATA[2];	 //已接收的数据, 如2个数，则为Recv_DATA[0] Recv_DATA[1]

//---------------------------------------
//名称：1602液晶用延时函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
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
//日期：20120914
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
//日期：20120914
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
//日期：20120914
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
//日期：20120914
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
//日期：20120914
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
//日期：20120914
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
//日期：20120914
//---------------------------------------
void LCD1602_Disp(unsigned char x,unsigned char y,unsigned char buf)
{ 
     LCD1602_Write_address(x,y);    //先将地址信息写入
     LCD1602_Write_data_busy(buf);  //再写入要显示的数据
} 

//---------------------------------------
//名称: SPI写入一个字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void Send_OneByte(unsigned char DATA8) //从SPI发8位数
{			       				            //上升沿写入
   unsigned char x;      
   for (x=0;x<8;x++)
   { 
	 	SCLK=0;
	 	if(DATA8&0x80)DIO=1;
	 	else DIO=0;
	 	SCLK=1;
	 	DATA8=DATA8<<1;
	}     
} 

//---------------------------------------
//名称: SPI读出一个字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
unsigned char Read_OneByte(void)     //从SPI收8位数
   {						         //下降沿输出
   unsigned char DATA8;
   unsigned char x;
   SCLK=1;
   DATA8=0x00;
   for (x=0;x<8;x++)
   { 
	 	_nop_();
	 	SCLK=0;
	 	DATA8=DATA8<<1;
	 	if(DO)DATA8=DATA8|0x01;
	 	SCLK=1;	 
	}
   return (DATA8);   
}
//---------------------------------------
//名称: 写允许函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void WriteEnable  (void)
{
   SCLK=1;
   CS=0;
   Send_OneByte(W25X_WriteEnable);  
   CS=1;
   SCLK=1;
}
//---------------------------------------
//名称: 写禁止函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void WriteDisable (void)
{
   SCLK=1;
   CS=0;
   Send_OneByte(W25X_WriteDisable);  
   CS=1;
   SCLK=1;
}
//---------------------------------------
//名称: 判断W25Q16忙函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
unsigned char W25X_BUSY_OrNot (void) 	//在读和写之前得先判断FLASH是否BUSY
{				         						//BUSY的原因是擦除，或是连续读写
   unsigned char k;          				//如果没有以上方式，不必判定可以写读  
   SCLK=1;
   _nop_();
   CS=0;
   Send_OneByte(W25X_ReadStatus);   //读状态寄存器
   k=Read_OneByte();  					//读一个字节
   k=k&0x01;
   CS=1;
	_nop_();
   SCLK=1;
   return k;                         //返回1表示忙，返回0表示不忙   
}	
//---------------------------------------
//名称: 往FLASH存储器中写数据函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
//Addre24为24位地址，格式为0xYYYYYY
//Quantity为写入数据数量，范围为0-255
//连续写的时候，地址最后八位必须从00开始写
//如果256个字节都读满或写满，三字节地址最后一个字节必须为0
//否则当地址越过分面时，会从本页的00从新开始，造成错写
//写入内容需要预先放置于Send_DATA[]中
void W25X_Flash_Byte_Write(unsigned long Addre24,unsigned char Quantity)    
   {						 		 
   unsigned char Addre3;	 //
   unsigned char Addre2;	 //
   unsigned char Addre1;
   unsigned char J;   //计字节数
   unsigned char x;

   while(W25X_BUSY_OrNot ());  //判BUSY	等到Flash闲才能操作

   WriteEnable();   //写允许
   SCLK=1;
   Addre1=Addre24;
   Addre24=Addre24>>8;
   Addre2=Addre24;
   Addre24=Addre24>>8;
   Addre3=Addre24;		    //把地址拆开来
   
   CS=0;
   Send_OneByte(W25X_Write);  //命令
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);

   for (J=0;J<Quantity;J++)
   {
     Send_OneByte(Send_DATA[J]); //写字节
  	}
   CS=1;
   _nop_();
	_nop_();
   SCLK=1;
   for(x=0;x<200;x++) //延时一点点
   {
     _nop_();
	  _nop_();
   }
}	
//---------------------------------------
//名称: 从FLASH存储器中读数据函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
//Addre24为24位地址，格式为0xYYYYYY
//Quantity为读出数据数量，范围为0-255
//读出内容放置于Recv_DATA[]中
void W25X_Flash_Byte_Read (unsigned long Addre24,unsigned char Quantity)  //从Flash里读出小于256字节数
{
   unsigned char J;	 //计字节数
   unsigned char Addre3;
   unsigned char Addre2;
   unsigned char Addre1;
   
   while(W25X_BUSY_OrNot()==1);  //判BUSY

   Addre1=Addre24;
   Addre24=Addre24>>8;
   Addre2=Addre24;
   Addre24=Addre24>>8;
   Addre3=Addre24;		 //把地址拆开来
   
   CS=0;
   Send_OneByte(W25X_ReadDATA8);//命令读
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);

   for (J=0;J<Quantity;J++)
   {
     Recv_DATA[J]=Read_OneByte();	 //读一个字节
	}
   CS=1;
   _nop_();
	_nop_();
   SCLK=1;
   _nop_();
	_nop_();
}	  

//---------------------------------------
//名称: 整片擦除函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void W25X_ChipErase(void)
{
  	WriteEnable();              //写允许
  	SCLK=1;
  	CS=0;
  	Send_OneByte(W25X_C_Erase);//整片擦除命令
  	CS=1;	                     //从CS=1时开始执行擦除
  	SCLK=1;  
  }

//---------------------------------------
//名称: 4K扇区擦除函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void W25X_SectorErase(unsigned long Addre24)	//擦除资料图示的4KB空间
{

   unsigned char Addre3;
   unsigned char Addre2;
   unsigned char Addre1;

   WriteEnable();   //写允许
   Addre1=Addre24;
   Addre24=Addre24>>8;
   Addre2=Addre24;
   Addre24=Addre24>>8;
   Addre3=Addre24;		 //把地址拆开来

   SCLK=1;
   CS=0;
   Send_OneByte(W25X_S_Erase);//整扇擦除命令
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);
   CS=1;
   _nop_();
   SCLK=1;
   _nop_();
	_nop_();
} 
//---------------------------------------
//名称: 64K块区擦除函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void W25X_BlockErase(unsigned long Addre24)	//擦除资料图示的64KB空间
{
   unsigned char Addre3;
   unsigned char Addre2;
   unsigned char Addre1;

   WriteEnable();   //写允许
   Addre1=Addre24;
   Addre24=Addre24>>8;
   Addre2=Addre24;
   Addre24=Addre24>>8;
   Addre3=Addre24;		 //把地址拆开来

   SCLK=1;
   CS=0;
   Send_OneByte(W25X_B_Erase);//整扇擦除命令
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);
   CS=1;
   _nop_();
	_nop_();
   SCLK=1;
   _nop_();
	_nop_();
} 

//---------------------------------------
//名称: 延时函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
void Delay(unsigned int s) //
{
   unsigned int loop;
   for(loop=s;loop>0;loop--)  
   {        
      _nop_();
   }
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
	LCD1602_init();        //调用1602液晶初始化函数
 	W25X_Flash_Byte_Read (0x000000,1);  //读1个数
	Send_DATA[0]=Recv_DATA[0]+1;  	
  	W25X_SectorErase(0); 
  	Delay(4000); //
   W25X_Flash_Byte_Write(0x000000,1);  //写1个数  
  	
	//**给1602显示寄存器赋值(0-255)**
   DISbuf=Send_DATA[0];          //
   //*******************************

   //***1602液晶显示0-255***
   LCD1602_Disp(0,0,DISbuf/100+'0');      //在第1行的第1列显示百位
   LCD1602_Disp(1,0,(DISbuf%100)/10+'0'); //在第1行的第2列显示十位
   LCD1602_Disp(2,0,DISbuf%10+'0');       //在第1行的第3列显示个位
   //***********************
   while(1)               //死循环,单片机初始化后,将一直运行这个死循环
   {
   	
	}			   
}	

