////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件
#include <Intrins.h>    //因为本例中用到空操作_nop_();所以必须调用这个头文件

//---------------------------------------
//12864液晶相关I/O设置
sbit RS=P2^0; 			//并行数据/控制字选择 H:数据  L:控制字
sbit RW=P2^1; 			//并行读/写选择       H:读    L:写
sbit E =P2^2; 			//并行读写使能        H有效,下降沿锁定数据
sbit PSB=P2^3; 		//串口,并口选择       H:并口  L:串口（开发板上引脚标识为CS1）
sbit RST=P2^5; 		//复位引脚            L:液晶复位
sbit DB0=P0^7; 			//
sbit DB1=P0^6; 			//
sbit DB2=P0^5; 			//
sbit DB3=P0^4; 			//
sbit DB4=P0^3; 			//
sbit DB5=P0^2; 			//
sbit DB6=P0^1; 			//
sbit DB7=P0^0; 			//
//---------------------------------------
unsigned char code dis[] = {'0','1','2','3','4','5','6','7','8','9'};
//---------------------------------------
//名称：液晶用延时函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120918
//---------------------------------------
void delay(unsigned int t)
{
	unsigned int i;
	for(i=0;i<t;i++);	
}
//---------------------------------------
//名称：字节内位数据位置转换函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120918
//---------------------------------------
unsigned char num(unsigned char dat)
{
   unsigned char val;
	val = ((dat & 0x01) << 7) | ((dat & 0x02) << 5) | ((dat & 0x04) << 3) | ((dat & 0x08) << 1) |
   ((dat & 0x10) >> 1) | ((dat & 0x20) >> 3) | ((dat & 0x40) >> 5) | ((dat & 0x80) >> 7);
   return  val;
} 
//---------------------------------------
//名称：写命令函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120918
//---------------------------------------
void write_com(unsigned char cmdcode)
{		
	RS=0;                   //设置该字节数据为命令代码
	RW=1;                   //设置此次操作为读
	E=1;                    //使能
	_nop_();            		//空操作，做短暂的延时
	_nop_();            		//空操作，做短暂的延时
	E=0;                    //失能
	RS=0;                   //设置该字节数据为命令代码
	RW=0;                   //设置此次操作为读写
	P0=num(cmdcode);    		//将命令写入总线
	_nop_();            		//空操作，做短暂的延时
	E=1;           			//E的下降沿，数据写入
	_nop_();            		//空操作，做短暂的延时
	E=0;           			//E的下降沿，数据写入
}
//---------------------------------------
//名称：写数据函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120918
//---------------------------------------
void write_data(unsigned char Rsspdata)
{
	RS=0;                   //设置该字节数据为命令代码
	RW=1;                   //设置此次操作为读
	E=1;                    //使能
	_nop_();            		//空操作，做短暂的延时
	_nop_();            		//空操作，做短暂的延时
	E=0;                    //失能
	RS=1;                   //设置该字节数据为数据代码
	RW=0;                   //设置此次操作为读写
	P0=num(Rsspdata);   		//将数据写入总线
	_nop_();            		//空操作，做短暂的延时
	E=1;           			//E的下降沿，数据写入
	_nop_();            		//空操作，做短暂的延时
	E=0;           			//E的下降沿，数据写入
} 
//---------------------------------------
//名称：地址写入函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120918
//---------------------------------------
void write_xy(unsigned char x,unsigned char y)
{
	unsigned char address;
	switch(y)
	{
		case 0:address=0x80+x;break;  //第一行的首地址是0x80
		case 1:address=0x90+x;break;  //第二行的首地址是0x90
		case 2:address=0x88+x;break;  //第三行的首地址是0x88
		case 3:address=0x98+x;break;  //第四行的首地址是0x98
		default:address=0x80+x;
   }
	write_com(address);	
} 
//---------------------------------------
//名称：12864初始化函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120918
//--------------------------------------- 
void init_lcd(void)
{	   
	RST=0;           //复位液晶
	delay(250);      //加些延时
	RST=1;           //复位结束
	delay(250);      //加些延时
	PSB=1;           //选择8bit并口

	write_com(0x30);  //基本指令集  
	write_com(0x0c);  //显示开
	write_com(0x06);  //光标右移，整体显示不移动
	write_com(0x01);  //清除显示(清零DDRAM)
	delay(250);
}  

//---------------------------------------
//名称: 主函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120918
//--------------------------------------- 	
void main()
{  
	unsigned int i,k;
	init_lcd();					  //初始化液晶	
  	while(1)
	{		   	
		if(++i>20000)             //做个延时，不用精确，每20000个计数到，显示数字加一
    	{
    		i=0;                  //清零为下一个循环做准备
    		if(++k>50000) k=0;    //显示数据加一，限制最大数为50000，因为设定的是int,最大65535
			write_xy(0,0);        //设定开始显示的地址，第一行的第一列
    		write_data(dis[k/10000]);   		//显示万位	
			write_data(dis[(k%10000)/1000]);    //显示千位
			write_data(dis[(k%1000)/100]);   	//显示百位
			write_data(dis[(k%100)/10]);   		//显示十位
			write_data(dis[k%10]);   			//显示个位	
		}
	}
}

