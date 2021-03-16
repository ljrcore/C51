/*******************普中科技 www.prechin.com**********************************
*					 
*                   用STM32的AD读取外部模拟输入
*
*   连线方法： 用杜邦线AD0或者AD1点位器，也可以连在光敏组和热敏电阻上
*
*   实验目的： 熟悉了解AD和DMA的正确配置
*               
*	现    象： 当有电压改变时，数码管显示当前的电压值
*
*
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"


/******************************** 宏定义 ------------------------------------*/
#define ADC1_DR_Address    ((u32)0x4001244C)
#define ADC3_DR_Address    ((u32)0x40013C4C)


/******************************** 变量定义 ------------------------------------*/
ADC_InitTypeDef ADC_InitStructure;
DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure; //定义GPIO初始化结构体
vu16 ADC1ConvertedValue = 0, ADC3ConvertedValue = 0;
ErrorStatus HSEStartUpStatus;
unsigned int jj = 0;
//此表为 LED 的字模, 共阴数码管 0-9  - 
unsigned int Disp_Tab[] = {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x40};  //段码控制

//此表为8个数码管位选控制, 共阴数码管 1-8个  - 
unsigned int dispbit[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdF,0xbF,0x7F};    //位选控制   查表的方法控制

unsigned int LedOut[10];		   //变量定义
    
/*********************************声明函数 -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);



/*******************************************************************************
* 
*            主函数
* 
*******************************************************************************/
int main(void)
{ unsigned int  LedNumVal = 0 ,LedNumVal1 = 0;	   //变量定义
#ifdef DEBUG
  debug();
#endif
 																				 
  //RCC配置
  RCC_Configuration();

  // NVIC配置
  NVIC_Configuration();

  //GPIO配置
  GPIO_Configuration();

  //DMA1 通道配置
  DMA_DeInit(DMA1_Channel1); //设置成CH1 DMA中包含了7个通道（CH1-CH7）
  DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; //给DMA起始地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC1ConvertedValue;//DMA连接在内存中的变量地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; //设置DMA传输方向 单向传输
  DMA_InitStructure.DMA_BufferSize = 1; //设置DMA在传输时缓冲区的长度
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //设置DMA的外设递增模式
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;//设置DMA的内存递增模式
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//DMA在访问时每次操作的数据长度
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA的传输模式,连续不断的循环模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_High; //DMA的优先级别：可以分为4级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;//DMA的2个memory中的变量互相访问的
  DMA_Init(DMA1_Channel1, &DMA_InitStructure); //DMA整个模块初始化 
  //开启DMA通道1
  DMA_Cmd(DMA1_Channel1, ENABLE); 
     
  // ADC1 配置
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent; //ADC1工作在独立模式
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;//使能扫描
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;;//ADC转换工作在连续模式
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//由软件控制转换
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//转换数据右对齐
  ADC_InitStructure.ADC_NbrOfChannel = 14;//转换通道为通道1
  ADC_Init(ADC1, &ADC_InitStructure); //初始化ADC 

  //ADC1选择信道14,音序器等级1,采样时间239.5个周期
  ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_28Cycles5);    
  //使能ADC1模块DMA
  ADC_DMACmd(ADC1, ENABLE); 
    //打开ADC1
  ADC_Cmd(ADC1, ENABLE);

 //重置ADC1校准寄存器 
  ADC_ResetCalibration(ADC1); 
 //等待ADC1校准重置完成
  while(ADC_GetResetCalibrationStatus(ADC1));  

  //开始ADC1校准
  ADC_StartCalibration(ADC1); 

 //等待ADC1校准完成
  while(ADC_GetCalibrationStatus(ADC1)); 

 //使能ADC1软件开始转换
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
	 
	 LedOut[4]=Disp_Tab[LedNumVal1%10000/1000];	   //千位
     LedOut[5]=Disp_Tab[LedNumVal1%1000/100]|0x80;  //百位带小数点
     LedOut[6]=Disp_Tab[LedNumVal1%100/10];		   //十位
     LedOut[7]=Disp_Tab[LedNumVal1%10];             //个位	 

	 for( i=0; i<8; i++) 
	 {	 
	    //GPIO_Write(GPIOA,LedOut[i]<<8);
	    GPIOB->BSRR = LedOut[i]<<8 & 0xFF00;   
        GPIOB->BRR = (~(LedOut[i]<<8)) & 0xFF00;


        //GPIO_Write(GPIOB,dispbit[i]<<8);  //使用查表法进行位选 
	    GPIOB->BSRR = dispbit[i] & 0x00FF;   
        GPIOB->BRR = (~dispbit[i]) & 0x00FF;
       
       Delay(0x0fff);		 //扫描间隔时间
	 }	  
  
   }
}


void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);

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


  // 开启DMA1时钟 Enable
   RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1 , ENABLE);

  //开启ADC1时钟 
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1   , ENABLE); 
                   
    //下面是给各模块开启时钟
    //启动GPIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB ,ENABLE);
    //启动AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //启动DMA时钟
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    //启动ADC1时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}

/*************************************************
函数: void GPIO_Config(void）
功能: GPIO配置
**************************************************/
void GPIO_Configuration(void)
{
   

   //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; //引脚频率50M
    GPIO_Init(GPIOB, &GPIO_InitStructure);

	
    //配置PA0为模拟输入
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


