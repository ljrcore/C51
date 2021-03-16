#include <define.h>

#define BYTE unsigned char
#define WORD unsigned int
sbit POWER=P1^0;          //电源
sbit RST=P1^1;            //复位
sbit CHECK=P3^3;          //检卡
sbit VPP=P1^4;
bit count=0;
bit mark=0;
void mDelay(BYTE j)
  {
    WORD i;
    for(;j>0;j--)
    {
      for(i=0;i<228;i--) //125
      {;}
    }
  }



/**********************************************************
初始化CPU及IO
***********************************************************/
void InitCPUIO(void)
{
//-------------------------------------
	P0=0xff;
	P1=0xff;
	P3=0xfe;
	P2=ReadyTwice;
	LE373=1;
	LE373=0;
	P2=0xff;
//-------------------------------------	
	IE=0x00;
	IP=0x00;
//	SP=0xd0;
}


/**************************************
* 延时函数1mS（实测为1.18ms）
***************************************/
void Delayms(Word count)

{Word j;
 while(count--!=0)
	for(j=0;j<46;j++);
}
/**************************************
* 延时函数250uS
***************************************/
void Delay250uS(Word count)
{Word j;
 while(count--!=0)
	for(j=0;j<12;j++);
}

/***************************************************************************** 
Function:     Power_Up                                                      
*****************************************************************************/

/**************************************
*蜂鸣器函数：		Beep()
*入口参数：			count 鸣叫次数
***************************************/

void SBeep(Byte count)
{	Byte i;
	for(;count;count--)
	{	
		for(i=0;i<50;i++)		//255个脉冲	
		{	
			P2=ReadyTwice;
			P_Beep=0;			//拉低
			LE373=1;
			LE373=0;
			P2=0xff;
		 	Delay250uS(2);
		 	
		 	P2=ReadyTwice;		//拉高
			LE373=1;
			LE373=0;
			P2=0xff;
		 	Delay250uS(2);
		 }
		 Delayms(100);			//延时0.5S
	}
}
void Power_dUp(void)
{
  RST=0;
  SCL=0;
  SDA=0;
  VPP=0;
  POWER=0;
  mDelay(20);
}
/*****************************************************************************
Function:     Power_off                                                   
*****************************************************************************/
void Power_off(void)
{ 
  SCL=0;
  SDA=0;
  RST=0;
  VPP=0;
  POWER=1;
  mDelay(10);
}
/***************************************************************************** 
Function:     I2C_Start                                                   
*****************************************************************************/
void I2C_Start(void)
{
  SDA=1;
  SCL=1;
  if(SDA==0)CY=1;
  if(SCL==0)return;
   _nop_();_nop_();
  SDA=0;
  _nop_();_nop_();
  _nop_();_nop_();
  SCL=0;
  CY=0;
  return;
}

/***************************************************************************** 
Function:     I2C_Stop                                                    
*****************************************************************************/
void I2C_Stop(void)
{ 
  SDA=0;
   _nop_();_nop_();
  SCL=1;
   _nop_();_nop_();
   _nop_();_nop_();
  SDA=1;
}
/***************************************************************************** 
Function:     I2C_WtByt                                                   
*****************************************************************************/
void I2C_WtByt(BYTE _data)
{
BYTE i;
for(i=8;i!=0;i--)
{ 
  _data<<=1;  
  SDA=CY; 
  _nop_();
  SCL=1;  
  _nop_();_nop_();
  _nop_();_nop_(); 
   SCL=0;				//??
}  
SDA=1;
_nop_();_nop_();
SCL=1;
_nop_();_nop_();
_nop_();_nop_();
CY=SDA;
SCL=0;
}
/*****************************************************************************
Function:     I2C_NoAck                                                   
*****************************************************************************/
void I2C_NoAck(void)
{
  SDA=1;
  _nop_();_nop_();
  SCL=1;
   _nop_();_nop_();
   _nop_();_nop_();
  SCL=0;
}
/***************************************************************************** 
Function:     I2C_Ack                                                     
*****************************************************************************/
void I2C_Ack(void)
{
SDA=0;
_nop_();_nop_();
SCL=1;
_nop_();_nop_();
_nop_();_nop_();
SCL=0;
}
/*****************************************************************************
Function:     I2C_RdByt                                                   
*****************************************************************************/
BYTE I2C_RdByt(void)
{
BYTE i,_data;
SDA=1;  
for(i=8;i!=0;i--)
{  
  _nop_();_nop_();
  SCL=1;
  _nop_();_nop_();
  if(SDA)
     _data=_data|0x01;
     else
     _data=_data&0xfe;
  _data<<=1;
  SCL=0;
}  
return(_data);
}
/***************************************************************************** 
Function:     I2C_WtIC                                                    
*****************************************************************************/
void I2C_WtIC(WORD Address,BYTE Data[],BYTE Num)
{
  BYTE i;
  BYTE *PData;
  PData=Data;
  for(i=0;i<Num;i++)
  {
    I2C_Start();
    I2C_WtByt(0xa0); 
    I2C_Ack();
    I2C_WtByt(Address+i);
    I2C_Ack();
    I2C_WtByt(*(PData+i));
    I2C_Ack();
    I2C_Stop(); 
    mDelay(20);
  }
}
/*****************************************************************************
Function:     I2C_RdIC                                                    
*****************************************************************************/
void I2C_RdIC(WORD Address,BYTE Data[],BYTE Num)
{
  BYTE i;
  BYTE *PData;
  PData=Data;
  I2C_Start();
  I2C_WtByt(0xa0); 
  I2C_Ack();
  I2C_WtByt(Address);
  I2C_Ack();
  I2C_Start();
  I2C_WtByt(0xa1);
  I2C_Ack();
  for(i=0;i<Num;i++)
  {
    *(PData+i)=I2C_RdByt();
    SCL=0;
    I2C_NoAck();
    I2C_Stop();
  }
}
/**********************************************************
*发送数据到Led1---Led4进行显示。
*入口参数： dat（低四位有效的4位数据）
*出口参数： 无
***********************************************************/
void DisplayData(Byte dat)
{
	if (dat&0x08)	LED4=0;	//Led4亮
	else	LED4=1;			//Led4灭
	P1=~(dat&0x07);		//Led1---Led3
}


/**********************************************************
*启动定时器函数：
*入口参数：bit tx （0：计数器0	1：定时器1）
*出口参数： 无
***********************************************************/
void StartTimer(bit tx)	
{
	TMOD=0x15;		//计数器0,定时器1
	TCON=0;
	IP=0;
	IE=0;
	if(!tx)
	{
		TH0=0xff;	//计数一次溢出
		TL0=0xff;
		ET0=1;
		TR0=1;
		EA=1;
	}
	else
	{
		TH1=0xEC;
		TL1=0x78;
		ET1=1;
		TR1=1;
		EA=1;	
	}
}
#pragma save
#pragma noregparms
Byte idata * MakeVoice(Word Num)
{
	Word 	Tmp;
	static 	Byte  	idata 	Musicbuf[5];			//千位，百位，十位，个位，0
	if (Num<10)
	{
		Musicbuf[0]=(Byte)(Num+1);
		Musicbuf[1]=0;
	}
	else if (Num<100)
	{
		Musicbuf[0]=Num/10+1;
		Musicbuf[1]=Num%10+1;
		Musicbuf[2]=0;
	}
	else if (Num<1000)
	{
		Musicbuf[0]=Num/100+1;
		Tmp=Num%100;
		Musicbuf[1]=Tmp/10+1;
		Musicbuf[2]=Tmp%10+1;
		Musicbuf[3]=0;
	}
	else if (Num<10000)
	{
		Musicbuf[0]=Num/1000+1;
		Tmp=Num%1000;
		Musicbuf[1]=Tmp/100+1;
		Tmp%=100;
		Musicbuf[2]=Tmp/10+1;
		Musicbuf[3]=Tmp%10+1;
		Musicbuf[4]=0;
	}
	else
	{
		Musicbuf[0]=10;
		Musicbuf[1]=10;
		Musicbuf[2]=10;
		Musicbuf[3]=10;
		Musicbuf[4]=0;
	}
	return Musicbuf;
}
#pragma restore
/**********************************************************
*停止定时器函数：
*入口参数：bit tx （0：计数器0	1：定时器1）
*出口参数： 无
***********************************************************/
void StopTimer(bit tx)	
{
	if(!tx)
	{
		TR0=0;
	}
	else
	{
		TR1=0;
	}
}

/**********************************************************
*片选脉冲	ISDPulse()
*入口参数： Number	第几段
*出口参数： 无
***********************************************************/
void PSearch(void)
{
	ISD_CE=0;			//CE加脉冲
	LE373=1;
	LE373=0;
	ISD_CE=1;
	LE373=1;
	LE373=0;
	StartTimer(0);		//启动定时器
	while(!FgT0Over);
	StopTimer(0);
	FgT0Over=0;
}


/**********************************************************
*放音函数PlayMusic()
*入口参数： Number	第几段
*出口参数： 无
***********************************************************/
void PlayMusic(Byte idata *p)
{	bit Tmpbb;
	Byte i;
    while(*p!=0)
	{	
		P_Speak=0;					//放音继电器吸合
		P0=0;	
		ISD_A8=1;
	    ISD_A9=1;
	    ISD_PD=1;					//PD=1地址复位
	    ISD_PR=1;
		LE373=1;
		LE373=0;
		Delayms(20);				//Tpud	Max=27.8ms
		ISD_PD=0;					//PD=0，开始操作
		LE373=1;
		LE373=0;
		ISD_A0=1;					//检索模式，连续寻址，开始搜索
		ISD_A4=1;
		for(i=0;i<*p-1;i++)
		{
			PSearch();
		}
		p++;
		ISD_A0=0;					// 退出检索，开始放音
		PSearch();
		Tmpbb=P_Online;
	 	P2=0xBF;					//此处片选置 1,继电器保持
	 	P_Online=Tmpbb;

		LE373=1;
		LE373=0;
		P2=0xff;
		P0=0xff;
	}
}


//**********************************************************
void main(void)
  {
    BYTE *Number={3,4,5,6,7,8,9,10};
    BYTE  *OutNumber;
    
	Byte i;
	InitCPUIO();
     Power_dUp(); 
     I2C_WtIC(10,Number,8);
     Power_off();
     mDelay(20); 

     Power_dUp();
     I2C_RdIC(10,OutNumber,8);
     Power_off();
	
	for (i=0;i<8;i++)
	{	
		DisplayData(i);
		if(*(OutNumber+i)==*(Number+i))
		{
		
			PlayMusic(MakeVoice(*(OutNumber+i)));
			SBeep(1);
	  		Delayms(2000);
		}
	}
}



//***********************************************************
//Timer0中断服务函数
void ISR_Timer0()	interrupt 1	using	1
{
	FgT0Over=1;
	TR0=0;
}
//说明:我用的是22.118M的晶体,如用12M,用(_nop())代替(_nop_();_nop_())即可(我没试)
// 好痛快!!!再次感谢cwcyxy兄,也请他原谅我的打扰!
