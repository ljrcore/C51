/******************** 普中科技 www.prechin.com************ ********************
* 
*                          1秒钟定时中断实验
* 
*   实验目的： 	熟悉了解定时中断的配置和如何设定定时时间。
* 
*   连接方法： 参考“连接说明”的图片演示
*
*   实验现象： 单位数码管显示每隔1秒数据变化一次
*
*******************************************************************************/


#include "stm32f10x_lib.h"


/******************************** 变量定义 ------------------------------------*/
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
TIM_OCInitTypeDef  TIM_OCInitStructure;
TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
ErrorStatus HSEStartUpStatus;

u16  PrescalerValue;
extern u8  Count;

// 此表为 LED 的字模          
unsigned char LED7Code[] = {~0x3F,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F,~0x77,~0x7C,~0x39,~0x5E,~0x79,~0x71};

/*********************************声明函数 -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void SysTick_Configuration(void);
void NVIC_Configuration(void);


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

  RCC_Configuration();  //系统时钟配置

  NVIC_Configuration();	 //NVIC配置

  GPIO_Configuration();	 //通用IO端口配置

  /*-----------------------------------------------------------------------------*/

  /***772M下定时值的计算（（1+预分频TIM_Prescaler）/72*(1+定时周期TIM_Period)）*/
 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //配置RCC，使能TIMx

  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 7199;  //时钟预分频数 例如:时钟频率=72/(时钟预分频+1)  
  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; ////定时器模式 向上计数  

  TIM_TimeBaseStructure.TIM_Period = 9999;//自动重装载寄存器周期的值(定时时间)累计 0xFFFF个频率后产生个更新或者中断(也是说定时时间到)

  TIM_TimeBaseStructure.TIM_ClockDivision = 0; ////时间分割值  

  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); //初始化定时器2

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //打开中断 溢出中断  

 //打开定时器
  TIM_Cmd(TIM2, ENABLE);  
   /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM2, ENABLE);

  while (1)
  {  
  	 GPIO_Write( GPIOB ,  LED7Code[Count%16]<<8); //将Count数据送到GPIOB高八位
	 
  }
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

  /* TIM1, GPIOA and GPIOB clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB2Periph_GPIOA |
                         RCC_APB2Periph_GPIOB, ENABLE);
}

/*************************************************
函数: void GPIO_Config(void）
功能: GPIO配置
**************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

   /* GPIOA Configuration: */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);  


  
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

  /* Enable the TIM1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  //NVIC_SystemHandlerPriorityConfig(SystemHandler_SysTick, 0, 0);
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
