#include "REG51.H"
#include "lcd_driver.h"

/****************************************************************************
*��������main
*��  �룺��
*��  ������
*��  �ܣ�������
****************************************************************************/

void main (void)
{
	TFT_Init();                   //��ʼ��TFT

	while(1)
	{
		TFT_ClearScreen(BLACK);	  //ˢ��ɫ
		TFT_ClearScreen(BLUE);
		TFT_ClearScreen(RED);
		TFT_ClearScreen(MAGENTA);
		TFT_ClearScreen(GREEN);
		TFT_ClearScreen(CYAN);
		TFT_ClearScreen(YELLOW);
		TFT_ClearScreen(WHITE);		
	}
}

	