/******************** ���пƼ� www.prechin.com ********************
* 
*                         FLASH��������ʵ��
* ʵ��Ŀ�ģ�  ��ϤFLASH�������
*
* ���ӷ����� �ο� �����ӷ����� ͼƬ��ʾ
*
* ʵ������ ��K1�趨һ�����ݣ� ����K2����ָ��FLASH���� �ٰ�K3�������� 
*            �ٰ�K4�����ݵ����������ʾ������ǰ�趨�����ݶԱ��¡�
*            Ҳ���Թص���Դ�󿪻�����K4������ʾ��ǰ���������
*
*******************************************************************************/


#include "stm32f10x_lib.h"

/* Private typedef -----------------------------------------------------------*/
typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;

/* Private define ------------------------------------------------------------*/
#define FLASH_PAGE_SIZE    ((u16)0x400)   //USE_STM3210B
#define StartAddr          ((u32)0x08008000)
#define EndAddr            ((u32)0x0800C000)



/******************************** �������� ------------------------------------*/
u32 EraseCounter = 0x00, Address = 0x00;
u32 Data;
vu32 NbrOfPage = 0x00;
volatile FLASH_Status FLASHStatus;
volatile TestStatus MemoryProgramStatus;
ErrorStatus HSEStartUpStatus;
bool EraseFlag  = FALSE , ProgramFlag = FALSE;

unsigned int jj = 0;
unsigned int  LedNumVal = 0 ,LedNumVal1 = 0;	   //��������
//�˱�Ϊ LED ����ģ, ��������� 0-9  - 
unsigned char Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};  //�������

//�˱�Ϊ8�������λѡ����, ��������� 1-8��  - 
unsigned char dispbit[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdF,0xbF,0x7F};    //λѡ����   ���ķ�������

unsigned int LedOut[10];		   //��������

/*********************************�������� -----------------------------------------------*/
void NVIC_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void Delay(vu32 nCount);
    
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : main
* Description    : Main program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif

  FLASHStatus = FLASH_COMPLETE;
  MemoryProgramStatus = PASSED;
  Data = 0x15041979;
  
  RCC_Configuration();  //����ϵͳʱ��

  NVIC_Configuration();	 //����NVIC�ж�

  FLASH_Unlock(); //����FLASH ��̲���������

  GPIO_Configuration();	  //����GPIO

  /* Define the number of page to be erased */
  NbrOfPage = (EndAddr - StartAddr) / FLASH_PAGE_SIZE;

    //������б�־��־
  FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	  
  /*  FLASH Word program of data 0x15041979 at addresses defined by StartAddr and EndAddr*/
   
  
  while (1)
  {
     
    unsigned int i ;
     
    if (++jj >= 0x00ff && GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0)
     { LedNumVal1++ ;
       jj = 0;
       EraseFlag = FALSE;
	   ProgramFlag = FALSE;
     }
   //GPIO_Pin_6 ����FLASH��ť
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) == 0 && !EraseFlag) 
   { 
     /* ���FLASH������ı�־λ */
     FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);	
     FLASHStatus = FLASH_ErasePage(StartAddr);
     EraseFlag = TRUE; //���˸�������־��FLASH�ɲ������������ޣ����⵱��ť��ס����ʱ��������FLASH.
    
    }//if
   
   //GPIO_Pin_5 �������ݵ�FLASH��ť
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2) == 0 && !ProgramFlag ) 
   {    Address = StartAddr;
	    FLASHStatus = FLASH_ProgramWord(Address, LedNumVal1);
		ProgramFlag = TRUE;
	
   }//if
    //GPIO_Pin_4 ��FLASH�ж������ݰ�ť
   if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3) == 0) 
   {
      Address = StartAddr;
      LedNumVal =  (*(vu32*) Address);
   
    }//if
         
     LedOut[0]=Disp_Tab[LedNumVal%10000/1000];
     LedOut[1]=Disp_Tab[LedNumVal%1000/100];
     LedOut[2]=Disp_Tab[LedNumVal%100/10];
     LedOut[3]=Disp_Tab[LedNumVal%10];
	 
	 LedOut[4]=Disp_Tab[LedNumVal1%100000/1000];	    
     LedOut[5]=Disp_Tab[LedNumVal1%1000/100];
     LedOut[6]=Disp_Tab[LedNumVal1%100/10];  //ʮλ
     LedOut[7]=Disp_Tab[LedNumVal1%10];     //��λ	 

	 for( i=0; i<8; i++) 
	 {	 
	    GPIOB->BSRR = LedOut[i]<<8 & 0xFF00;   
        GPIOB->BRR = (~(LedOut[i]<<8)) & 0xFF00;


         //ʹ�ò������λѡ 
	    GPIOB->BSRR = dispbit[i] & 0x00FF;   
        GPIOB->BRR = (~dispbit[i]) & 0x00FF;
       
        Delay(0x000ff);		 //ɨ����ʱ��
	 }	
   
  }
}

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
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
  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
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
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
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
  
   //����GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB ,ENABLE);

    //����AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

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

  while (1)
  {
  }
}
#endif

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
