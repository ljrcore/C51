/*********************** 普中科技 www.prechin.com*******************************
* 						 
*                      串口通信实验（查询方式 串口1）
* 
* 
*  实验目的： 熟悉了解串口的配置  
*
*  接线方式： 参考“接线演示”图片
*  
*  实验现象： 用串口调试助手收单片机发出的字符数据 
* 			 （串口调试助手设置  波特率 115200 数据位 8 停止位 1  奇偶位 NONE  ）
*
*******************************************************************************/

#include "stm32f10x_lib.h"

/*************************** 宏定义***********************************************/
#define  USARTx                     USART1
#define  GPIOx                      GPIOA
#define  RCC_APB2Periph_GPIOx       RCC_APB2Periph_GPIOA
#define  GPIO_RxPin                 GPIO_Pin_10
#define  GPIO_TxPin                 GPIO_Pin_9

/******************************** 变量定义 ------------------------------------*/
USART_InitTypeDef USART_InitStructure;
ErrorStatus HSEStartUpStatus;


/*********************************声明函数 ------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void Uart1_PutString(u8* buf , u8 len);
u8 Uart1_PutChar(u8 ch);
void Delay(u32 nCount);


/*******************************************************************************
* 
*            主函数
* 
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif

  RCC_Configuration();   //配置系统时钟
       
  NVIC_Configuration();	 //NVIC配置

  GPIO_Configuration();	 //GPIO端口配置


  //串口配置： 波特率 115200 数据位 8 停止位 1  奇偶位 NONE  
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity =  USART_Parity_No ;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    //初始化串口
  USART_Init(USARTx, &USART_InitStructure);
  //启动串口
  USART_Cmd(USARTx, ENABLE);


  while (1)
  {  
    Uart1_PutString("普中科技推出ARM/51综合板带您进入32位处理世界" ,50 );
    Delay(0x00ffff);
  }
}


/*******************************************************************************
* 
* 
*   Delay  延时程序
* 
*
*******************************************************************************/
void Delay(u32 nCount)
{ 
 for(; nCount != 0 ; nCount--);

}

//发送一个字符串
/*******************************************************************************
* Name  : Uart1_PutString
* Deion : print a string to the uart1
* Input : buf为发送数据的地址 , len为发送字符的个数
*******************************************************************************/
void Uart1_PutString(u8* buf , u8 len)
{   u8 i;
    for(i=0;i<len;i++)
    {
        Uart1_PutChar(*buf++);
    }
}


//发送一个字符
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
*            RCC配置
* 
*******************************************************************************/
void RCC_Configuration(void)
{
  //复位RCC外部设备寄存器到默认值
  RCC_DeInit();  

  //打开外部高速晶振
  RCC_HSEConfig(RCC_HSE_ON); 

 //等待外部高速时钟准备好
  HSEStartUpStatus = RCC_WaitForHSEStartUp(); 

  //外部高速时钟已经准别好
  if(HSEStartUpStatus == SUCCESS)  
  {
    
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

   
    FLASH_SetLatency(FLASH_Latency_2);
  
   //配置AHB(HCLK)时钟=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
  
    //配置APB2(PCLK2)钟=AHB时钟
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //配置APB1(PCLK1)钟=AHB 1/2时钟
    RCC_PCLK1Config(RCC_HCLK_Div2);  

    //配置ADC时钟=PCLK2 1/4
    RCC_ADCCLKConfig(RCC_PCLK2_Div4); 
  
    //配置PLL时钟 == 外部高速晶体时钟*9
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9); 
    
	//配置ADC时钟= PCLK2/4
    RCC_ADCCLKConfig(RCC_PCLK2_Div4);

   //使能PLL时钟
    RCC_PLLCmd(ENABLE);  

   //等待PLL时钟就绪
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)  
    {
    }

    //配置系统时钟 = PLL时钟
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK); 

   //检查PLL时钟是否作为系统时钟
    while(RCC_GetSYSCLKSource() != 0x08)  
    {
    }
  }
    
  //开启GPIO时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOx, ENABLE);

  //开启串口时钟
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

  //开启AFIO时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

   //配置USARTx_Tx为复合推挽输出
  GPIO_InitStructure.GPIO_Pin = GPIO_TxPin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOx, &GPIO_InitStructure);

  //配置 USARTx_Rx 为浮空输入
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
