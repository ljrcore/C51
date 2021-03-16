/*********************** ���пƼ� www.prechin.com*******************************
* 						 
*                      ����ͨ��ʵ�飨��ѯ��ʽ ����1��
* 
* 
*  ʵ��Ŀ�ģ� ��Ϥ�˽⴮�ڵ�����  
*
*  ���߷�ʽ�� �ο���������ʾ��ͼƬ
*  
*  ʵ������ �ô��ڵ��������յ�Ƭ���������ַ����� 
* 			 �����ڵ�����������  ������ 115200 ����λ 8 ֹͣλ 1  ��żλ NONE  ��
*
*******************************************************************************/

#include "stm32f10x_lib.h"

/*************************** �궨��***********************************************/
#define  USARTx                     USART1
#define  GPIOx                      GPIOA
#define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOA
#define  GPIO_RxPin                 GPIO_Pin_10
#define  GPIO_TxPin                 GPIO_Pin_9

/******************************** �������� ------------------------------------*/
USART_InitTypeDef USART_InitStructure;
ErrorStatus HSEStartUpStatus;


/*********************************�������� ------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void Uart1_PutString(u8* buf , u8 len);
u8 Uart1_PutChar(u8 ch);
void Delay(u32 nCount);


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

  RCC_Configuration();   //����ϵͳʱ��
       
  NVIC_Configuration();	 //NVIC����

  GPIO_Configuration();	 //GPIO�˿�����


  //�������ã� ������ 115200 ����λ 8 ֹͣλ 1  ��żλ NONE  
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    //��ʼ������
  USART_Init(USARTx, &USART_InitStructure);
  //��������
  USART_Cmd(USARTx, ENABLE);


  while (1)
  {  
    Uart1_PutString("���пƼ��Ƴ�ARM/51�ۺϰ��������32λ��������" ,50 );
    Delay(0x00ffff);
  }
}


/*******************************************************************************
* 
* 
*   Delay  ��ʱ����
* 
*
*******************************************************************************/
void Delay(u32 nCount)
{ 
 for(; nCount != 0 ; nCount--);

}

//����һ���ַ���
/*******************************************************************************
* Name  : Uart1_PutString
* Deion : print a string to the uart1
* Input : bufΪ�������ݵĵ�ַ , lenΪ�����ַ��ĸ���
*******************************************************************************/
void Uart1_PutString(u8* buf , u8 len)
{   u8 i;
    for(i=0;i<len;i++)
    {
        Uart1_PutChar(*buf++);
    }
}


//����һ���ַ�
/*******************************************************************************
* Name  : Uart1_PutChar
* Deion : printf a char to the uart.
*******************************************************************************/
u8 Uart1_PutChar(u8 ch)
{
    /* Write a character to the USART */
    USART_SendData(USART1, (u8) ch);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
   {
   }
   return ch;
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
    
  //����GPIOʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);

  //��������ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

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

  //����AFIOʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

   //����USARTx_TxΪ�����������
  GPIO_InitStructure.GPIO_Pin = GPIO_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOx, &GPIO_InitStructure);

  //���� USARTx_Rx Ϊ��������
  GPIO_InitStructure.GPIO_Pin = GPIO_RxPin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOx, &GPIO_InitStructure);

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
