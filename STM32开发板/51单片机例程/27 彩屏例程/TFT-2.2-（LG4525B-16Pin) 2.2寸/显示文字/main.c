#include "REG51.H"
#include "lcd_driver.h"
#include "gui.h"

/****************************************************************************
*��������main
*��  �룺��
*��  ������
*��  �ܣ�������
****************************************************************************/

void main (void)
{
	TFT_Init();                   //��ʼ��TFT
	TFT_ClearScreen(BLACK);	  	  //ˢ��ɫ

	while(1)
	{
		GUI_Write32CnChar(25, 24, "���пƼ�", RED, BLACK);
		GUI_Line(30, 54, 150, 54, RED);
		GUI_WriteASCII(0, 65, "2013", RED, BLACK);
		GUI_Write32CnChar(64, 60, "��", RED, BLACK);
		GUI_WriteASCII(100, 65, "12", RED, BLACK);
		GUI_Write32CnChar(130, 60, "��", RED, BLACK);
		GUI_WriteASCII(160, 65, "31", RED, BLACK);
		//GUI_Write32CnChar(186, 60, "��", RED, BLACK);
		GUI_WriteASCII(0, 100, "12-00-00", RED, BLACK);
		GUI_Write32CnChar(0, 140, "����", RED, BLACK);
		GUI_WriteASCII(70, 140, "2", RED, BLACK);
		while(1);
	}		
}

	