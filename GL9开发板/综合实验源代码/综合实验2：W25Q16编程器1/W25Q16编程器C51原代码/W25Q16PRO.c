////////////////////////////////////////////////////////////////////////////
//                �����ߵ�Ƭ������ѧϰϵͳ������ѧϰ��������              //
////////////////////////////////////////////////////////////////////////////
//                     ѧϰ51��Ƭ������ʵ���Ժܼ�                       //
////////////////////////////////////////////////////////////////////////////
//                ����о���������޹�˾  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////
#include <AT89X52.h>       //����51��Ƭ����ͷ�ļ�
#include <Intrins.h>       //������Ҫʹ�ÿղ���������������ͷ�ļ�

//---------------------------------------
//W25Q16���I/O����
sbit CS          = P3^6;	//ѡͨ  
sbit DIO         = P3^5;   //��Ƭ�����
sbit DO          = P3^7;	//FLASH���
sbit SCLK        = P3^4;	//ʱ��
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
unsigned char n;	
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
void W25X_Flash_Byte_Read (unsigned char AddreH,unsigned char AddreM,unsigned char AddreL)  //��Flash�����16�ֽ���
{
   unsigned char J;	 //���ֽ���   
   while(W25X_BUSY_OrNot()==1);  //��BUSY
	_nop_();
	_nop_();
   CS=0;
   Send_OneByte(W25X_ReadDATA8);//�����
   Send_OneByte(AddreH);
   Send_OneByte(AddreM);
   Send_OneByte(AddreL);
   for (J=0;J<16;J++)
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
//����: ��Ƭ��������
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
void W25X_ChipErase(void)
{
  	WriteEnable();              //д����
  	SCLK=1;
  	CS=0;
  	Send_OneByte(W25X_C_Erase);//��Ƭ��������
  	CS=1;	                     //��CS=1ʱ��ʼִ�в���
  	SCLK=1;  
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
//����: 64K������������
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
void W25X_BlockErase(unsigned char AddreH,unsigned char AddreM,unsigned char AddreL)	//��������ͼʾ��64KB�ռ�
{
   WriteEnable();   //д����

   SCLK=1;
   CS=0;
   Send_OneByte(W25X_B_Erase);//���Ȳ�������
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
//����: ����λ������18�ֽں���
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
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
	ES=0;                  //��ֹ�����ж�
   //**************************
	while(1)               //��ѭ��,��Ƭ����ʼ����,��һֱ���������ѭ��
   	{    
   		if(WaitData()==1)   //������ճɹ�
		{		
			if(ComBuf[0]==1) //�����λ����1��Ϊ��ʶ����
			{
				ComBuf[2]=6;
    			ComBuf[3]=2;
    			ComBuf[4]=4;  
  				SendData();  //��ʶ����624������λ��
			}
			else if(ComBuf[0]==2) //�����λ����2��ΪдW25Q16
			{
				SendData();//��Ӧ��λ����ʾ����д����״̬�����Է�������		
				while(1)
				{
					if(WaitData()==1&&ComBuf[1]==0x01)//����������ݳɹ�����ComBuf[0]==1��ʾ����д
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
						break;  //�˳�while(1)
					}
				}		
			}	
			else if(ComBuf[0]==3) //�����λ����3��Ϊ��W25Q16
			{
				SendData();//��Ӧ��λ����ʾ�����״̬				
				while(1)
				{
					if(WaitData()==1&&ComBuf[1]==1)//����������ݳɹ�����ComBuf[0]==1��ʾ������
					{
						W25X_Flash_Byte_Read(ComBuf[18],ComBuf[19],ComBuf[20]);//��Address��ʼ��������16���ֽڣ�����BUF[]��
						for(n=0;n<16;n++)
						{
							ComBuf[n+2]=Buf[n];				
						}			
						SendData();				
					}
					else
					{
						break;  //�˳�while(1)
					}
				}		
			}
			else if(ComBuf[0]==4) //�����λ����4��Ϊ��Ƭ����(2M bytes)
			{
				SendData();//��Ӧ��λ����ʾ������Ƭ����					
				W25X_ChipErase();				
				Delay(50000); //
			}
			else if(ComBuf[0]==5) //�����λ����5��Ϊ��������(64K bytes)
			{
				SendData();//��Ӧ��λ����ʾ�����������				
				W25X_BlockErase(ComBuf[18],ComBuf[19],0);				
				Delay(8000); //
			}
			else if(ComBuf[0]==6) //�����λ����6��Ϊ��������(4K bytes)
			{
				SendData();//��Ӧ��λ����ʾ������������				
				W25X_SectorErase(ComBuf[18],ComBuf[19],0);				
				Delay(8000); //
			}
		}     
   	}
}

