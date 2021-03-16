////////////////////////////////////////////////////////////////////////////
//                �����ߵ�Ƭ������ѧϰϵͳ������ѧϰ��������              //
////////////////////////////////////////////////////////////////////////////
//                     ѧϰ51��Ƭ������ʵ���Ժܼ�                       //
////////////////////////////////////////////////////////////////////////////
//                ����о���������޹�˾  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////
#include <AT89X52.h>       //����51��Ƭ����ͷ�ļ�
#include <Intrins.h>       //������Ҫʹ�ÿղ���������������ͷ�ļ�

sfr	 WDT_CONTR=0xe1;
//---------------------------------------
//W25Q16���I/O����
sbit CS          = P3^6;	//ѡͨ  
sbit DIO         = P3^5;   //��Ƭ�����
sbit DO          = P3^7;	//FLASH���
sbit SCLK        = P3^4;	//ʱ��
//---------------------------------------
//---------------------------------------
//LED���������I/O����
sbit U15E3=P1^3;           //LED��������Ԫ��U15(74HC138)��ʹ�ܶ�E3�Ž���P1.3����
sbit U14E3=P1^4;           //LED��������Ԫ��U14(74HC138)��ʹ�ܶ�E3�Ž���P1.4����
//---------------------------------------

//---------------------------------------
//LED�������Ĵ�������
unsigned char m=15;        //����8λ��unsigend char�ͼĴ���������������ʾ������
unsigned char n;           //����8λ��unsigend char�ͼĴ�����������ʱ��
unsigned char w;           //����8λ��unsigend char�ͼĴ�����������ʱ��
unsigned int  v;           //����8λ��unsigend char�ͼĴ����������ƶ�����
unsigned char  xdata hanzibuf1[512];
unsigned char  xdata hanzibuf2[512];
unsigned char L;
//---------------------------------------
//***************************************************************
#define W25X_ReadStatus       0x05		//��״̬�Ĵ���
#define W25X_WriteStatus      0x01		//д״̬�Ĵ���
#define W25X_ReadDATA8        0x03		//�ն�_����
#define W25X_FastRead         0x0B		//���_����
#define W25X_DualOutput       0x3B		//���_˫���
#define W25X_Write            0x02		//д_����_0~255���ֽ�
#define W25X_S_Erase          0x20		//��������4KB
#define W25X_B_Erase          0xD8		//��������64KB
#define W25X_C_Erase          0xC7		//��Ƭ��ʽ��
#define W25X_PowerDown        0xB9		//����
#define W25X_PowerON_ID       0xAB		//�������Ƕ�ID
#define W25X_JEDEC_ID         0x9F		//ʮ��λ��JEDEC_ID
#define W25X_WriteEnable      0x06		//д����
#define W25X_WriteDisable     0x04		//д��ֹ

unsigned char ComBuf[21];//����ͨѶ���ݻ��棬���ͺͽ��ն�ʹ��
unsigned int  nTimeOut;//��ʱ����
unsigned char Buf[16];

long neima(unsigned char qh,wh)
{
   unsigned long vb;	
	qh=qh-0xa0;   //�õ�����
	wh=wh-0xa0;   //�õ�����	
	vb=(94*(qh-1)+(wh-1));
	vb=vb<<5;		
	return vb;
} 

//---------------------------------------
//����: SPIд��һ���ֽں���
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
void Send_OneByte(unsigned char DATA8) //��SPI��8λ��
{			       				            //������д��
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
//����: SPI����һ���ֽں���
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
unsigned char Read_OneByte(void)     //��SPI��8λ��
   {						         //�½������
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
//����: д������
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
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
//����: д��ֹ����
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
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
//����: �ж�W25Q16æ����
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
unsigned char W25X_BUSY_OrNot (void) 	//�ڶ���д֮ǰ�����ж�FLASH�Ƿ�BUSY
{				         						//BUSY��ԭ���ǲ���������������д
   unsigned char k;          				//���û�����Ϸ�ʽ�������ж�����д��  
   SCLK=1;
   _nop_();
   CS=0;
   Send_OneByte(W25X_ReadStatus);   //��״̬�Ĵ���
   k=Read_OneByte();  					//��һ���ֽ�
   k=k&0x01;
   CS=1;
	_nop_();
   SCLK=1;
   return k;                         //����1��ʾæ������0��ʾ��æ   
}	
//---------------------------------------
//����: ��FLASH�洢����д���ݺ���
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
void W25X_Flash_Byte_Write(unsigned char AddreH,unsigned char AddreM,unsigned char AddreL)    
{						 		 
   unsigned char J;   //���ֽ���
   while(W25X_BUSY_OrNot ());  //��BUSY	�ȵ�Flash�в��ܲ���
   WriteEnable();   //д����
   SCLK=1;   
	_nop_();
	_nop_();
   CS=0;
   Send_OneByte(W25X_Write);  //����
   Send_OneByte(AddreH);
   Send_OneByte(AddreM);
   Send_OneByte(AddreL);
   for (J=0;J<16;J++)
   {
     	Send_OneByte(Buf[J]); //д�ֽ�
  	}
   CS=1;
   _nop_();
	_nop_();
   SCLK=1;
   for(J=0;J<200;J++) //��ʱһ���
   {
     _nop_();
	  _nop_();
   }
}	
//---------------------------------------
//����: ��FLASH�洢���ж����ݺ���
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
//�������ݷ�����Buf[]��
void W25X_Flash_Byte_Read (unsigned long Addre24,unsigned char Quantity)  //��Flash�����16�ֽ���
{
   unsigned char J;	 //���ֽ��� 
   unsigned char Addre3;
   unsigned char Addre2;
   unsigned char Addre1;
   while(W25X_BUSY_OrNot()==1);  //��BUSY
	Addre1=Addre24;
   Addre24=Addre24>>8;
   Addre2=Addre24;
   Addre24=Addre24>>8;
   Addre3=Addre24;
   CS=0;
   Send_OneByte(W25X_ReadDATA8);//�����
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);
   for (J=0;J<Quantity;J++)
   {
     	Buf[J]=Read_OneByte();	 //��һ���ֽ�
	}
   CS=1;
   _nop_();
	_nop_();
   SCLK=1;
   _nop_();
	_nop_();
}	  
//---------------------------------------
//����: 4K������������
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
void W25X_SectorErase(unsigned char AddreH,unsigned char AddreM,unsigned char AddreL)	//��������ͼʾ��4KB�ռ�
{
   WriteEnable();   //д����  

   SCLK=1;
   CS=0;
   Send_OneByte(W25X_S_Erase);//���Ȳ�������
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
//����: ��ʱ����
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
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
//����: �ȴ���λ��18�ֽں���
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
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
//����: ����λ������18�ֽں���
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
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
void zhuan(unsigned char i)            //�����ʾ16���֣�0-15
{
	unsigned char k,g;
	long Address;
	unsigned char zc;
	if(i<8)
	{
		W25X_Flash_Byte_Read(0x1fff00,16);//������16���ֽڣ�����BUF[]��	
		Address=neima(Buf[i*2],Buf[i*2+1]);
	}
	else if(i<16)
	{
		W25X_Flash_Byte_Read(0x1fff10,16);//������16���ֽڣ�����BUF[]��	
		Address=neima(Buf[(i-8)*2],Buf[(i-8)*2+1]);
	}		
	else if(i<24)
	{
		W25X_Flash_Byte_Read(0x1fff20,16);//������16���ֽڣ�����BUF[]��	
		Address=neima(Buf[(i-16)*2],Buf[(i-16)*2+1]);
	}
	else
	{
		W25X_Flash_Byte_Read(0x1fff30,16);//������16���ֽڣ�����BUF[]��	
		Address=neima(Buf[(i-24)*2],Buf[(i-24)*2+1]);
	}
	//W25X_Flash_Byte_Read(0x1fff00+(i/8)&0x10,16);//������16���ֽڣ�����BUF[]��	
	//Address=neima(Buf[(i%8)*2],Buf[(i%8)*2+1]);

	W25X_Flash_Byte_Read(Address,16);//������16���ֽڣ�����BUF[]��
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
	W25X_Flash_Byte_Read(Address+16,16);//������16���ֽڣ�����BUF[]��
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
//���ƣ������жϷ������
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void UART_SER (void) interrupt 4 
{
	if(RI==1)              //������ձ�־λΪ1��˵�������ݽ������
   {                      //RCIF�ڼĴ������������Զ�����
      ComBuf[0]=SBUF;     //�����ջ���������ת��USARTbuf�Ĵ�����
      RI=0;               //������ձ�־λ   
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
	if(ComBuf[0]==1) 	//�����λ����1��Ϊ��ʶ����
	{
		ComBuf[2]=6;
   	ComBuf[3]=2;
   	ComBuf[4]=4;  
  		SendData();  	//��ʶ����624������λ��
		while(1);
	}
	else if(ComBuf[0]==2) //�����λ����2��ΪдW25Q16
	{
		W25X_SectorErase(0x1F,0xFF,0);				
		Delay(10000); //
		SendData();//��Ӧ��λ����ʾ����д����״̬�����Է�������		
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
			if(ComBuf[1]==0x01)//����������ݳɹ�����ComBuf[0]==1��ʾ����д
			{						
				for(n=0;n<16;n++)
				{
					Buf[n]=ComBuf[n+2];  //�ѽ��յ���COMBUF[2]-[17]�ڵ������Ƶ�
					//BUF[0]-[15]�ڣ��Ա���������д������ʽ
				}		
				W25X_Flash_Byte_Write(ComBuf[18],ComBuf[19],ComBuf[20]);//ComBuf[2~17]Ϊ��д�����ݿ�
				SendData();					//֪ͨ��λ��������			
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
//����: ������
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void main(void)            //������,��Ƭ����������Ǵ����������ʼ����
{
	
    //*****USART���ڳ�ʼ��*****
	TMOD&=0x0F;            //��TMOD��4λ��0
	TMOD|=0x20;            //��TMOD��M1λ��1�����ó��Զ�װ���8λ��ʱ��
   TH1=0xFF;              //���ò�����Ϊ57600
   TL1=0xFF;              //���ò�����Ϊ57600
   TR1=1;                 //������ʱ��T1����Ϊ���ڲ����ʷ�����
   SCON=0x50;             //10λ�첽�շ����������ɶ�ʱ�����ƣ������ڽ���
	ES=1;                  //�������ж�
   //**************************	
	W25X_Flash_Byte_Read(0x1ffff0,16);//������16���ֽڣ�����BUF[]��
	L=Buf[12];
	for(nTimeOut=0;nTimeOut<512;nTimeOut++) hanzibuf1[nTimeOut]=0;
	for(nTimeOut=0;nTimeOut<512;nTimeOut++) hanzibuf2[nTimeOut]=0;
	for(n=0;n<L;n++) zhuan(n);				
	
	WDT_CONTR=0x3e;
	//12ʱ��ģʽ�����Ź����ʱ��=��12*Pre_scale*32768��/12000000
	//=	Pre_scale*393216/12000000
	//����Ϊ128��Ƶ�����Ź����ʱ��Ϊ2.1��

	//***��ȫ���ж�����****
    //���ڽӿ�UART�������ж�����,�˴�Ҫ��ȫ���ж�
    EA=1;                  //��ȫ���ж�
    //*********************
	while(1)               	//��ѭ��,��Ƭ����ʼ����,��һֱ���������ѭ��
    {    
	 	WDT_CONTR=0x3e;
		for(n=0;n<100;n++); 	//��һ��0-80��ѭ������ִ������������ֻΪ��ʱ
	   if(++w>250)        	//��Ƕ��һ����ʱ��ÿ220��ɨ�����ڽ���������һ��
      {
         w=0;           	//���㣬��׼����һ����ʱ
         if(++v>(L*16-1)) v=0;;					//�ƶ��������޶���0-191
      }
      if(++m>15) m=0;    	//ÿ����һ�κ�����m��1����������0-15����
      P1=0;              	//��LED���������п����ź�ȫ�����㣬׼������  
		if(m+v>511)
		{
			P0=0;		
			P2=0;             
		}
		else
		{
			P0=hanzibuf1[m+v];		
			P2=hanzibuf2[m+v]; //LED���������°�������m+16���������P2 
		}
      P1|=m&0x07;        	//������m�ĵ�3λ�͸�P1�ĵ�3λ����ʹ74HC138ȥƬѡ 
      if(m<8) U15E3=1;   	//ǰ8����Ҫʹ��U15(74HC138) 
      else U14E3=1;      	//��8����Ҫʹ��U14(74HC138)    	
   }
}

