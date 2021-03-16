/*********************************************************************
**�� �� ����system.c
**�汾��Ϣ��
**�� �� �ˣ�˼����
**���ʱ�䣺2013��7��3��
**ժ    Ҫ������ļ��ṩ�˽�ϵͳʱ�ӳ�ʼ����72MHZ�ĺ���
*********************************************************************/

#include"system.h"
/********************************************************************
*��������Set_SysClockTo72M
*��  �ܣ�����ϵͳ��ʱ��
*��  �룺Pll
*��  ����
********************************************************************/

void Set_SysClockTo72M(void)
{
	uint32_t rccCrHserdy = 0;
	uint32_t faultTime = 0;

	/*��λRCC_CR�Ĵ���*/
	RCC->CR = RCC_CR_RESET;

	/*�����ⲿʱ��*/
	RCC->CR &= (~RCC_CR_HSEON);
	RCC->CR |= RCC_CR_HSEON;//���õ�16λ

	/*����ⲿʱ�ӿ����ɹ�*/
	do
	{
		rccCrHserdy = RCC->CR & RCC_CR_HSERDY;//����17λ�Ƿ�Ϊ1
		faultTime++;//���ʱ��
	}
	while ((faultTime<0x0FFFFFFF) && (rccCrHserdy==0));
	/* ����ⲿʱ�ӿ����ɹ�*/
	if ((RCC->CR & RCC_CR_HSERDY) != 0)
	{
		/* Enable Prefetch Buffer */
	    FLASH->ACR |= FLASH_ACR_PRFTBE;

	    /* Flash 2 wait state */
	    FLASH->ACR &= (~(uint32_t)FLASH_ACR_LATENCY);
	    FLASH->ACR |= (uint32_t) FLASH_ACR_LATENCY_2;  

		/*AHB��0000����APB2��000������Ƶ����PLL���ʱ�ӣ�*/
		/*APB1��100��Ҫ2��Ƶ�������ֻ��36MHZ��*/
		RCC->CFGR &= (~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2));
		RCC->CFGR |= (RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV2
		              | RCC_CFGR_PPRE2_DIV1);

		/*����HSEΪ����ʱ�ӣ�ͬ��HSE����Ƶ*/
		RCC->CFGR &= (~(uint32_t)(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE ));
		RCC->CFGR |= (RCC_CFGR_PLLSRC);

		/*����PLL��Ƶϵ��Ϊ9��*/
		RCC->CFGR &= (~RCC_CFGR_PLLMULL);//�����ԭ��������
		RCC->CFGR |= (RCC_CFGR_PLLMULL8);//���ñ�Ƶϵ��

		/*��PLLʹ��*/
		RCC->CR |= RCC_CR_PLLON;

		/*�ȴ�����PLL�����ɹ�*/
		while ((RCC->CR & RCC_CR_PLLRDY) == 0)
		{
		}

		/*��PLL��ΪSYSCLK��ʱ����Դ*/
		RCC->CFGR &= (~RCC_CFGR_SW);//�������ǰ������
		RCC->CFGR |= RCC_CFGR_SW_PLL;

		/*�ȴ�PLL��ΪSYSCLKʱ�������ɹ�*/
		while ((RCC->CFGR & RCC_CFGR_SWS) != (uint32_t)RCC_CFGR_SWS_PLL)
		{
		}
	}/*end of if((RCC->CR & RCC_CR_HSERDY) != 0)*/
	/*����ⲿʱ�ӿ���ʧ��*/
	else
	{
		while (1)
		{
		}
	}	
}
