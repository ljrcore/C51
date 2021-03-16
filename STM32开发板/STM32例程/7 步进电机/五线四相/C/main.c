/***************************普中科技 www.prechin.com****************************
	                           步进电机实验
 实验目的： 熟悉了解STM32GPIO的操作和库函数的使用
*;   单双八拍工作方式：                                                         *
*;   A-AB-B-BC-C-CD-D-DA (即一个脉冲,转 3.75 度)      						    *
*实验注意： J14短路冒需断开 如果用步进电机内部供电 请将电源跳到5V位置 否则步进电机因电压过低，而不能转                 	                                             *
 实验现象：	电机旋转

*******************************************************************************/

#include "stm32f10x_lib.h"

/******************************** 变量定义 ---------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure;
ErrorStatus HSEStartUpStatus;

unsigned char  RUN[8]={0xfe,0xfc,0xfd,0xf9,0xfb,0xf3,0xf7,0xf6};  //步进电机相序表

/*********************************声明函数 -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);


/*******************************************************************************
                                  主函数
*******************************************************************************/
int main(void)
{  unsigned char i;
#ifdef DEBUG
  debug();
#endif

  RCC_Configuration(); //系统时钟配置函数    

  NVIC_Configuration();	 //NVIC配置函数

  //使能APB2总线外设时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);  //关闭调试 端口重新映射  使用仿真器调试时，不能用此语

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;  // 选择所有脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  //配置成推挽式输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //输出模式下 I/O输出速度 50M HZ
  GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA口
  GPIO_Init(GPIOB, &GPIO_InitStructure);  //初始化PB口

 while (1)
 { 
 
        for (i=0; i<8; i++)       //一个周期转3.75*8=30度
        {
          GPIO_Write(GPIOA, RUN[i]&0x1f); //取数据 从GPIO口输出
          Delay(0x01FFFF);             //调节转速
        }
  }

}


/*******************************************************************************
*                           配置RCC
*******************************************************************************/
void RCC_Configuration(void)
{   
 //复位RCC外部设备寄存器到默认值
  RCC_DeInit();

  //打开外部高速晶振
  RCC_HSEConfig(RCC_HSE_ON);

   //等待外部高速时钟准备好
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if(HSEStartUpStatus == SUCCESS)   //外部高速时钟已经准别好
  {								    
    //开启FLASH的预取功能
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    //FLASH延迟2个周期
    FLASH_SetLatency(FLASH_Latency_2);
 	
  //配置AHB(HCLK)时钟=SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1);  
  
   //配置APB2(PCLK2)钟=AHB时钟
    RCC_PCLK2Config(RCC_HCLK_Div1); 

    //配置APB1(PCLK1)钟=AHB 1/2时钟
    RCC_PCLK1Config(RCC_HCLK_Div2);

     //配置PLL时钟 == 外部高速晶体时钟*9  PLLCLK = 8MHz * 9 = 72 MHz 
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

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
}

/*******************************************************************************
*                             NVIC配置函数
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
*                              延时函数
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
