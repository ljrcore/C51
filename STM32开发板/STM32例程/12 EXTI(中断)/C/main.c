/*******************���пƼ� www.prechin.com**********************************
*
*                           STM32�ж�ʵ��
*
*	ʵ��Ŀ�ģ� �����жϵ�����
*   ���ӷ����� �����߻�Ű��߷ֱ��� JP10--JP1   JP11--JP5
*	ʵ������ ��K7����LED�� �ٰ�ʱ��LED�ƻ�Ϩ��   
*
*******************************************************************************/


#include "stm32f10x_lib.h"


/******************************** �������� ------------------------------------*/
EXTI_InitTypeDef EXTI_InitStructure;
ErrorStatus HSEStartUpStatus;


/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);


/*******************************************************************************
* 
*            ������
* 
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif
  
 
  RCC_Configuration();	 //ϵͳʱ������   
 
  NVIC_Configuration();	//NVIC����
    
  GPIO_Configuration();  //����GPIO
  
  ///*��EXTI��6���ӵ�PB6*/
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6); 

  /* Configure Key Button EXTI Line to generate an interrupt on falling edge */  
  //���ð�ť�ж��ߴ�����ʽ
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
  EXTI_InitStructure.EXTI_LineCmd = ENABLE; //�ж���ʹ��
  EXTI_Init(&EXTI_InitStructure); //��ʼ���ж�

  /* Generate software interrupt: simulate a falling edge applied on Key Button EXTI line */
  EXTI_GenerateSWInterrupt(EXTI_Line6); //EXTI_Line6�ж����� �����ж��������,����д�жϴ�������
        
  while (1)
  {
  }
}


/*******************************************************************************
* 
*            RCC����
* 
*******************************************************************************/
void RCC_Configuration(void)
{
//��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
  RCC_DeInit();  

  //���ⲿ���پ���
  RCC_HSEConfig(RCC_HSE_ON); 

 //�ȴ��ⲿ����ʱ��׼����
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

  //�ⲿ����ʱ���Ѿ�׼���
  if(HSEStartUpStatus == SUCCESS)  
  {
    
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

   
    FLASH_SetLatency(FLASH_Latency_2);
  
   //����AHB(HCLK)ʱ��=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
  
    //����APB2(PCLK2)��=AHBʱ��
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //����APB1(PCLK1)��=AHB 1/2ʱ��
    RCC_PCLK1Config(RCC_HCLK_Div2);  

    //����ADCʱ��=PCLK2 1/4
    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
  
    //����PLLʱ�� == �ⲿ���پ���ʱ��*9
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); 
    
	//����ADCʱ��= PCLK2/4
    RCC_ADCCLKConfig(RCC_PCLK2_Div4);

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
   
  /* Enable Key Button GPIO Port, GPIO_LED and AFIO clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB
                         | RCC_APB2Periph_AFIO, ENABLE);
}

/*************************************************
����: void GPIO_Config(void��
����: GPIO����
**************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       //��������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;	  //���ø�������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configure the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);   //�����ж�������
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);  //�����ж����ȼ�
  
  /* Enable the EXTI9_5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel; //�ж�ͨ��
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =  0;  //ǿռ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;//�����ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ͨ���ж�ʹ��
  NVIC_Init(&NVIC_InitStructure);//��ʼ���ж�
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
