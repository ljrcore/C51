////////////////////////////////////////////////////////////////////////////
//                �����ߵ�Ƭ������ѧϰϵͳ������ѧϰ��������              //
////////////////////////////////////////////////////////////////////////////
//                     ѧϰ51��Ƭ������ʵ���Ժܼ�                       //
////////////////////////////////////////////////////////////////////////////
//                ����о���������޹�˾  www.MovingChip.com                //
////////////////////////////////////////////////////////////////////////////

#include <AT89X52.h>       //����51��Ƭ����ͷ�ļ�
#include <intrins.h>       //����λ�ƺ�_nop_();

//---------------------------------------
//1602Һ�����I/O����
sbit E=P2^3;               //1602Һ����E�Ž���P2.3����
sbit RW=P2^4;              //1602Һ����RW�Ž���P2.4����
sbit RS=P2^5;              //1602Һ����RS�Ž���P2.5����
//---------------------------------------

//---------------------------------------
//W25Q16���I/O����
sbit CS          = P3^6;	//ѡͨ  
sbit DIO         = P3^5;   //��Ƭ�����
sbit DO          = P3^7;	//FLASH���
sbit SCLK        = P3^4;	//ʱ��
//---------------------------------------

//---------------------------------------
//1602Һ���Ĵ�������
unsigned char DISbuf;     //����8λ��unsigend char�ͼĴ��������ݴ�1602Ҫ��ʾ������
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


unsigned char xdata Send_DATA[2];	 //Ҫ���͵�����
unsigned char xdata Recv_DATA[2];	 //�ѽ��յ�����, ��2��������ΪRecv_DATA[0] Recv_DATA[1]

//---------------------------------------
//���ƣ�1602Һ������ʱ����
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void Delay1602(unsigned int t)
{ 
     unsigned int k;      //����һ��16λ�Ĵ�����������ʱ�� 
     for(k=0;k<t;k++);    //��ʱ 
} 

//---------------------------------------
//���ƣ�1602Һ��æ��⺯��
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void LCD1602_busy(void)
{ 
     P0_7=1;              //��P0.7��1��Ϊ��״̬��׼�� 
     RS=0;                //RS=0��RW=1��E=1ʱ��æ�ź������DB7����P0.7����
     RW=1;                //RS=0��RW=1��E=1ʱ��æ�ź������DB7����P0.7����
     E=1;                 //RS=0��RW=1��E=1ʱ��æ�ź������DB7����P0.7����
     while(P0_7==1);      //��P0.7����1����ʾ1602Һ��æ����Ҫ�ȴ�
     E=0;                 //�����Ժ󣬻ָ�E�ĵ�ƽ
} 

//---------------------------------------
//���ƣ�1600д�����
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void LCD1602_Write_com(unsigned char combuf)
{ 
     RS=0;                //ѡ��ָ��Ĵ���
     RW=0;                //ѡ��д״̬
     P0=combuf;           //��������ͨ��P0������DB
     E=1;                 //E�ߵ�ƽ��������д��1602Һ��
     E=0;                 //д���Ժ󣬻ָ�E�ĵ�ƽ
} 

//---------------------------------------
//���ƣ�1602д�����(��æ���)
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void LCD1602_Write_com_busy(unsigned char combuf)
{ 
     LCD1602_busy();            //����æ��⺯��
     LCD1602_Write_com(combuf); //����æ��⺯��
} 

//---------------------------------------
//���ƣ�1602д���ݺ���(��æ���)
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void LCD1602_Write_data_busy(unsigned char databuf)
{ 
     LCD1602_busy();      //����æ��⺯��
     RS=1;                //ѡ�����ݼĴ���
     RW=0;                //ѡ��д״̬
     P0=databuf;          //��������ͨ��P0������DB
     E=1;                 //E�ߵ�ƽ��������д��1602Һ��
     E=0;                 //д���Ժ󣬻ָ�E�ĵ�ƽ
} 

//---------------------------------------
//���ƣ�1602Һ����ʾ��ַд����
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void LCD1602_Write_address(unsigned char x,unsigned char y)
{ 
     x&=0x0f;             //�е�ַ������0-15��
     y&=0x01;             //�е�ַ������0-1��
     if(y==0)             //����ǵ�һ��
         LCD1602_Write_com_busy(x|0x80);        //���е�ַд��
     else                 //����ǵڶ���
         LCD1602_Write_com_busy((x+0x40)|0x80); //���е�ַд��
} 

//---------------------------------------
//���ƣ�1602Һ����ʼ������
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void LCD1602_init(void)
{ 
     Delay1602(1500);               //������ʱ����
     LCD1602_Write_com(0x38);       //8λ�������ߣ�������ʾģʽ��5*7������ʾ
     Delay1602(500);                //������ʱ����
     LCD1602_Write_com(0x38);       //8λ�������ߣ�������ʾģʽ��5*7������ʾ
     Delay1602(500);                //������ʱ����
     LCD1602_Write_com(0x38);       //8λ�������ߣ�������ʾģʽ��5*7������ʾ
     LCD1602_Write_com_busy(0x38);  //8λ�������ߣ�������ʾģʽ��5*7������ʾ
     LCD1602_Write_com_busy(0x08);  //��ʾ���ܹأ��޹��
     LCD1602_Write_com_busy(0x01);  //����
     LCD1602_Write_com_busy(0x06);  //д���µ����ݺ󣬹�����ƣ���ʾ�����ƶ�
     LCD1602_Write_com_busy(0x0C);  //��ʾ���ܿ����޹��
} 

//---------------------------------------
//���ƣ�1602Һ��ָ����ַ��ʾ����
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120914
//---------------------------------------
void LCD1602_Disp(unsigned char x,unsigned char y,unsigned char buf)
{ 
     LCD1602_Write_address(x,y);    //�Ƚ���ַ��Ϣд��
     LCD1602_Write_data_busy(buf);  //��д��Ҫ��ʾ������
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
//Addre24Ϊ24λ��ַ����ʽΪ0xYYYYYY
//QuantityΪд��������������ΧΪ0-255
//����д��ʱ�򣬵�ַ����λ�����00��ʼд
//���256���ֽڶ�������д�������ֽڵ�ַ���һ���ֽڱ���Ϊ0
//���򵱵�ַԽ������ʱ����ӱ�ҳ��00���¿�ʼ����ɴ�д
//д��������ҪԤ�ȷ�����Send_DATA[]��
void W25X_Flash_Byte_Write(unsigned long Addre24,unsigned char Quantity)    
   {						 		 
   unsigned char Addre3;	 //
   unsigned char Addre2;	 //
   unsigned char Addre1;
   unsigned char J;   //���ֽ���
   unsigned char x;

   while(W25X_BUSY_OrNot ());  //��BUSY	�ȵ�Flash�в��ܲ���

   WriteEnable();   //д����
   SCLK=1;
   Addre1=Addre24;
   Addre24=Addre24>>8;
   Addre2=Addre24;
   Addre24=Addre24>>8;
   Addre3=Addre24;		    //�ѵ�ַ����
   
   CS=0;
   Send_OneByte(W25X_Write);  //����
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);

   for (J=0;J<Quantity;J++)
   {
     Send_OneByte(Send_DATA[J]); //д�ֽ�
  	}
   CS=1;
   _nop_();
	_nop_();
   SCLK=1;
   for(x=0;x<200;x++) //��ʱһ���
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
//Addre24Ϊ24λ��ַ����ʽΪ0xYYYYYY
//QuantityΪ����������������ΧΪ0-255
//�������ݷ�����Recv_DATA[]��
void W25X_Flash_Byte_Read (unsigned long Addre24,unsigned char Quantity)  //��Flash�����С��256�ֽ���
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
   Addre3=Addre24;		 //�ѵ�ַ����
   
   CS=0;
   Send_OneByte(W25X_ReadDATA8);//�����
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);

   for (J=0;J<Quantity;J++)
   {
     Recv_DATA[J]=Read_OneByte();	 //��һ���ֽ�
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
void W25X_SectorErase(unsigned long Addre24)	//��������ͼʾ��4KB�ռ�
{

   unsigned char Addre3;
   unsigned char Addre2;
   unsigned char Addre1;

   WriteEnable();   //д����
   Addre1=Addre24;
   Addre24=Addre24>>8;
   Addre2=Addre24;
   Addre24=Addre24>>8;
   Addre3=Addre24;		 //�ѵ�ַ����

   SCLK=1;
   CS=0;
   Send_OneByte(W25X_S_Erase);//���Ȳ�������
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);
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
void W25X_BlockErase(unsigned long Addre24)	//��������ͼʾ��64KB�ռ�
{
   unsigned char Addre3;
   unsigned char Addre2;
   unsigned char Addre1;

   WriteEnable();   //д����
   Addre1=Addre24;
   Addre24=Addre24>>8;
   Addre2=Addre24;
   Addre24=Addre24>>8;
   Addre3=Addre24;		 //�ѵ�ַ����

   SCLK=1;
   CS=0;
   Send_OneByte(W25X_B_Erase);//���Ȳ�������
   Send_OneByte(Addre3);
   Send_OneByte(Addre2);
   Send_OneByte(Addre1);
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
//����: ������
//���ã�������GL9��Ƭ������ѧϰϵͳ
//��˾������о���������޹�˾
//��ַ��www.MovingChip.com
//���ڣ�20120916
//---------------------------------------
void main(void)            //������,��Ƭ����������Ǵ����������ʼ����
{
	LCD1602_init();        //����1602Һ����ʼ������
 	W25X_Flash_Byte_Read (0x000000,1);  //��1����
	Send_DATA[0]=Recv_DATA[0]+1;  	
  	W25X_SectorErase(0); 
  	Delay(4000); //
   W25X_Flash_Byte_Write(0x000000,1);  //д1����  
  	
	//**��1602��ʾ�Ĵ�����ֵ(0-255)**
   DISbuf=Send_DATA[0];          //
   //*******************************

   //***1602Һ����ʾ0-255***
   LCD1602_Disp(0,0,DISbuf/100+'0');      //�ڵ�1�еĵ�1����ʾ��λ
   LCD1602_Disp(1,0,(DISbuf%100)/10+'0'); //�ڵ�1�еĵ�2����ʾʮλ
   LCD1602_Disp(2,0,DISbuf%10+'0');       //�ڵ�1�еĵ�3����ʾ��λ
   //***********************
   while(1)               //��ѭ��,��Ƭ����ʼ����,��һֱ���������ѭ��
   {
   	
	}			   
}	

