#include<stm32f10x.h>
#include"system.h"
#include"led.h"

void Delay(uint16_t c);
/*********************************************************************************
*函数名：main
*功  能：主函数
*输  入：无
*输  出：无
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
		/****左移16次****/
		for (count=0; count<15; count++)
		{												 
			Led_Sets(endValue);
			/****当左移到最左边之后重新赋值****/
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

		/****右移16次****/
		for (count=0; count<15; count++)
		{												 
			Led_Sets(endValue);

			/****当右移移到最右边之后重新赋值****/
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
*函数名：Delay
*功  能：延时函数
*输  入：无
*输  出：无
**********************************************************************************/

void Delay(uint16_t c)
{
	uint16_t a, b;
	for (; c>0; c--)
		for (a=1000; a>0; a--)
			for (b=1000; b>0; b--);
}
