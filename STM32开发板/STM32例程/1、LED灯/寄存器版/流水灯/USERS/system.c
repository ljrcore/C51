/*********************************************************************
**文 件 名：system.c
**版本信息：
**创 建 人：思良月
**完成时间：2013年7月3日
**摘    要：这个文件提供了将系统时钟初始化到72MHZ的函数
*********************************************************************/

#include"system.h"
/********************************************************************
*函数名：Set_SysClockTo72M
*功  能：设置系统的时钟
*输  入：Pll
*输  出：
********************************************************************/

void Set_SysClockTo72M(void)
{
	uint32_t rccCrHserdy = 0;
	uint32_t faultTime = 0;

	/*复位RCC_CR寄存器*/
	RCC->CR = RCC_CR_RESET;

	/*开启外部时钟*/
	RCC->CR &= (~RCC_CR_HSEON);
	RCC->CR |= RCC_CR_HSEON;//设置第16位

	/*检测外部时钟开启成功*/
	do
	{
		rccCrHserdy = RCC->CR & RCC_CR_HSERDY;//检测第17位是否为1
		faultTime++;//检测时间
	}
	while ((faultTime<0x0FFFFFFF) && (rccCrHserdy==0));
	/* 如果外部时钟开启成功*/
	if ((RCC->CR & RCC_CR_HSERDY) != 0)
	{
		/* Enable Prefetch Buffer */
	    FLASH->ACR |= FLASH_ACR_PRFTBE;

	    /* Flash 2 wait state */
	    FLASH->ACR &= (~(uint32_t)FLASH_ACR_LATENCY);
	    FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_2;  

		/*AHB（0000）、APB2（000）不分频（即PLL输出时钟）*/
		/*APB1（100）要2分频（因最大只能36MHZ）*/
		RCC->CFGR &= (~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2));
		RCC->CFGR |= (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2
		              | RCC_CFGR_PPRE2_DIV1);

		/*设置HSE为输入时钟，同事HSE不分频*/
		RCC->CFGR &= (~(uint32_t)(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE ));
		RCC->CFGR |= (RCC_CFGR_PLLSRC);

		/*设置PLL倍频系数为9倍*/
		RCC->CFGR &= (~RCC_CFGR_PLLMULL);//先清除原来的设置
		RCC->CFGR |= (RCC_CFGR_PLLMULL8);//设置倍频系数

		/*打开PLL使能*/
		RCC->CR |= RCC_CR_PLLON;

		/*等待开启PLL开启成功*/
		while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		{
		}

		/*将PLL作为SYSCLK的时候来源*/
		RCC->CFGR &= (~RCC_CFGR_SW);//先清除先前的设置
		RCC->CFGR |= RCC_CFGR_SW_PLL;

		/*等待PLL作为SYSCLK时钟启动成功*/
		while ((RCC->CFGR & RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
		{
		}
	}/*end of if((RCC->CR & RCC_CR_HSERDY) != 0)*/
	/*如果外部时钟开启失败*/
	else
	{
		while (1)
		{
		}
	}	
}
