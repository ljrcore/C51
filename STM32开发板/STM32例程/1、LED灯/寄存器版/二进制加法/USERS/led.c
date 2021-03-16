/*********************************************************************
**文 件 名：led.c
**版本信息：
**创 建 人：思良月
**完成时间：2013年7月3日
**摘    要：这个文件提供了将LED使用GPIO初始化和点亮的函数
*********************************************************************/

#include"led.h"
/********************************************************************
*函数名：Led_Init
*功  能：初始化LED所使用的IO
*输  入：无
*输  出：无
********************************************************************/

void Led_Init(void)
{
	GPIO_TypeDef *GPIOx;
	uint8_t pin, count;

	GPIOx = GPIO_LED;

	/*打开GPIOB的时钟*/
	RCC->APB2ENR |= RCC_LED;

	/*设置PIN口的输出模式*/
	pin = PIN_LED & 0x00FF;//取低八位是否有设置

	if (pin != 0x00)
	{
		for (count=0; count<8; count++)//一共设置8位
		{
			if ((pin & 0x01) != 0x00)
			{
				GPIOx->CRL &= (~((uint32_t)0x0F << (count * 4)));
				GPIOx->CRL |= ((uint32_t)GPIOMODE_LED << (count * 4));
			}
			pin >>= 1;
		}
	}
	pin = (uint8_t)(PIN_LED >> 8);//取高8位是否有设置
	if (pin != 0x00)
	{
		for (count=0; count<8; count++)
		{
			if ((pin&0x01) != 0x00)
			{
				/*清除原来的设置，然后设置GPIO模式*/
				GPIOx->CRH &= (~((uint32_t)0x0F << (count * 4)));
				GPIOx->CRH |= ((uint32_t)GPIOMODE_LED << (count * 4));
			}
			pin >>= 1;
		}
	}
	/*初始化输出为0*/
	GPIOx->ODR = 0x00;
}
/********************************************************************
*函数名：LED1
*功  能：设置LED1的状态
*输  入：无
*输  出：无
********************************************************************/

void LED1(uint8_t status)
{
	GPIO_TypeDef *GPIOx;

	GPIOx = GPIO_LED;

	if (status != 0)
	{
		GPIOx->BSRR = PIN_LED1;
	}
	else
	{	
		GPIOx->BRR = PIN_LED1;
	}
}

/*********************************************************************
*函数名：LED1
*功  能：设置LED1的状态
*输  入：无
*输  出：无
*********************************************************************/

void Led_Sets(uint8_t data)
{
	GPIO_TypeDef *GPIOx;

	GPIOx = GPIO_LED;

	GPIOx->ODR &= (~PIN_LED);
	GPIOx->ODR |= ((uint16_t)(data << 8));
}

