#include "REG51.H"
//#include "lcd_driver.h"
#include "touch.h"
#include "gui.h"
#include<stdio.h>

/****************************************************************************
*��������main
*��  �룺��
*��  ������
*��  �ܣ�������
****************************************************************************/

void main (void)
{
	uchar rst = 0;
	//--���������ֵʹ�������ڴ��������ı����ָ���--//
	uchar  xValue[6] = {0, 0, 0, 0, 0, 0}, yValue[6] = {0, 0, 0, 0, 0, 0};
	long x, y;

	TFT_Init();
	rst = 1;

	while(1)
	{
		if(rst == 1)
		{	
			TFT_ClearScreen(0x0000);
			GUI_Write32CnChar(20, 24, "���пƼ�", 0xF800, 0x0000);
			GUI_Line(20, 54, 140, 54, 0xF800);
			GUI_Line(20, 54, 140, 54, 0xF800);
			GUI_WriteASCII(127, 0, "RST", 0xF800, 0x0000);
			rst = 0;
		}

		if(TOUCH_XPT_ReadXY() == 1)
		{
			//--�����������ʾ����ƫ�ƣ����Ը�����ʾADֵ--//
			//--�������湫ʽ�������ֵ--//
			x = xpt_xy.x;
			x = (x - 304)*175/3422; 
			y =	xpt_xy.y;
			y = (y - 256) *219/3340;



			if (x > 175 )
			{
				x = 174;
			}
			if (y > 219)
			{
				y = 218;
			}
			if ((x > 127) && (y < 24))
			{
				rst = 1;
			}
			else
			{
				GUI_Dot((uint)x , (uint)y, 0x001F);
				//--�����ȡ����ADֵ--//
				//--�����������ʾADֵ��������Ҫʱ�䣬���Դ�����һ���ӳ�--//xpt_xy.
				xValue[1] = (xpt_xy.x % 10000 /1000) + '0';
				xValue[2] = (xpt_xy.x % 1000 /100) + '0';
				xValue[3] = (xpt_xy.x % 100 /10) + '0';
				xValue[4] = (xpt_xy.x % 10) + '0';

				yValue[1] = (xpt_xy.y % 10000 /1000) + '0';
				yValue[2] = (xpt_xy.y % 1000 /100) + '0';
				yValue[3] = (xpt_xy.y % 100 /10) + '0';
				yValue[4] = (xpt_xy.y % 10) + '0';

				//--��ʾADֵ--//
				GUI_WriteASCII(0, 170, "X:", 0xF800, 0x0000);
				GUI_WriteASCII(32, 170, &xValue[1], 0xF800, 0x0000);	
				GUI_WriteASCII(0, 195, "Y:", 0xF800, 0x0000);
				GUI_WriteASCII(32, 195, &yValue[1], 0xF800, 0x0000);
			}
		}
	}
}

	