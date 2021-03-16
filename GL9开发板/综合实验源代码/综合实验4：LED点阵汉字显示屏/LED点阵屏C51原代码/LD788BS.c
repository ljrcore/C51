////////////////////////////////////////////////////////////////////////////
//                给力者单片机开发学习系统，开发学习都给力！              //
////////////////////////////////////////////////////////////////////////////
//                     学习51单片机，其实可以很简单                       //
////////////////////////////////////////////////////////////////////////////
//                宁波芯动电子有限公司  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////
#include <AT89X52.h>       //调用51单片机的头文件
#include <Intrins.h>       //因本例需要使用空操作，必须调用这个头文件

sfr	 WDT_CONTR=0xe1;
//---------------------------------------
//W25Q16相关I/O设置
sbit CS          = P3^6;	//选通  
sbit DIO         = P3^5;   //单片机输出
sbit DO          = P3^7;	//FLASH输出
sbit SCLK        = P3^4;	//时钟
//---------------------------------------
//---------------------------------------
//LED点阵屏相关I/O设置
sbit U15E3=P1^3;           //LED点阵屏单元的U15(74HC138)的使能端E3脚接在P1.3口上
sbit U14E3=P1^4;           //LED点阵屏单元的U14(74HC138)的使能端E3脚接在P1.4口上
//---------------------------------------

//---------------------------------------
//LED点阵屏寄存器设置
unsigned char m=15;        //设置8位的unsigend char型寄存器用来做汉字显示的索引
unsigned char n;           //设置8位的unsigend char型寄存器用来做延时用
unsigned char w;           //设置8位的unsigend char型寄存器用来做延时用
unsigned int  v;           //设置8位的unsigend char型寄存器用来做移动索引
unsigned char  xdata hanzibuf1[512];
unsigned char  xdata hanzibuf2[512];
unsigned char L;
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

long neima(unsigned char qh,wh)
{
   unsigned long vb;	
	qh=qh-0xa0;   //得到区号
	wh=wh-0xa0;   //得到区号	
	vb=(94*(qh-1)+(wh-1));
	vb=vb<<5;		
	return vb;
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
void W25X_Flash_Byte_Read (unsigned long Addre24,unsigned char Quantity)  //从Flash里读出16字节数
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
   Addre3=Addre24;
   CS=0;
   Send_OneByte(W25X_ReadDATA8);//命令读
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);
   for (J=0;J<Quantity;J++)
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
/*bit WaitData()
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
}*/
//---------------------------------------
//名称: 向上位机发送18字节函数
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void SendData()
{
	unsigned char s;
	for(s=0;s<21;s++)
	{
		TI=0;
		SBUF=ComBuf[s];
		while(!TI){}
		TI=0;
	}
}
void zhuan(unsigned char i)            //最多显示16汉字，0-15
{
	unsigned char k,g;
	long Address;
	unsigned char zc;
	if(i<8)
	{
		W25X_Flash_Byte_Read(0x1fff00,16);//连续读16个字节，放入BUF[]里	
		Address=neima(Buf[i*2],Buf[i*2+1]);
	}
	else if(i<16)
	{
		W25X_Flash_Byte_Read(0x1fff10,16);//连续读16个字节，放入BUF[]里	
		Address=neima(Buf[(i-8)*2],Buf[(i-8)*2+1]);
	}		
	else if(i<24)
	{
		W25X_Flash_Byte_Read(0x1fff20,16);//连续读16个字节，放入BUF[]里	
		Address=neima(Buf[(i-16)*2],Buf[(i-16)*2+1]);
	}
	else
	{
		W25X_Flash_Byte_Read(0x1fff30,16);//连续读16个字节，放入BUF[]里	
		Address=neima(Buf[(i-24)*2],Buf[(i-24)*2+1]);
	}
	//W25X_Flash_Byte_Read(0x1fff00+(i/8)&0x10,16);//连续读16个字节，放入BUF[]里	
	//Address=neima(Buf[(i%8)*2],Buf[(i%8)*2+1]);

	W25X_Flash_Byte_Read(Address,16);//连续读16个字节，放入BUF[]里
	for(g=0;g<8;g++)  //bit7-bit0
	{
		zc=0;
		for(k=0;k<8;k++)
		{
			zc=zc<<1;
			if(Buf[k*2]&0x80) zc|=0x01;
			Buf[k*2]=Buf[k*2]<<1;				
		}
		hanzibuf1[i*16+g]=zc;
	}
	for(g=0;g<8;g++)  //bit7-bit0
	{
		zc=0;
		for(k=0;k<8;k++)
		{
			zc=zc<<1;
			if(Buf[k*2+1]&0x80) zc|=0x01;
			Buf[k*2+1]=Buf[k*2+1]<<1;
		}
		hanzibuf1[i*16+8+g]=zc;
	}
	W25X_Flash_Byte_Read(Address+16,16);//连续读16个字节，放入BUF[]里
	for(g=0;g<8;g++)  //bit7-bit0
	{
		zc=0;
		for(k=0;k<8;k++)
		{
			zc=zc<<1;
			if(Buf[k*2]&0x80) zc|=0x01;
			Buf[k*2]=Buf[k*2]<<1;				
		}
		hanzibuf2[i*16+g]=zc;
	}
	for(g=0;g<8;g++)  //bit7-bit0
	{
		zc=0;
		for(k=0;k<8;k++)
		{
			zc=zc<<1;
			if(Buf[k*2+1]&0x80) zc|=0x01;
			Buf[k*2+1]=Buf[k*2+1]<<1;
		}
		hanzibuf2[i*16+8+g]=zc;
	}
}
//---------------------------------------
//名称：串口中断服务程序
//适用：给力者GL9单片机开发学习系统
//公司：宁波芯动电子有限公司
//网址：www.MovingChip.com
//日期：20120914
//---------------------------------------
void UART_SER (void) interrupt 4 
{
	if(RI==1)              //如果接收标志位为1，说明有数据接收完毕
   {                      //RCIF在寄存器被读出后自动清零
      ComBuf[0]=SBUF;     //将接收缓冲区内容转至USARTbuf寄存器中
      RI=0;               //清除接收标志位   
		EA=0;
   }
   for(n=1;n<21;n++)
   {
		nTimeOut=0;
		while(!RI)
		{
			nTimeOut++;
			if(nTimeOut>10000)
			{
				while(1);
			}
		}
		RI=0;
		ComBuf[n]=SBUF;
	}
	if(ComBuf[0]==1) 	//如果上位机发1，为读识别码
	{
		ComBuf[2]=6;
   	ComBuf[3]=2;
   	ComBuf[4]=4;  
  		SendData();  	//将识别码624发给上位机
		while(1);
	}
	else if(ComBuf[0]==2) //如果上位机发2，为写W25Q16
	{
		W25X_SectorErase(0x1F,0xFF,0);				
		Delay(10000); //
		SendData();//回应上位机表示进入写器件状态，可以发来数据		
		while(1)
		{
			for(n=0;n<21;n++)
   		{
				nTimeOut=0;
				while(!RI)
				{
					nTimeOut++;
					if(nTimeOut>10000)
					{
						while(1);
					}
				}
				RI=0;
				ComBuf[n]=SBUF;
			}
			if(ComBuf[1]==0x01)//如果接收数据成功并且ComBuf[0]==1表示继续写
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
				while(1);
			}
		}		
	}			
	while(1);
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
	ES=1;                  //允许串口中断
   //**************************	
	W25X_Flash_Byte_Read(0x1ffff0,16);//连续读16个字节，放入BUF[]里
	L=Buf[12];
	for(nTimeOut=0;nTimeOut<512;nTimeOut++) hanzibuf1[nTimeOut]=0;
	for(nTimeOut=0;nTimeOut<512;nTimeOut++) hanzibuf2[nTimeOut]=0;
	for(n=0;n<L;n++) zhuan(n);				
	
	WDT_CONTR=0x3e;
	//12时钟模式，看门狗溢出时间=（12*Pre_scale*32768）/12000000
	//=	Pre_scale*393216/12000000
	//设置为128分频，看门狗溢出时间为2.1秒

	//***开全局中断设置****
    //串口接口UART设置了中断允许,此处要开全局中断
    EA=1;                  //开全局中断
    //*********************
	while(1)               	//死循环,单片机初始化后,将一直运行这个死循环
    {    
	 	WDT_CONTR=0x3e;
		for(n=0;n<100;n++); 	//做一个0-80的循环，不执行其他操作，只为延时
	   if(++w>250)        	//再嵌套一个延时，每220个扫描周期将汉字左移一格
      {
         w=0;           	//清零，以准备下一个延时
         if(++v>(L*16-1)) v=0;;					//移动索引，限定在0-191
      }
      if(++m>15) m=0;    	//每调用一次函数将m加1，并限制在0-15以内
      P1=0;              	//将LED点阵屏的列控制信号全部清零，准备重置  
		if(m+v>511)
		{
			P0=0;		
			P2=0;             
		}
		else
		{
			P0=hanzibuf1[m+v];		
			P2=hanzibuf2[m+v]; //LED点阵屏的下半屏，按m+16索引查表送P2 
		}
      P1|=m&0x07;        	//将索引m的低3位送给P1的低3位，以使74HC138去片选 
      if(m<8) U15E3=1;   	//前8列需要使能U15(74HC138) 
      else U14E3=1;      	//后8列需要使能U14(74HC138)    	
   }
}

