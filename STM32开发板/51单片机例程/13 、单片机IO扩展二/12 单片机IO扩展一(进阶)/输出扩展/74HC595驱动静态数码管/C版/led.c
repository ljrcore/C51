/*******************************************************************************
*  ����:                  ����74HC595�������������ʾ���֣�C���ԣ�             *
* 																			   *
*   ���ӷ�����JP595������ð�̽�  JP3��P595_A ��8PIN��������					       *													 
********************************************************************************
* ͨ���������˽� 74HC595�����벢��������ԭ���ʹ��  		                   *
*                         	       										       *
* ��ѧԱ�������������̣���74C595��C�����еĲ���                                *
********************************************************************************/


#include <reg51.h> 
#include <intrins.h>
#define  NOP() _nop_()  /* �����ָ�� */

//SPI IO
sbit MOSIO =P3^4;  //����������
sbit R_CLK =P3^5;  //���ݲ����������
sbit S_CLK =P3^6;  //����ʱ����


void delay(unsigned int i);      //��������
void HC595SendData(unsigned char SendVal);  //��������
 
// �˱�Ϊ LED ����ģ            // 0    1    2    3    4    5    6   7    8    9    A    b    c    d    E    -    L   P    U    Hidden  _ (20)
unsigned char code LED7Code[] = {~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};
 
main()
{  unsigned char  HC595SendVal;
   unsigned int LedNumVal;
   
  while(1)
  {	 
	 	LedNumVal++;
		HC595SendVal = LED7Code[LedNumVal%16];     //LED7;��ʾ0-F  LedNumVal%10 ��ʾ0-9
	    HC595SendData(HC595SendVal); //����595��������	
  		delay(200);
	 
  }   
}	
/*******************��ʱ����************/
void delay(unsigned int i)
{
    unsigned int j;
    for(i; i > 0; i--)	 //CPUѭ��ִ��i*300��
        for(j = 300; j > 0; j--);
}


/*********************************************************************************************************
** ��������: HC595SendData
** ��������: ��SPI���߷�������
*********************************************************************************************************/
void HC595SendData(unsigned char SendVal)
{  
  unsigned char i;
		
  for(i=0;i<8;i++) 
   {
	if((SendVal<<i)&0x80) MOSIO=1; //set dataline high  0X80  ���λ��SendVal���Ƶ����λ �����߼�����
	else MOSIO=0;				   // ���Ϊ�� MOSIO = 1  
 
	S_CLK=0;  
	NOP();	 //������ʱ����һ����ȵ������ź�
	NOP();	 //������ʱ
	S_CLK=1;
		
   }

 
  R_CLK=0; //set dataline low
  NOP();  //������ʱ
  NOP();  //������ʱ
  R_CLK=1; 	//
	

}

