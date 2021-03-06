////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //调用51单片机的头文件
#include <Intrins.h>  
//---------------------------------------
//1602液晶相关I/O设置
sbit E=P2^3;               //1602液晶的E脚接在P2.3口上
sbit RW=P2^4;              //1602液晶的RW脚接在P2.4口上
sbit RS=P2^5;              //1602液晶的RS脚接在P2.5口上
//---------------------------------------
sbit ds18b20=P3^7;	
//---------------------------------------
//1602液晶寄存器设置
unsigned char DISbuf;     //设置8位的unsigend char型寄存器用来暂存1602要显示的内容
//--------------------------------------- 	 
unsigned char temp1;
unsigned char temp2;
unsigned char code table[16]={0,0,1,2,2,3,4,4,5,6,6,7,8,8,9,9};

//---------------------------------------
//名称：延时函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130608
//---------------------------------------
void Delay(unsigned int nTimeDelay) 
{ 
    unsigned int i;
    while (nTimeDelay--) 
        for (i=0;i<125;i++);
}
//---------------------------------------
//名称：复位DS18B20函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130608
//---------------------------------------
bit Reset(void)
{
	unsigned int i;
   bit k;
   ds18b20=0;     			//拉低DQ总线开始复位	
   i=200;     					//保持DQ低大约870uS，符合不低于48US的要求
   while(i>0)     			//保持DQ低大约870uS，符合不低于48US的要求 
       i--;       			//保持DQ低大约870uS，符合不低于48US的要求	    
   ds18b20=1;     			//拉高准备接收数据   
   i=18;    					//大约80uS后
   while(i>0)    				//大约80uS后 
       i--;      				//大约80uS后
   k=ds18b20;    	   		//读出数据并保存    
   i=91;  		  				//维持约400US，符合总读时隙不低于480US的要求
   while(i>0)    				//维持约400US，符合总读时隙不低于480US的要求
       i--;      				//维持约400US，符合总读时隙不低于480US的要求
   return k;               //k=0为复位成功，k=1为复位失败
}
//---------------------------------------
//名称：读一字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130608
//---------------------------------------
unsigned char ReadByte(void)
{
	unsigned int i;
   unsigned char j,buf=0;
   for(j=0;j<8;j++)			//接收8次还原一个字节数据 
   {
		buf=buf>>1;  			//接收前，想将接收缓冲区右移
		ds18b20=0; 				//拉低      
      _nop_();       		//维持2US，符合大于1US小于15US的规范
      _nop_();       		//维持2US，符合大于1US小于15US的规范
      _nop_();       		//维持2US，符合大于1US小于15US的规范
	   _nop_();       		//维持2US，符合大于1US小于15US的规范
      ds18b20=1; 	 			//拉高,为读数据做准备 
		_nop_();       		//维持6US，符合大于1US小于15US的规范
      _nop_();       		//维持6US，符合大于1US小于15US的规范
      _nop_();       		//维持6US，符合大于1US小于15US的规范
	   _nop_();       		//维持6US，符合大于1US小于15US的规范
		_nop_();       		//维持6US，符合大于1US小于15US的规范
      _nop_();       		//维持6US，符合大于1US小于15US的规范
      _nop_();       		//维持6US，符合大于1US小于15US的规范
	   _nop_();       		//维持6US，符合大于1US小于15US的规范
		_nop_();       		//维持6US，符合大于1US小于15US的规范
      _nop_();       		//维持6US，符合大于1US小于15US的规范
      _nop_();       		//维持6US，符合大于1US小于15US的规范
	   _nop_();       		//维持6US，符合大于1US小于15US的规范
		if(ds18b20==1) buf|=0x80;  //读出1位数据保存于buf中
		i=12;  					//维持约52US，符合总读时隙不低于60US的要求
      while(i>0)  			//维持约52US，符合总读时隙不低于60US的要求
      	i--;     			//维持约52US，符合总读时隙不低于60US的要求
	}
   return buf;             //退出的同时将接收缓冲区参数返回
}

//---------------------------------------
//名称：写一字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130608
//---------------------------------------
void WriteByte(unsigned char dat)
{
	unsigned int i;
   unsigned char j;
   for(j=0;j<8;j++)
   {             
		if(dat&0x01)			//如果写1
      {      
	   	ds18b20=0; 			//拉低      
         _nop_();       	//维持2US，符合大于1US小于15US的规范
         _nop_();       	//维持2US，符合大于1US小于15US的规范
         _nop_();       	//维持2US，符合大于1US小于15US的规范
	    	_nop_();       	//维持2US，符合大于1US小于15US的规范
         ds18b20=1; 	 		//拉高        
         i=14;  				//维持约63US，符合不低于60US的要求
         while(i>0)  		//维持约63US，符合不低于60US的要求
         	i--;     		//维持约63US，符合不低于60US的要求
		}
      else						//如果写0
      {            
			ds18b20=0; 			//拉低 	        
         i=14;					//维持约63US，符合不低于60US的要求 
         while(i>0)			//维持约63US，符合不低于60US的要求 
         	i--;    			//维持约63US，符合不低于60US的要求        
         ds18b20=1; 			//拉高	        
         _nop_();       	//维持2US，符合大于1US的规范
         _nop_();       	//维持2US，符合大于1US的规范
         _nop_();       	//维持2US，符合大于1US的规范
	    	_nop_();       	//维持2US，符合大于1US的规范
      }
		dat=dat>>1;				//写入字节右移1位
	}
}

//---------------------------------------
//名称：DS18B20温度转换函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130608
//---------------------------------------
bit Convert(void)
{    
	if(Reset()==0)          //复位DS18B20
	{		
    	WriteByte(0xcc);		//写入跳过序列号命令字 Skip Rom
      WriteByte(0x44);		//写入温度转换命令字 Convert T  
	  	return 1;            //启动温度转换成功
	}
	else
	{	  
	  	return 0;            //启动温度转换失败
	}
}

//---------------------------------------
//名称：转换结束处理函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130608
//---------------------------------------
void ReadFlash(void)
{    
	unsigned char Lsb,Msb;	
   if(Reset()==0)          //复位DS18B20
	{
      WriteByte(0xcc);		//写入跳过序列号命令字 Skip Rom
      WriteByte(0xbe);		//写入读取数据令字 Read Scratchpad
      Lsb=ReadByte();		//读出第一个字节暂存于LSB
      Msb=ReadByte();		//读出第二个字节暂存于MSB	
	  	temp1=Lsb&0x0f;		//temp1内装温度参数的小数部分
      temp2=(Lsb>>4)|(Msb<<4);//temp2内装温度参数的整数部分 	 
	}	
	else
	{
		temp1=0;					//如果复位失败，温度参数清零
      temp2=0;					//如果复位失败，温度参数清零	
	}
}
//---------------------------------------
//名称：1602液晶忙检测函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20130608
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
//日期：20130608
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
//日期：20130608
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
//日期：20130608
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
//日期：20130608
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
//日期：20130608
//---------------------------------------
void LCD1602_init(void)
{ 
     Delay(150);               //调用延时函数
     LCD1602_Write_com(0x38);       //8位数据总线，两行显示模式，5*7点阵显示
     Delay(50);                //调用延时函数
     LCD1602_Write_com(0x38);       //8位数据总线，两行显示模式，5*7点阵显示
     Delay(50);                //调用延时函数
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
//日期：20130608
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
//日期：20130608
//---------------------------------------
void main(void)            //主函数,单片机开机后就是从这个函数开始运行
{
	unsigned char USARTbuf;
   LCD1602_init();        //调用1602液晶初始化函数
	//*****USART串口初始化*****
    TMOD&=0x0F;            //把TMOD高4位清0
    TMOD|=0x20;            //将TMOD的M1位置1，设置成自动装入的8位定时器
    TH1=0xFA;              //设置波特率为9600
    TL1=0xFA;              //设置波特率为9600
    TR1=1;                 //启动定时器T1，作为串口波特率发生器
    SCON=0x50;             //10位异步收发，波特率由定时器控制，允许串口接收
    ES=0;                  //禁止串口中断
    //**************************
   while(1)               //死循环,单片机初始化后,将一直运行这个死循环
   {
      if(Convert()==1)		 				//启动转换
		{	     
	    	ReadFlash();               	//读取温度	  		 
         if(temp2>99) temp2=99;			 
		 	if(temp1>15) temp1=0; 
 			temp1=table[temp1];			
			LCD1602_Disp(0,0,temp2/10+'0');  //温度整数部分十位				
		   LCD1602_Disp(1,0,temp2%10+'0');  //温度整数部分个位
			LCD1602_Disp(2,0,'.');  //.		
			LCD1602_Disp(3,0,temp1+'0');  //温度小数部分
			LCD1602_Disp(4,0,0xdf);   //.
			LCD1602_Disp(5,0,0x43);   //C			 			 		
	    }  
		//****查询式串口接收程序****
        if(RI==1)               //如果接收标志位为1，说明有数据接收完毕
        {                       //RCIF在寄存器被读出后自动清零
            USARTbuf=SBUF;      //将接收缓冲区内容转至USARTbuf寄存器中
            RI=0;               //清除接收标志位
			if(USARTbuf==0x89)
			{
					TI=0;
            	SBUF=0x90;    //发回第一个数据0X90，作为数据头使用
            	while(!TI);         //一直等到数据发送完毕
					TI=0;
				SBUF=temp2;    //发回温度的整数部分
            	while(!TI);         //一直等到数据发送完毕
					TI=0;
				SBUF=temp1;    //发回温度的小数部分
            	while(!TI);         //一直等到数据发送完毕
			}
        }
    //************************** 
    }
}

