////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件
#include <Intrins.h>       //因本例需要使用空操作，必须调用这个头文件

//---------------------------------------
//1602液晶相关I/O设置
sbit E=P2^3;               //1602液晶的E脚接在P2.3口上
sbit RW=P2^4;              //1602液晶的RW脚接在P2.4口上
sbit RS=P2^5;              //1602液晶的RS脚接在P2.5口上
//---------------------------------------

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
//1602液晶寄存器设置
unsigned char DISbuf;     //设置8位的unsigend char型寄存器用来暂存1602要显示的内容
unsigned char j;          //设置8位的unsigend char型寄存器用来暂存转换数据
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
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{

    LCD1602_init();        //调用1602液晶初始化函数

    while(1)               //死循环,单片机初始化后,将一直运行这个死循环
    {
        ADbuf=ReadPCF8591(1);     //将AIN1通道A/D转换结果暂存在ADbuf

    //**给1602显示寄存器赋值(0x00-0xFF)**
        DISbuf=ADbuf;           //
    //***********************************

    //***1602液晶显示0x00-0xFF***
        LCD1602_Disp(0,0,'0');      //在第1行的第1列显示0
        LCD1602_Disp(1,0,'x');      //在第1行的第2列显示x
        j=DISbuf>>4;                //把要显示内容的高4位移到低4位上
        if(j<10)                    //0-F在ASCII码中并不连续，所以要分开处理
        {
            j+='0';                 //0-9的数据以0为基点进行偏移即可
        }
        else
        {
            j=j-10+'A';             //A-F的数据以A为基点进行偏移即可
        }
        LCD1602_Disp(2,0,j);        //在第1行的第3列显示高4位的十六进制数字
        j=DISbuf&0x0F;              //把要显示内容的高4位屏蔽掉，保留低4位
        if(j<10)                    //0-F在ASCII码中并不连续，所以要分开处理
        {
            j+='0';                 //0-9的数据以0为基点进行偏移即可
        }
        else
        {
            j=j-10+'A';             //A-F的数据以A为基点进行偏移即可
        }
        LCD1602_Disp(3,0,j);        //在第1行的第4列显示低4位的十六进制数字
    //***********************

    }
}

