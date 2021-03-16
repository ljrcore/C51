/*******************���пƼ� www.prechin.com**********************************
*					 
*                   ��STM32��AD��ȡ�ⲿģ������
*
*   ���߷����� �öŰ���AD0����AD1��λ����Ҳ�������ڹ����������������
*
*   ʵ��Ŀ�ģ� ��Ϥ�˽�AD��DMA����ȷ����
*               
*	��    �� ���е�ѹ�ı�ʱ���������ʾ��ǰ�ĵ�ѹֵ
*
*
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"


/******************************** �궨�� ------------------------------------*/
#define ADC1_DR_Address    ((u32)0x4001244C)
#define ADC3_DR_Address    ((u32)0x40013C4C)


/******************************** �������� ------------------------------------*/
ADC_InitTypeDef ADC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure; //����GPIO��ʼ���ṹ��
vu16 ADC1ConvertedValue = 0, ADC3ConvertedValue = 0;
ErrorStatus HSEStartUpStatus;
unsigned int jj = 0;
//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned int Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};  //�������

//�˱�Ϊ8�������λѡ����, ��������� 1-8��  - 
unsigned int dispbit[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdF,0xbF,0x7F};    //λѡ����   ���ķ�������

unsigned int LedOut[10];		   //��������
    
/*********************************�������� -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);



/*******************************************************************************
* 
*            ������
* 
*******************************************************************************/
int main(void)
{ unsigned int  LedNumVal = 0 ,LedNumVal1 = 0;	   //��������
#ifdef DEBUG
  debug();
#endif
 																				 
  //RCC����
  RCC_Configuration();

  // NVIC����
  NVIC_Configuration();

  //GPIO����
  GPIO_Configuration();

  //DMA1 ͨ������
  DMA_DeInit(DMA1_Channel1); //���ó�CH1 DMA�а�����7��ͨ����CH1-CH7��
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; //��DMA��ʼ��ַ
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC1ConvertedValue;//DMA�������ڴ��еı�����ַ
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //����DMA���䷽�� ������
  DMA_InitStructure.DMA_BufferSize = 1; //����DMA�ڴ���ʱ�������ĳ���
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //����DMA���������ģʽ
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;//����DMA���ڴ����ģʽ
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//DMA�ڷ���ʱÿ�β��������ݳ���
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA�Ĵ���ģʽ,�������ϵ�ѭ��ģʽ
  DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA�����ȼ��𣺿��Է�Ϊ4��
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//DMA��2��memory�еı���������ʵ�
  DMA_Init(DMA1_Channel1, &DMA_InitStructure); //DMA����ģ���ʼ�� 
  //����DMAͨ��1
  DMA_Cmd(DMA1_Channel1, ENABLE); 
     
  // ADC1 ����
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC1�����ڶ���ģʽ
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//ʹ��ɨ��
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;;//ADCת������������ģʽ
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//���������ת��
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//ת�������Ҷ���
  ADC_InitStructure.ADC_NbrOfChannel = 14;//ת��ͨ��Ϊͨ��1
  ADC_Init(ADC1, &ADC_InitStructure); //��ʼ��ADC 

  //ADC1ѡ���ŵ�14,�������ȼ�1,����ʱ��239.5������
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_28Cycles5);    
  //ʹ��ADC1ģ��DMA
  ADC_DMACmd(ADC1, ENABLE); 
    //��ADC1
  ADC_Cmd(ADC1, ENABLE);

 //����ADC1У׼�Ĵ��� 
  ADC_ResetCalibration(ADC1); 
 //�ȴ�ADC1У׼�������
  while(ADC_GetResetCalibrationStatus(ADC1));  

  //��ʼADC1У׼
  ADC_StartCalibration(ADC1); 

 //�ȴ�ADC1У׼���
  while(ADC_GetCalibrationStatus(ADC1)); 

 //ʹ��ADC1�����ʼת��
  ADC_SoftwareStartConvCmd(ADC1, ENABLE); 

 
  while (1)
  {  unsigned int i ;
       
     if (++jj >= 0x01ff)
     { LedNumVal1++ ;
       jj = 0;
     }
     LedNumVal = (u16)ADC1ConvertedValue*3300/4096;
     LedOut[0]=Disp_Tab[LedNumVal%10000/1000]|0x80;
     LedOut[1]=Disp_Tab[LedNumVal%1000/100];
     LedOut[2]=Disp_Tab[LedNumVal%100/10];
     LedOut[3]=Disp_Tab[LedNumVal%10];
	 
	 LedOut[4]=Disp_Tab[LedNumVal1%10000/1000];	   //ǧλ
     LedOut[5]=Disp_Tab[LedNumVal1%1000/100]|0x80;  //��λ��С����
     LedOut[6]=Disp_Tab[LedNumVal1%100/10];		   //ʮλ
     LedOut[7]=Disp_Tab[LedNumVal1%10];             //��λ	 

	 for( i=0; i<8; i++) 
	 {	 
	    //GPIO_Write(GPIOA,LedOut[i]<<8);
	    GPIOB->BSRR = LedOut[i]<<8 & 0xFF00;   
        GPIOB->BRR = (~(LedOut[i]<<8)) & 0xFF00;


        //GPIO_Write(GPIOB,dispbit[i]<<8);  //ʹ�ò������λѡ 
	    GPIOB->BSRR = dispbit[i] & 0x00FF;   
        GPIOB->BRR = (~dispbit[i]) & 0x00FF;
       
       Delay(0x0fff);		 //ɨ����ʱ��
	 }	  
  
   }
}


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);

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


  // ����DMA1ʱ�� Enable
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);

  //����ADC1ʱ�� 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1   , ENABLE); 
                   
    //�����Ǹ���ģ�鿪��ʱ��
    //����GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB ,ENABLE);
    //����AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //����DMAʱ��
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    //����ADC1ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}

/*************************************************
����: void GPIO_Config(void��
����: GPIO����
**************************************************/
void GPIO_Configuration(void)
{
   

   //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //����Ƶ��50M
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	
    //����PA0Ϊģ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
   

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
  NVIC_InitTypeDef NVIC_InitStructure;

#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif

  /* Configure and enable ADC interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQChannel;
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


