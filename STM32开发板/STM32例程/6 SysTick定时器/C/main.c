/********************���пƼ�  www.prechin.com ************ ********************
* 
*                          SysTick��ʱ��ʵ��
*  
*    ʵ��Ŀ�ģ�	��Ϥ�˽�SysTick���ú͵δ�ʱ�趨
* 
*    ���߷����� �ο���������ʾ��ͼƬ
* 
*    ʵ������	D1��D2�������
* 
*******************************************************************************/

#include "stm32f10x_lib.h"
 
/******************************** �������� ------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
static vu32 TimingDelay;
ErrorStatus HSEStartUpStatus;
void TimingDelay_Decrement(void);

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nTime);


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

  RCC_Configuration();   //ϵͳʱ������ 
   
  NVIC_Configuration();	 //NVIC����

   //ϵͳĬ��SysTick��8��Ƶ��HCLK/8����ǰϵͳʱ��72M�Ļ� 72/8 = 9MHZ
  SysTick_SetReload(9000); //�������9000ʱ��������9000ʱ������1MS�ж�	   ��ʱ��װ��ֵ

  //����SysTick�ж�
  SysTick_ITConfig(ENABLE);												 //����
 
  //����GPIOB�˿�
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 
  GPIO_Write(GPIOB, GPIO_Pin_6 | GPIO_Pin_8);

  while (1)
  {

    GPIO_Write(GPIOB, (u16)~GPIO_ReadOutputData(GPIOB));
    Delay(500);	  //��ʱ500MS
     GPIO_Write(GPIOB, (u16)~GPIO_ReadOutputData(GPIOB));
    Delay(500);	 //��ʱ500MS  
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

}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Output         : None
* Return         : None
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
* 
*           ��ϵͳ�δ�����ʱ����
* 
*******************************************************************************/
void Delay(u32 nTime)
{
  //����SysTick������
  SysTick_CounterCmd(SysTick_Counter_Enable);
  
  TimingDelay = nTime;

  while(TimingDelay != 0);	   //���ȴ�


  //�ر�ϵͳ�δ�
  SysTick_CounterCmd(SysTick_Counter_Disable);
  //���SysTick ������
  SysTick_CounterCmd(SysTick_Counter_Clear);
}


/*******************************************************************************
*
*          SysTick�жϴ�����
* 
*******************************************************************************/
void SysTick_Handler(void)
{
   if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
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
