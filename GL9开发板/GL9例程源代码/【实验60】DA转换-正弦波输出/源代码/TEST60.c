////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件
#include <Intrins.h>       //因本例需要使用空操作，必须调用这个头文件

unsigned char code tab[]={
0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x99,0x9c,
0x9f,0xa2,0xa5,0xa8,0xab,0xae,0xb1,0xb4,0xb6,0xb9,
0xbc,0xbf,0xc2,0xc4,0xc7,0xc9,0xcc,0xce,0xd1,0xd3,
0xd6,0xd8,0xda,0xdc,0xdf,0xe1,0xe3,0xe5,0xe7,0xe8,
0xea,0xec,0xee,0xef,0xf1,0xf2,0xf3,0xf5,0xf6,0xf7,
0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfd,0xfe,0xfe,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xfe,
0xfe,0xfd,0xfd,0xfc,0xfb,0xfb,0xfa,0xf9,0xf8,0xf7,
0xf5,0xf4,0xf3,0xf1,0xf0,0xee,0xed,0xeb,0xe9,0xe8,
0xe6,0xe4,0xe2,0xe0,0xde,0xdb,0xd9,0xd7,0xd5,0xd2,
0xd0,0xcd,0xcb,0xc8,0xc6,0xc3,0xc0,0xbe,0xbb,0xb8,
0xb5,0xb2,0xaf,0xac,0xa9,0xa6,0xa3,0xa0,0x9d,0x9a,
0x97,0x94,0x91,0x8e,0x8b,0x88,0x84,0x81,0x7e,0x7b,
0x78,0x75,0x72,0x6e,0x6b,0x68,0x65,0x62,0x5f,0x5c,
0x59,0x56,0x53,0x50,0x4d,0x4a,0x47,0x45,0x42,0x3f,
0x3c,0x3a,0x37,0x34,0x32,0x2f,0x2d,0x2b,0x28,0x26,
0x24,0x22,0x20,0x1d,0x1b,0x1a,0x18,0x16,0x14,0x12,
0x11,0xf,0xe,0xc,0xb,0xa,0x9,0x7,0x6,0x5,
0x4,0x4,0x3,0x2,0x2,0x1,0x1,0x0,0x0,0x0,
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x1,0x1,0x2,
0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9,0xa,0xb,
0xd,0xe,0x10,0x11,0x13,0x15,0x16,0x18,0x1a,0x1c,
0x1e,0x20,0x22,0x24,0x27,0x29,0x2b,0x2e,0x30,0x33,
0x35,0x38,0x3a,0x3d,0x40,0x43,0x45,0x48,0x4b,0x4e,
0x51,0x54,0x57,0x5a,0x5d,0x60,0x63,0x66,0x69,0x6c,
0x6f,0x73,0x76,0x79,0x7c
};

//---------------------------------------
//软件模拟IIC相关I/O设置
sbit SCL=P1^7;             //PCF8591T的 SCL 引脚接于单片机的P1^7引脚上
sbit SDA=P1^6;             //PCF8591T的 SDA 引脚接于单片机的P1^6引脚上
//---------------------------------------

//---------------------------------------
//A/D转换用寄存器设置
unsigned char ADbuf;       //设置8位的寄存器用来暂存A/D转换结果
//---------------------------------------

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
//名称：从IIC总线读入1个字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
unsigned char Read1Byte(void)
{ 
     unsigned char k;      //1个字节要分8次读出，需要定义一个寄存器用来计数
     unsigned char t=0;    //定义一个寄存器用保存读出数据
     for(k=0;k<8;k++)      //做一个8次的循环，每次读入1位，需要读8次
     {
         t=t<<1;           //数据左移一位，空出最低位以准备保存读入的一位数据
         SDA=1;            //将SDA写1准备读
         SCL=1;            //将SCL=1，做个上升沿准备读一位数据
         _nop_();          //略做延时
         _nop_();          //略做延时
         if(SDA==1)        //读一位数据，并判断 
         {
             t=t|0x01;     //如果读入数据为1，就将接收缓冲区最低一位置1
         }
         else
         {
             t=t&0xfe;     //如果读入数据为0，就将接收缓冲区最低一位写0
         }
         SCL=0;            //SCL恢复为0，结束一位数据读操作
         _nop_();          //略做延时
         _nop_();          //略做延时
     }
     return t;             //将读入的一个字节返回
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
//名称：软件模拟IIC从PCF8563指定地址读一个字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
unsigned ReadPCF8591(unsigned char Ch)
{                          //直接调用本函数即可从PCF8591的Ch通道读出数据返回
    unsigned char buf;     //定义一个寄存器用来暂存读出的数据
    IICstart();            //IIC启动信号

    Write1Byte(0x90);      //发送PCF8591的器件地址和写信号

    Write1Byte(0x40|Ch);   //发送器件通道参数Ch=0-3

    IICstart();            //IIC启动信号

    Write1Byte(0x91);      //发送PCF8591的器件地址和读信号

    buf=Read1Byte();//读一个字节数据

    IICstop();             //产生IIC停止信号

    return(buf);           //将读出数据返回
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
	unsigned char i;  
    unsigned int  l;
    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {
		for(i=0;i<255;i++)
	    {
        	WritePCF8591(tab[i]);        //利用输入参数进行D/A转换
			for(l=0;l<2000;l++);
		}
    }
}

