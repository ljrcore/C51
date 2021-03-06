#include<stm32f10x.h>
#include"system.h"
#include"led.h"

void Delay(uint16_t);
/*********************************************************************************
*函数名：main
*功  能：主函数
*输  入：无
*输  出：无
**********************************************************************************/

int main(void)
{
	uint8_t endValue = 0;

	Set_SysClockTo72M();//倍频9倍
	Led_Init();

	while (1)
	{
		Led_Sets(endValue);
		endValue++;
		Delay(10);
	}
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
