////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件
#include <Intrins.h>       //因本例需要使用空操作，必须调用这个头文件

#define WAV_LEN 271919  /*WAV_LEN是WAV数组的长度*/
long counter;

//---------------------------------------
//软件模拟IIC相关I/O设置
sbit SCL=P1^7;             //PCF8591T的 SCL 引脚接于单片机的P1^7引脚上
sbit SDA=P1^6;             //PCF8591T的 SDA 引脚接于单片机的P1^6引脚上
//---------------------------------------
//---------------------------------------
//W25Q16相关I/O设置
sbit CS          = P3^6;	//选通  
sbit DIO         = P3^5;   //单片机输出
sbit DO          = P3^7;	//FLASH输出
sbit SCLK        = P3^4;	//时钟
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
//名称: 从FLASH存储器中读数据函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120916
//---------------------------------------
//读出内容放置于Buf[]中
unsigned char W25X_Flash_Byte_Read (unsigned long Addre24)  //从Flash里读出16字节数
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
   J=Read_OneByte();	 //读一个字节
   CS=1;
   _nop_();
	_nop_();
   SCLK=1;  
	return J;
}	  
//---------------------------------------
//名称：生IIC启动信号函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void IICstart(void)
{ 
     SDA=1;                //先将SDA=1，以准备在SCL=1时，将SDA=0
     SCL=1;                //时钟总线拉高 
     _nop_();          		//略做延时
     _nop_();          		//略做延时
     SDA=0;                //SCL=1时，将SDA拉低即产生启动信号 
     _nop_();          		//略做延时
     _nop_();          		//略做延时
     SCL=0;                //将SCL=0，完成启动信号操作      
} 

//---------------------------------------
//名称：IIC停止信号函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void IICstop(void)
{ 
     SDA=0;                //先将SDA=0，以准备在SCL=1时，将SDA=1
     SCL=1;                //时钟总线拉高 
     _nop_();          		//略做延时
     _nop_();          		//略做延时
     SDA=1;                //SCL=1时，将SDA拉高即产生停止信号 
     _nop_();          		//略做延时
     _nop_();          		//略做延时
     SCL=0;                //将SCL=0，完成启动信号操作      
} 

//---------------------------------------
//名称：向IIC总线写入1个字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void Write1Byte(unsigned char Buf1)
{ 
     unsigned char k;      //1个字节要分8次写入，需要定义一个寄存器用来计数
     for(k=0;k<8;k++)      //做一个8次的循环，每次写入1位，需要写8次
     {
         if(Buf1&0x80)     //从最高位开始写 
         {
             SDA=1;        //如果欲写入数据为1，就将数据线置1
         }
         else
         {
             SDA=0;        //如果欲写入数据为0，就将数据线写0 
         }
         _nop_();          //略做延时
         _nop_();          //略做延时
         SCL=1;            //时钟线做一个上升沿，将一位数据写入
         Buf1=Buf1<<1;     //数据左移一位，将下次要写入的位数据移到最高位
         _nop_();          //略做延时
         SCL=0;            //将SCL=0，以准备通过上升沿将数据写入
         _nop_();          //略做延时
     }
     SDA=1;                //将SDA=1，准备读应答信号
     _nop_();              //略做延时
     SCL=1;                //将SCL=1，做个上升沿准备读应答信号
     _nop_();              //略做延时
     _nop_();              //略做延时
     SCL=0;                //将SCL=0，结束应答信号读操作
} 


//---------------------------------------
//名称：软件模拟IIC向PCF8591指定地址写一个字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void WritePCF8591(unsigned char Databuf)
{                          //直接调用本函数即可启动PCF8591的D/A转换
    IICstart();            //IIC启动信号

    Write1Byte(0x90);      //发送PCF8591的器件地址和写信号

    Write1Byte(0x40);      //发送器件子地址

    Write1Byte(Databuf);   //发送数据

    IICstop();             //产生IIC停止信号
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
    counter=44;
    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {
		counter++;
		if(counter>WAV_LEN) counter=45;; //counter在45到WAV_LEN-1循环变化 
		WritePCF8591(W25X_Flash_Byte_Read(counter)>>1); //将wav数组中的数据缩小一倍后写入PCF8591，为了使音频输出电压范围为0~2.5V	
    }
}

