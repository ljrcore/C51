#include<stm32f10x.h>
#include"system.h"
#include"led.h"

void Delay(uint16_t c);
/*********************************************************************************
*��������main
*��  �ܣ�������
*��  �룺��
*��  ������
**********************************************************************************/

int main(void)
{
	uint8_t endValue = 0;
	uint8_t count = 0;

	endValue = 0x01;

	Set_SysClockTo72M();
	Led_Init();

	while (1)
	{	
		/****����16��****/
		for (count=0; count<15; count++)
		{												 
			Led_Sets(endValue);
			/****�����Ƶ������֮�����¸�ֵ****/
			if (endValue == 0x80)
			{
				endValue = 0x01;
			}			
			else
			{
				endValue <<= 1;
			}

			Delay(10);
		}/*end of for (count=0; count<15; count++)*/

		/****����16��****/
		for (count=0; count<15; count++)
		{												 
			Led_Sets(endValue);

			/****�������Ƶ����ұ�֮�����¸�ֵ****/
			if (endValue==0x01)
			{
				endValue=0x80;
			}			
			else
			{
				endValue >>= 1;
			}
			
			Delay(10);
		}/*end of for (count=0; count<15; count++)*/
	}/*end of while (1)*/
}
/*********************************************************************************
*��������Delay
*��  �ܣ���ʱ����
*��  �룺��
*��  ������
**********************************************************************************/

void Delay(uint16_t c)
{
	uint16_t a, b;
	for (; c>0; c--)
		for (a=1000; a>0; a--)
			for (b=1000; b>0; b--);
}
