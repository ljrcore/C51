/*********************************************************************************************
*																                             *
*	                        ˫595����LED����ʵ�� 										     *
*                             		                                                         *
*	˵���� ����ĺ��̽ӿڷֱ����595������˿�JP2��P595									     *
*   ����(������ʾ1 2 3 4 5 6 7 8 9)													     *
*   ʵ��Ŀ�ģ�����LED����Ķ���ԭ���74HC595�ļ�������							             *
*             Ҫ��ѧԱ���� LED����Ĺ���ԭ��� ������ŵĶ��弰�ӷ������������ο�����˵��  *
**********************************************************************************************/
	
#include<reg51.h>
#include <intrins.h>

#define  NOP() _nop_()  /* �����ָ�� */

//SPI IO
sbit MOSIO =P3^4;   	 //����ܽ�
sbit R_CLK =P3^5;        //����ܽ�
sbit S_CLK =P3^6;        //����ܽ�

void HC595SendData(unsigned int SendVal);	  //595������������
void delay(unsigned char ms); 
	
	void main(void)
	{
	  while(1)
	  {
		 P0 = 0xff;
		 HC595SendData(0x00ff);
		 delay(250); delay(250);delay(250);delay(250);
		 P0 = 0xff;
		 HC595SendData(0xff00);
		 delay(250);delay(250);delay(250);delay(250);
		 P0 =  0x00;
		 HC595SendData(0x0000);
		 delay(250); delay(250);delay(250);delay(250);
	  }

    }
/*********************************************************************************************************
** ��������: HC595SendData
** ��������: ��SPI���߷�������
*********************************************************************************************************/
void HC595SendData(unsigned int SendVal)
{  
  unsigned char i;
		
  for(i=0;i<16;i++) 
   {
	if((SendVal<<i)&0x8000) MOSIO=1; //set dataline high  0X8000  ���λ��SendVal���Ƶ����λ �����߼�����
	else MOSIO=0;				   // ���Ϊ�� MOSIO = 1  
 
	S_CLK=0;
	NOP();
	NOP();
	S_CLK=1;	
   }
   
	
  R_CLK=0; //set dataline low
  NOP();
  NOP();
  R_CLK=1; //Ƭѡ

}

void delay(unsigned char ms)
{
  unsigned char i,j;
  for(i = 0;i < ms;i++)
    for(j= 0;j<110;j++);
}
	
