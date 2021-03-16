#include "REG51.H"
#include "lcd_drive.h"
#include "gui.h"

void main(void)
{
	TFT_Init();
	TFT_ClearScreen(BLACK);   //��
	while(1)
	{
		GUI_Write32CnChar(60, 24, "���пƼ�", RED, BLACK); //
		GUI_Line(60, 54, 180, 54, RED);
		GUI_WriteASCII(0, 65, "2013", RED, BLACK);
		GUI_Write32CnChar(64, 60, "��", RED, BLACK);
		GUI_WriteASCII(90, 65, "12", RED, BLACK);
		GUI_Write32CnChar(122, 60, "��", RED, BLACK);
		GUI_WriteASCII(154, 65, "31", RED, BLACK);
		GUI_Write32CnChar(186, 60, "��", RED, BLACK);
		GUI_WriteASCII(0, 100, "12-00-00", RED, BLACK);
		GUI_Write32CnChar(128, 95, "����", RED, BLACK);
		GUI_WriteASCII(192, 100, "2", RED, BLACK);
		while(1);
	}
}
	