/******************** ���пƼ�  www.prechin.com  *******************************
*                      
*                     STM32�ڲ�ʱ��ʵ��
*  ʵ��Ŀ�ģ�  ��Ϥ�˽�RTC�����ü����ȡʱ��ķ�����
*  ���ӷ�����  J17��JP10   J16��JP11
*  ʵ������  ����8λ�����ʱ�Ӳ�ͣ���߶�
*
*
*******************************************************************************/


#include "stm32f10x_lib.h"


/******************************** �������� ---------------------------------------------------------*/
vu32 TimeDisplay = 0;
ErrorStatus HSEStartUpStatus;
u32 THH = 0, TMM = 0, TSS = 0;

unsigned int jj = 0;
unsigned int  LedNumVal = 0 ,LedNumVal1 = 0;	   //��������
//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned char Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};  //�������

//�˱�Ϊ8�������λѡ����, ��������� 1-8��  - 
unsigned char dispbit[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdF,0xbF,0x7F};    //λѡ����   ���ķ�������

unsigned int LedOut[10];		   //��������

/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void RTC_Configuration(void);
void NVIC_Configuration(void);
u32 Time_Regulate(void);
void Time_Adjust(void);
void Time_Show(void);
void Time_Display(u32 TimeVar);
void Delay(vu32 nCount);


/*******************************************************************************
                                  ������
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif

  RCC_Configuration();   //ϵͳʱ�����ú���   

  NVIC_Configuration();	 //NVIC���ú���

  GPIO_Configuration();	  //����GPIO


  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
  {
    //����RTC
    RTC_Configuration();

    /* Adjust time by values entred by the user on the hyperterminal */
    Time_Adjust();

     BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
  }
   else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
   // {
       /* Wait for RTC registers synchronization */
       RTC_WaitForSynchro();

    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
  }

#ifdef RTCClockOutput_Enable
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Disable the Tamper Pin */
  BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
                                 functionality must be disabled */

  /* Enable RTC Clock Output on Tamper Pin */
  BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif

  //�����λ��־
  RCC_ClearFlag();


 while (1)
{     unsigned int i ;
     
   // if (++jj >= 0x01ff)
   // { LedNumVal1++ ;
   //    jj = 0;
   //  }
      //�õ�ʱ�䲢��ʾ
     Time_Display(RTC_GetCounter());

     LedOut[0]=Disp_Tab[THH%100/10];
     LedOut[1]=Disp_Tab[THH%10];
     LedOut[2]=~0XBF; //����
     LedOut[3]=Disp_Tab[TMM%100/10];
	 
	 LedOut[4]=Disp_Tab[TMM%10];	    
     LedOut[5]=~0XBF;  //����
     LedOut[6]=Disp_Tab[TSS%100/10];  //ʮλ
     LedOut[7]=Disp_Tab[TSS%10];     //��λ	 

	 for( i=0; i<8; i++) 
	 {	 
	    GPIOB->BSRR = LedOut[i]<<8 & 0xFF00;   
        GPIOB->BRR = (~(LedOut[i]<<8)) & 0xFF00;
	         
	    GPIOB->BSRR = dispbit[i] & 0x00FF;   //ʹ�ò������λѡ  
        GPIOB->BRR = (~dispbit[i]) & 0x00FF;
       
        Delay(0x000ff);		 //ɨ����ʱ��
	 }	
  } //while 
}


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
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

    //����GPIO
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB ,ENABLE);

    //����AFIO
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
                         
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the nested vectored interrupt controller.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM
  /* Set the Vector Table base location at 0x20000000 */
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);


}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����Ƶ��50M
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*******************************************************************************
* Function Name  : RTC_Configuration
* Description    : Configures the RTC.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void RTC_Configuration(void)
{ 
  //����PWR��BKP��ʱ�ӣ�from APB1��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

    //�������
  PWR_BackupAccessCmd(ENABLE);

 //���ݼĴ���ģ�鸴λ
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
 
  //�ȴ��ȶ�
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}
  //RTCʱ��Դ���ó�LSE���ⲿ32.768K��
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  //RTC����
  RCC_RTCCLKCmd(ENABLE);

  //��������Ҫ�ȴ�APB1ʱ����RTCʱ��ͬ�������ܶ�д�Ĵ���
  RTC_WaitForSynchro();

  //��д�Ĵ���ǰ��Ҫȷ����һ�������Ѿ�����
  RTC_WaitForLastTask();
  
    //ʹ�����ж�
  RTC_ITConfig(RTC_IT_SEC, ENABLE);   

  //��д�Ĵ���ǰ��Ҫȷ����һ�������Ѿ�����
  RTC_WaitForLastTask();

  //����RTC��Ƶ����ʹRTCʱ��Ϊ1Hz
  //RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1)
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  //�ȴ��Ĵ���д�����
  RTC_WaitForLastTask();

    //�ȴ�д�����
  RTC_WaitForLastTask();

}

/*******************************************************************************
* Function Name  : Time_Adjust
* Description    : Adjusts time.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Time_Adjust(void)
{ 
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
  /* Change the current time */
  RTC_SetCounter(12*3600 + 2*60 + 0);
  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

/*******************************************************************************
* Function Name  : Time_Display
* Description    : Displays the current time.
* Input          : - TimeVar: RTC counter value.
* Output         : None
* Return         : None
*******************************************************************************/
void Time_Display(u32 TimeVar)
{

  /* Compute  hours */
  THH = TimeVar / 3600;
  /* Compute minutes */
  TMM = (TimeVar % 3600) / 60;
  /* Compute seconds */
  TSS = (TimeVar % 3600) % 60;

 }


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
  {}
}


/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
