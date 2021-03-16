/***************************���пƼ� www.prechin.com****************************
	                          STM32-��������ʵ��
 ʵ��Ŀ�ģ� ��Ϥ�˽�STM32GPIO�Ĳ����Ϳ⺯����ʹ��
 ���ӷ����� �ο�����ͼƬ
 ʵ������	ûǰ��3����ť ����LED���� �ɿ�LED��

*******************************************************************************/

#include "stm32f10x_lib.h"

/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);


/*******************************************************************************
                                  ������
*******************************************************************************/
int main(void)
{ //int retval;
#ifdef DEBUG
  debug();
#endif

  RCC_Configuration(); //ϵͳʱ�����ú���    

  NVIC_Configuration();	 //NVIC���ú���

  //ʹ��APB2��������ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //�رյ��� �˿�����ӳ��  ʹ�÷���������ʱ�������ô���

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; // ѡ�����н�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //���ó�����ʽ���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
   GPIO_Init(GPIOA, &GPIO_InitStructure);  //��PA��ʼ��
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;  // ѡ�����н�
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //���ó�����ʽ����
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //���ģʽ�� I/O����ٶ� 50M HZ
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //��ʼ��PB��


  GPIO_Write(GPIOA,0Xffff); //��ʼ��PA�˿��� LED����Ϩ��״̬
 
  while (1)
  { 
 /* 	if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8))  //���PB�ڵĵ�9���ܽŵĵ�ƽ
	GPIO_ResetBits(GPIOA,GPIO_Pin_0); //ʹ��1���ܽ�Ϊ 0 
	else
	GPIO_SetBits(GPIOA,GPIO_Pin_0);	  //ʹ��1���ܽ�Ϊ 1

	if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9))  //���PB�ڵĵ�10���ܽŵĵ�ƽ
	GPIO_ResetBits(GPIOA,GPIO_Pin_1); //ʹ��2���ܽ�Ϊ 0 
	else
	GPIO_SetBits(GPIOA,GPIO_Pin_1);	 //ʹ��1���ܽ�Ϊ 1

	if(!GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)) //���PB�ڵĵ�11���ܽŵĵ�ƽ
	GPIO_ResetBits(GPIOA,GPIO_Pin_2); //ʹ��3���ܽ�Ϊ 0 
	else
	GPIO_SetBits(GPIOA,GPIO_Pin_2);	  //ʹ��1���ܽ�Ϊ 1	*/

	GPIO_Write(GPIOA , ~GPIO_ReadInputData(GPIOB));

	
  }
}
/*******************************************************************************
*                           ����RCC
*******************************************************************************/
void RCC_Configuration(void)
{   
 //��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_DeInit();

  //���ⲿ���پ���
  RCC_HSEConfig(RCC_HSE_ON);

   //�ȴ��ⲿ����ʱ��׼����
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //�ⲿ����ʱ���Ѿ�׼���
  {								    
    //����FLASH��Ԥȡ����
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH�ӳ�2������
    FLASH_SetLatency(FLASH_Latency_2);
 	
  //����AHB(HCLK)ʱ��=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //����APB2(PCLK2)��=AHBʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    //ʹ��PLLʱ��
    RCC_PLLCmd(ENABLE);

   //�ȴ�PLLʱ�Ӿ���
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {
    }

  //����ϵͳʱ�� = PLLʱ��
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

   //���PLLʱ���Ƿ���Ϊϵͳʱ��
    while(RCC_GetSYSCLKSource() != 0x08)
    {
    }
  }
}

/*******************************************************************************
*                             NVIC���ú���
*******************************************************************************/
void NVIC_Configuration(void)
{
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}

/*******************************************************************************
*                              ��ʱ����
*******************************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

#ifdef  DEBUG
/*******************************************************************************
* Function Name  : assert_failed
* Description    : Reports the name of the source file and the source line number
*                  where the assert_param error has occurred.
* Input          : - file: pointer to the source file name
*                  - line: assert_param error line source number
* Output         : None
* Return         : None
*******************************************************************************/
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
