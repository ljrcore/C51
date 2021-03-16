 /*******************************************************************************
*  ����:                  �������������ʾ�¶�                                  *
*																			    *
*********************************************************************************
* Ŀ�ģ� 1.ͨ���������˽� DLASS18b20�Ļ���ԭ���ʹ�� ,��Ⲣ����18B20��������ı�д	*
*        2.�˽����ա�һ�ߡ����߽ӿڵĹ���ԭ��һ���̷����� 					*
* ����   ����18B20 �۲�����ܵ�ʵ���¶���ʾ
* ���ӣ� �����߽�JP8(P0��) �� J12 ������������Ͽ��Կ��¶���ʾ					*
* 																				*
* ���飺 ��Ҫ��ʱ�ȴ����ö�ʱ�ж�ʵ��ʱ������߳������ٶ�                   *
* ��ѧԱ�������������̣���DLASS18b20��C�����еĲ���                       	    *
********************************************************************************/
#include "stm32f10x_lib.h"


 /********************************Ӳ���ӿڶ���*********************************/
#define    LS138A  GPIO_Pin_5 //=P2^2;       //�ܽŶ���
#define    LS138B  GPIO_Pin_4 //=P2^3;
#define    LS138C  GPIO_Pin_3 //=P2^4; 


/******************************** �������� ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
ErrorStatus HSEStartUpStatus;

//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned char  Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40}; 
u32  LedOut[7],LedNumVal;
u8 Count;
static vu32 TimingDelay;



/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void SysTick_Configuration(void);
void HC595SendData(unsigned char SendVal);
void NOP(void);
extern GetTemp(void);						      //���������ⲿ����
extern unsigned int   Temperature;	              // ���������ⲿ����
void delay(unsigned int i);
void Tim_Setting(void);
void Delay_us(u32 nTime);


main()
{    unsigned char i; 	
	
	#ifdef DEBUG
//	debug();  //���ߵ���ʹ��
	#endif
	
	RCC_Configuration();      //ϵͳʱ�����ú��� 
	
	NVIC_Configuration();     //NVIC���ú��� 
	
    SysTick_Configuration();   //Systick���ú���
	
	Tim_Setting();	  //�����¼��趨����
	
	//����GPIOģ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB1Periph_TIM2 | RCC_APB2Periph_AFIO, ENABLE);
	//�ѵ���������ͨIO��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);  
	                        
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; //����GPIOΪͬһ���Ͷ˿�
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA�˿�
	GPIO_Init(GPIOB, &GPIO_InitStructure);   //��ʼ��GPIOB�˿�

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //��DS18B20��Ϊ16��
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;  //��©���	 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //��������Ƶ��Ϊ50HZ
	GPIO_Init(GPIOA, &GPIO_InitStructure);   //��ʼ��GPIOA�˿�

 
	
	GPIO_Write(GPIOA,0xffff);  //��GPIOA 16���˿�ȫ����Ϊ�ߵ�ƽ
	GPIO_Write(GPIOB,0xffff);  //��GPIOB 16���˿�ȫ����Ϊ�ߵ�
   
    

    while(1)
   {	
	  GetTemp();

   	  /********���½���18b20�������͵�LED�������ʾ*************/
      LedNumVal=Temperature;      //��ʵ���¶��͵�LedNumVal������

	  LedOut[0]=Disp_Tab[LedNumVal%10000/1000];
      LedOut[1]=Disp_Tab[LedNumVal%1000/100];
      LedOut[2]=Disp_Tab[LedNumVal%100/10];	 //ʮλ
      LedOut[3]=Disp_Tab[LedNumVal%10];    //��λ
  	  
    for(i=0; i<4; i++) 
	  {		
	GPIOA->BSRR = LedOut[i] & 0x00FF;   
    GPIOA->BRR = (~LedOut[i]) & 0x00FF;
	  			 	 	  	
		switch(i)					  
         {	    	  //138����
			case 0:	  //0 0 0 
			GPIO_ResetBits(GPIOB, LS138A);
			GPIO_ResetBits(GPIOB, LS138B);
			GPIO_ResetBits(GPIOB, LS138C);
			break;         
            case 1:	 //1 0 0 
			GPIO_SetBits(GPIOB, LS138A);
			GPIO_ResetBits(GPIOB, LS138B);
			GPIO_ResetBits(GPIOB, LS138C);
			 break;             	
            case 2:	 //0 1 0
			GPIO_ResetBits(GPIOB, LS138A);
			GPIO_SetBits(GPIOB, LS138B);
			GPIO_ResetBits(GPIOB, LS138C);
			break; 
            case 3:	 //1 1 0
			GPIO_SetBits(GPIOB, LS138A);
			GPIO_SetBits(GPIOB, LS138B);
			GPIO_ResetBits(GPIOB, LS138C);
			break; 

         }
		 
		Delay_us(2);
	  }

    }
}

void Tim_Setting(void)
{
  	/*-----------------------------------------------------------------------------*/

  /***772M�¶�ʱֵ�ļ��㣨��1+Ԥ��ƵTIM_Prescaler��/72*(1+��ʱ����TIM_Period)��*/
 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //����RCC��ʹ��TIMx

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 7199;  //ʱ��Ԥ��Ƶ�� ����:ʱ��Ƶ��=72/(ʱ��Ԥ��Ƶ+1)  
  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////��ʱ��ģʽ ���ϼ���  

  TIM_TimeBaseStructure.TIM_Period = 9999;//�Զ���װ�ؼĴ������ڵ�ֵ(��ʱʱ��)�ۼ� 0xFFFF��Ƶ�ʺ���������»����ж�(Ҳ��˵��ʱʱ�䵽)

  TIM_TimeBaseStructure.TIM_ClockDivision = 0; ////ʱ��ָ�ֵ  

  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //��ʼ����ʱ��2

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //���ж� ����ж�  


  TIM_Cmd(TIM2, ENABLE);  //�򿪶�ʱ��

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);


}

/******************************************************************************
*
*                         ��׼��ʱ����
*
**********************************************************************************/
void Delay_us(u32 nTime)
{
  /* Enable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);
  
  TimingDelay = nTime;

  while(TimingDelay != 0);

  /* Disable SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Disable);
  /* Clear SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Clear);
}

/*******************************************************************************
*
*                        ��ʱ�жϴ�����
*
*******************************************************************************/
void TIM2_IRQHandler(void)
{
  
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)  //����ƶ����ж��Ƿ���

  {

     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  //����жϴ���λ��

     Count++ ;
	 

   }
}

/*******************************************************************************
*
*                         ϵͳSystick �жϴ�����
*
*******************************************************************************/
void SysTick_Handler(void)   
{   
   if (TimingDelay != 0x00)
  { 
    TimingDelay--;
	
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


void SysTick_Configuration(void)   
{   
  /*  ����AHBʱ��ΪSysTickʱ��*/  
  SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);  //����8��Ƶ 
  
  /* ����SysTicks�ж���ռ���ȼ� 3�� �����ȼ�0*/  
  NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 3, 0);   
      
  /* ÿ1ms����һ��SysTick�ж� ��72M��ʱ����*/  
  SysTick_SetReload(9);     //�ò���ȡֵ������1��0x00FFFFFF֮��	 9/(72000 000/8)= 1us  1΢�����    
  
  /* ����SysTick�ж� */  
  SysTick_ITConfig(ENABLE);   
}  


/*******************************************************************************
*                             NVIC���ú���
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

  
       /* ������ʱ��2 */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
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






