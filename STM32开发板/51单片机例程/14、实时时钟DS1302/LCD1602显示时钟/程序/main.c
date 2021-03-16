/*******************************************************************************
*                 
*                 		       ���пƼ�
--------------------------------------------------------------------------------
* ʵ �� ��		 : DS1302ʱ����ʾ����
* ʵ��˵��       : LCD1602��ʾʱ����Ϣ
* ���ӷ�ʽ       : ������ͼ
* ע    ��		 : 
*******************************************************************************/

#include<reg51.h>
#include"lcd.h"
#include"ds1302.h"

void LcdDisplay();

/*******************************************************************************
* ������         : main
* ��������		   : ������
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void main()
{
	LcdInit();
	Ds1302Init();
	while(1)
	{	
		Ds1302ReadTime();
		LcdDisplay();	
	}
	
}
/*******************************************************************************
* ������         : LcdDisplay()
* ��������		   : ��ʾ����
* ����           : ��
* ���         	 : ��
*******************************************************************************/

void LcdDisplay()
{
	LcdWriteCom(0x80+0X40);
	LcdWriteData('0'+TIME[2]/16);				//ʱ
	LcdWriteData('0'+(TIME[2]&0x0f));				 
	LcdWriteData('-');
	LcdWriteData('0'+TIME[1]/16);				//��
	LcdWriteData('0'+(TIME[1]&0x0f));	
	LcdWriteData('-');
	LcdWriteData('0'+TIME[0]/16);				//��
	LcdWriteData('0'+(TIME[0]&0x0f));

	LcdWriteCom(0x80);
	LcdWriteData('2');
	LcdWriteData('0');
	LcdWriteData('0'+TIME[6]/16);			//��
	LcdWriteData('0'+(TIME[6]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);			//��
	LcdWriteData('0'+(TIME[4]&0x0f));
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);			//��
	LcdWriteData('0'+(TIME[3]&0x0f));
	LcdWriteCom(0x8D);
	LcdWriteData('0'+(TIME[5]&0x07));	//����			 
}