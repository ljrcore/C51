#include <system.h>
 //**********ʱ��оƬ�������**********************
void InitTimer()
{
  unsigned char td[8]={0,0,0x00,0x59,0x23,0x31,0x05,0x01};	//�����ʼ����

  unsigned char td1[1]={8};	//�����ʼ����

  ISendStr(PCF8563,0,td,8);	//��ʼ��PCF8563 
  delay(50);
  ISendStr(PCF8563,8,td,1);	//��ʼ��PCF8563 
}

  

//�õ�ʵʱʱ�ӵ�ʱ��ֵ
unsigned int TimerTick=0;
void GetTimer()
{
    if(TickOut(&TimerTick,100))
    {  
	   unsigned char i;
	   unsigned char rd[10];  //����ʵʱʱ�����ݻ�����

       IRcvStr(PCF8563,2,rd,6);    //�����ڵ�ʱ���֡���
       rd[0]&=0x7f; 
	   rd[1]&=0x7f; 
	   rd[2]&=0x3f; 
	   rd[3]&=0x3f;
	   rd[4]&=0x07;
	   rd[5]&=0x1f;

	   for(i=0; i<6; i++) D[6+i]=(rd[i]>>4)*10+(rd[i]&0x0f); 
 
    }
}

