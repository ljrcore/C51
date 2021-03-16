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

unsigned char ComBuf[21];//串口通讯数据缓存，发送和接收都使用
unsigned int  nTimeOut;//超时计数
unsigned char Buf[16];
unsigned char n;	
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
void W25X_Flash_Byte_Write(unsigned char AddreH,unsigned char AddreM,unsigned char AddreL)    
{						 		 
   unsigned char J;   //计字节数
   while(W25X_BUSY_OrNot ());  //判BUSY	等到Flash闲才能操作
   WriteEnable();   //写允许
   SCLK=1;   
	_nop_();
	_nop_();
   CS=0;
   Send_OneByte(W25X_Write);  //命令
   Send_OneByte(AddreH);
   Send_OneByte(AddreM);
   Send_OneByte(AddreL);
   for (J=0;J<16;J++)
   {
     	Send_OneByte(Buf[J]); //写字节
  	}
   CS=1;
   _nop_();
	_nop_();
   SCLK=1;
   for(J=0;J<200;J++) //延时一点点
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
//读出内容放置于Buf[]中
void W25X_Flash_Byte_Read (unsigned char AddreH,unsigned char AddreM,unsigned char AddreL)  //从Flash里读出16字节数
{
   unsigned char J;	 //计字节数   
   while(W25X_BUSY_OrNot()==1);  //判BUSY
	_nop_();
	_nop_();
   CS=0;
   Send_OneByte(W25X_ReadDATA8);//命令读
   Send_OneByte(AddreH);
   Send_OneByte(AddreM);
   Send_OneByte(AddreL);
   for (J=0;J<16;J++)
   {
     	Buf[J]=Read_OneByte();	 //读一个字节
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
void W25X_SectorErase(unsigned char AddreH,unsigned char AddreM,unsigned char AddreL)	//擦除资料图示的4KB空间
{
   WriteEnable();   //写允许  

   SCLK=1;
   CS=0;
   Send_OneByte(W25X_S_Erase);//整扇擦除命令
   Send_OneByte(AddreH);
   Send_OneByte(AddreM);
   Send_OneByte(AddreL);
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
void W25X_BlockErase(unsigned char AddreH,unsigned char AddreM,unsigned char AddreL)	//擦除资料图示的64KB空间
{
   WriteEnable();   //写允许

   SCLK=1;
   CS=0;
   Send_OneByte(W25X_B_Erase);//整扇擦除命令
   Send_OneByte(AddreH);
   Send_OneByte(AddreM);
   Send_OneByte(AddreL);
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
//名称: 等待上位机18字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
bit WaitData()
{
	unsigned char n;
	RI=0;
	for(n=0;n<21;n++)
	{
		nTimeOut=0;
		while(!RI)
		{
			nTimeOut++;
			if(nTimeOut>10000)
			{
				return 0;
			}
		}
		RI=0;
		ComBuf[n]=SBUF;
	}
	return 1;
}
//---------------------------------------
//名称: 向上位机发送18字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void SendData()
{
	unsigned char n=0;
	for(n;n<21;n++)
	{
		TI=0;
		SBUF=ComBuf[n];
		while(!TI){}
		TI=0;
	}
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
    //*****USART串口初始化*****
	TMOD&=0x0F;            //把TMOD高4位清0
	TMOD|=0x20;            //将TMOD的M1位置1，设置成自动装入的8位定时器
   TH1=0xFF;              //设置波特率为57600
   TL1=0xFF;              //设置波特率为57600
   TR1=1;                 //启动定时器T1，作为串口波特率发生器
   SCON=0x50;             //10位异步收发，波特率由定时器控制，允许串口接收
	ES=0;                  //禁止串口中断
   //**************************
	while(1)               //死循环,单片机初始化后,将一直运行这个死循环
   	{    
   		if(WaitData()==1)   //如果接收成功
		{		
			if(ComBuf[0]==1) //如果上位机发1，为读识别码
			{
				ComBuf[2]=6;
    			ComBuf[3]=2;
    			ComBuf[4]=4;  
  				SendData();  //将识别码624发给上位机
			}
			else if(ComBuf[0]==2) //如果上位机发2，为写W25Q16
			{
				SendData();//回应上位机表示进入写器件状态，可以发来数据		
				while(1)
				{
					if(WaitData()==1&&ComBuf[1]==0x01)//如果接收数据成功并且ComBuf[0]==1表示继续写
					{						
						for(n=0;n<16;n++)
						{
							Buf[n]=ComBuf[n+2];  //把接收到的COMBUF[2]-[17]内的数据移到
							//BUF[0]-[15]内，以便套用连续写函数格式
						}		
						W25X_Flash_Byte_Write(ComBuf[18],ComBuf[19],ComBuf[20]);//ComBuf[2~17]为待写入数据块
						SendData();					//通知上位机继续发			
					}	
					else
					{
						break;  //退出while(1)
					}
				}		
			}	
			else if(ComBuf[0]==3) //如果上位机发3，为读W25Q16
			{
				SendData();//回应上位机表示进入读状态				
				while(1)
				{
					if(WaitData()==1&&ComBuf[1]==1)//如果接收数据成功并且ComBuf[0]==1表示继续读
					{
						W25X_Flash_Byte_Read(ComBuf[18],ComBuf[19],ComBuf[20]);//从Address开始，连续读16个字节，放入BUF[]里
						for(n=0;n<16;n++)
						{
							ComBuf[n+2]=Buf[n];				
						}			
						SendData();				
					}
					else
					{
						break;  //退出while(1)
					}
				}		
			}
			else if(ComBuf[0]==4) //如果上位机发4，为整片擦除(2M bytes)
			{
				SendData();//回应上位机表示进入整片擦除					
				W25X_ChipErase();				
				Delay(50000); //
			}
			else if(ComBuf[0]==5) //如果上位机发5，为块区擦除(64K bytes)
			{
				SendData();//回应上位机表示进入块区擦除				
				W25X_BlockErase(ComBuf[18],ComBuf[19],0);				
				Delay(8000); //
			}
			else if(ComBuf[0]==6) //如果上位机发6，为扇区擦除(4K bytes)
			{
				SendData();//回应上位机表示进入扇区擦除				
				W25X_SectorErase(ComBuf[18],ComBuf[19],0);				
				Delay(8000); //
			}
		}     
   	}
}

