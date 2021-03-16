#include"stm32f10x.h"
#include"led.h"

void Delay(uint16_t c);
/****************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/

int main(void)
{
	uint8_t endValue = 0;
	uint8_t count = 0;
	endValue = 0x01;
	LED_Init();
	while(1)
	{	
		/****左移16次****/
		for(count=0; count<15; count++)
		{												 
			LED_Sets(endValue);

			/****当左移到最左边之后重新赋值****/
			if(endValue == 0x80)
			{
				endValue = 0x01;
			}
			else
			{
				endValue <<= 1;
			}
			
			Delay(10);
		}
		/****右移16次****/
		for(count=0; count<15; count++)
		{												 
			LED_Sets(endValue);

			/****当右移移到最右边之后重新赋值****/
			if(endValue == 0x01)
			{
				endValue = 0x80;
			}
			else
			{
				endValue >>= 1;
			}
			
			Delay(10);
		}
	}
}
/*******************************************************************************
* Function Name  : Delay
* Description    : 延时程序
* Input          : c
* Output         : None
* Return         : None
*******************************************************************************/

void Delay(uint16_t c)
{
	uint16_t a, b;
	for(; c>0; c--)
		for(a=1000; a>0; a--)
			for(b=1000; b>0; b--);
}
